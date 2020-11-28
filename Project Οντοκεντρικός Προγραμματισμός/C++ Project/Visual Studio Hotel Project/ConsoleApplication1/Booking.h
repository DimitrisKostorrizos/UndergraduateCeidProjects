#ifndef BOOKING_H
#define BOOKING_H

#include<iostream>

#include<string>

using namespace std;

class Room;//Forward Declaration.

class Booking
{
public:
	Booking(string name, int _arrivalDay, int _accomodationDays, int _peopleNum);
	virtual ~Booking();

	string getClientName() { return clientName; }
	void setClientName(string val) { clientName = val; }
	int getArrivalDay() { return arrivalDay; }
	void setArrivalDay(int val) { arrivalDay = val; }
	int getAccomodationDays() { return accomodationDays; }
	void setAccomodationDays(int val) { accomodationDays = val; }
	int getPeopleNum() { return peopleNum; }
	void setPeopleNum(int val) { peopleNum = val; }
	void setBookingID() { bookingID = ++bookingInstanceCounter; };
	int getBookingID() { return bookingID; }
	void setRoom(Room *a) { room = a; }
	Room* getRoom() { return room; }
	friend ostream& operator<<(ostream& os, const Booking& b);//Declaration for the overloading of the operator <<, used by a Booking type object.
private:
	string clientName;
	int arrivalDay;
	int accomodationDays;
	int peopleNum;
	int bookingID;
	static int bookingInstanceCounter;
	Room *room;

};
#endif//BOOKING_H