#ifndef ROOMTYPEE_H
#define ROOMTYPEE_H

#include "RoomTypeC.h"


class RoomTypeE : public RoomTypeC
{
public:
	RoomTypeE(int minPeople, int minDays, int maxPeople, int pricePerPerson);
	virtual ~RoomTypeE();

	double getPriceOfRoom();
};
#endif // ROOMTYPEE_H