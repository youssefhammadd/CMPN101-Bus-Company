#pragma once
#include"Passenger.h"

class Company;

class Event
{
	Time EventTime;
	int ID;
	
public:
	
	Event(int hours, int mins, int id);

	void setID(int id);
	int getID() const;

	void setEventTime(Time time);
	Time getEventTime() const;

	virtual void Execute(Company* pCom) = 0;

};
