public class Room //Η κλάση για ένα γενικού τύπου δωμάτιο του ξενοδοχείου.
{
    private static int roomInstanceCounter=100; //Μεταβλητή για την αντιστοίχιση του ID.
    private int roomID;                         //Μεταβλητή για την αντιστοίχιση του ID.
    private static int maxPeople=10;            //Μεταβλητή για μέγιστο αριθμό ατόμων.
    private static double pricePerPerson=15;    //Μεταβλητή για τιμή ανά άτομο.

    protected Booking roomAvailability[] = new Booking[31];
     
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Setters
    public void setRoomID() 
    {
        roomInstanceCounter++;
        roomID = roomInstanceCounter;
    }
    public static void setMaxPeople(int maxPeoplee)
    {
        maxPeople=maxPeoplee;
    }
    public static void setPricePerPerson(int pricePerPersonn)
    {
        pricePerPerson=pricePerPersonn;
    }
    //Getters
    public double getPricePerPerson()
    {
        return pricePerPerson;
    }
     public int getMaxPeople()
    {
        return maxPeople;
    }
    public int getRoomID()
    {
        return roomID;
    }
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    public Room()//Constructor για το αντικείμενο Room.
    {
        int i=0;
        Booking roomAvailability[] = new Booking[31];
        for(i=0; i < 31; i++)
        {
            roomAvailability[i]=null;
        }
        setRoomID();//Κάθε φορά που δημιουργούμε ένα δωμάτιο καλείται η μέθοδος setRoomID() για την αντιστοίχιση δωματίου και ID.
    }
    public boolean addBooking(Booking a) //Η μέθοδος ελέγχει αν μπορεί να γίνει κράτηση σε ένα δωμάτιο,αν ταιριάζουν
    {                                    //οι μέρες διαμονής και η μέρα άφιξης και το προσθέτει στον πίνακα διαθεσιμότητας.
        int i=0; 
        for(i=a.getArrivalDate(); i < a.getArrivalDate()+a.getAccomodationDays()-1; i++)
        {
             if(roomAvailability[i]!=null || a.getPeopleNum()>maxPeople)
            {
                return false;
            }
        }
        for(i=a.getArrivalDate(); i <= a.getArrivalDate()+a.getAccomodationDays()-1; i++)
        {
            roomAvailability[i] = a;
        }
        a.setRoom(this);//Μέθοδος που ενημερώνει την μεταβλητή Room στο πεδίο της Booking.
        return true;
    }
    public double getPriceOfRoom()//Μέθοδος υπολογισμού εσόδων ενός δωματίου.
    {
        int i=0;
        double moneyEarnedFromRoom; //Μεταβλητή για έσοδα δωματίου.
        moneyEarnedFromRoom=0;
        for(i=1; i<31; i++)
        {
            if(roomAvailability[i]!=null)
                {
                    moneyEarnedFromRoom = (moneyEarnedFromRoom + (roomAvailability[i].getPeopleNum() * getPricePerPerson()));
                }
        }
        return moneyEarnedFromRoom;
    }
    public boolean cancelBooking(int bookingID)//Μέθοδος ακύρωσης συγκεκριμένης κράτησης σε ένα δωμάτιο.
    {
        int i;
        boolean found=false;
        for(i=1; i<31; i++)
        {
            if( this.roomAvailability[i]!=null && roomAvailability[i].getBookingID() == bookingID)
            {
                roomAvailability[i]=null;
                found=true;
                
            }
        }
            return true;
    }
    public double checkFullness()//Μέθοδος η οποία εκτυπώνει την διαθεσημότητα ενός δωματίου.
    {
        int i;
        double fullnessPercentage=0;//Μεταβλητή στην οποία αποθηκεύεται το ποσοστό.
        int daysCounter=0;//Μεταβλητή που μετράει τις μέρες και την αξιοποιούμε για να βρούμε το ποσοστό.
        for(i=1; i<31; i++)//Αν κάθε κελί του πίνακα διαθεσιμότητας δεν είναι null τότε αυξάνει τον daysCounter κατά 1.
        {
            if(roomAvailability[i]!=null)
            {
                daysCounter++;
            }
        }
        fullnessPercentage=((double)daysCounter/30) * 100.0;//Υπολογισμός ποσοστού.
        return fullnessPercentage;
    }
}

    