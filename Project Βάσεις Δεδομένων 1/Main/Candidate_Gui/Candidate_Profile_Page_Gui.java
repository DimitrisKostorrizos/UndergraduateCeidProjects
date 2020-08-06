package Classes.Swing.Main.Candidate_Gui;

import javax.swing.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Candidate_Profile_Page_Gui
{
    private JPanel candidate_profile_screen;
    private JTextField username_field;
    private JTextField name_field;
    private JTextField password_field;
    private JTextField surname_field;
    private JButton save_button;
    private JTextField reg_date_field;
    private JTextField email_field;
    private JTextField sistatikes_field;
    private JTextField certificates_field;
    private JLabel username_label;
    private JLabel password_label;
    private JLabel name_label;
    private JLabel surname_label;
    private JLabel reg_date_label;
    private JLabel email_label;
    private JLabel bio_label;
    private JLabel sistatikes_label;
    private JLabel certificates_label;
    private JTextArea bio_area;
    private JScrollPane area;

    JPanel getCandidate_profile_screen()
    {
        return candidate_profile_screen;
    }

    Candidate_Profile_Page_Gui(Connection conn, String user)
    {
        username_label.setText("Your username.");
        password_label.setText("Enter password.");
        name_label.setText("Enter name.");
        surname_label.setText("Enter surname.");
        email_label.setText("Enter email.");
        bio_label.setText("Enter bio.");
        reg_date_label.setText("Your account registration date.");
        sistatikes_label.setText("Enter sistatikes.");
        certificates_label.setText("Enter certificate.");
        username_field.setEditable(false);
        reg_date_field.setEditable(false);

        if (conn != null)
        {
            ResultSet full_candidate_set;
            String search_query = "SELECT * FROM erecruit.user inner join erecruit.candidate on user.username = candidate.username where user.username = ?";
            try
            {
                PreparedStatement full_candidate_statement = conn.prepareStatement(search_query);
                full_candidate_statement.setString(1, user);
                full_candidate_set = full_candidate_statement.executeQuery();
                while (full_candidate_set.next())
                {
                    username_field.setText(full_candidate_set.getString("username"));
                    password_field.setText(full_candidate_set.getString("password"));
                    name_field.setText(full_candidate_set.getString("name"));
                    surname_field.setText(full_candidate_set.getString("surname"));
                    reg_date_field.setText(full_candidate_set.getString("reg_date"));
                    email_field.setText(full_candidate_set.getString("email"));
                    bio_area.setText(full_candidate_set.getString("bio"));
                    sistatikes_field.setText(full_candidate_set.getString("sistatikes"));
                    certificates_field.setText(full_candidate_set.getString("certificates"));
                }
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }

        save_button.addActionListener(e ->
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
            String bio = bio_area.getText();
            String sistatikes = sistatikes_field.getText();
            if(sistatikes.isEmpty())
            {
                sistatikes = null;
            }
            String certificates = certificates_field.getText();
            if(certificates.isEmpty())
            {
                certificates = null;
            }
            try
            {
                if (conn != null)
                {
                    if (!name.isEmpty())
                    {
                        if (!surname.isEmpty())
                        {
                            if (!bio.isEmpty())
                            {
                                String update_user_query = "UPDATE erecruit.user SET user.password = ?, user.name = ?, user.surname = ?, user.email = ? WHERE user.username = ?";
                                String update_candidate_query = "UPDATE erecruit.candidate SET candidate.bio = ?, candidate.sistatikes = ?, candidate.certificates = ? WHERE candidate.username = ?";
                                PreparedStatement update_user_statement = conn.prepareStatement(update_user_query);
                                update_user_statement.setString(1, password);
                                update_user_statement.setString(2, name);
                                update_user_statement.setString(3, surname);
                                update_user_statement.setString(4, email);
                                update_user_statement.setString(5, user);
                                PreparedStatement update_candidate_statement = conn.prepareStatement(update_candidate_query);
                                update_candidate_statement.setString(1, bio);
                                update_candidate_statement.setString(2, sistatikes);
                                update_candidate_statement.setString(3, certificates);
                                update_candidate_statement.setString(4, user);
                                update_user_statement.executeUpdate();
                                update_candidate_statement.executeUpdate();
                                JOptionPane.showMessageDialog(null, "Successful candidate update.");
                            }
                            else
                            {
                                JOptionPane.showMessageDialog(null, "Invalid empty bio.");
                                String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                                PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                                fail_statement.setString(1, user);
                                fail_statement.setString(2, "candidate");
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