package Classes.Swing.Main.Recruiter_Gui;

import javax.swing.*;
import java.sql.Connection;

public class Recruiter_Page_Gui
{
    private String user;
    private JPanel recruiter_screen;
    private JLabel intro_message;
    private JButton etaireia_button;
    private JButton profile_button;
    private JButton insert_button;
    private JButton check_button;
    private JButton jobs_button;

    public JPanel getRecruiter_screen()
    {
        return recruiter_screen;
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

    public Recruiter_Page_Gui(Connection conn)
    {
        etaireia_button.addActionListener(e ->
        {
            JFrame frame = new JFrame("etaireia_screen");
            Etaireia_Page_Gui etaireia_Page = new Etaireia_Page_Gui(conn, this.getUser());
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(etaireia_Page.getEtaireia_screen());
            frame.setSize(600, 600);
            frame.setVisible(true);
        });

        profile_button.addActionListener(e ->
        {
            JFrame frame = new JFrame("profile_screen");
            Recruiter_Profile_Page_Gui profile_Page = new Recruiter_Profile_Page_Gui(conn, this.getUser());
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(profile_Page.getRecruiter_profile_screen());
            frame.setSize(600, 600);
            frame.setVisible(true);
        });

        insert_button.addActionListener(e ->
        {
            JFrame frame = new JFrame("job_screen");
            Job_Page_Gui job_Page = new Job_Page_Gui(conn, this.getUser());
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(job_Page.getJob_screen());
            frame.setSize(1000, 600);
            frame.setVisible(true);
        });

        check_button.addActionListener(e ->
        {
            JFrame frame = new JFrame("check_jobs_screen");
            Check_Job_Page_Gui check_Job_Page = new Check_Job_Page_Gui(conn, this.getUser());
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(check_Job_Page.getCheck_jobs_screen());
            frame.setSize(1300, 600);
            frame.setVisible(true);
        });

        jobs_button.addActionListener(e ->
        {
            JFrame frame = new JFrame("company_screen");
            Etaireia_Jobs_Page_Gui company_Page = new Etaireia_Jobs_Page_Gui(conn, this.getUser());
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(company_Page.getEtaireia_jobs_screen());
            frame.setSize(1100, 600);
            frame.setVisible(true);
        });
    }
}
