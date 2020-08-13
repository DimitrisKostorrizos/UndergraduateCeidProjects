package Classes.Swing.Main.Recruiter_Gui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Arrays;
import java.util.Vector;

public class Stored_Procedure_Gui
{
    private JPanel stored_procedure_screen;
    private JTable valid_candidate_table;
    private JTable failed_candidate_table;
    private JLabel status_message;
    private JScrollPane valid_candidate_pane;
    private JScrollPane failed_candidate_pane;

    JPanel getStored_procedure_screen()
    {
        return stored_procedure_screen;
    }

    Stored_Procedure_Gui(Connection conn, int job_id)
    {

        if (conn != null)
        {
            String procedure = "{call erecruit.assessment_check(?)}";
            try
            {
                CallableStatement sp_statement = conn.prepareCall(procedure);
                sp_statement.setInt(1, job_id);
                sp_statement.execute();
                ResultSet mess_set = sp_statement.getResultSet();
                while(mess_set.next())
                {
                    status_message.setText(mess_set.getString(1));
                }
                if (sp_statement.getMoreResults())
                {
                    ResultSet sp_set = sp_statement.getResultSet();
                    String[] columns = {"Candidate Username", "Total Grade", "Personality Grade", "Education Grade", "Experience Grade", "Number of Interviews"};
                    Vector rows = new Vector();
                    while (sp_set.next())
                    {
                        Vector newRow = new Vector();
                        newRow.addElement(sp_set.getString("Candidate_Username"));
                        newRow.addElement(sp_set.getString("Total_Grade"));
                        newRow.addElement(sp_set.getString("Personality_Grade"));
                        newRow.addElement(sp_set.getString("Education_Grade"));
                        newRow.addElement(sp_set.getString("Experience_Grade"));
                        newRow.addElement(sp_set.getString("Number_of_Interviews"));
                        rows.addElement(newRow);
                    }
                    sp_set.close();
                    Vector<String> column = new Vector<>(Arrays.asList(columns));
                    DefaultTableModel valid_model = new DefaultTableModel(rows, column)
                    {
                        @Override
                        public boolean isCellEditable(int row, int column)
                        {
                            return false;
                        }
                    };
                    valid_candidate_table.setModel(valid_model);
                }
                else
                {
                    valid_candidate_table.setVisible(false);
                    valid_candidate_pane.setVisible(false);
                }
                if (sp_statement.getMoreResults())
                {
                    String[] columns_2 = {"Candidate Username", "Explanation"};
                    Vector rows_2 = new Vector();
                    ResultSet sp_set_2 = sp_statement.getResultSet();
                    while (sp_set_2.next())
                    {
                        Vector newRow = new Vector();
                        newRow.addElement(sp_set_2.getString("Candidate_Username"));
                        newRow.addElement(sp_set_2.getString("Explanation"));
                        rows_2.addElement(newRow);
                    }
                    sp_set_2.close();
                    Vector<String> column_2 = new Vector<>(Arrays.asList(columns_2));
                    DefaultTableModel failed_model = new DefaultTableModel(rows_2, column_2)
                    {
                        @Override
                        public boolean isCellEditable(int row, int column)
                        {
                            return false;
                        }
                    };
                    failed_candidate_table.setModel(failed_model);
                }
                else
                {
                    failed_candidate_table.setVisible(false);
                    failed_candidate_pane.setVisible(false);
                }
                sp_statement.close();
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }
    }
}
