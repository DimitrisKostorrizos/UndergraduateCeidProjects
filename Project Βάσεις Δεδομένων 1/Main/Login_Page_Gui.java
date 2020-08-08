package Classes.Swing.Main;

import Classes.Swing.Main.Admin_Gui.Admin_Page_Gui;
import Classes.Swing.Main.Candidate_Gui.Candidate_Page_Gui;
import Classes.Swing.Main.Recruiter_Gui.Recruiter_Page_Gui;

import javax.swing.*;
import java.sql.*;

public class Login_Page_Gui extends javax.swing.JPanel
{
    private JPanel login_screen;
    private JPasswordField password_field;
    private JButton login_button;
    private JTextField username_field;

    JPanel getLogin_Screen()
    {
        return login_screen;
    }

    public String getUsername()
    {
        return username_field.getText();
    }

    private char[] getPassword()
    {
        return password_field.getPassword();
    }

    Login_Page_Gui(Connection conn)
    {
        login_button.addActionListener(e ->
        {
            String urn = getUsername();
            String pass = String.valueOf(getPassword());
            String query = "SELECT username FROM erecruit.user where (username = ? and password = ?)";
            ResultSet login;
            if (conn != null)
            {
                if(!urn.isEmpty())
                {
                    if(!pass.isEmpty())
                    {
                        try
                        {
                            PreparedStatement user_password_statement = conn.prepareStatement(query);
                            user_password_statement.setString(1, urn);
                            user_password_statement.setString(2, pass);
                            login = user_password_statement.executeQuery();
                            if (login.next())
                            {
                                JOptionPane.showMessageDialog(null, "Login Successful.");
                                String login_query = "insert into erecruit.login values(?,NOW())";
                                PreparedStatement login_statement = conn.prepareStatement(login_query);
                                login_statement.setString(1, urn);
                                login_statement.executeUpdate();
                                String candidate_query = "SELECT username FROM erecruit.candidate where username = ?";
                                ResultSet candidate;
                                PreparedStatement candidate_statement = conn.prepareStatement(candidate_query);
                                candidate_statement.setString(1, urn);
                                candidate = candidate_statement.executeQuery();
                                if (candidate.next())
                                {
                                    JFrame frame = new JFrame("candidate_screen");
                                    Candidate_Page_Gui candidate_Page = new Candidate_Page_Gui(conn);
                                    frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                                    frame.setContentPane(candidate_Page.getCandidate_screen());
                                    frame.setSize(500, 500);
                                    frame.setVisible(true);
                                    candidate_Page.setIntro_message(" Welcome, Candidate " + urn + ". Your available actions are the following:");
                                    candidate_Page.setUser(urn);
                                }
                                else
                                {
                                    String recruiter_query = "SELECT username FROM erecruit.recruiter where username = ?";
                                    ResultSet recruiter;
                                    PreparedStatement recruiter_statement = conn.prepareStatement(recruiter_query);
                                    recruiter_statement.setString(1, urn);
                                    recruiter = recruiter_statement.executeQuery();
                                    if (recruiter.next())
                                    {
                                        JFrame frame = new JFrame("recruiter_screen");
                                        Recruiter_Page_Gui recruiter_page = new Recruiter_Page_Gui(conn);
                                        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                                        frame.setContentPane(recruiter_page.getRecruiter_screen());
                                        frame.setSize(500, 500);
                                        frame.setVisible(true);
                                        recruiter_page.setIntro_message(" Welcome, Recruiter " + urn + ". Your available actions are the following:");
                                        recruiter_page.setUser(urn);
                                    }
                                    else
                                    {
                                        JFrame frame = new JFrame("admin_screen");
                                        Admin_Page_Gui admin_Page = new Admin_Page_Gui(conn);
                                        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                                        frame.setContentPane(admin_Page.getAdmin_Screen());
                                        frame.setSize(500, 500);
                                        frame.setVisible(true);
                                        admin_Page.setIntro_message(" Welcome, Admin " + urn + ". Your available actions are the following:");
                                        admin_Page.setUser(urn);
                                    }
                                }
                            }
                            else
                            {
                                JOptionPane.showMessageDialog(null, "Invalid username and password combination. Try again.");
                            }
                        }
                        catch (SQLException ex)
                        {
                            ex.printStackTrace();
                        }
                    }
                    else
                    {
                        JOptionPane.showMessageDialog(null, "Invalid empty password.");
                    }
                }
                else
                {
                    JOptionPane.showMessageDialog(null, "Invalid empty username.");
                }
            }
        });
    }
}

