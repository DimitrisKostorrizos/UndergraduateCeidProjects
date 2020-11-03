#ifndef ROOMTYPED_H
#define ROOMTYPED_H

#include <Room.h>
#include <Booking.h>


class RoomTypeD : public Room
{
public:
	RoomTypeD(double priceOfRoom, int maxPeople);
	virtual ~RoomTypeD();

	double getPriceOfRoom();
	void setPriceOfRoom(double price)
	{
		priceOfRoom = price;
	}
	bool cancelBooking(int);
	bool addBooking(Booking* a);
private:
	double priceOfRoom;
};
#endif // ROOMTYPED_H
