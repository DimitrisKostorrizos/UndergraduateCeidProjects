package Classes.Swing.Main.Candidate_Gui;


import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class Application_Page_Gui
{
    private JPanel application_page;
    private JTable application_stats_table;
    private JButton search_button;
    private JButton applies_button;
    private JLabel search_label;
    private JScrollPane application_stats_pane;
    private JTable available_application_table;
    private JScrollPane available_application_pane;
    private JLabel application_label;

    JPanel getApplication_page()
    {
        return application_page;
    }

    Application_Page_Gui(Connection conn, String user)
    {
        search_label.setText("View your applications in the table below.");
        application_label.setText("Choose jobs from the table, to create an application.");
        String jobs_query = "SELECT * FROM erecruit.job where id not in (SELECT job_id FROM erecruit.applies where applies.cand_usrname = ? group by job_id) and datediff(submission_date, CURDATE()) >= 0";
        ResultSet available_set;
        if (conn != null)
        {
            try
            {
                PreparedStatement jobs_statement = conn.prepareStatement(jobs_query);
                jobs_statement.setString(1, user);
                available_set = jobs_statement.executeQuery();
                Vector rows = new Vector();
                while (available_set.next())
                {
                    Vector newRow = new Vector();
                    newRow.addElement(available_set.getString("id"));
                    newRow.addElement(available_set.getString("start_date"));
                    newRow.addElement(available_set.getString("salary"));
                    newRow.addElement(available_set.getString("position"));
                    newRow.addElement(available_set.getString("edra"));
                    newRow.addElement(available_set.getString("recruiter"));
                    newRow.addElement(available_set.getString("announce_date"));
                    newRow.addElement(available_set.getString("submission_date"));
                    newRow.addElement(Boolean.FALSE);
                    rows.addElement(newRow);
                }
                String[] columns = { "Job ID", "Start Date", "Salary", "Position", "Edra", "Recruiter", "Announce Date", "Submission Date", "Selected" };
                Vector<String> column = new Vector<>(Arrays.asList(columns));
                DefaultTableModel model = new DefaultTableModel(rows, column)
                {
                    @Override
                    public Class<?> getColumnClass(int columnIndex)
                    {
                        return columnIndex == 8 ? Boolean.class : super.getColumnClass(columnIndex);
                    }

                    @Override
                    public boolean isCellEditable(int row, int column)
                    {
                        return column == 8;
                    }
                };
                available_application_table.setModel(model);
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }

        applies_button.addActionListener(e ->
        {
            if (conn != null)
            {
                ResultSet available_job_set;
                String insert_query = "insert into applies (cand_usrname, job_id, personality_grade, education_grade, experience_grade) values (?, ?, null, null, null)";
                int row_count = available_application_table.getRowCount();
                ArrayList<String> jobs = new ArrayList<>();
                for (int index = 0; index < row_count; index++)
                {
                    if(Boolean.parseBoolean(available_application_table.getValueAt(index, 8).toString()))
                    {
                        jobs.add(available_application_table.getValueAt(index, 0).toString());
                    }
                }
                try
                {
                    PreparedStatement insert_statement = conn.prepareStatement(insert_query);
                    insert_statement.setString(1, user);
                    for (String job : jobs)
                    {
                        insert_statement.setString(2, job);
                        insert_statement.executeUpdate();
                    }
                    JOptionPane.showMessageDialog(null, "Successful applications creation.");
                    PreparedStatement jobs_statement = conn.prepareStatement(jobs_query);
                    jobs_statement.setString(1, user);
                    available_job_set = jobs_statement.executeQuery();
                    Vector rows = new Vector();
                    while (available_job_set.next())
                    {
                        Vector newRow = new Vector();
                        newRow.addElement(available_job_set.getString("id"));
                        newRow.addElement(available_job_set.getString("start_date"));
                        newRow.addElement(available_job_set.getString("salary"));
                        newRow.addElement(available_job_set.getString("position"));
                        newRow.addElement(available_job_set.getString("edra"));
                        newRow.addElement(available_job_set.getString("recruiter"));
                        newRow.addElement(available_job_set.getString("announce_date"));
                        newRow.addElement(available_job_set.getString("submission_date"));
                        newRow.addElement(Boolean.FALSE);
                        rows.addElement(newRow);
                    }
                    String[] columns = { "Job ID", "Start Date", "Salary", "Position", "Edra", "Recruiter", "Announce Date", "Submission Date", "Selected" };
                    Vector<String> column = new Vector<>(Arrays.asList(columns));
                    DefaultTableModel model = new DefaultTableModel(rows, column)
                    {
                        @Override
                        public Class<?> getColumnClass(int columnIndex)
                        {
                            return columnIndex == 8 ? Boolean.class : super.getColumnClass(columnIndex);
                        }

                        @Override
                        public boolean isCellEditable(int row, int column)
                        {
                            return column == 8;
                        }
                    };
                    available_application_table.setModel(model);
                }
                catch (SQLException ex)
                {
                    ex.printStackTrace();
                }
            }
        });

        search_button.addActionListener(e ->
        {
            String search_query = "SELECT * FROM erecruit.job inner join erecruit.applies on job.id = applies.job_id where applies.cand_usrname = ?";
            String applies_query = "SELECT * FROM erecruit.applies where applies.job_id = ?";
            ResultSet applications_set;
            if (conn != null)
            {
                try
                {
                    PreparedStatement applications_statement = conn.prepareStatement(search_query);
                    applications_statement.setString(1, user);
                    applications_set = applications_statement.executeQuery();
                    Vector rows = new Vector();
                    Date current_date = new Date();
                    SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");
                    formatter.format(current_date);
                    while (applications_set.next())
                    {
                        Vector newRow = new Vector();
                        newRow.addElement(applications_set.getString("id"));
                        try
                        {
                            Date sub_date = formatter.parse(applications_set.getString("submission_date"));
                            if(!current_date.after(sub_date))
                            {
                                newRow.addElement("Open for submission.");
                                newRow.addElement("-");
                            }
                            else
                            {
                                ResultSet applies_set;
                                PreparedStatement applies_statement = conn.prepareStatement(applies_query);
                                applies_statement.setString(1, applications_set.getString("id"));
                                applies_set = applies_statement.executeQuery();
                                int empty_grade = 0;
                                while (applies_set.next() && empty_grade == 0)
                                {
                                    String personality_grade = applications_set.getString("personality_grade");
                                    String education_grade = applications_set.getString("education_grade");
                                    String experience_grade = applications_set.getString("experience_grade");
                                    if(personality_grade == null || education_grade == null || experience_grade == null)
                                    {
                                        empty_grade = 1;
                                        newRow.addElement("Under assessment.");
                                        newRow.addElement("-");
                                    }
                                }
                                if(empty_grade == 0)
                                {
                                    newRow.addElement("Assessment completed.");
                                    applies_set.beforeFirst();
                                    float user_grade = 0;
                                    ArrayList<Float> total_grades = new ArrayList<>();
                                    while (applies_set.next() )
                                    {
                                        Float pe_grade = Float.valueOf(applications_set.getString("personality_grade"));
                                        Float ed_grade = Float.valueOf(applications_set.getString("education_grade"));
                                        Float ex_grade = Float.valueOf(applications_set.getString("experience_grade"));
                                        total_grades.add(pe_grade + ed_grade + ed_grade);
                                        String candidate = applications_set.getString("cand_usrname");
                                        if(candidate.equals(user))
                                        {
                                            user_grade = pe_grade + ed_grade + ed_grade;
                                        }
                                    }
                                    Collections.sort(total_grades);
                                    newRow.addElement("Ranking: " + (total_grades.indexOf(user_grade) + 1) + "/" + total_grades.size() + ".");
                                }
                            }
                        }
                        catch (ParseException | SQLException | NumberFormatException ex)
                        {
                            ex.printStackTrace();
                        }
                        rows.addElement(newRow);
                    }
                    String[] columns = { "Job ID", "Job Status", "Ranking"};
                    Vector<String> column = new Vector<>(Arrays.asList(columns));
                    DefaultTableModel model = new DefaultTableModel(rows, column)
                    {
                        @Override
                        public boolean isCellEditable(int row, int column)
                        {
                            return false;
                        }
                    };
                    application_stats_table.setModel(model);
                }
                catch (SQLException ex)
                {
                    ex.printStackTrace();
                }
            }
        });
    }
}
