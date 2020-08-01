package Classes.Swing.Main.Admin_Gui;

import javax.swing.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class Account_Page_Gui
{
    private JPanel Account_Page_Screen;
    private JTextField username_field;
    private JTextField email_field;
    private JTextField name_field;
    private JTextField surname_field;
    private JTextField password_field;
    private JButton insert_button;
    private JComboBox mode_box;
    private JComboBox firm_box;
    private JTextField exp_years_field;
    private JTextField sistatikes_field;
    private JTextField certificates_field;
    private JTextArea bio_area;
    private JLabel username_label;
    private JLabel password_label;
    private JLabel mode_label;
    private JLabel exp_years_label;
    private JLabel name_label;
    private JLabel surname_label;
    private JLabel firm_label;
    private JLabel sistatikes_label;
    private JLabel certificates_label;
    private JLabel bio_label;
    private JLabel email_label;
    private JScrollPane bio_pane;

    JPanel getAccount_Page_Screen()
    {
        return Account_Page_Screen;
    }

    Account_Page_Gui(Connection conn, String user)
    {
        mode_label.setText("Select candidate or recruiter");
        String[] options = { "candidate", "recruiter" };
        DefaultComboBoxModel table_model = new DefaultComboBoxModel( options );
        mode_box.setModel( table_model );
        username_label.setText("Enter candidate username.");
        password_label.setText("Enter candidate password.");
        name_label.setText("Enter candidate name.");
        surname_label.setText("Enter candidate surname.");
        email_label.setText("Enter candidate email.");
        bio_label.setText("Enter candidate bio.");
        sistatikes_label.setText("Enter candidate sistatikes.");
        certificates_label.setText("Enter candidate certificate.");
        exp_years_label.setVisible(false);
        exp_years_field.setVisible(false);
        firm_label.setVisible(false);
        firm_box.setVisible(false);
        ArrayList<String> afms = new ArrayList<>();
        afms.add("-");
        if (conn != null )
        {
            ResultSet firm_set;
            String search_query = "SELECT afm FROM erecruit.etaireia group by afm";
            try
            {
                PreparedStatement afm_statement = conn.prepareStatement(search_query);
                firm_set = afm_statement.executeQuery();
                while (firm_set.next())
                {
                    afms.add(firm_set.getString("afm"));
                }
                DefaultComboBoxModel afm_model = new DefaultComboBoxModel( afms.toArray() );
                firm_box.setModel( afm_model );
            } catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }

        mode_box.addActionListener(e ->
        {
            String mode = String.valueOf(mode_box.getSelectedItem());
            if(mode.equals("candidate"))
            {
                username_label.setText("Enter candidate username.");
                password_label.setText("Enter candidate password.");
                name_label.setText("Enter candidate name.");
                surname_label.setText("Enter candidate surname.");
                email_label.setText("Enter candidate email.");
                bio_label.setText("Enter candidate bio.");
                sistatikes_label.setText("Enter candidate sistatikes.");
                certificates_label.setText("Enter candidate certificate.");
                exp_years_label.setVisible(false);
                exp_years_field.setVisible(false);
                firm_label.setVisible(false);
                firm_box.setVisible(false);
                bio_pane.setVisible(true);
                bio_label.setVisible(true);
                bio_area.setVisible(true);
                sistatikes_label.setVisible(true);
                sistatikes_field.setVisible(true);
                certificates_label.setVisible(true);
                certificates_field.setVisible(true);
            }
            else
            {
                username_label.setText("Enter recruiter username.");
                password_label.setText("Enter recruiter password.");
                name_label.setText("Enter recruiter name.");
                surname_label.setText("Enter recruiter surname.");
                email_label.setText("Enter recruiter email.");
                exp_years_label.setText("Enter recruiter experience years.");
                firm_label.setText("Select recruiter firm.");
                bio_label.setVisible(false);
                bio_area.setVisible(false);
                bio_pane.setVisible(false);
                sistatikes_label.setVisible(false);
                sistatikes_field.setVisible(false);
                certificates_label.setVisible(false);
                certificates_field.setVisible(false);
                exp_years_label.setVisible(true);
                exp_years_field.setVisible(true);
                firm_label.setVisible(true);
                firm_box.setVisible(true);
            }
        });

        insert_button.addActionListener(e ->
        {
            String mode = String.valueOf(mode_box.getSelectedItem());
            String username = username_field.getText();
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
            try
            {
                if (conn != null)
                {
                    if (!username.isEmpty())
                    {
                        ResultSet username_set;
                        String search_query = "SELECT * FROM erecruit.user where user.username = ?";
                        PreparedStatement title_statement = conn.prepareStatement(search_query);
                        title_statement.setString(1, username);
                        username_set = title_statement.executeQuery();
                        if (!username_set.next())
                        {
                            if (!name.isEmpty())
                            {
                                if (!surname.isEmpty())
                                {
                                    String user_query = "insert into erecruit.user (username, password, name, surname, reg_date, email) values (?, ?, ?, ?, now(), ?)";
                                    PreparedStatement user_statement = conn.prepareStatement(user_query);
                                    user_statement.setString(1, username);
                                    user_statement.setString(2, password);
                                    user_statement.setString(3, name);
                                    user_statement.setString(4, surname);
                                    user_statement.setString(5, email);
                                    if (mode.equals("candidate"))
                                    {
                                        String bio = bio_area.getText();
                                        if (!bio.isEmpty())
                                        {
                                            String sistatikes = sistatikes_field.getText();
                                            if (sistatikes.isEmpty())
                                            {
                                                sistatikes = null;
                                            }
                                            String certificates = certificates_field.getText();
                                            if (certificates.isEmpty())
                                            {
                                                certificates = null;
                                            }
                                            String candidate_query = "insert into candidate(username, bio, sistatikes, certificates) values (?, ?, ?, ?)";
                                            PreparedStatement candidate_statement = conn.prepareStatement(candidate_query);
                                            candidate_statement.setString(1, username);
                                            candidate_statement.setString(2, bio);
                                            candidate_statement.setString(3, sistatikes);
                                            candidate_statement.setString(4, certificates);
                                            user_statement.executeUpdate();
                                            candidate_statement.executeUpdate();
                                            JOptionPane.showMessageDialog(null, "Successful candidate insert.");
                                        }
                                        else
                                        {
                                            JOptionPane.showMessageDialog(null, "Invalid empty bio.");
                                            String fail_query = "insert into record values (?, now(), 'Fail', 'insert', ?);";
                                            PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                                            fail_statement.setString(1, user);
                                            fail_statement.setString(2, mode);
                                            fail_statement.executeUpdate();
                                        }
                                    }
                                    else
                                    {
                                        String exp_years = exp_years_field.getText();
                                        Integer years = null;
                                        if (!exp_years.isEmpty())
                                        {
                                            years = Integer.valueOf(exp_years);
                                        }
                                        String firm = String.valueOf(firm_box.getSelectedItem());
                                        if (firm.equals("-"))
                                        {
                                            firm = null;
                                        }
                                        String recruiter_query = "insert into recruiter (username, exp_years, firm) values (?, ?, ?)";
                                        PreparedStatement recruiter_statement = conn.prepareStatement(recruiter_query);
                                        recruiter_statement.setString(1, username);
                                        if (years == null)
                                        {
                                            recruiter_statement.setString(2, null);
                                        }
                                        else
                                        {
                                            recruiter_statement.setInt(2, years);
                                        }
                                        recruiter_statement.setString(3, firm);
                                        user_statement.executeUpdate();
                                        recruiter_statement.executeUpdate();
                                        JOptionPane.showMessageDialog(null, "Successful recruiter insert.");
                                    }
                                }
                                else
                                {
                                    JOptionPane.showMessageDialog(null, "Invalid empty surname.");
                                    String fail_query = "insert into record values (?, now(), 'Fail', 'insert', ?);";
                                    PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                                    fail_statement.setString(1, user);
                                    fail_statement.setString(2, "user");
                                    fail_statement.executeUpdate();
                                }
                            }
                            else
                            {
                                JOptionPane.showMessageDialog(null, "Invalid empty name.");
                                String fail_query = "insert into record values (?, now(), 'Fail', 'insert', ?);";
                                PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                                fail_statement.setString(1, user);
                                fail_statement.setString(2, "user");
                                fail_statement.executeUpdate();
                            }
                        }
                        else
                        {
                            JOptionPane.showMessageDialog(null, "Invalid existing username.");
                            String fail_query = "insert into record values (?, now(), 'Fail', 'insert', ?);";
                            PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                            fail_statement.setString(1, user);
                            fail_statement.setString(2, "user");
                            fail_statement.executeUpdate();
                        }
                    }
                    else
                    {
                        JOptionPane.showMessageDialog(null, "Invalid empty username.");
                        String fail_query = "insert into record values (?, now(), 'Fail', 'insert', ?);";
                        PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                        fail_statement.setString(1, user);
                        fail_statement.setString(2, "user");
                        fail_statement.executeUpdate();
                    }
                }
            }
            catch (NumberFormatException NaN)
            {
                JOptionPane.showMessageDialog(null, "Invalid exp_years, not an integer.");
                try
                {
                    String fail_query = "insert into record values (?, now(), 'Fail', 'insert', ?);";
                    PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                    fail_statement.setString(1, user);
                    fail_statement.setString(2, mode);
                    fail_statement.executeUpdate();
                }
                catch (SQLException ex)
                {
                    ex.printStackTrace();
                }
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        });
    }
}