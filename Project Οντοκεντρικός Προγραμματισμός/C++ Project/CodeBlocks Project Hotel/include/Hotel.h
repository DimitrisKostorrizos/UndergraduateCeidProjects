#ifndef HOTEL_H
#define HOTEL_H

#include<iostream>
#include<string>
#include<vector>

#include<Room.h>
#include<RoomTypeC.h>
#include<RoomTypeD.h>
#include<RoomTypeE.h>
#include<Booking.h>


using namespace std;

class Hotel
{
public:
	Hotel(string);
	virtual ~Hotel();

	string getHotelName() { return hotelName; }
	void setHotelName(string name){	hotelName = name; }
	void addHotelRoom(Room* room);
	Room* recoverRoomOutOfID(int);
	Booking* recoverBookingOutOfID(int);
	bool addBookingToRoom(Booking*, int);
	int addBookingNoID(Booking*);
	void deleteBooking(int);
	double income(int);
	double income();
	void bookingPlan();
	vector <Room*> hotelRoom;
	vector<Booking*> hotelBooking;
	friend bool operator>(Booking& bb, RoomTypeC& cc);
	friend bool operator<(int x, Booking& aa);
private:
	string hotelName;
};
#endif // HOTEL_H
