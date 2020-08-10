package Classes.Swing.Main.Recruiter_Gui;

import javax.swing.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Etaireia_Page_Gui
{
    private JPanel etaireia_screen;
    private JTextField afm_field;
    private JTextField doy_field;
    private JTextField name_field;
    private JTextField tel_field;
    private JTextField street_field;
    private JTextField num_field;
    private JTextField city_field;
    private JTextField country_field;
    private JTextField field_name_field;
    private JButton update_button;
    private JLabel afm_label;
    private JLabel doy_label;
    private JLabel name_label;
    private JLabel tel_label;
    private JLabel street_label;
    private JLabel num_label;
    private JLabel city_label;
    private JLabel country_label;
    private JLabel field_name_label;

    JPanel getEtaireia_screen()
    {
        return etaireia_screen;
    }

    Etaireia_Page_Gui(Connection conn, String user)
    {
        afm_label.setText("Your afm.");
        doy_label.setText("Your doy.");
        name_label.setText("Enter name.");
        tel_label.setText("Enter telephone number.");
        street_label.setText("Enter company street.");
        num_label.setText("Enter company number.");
        city_label.setText("Enter company city.");
        country_label.setText("Enter company country.");
        afm_field.setEditable(false);
        doy_field.setEditable(false);
        name_field.setEditable(false);

        if (conn != null)
        {
            ResultSet etaireia_set;
            String search_query = "SELECT * FROM erecruit.etaireia inner join erecruit.recruiter on etaireia.afm = recruiter.firm where recruiter.username = ?";
            try
            {
                PreparedStatement etaireia_statement = conn.prepareStatement(search_query);
                etaireia_statement.setString(1, user);
                etaireia_set = etaireia_statement.executeQuery();
                while (etaireia_set.next())
                {
                    afm_field.setText(etaireia_set.getString("AFM"));
                    doy_field.setText(etaireia_set.getString("DOY"));
                    name_field.setText(etaireia_set.getString("name"));
                    tel_field.setText(etaireia_set.getString("tel"));
                    street_field.setText(etaireia_set.getString("street"));
                    num_field.setText(etaireia_set.getString("num"));
                    city_field.setText(etaireia_set.getString("city"));
                    country_field.setText(etaireia_set.getString("country"));
                }
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }

        update_button.addActionListener(e ->
        {
            String afm = afm_field.getText();
            String tele = tel_field.getText();
            long tel = 0;
            int tel_error = 0;
            int valid_field_name = 1;
            if (!tele.isEmpty()) {
                try {
                    tel = Long.parseLong(tele);
                } catch (NumberFormatException ex) {
                    tel_error = 1;
                }
            }
            String street = street_field.getText();
            if (street.isEmpty()) {
                street = null;
            }
            String numb = num_field.getText();
            int num = 0;
            int num_error = 0;
            if (!numb.isEmpty()) {
                try {
                    num = Integer.parseInt(numb);
                } catch (NumberFormatException ex) {
                    num_error = 1;
                }
            }
            String city = city_field.getText();
            if (city.isEmpty()) {
                city = null;
            }
            String country = country_field.getText();
            if (country.isEmpty()) {
                country = null;
            }
            try
            {
                if (conn != null)
                {
                    if (tel_error == 0)
                    {
                        if (num_error == 0)
                        {
                            String update_etaireia_query = "UPDATE erecruit.etaireia SET etaireia.tel = ?, etaireia.street = ?, etaireia.num = ?, etaireia.city = ?, etaireia.country = ? WHERE etaireia.afm = ?";
                            PreparedStatement update_etaireia_statement = conn.prepareStatement(update_etaireia_query);
                            update_etaireia_statement.setLong(1, tel);
                            update_etaireia_statement.setString(2, street);
                            update_etaireia_statement.setInt(3, num);
                            update_etaireia_statement.setString(4, city);
                            update_etaireia_statement.setString(5, country);
                            update_etaireia_statement.setString(6, afm);
                            update_etaireia_statement.executeUpdate();
                            JOptionPane.showMessageDialog(null, "Successful etaireia update.");
                        }
                        else
                        {
                            JOptionPane.showMessageDialog(null, "Company num must be integer.");
                            String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                            PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                            fail_statement.setString(1, user);
                            fail_statement.setString(2, "etaireia");
                            fail_statement.executeUpdate();
                        }
                    }
                    else
                    {
                        JOptionPane.showMessageDialog(null, "Company tele must be integer.");
                        String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                        PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                        fail_statement.setString(1, user);
                        fail_statement.setString(2, "etaireia");
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
