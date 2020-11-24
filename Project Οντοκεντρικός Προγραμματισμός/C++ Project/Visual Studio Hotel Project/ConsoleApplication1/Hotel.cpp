#include "Hotel.h"
#include <vector>
#include <algorithm>

string hotelName;//Variable used for the name of a Hotel type object.
vector<Room> hotelRoom;//Vector used for the rooms of a Hotel type object.
vector<Booking> hotelBooking;//Vector used for the bookings of a Hotel type object.


Hotel::Hotel(string name)//Constructor for a Hotel type object.
{
	hotelName = name;
	vector<Room*> hotelRoom;//Creation of vector used for Room type pointers.
	vector<Booking*> hotelBooking;//Creation of vector used for Booking type pointers.
}

Hotel::~Hotel()//Default destructor for a Hotel type object.
{
}


bool operator>(Booking& bb, RoomTypeC& cc)//Implementation for the overloading of the operator >, used by a Booking and RoomTypeC type objects.
{
	return (bb.getPeopleNum() < cc.getMinPeople() || bb.getAccomodationDays() < cc.getMinDays());//Checking the minDays and the minPeople variables of a Room *bb and a RoomTypeC *cc.
}

bool operator<(int x, Booking& booking)//Implementation for the overloading of the operator <, used by a Booking type object and an integer.
{
	return x < booking.getAccomodationDays();//Checking if the accomodationDays variable, of Booking *bb, is greater than x.
}

void Hotel::addHotelRoom(Room* room)//Function that puts a Room type object in the hotelRoom vector.
{
	hotelRoom.push_back(room);
}

Room* Hotel::recoverRoomOutOfID(int ID)//Function that returns a Room type pointer if there is a room with the ID or 0(null pointer) if not.
{
	unsigned int i;
	for (i = 0; i<hotelRoom.size(); i++)
	{
		if (hotelRoom[i]->getRoomID() == ID)
		{
			return hotelRoom[i];
		}
	}
	return false;
}

Booking* Hotel::recoverBookingOutOfID(int ID)//Function that returns a Booking type pointer if there is a booking with the ID or 0(null pointer) if not.
{
	unsigned int i;
	for (i = 0; i < hotelBooking.size(); i++)
	{
		if (hotelBooking[i]->getBookingID() == ID)
			return hotelBooking[i];
	}
	return false;
}

bool Hotel::addBookingToRoom(Booking* aa, int ID)//Function that returns true if you can book in a room with the ID or false if not.
{
	Room *roomaki = new Room();
	if ((roomaki->addBooking(aa) == false) || (recoverRoomOutOfID(ID)==false))
	{
		cout << "Booking not successful" << endl;
		return false;
	}
	if (RoomTypeE* rte = dynamic_cast<RoomTypeE*>(recoverRoomOutOfID(ID)))//Checking if the room *aa is a RoomTypeC object.
	{
		if (*aa > *rte)
		{
			cout << "Booking not successful, cannot Book in Room Type E not enough days or not enough people." << endl;
			return false;
		}
	}
	if (RoomTypeC* rtc = dynamic_cast<RoomTypeC*>(recoverRoomOutOfID(ID)))//Checking if the room *aa is a RoomTypeC object.
	{
		if (*aa > *rtc)
		{
			cout << "Booking not successful, cannot Book in Room Type C not enough days or not enough people." << endl;
			return false;
		}
	}
	if (RoomTypeD* rtd = dynamic_cast<RoomTypeD*>(recoverRoomOutOfID(ID)))//Checking if the room *aa is a RoomTypeD object.
	{
		if (1 < *aa)
		{
			cout << "Booking not successful, cannot Book in Room Type D single day room." << endl;
			return false;
		}

	}
	recoverRoomOutOfID(ID)->addBooking(aa);
	hotelBooking.push_back(aa);
	cout << "Booking succcessful with ID: " << aa->getBookingID() << endl;
	return true;
}

int Hotel::addBookingNoID(Booking* aaa)//Function that returns true if you can book in a room or false if not.
{
	unsigned int i;
	for (i = 0; i < hotelRoom.size(); i++)
	{
		if (hotelRoom[i]->addBooking(aaa) == true)
		{
			hotelRoom[i]->addBooking(aaa);
			cout << "Booking successful in room with id: " << hotelRoom[i]->getRoomID() << endl;
			cout << "Booking ID: " << aaa->getBookingID() <<endl;
			hotelBooking.push_back(aaa);
			return hotelRoom[i]->getRoomID();
		}

	}
	cout << "NOT SUCCESSFUL BOOKING." << endl;
	return 0;
}

void Hotel::deleteBooking(int ID)//Function that returns a message that informs if you can delete a booking or if there isn't a booking with an ID.
{
	if (recoverBookingOutOfID(ID) != 0)
	{
		if (recoverBookingOutOfID(ID)->getRoom()->cancelBooking(ID) == true)
		{
			recoverBookingOutOfID(ID)->getRoom()->cancelBooking(ID);
			hotelBooking.erase(remove(hotelBooking.begin(), hotelBooking.end(), recoverBookingOutOfID(ID)), hotelBooking.end());//Searches the whole vector and if it finds the object we want, it will get deleted.
			cout << "Cancelation Successful!" << endl;
		}
	}
	else
		cout << "There is not a booking with this ID, check bookings and try again." << endl;
}

double Hotel::income(int ID)//Function that returns the amount of income earned from a room.
{
	if (recoverRoomOutOfID(ID) == false)
	{
		cout << "No room with this ID" << endl;
		return 0;
	}
	cout << "Money earned from this room " << recoverRoomOutOfID(ID)->getPriceOfRoom() << "." << endl;
	return recoverRoomOutOfID(ID)->getPriceOfRoom();
}

double Hotel::income()//Function that returns the amount of income earned from the hotel.
{
	double totalEarnings = 0;
	unsigned int i;
	for (i = 0; i < hotelRoom.size(); i++)
	{
		totalEarnings += hotelRoom[i]->getPriceOfRoom();
	}
	return totalEarnings;
}

void Hotel::bookingPlan()//Function that prints the booking plan of all the rooms currently at the hotel.
{
	unsigned int i, k;
	cout << "Room\t\t";
	for (i = 1; i<31; i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (i = 0; i < hotelRoom.size(); i++)
	{
		cout << hotelRoom[i]->getRoomID() << "\t\t";
		for (k = 1; k<31; k++)
		{
			if (hotelRoom[i]->getRoomAvailability(k) == 0)
			{
				cout << "_\t";
			}
			else
			{
				cout << "*\t";
			}
		}
		cout << endl;
	}
}

string getHotelName()//Getter for the variable hotelName.
{ 
	return hotelName; 
}

void setHotelName(string name)//Setter for the variable hotelName.
{
	hotelName = name;
}