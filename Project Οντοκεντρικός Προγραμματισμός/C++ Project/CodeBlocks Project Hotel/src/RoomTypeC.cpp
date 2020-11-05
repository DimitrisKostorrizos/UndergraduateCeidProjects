#include <RoomTypeC.h>

#include<Booking.h>

int minPeople;//Variable used for the minimum people of a room type C.
int minDays;//Variable used for the minimum days of a room type C.

RoomTypeC::RoomTypeC()//Default constructor for a RoomTypeC type object.
{
}

RoomTypeC::RoomTypeC(int minPeople, int minDays,int maxPeople,double pricePerPerson)//Constructor for a RoomTypeC type object.
{
	setMinPeople(minPeople);
	setMinDays(minDays);
	setMaxPeople(maxPeople);
	setPricePerPerson(pricePerPerson);
}

RoomTypeC::~RoomTypeC()//Default destructor for a RoomTypeC type object.
{
}

bool RoomTypeC::addBooking(Booking *a)//Function that returns true if you can book in a room type C or false if not.
{
	int i;
	for (i = a->getArrivalDay(); i <= a->getArrivalDay() + a->getAccomodationDays() - 1; i++)
	{
		if (roomAvailability[i] != 0 || a->getPeopleNum() > this->getMaxPeople() || a->getPeopleNum() < this->minPeople || a->getAccomodationDays() < this->minDays)
			return false;
	}
	for (i = a->getArrivalDay(); i <= a->getArrivalDay() + a->getAccomodationDays() - 1; i++)
	{
		roomAvailability[i] = a;
	}
	a->setRoom(this);//Change the Room type pointer form 0(null pointer) to this RoomTypeC.
	return true;
}

int getMinPeople()//Getter for the variable minPeople.
{
	return minPeople;
}

void setMinPeople(int val)//Setter for the variable minPeople.
{
	minPeople = val;
}

int getMinDays()//Getter for the variable minDays.
{
	return minDays;
}

void setMinDays(int val)//Setter for the variable minDays.
{
	minDays = val;
}
