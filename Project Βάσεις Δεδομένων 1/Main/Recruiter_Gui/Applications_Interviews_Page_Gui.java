package Classes.Swing.Main.Recruiter_Gui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Vector;

public class Applications_Interviews_Page_Gui
{
    private JPanel applications_interviews_screen;
    private JTable application_table;
    private JButton update_button;
    private JLabel message_tip;
    private JScrollPane application_pane;
    private JButton insert_button;

    JPanel getApplications_interviews_screen()
    {
        return applications_interviews_screen;
    }

    Applications_Interviews_Page_Gui(Connection conn, String user, int id)
    {
        message_tip.setText("Check jobs from the table.You can also edit the grades of an interview.");
        ArrayList<String> candidates = new ArrayList<>();
        String[] scores = {null, "1", "2", "3", "4", "5"};

        if (conn != null)
        {
            String[] applies_columns = {"Candidate Username", "Job ID", "Personality Grade", "Education Grade", "Experience Grade"};
            String applies_query = "select * from erecruit.applies where applies.job_id = ?";
            Vector application_rows = new Vector();
            try
            {
                ResultSet application_set;
                PreparedStatement application_statement = conn.prepareStatement(applies_query);
                application_statement.setInt(1, id);
                application_set = application_statement.executeQuery();
                while (application_set.next())
                {
                    Vector newRow = new Vector();
                    candidates.add(application_set.getString("cand_usrname"));
                    newRow.addElement(application_set.getString("cand_usrname"));
                    newRow.addElement(application_set.getString("job_id"));
                    newRow.addElement(application_set.getString("personality_grade"));
                    newRow.addElement(application_set.getString("education_grade"));
                    newRow.addElement(application_set.getString("experience_grade"));
                    application_rows.addElement(newRow);
                }
                Vector<String> applies_column = new Vector<>(Arrays.asList(applies_columns));
                DefaultTableModel application_model = new DefaultTableModel(application_rows, applies_column)
                {
                    @Override
                    public boolean isCellEditable(int row, int column)
                    {
                            return column > 2;
                    }
                };
                application_table.setModel(application_model);
                TableColumn combo_box_Column = application_table.getColumnModel().getColumn(3);
                TableColumn combo_box_Column_2 = application_table.getColumnModel().getColumn(4);
                JComboBox comboBox = new JComboBox();
                DefaultComboBoxModel table_model = new DefaultComboBoxModel(scores);
                comboBox.setModel( table_model );
                combo_box_Column.setCellEditor(new DefaultCellEditor(comboBox));
                combo_box_Column_2.setCellEditor(new DefaultCellEditor(comboBox));
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
                String update_query = "update erecruit.applies set applies.education_grade = ?, applies.experience_grade = ?  WHERE (applies.job_id = ? and applies.cand_usrname = ?)";
                int row_count = application_table.getRowCount();
                for (int index = 0; index < row_count; index++)
                {
                    try
                    {
                        PreparedStatement update_statement = conn.prepareStatement(update_query);
                        String candidate = application_table.getValueAt(index, 0).toString();
                        String ed = String.valueOf(application_table.getValueAt(index, 3));
                        if(ed.equals("null"))
                        {
                            update_statement.setString(1, null);
                        }
                        else
                        {
                            int education_grade = Integer.parseInt(ed);
                            update_statement.setInt(1, education_grade);
                        }
                        String xd = String.valueOf(application_table.getValueAt(index, 4));
                        if(xd.equals("null"))
                        {
                            update_statement.setString(2, null);
                        }
                        else
                        {
                            int experience_grade = Integer.parseInt(ed);
                            update_statement.setInt(2, experience_grade);
                        }
                        update_statement.setInt(3, id);
                        update_statement.setString(4, candidate);
                        update_statement.executeUpdate();
                    }
                    catch (SQLException ex)
                    {
                        ex.printStackTrace();
                    }
                }
                JOptionPane.showMessageDialog(null, "Successful update.");
            }
        });

        insert_button.addActionListener(e ->
        {
            JFrame frame = new JFrame("interview_screen");
            Interviews_Page_Gui interview_Page = new Interviews_Page_Gui(conn, user,id,candidates);
            frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
            frame.addWindowListener(new WindowAdapter()
            {
                public void windowClosing(WindowEvent evt)
                {
                    if(interview_Page.getCan_Dispose())
                    {
                        if (conn != null)
                        {
                            String[] applies_columns = {"Candidate Username", "Job ID", "Personality Grade", "Education Grade", "Experience Grade"};
                            String applies_query = "select * from erecruit.applies where applies.job_id = ?";
                            Vector application_rows = new Vector();
                            try
                            {
                                ResultSet application_set;
                                PreparedStatement application_statement = conn.prepareStatement(applies_query);
                                application_statement.setInt(1, id);
                                application_set = application_statement.executeQuery();
                                while (application_set.next())
                                {
                                    Vector newRow = new Vector();
                                    newRow.addElement(application_set.getString("cand_usrname"));
                                    newRow.addElement(application_set.getString("job_id"));
                                    newRow.addElement(application_set.getString("personality_grade"));
                                    newRow.addElement(application_set.getString("education_grade"));
                                    newRow.addElement(application_set.getString("experience_grade"));
                                    application_rows.addElement(newRow);
                                }
                                Vector<String> applies_column = new Vector<>(Arrays.asList(applies_columns));
                                DefaultTableModel application_model = new DefaultTableModel(application_rows, applies_column)
                                {
                                    @Override
                                    public boolean isCellEditable(int row, int column)
                                    {
                                        return column > 2;
                                    }
                                };
                                application_table.setModel(application_model);
                                TableColumn combo_box_Column = application_table.getColumnModel().getColumn(3);
                                TableColumn combo_box_Column_2 = application_table.getColumnModel().getColumn(4);
                                JComboBox comboBox = new JComboBox();
                                DefaultComboBoxModel table_model = new DefaultComboBoxModel(scores);
                                comboBox.setModel( table_model );
                                combo_box_Column.setCellEditor(new DefaultCellEditor(comboBox));
                                combo_box_Column_2.setCellEditor(new DefaultCellEditor(comboBox));
                            }
                            catch (SQLException ex)
                            {
                                ex.printStackTrace();
                            }
                        }
                        frame.dispose();
                    }
                    else
                    {
                        JOptionPane.showMessageDialog(null, "You must insert at least an interview for every candidate.");
                    }
                }
            });
            frame.setContentPane(interview_Page.getInterviews_screen());
            frame.setSize(1000, 600);
            frame.setVisible(true);
        });
    }
}
