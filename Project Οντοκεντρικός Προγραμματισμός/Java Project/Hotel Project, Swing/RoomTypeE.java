public class RoomTypeE extends RoomTypeC//Δωμάτιο τύπου C,αλλά με έκπτωση 50% ανά άτομο μετά την τρίτη μέρα.
{
     public double getPriceOfRoom()//Μέθοδος για τον υπολογισμό των εσόδων δωματίου τύπου E,λαμβάνοντας υπόψη τα ελάχιστα//
    {                              //άτομα και μέρες,καθώς και την έκπτωση.
        int i=0;
        double moneyEarnedFromRoom=0; //Μεταβλητή για έσοδα από δωμάτιο.
        double discountPerPerson; //Μεταβλητή για έκπτωση ανά άτομο.
        for(i=1; i<31; i++)
        {
            if(roomAvailability[i]!=null)
                {
                    if(i<=3)
                    {
                        discountPerPerson = (getPricePerPerson() / 2 );
                        moneyEarnedFromRoom+=(roomAvailability[i].getPeopleNum()*( getPricePerPerson() - discountPerPerson));
                        continue;
                    }
                    moneyEarnedFromRoom = (moneyEarnedFromRoom + (roomAvailability[i].getPeopleNum() * getPricePerPerson()));
                }
        }
        return moneyEarnedFromRoom;
    }



}
