package Classes.Swing.Main.Recruiter_Gui;

import javax.swing.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class Recruiter_Profile_Page_Gui
{
    private JPanel recruiter_profile_screen;
    private JTextField username_field;
    private JTextField password_field;
    private JTextField name_field;
    private JTextField surname_field;
    private JTextField reg_date_field;
    private JTextField email_field;
    private JTextField exp_years_field;
    private JComboBox firm_box;
    private JButton update_button;
    private JLabel username_label;
    private JLabel password_label;
    private JLabel name_label;
    private JLabel surname_label;
    private JLabel reg_date_label;
    private JLabel email_label;
    private JLabel exp_years_label;
    private JLabel firm_label;

    JPanel getRecruiter_profile_screen()
    {
        return recruiter_profile_screen;
    }

    Recruiter_Profile_Page_Gui(Connection conn, String user)
    {
        username_label.setText("Your username.");
        password_label.setText("Enter password.");
        name_label.setText("Enter name.");
        surname_label.setText("Enter surname.");
        email_label.setText("Enter email.");
        reg_date_label.setText("Your account registration date.");
        exp_years_label.setText("Enter exp years.");
        firm_label.setText("Choose firm name.");
        username_field.setEditable(false);
        reg_date_field.setEditable(false);

        if (conn != null)
        {
            ResultSet full_recruiter_set;
            String search_query = "SELECT * FROM erecruit.user inner join erecruit.recruiter on user.username = recruiter.username where user.username = ?";
            String firm_query = "SELECT * FROM erecruit.etaireia";
            try
            {
                PreparedStatement full_recruiter_statement = conn.prepareStatement(search_query);
                PreparedStatement firm_statement = conn.prepareStatement(firm_query);
                full_recruiter_statement.setString(1, user);
                full_recruiter_set = full_recruiter_statement.executeQuery();
                ResultSet firm;
                firm = firm_statement.executeQuery();
                ArrayList<String> firms = new ArrayList();
                while (firm.next())
                {
                    firms.add(firm.getString("afm"));
                }
                DefaultComboBoxModel table_model = new DefaultComboBoxModel( firms.toArray() );
                firm_box.setModel( table_model );
                while (full_recruiter_set.next())
                {
                    username_field.setText(full_recruiter_set.getString("username"));
                    password_field.setText(full_recruiter_set.getString("password"));
                    name_field.setText(full_recruiter_set.getString("name"));
                    surname_field.setText(full_recruiter_set.getString("surname"));
                    reg_date_field.setText(full_recruiter_set.getString("reg_date"));
                    email_field.setText(full_recruiter_set.getString("email"));
                    exp_years_field.setText(full_recruiter_set.getString("exp_years"));
                    firm_box.setSelectedItem(full_recruiter_set.getString("firm"));
                }

            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }

        update_button.addActionListener(e ->
        {
            String password = password_field.getText();
            if(password.isEmpty())
            {
                password = null;
            }
            String name = name_field.getText();
            String surname = surname_field.getText();
            String email = email_field.getText();
            if(email.isEmpty())
            {
                email = null;
            }
            String exp_year = exp_years_field.getText();
            int exp_years = 0;
            int exp_years_error = 0;
            if(!exp_year.isEmpty())
            {
                try
                {
                    exp_years = Integer.parseInt(exp_year);
                }
                catch (NumberFormatException ex)
                {
                    exp_years_error = 1;
                }
            }
            String firm = String.valueOf(firm_box.getSelectedItem());
            if(firm.equals("-"))
            {
                firm = null;
            }
            try
            {
                if (conn != null)
                {
                    if (!name.isEmpty())
                    {
                        if (!surname.isEmpty())
                        {
                            if (exp_years_error == 0)
                            {
                                String update_user_query = "UPDATE erecruit.user SET user.password = ?, user.name = ?, user.surname = ?, user.email = ? WHERE user.username = ?";
                                String update_recruiter_query = "UPDATE erecruit.recruiter SET recruiter.exp_years = ?, recruiter.firm = ? WHERE recruiter.username = ?";
                                PreparedStatement update_user_statement = conn.prepareStatement(update_user_query);
                                update_user_statement.setString(1, password);
                                update_user_statement.setString(2, name);
                                update_user_statement.setString(3, surname);
                                update_user_statement.setString(4, email);
                                update_user_statement.setString(5, user);
                                PreparedStatement update_recruiter_statement = conn.prepareStatement(update_recruiter_query);
                                update_recruiter_statement.setInt(1, exp_years);
                                update_recruiter_statement.setString(2, firm);
                                update_recruiter_statement.setString(3, user);
                                update_user_statement.executeUpdate();
                                update_recruiter_statement.executeUpdate();
                                JOptionPane.showMessageDialog(null, "Successful recruiter update.");
                            }
                            else
                            {
                                JOptionPane.showMessageDialog(null, "Recruiter exp_years must be an integer.");
                                String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                                PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                                fail_statement.setString(1, user);
                                fail_statement.setString(2, "recruiter");
                                fail_statement.executeUpdate();
                            }
                        }
                        else
                        {
                            JOptionPane.showMessageDialog(null, "Invalid empty surname.");
                            String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                            PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                            fail_statement.setString(1, user);
                            fail_statement.setString(2, "user");
                            fail_statement.executeUpdate();
                        }
                    }
                    else
                    {
                        JOptionPane.showMessageDialog(null, "Invalid empty name.");
                        String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                        PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                        fail_statement.setString(1, user);
                        fail_statement.setString(2, "user");
                        fail_statement.executeUpdate();
                    }
                }
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        });
    }
}
