package Classes.Swing.Main;

import java.sql.Connection;
import java.sql.DriverManager;

class ConnectionConfig
{
    static Connection ConnectDb()
    {
        Connection conn;
        try
        {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/erecruit?useTimezone=true&serverTimezone=UTC", "root", "user");
            return conn;
        }
        catch(Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }
}
