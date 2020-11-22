public class Booking
{
    private String clientName="No name";
    private static int instanceCounter;//Μεταβλητή για την αντιστοίχιση του ID.
    private int bookingID;             //Μεταβλητή για την αντιστοίχιση του ID.
    private int arrivalDate;           //Μεταβλητή για την μέρα άφιξης.
    private int accomodationDays;      //Μεταβλητή για τις μέρες διαμονής.
    private int peopleNum;             //Μεταβλητή για τον αριθμό των ατόμων.
    private Room room;                 //Μεταβλητή τύπου δωμάτιο.
    //Setters
    public void setBookingID() 
    {
        instanceCounter++;
        bookingID = instanceCounter;
    }
    public void setClientName(String clientName)
    {
        this.clientName=clientName;
    }
    public void setArrivalDate(int arrivalDate) 
    {
        this.arrivalDate=arrivalDate;
    }
    public void setAccomodationDays(int accomodationDays)
    {
        this.accomodationDays=accomodationDays;
    }
    public void setPeopleNum(int peopleNum)
    {
        this.peopleNum=peopleNum;
    }
    public void setRoom(Room roomToGetAssigned ) //Μέθοδος η οποία αναθέτει ένα αντικείμενο τύπου δωμάτιο στην μεταβλητή 'δωμάτιο' αυτής της κλάσης.
    {
        room=roomToGetAssigned;
    }
    //Getters
    public String getClientName()
    {
        return clientName;
    }
        public int getBookingID()
    {
        return bookingID;
    }
    public int getArrivalDate()
    {
        return arrivalDate;
    }
    public int getAccomodationDays()
    {
        return accomodationDays;
    }
    public int getPeopleNum()
    {
        return peopleNum;
    }
    public Room getRoom()
    {
        return room;
    }
    
    public Booking(String clientName,int arrivalDate, int accomodationDays, int peopleNum) //Constructor για τα αντκείμενα τύπου κράτησης.
    {
        setBookingID();
        setClientName(clientName);
        setArrivalDate(arrivalDate);
        setAccomodationDays(accomodationDays);
        setPeopleNum(peopleNum);
        setRoom(null);
        System.out.println("Booking created");
    }
    
    public void printBooking()//Μεθοδος εκτύπωσης μίας κράτησης.
    {
        System.out.println("Client Name: " + getClientName() + "\nArrival Date: " + getArrivalDate() + "\nAccomodation Days: " + getAccomodationDays() + "\nPeopleNum: " + getPeopleNum() + "\nBookingID: " + getBookingID());
    }
}













