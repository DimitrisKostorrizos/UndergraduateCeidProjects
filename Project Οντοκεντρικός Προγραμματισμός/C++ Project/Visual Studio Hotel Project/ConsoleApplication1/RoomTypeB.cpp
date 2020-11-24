#include "RoomTypeB.h"

int discountPerDay = 0;//Variable for the discount per day of a room type B and initialization of it at 0.

RoomTypeB::RoomTypeB()//Default constructor for a RoomTypeB type object.
{
}

RoomTypeB::RoomTypeB(double pricePerDay,int maxPeople)//Constructor for a RoomTypeB type object.
{
	setPricePerDay(pricePerDay);
	setMaxPeople(maxPeople);
}

RoomTypeB::~RoomTypeB()//Default destructor for a RoomTypeB type object.
{
}

double RoomTypeB::getPriceOfRoom()//Function that returns the price of a room type B.
{
	int i = 0;
	double totalEarnings;
	double moneyEarnedFromRoom = 0;
	discountPerDay = 0;
	for (i = 1; i < 31; i++)
	{
		if (roomAvailability[i] != 0)
		{
			moneyEarnedFromRoom += (getPricePerDay() - discountPerDay);
			discountPerDay += 10;
			if ((discountPerDay / getPricePerDay()) > 0.5)//Calculating the discount per day for a room type B.
				discountPerDay = 0.5 * getPricePerDay();
		}
	}
	return moneyEarnedFromRoom;
}

bool RoomTypeB::cancelBooking(int bookingID)//Function that returns false when trying to cancel a booking at a room type B.
{
	std::cout << "Can't cancel room type B.";
	return false;
}