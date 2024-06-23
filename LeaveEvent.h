#include"Event.h"
#pragma once

class Company;

class LeaveEvent :public Event
{
	char Leave;
	int Id;
	Time EventTime;
	int StartStation;
public:
	LeaveEvent(char L, int hour, int min, int id, int ststation);
	virtual void Execute(Company* pComp);
};
