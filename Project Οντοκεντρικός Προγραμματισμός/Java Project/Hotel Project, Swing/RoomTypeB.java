public class RoomTypeB extends RoomTypeA
{
    private static double discountPerDay=0; //Μεταβλητή για έκπτωση ανά μέρα.
    //Setter
    public static void setDiscountPerDay(int aaa)
    {
        discountPerDay=aaa;
    }
    public double getPriceOfRoom()//Η μέθοδος ελέγχει ποιές μέρες είναι κλεισμένο το δωμάτιο και υπολογίζει τα εσοδά του,
    {                             //υπολογίζωντας την καθημερινή έκπτωση.
        int i=0;
        double totalEarnings; //Μεταβλητή για συνολικά έσοδα.
        double moneyEarnedFromRoom=0; //Μεταβλητή για έσοδα ανά μέρα.
        discountPerDay=0;
        for(i=1; i<31; i++)
            {
                if(roomAvailability[i]!=null)
                    {
                        moneyEarnedFromRoom += (getPricePerDay() - discountPerDay);
                        discountPerDay += 10;
                        if( (discountPerDay / getPricePerDay()) > 0.5)
                        {
                            discountPerDay = 0.5 * getPricePerDay();
                        }
                    }
            }
        return moneyEarnedFromRoom;
    }
    public boolean cancelBooking(int bookingID)//Η μέθοδος δείχνει ότι το δωμάτιο τύπου B δεν μπορεί να ακυρωθεί.
    {
        System.out.println("Can't cancel this kind of room");
        return false;
    }
}