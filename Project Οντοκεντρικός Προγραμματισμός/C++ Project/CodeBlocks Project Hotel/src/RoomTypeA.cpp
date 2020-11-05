#include <RoomTypeA.h>

double pricePerDay;//Variable for the price per day of a room type A.

RoomTypeA::RoomTypeA()//Default constructor for a RoomTypeA type object.
{
}

RoomTypeA::RoomTypeA(double pricePerDay,int maxPeople)//Constructor for a RoomTypeA type object.
{
	setPricePerDay(pricePerDay);
	setMaxPeople(maxPeople);
}

RoomTypeA::~RoomTypeA()//Default destructor for a RoomTypeA type object.
{
}

double RoomTypeA::getPriceOfRoom()//Function that returns the price of a room type A.
{
	int i;
	double moneyEarnedFromRoom = 0;
	for (i = 0; i < 31; i++)
	{
		if (roomAvailability[i] != 0)
			moneyEarnedFromRoom += pricePerDay;
	}
	return moneyEarnedFromRoom;
}

double getPricePerDay()//Getter for the variable pricePerDay.
{
	return pricePerDay;
}

void setPricePerDay(double val)//Setter for the variable pricePerDay.
{
	pricePerDay = val;
}
