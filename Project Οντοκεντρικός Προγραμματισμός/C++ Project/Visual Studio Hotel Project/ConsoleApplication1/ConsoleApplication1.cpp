#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include "Booking.h"
#include "Hotel.h"
#include "Room.h"
#include "RoomTypeA.h"
#include "RoomTypeB.h"
#include "RoomTypeC.h"
#include "RoomTypeD.h"
#include "RoomTypeE.h"


using namespace std;

int cancelationChance;//Variable used for calculating the cancelation chance, used for deleting one random booking.
void setCancelationChance(int cancelationChan)//Getter for the variable cancelationChance.
{
	cancelationChance = cancelationChan;
}

int main()
{
	int input, i;

	string names[] = { "John", "George", "Luther","Harry","Ross","Bruce","Cook",//Array used to random get a name for a random booking.
		"Morgan","Albert",
		"Walker","Rogers",
		"Randy","Reed",
		"Larry","Barnes",
		"Lois","Wilson",
		"Jesse","Ernest",
		"Henry","Simmons",
		"Perry","Frank",
		"Butler","Shirley" };





	Hotel *me = new Hotel("Me");

	RoomTypeA *a = new RoomTypeA(50,10);
	me->hotelRoom.push_back(a);
	RoomTypeB *b = new RoomTypeB(50.0,10);
	me->hotelRoom.push_back(b);
	RoomTypeC *c = new RoomTypeC(5,5,10,15);
	me->hotelRoom.push_back(c);
	RoomTypeB *d = new RoomTypeB(40,10);
	me->hotelRoom.push_back(d);
	RoomTypeB *e = new RoomTypeB(50,10);
	me->hotelRoom.push_back(e);
	RoomTypeA *f = new RoomTypeA(50,10);
	me->hotelRoom.push_back(f);
	RoomTypeC *g = new RoomTypeC(5,5,10,15);
	me->hotelRoom.push_back(g);
	RoomTypeD *h = new RoomTypeD(50, 10);
	me->hotelRoom.push_back(h);
	RoomTypeA *j = new RoomTypeA(50,10);
	me->hotelRoom.push_back(j);
	RoomTypeC *k = new RoomTypeC(5,5,10,15);
	me->hotelRoom.push_back(k);
	RoomTypeD *ll = new RoomTypeD(50,10);
	me->hotelRoom.push_back(ll);
	RoomTypeA *m = new RoomTypeA(50,10);
	me->hotelRoom.push_back(m);
	RoomTypeD *n = new RoomTypeD(50,10);
	me->hotelRoom.push_back(n);
	RoomTypeE *o = new RoomTypeE(5,5,10,20);
	me->hotelRoom.push_back(o);
	RoomTypeE *pp = new RoomTypeE(5,5,10,20);
	me->hotelRoom.push_back(pp);
	RoomTypeE *q = new RoomTypeE(5,5,10,20);
	me->hotelRoom.push_back(q);
	Room *r = new Room(15);
	me->hotelRoom.push_back(r);

	cout << "\nRooms Added To The Hotel LIST Successfully!" << endl;

	srand(time(NULL));//Seeding the generator of pseudo-random integers.
	do
	{
		cout << ("\n-----------------------------------------------------------------------------------\n\n");
		int arrDay = 1;
		arrDay = ((1 + rand()) % 30);//Generating the number of the arrival day.
		int accDays;
		if (arrDay == 30)//Checking if the arrival day exceeds 30.
			accDays = 1;
		else
		{
			accDays = 1 + (rand() % (30 - arrDay));//Generating the number of accomodation days.
		}
		Booking *booka = new Booking(names[rand() % 25], arrDay, accDays, 1 + (rand() % 10));//Creating a random booking.
		cout << "********************************************************************" << endl;
		cout << *booka;
		cout << "********************************************************************" << endl;
		me->addBookingNoID(booka);

		int chance = 2;//Setting the random booking cancelation chance at 25%.
		setCancelationChance(4);
		if ((rand() % cancelationChance) == chance)//Checking if a random booking will be deleted.
		{
			int qw = rand() % (me->hotelBooking.size());
			cout << "\n\nRANDOM canceling booking with ID: " << me->hotelBooking[qw]->getBookingID()<< endl << endl;
			me->deleteBooking(me->hotelBooking[qw]->getBookingID());
		}
		else
		{
			cout << "\nThere was not a RANDOM Cancelation!\n" << endl<< endl;
		}
		cout << ("--Next Loop 1") << endl;
		cout << ("--Add Booking 2") << endl;
		cout << ("--Cancel Booking 3") << endl;
		cout << ("--Print Booking 4") << endl;
		cout << ("--Print Rooms 5") << endl;
		cout << ("--Print Booking Plan 6") << endl;
		cout << ("--Print Income 7") << endl;
		cout << ("--Exit 8") << endl;
		cout << ("Choose what you want to do, give a number: ") << endl;

		cin >> input;//Reading the user's choice.
		switch (input)//Checking the function that the user wants.
		{
		case 1:
			cout << "Next loop" << endl;
			break;
		case 2:
		{
			cout << "Creating Booking.. :" << endl;
			cout << "Enter name: " << endl;
			string name;
			cin.ignore();
			getline(cin, name);
			cout << "Enter arrival day: " << endl;
			int arrivDay;
			cin >> arrivDay;
			cout << "Enter accomodation days:" << endl;
			int accomDay;
			cin >> accomDay;
			cout << "Enter how many people will be in the room:" << endl;
			int peopNum;
			cin >> peopNum;
			string remainder; //Reading the remainder of line.
			getline(cin, remainder);
			Booking *bookia = new Booking(name, arrivDay, accomDay, peopNum);
			cout << "Do you wanna book in a specific ROOM? Enter Room ID. Otherwise enter 0" << endl;
			int ID;
			cin >> ID;
			if (ID == 0)
			{
				me->addBookingNoID(bookia);
			}
			else
			{
				me->addBookingToRoom(bookia, ID);
			}
			break;
		}
		case 3:
			cout << "Enter the ID of the booking" << endl;
			int BID;
			cin >> BID;
			cout << "Canceling your Booking.." << endl;
			me->deleteBooking(BID);
			break;
		case 4:
		{
			int i = 0;
			cout << "BookingID\tClient Name\tRoomID" << endl;
			for (i = 0; i < me->hotelBooking.size(); i++)
			{
				cout << me->hotelBooking[i]->getBookingID()
					<< "\t\t" << me->hotelBooking[i]->getClientName() << "\t\t" << me->hotelBooking[i]->getRoom()->getRoomID()
					<< endl;
			}
			break;
		}
		case 5:
		{
			cout << "Room ID\t\tFullness\t\tIncome" << endl;
			double priceOfRoom;
			for (i = 0; i < me->hotelRoom.size(); i++)
			{
				priceOfRoom = me->hotelRoom[i]->getPriceOfRoom();

				cout << me->hotelRoom[i]->getRoomID() << "\t\t" << me->hotelRoom[i]->checkFullness() << "%\t\t" << priceOfRoom << endl;
			}
			break;
		}
		case 6:
			cout << "Booking Plan:" << endl;
			me->bookingPlan();
			break;
		case 7:
			cout << "Specific Room ID? (Press 0 if you don't want to enter an ID)"<<endl;
			int RID;
			cin >> RID;
			if (RID == 0)
				cout << "Total income of the hotel is: " << me->income() << endl;
			else
				me->income(RID);
			break;
		case 8:
			cout << "Simulation Terminated" << endl;
			exit(0);
			break;
		}
		cout << "Press 9 to end simulation!!!" << endl;
		cin >> input;
	} while (input != 9);
	return 0;
}