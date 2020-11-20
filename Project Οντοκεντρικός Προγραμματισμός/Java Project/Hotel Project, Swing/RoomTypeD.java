public class RoomTypeD extends Room//Δωμάτιο μονοήμερης διαμονής.
{
    static double priceOfRoom=40; //Μεταβλητή για τιμή ανά δωμάτιο.
    //Setter
    public static void setPriceOfRoom(double x)
    {
        priceOfRoom=x;
    }
    public double getPriceOfRoom()//Μέθοδος υπολογισμού των εσόδων του δωματίου τύπου D.
    {
        double moneyEarnedFromRoom=0; //Μεταβλητή για έσοδα δωματίου.
        int i=0;
        boolean found=false;
        for(i = 1; i<31; i++)
        {
            if(roomAvailability[i]!=null)
                moneyEarnedFromRoom += priceOfRoom;
        }
        return moneyEarnedFromRoom;
    }    
    public boolean cancelBooking(int bookingID)//Η μέθοδος δείχνει ότι το δωμάτιο τύπου D δεν μπορεί να ακυρωθεί.
    {
        System.out.println("Can't cancel this kind of room");
        return false;
    }
}
