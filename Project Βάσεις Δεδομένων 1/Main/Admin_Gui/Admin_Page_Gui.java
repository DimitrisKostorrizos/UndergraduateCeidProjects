package Classes.Swing.Main.Admin_Gui;


import javax.swing.*;
import java.sql.Connection;

public class Admin_Page_Gui extends javax.swing.JPanel
{
    private JButton Accounts_Button;
    private JButton Record_Button;
    private JLabel intro_message;
    private JButton Insert_Button;
    private JPanel admin_screen;
    private String user;

    public JPanel getAdmin_Screen()
    {
        return admin_screen;
    }

    public void setUser(String user)
    {
        this.user = user;
    }

    public void setIntro_message(String t)
    {
        this.intro_message.setText(t);
    }

    public Admin_Page_Gui(Connection conn)
    {
        Accounts_Button.addActionListener(e ->
        {
            JFrame frame = new JFrame("account_screen");
            Account_Page_Gui account_Page = new Account_Page_Gui(conn, user);
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(account_Page.getAccount_Page_Screen());
            frame.setSize(700, 500);
            frame.setVisible(true);
        });

        Insert_Button.addActionListener(e ->
        {
            JFrame frame = new JFrame("insert_screen");
            Insert_Page_Gui insert_Page = new Insert_Page_Gui(conn);
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(insert_Page.getInsert_Page_Screen());
            frame.setSize(700, 500);
            frame.setVisible(true);
        });

        Record_Button.addActionListener(e ->
        {
            JFrame frame = new JFrame("record_screen");
            Record_Table_Gui record_Page = new Record_Table_Gui(conn);
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setContentPane(record_Page.getRecord_Table_Screen());
            frame.setSize(700, 500);
            frame.setVisible(true);
        });
    }
}
