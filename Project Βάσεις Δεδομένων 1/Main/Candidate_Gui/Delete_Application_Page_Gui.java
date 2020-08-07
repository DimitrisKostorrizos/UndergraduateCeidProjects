package Classes.Swing.Main.Candidate_Gui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.Vector;

public class Delete_Application_Page_Gui
{
    private JPanel delete_application_screen;
    private JTable applications_table;
    private JButton delete_button;
    private JLabel message_tip;
    private JScrollPane applications_panel;

    JPanel getDelete_application_screen()
    {
        return delete_application_screen;
    }

    Delete_Application_Page_Gui(Connection conn, String user)
    {
        message_tip.setText("Select applications from the table, click the button to delete the selected ones.You cannot select applications for closed jobs.");

        if (conn != null)
        {
            String[] columns = { "Job ID", "Start Date", "Salary", "Position", "Edra", "Recruiter", "Announce Date", "Submission Date", "Personality Grade", "Education Grade", "Experience Grade", "Selected" };
            ResultSet applications_set;
            String search_query = "SELECT * FROM erecruit.job inner join erecruit.applies on job.id = applies.job_id where applies.cand_usrname = ?";
            Vector rows = new Vector();
            try
            {
                PreparedStatement applications_statement = conn.prepareStatement(search_query);
                applications_statement.setString(1, user);
                applications_set = applications_statement.executeQuery();
                while (applications_set.next())
                {
                    Vector newRow = new Vector();
                    newRow.addElement(applications_set.getString("id"));
                    newRow.addElement(applications_set.getString("start_date"));
                    newRow.addElement(applications_set.getString("salary"));
                    newRow.addElement(applications_set.getString("position"));
                    newRow.addElement(applications_set.getString("edra"));
                    newRow.addElement(applications_set.getString("recruiter"));
                    newRow.addElement(applications_set.getString("announce_date"));
                    newRow.addElement(applications_set.getString("submission_date"));
                    newRow.addElement(applications_set.getString("personality_grade"));
                    newRow.addElement(applications_set.getString("education_grade"));
                    newRow.addElement(applications_set.getString("experience_grade"));
                    newRow.addElement(Boolean.FALSE);
                    rows.addElement(newRow);
                }
                Vector<String> column = new Vector<>(Arrays.asList(columns));
                DefaultTableModel model = new DefaultTableModel(rows, column)
                {
                    @Override
                    public Class<?> getColumnClass(int columnIndex)
                    {
                        return columnIndex == 11 ? Boolean.class : super.getColumnClass(columnIndex);
                    }

                    @Override
                    public boolean isCellEditable(int row, int column)
                    {
                        Date date = new Date();
                        SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");
                        formatter.format(date);
                        try
                        {
                            Date sub_date = formatter.parse(applications_table.getValueAt(row, 7).toString());
                            if(column == 11 && date.after(sub_date))
                            {
                                return false;
                            }
                        }
                        catch (ParseException e)
                        {
                            e.printStackTrace();
                        }
                        return column == 11;
                    }
                };
                applications_table.setModel(model);
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }

        delete_button.addActionListener(e ->
        {
            if (conn != null)
            {
                String delete_query = "DELETE FROM erecruit.applies WHERE applies.cand_usrname = ? and applies.job_id = ?";
                int row_count = applications_table.getRowCount();
                ArrayList<String> jobs = new ArrayList<>();
                for (int index = 0; index < row_count; index++)
                {
                    if(Boolean.parseBoolean(applications_table.getValueAt(index, 11).toString()))
                    {
                        jobs.add(applications_table.getValueAt(index, 0).toString());
                    }
                }
                try
                {
                    PreparedStatement delete_statement = conn.prepareStatement(delete_query);
                    delete_statement.setString(1, user);
                    for (String job : jobs)
                    {
                        delete_statement.setString(2, job);
                        delete_statement.executeUpdate();
                    }
                    JOptionPane.showMessageDialog(null, "Successful applications delete.");

                    String[] columns = {"Job ID", "Start Date", "Salary", "Position", "Edra", "Recruiter", "Announce Date", "Submission Date", "Personality Grade", "Education Grade", "Experience Grade", "Selected"};
                    ResultSet applications_set;
                    String search_query = "SELECT * FROM erecruit.job inner join erecruit.applies on job.id = applies.job_id where applies.cand_usrname = ?";
                    Vector rows = new Vector();
                    PreparedStatement applications_statement = conn.prepareStatement(search_query);
                    applications_statement.setString(1, user);
                    applications_set = applications_statement.executeQuery();
                    while (applications_set.next())
                    {
                        Vector newRow = new Vector();
                        newRow.addElement(applications_set.getString("id"));
                        newRow.addElement(applications_set.getString("start_date"));
                        newRow.addElement(applications_set.getString("salary"));
                        newRow.addElement(applications_set.getString("position"));
                        newRow.addElement(applications_set.getString("edra"));
                        newRow.addElement(applications_set.getString("recruiter"));
                        newRow.addElement(applications_set.getString("announce_date"));
                        newRow.addElement(applications_set.getString("submission_date"));
                        newRow.addElement(applications_set.getString("personality_grade"));
                        newRow.addElement(applications_set.getString("education_grade"));
                        newRow.addElement(applications_set.getString("experience_grade"));
                        newRow.addElement(Boolean.FALSE);
                        rows.addElement(newRow);
                    }
                    Vector<String> column = new Vector<>(Arrays.asList(columns));
                    DefaultTableModel model = new DefaultTableModel(rows, column)
                    {
                        @Override
                        public Class<?> getColumnClass(int columnIndex)
                        {
                            return columnIndex == 11 ? Boolean.class : super.getColumnClass(columnIndex);
                        }

                        @Override
                        public boolean isCellEditable(int row, int column)
                        {
                            Date date = new Date();
                            SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");
                            formatter.format(date);
                            try
                            {
                                Date sub_date = formatter.parse(applications_table.getValueAt(row, 7).toString());
                                if(column == 11 && date.after(sub_date))
                                {
                                    return false;
                                }
                            }
                            catch (ParseException e)
                            {
                                e.printStackTrace();
                            }
                            return column == 11;
                        }
                    };
                    applications_table.setModel(model);
                }
                catch (SQLException ex)
                {
                    ex.printStackTrace();
                }
            }
        });
    }
}