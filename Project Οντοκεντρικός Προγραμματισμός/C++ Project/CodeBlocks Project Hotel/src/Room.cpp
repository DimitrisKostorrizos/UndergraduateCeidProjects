#include <Room.h>
#include <Booking.h>

int Room::roomInstanceCounter = 100;//Initialization of the variable roomInstanceCounter at 100, used for Room ID binding.
int pricePerPerson;//Variable used for the price per person of a Room object.
int maxPeople;//Variable used for the maximum people of a Room object.
Booking *roomAvailability[31];//An 31 Booking pointers elements array.
int roomID;//Variable used for Room ID binding.
static int roomInstanceCounter;//Variable used for Room ID binding.

Room::Room()//Constructor for a Room type object.
{
	setPricePerPerson(15);//Initialization of the pricePerPerson variable at 15.
	setMaxPeople(10);//Initialization of the maxPeople variable at 10.
	Booking *roomAvailability[31] = { 0 };//Initialization of every element of the roomAvailability array at 0(null pointer).
	setRoomID();//Increasing the roomID variable by each successful room constructed.
}

Room::Room(int pricePerPerson)//Constructor for a Room type object.
{
	setPricePerPerson(pricePerPerson);//Initialization of the pricePerPerson variable at 15.
	setMaxPeople(10);//Initialization of the maxPeople variable at 10.
	Booking *roomAvailability[31] = { 0 };//Initialization of every element of the roomAvailability array at 0(null pointer).
	setRoomID();//Increasing the roomID variable by each successful room constructed.
}

Room::~Room()//Default destructor for a Room type object.
{
	roomInstanceCounter--;
}

bool Room::addBooking(Booking* a)//Function that returns true if you can book in a room and books at it or false if not.
{
	int i;
	for (i = a->getArrivalDay(); i <= a->getArrivalDay()+ a->getAccomodationDays() - 1; i++)
	{
		if (this->roomAvailability[i] != 0 || a->getPeopleNum() > this->getMaxPeople())
			return false;
	}
	for (i = a->getArrivalDay(); i <= a->getArrivalDay() + a->getAccomodationDays() - 1; i++)
	{
		this->roomAvailability[i] = a;
	}
	a->setRoom(this);//Change the Room type pointer form 0(null pointer) to this Room.
	return true;
}


double Room::getPriceOfRoom()//Function that returns the money earned from a room.
{
	int i;
	double moneyEarnedFromRoom = 0;
	for (i = 1; i < 31; i++)
	{
		if (this->roomAvailability[i] != 0)
			moneyEarnedFromRoom += (roomAvailability[i]->getPeopleNum() * getPricePerPerson());
	}
	return moneyEarnedFromRoom;
}


bool Room::cancelBooking(int BookingID)//Function that cancels a booking.
{
	int i;
	for (i = 1; i<31; i++)
	{
		if (this->roomAvailability[i] != 0 && this->roomAvailability[i]->getBookingID() == BookingID)
		{
			this->roomAvailability[i] = 0;
		}
	}
	return true;
}


double Room::checkFullness()//Function that returns the percentage fullness of a room.
{
	int i;
	double fullnessPercentage = 0;
	int daysCounter = 0;
	for (i = 1; i<31; i++)
	{
		if (this->roomAvailability[i] != 0)
		{
			daysCounter++;
		}
	}
	fullnessPercentage = ((double)daysCounter / 30) * 100.0;
	return fullnessPercentage;
}

int getPricePerPerson()//Getter for the variable pricePerPerson.
{
	return pricePerPerson;
}

void setPricePerPerson(int val)//Setter for the variable pricePerPerson.
{
	pricePerPerson = val;
}

int getMaxPeople()//Getter for the variable maxPeople.
{
	return maxPeople;
}

void setMaxPeople(int val)//Setter for the variable maxPeople.
{
	maxPeople = val;
}

void setRoomID()//Setter for the variable roomID.
{
	roomID = ++roomInstanceCounter;
}

int getRoomID()//Getter for the variable roomID.
{
	return roomID;
}

Booking* getRoomAvailability(int i)//Function that returns the element of the roomAvailability array at [i].
{
	return *(roomAvailability + i);
}
