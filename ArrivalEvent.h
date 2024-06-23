#include"Event.h"
#pragma once
class Company;

class ArrivalEvent : public Event
{
	char ArrivalChar;
	string PassengerType;
	Time EventTime;
	int Id;
	int StartStation;
	int EndStation;
	int Geton_offTime;
public:

	ArrivalEvent(char, string, string, int hour, int min, int id, int Startstation, int Endstation,int);
	virtual void Execute(Company* pCompany);
};

