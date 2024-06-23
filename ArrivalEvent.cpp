#include "ArrivalEvent.h"
#include "Company.h"

ArrivalEvent::ArrivalEvent(char Arrival, string typ, string ExtraTyp, int hour, int min, int id, int Ststation, int Enstation,int GetONandOFF) :Event(hour, min, id)
{
	ArrivalChar = Arrival;
	if (typ == "SP")
	{
		PassengerType = typ + ExtraTyp;
	}
	else
	{
		PassengerType = typ;
	}
	EventTime.SetTime(hour, min);
	Id = id;
	StartStation = Ststation;
	EndStation = Enstation;
	Geton_offTime = GetONandOFF;
}
void ArrivalEvent::Execute(Company* pComp)
{
	Passenger* pPassenger = new Passenger();
	pPassenger->SetType(PassengerType);
	pPassenger->SetArrTime(EventTime.GetHours(), EventTime.GetMin());
	pPassenger->SetEndStation(EndStation);
	pPassenger->SetStartStation(StartStation);
	pPassenger->SetDirection(StartStation, EndStation);
	pPassenger->SetID(Id);
	pPassenger->SetGetONorOFF_Time(Geton_offTime);
	pComp->AddPassengertoStationList(pPassenger);

}
