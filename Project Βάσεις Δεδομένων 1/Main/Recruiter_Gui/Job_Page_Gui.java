package Classes.Swing.Main.Recruiter_Gui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Vector;

public class Job_Page_Gui
{
    private JPanel job_screen;
    private JSpinner start_date_spinner;
    private JTextField salary_field;
    private JTextField position_field;
    private JTextField edra_field;
    private JSpinner submission_date_spinner;
    private JButton insert_button;
    private JTable antikeim_table;
    private JLabel start_date_label;
    private JLabel salary_label;
    private JLabel position_label;
    private JLabel edra_label;
    private JLabel announce_date_label;
    private JLabel submission_date_label;
    private JScrollPane antikeim_pane;
    private JLabel antikeim_label;
    private JPanel stats_panel;

    JPanel getJob_screen()
    {
        return job_screen;
    }

    Job_Page_Gui(Connection conn, String user)
    {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        SpinnerDateModel startingModel = new SpinnerDateModel();
        SpinnerDateModel announceModel = new SpinnerDateModel();
        SpinnerDateModel submissionModel = new SpinnerDateModel();
        start_date_spinner.setModel(startingModel);
        submission_date_spinner.setModel(submissionModel);
        start_date_spinner.setEditor(new JSpinner.DateEditor(start_date_spinner, "yyyy-MM-dd"));
        submission_date_spinner.setEditor(new JSpinner.DateEditor(submission_date_spinner, "yyyy-MM-dd"));

        start_date_label.setText("Enter job starting date.");
        salary_label.setText("Enter job salary.");
        position_label.setText("Enter job position.");
        edra_label.setText("Enter job edra.");
        submission_date_label.setText("Enter job submission date.");
        antikeim_label.setText("Select antikeim this job requires.");

        String antikeim_query = "SELECT * FROM erecruit.antikeim";
        ResultSet antikeim_set;
        Vector rows = new Vector();
        if (conn != null )
        {
            try
            {
                PreparedStatement antikeim_statement = conn.prepareStatement(antikeim_query);
                antikeim_set = antikeim_statement.executeQuery();
                while(antikeim_set.next())
                {
                    Vector newRow = new Vector();
                    newRow.addElement(antikeim_set.getString("title"));
                    newRow.addElement(antikeim_set.getString("descr"));
                    newRow.addElement(antikeim_set.getString("belongs_to"));
                    newRow.addElement(Boolean.FALSE);
                    rows.addElement(newRow);
                }
                String[] columns = { "title", "descr", "belongs_to", "selected"};
                Vector<String> column = new Vector<>(Arrays.asList(columns));
                DefaultTableModel model = new DefaultTableModel(rows, column)
                {
                    @Override
                    public Class<?> getColumnClass(int columnIndex)
                    {
                        return columnIndex == 3 ? Boolean.class : super.getColumnClass(columnIndex);
                    }

                    @Override
                    public boolean isCellEditable(int row, int column)
                    {
                        return column == 3;
                    }
                };
                antikeim_table.setModel(model);
            }
            catch (SQLException e)
            {
                e.printStackTrace();
            }
        }

        insert_button.addActionListener(e ->
        {
            if (conn != null )
            {
                String starting_Date = dateFormat.format(start_date_spinner.getValue());
                String salar = salary_field.getText();
                float  salary = 0;
                int salary_error = 0;
                if(!salar.isEmpty())
                {
                    try
                    {
                        salary = Float.parseFloat(salar);
                    }
                    catch (NumberFormatException ex)
                    {
                        salary_error = 1;
                    }
                }
                String position = position_field.getText();
                if(position.isEmpty())
                {
                    position= null;
                }
                String edra = edra_field.getText();
                if(edra.isEmpty())
                {
                    edra = null;
                }
                String submission_date = dateFormat.format(submission_date_spinner.getValue());
                try
                {
                    if (salary_error == 0)
                    {
                        String insert_query = "insert into job (start_date, salary, position, edra, recruiter, announce_date, submission_date) values (?, ?, ?, ?, ?, NOW(), ?)";
                        PreparedStatement insert_statement = conn.prepareStatement(insert_query, PreparedStatement.RETURN_GENERATED_KEYS);
                        insert_statement.setString(1, starting_Date);
                        insert_statement.setFloat(2, salary);
                        insert_statement.setString(3, position);
                        insert_statement.setString(4, edra);
                        insert_statement.setString(5, user);
                        insert_statement.setString(6, submission_date);
                        insert_statement.executeUpdate();
                        ResultSet returned_id = insert_statement.getGeneratedKeys();
                        int id = returned_id.next() ? returned_id.getInt(1) : 0;
                        System.out.println(id);
                        int row_count = antikeim_table.getRowCount();
                        ArrayList<String> antikeim = new ArrayList<>();
                        for (int index = 0; index < row_count; index++)
                        {
                            if(Boolean.parseBoolean(antikeim_table.getValueAt(index, 3).toString()))
                            {
                                antikeim.add(antikeim_table.getValueAt(index, 0).toString());
                            }
                        }
                        String insert_antikeim_query = "insert into requires (job_id, antikeim_title) values (?, ?)";
                        PreparedStatement antikeim_statement = conn.prepareStatement(insert_antikeim_query);
                        antikeim_statement.setInt(1, id);
                        for (String anti : antikeim)
                        {
                            antikeim_statement.setString(2, anti);
                            antikeim_statement.executeUpdate();
                        }
                        JOptionPane.showMessageDialog(null, "Successful job insert.");
                     }
                    else
                    {
                        JOptionPane.showMessageDialog(null, "Salary must be a float.");
                        String fail_query = "insert into record values (?, now(), 'Fail', 'insert', ?);";
                        PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                        fail_statement.setString(1, user);
                        fail_statement.setString(2, "job");
                        fail_statement.executeUpdate();
                    }
                }
                catch (SQLException ex)
                {
                    ex.printStackTrace();
                }
            }
        });
    }
}
