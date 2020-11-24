#include "RoomTypeD.h"
#include <iostream>
double priceOfRoom;

RoomTypeD::RoomTypeD(double priceOfRoom,int maxPeople)//Default cestructor for a RoomTypeD type object.
{
	setPriceOfRoom(priceOfRoom);
	setMaxPeople(maxPeople);
}

RoomTypeD::~RoomTypeD()//Default destructor for a RoomTypeD type object.
{
}

double RoomTypeD::getPriceOfRoom()//Function that returns the price of a room type D.
{
	double moneyEarnedFromRoom = 0;
	int i = 0;
	for (i = 1; i<31; i++)
	{
		if (roomAvailability[i] != 0)
			moneyEarnedFromRoom += priceOfRoom;
	}
	return moneyEarnedFromRoom;
}

bool RoomTypeD::addBooking(Booking* a)//Function that returns true if you can book in a room and books at it or false if not.
{
	int i;
	for (i = a->getArrivalDay(); i <= a->getArrivalDay() + a->getAccomodationDays() - 1; i++)
	{
		if (this->roomAvailability[i] != 0 || a->getPeopleNum() > this->getMaxPeople())
			return false;
	}
	
	if (a->getAccomodationDays() == 1)
	{
		this->roomAvailability[i] = a;
	}
	else
	{
		return false;
	}
	a->setRoom(this);//Change the Room type pointer form 0(null pointer) to this Room.
	return true;
}

bool RoomTypeD::cancelBooking(int bookingID)//Function that returns false when trying to cancel a booking at a room type D.
{
	std::cout << "Can't cancel room type D." ;
	return false;
}

void setPriceOfRoom(double priceOfRoom)
{
	priceOfRoom = priceOfRoom;
}