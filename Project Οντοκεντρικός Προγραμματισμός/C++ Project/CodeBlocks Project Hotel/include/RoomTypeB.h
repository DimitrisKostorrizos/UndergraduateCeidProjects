#ifndef ROOMTYPEB_H
#define ROOMTYPEB_H

#include<iostream>

#include <RoomTypeA.h>


class RoomTypeB : public RoomTypeA
{
public:
	RoomTypeB();
	RoomTypeB(double pricePerDay, int maxPeople);
	virtual ~RoomTypeB();

	int getDiscountPerDay() { return discountPerDay; }
	void setDiscountPerDay(int val) { discountPerDay = val; }

	double getPriceOfRoom();

	bool cancelBooking(int);

private:
	int discountPerDay;
};

#endif // ROOMTYPEB_H
