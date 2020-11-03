#ifndef ROOMTYPEA_H
#define ROOMTYPEA_H

#include <Room.h>


class RoomTypeA : public Room
{
public:
	RoomTypeA();
	RoomTypeA(double pricePerDay, int maxPeople);
	virtual ~RoomTypeA();

	double getPricePerDay() { return pricePerDay; }
	void setPricePerDay(double val) { pricePerDay = val; }

	double getPriceOfRoom();
private:
	double pricePerDay;
};

#endif // ROOMTYPEA_H
