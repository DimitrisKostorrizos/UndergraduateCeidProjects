package Classes.Swing.Main.Candidate_Gui;

import javax.swing.*;
import java.sql.Connection;

public class Candidate_Page_Gui
{
    private String user;
    private JPanel candidate_screen;
    private JButton profile_button;
    private JButton applies_button;
    private JButton delete_button;
    private JLabel intro_message;

    public JPanel getCandidate_screen()
    {
        return candidate_screen;
    }

    public void setIntro_message(String intro_message)
    {
        this.intro_message.setText(intro_message);
    }

    public void setUser(String user)
    {
        this.user = user;
    }

    private String getUser()
    {
        return user;
    }

    public Candidate_Page_Gui(Connection conn)
    {
        profile_button.addActionListener(e ->
        {
            JFrame frame = new JFrame("profile_screen");
            Candidate_Profile_Page_Gui profile_Page = new Candidate_Profile_Page_Gui(conn, this.getUser());
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(profile_Page.getCandidate_profile_screen());
            frame.setSize(600, 600);
            frame.setVisible(true);
        });

        applies_button.addActionListener(e ->
        {
            JFrame frame = new JFrame("application_screen");
            Application_Page_Gui application_Page = new Application_Page_Gui(conn, this.getUser());
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(application_Page.getApplication_page());
            frame.setSize(1100, 600);
            frame.setVisible(true);
        });

        delete_button.addActionListener(e ->
        {
            JFrame frame = new JFrame("delete_screen");
            Delete_Application_Page_Gui delete_Page = new Delete_Application_Page_Gui(conn, this.getUser());
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(delete_Page.getDelete_application_screen());
            frame.setSize(1300, 600);
            frame.setVisible(true);
        });
    }
}
