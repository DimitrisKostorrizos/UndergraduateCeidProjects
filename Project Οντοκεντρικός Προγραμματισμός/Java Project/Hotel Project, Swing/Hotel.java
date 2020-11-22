import java.util.*;
public class Hotel
{

    private String hotelName;
    protected ArrayList<Room> hotelRoom = new ArrayList<Room>(1); //Λίστα με τα δωμάτια.
    protected ArrayList<Booking> hotelBooking = new ArrayList<Booking>(1); //Λίστα με τις κρατήσεις.
    //Getter
    public String getHotelName()
    {
        return hotelName;
    }
   
    public Hotel(String name)//Constructor για το αντικείμενο Hotel.
    {
        hotelName=name;
    }
    
    public void addHotelRoom(Room room)//Μέθοδος προσθήκης δωματίου στη λίστα δωματίων.
    {
            hotelRoom.add(room);
    }
    public Room recoverRoomOutOfID(int ID)//Μέθοδος η οποία βρίσκει το δωμάτιο με δεδομένο ID. 
    {
        int i;
        for(i=0; i<hotelRoom.size(); i++)
        {
            if(hotelRoom.get(i).getRoomID()==ID)
            {   
                return hotelRoom.get(i);
            }
        }
        return null;  
    }
    public Booking recoverBookingOutOfID(int ID)//Μέθοδος η οποία βρίσκει τη κράτηση με δεδομένο ID.
    {
        int i;
        for(i=0; i<hotelBooking.size(); i++)
        {
            if(hotelBooking.get(i).getBookingID()==ID)
            {   
                return hotelBooking.get(i);
            }
        }
        return null;      
    }
    public boolean addBookingToRoom(Booking aa,int ID)//Μέθοδος προσθήκης κράτησης σε ένα δωμάτιο.
    {
       Room roomaki = new Room();
       int i;
       if(recoverRoomOutOfID(ID)==null || roomaki.addBooking(aa)==false) //Αν δεν υπάρχει δωμάτιο ή το δωμάτιο έχει ήδη κρατηθεί.
       {
           System.out.println("Booking not successful.");
           return false;
       }
       if(recoverRoomOutOfID(ID) instanceof RoomTypeC && (aa.getPeopleNum()<RoomTypeC.getMinPeople() || aa.getAccomodationDays()<RoomTypeC.getMinDays()))//Αν δεν ταιριάζουν τα ελάχιστα άτομα ή οι ελάχιστες μέρες για κράτηση σε δωμάτιο τύπου C ή E.
       {
           System.out.println("Booking not successful, cannot Book in Room Type C not enough days or not enough people.");
           return false;           
       }
       if(recoverRoomOutOfID(ID) instanceof RoomTypeD && (aa.getAccomodationDays()>1))//Αν ο χρήστης δηλώσει παραπάνω μέρες από μία για να γίνει κράτηση σε δωμάτιο τύπου D.
       {
           System.out.println("Booking not successful, cannot Book in Room Type D single day room.");
           return false; 
       }
       recoverRoomOutOfID(ID).addBooking(aa); 
       hotelBooking.add(aa);
       System.out.println("Booking succcessful with ID: " + aa.getBookingID());
       return true;
    }
    public int addBookingNoID(Booking aaa)//Μέθοδος προσθήκης κράτησης σε δωμάτιο με βάση το ID.
    {
        int i;
        boolean found=false;
        for(i=0; i<hotelRoom.size(); i++)
        {
            Room roomaki = new Room(); //Το αντικείμενο Roomaki πρέπει να αρχικοποιείται σε κάθε επανάληψη.
            if( roomaki.addBooking(aaa)==false) 
            {
                System.out.println("Booking not Succesful.");
                return 0;
            }
            else if(aaa.getAccomodationDays()==1)
            {
                if(hotelRoom.get(i) instanceof RoomTypeD)
                {
                    if(hotelRoom.get(i).addBooking(aaa)==true)
                       System.out.println("Booking with ID: " + aaa.getBookingID() + " Successfully booked in " + aaa.getRoom().getClass());
                    else
                        continue;
                    hotelBooking.add(aaa);
                    found=true;
                    break;
                }
                else    
                    continue;
            }
            else if(aaa.getPeopleNum() >= RoomTypeC.getMinPeople() && aaa.getAccomodationDays() >= RoomTypeC.getMinDays())
            {
                if(hotelRoom.get(i) instanceof RoomTypeC  || hotelRoom.get(i) instanceof RoomTypeE)
                {
                    if(hotelRoom.get(i).addBooking(aaa)==true) 
                        System.out.println("Booking with ID: " + aaa.getBookingID() + " Successfully booked in " + aaa.getRoom().getClass());
                    else 
                        continue;
                    hotelBooking.add(aaa);
                    found=true;
                    break;
                }
                else
                    continue;
            }
            else
            {
                if(hotelRoom.get(i).addBooking(aaa)==true)
                    System.out.println("Booking with ID: " + aaa.getBookingID() + " Successfully booked in " + aaa.getRoom().getClass());
                else
                    continue;
                hotelBooking.add(aaa);
                found=true;
                break;
            }
          
        }
        if(found==true)
        {
            if(i == hotelRoom.size())
                i = (i - 1 );
            System.out.println("Room ID: " + hotelRoom.get(i).getRoomID());
            return hotelRoom.get(i).getRoomID();
        }
        else
        {   
            System.out.println("Not available Booking");
            return 0;
        }
    }
    public void deleteBooking(int ID) //Μέθοδος διαγραφής κράτησης σε ένα δωμάτιο με βάση το ID.
    {
        if(recoverBookingOutOfID(ID)!=null)        
        {
          if(recoverBookingOutOfID(ID).getRoom().cancelBooking(ID)==true)
           {
               recoverBookingOutOfID(ID).getRoom().cancelBooking(ID);
               hotelBooking.remove(recoverBookingOutOfID(ID));
               System.out.println("Cancelation Successful!");
           }
        }
        else
        {
            System.out.println("There is not a booking with this ID, check bookings and try again.");
        }
    }
    public double income(int ID)//Μέθοδος υπολογισμού των εσόδων ενός δωματίου με βάση το ID.
    {
        if(recoverRoomOutOfID(ID)==null)
        {
            System.out.println("No room with this ID");    
            return 0;
        }
        System.out.println("Money earned from this room: " + recoverRoomOutOfID(ID).getPriceOfRoom());
        return recoverRoomOutOfID(ID).getPriceOfRoom();
    }
    public double income()//Μέθοδος υπολογισμού των εσόδων ενός δωματίου.
    {
        double totalEarnings=0;
        int i;
        for(i=0; i < hotelRoom.size(); i++)
        {
            totalEarnings += hotelRoom.get(i).getPriceOfRoom(); 
        }
        return totalEarnings;
    }
    public void bookingPlan()//Μεθοδος εκτύπωσης του πλάνου κρατήσεων του ξενοδοχείου.
    {
        int i,k;
        System.out.print("Room\t\t");
        for(i=1; i<31; i++)
        {
            System.out.print(i +"\t");
        }
        System.out.println("\n");
        for(i=0; i < hotelRoom.size(); i++)
        {
            System.out.print(hotelRoom.get(i).getRoomID() + "\t\t");
            for(k=1; k<31; k++)
            {
                if(hotelRoom.get(i).roomAvailability[k]==null)
                {
                    System.out.print("_" + "\t");
                }
                else
                {
                    System.out.print("*" + "\t");
                }
            }
            System.out.println();
        }
    }
}