public class RoomTypeC extends Room
{
    private static int minPeople=5; //Μεταβλητή για ελάχιστα άτομα στο δωμάτιο τύπου C.
    private static int minDays=5;  //Μεταβλητή για ελάχιστες μέρες στο δωμάτιο τύπου C.
    //Getters
    public static int getMinDays()
    {
        return minDays;
    }
     public static int getMinPeople()
    {
        return minPeople;
    }
    //Setters
    public static void setMinDays(int ab)
    {
        minDays = ab;
    }
    public static void setMinPeople(int abbb)
    {
        minPeople = abbb;
    }
    public boolean  addBooking (Booking a)//Ειδική μέθοδος για την προσθήκη κράτησης,για δωμάτιο τύπου C,με βάση τον
    {                                     //αριθμό τον ελάχιστων ατόμων και ημερών διαμονής.
        int i=0;
        for(i=a.getArrivalDate(); i < a.getArrivalDate()+a.getAccomodationDays()-1; i++)
        {
            if(roomAvailability[i]!=null || a.getPeopleNum()>getMaxPeople() || a.getPeopleNum() < minPeople || a.getAccomodationDays() < minDays)
            {
                return false;   
            }
        }
        for(i=a.getArrivalDate(); i <= a.getArrivalDate()+a.getAccomodationDays() - 1; i++)
        {
            roomAvailability[i] = a;
        }
        a.setRoom(this);
        return true;
    }
}