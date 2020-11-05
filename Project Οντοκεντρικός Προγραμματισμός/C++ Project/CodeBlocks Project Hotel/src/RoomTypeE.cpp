#include <RoomTypeE.h>
#include <Booking.h>

RoomTypeE::RoomTypeE(int minPeople, int minDays,int maxPeople,int pricePerPerson)//Constructor for a RoomTypeE type object.
{
	setMinPeople(minPeople);
	setMinDays(minDays);
	setMaxPeople(maxPeople);
	setPricePerPerson(pricePerPerson);
}

RoomTypeE::~RoomTypeE()//Default destructor for a RoomTypeE type object.
{
}

double RoomTypeE::getPriceOfRoom()//Function that returns the price of a room type E.
{
	int i = 0;
	double moneyEarnedFromRoom = 0;
	double discountPerPerson;
	for (i = 1; i<31; i++)
	{
		if (roomAvailability[i] != 0)
		{
			if (i <= 3)
			{
				discountPerPerson = (this->getPricePerPerson() / 2);//Calculating the discount per day for a room type E.
				moneyEarnedFromRoom += (roomAvailability[i]->getPeopleNum()*(this->getPricePerPerson() - discountPerPerson));
				continue;
			}
			moneyEarnedFromRoom += (roomAvailability[i]->getPeopleNum() * this->getPricePerPerson());
		}
	}
	return moneyEarnedFromRoom;
}
