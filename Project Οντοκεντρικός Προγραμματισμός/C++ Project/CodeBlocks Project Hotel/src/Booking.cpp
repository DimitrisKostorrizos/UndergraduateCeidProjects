#include <Booking.h>

int Booking::bookingInstanceCounter = 0; //Initialization of the variable "bookingInstanceCounter" at 0, used for ID binding.
string clientName;//Variable used for the name of the client for a Booking object.
int arrivalDay;//Variable used for the arrival day of a Booking object.
int accomodationDays;//Variable used for the accomodation days of a Booking object.
int peopleNum;//Variable used for the number of people of a Booking object.
int bookingID; //Variable used for ID binding.
static int bookingInstanceCounter; //Variable used for ID binding.
Room *room;//Room type pointer.


Booking::Booking(string name, int _arrivalDay, int _accomodationDays, int _peopleNum)//Constructor for a Booking type object.
{
	clientName = name;
	arrivalDay = _arrivalDay;
	accomodationDays = _accomodationDays;
	peopleNum = _peopleNum;
	setBookingID();//Increasing the bookingID variable by each successful booking constructed.
}

Booking::~Booking()//Default destructor for a Booking type object.
{
}

string getClientName()//Getter for the variable clientName.
{
	return clientName;
};

void setClientName(string val)//Setter for the variable clientName.
{
	clientName = val;
}

int getArrivalDay()//Getter for the variable arrivalDay.
{
	return arrivalDay;
}

void setArrivalDay(int val)//Setter for the variable arrivalDay.
{
	arrivalDay = val;
}

int getAccomodationDays()//Getter for the variable accomodationDays.
{
	return accomodationDays;
}

void setAccomodationDays(int val)//Setter for the variable accomodationDays.
{
	accomodationDays = val;
}

int getPeopleNum()//Getter for the variable peopleNum.
{
	return peopleNum;
}

void setPeopleNum(int val)//Setter for the variable peopleNum.
{
	peopleNum = val;
}

void setBookingID()//Setter for the variable bookingID.
{
	bookingID = ++bookingInstanceCounter;
}

int getBookingID()//Getter for the variable bookingID.
{
	return bookingID;
}

void setRoom(Room *a)//Setter for the Room type pointer.
{
	room = a;
}

Room* getRoom()//Getter for the Room type pointer.
{
	return room;
}
