public class RoomTypeA extends Room
{
    private static double pricePerDay=50; //Μεταβλητή για τιμή ανά δωμάτιο τύπου Α.
    //Getter
    public double getPricePerDay()
    {
        return pricePerDay;
    }
    //Setter
    public static void setPricePerDay(double aa)
    {
        pricePerDay = aa;
    }
    public double getPriceOfRoom()//Η μέθοδος ελέγχει ποιές μέρες είναι κλεισμένο το δωμάτιο και υπολογίζει τα εσοδά του.
    {
        int i=0;
        double moneyEarnedFromRoom=0; //Μεταβλητή για έσοδα δωματίου. 
        for(i=1; i<31; i++)
        {
            if(roomAvailability[i]!=null)
            {
                moneyEarnedFromRoom = (moneyEarnedFromRoom + pricePerDay);
            }
        }
        return moneyEarnedFromRoom;
    }
}