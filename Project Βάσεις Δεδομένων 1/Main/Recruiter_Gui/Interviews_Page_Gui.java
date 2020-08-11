package Classes.Swing.Main.Recruiter_Gui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Vector;


public class Interviews_Page_Gui extends  JFrame
{
    private JPanel interviews_screen;
    private JTable interview_table;
    private JButton update_button;
    private JButton insert_button;
    private JSpinner date_spinner;
    private JSpinner starting_time_spinner;
    private JSpinner duration_spinner;
    private JComboBox score_box;
    private JTextArea comment_area;
    private JScrollPane interview_pane;
    private JLabel message_tip;
    private JLabel date_label;
    private JLabel starting_time_label;
    private JLabel duration_label;
    private JLabel comment_label;
    private JLabel score_label;
    private JComboBox candidates_box;
    private JLabel candidates_label;
    private boolean can_Dispose;

    boolean getCan_Dispose()
    {
        return can_Dispose;
    }

    private void setCan_Dispose(boolean can_Dispose)
    {
        this.can_Dispose = can_Dispose;
    }

    JPanel getInterviews_screen()
    {
        return interviews_screen;
    }

    Interviews_Page_Gui(Connection conn, String user, int id, ArrayList<String> candidates)
    {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm:ss");
        String[] scores = {null, "1", "2", "3", "4", "5"};
        Vector interview_rows = new Vector();
        DefaultComboBoxModel candidates_model = new DefaultComboBoxModel( candidates.toArray() );
        candidates_box.setModel( candidates_model );
        DefaultComboBoxModel score_model = new DefaultComboBoxModel( scores );
        score_box.setModel( score_model );
        SpinnerDateModel dateModel = new SpinnerDateModel();
        SpinnerDateModel starting_timeModel = new SpinnerDateModel();
        SpinnerDateModel durationModel = new SpinnerDateModel();
        date_spinner.setModel(dateModel);
        starting_time_spinner.setModel(starting_timeModel);
        duration_spinner.setModel(durationModel);
        date_spinner.setEditor(new JSpinner.DateEditor(date_spinner, "yyyy-MM-dd"));
        starting_time_spinner.setEditor(new JSpinner.DateEditor(starting_time_spinner, "HH:mm:ss"));
        duration_spinner.setEditor(new JSpinner.DateEditor(duration_spinner, "HH:mm:ss"));
        date_label.setText("Enter interview date");
        starting_time_label.setText("Enter interview starting time");
        duration_label.setText("Enter interview duration");
        comment_label.setText("Enter interview comments");
        score_label.setText("Choose interview score");
        candidates_label.setText("Choose interview candidate");

        if (conn != null)
        {
            String[] interview_columns = {"Date", "Starting Time", "Duration", "Comments", "Score", "Recruiter Username", "Candidate Username", "Job ID"};
            String interview_query = "select * from erecruit.interview where (interview.recruiter = ? and interview.job_id = ?)";
            try
            {
                ResultSet interview_set;
                PreparedStatement interview_statement = conn.prepareStatement(interview_query);
                interview_statement.setString(1, user);
                interview_statement.setInt(2, id);
                interview_set = interview_statement.executeQuery();
                while (interview_set.next())
                {
                    Vector newRow = new Vector();
                    newRow.addElement(interview_set.getString("date"));
                    newRow.addElement(interview_set.getString("starting_time"));
                    newRow.addElement(interview_set.getString("duration"));
                    newRow.addElement(interview_set.getString("comments"));
                    newRow.addElement(interview_set.getString("score"));
                    newRow.addElement(interview_set.getString("recruiter"));
                    newRow.addElement(interview_set.getString("candidate"));
                    candidates.remove(interview_set.getString("candidate"));
                    newRow.addElement(interview_set.getString("job_id"));
                    interview_rows.addElement(newRow);
                }
                if(candidates.isEmpty())
                {
                    setCan_Dispose(true);
                }
                else
                {
                    setCan_Dispose(false);
                }
                Vector<String> interview_column = new Vector<>(Arrays.asList(interview_columns));
                DefaultTableModel interview_model = new DefaultTableModel(interview_rows, interview_column)
                {
                    @Override
                    public boolean isCellEditable(int row, int column)
                    {
                        return column < 5;
                    }
                };
                interview_table.setModel(interview_model);
                TableColumn combo_box_Column = interview_table.getColumnModel().getColumn(4);
                JComboBox comboBox = new JComboBox();
                DefaultComboBoxModel table_model = new DefaultComboBoxModel(scores);
                comboBox.setModel( table_model );
                combo_box_Column.setCellEditor(new DefaultCellEditor(comboBox));
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }

        insert_button.addActionListener(e->
        {
            if (conn != null)
            {
                String insert_query = "insert into interview (date, starting_time, duration, comments, score, recruiter, candidate, job_id) values (?, ?, ?, ?, ?, ?, ?, ?)";
                try
                {
                    String date = dateFormat.format(date_spinner.getValue());
                    String starting_time = timeFormat.format(starting_time_spinner.getValue());
                    String duration = timeFormat.format(duration_spinner.getValue());
                    String candidate = String.valueOf(candidates_box.getSelectedItem());
                    candidates.remove(candidate);
                    String sco = String.valueOf(score_box.getSelectedItem());
                    PreparedStatement insert_statement = conn.prepareStatement(insert_query);
                    if (sco.equals("null"))
                    {
                        insert_statement.setString(5, null);
                    }
                    else
                    {
                        int score = Integer.parseInt(sco);
                        insert_statement.setInt(5, score);
                    }
                    String comments = comment_area.getText();
                    if (comments.isEmpty())
                    {
                        insert_statement.setString(4, null);
                    }
                    else
                    {
                        insert_statement.setString(4, comments);
                    }
                    insert_statement.setString(1, date);
                    insert_statement.setString(2, starting_time);
                    insert_statement.setString(3, duration);
                    insert_statement.setString(6, user);
                    insert_statement.setString(7, candidate);
                    insert_statement.setInt(8, id);
                    insert_statement.executeUpdate();
                }
                catch (SQLException ex)
                {
                    ex.printStackTrace();
                }
                JOptionPane.showMessageDialog(null, "Successful insert.");

                if(candidates.isEmpty())
                {
                    setCan_Dispose(true);
                }
                else
                {
                    setCan_Dispose(false);
                }

                Vector rows = new Vector();
                String[] interview_columns = {"Date", "Starting Time", "Duration", "Comments", "Score", "Recruiter Username", "Candidate Username", "Job ID"};
                String interview_query = "select * from erecruit.interview where (interview.recruiter = ? and interview.job_id = ?)";
                try
                {
                    ResultSet interview_set;
                    PreparedStatement interview_statement = conn.prepareStatement(interview_query);
                    interview_statement.setString(1, user);
                    interview_statement.setInt(2, id);
                    interview_set = interview_statement.executeQuery();
                    while (interview_set.next())
                    {
                        Vector newRow = new Vector();
                        newRow.addElement(interview_set.getString("date"));
                        newRow.addElement(interview_set.getString("starting_time"));
                        newRow.addElement(interview_set.getString("duration"));
                        newRow.addElement(interview_set.getString("comments"));
                        newRow.addElement(interview_set.getString("score"));
                        newRow.addElement(interview_set.getString("recruiter"));
                        newRow.addElement(interview_set.getString("candidate"));
                        newRow.addElement(interview_set.getString("job_id"));
                        rows.addElement(newRow);
                    }
                    Vector<String> interview_column = new Vector<>(Arrays.asList(interview_columns));
                    DefaultTableModel interview_model = new DefaultTableModel(rows, interview_column)
                    {
                        @Override
                        public boolean isCellEditable(int row, int column)
                        {
                            return column < 5;
                        }
                    };
                    interview_table.setModel(interview_model);
                    TableColumn combo_box_Column = interview_table.getColumnModel().getColumn(4);
                    JComboBox comboBox = new JComboBox();
                    DefaultComboBoxModel table_model = new DefaultComboBoxModel(scores);
                    comboBox.setModel( table_model );
                    combo_box_Column.setCellEditor(new DefaultCellEditor(comboBox));
                }
                catch (SQLException ex)
                {
                    ex.printStackTrace();
                }
            }
        });
    }
}
