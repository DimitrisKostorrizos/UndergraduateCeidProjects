#include "stdio.h"


int main()

{
	float res1, res2, res3, res4, res5, res6;

	int x = 3, y = 3, z = 1, w = 15, a = 14, b = 3;

	res1 = y + z / x;//Πρώτα διαιρείται το z από το x και μετά το αποτέλεσμα της διαίρεσης προστίθεται στο y.

	res2 = w*x / y / z;/*Πρώτα πολλαπλασιάζεται το w με το x,έπειτα το γινόμενο w*x διαιρείται απο το y και μετά το αποτέλεσμα της 
διαίρεσης διαιρείται από το z.*/

	res3 = w / x*++z + x / y;/*Πρώτα το w διαιρείται από το x,το z αυξάνεται κατά 1 και το x διαιρείται από το y,έπειτα το 
αποτέλεσμα της διαίρεσης του w από το x πολλαπλασιάζεται με το z και μετά προστίθεται στο αποτέλεσμα της διαίρεσης του x από το y.*/

	res4 = ++b, --a;/*Πρώτα το b αυξάνεται κατά 1 και το a μειώνεται κατά 1,μετά στη μεταβλητή res4 εκχωρείται το b,το a δεν 
χρησιμοποιείται.*/

	res5 = (--b, ++a);//Πρώτα το a αυξάνεται κατά 1 και το b μειώνεται κατά 1,μετά στην μεταβλητή res5 εκχωρείται το a.

	res6 = (a > b) ? b : a;/*Πρώτα ελέγχει αν το a είναι μεγαλύτερο από το b και αφου το a είναι μεγαλυτερο από το b,εκχωρεί στη 
μεταβλητή res6 το b,αλλιώς θα εκχωρούσε στη μεταβλητή res6 το a.*/

	return 0;

}
