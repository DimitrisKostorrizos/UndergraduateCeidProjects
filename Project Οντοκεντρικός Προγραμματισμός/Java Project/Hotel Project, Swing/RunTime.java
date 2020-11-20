import java.util.*;
import java.lang.*;
import javax.swing.*; 
import java.util.concurrent.*; 

 public class RunTime
{
    private static int cancelationChance = 4;
    //Setter
    public static void setCancelationChance(int cancelationChan) //Μέθοδος για αλλαγή της πιθανότητας ακύρωσης.
    {
        cancelationChance =cancelationChan;
    }
    public static void main(String args[])
    {
        //Κλήση μεθόδων για την αρχικοποίηση των σταθερών των κλάσεων.
        RoomTypeD.setPriceOfRoom(40);//Method for setting the prize of room type D.
        Room.setMaxPeople(10);//method for setting every room's max people number.
        Room.setPricePerPerson(15);//method for setting the price paid by every person in every room.
        RoomTypeA.setPricePerDay(50);//method for setting the price received every day for room type A.
        RoomTypeB.setDiscountPerDay(0);//method for setting the discount per day for room type B.
        RoomTypeC.setMinDays(5);//method for setting the minimum days, to be able to book in a room type C.
        RoomTypeC.setMinPeople(5);//method for setting the minimum people, to be able to book in a room type C.
        RunTime.setCancelationChance(3);//method for setting the cancelation chance, used to cancel a random booking.
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
        //Δημιουργία ενός αντικειμένου τύπου ξενοδοχείου.
        Hotel me = new Hotel("My Hotel");
        System.out.println("Hotel: " + "'" + me.getHotelName() + "'"  + " Created!");
        //Δημιουργία των δωματίων διαφόρων τύπων.
        RoomTypeA a = new RoomTypeA();//Δημιουργία δωματίου τύπου Α.
        System.out.println("Room a Created! ---" + a.getClass());
        RoomTypeB b = new RoomTypeB();//Δημιουργία δωματίου τύπου Β.
        System.out.println("Room b Created! ---" + b.getClass());
        RoomTypeC c = new RoomTypeC();
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
        //Προσθήκη των δωματίων στην λίστα δωματίων.
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
        System.out.println("\nRooms Added To The Hotel LIST Successfully!");
           do
            {
            System.out.println("\n-----------------------------------------------------------------------------------\n\n");
            int arrDay=1;
            arrDay=1+dice.nextInt(30);
            int accDays;
            if (arrDay == 30) //Αποφυγή της ύπαρξης μηδενικού ορίσματος για τη μέθοδο nextInt() και δημιουργία εξαίρεσης.
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
            if(dice.nextInt(cancelationChance)==chance)//Κωδικας για την τυχαία ακύρωση κράτησης.
            {
                int qw = dice.nextInt(me.hotelBooking.size());
                System.out.println("\n\n Random canceling booking with ID: " + me.hotelBooking.get(qw).getBookingID() + " ..");
                me.deleteBooking(me.hotelBooking.get(qw).getBookingID());
            }
            else
                System.out.println("\nThere was not a Cancelation!\n\n");
                //Εμφάνιση των δυνατών επιλογών του χρήστη.
            System.out.println("--Next Loop 1");
            System.out.println("--Add Booking 2");
            System.out.println("--Cancel Booking 3");
            System.out.println("--Print Booking 4");
            System.out.println("--Print Rooms 5");
            System.out.println("--Print Booking Plan 6");
            System.out.println("--Print Income 7");
            System.out.println("--Exit 8");
            System.out.println("Choose what you want to do, give a number: ");
            //Κώδικας για εκτέλεση της κάθε διαφορετικής επιλογής από τον χρήστη.
            switch(input.nextInt())
            {
                case 1 :
                    System.out.println("Next loop..\n");
                    break;
                case 2 :
                    System.out.println("Creating Booking.. :");
                    System.out.println("Enter name:");
                    String name = choose.nextLine();
                    System.out.println("Enter Arrival Day:");
                    int arrivDay = input.nextInt();
                    System.out.println("Enter Accomodation Days:");
                    int accomDay = input.nextInt();
                    System.out.println("Enter how many people will be in the room:");
                    int peopNum = input.nextInt();
                    Booking bookia = new Booking(name, arrivDay, accomDay, peopNum);
                    System.out.println("Do you wanna book in a specific ROOM? Enter Room ID. Otherwise enter 0");
                    int ID = input.nextInt();
                    if(ID == 0)
                    {
                        me.addBookingNoID(bookia);
                    }
                    else
                    {
                        me.addBookingToRoom(bookia, ID);
                    }
                    break;
                case 3 :
                    System.out.println("Enter the ID of the booking");
                    int BID = input.nextInt();
                    System.out.println("Canceling your Booking..");                        
                    me.deleteBooking(BID);
                    break;
                case 4 :
                    int i=0;
                    System.out.println("BookingID\tClient Name\tRoomID");
                    for(i=0; i < me.hotelBooking.size(); i++)
                    {
                        System.out.println(me.hotelBooking.get(i).getBookingID() + "\t\t" + me.hotelBooking.get(i).getClientName() + "\t\t" + me.hotelBooking.get(i).getRoom().getRoomID());
                    }
                    break;
                case 5 :
                    System.out.println("Room ID\t\tFullness\t\tIncome");
                     double priceOfRoom;
                     for(i=0; i < me.hotelRoom.size(); i++)
                    {
                        priceOfRoom = me.hotelRoom.get(i).getPriceOfRoom();
                        System.out.println(me.hotelRoom.get(i).getRoomID() + "\t\t" + Math.round(me.hotelRoom.get(i).checkFullness()) + "%\t\t" + priceOfRoom );
                        priceOfRoom=0;
                    }
                    break;     
                case 6 :
                    System.out.println("Booking Plan:");
                    me.bookingPlan();
                     break;
                case 7 :
                    System.out.println("Specific Room ID? (Press 0 if you don't wanna enter an ID)");
                    int RID = input.nextInt();
                    if(RID == 0)
                        System.out.println("Total income of the hotel is: " + me.income());
                    else
                        me.income(RID);
                    break;
                case 8 :
                    System.out.println("Simulation Terminated!");
                    System.exit(0);
                    break;     
            }
            //Επιλογή για εξόδο από το πρόγραμμα.
            System.out.println("Press 9 to end simulation!!!");
        }while(input.nextInt()!=9);
    }
}

