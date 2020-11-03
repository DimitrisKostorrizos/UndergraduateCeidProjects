#ifndef ROOM_H
#define ROOM_H

class Booking;//Forward Declaration.

class Room
{
public:
	Room();
	Room(int pricePerPerson);
	virtual ~Room();

	double getPricePerPerson() { return pricePerPerson; }
	void setPricePerPerson(int val) { pricePerPerson = val; }
	int getMaxPeople() { return maxPeople; }
	void setMaxPeople(int val) { maxPeople = val; }
	void setRoomID() { roomID = ++roomInstanceCounter; }
	int getRoomID() { return roomID; }

	Booking* getRoomAvailability(int i) { return *(roomAvailability + i); }

	virtual bool addBooking(Booking*);

	virtual double getPriceOfRoom();
	virtual bool cancelBooking(int);
	double checkFullness();

protected:
	Booking *roomAvailability[31] = {};

private:
	int pricePerPerson;
	int maxPeople;
	int roomID;
	static int roomInstanceCounter;
};
#endif // ROOM_H
