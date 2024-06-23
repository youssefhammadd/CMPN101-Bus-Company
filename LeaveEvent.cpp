#include "LeaveEvent.h"
#include"Company.h"
LeaveEvent::LeaveEvent(char L, int hour, int min, int id, int ststation) :Event(hour, min, id)
{
	Leave = L;
	EventTime.SetTime(hour, min);
	Id = id;
	StartStation = ststation;
}
void LeaveEvent::Execute(Company* pCom)
{
	pCom->LeavePassengerEvent(Id, StartStation);
}
