package Classes.Swing.Main;


import javax.swing.*;
import java.sql.Connection;

public class Main
{
    public static void main(String[] args)
    {
        Connection connection;
        try
        {
            connection = ConnectionConfig.ConnectDb();
            if (connection != null)
            {
                JFrame frame = new JFrame("login_screen");
                Login_Page_Gui login_Page = new Login_Page_Gui(connection);
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setContentPane(login_Page.getLogin_Screen());
                frame.setSize(500, 500);
                frame.setVisible(true);
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
            JOptionPane.showMessageDialog(null, "Error: Connection to the database was unsuccessful.");
        }
    }
}
