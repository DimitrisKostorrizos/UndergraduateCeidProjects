package Classes.Swing.Main.Admin_Gui;


import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Vector;

public class Record_Table_Gui
{
    private JPanel Record_Table_Screen;
    private JComboBox table_name_box;
    private JComboBox username_box;
    private JButton search_button;
    private JLabel text_tip;
    private JTable result_table;
    private JScrollPane Table_Panel;
    private JSpinner starting_date_spinner;
    private JSpinner ending_date_spinner;
    private JCheckBox starting_date_checkbox;
    private JCheckBox ending_date_checkbox;
    private JLabel user_label;
    private JLabel date_label;
    private JLabel checkbox_label;

    JPanel getRecord_Table_Screen()
    {
        return Record_Table_Screen;
    }

    Record_Table_Gui(Connection conn)
    {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        SpinnerDateModel startingModel = new SpinnerDateModel();
        SpinnerDateModel endingModel = new SpinnerDateModel();
        starting_date_spinner.setModel(startingModel);
        ending_date_spinner.setModel(endingModel);
        starting_date_spinner.setEditor(new JSpinner.DateEditor(starting_date_spinner, "yyyy-MM-dd HH:mm:ss"));
        ending_date_spinner.setEditor(new JSpinner.DateEditor(ending_date_spinner, "yyyy-MM-dd HH:mm:ss"));
        text_tip.setText("Choose table.");
        user_label.setText("Choose user.");
        date_label.setText("Set the starting and ending dates.");
        checkbox_label.setText("Click to include the dates to your search.");
        String username_query = "SELECT username FROM erecruit.record group by username";
        ResultSet username;
        ArrayList<String> user_names = new ArrayList<>();
        user_names.add("-");
        String[] table_names = { "-", "antikeim", "applies", "candidate", "degree", "etaireia", "field", "has_degree", "interview", "job", "languages", "project", "record", "recruiter", "requires", "user" };
        DefaultComboBoxModel table_model = new DefaultComboBoxModel( table_names);
        table_name_box.setModel( table_model );
        if (conn != null )
        {
            try
            {
                PreparedStatement record_username_statement = conn.prepareStatement(username_query);
                username = record_username_statement.executeQuery();
                while(username.next())
                {
                    user_names.add(username.getString("username"));
                }
                DefaultComboBoxModel username_model = new DefaultComboBoxModel( user_names.toArray());
                username_box.setModel( username_model );
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }

        search_button.addActionListener(e ->
        {
            if (conn != null )
            {
                ResultSet record;
                String table = String.valueOf(table_name_box.getSelectedItem());
                String column_username = String.valueOf(username_box.getSelectedItem());
                String starting_Date = dateFormat.format(starting_date_spinner.getValue());
                String ending_Date = dateFormat.format(ending_date_spinner.getValue());
                String search_query = "SELECT * FROM erecruit.record where record.table = \'" + table + "\' and username = \'" + column_username + "\'";
                if(table.equals("-") && column_username.equals("-"))
                {
                    search_query = "SELECT * FROM erecruit.record";
                }
                else
                {
                    if (table.equals("-"))
                    {
                        search_query = "SELECT * FROM erecruit.record where username = \'" + column_username + "\'";
                    }
                    if (column_username.equals("-"))
                    {
                        search_query = "SELECT * FROM erecruit.record where record.table = \'" + table + "\'";
                    }
                }
                if(starting_date_checkbox.isSelected() && ending_date_checkbox.isSelected())
                {
                    search_query = search_query + " having (datediff(record.datetime,\'" + starting_Date + "\') >= 0 and datediff(record.datetime,\'" + ending_Date + "\') <= 0)";
                }
                else
                {
                    if(starting_date_checkbox.isSelected())
                    {
                        search_query = search_query + " having datediff(record.datetime,\'" + starting_Date +"\') >= 0";
                    }
                    if (ending_date_checkbox.isSelected())
                    {
                        search_query = search_query + " having datediff(record.datetime,\'" + ending_Date + "\') <= 0";
                    }
                }
                try
                {
                    PreparedStatement record_statement = conn.prepareStatement(search_query);
                    record = record_statement.executeQuery();
                    Vector rows = new Vector();
                    while(record.next())
                    {
                        Vector newRow = new Vector();
                        newRow.addElement(record.getString("username"));
                        newRow.addElement(record.getString("datetime"));
                        newRow.addElement(record.getString("status"));
                        newRow.addElement(record.getString("type"));
                        newRow.addElement(record.getString("table"));
                        rows.addElement(newRow);
                    }
                    String[] columns ={ "Username", "Datetime", "Status", "Type", "Table" };
                    Vector<String> column = new Vector<>(Arrays.asList(columns));
                    DefaultTableModel model = new DefaultTableModel(rows, column);
                    result_table.setModel(model);
                }
                catch (SQLException ex)
                {
                    ex.printStackTrace();
                }
            }
        });
    }
}