import javax.swing.*;
import javax.swing.SpringLayout;
import java.lang.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class SwingHere
{
   private static int cancalationChance = 4;
   public void setCancalationChance(int cancalationChance) //Μέθοδος για αλλαγή της πιθανότητας ακύρωσης.
    {
        this.cancalationChance = cancalationChance;
    }
   public static void main(String args[])
   {
        //Κλήση μεθόδων για την αρχικοποίηση των σταθερών των κλάσεων.
        RoomTypeD.setPriceOfRoom(40);//Method for setting the prize of room type D.
        Room.setMaxPeople(10);//method for setting every room's max people number.//
        Room.setPricePerPerson(15);//method for setting the price paid by every person in every room.//
        RoomTypeA.setPricePerDay(50);//method for setting the price received every day for room type A.//
        RoomTypeB.setDiscountPerDay(0);//method for setting the discount per day for room type B.//
        RoomTypeC.setMinDays(5);//method for setting the minimum days, to be able to book in a room type C.//
        RoomTypeC.setMinPeople(5);//method for setting the minimum people, to be able to book in a room type C.//
        RunTime.setCancelationChance(3);//method for setting the cancelation chance, used to cancel a random booking.//
        String names[]={"John", "George", "Luther","Harry","Ross","Bruce","Cook",
                        "Morgan","Albert",
                        "Walker","Rogers",
                        "Randy","Reed",
                        "Larry","Barnes",
                        "Lois","Wilson",
                        "Jesse","Ernest",
                        "Henry","Simmons",
                        "Perry","Frank",
                        "Butler","Shirley"};
        Random dice = new Random();
        Scanner choose = new Scanner(System.in);
        Scanner input = new Scanner(System.in);
        
        Hotel me = new Hotel("ME");
        System.out.println("Hotel: " + "'" + me.getHotelName() + "'"  + " Created!");
        
        RoomTypeA a = new RoomTypeA(); // create a room type RoomTypeA named a.
        System.out.println("Room a Created! ---" + a.getClass());
        RoomTypeB b = new RoomTypeB(); // create a room type RoomTypeA named b.
        System.out.println("Room b Created! ---" + b.getClass());
        RoomTypeC c = new RoomTypeC(); // create a room type RoomTypeC named c.
        System.out.println("Room c Created! ---" + c.getClass());
        RoomTypeB d = new RoomTypeB();
        System.out.println("Room d Created! ---" + d.getClass());
        RoomTypeB e = new RoomTypeB();
        System.out.println("Room e Created! ---" + e.getClass());
        RoomTypeA f = new RoomTypeA();
        System.out.println("Room f Created! ---" + f.getClass());
        RoomTypeC g = new RoomTypeC();
        System.out.println("Room g Created! ---" + g.getClass());
        RoomTypeD h = new RoomTypeD();
        System.out.println("Room h Created! ---" + h.getClass());
        RoomTypeA j = new RoomTypeA();
        System.out.println("Room j Created! ---" + j.getClass());        
        RoomTypeC k = new RoomTypeC();
        System.out.println("Room k Created! ---" + k.getClass());
        RoomTypeD ll = new RoomTypeD();
        System.out.println("Room ll Created! ---" + ll.getClass());
        RoomTypeA m = new RoomTypeA();   
        System.out.println("Room m Created! ---" + m.getClass());
        RoomTypeD n = new RoomTypeD();
        System.out.println("Room n Created! ---" + n.getClass());
        RoomTypeE o = new RoomTypeE();
        System.out.println("Room o Created! ---" + o.getClass());
        RoomTypeE pp = new RoomTypeE();
        System.out.println("Room pp Created! ---" + pp.getClass());
        RoomTypeE q = new RoomTypeE();
        System.out.println("Room q Created! ---" + q.getClass());
        Room r = new Room();
        System.out.println("Room r Created! ---" + r.getClass());  
        
        ArrayList<Room> hotelRoom = new ArrayList<Room>();
        ArrayList<Booking> hotelBooking = new ArrayList<Booking>();
        

        me.addHotelRoom(a);
        me.addHotelRoom(b);
        me.addHotelRoom(c);
        me.addHotelRoom(d);
        me.addHotelRoom(e);
        me.addHotelRoom(f);
        me.addHotelRoom(g);
        me.addHotelRoom(h);
        me.addHotelRoom(j);
        me.addHotelRoom(k);
        me.addHotelRoom(ll);
        me.addHotelRoom(m);
        me.addHotelRoom(n);
        me.addHotelRoom(o);
        me.addHotelRoom(pp);
        me.addHotelRoom(q);
        me.addHotelRoom(r);
        
         int arrDay=1;
            arrDay=1+dice.nextInt(30);
            int accDays;
            if (arrDay == 30) // if arrDay == 30 than at accDays will be 30-30=0 which cannot be a parameter in nextInt();
            {
                accDays = 1;
            }
            else
                accDays = 1 + dice.nextInt(30 - arrDay);         
            Booking booka = new Booking(names[dice.nextInt(names.length)],arrDay, accDays,dice.nextInt(10)+1);
            System.out.println("********************************************************************");        
            booka.printBooking();
            System.out.println("********************************************************************");
            me.addBookingNoID(booka);
        
        int chance=2;
            if(dice.nextInt(cancalationChance)==chance)
            {
                    int qw = dice.nextInt(me.hotelBooking.size());
                    System.out.println("\n\n Random canceling booking with ID: " + me.hotelBooking.get(qw).getBookingID() + " ..");
                    me.deleteBooking(me.hotelBooking.get(qw).getBookingID());
            }
            else
                System.out.println("\nThere was not a Cancelation!\n\n");
        //---------------------------------------------------------------------------------------------------------------------------------
        
        // Graphics. GUI.
        
        //Main Frame.
        JFrame frame = new JFrame("Hotel: ME"); //Create the MAIN FRAME.
        frame.setSize(680, 410); // 
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        
        
       
        //Income Frame.
        JFrame incomeFrame = new JFrame("Income"); //FRAME FOR INCOME, CHOOSE ID.
        incomeFrame.setSize(200, 200); // 
        
        JPanel incomePanel = new JPanel(); //create the main panel.
        incomePanel.setLayout(new BorderLayout());
        
        //adding components to the panel of incomeFrame.
        JButton OKButton = new JButton("OK"); // Okay button.
        incomePanel.add(OKButton, BorderLayout.PAGE_END);
        
        JTextField textEnterRoomID = new JTextField("Enter Room ID:\n(0 for no Room ID)."); //Just a "label" message.
        incomePanel.add(textEnterRoomID, BorderLayout.LINE_START);
        
        JTextArea IDText = new JTextArea(); //Text area to enter ID.
        incomePanel.add(IDText, BorderLayout.PAGE_START);
        
                OKButton.addActionListener(new ActionListener() //BUTTON 7. PRINT INCOME/OK.
                {
                    public void actionPerformed(ActionEvent e)
                    {
                        if(OKButton.getModel().isArmed())
                        {
                            int RID=-1;
                            boolean done=false;
                            
                                try{
                                     RID = Integer.parseInt(IDText.getText());
                                     done=true;
                                }
                                catch(NumberFormatException ev)
                                {
                                    System.out.println("Please etner a number for the ROOM ID");
                                }
                                if(RID==0)
                                    {
                                        System.out.println("Income of the Hotel is : " + me.income());
                                        incomeFrame.dispose();
                                    }
                                else if(RID== -1)
                                {}
                                else
                                    {
                                        me.income(RID);
                                        incomeFrame.dispose();
                                    }
                        }
                    }
                });
        
        //adding panel to the main frame.
        incomeFrame.add(incomePanel); //end
        
        
        
        
        
        //Cancelation Frame.
        JFrame cancelFrame = new JFrame("Cancel Booking");
        cancelFrame.setSize(200, 200); // 
        
        JPanel cancelPanel = new JPanel(); //create the main panel.
        cancelPanel.setLayout(new BorderLayout());
        
        //adding components to the panel of cancelFrame.
        JButton cancelOKButton = new JButton("Cancel Booking"); // Okay button.
        cancelPanel.add(cancelOKButton, BorderLayout.PAGE_END);
        
        JTextField text = new JTextField("Enter Booking ID:"); //Just a "label" message.
        cancelPanel.add(text, BorderLayout.CENTER);
        
        JTextArea textArea = new JTextArea(); //Text area to enter ID.
        cancelPanel.add(textArea, BorderLayout.PAGE_START);
        

        
        cancelOKButton.addActionListener(new ActionListener() //BUTTON 3. Cancel Booking.
                {
                    public void actionPerformed(ActionEvent e)
                    {
                        if(cancelOKButton.getModel().isArmed())
                        {
                            int BID=-1;
                            boolean done=false;
                            
                                try{
                                     BID = Integer.parseInt(textArea.getText());
                                     done=true;
                                }
                                catch(NumberFormatException ev)
                                {
                                    System.out.println("Booking ID should be a number.");
                                }
                          
                                if(BID== -1)
                                {}
                                else
                                {
                                    System.out.println("Canceling your Booking..");                        
                                    me.deleteBooking(BID);
                                    cancelFrame.dispose();
                                }
                        }
                    }
                });        
        cancelFrame.add(cancelPanel); //end
        
     
        
        
        
        
        
        
        
        
        
        
        //Add Booking.
        JFrame addBookingFrame = new JFrame("Add Booking");
        addBookingFrame.setSize(300, 245); // size.
        
        //Add Panel.
        JPanel addBookingPanel = new JPanel(); //Main Panel.
        addBookingPanel.setLayout(new BorderLayout());
        
        //Add Button.
        JButton addBookingButton = new JButton("Add Booking");
        addBookingPanel.add(addBookingButton, BorderLayout.PAGE_END);
        
        //Add Check Box
        JCheckBox checkBox = new JCheckBox("ID");
        addBookingPanel.add(checkBox, BorderLayout.PAGE_START);
        

        
       
        
        String[] labels = {"Name: ", "Arrival Day: ", "Accomodation Days: ", "People Number: ", "ID: "};
        int numPairs = labels.length;
        JTextField fields[]=new JTextField[numPairs];
        
        //Create and populate the panel for a booking without ID.
        JPanel p = new JPanel(new SpringLayout());
        for (int i = 0; i < numPairs; i++) {
            JLabel l = new JLabel(labels[i], JLabel.TRAILING);
            p.add(l);
            fields[i] = new JTextField(10);
            l.setLabelFor(fields[i]);
            p.add(fields[i]);
        }
        //Lay out the panel.
        SpringUtilities.makeCompactGrid(p,
                                        numPairs, 2, //rows, cols
                                        6, 6,        //initX, initY
                                        6, 6);       //xPad, yPad
         
     
        
        addBookingPanel.add(p, BorderLayout.LINE_START); 
       
        addBookingButton.addActionListener(new ActionListener() //Add Booking Button.
                {
                    public void actionPerformed(ActionEvent e)
                    {
                        int arrDay=0,accDays=0,peopleNum=0,ID=0;
                        boolean done=false,done1=false,done2=false,done3=false;
                        
                        fields[0].getText();
                        
                        try
                        {   arrDay = Integer.parseInt(fields[1].getText());
                            done1=true;
                        }
                        catch(NumberFormatException ev)
                        {
                            System.out.println("Arrival day is Not a number.");
                        }
      
                        try
                        {
                            accDays = Integer.parseInt(fields[2].getText());
                            done2=true;
                        }
                        catch(NumberFormatException ev)
                        {
                            System.out.println("Accomodation Days is not a number.");
                        }

                        try
                        {
                            peopleNum = Integer.parseInt(fields[3].getText()); 
                            done3=true;
                        }
                        catch(NumberFormatException ev)
                        {
                            System.out.println("People number is not a number.");
                        }
                        if(done1==true && done2==true && done3==true)
                        {
                            Booking bookia = new Booking(fields[0].getText(), arrDay , accDays, peopleNum);
                        
                            //If check box is checked.
                            if(checkBox.isSelected())
                            {
                                try
                                {
                                    ID = Integer.parseInt(fields[4].getText());
                                    done=true;
                                }
                                catch(NumberFormatException ev)
                                {
                                    System.out.println("ID is not a number.");
                                }
                                
                                me.addBookingToRoom(bookia, ID);
                            }
                            else
                            {
                                me.addBookingNoID(bookia);
                            }
                            incomeFrame.dispose();
                        }
                        for(int i=0; i<numPairs; i++)
                        {
                            fields[i].setText(""); //Make text fields blank after clicking the button.
                        }
                        addBookingFrame.dispose();
                    }
                });        
       
        
        
        
        
        
        

        addBookingFrame.add(addBookingPanel); //end
        
        
        //FOR THE MAIN FRAME.
        JPanel mainPane = new JPanel(); //Create main Panel; main layout in which there will be placed more layouts. Doing that in order to adjust the "Border Layout".
        mainPane.setLayout(new BorderLayout());

        
        JPanel paneLeft = new JPanel(); //There will be placed the 3 buttons. At the LINE_START, CENTER, LINE_END.
        paneLeft.setLayout(new BorderLayout());
        
   
        JPanel paneRight = new JPanel(new BorderLayout()); // There will be placed 2 buttons buttons.
        paneRight.setLayout(new BorderLayout());
 
        
        
        JButton b1 = new JButton("Next Loop");
        mainPane.add(b1, BorderLayout.PAGE_START);
        
        JButton b2 = new JButton("Add Booking");
        paneLeft.add(b2, BorderLayout.LINE_START);
        
        JButton b3 = new JButton("Cancel Booking");
        paneLeft.add(b3, BorderLayout.CENTER);
        
        JButton b4 = new JButton("Print Booking");
        paneLeft.add(b4, BorderLayout.LINE_END);

        JButton b5 = new JButton("Print Room");
        paneRight.add(b5, BorderLayout.LINE_START);
        
        JButton b6 = new JButton("Booking Plan");
        paneRight.add(b6, BorderLayout.CENTER);
        
        JButton b7 = new JButton("Print Income");
        paneRight.add(b7, BorderLayout.LINE_END);
                
        JButton b8 = new JButton("Exit");
        mainPane.add(b8, BorderLayout.PAGE_END);
        
       
        
        frame.add(mainPane);                              //Added the main Panel.  
        mainPane.add(paneLeft, BorderLayout.LINE_START);  //Added to the main panel.
        mainPane.add(paneRight, BorderLayout.CENTER);     //Added to the main panel.
   
        
        
        
        
        
                
        b8.addActionListener(new ActionListener() //BUTTON 8. EXIT OPERATION.
        {
           public void actionPerformed(ActionEvent e)
           {
               System.exit(0);
           }
        });
            
        
        b7.addActionListener(new ActionListener() //BUTTON 7. PRINT INCOME.
        {
            public void actionPerformed(ActionEvent e)
            {
                incomeFrame.setVisible(true);
                incomeFrame.setLocationRelativeTo(null);
                System.out.println("\n\n");
            }
        });
        
        
        b6.addActionListener(new ActionListener() // BUTTON 6. PRINT BOOKING PLAN>=,
        {
            public void actionPerformed(ActionEvent e)
            {
                me.bookingPlan();
                System.out.println("\n\n");
            }
        });
        
        
        b5.addActionListener(new ActionListener() // BUTTON 5. PRINT ROOM>=,
        {
            public void actionPerformed(ActionEvent e)
            {
                System.out.println("Room ID\t\tFullness\t\tIncome");
                double priceOfRoom;
                for(int i=0; i < me.hotelRoom.size(); i++)
                {
                    priceOfRoom = me.hotelRoom.get(i).getPriceOfRoom();
                    System.out.println(me.hotelRoom.get(i).getRoomID() + "\t\t" + Math.round(me.hotelRoom.get(i).checkFullness()) + "%\t\t\t" + priceOfRoom + "$" );
                    priceOfRoom=0;
                }
                System.out.println("\n\n");
            }
        });
        
        
        
        b4.addActionListener(new ActionListener() // BUTTON 4. PRINT Booking>=,
        {
            public void actionPerformed(ActionEvent e)
            {
                System.out.println("BookingID\tClient Name\tRoomID");
                for(int i=0; i < me.hotelBooking.size(); i++)
                {
                    System.out.println(me.hotelBooking.get(i).getBookingID() + "\t\t" + me.hotelBooking.get(i).getClientName() + "\t\t" + me.hotelBooking.get(i).getRoom().getRoomID());
                }
                System.out.println("\n\n");
            }
        });
        
        
        b3.addActionListener(new ActionListener() // BUTTON 3. Cancel Booking>=,
        {
            public void actionPerformed(ActionEvent e)
            {
               cancelFrame.setVisible(true);
               cancelFrame.setLocationRelativeTo(null);
               System.out.println("\n\n");
            }
        });
        
        
        
        
        b2.addActionListener(new ActionListener() // BUTTON 2. Add Booking.>=,
        {
            public void actionPerformed(ActionEvent e)
            {
               addBookingFrame.setVisible(true);
               addBookingFrame.setLocationRelativeTo(null);
               System.out.println("\n\n");
            }
        });
        
        
        b1.addActionListener(new ActionListener() // Button 1.Next Loop>=,
        {
            public void actionPerformed(ActionEvent e)
            {
                int arrDay=1;
            arrDay=1+dice.nextInt(30);
            int accDays;
            if (arrDay == 30) // if arrDay == 30 than at accDays will be 30-30=0 which cannot be a parameter in nextInt();
            {
                accDays = 1;
            }
            else
                accDays = 1 + dice.nextInt(30 - arrDay);         
            Booking booka = new Booking(names[dice.nextInt(names.length)],arrDay, accDays,dice.nextInt(10)+1);
            System.out.println("********************************************************************");        
            booka.printBooking();
            System.out.println("********************************************************************");
            me.addBookingNoID(booka);
            
                if(dice.nextInt(cancalationChance)==chance)
                {
                        int qw = dice.nextInt(me.hotelBooking.size());
                        System.out.println("\n\n Random canceling booking with ID: " + me.hotelBooking.get(qw).getBookingID() + " ..");
                        me.deleteBooking(me.hotelBooking.get(qw).getBookingID());
                }
                else
                    System.out.println("\nThere was not a Cancelation!\n\n");
            }
        });
        frame.setVisible(true); // make window visible
    }    
}    


