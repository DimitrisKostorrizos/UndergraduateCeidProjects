#ifndef ROOMTYPEC_H
#define ROOMTYPEC_H

#include <Room.h>


class RoomTypeC : public Room
{
public:
	RoomTypeC();
	RoomTypeC(int minPeople, int minDays, int maxPeople, double pricePerPerson);
	virtual ~RoomTypeC();

	int getMinPeople() { return minPeople; }
	void setMinPeople(int val) { minPeople = val; }
	int getMinDays() { return minDays; }
	void setMinDays(int val) { minDays = val; }

	bool addBooking(Booking*);

private:
	int minPeople;
	int minDays;
};
#endif // ROOMTYPEC_H
