#include "Event.h"
#include"Company.h"



Event::Event(int hours, int min, int id)
{
	EventTime.SetTime(hours, min);
	ID = id;
}
/*Event::Event(Company* pComp)
{
	pCompany = pComp;
}*/
void Event::setID(int id)
{
	ID = id;
}
int Event::getID() const
{
	return ID;
}

void Event::setEventTime(Time time)
{
	EventTime = time;
}
Time Event::getEventTime() const
{
	return EventTime;
}
