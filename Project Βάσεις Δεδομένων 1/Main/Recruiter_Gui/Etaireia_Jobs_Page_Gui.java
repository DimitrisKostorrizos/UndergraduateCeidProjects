package Classes.Swing.Main.Recruiter_Gui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.Vector;

public class Etaireia_Jobs_Page_Gui
{
    private JPanel etaireia_jobs_screen;
    private JTable jobs_table;
    private JButton update_button;
    private JLabel message_tip;
    private JScrollPane jobs_pane;

    JPanel getEtaireia_jobs_screen()
    {
        return etaireia_jobs_screen;
    }

    Etaireia_Jobs_Page_Gui(Connection conn, String user)
    {
        message_tip.setText("Check/Edit your company's jobs in the table.You can edit jobs created by you.");

        if (conn != null)
        {
            String[] columns = {"Job ID", "Start Date", "Salary", "Position", "Edra", "Recruiter", "Announce Date", "Submission Date"};
            ResultSet jobs_set;
            String search_query = "select * from erecruit.job inner join recruiter on job.recruiter = recruiter.username where recruiter.firm = (select firm from erecruit.recruiter where recruiter.username = ?)";
            Vector rows = new Vector();
            try
            {
                PreparedStatement applications_statement = conn.prepareStatement(search_query);
                applications_statement.setString(1, user);
                jobs_set = applications_statement.executeQuery();
                while (jobs_set.next())
                {
                    Vector newRow = new Vector();
                    newRow.addElement(jobs_set.getString("id"));
                    newRow.addElement(jobs_set.getString("start_date"));
                    newRow.addElement(jobs_set.getString("salary"));
                    newRow.addElement(jobs_set.getString("position"));
                    newRow.addElement(jobs_set.getString("edra"));
                    newRow.addElement(jobs_set.getString("recruiter"));
                    newRow.addElement(jobs_set.getString("announce_date"));
                    newRow.addElement(jobs_set.getString("submission_date"));
                    rows.addElement(newRow);
                }
                Vector<String> column = new Vector<>(Arrays.asList(columns));
                DefaultTableModel model = new DefaultTableModel(rows, column)
                {

                    @Override
                    public boolean isCellEditable(int row, int column)
                    {
                        String job_recruiter = jobs_table.getValueAt(row, 5).toString();
                        if(job_recruiter.equals(user))
                        {
                            return column != 0 && column != 6 && column != 5;
                        }
                        return false;
                    }
                };
                jobs_table.setModel(model);
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }

        update_button.addActionListener(e ->
        {
            if (conn != null)
            {
                SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
                int error = 0;
                int start_date_error = 0;
                Date start = null;
                int submission_date_error = 0;
                Date submission = null;
                float salary = 0;
                int salary_error = 0;
                String update_query = "update erecruit.job set job.start_date = ?, job.salary = ?, job.position = ?, job.edra = ?, job.submission_date = ?  WHERE job.id = ?";
                int row_count = jobs_table.getRowCount();
                for (int index = 0; index < row_count; index++)
                {
                    if(error == 0)
                    {
                        if (jobs_table.getValueAt(index, 5).toString().equals(user))
                        {
                            try
                            {
                                try
                                {
                                    start = dateFormat.parse(jobs_table.getValueAt(index, 1).toString());
                                }
                                catch (ParseException ex)
                                {
                                    start_date_error = 1;
                                    error = 1;
                                }
                                if (start_date_error == 0)
                                {
                                    String start_date = dateFormat.format(start);
                                    try
                                    {
                                        submission = dateFormat.parse(jobs_table.getValueAt(index, 7).toString());
                                    }
                                    catch (ParseException ex)
                                    {
                                        submission_date_error = 1;
                                        error = 1;
                                    }
                                    if (submission_date_error == 0)
                                    {
                                        String submission_date = dateFormat.format(submission);
                                        try
                                        {
                                            salary = Float.parseFloat(jobs_table.getValueAt(index, 2).toString());
                                        }
                                        catch (NumberFormatException ex)
                                        {
                                            salary_error = 1;
                                            error = 1;
                                        }
                                        if (salary_error == 0)
                                        {
                                            String position = jobs_table.getValueAt(index, 3).toString();
                                            String edra = jobs_table.getValueAt(index, 4).toString();
                                            int id = Integer.parseInt(jobs_table.getValueAt(index, 0).toString());
                                            PreparedStatement update_statement = conn.prepareStatement(update_query);
                                            update_statement.setString(1, start_date);
                                            update_statement.setFloat(2, salary);
                                            update_statement.setString(3, position);
                                            update_statement.setString(4, edra);
                                            update_statement.setString(5, submission_date);
                                            update_statement.setInt(6, id);
                                            update_statement.executeUpdate();
                                        }
                                        else
                                        {
                                            JOptionPane.showMessageDialog(null, "Salary must be a float number.");
                                            String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                                            PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                                            fail_statement.setString(1, user);
                                            fail_statement.setString(2, "job");
                                            fail_statement.executeUpdate();
                                        }
                                    }
                                    else
                                    {
                                        JOptionPane.showMessageDialog(null, "Submission date must have the yyyy-MM-dd format.");
                                        String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                                        PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                                        fail_statement.setString(1, user);
                                        fail_statement.setString(2, "job");
                                        fail_statement.executeUpdate();
                                    }
                                }
                                else
                                {
                                    JOptionPane.showMessageDialog(null, "Start date must have the yyyy-MM-dd format.");
                                    String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
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
                    }
                }
                if(error == 0)
                {
                    JOptionPane.showMessageDialog(null, "Successful update.");
                }
            }
        });
    }
}
