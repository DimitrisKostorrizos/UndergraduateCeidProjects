package Classes.Swing.Main.Recruiter_Gui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.event.ActionEvent;
import java.sql.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.Vector;

public class Check_Job_Page_Gui
{
    private JPanel check_jobs_screen;
    private JTable jobs_table;
    private JScrollPane jobs_pane;
    private JLabel message_tip;
    private JButton update_button;

    JPanel getCheck_jobs_screen()
    {
        return check_jobs_screen;
    }

    Check_Job_Page_Gui(Connection conn, String user)
    {
        message_tip.setText("Check/Edit jobs that you have created from the table.You can also check/complete a jobs evaluation and check a job's rankings");

        if (conn != null)
        {
            Date current_date = new Date();
            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
            String[] columns = {"Job ID", "Start Date", "Salary", "Position", "Edra", "Recruiter", "Announce Date", "Submission Date", "Status", "Number of Applications", "Call Procedure", "Evaluation"};
            ResultSet jobs_set;
            String search_query = "select * from erecruit.job where job.recruiter = ?";
            Vector rows = new Vector();
            try
            {
                PreparedStatement job_statement = conn.prepareStatement(search_query);
                job_statement.setString(1, user);
                jobs_set = job_statement.executeQuery();
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
                    Date sub_date = dateFormat.parse(jobs_set.getString("submission_date"));
                    if (current_date.after(sub_date))
                    {
                        newRow.addElement("Closed");
                    }
                    else
                    {
                        newRow.addElement("Open");
                    }
                    ResultSet number_set;
                    String application_query = "select count(cand_usrname) from erecruit.applies where applies.job_id = ?";
                    PreparedStatement applications_statement = conn.prepareStatement(application_query);
                    int job_id = Integer.parseInt(jobs_set.getString("id"));
                    applications_statement.setInt(1, job_id);
                    number_set = applications_statement.executeQuery();
                    if (number_set.next())
                    {
                        newRow.addElement(number_set.getInt(1));
                    }
                    rows.addElement(newRow);
                }
                Vector<String> column = new Vector<>(Arrays.asList(columns));
                DefaultTableModel model = new DefaultTableModel(rows, column)
                {
                    @Override
                    public boolean isCellEditable(int row, int column)
                    {
                        String job_recruiter = jobs_table.getValueAt(row, 5).toString();
                        String stat = jobs_table.getValueAt(row, 8).toString();
                        if(stat.equals("Open") && column == 11)
                        {
                            return false;
                        }
                        if (job_recruiter.equals(user))
                        {
                            return column != 0 && column != 6 && column != 5 && column != 8 && column != 9;
                        }
                        return false;
                    }
                };
                jobs_table.setModel(model);
                Action call_procedure = new AbstractAction()
                {
                    public void actionPerformed(ActionEvent e)
                    {
                        int job_id = Integer.parseInt(jobs_table.getValueAt(jobs_table.getSelectedRow(), 0).toString());
                        JFrame frame = new JFrame("stored_procedure_screen");
                        Stored_Procedure_Gui stored_procedure_Page = new Stored_Procedure_Gui(conn, job_id);
                        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                        frame.setContentPane(stored_procedure_Page.getStored_procedure_screen());
                        frame.setSize(1000, 600);
                        frame.setVisible(true);
                    }
                };
                JTableColumnClass procedureColumn = new JTableColumnClass(jobs_table, call_procedure, 10);
                Action evaluation = new AbstractAction()
                {
                    public void actionPerformed(ActionEvent e)
                    {
                        String stat = jobs_table.getValueAt(jobs_table.getSelectedRow(), 8).toString();
                        if(stat.equals("Closed"))
                        {
                            int job_id = Integer.parseInt(jobs_table.getValueAt(jobs_table.getSelectedRow(), 0).toString());
                            JFrame frame = new JFrame("applications_interviews_screen");
                            Applications_Interviews_Page_Gui applications_interviews_Page = new Applications_Interviews_Page_Gui(conn, user, job_id);
                            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                            frame.setContentPane(applications_interviews_Page.getApplications_interviews_screen());
                            frame.setSize(1000, 600);
                            frame.setVisible(true);
                        }
                        else
                        {
                            JOptionPane.showMessageDialog(null, "This job is still open.");
                        }
                    }
                };
                JTableColumnClass evaluationColumn = new JTableColumnClass(jobs_table, evaluation, 11);
            }
            catch (SQLException | ParseException ex)
            {
                ex.printStackTrace();
            }
        }

        update_button.addActionListener(e ->
        {
            if (conn != null)
            {
                SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
                Date start = null;
                int start_error = 0;
                int error = 0;
                Date submission = null;
                int submission_error = 0;
                float salary = 0;
                int salary_error =0;
                String update_query = "update erecruit.job set job.start_date = ?, job.salary = ?, job.position = ?, job.edra = ?, job.submission_date = ?  WHERE job.id = ?";
                int row_count = jobs_table.getRowCount();
                for (int index = 0; index < row_count; index++)
                {
                    if(error == 0)
                    {
                        try
                        {
                            try
                            {
                                start = dateFormat.parse(jobs_table.getValueAt(index, 1).toString());
                            }
                            catch (ParseException ex)
                            {
                                error = 1;
                                start_error = 1;
                            }
                            if (start_error == 0)
                            {
                                String start_date = dateFormat.format(start);
                                try
                                {
                                    submission = dateFormat.parse(jobs_table.getValueAt(index, 7).toString());
                                }
                                catch (ParseException ex)
                                {
                                    error = 1;
                                    submission_error = 1;
                                }
                                if (submission_error == 0)
                                {
                                    String submission_date = dateFormat.format(submission);
                                    try
                                    {
                                        salary = Float.parseFloat(jobs_table.getValueAt(index, 2).toString());
                                    }
                                    catch (NumberFormatException ex)
                                    {
                                        error = 1;
                                        salary_error = 1;
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
                                        JOptionPane.showMessageDialog(null, "Salary must be a float number");
                                        String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                                        PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                                        fail_statement.setString(1, user);
                                        fail_statement.setString(2, "job");
                                        fail_statement.executeUpdate();
                                    }
                                }
                                else
                                {
                                    JOptionPane.showMessageDialog(null, "Submission Date must have yyyy-MM-dd format");
                                    String fail_query = "insert into record values (?, now(), 'Fail', 'update', ?);";
                                    PreparedStatement fail_statement = conn.prepareStatement(fail_query);
                                    fail_statement.setString(1, user);
                                    fail_statement.setString(2, "job");
                                    fail_statement.executeUpdate();
                                }
                            }
                            else
                            {
                                JOptionPane.showMessageDialog(null, "Start Date must have yyyy-MM-dd format");
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
                if(error == 0)
                {
                    JOptionPane.showMessageDialog(null, "Successful update.");
                }
            }
        });
    }
}
