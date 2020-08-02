package Classes.Swing.Main.Admin_Gui;


import javax.swing.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Insert_Page_Gui
{
    private JPanel Insert_Page_Screen;
    private JTextField conn_field;
    private JTextField title_field;
    private JTextArea text_area;
    private JButton insert_button;
    private JLabel title_label;
    private JLabel text_label;
    private JLabel self_connection_label;
    private JComboBox options_box;

    JPanel getInsert_Page_Screen()
    {
        return Insert_Page_Screen;
    }

    Insert_Page_Gui(Connection conn)
    {
        String[] options = { "antikeim", "field" };
        DefaultComboBoxModel table_model = new DefaultComboBoxModel( options );
        options_box.setModel( table_model );
        title_label.setText("Enter antikeim title.");
        text_label.setText("Enter this antikeim description.");
        self_connection_label.setText("Enter the antikeim title, this antikeim will be connected to, otherwise leave it blank.");

        options_box.addActionListener(e ->
        {
            String mode = String.valueOf(options_box.getSelectedItem());
            if(mode.equals("antikeim"))
            {
                title_label.setText("Enter antikeim title.");
                text_label.setText("Enter this antikeim description.");
                self_connection_label.setText("Enter the antikeim title, this antikeim will be connected to, otherwise leave it blank.");
            }
            else
            {
                title_label.setText("Enter field title.");
                text_label.setText("Enter this field description.");
                self_connection_label.setText("Enter the field title, this field will be connected to, otherwise leave it blank.");
            }
        });

        insert_button.addActionListener(e ->
        {
            if (conn != null )
            {
                String mode = String.valueOf(options_box.getSelectedItem());
                String title = title_field.getText();
                String desc = text_area.getText();
                String self = conn_field.getText();
                if(desc.isEmpty())
                {
                    desc = null;
                }
                if(self.isEmpty())
                {
                    self = null;
                }
                if (!title.isEmpty())
                {
                    if (mode.equals("antikeim"))
                    {
                        ResultSet title_set;
                        String search_query = "SELECT * FROM erecruit.antikeim where antikeim.title = ?";
                        try
                        {
                            PreparedStatement title_statement = conn.prepareStatement(search_query);
                            title_statement.setString(1, title);
                            title_set = title_statement.executeQuery();
                            if (!title_set.next())
                            {
                                ResultSet self_set;
                                String self_query = "SELECT * FROM erecruit.antikeim where antikeim.title = ?";
                                PreparedStatement belongs_statement = conn.prepareStatement(self_query);
                                belongs_statement.setString(1,self);
                                self_set = belongs_statement.executeQuery();
                                if(self_set.next() || self == null)
                                {
                                    String insert_query = "insert into erecruit.antikeim (title, descr, belongs_to) values (?, ?, ?)";
                                    PreparedStatement insert_statement = conn.prepareStatement(insert_query);
                                    insert_statement.setString(1, title);
                                    insert_statement.setString(2, desc);
                                    insert_statement.setString(3, self);
                                    insert_statement.executeUpdate();
                                    JOptionPane.showMessageDialog(null, "Successful antikeim insert.");
                                }
                                else
                                {
                                    JOptionPane.showMessageDialog(null, "Non Existing antikeim title to self connect.");
                                }
                            }
                            else
                            {
                                JOptionPane.showMessageDialog(null, "Duplicate antikeim title.");
                            }
                        } catch (SQLException ex)
                        {
                            ex.printStackTrace();
                        }
                    }
                    else
                    {
                            ResultSet title_set;
                            String search_query = "SELECT * FROM erecruit.field where field.title = ?";
                            try
                            {
                                PreparedStatement title_statement = conn.prepareStatement(search_query);
                                title_statement.setString(1,title);
                                title_set = title_statement.executeQuery();
                                if (!title_set.next())
                                {
                                    ResultSet self_set;
                                    String self_query = "SELECT * FROM erecruit.field where field.title = ?";
                                    PreparedStatement belongs_statement = conn.prepareStatement(self_query);
                                    belongs_statement.setString(1,self);
                                    self_set = belongs_statement.executeQuery();
                                    if(self_set.next() || self == null)
                                    {
                                        String insert_query = "insert into erecruit.field (title, text, connected_field) values (?, ?, ?)";
                                        PreparedStatement insert_statement = conn.prepareStatement(insert_query);
                                        insert_statement.setString(1, title);
                                        insert_statement.setString(2, desc);
                                        insert_statement.setString(3, self);
                                        insert_statement.executeUpdate();
                                        JOptionPane.showMessageDialog(null, "Successful field insert.");
                                    }
                                    else
                                    {
                                        JOptionPane.showMessageDialog(null, "Non Existing field title to self connect.");
                                    }
                                }
                                else
                                {
                                    JOptionPane.showMessageDialog(null, "Duplicate field title.");
                                }
                            } catch (SQLException ex)
                            {
                                ex.printStackTrace();
                            }
                    }
                }
                else
                {
                    JOptionPane.showMessageDialog(null, "Invalid empty title.");
                }
            }
        });
    }
}

