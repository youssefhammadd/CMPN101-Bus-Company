#pragma once

#include"ArrivalEvent.h"
#include"LeaveEvent.h"

#include"Station.h"
#include"Passenger.h"

#include"UI.h"
#include<fstream>

class UI;
class Event;
class Company
{
	Queue<Event*>* EventList;
	Station* ArrayofStations;
	Queue<Bus*>StationZeroBuses;
	Queue<Passenger*> FinishPassengerList;
	int NumberofStations;

	Queue<Bus*>MovingForwardBus;
	Queue<Bus*>MovingBackwardBus;

	Queue<Bus*> CheckupMBusList;
	Queue<Bus*> CheckupWBusList;

	Time Timer;
	UI* pUI;
	int TimeBetween2Stations;
	int ON_OFFTime;//Time in seconds for 1 passenger to get on or off the bus

public:
	Company();
	//int getRandomNumber();
	//void MoveRandomPassengertoFinishList();
	void SetON_OFFTime(int);
	int GetON_OFFTime();
	Time GetCurrTime();
	bool inWorkingHours(Time currTime);
	bool executeCurrEvents(Time currTime);
	/*bool ExecuteAll(Time currTime);*/
	void LoadFile();
	bool notEndOfSimulation();
	void AddPassengertoStationList(Passenger* p);//create passenger in arrival event and then call this function to put this passenger in his proper list
	void AddFinishedPassenger(Passenger* p);//passenger finished his destination
	void Simulate();
	bool FindPassengerinQueue(Queue<Passenger*> PassengerList, Passenger* p);// take a queue of passenger lookin for a certain passenger
	Passenger* FindPassengerinLinkedList(LinkedList<Passenger*> PassengerList, Passenger* p);//takes linkedlist of passenger looking for a certain passenger
	Passenger* LeavePassengerEvent(int id, int StationNumber);//when passenger has to leave his start station (LeaveEvent)
	Queue<Passenger*>* GetFinsihPassengerList();

	void MovingBusesfromStation0(Time CurrTime);
	void ArrivingBustoStation(Time CurrTime);
	bool BoardingPassengers(Time CurrTime);
	void DropOffPassenger(Time CurrTime);
	void LeavingBusFromStation(Time);



	Queue<Bus*> MovingForwardBusses();
	Queue<Bus*> MovingBackwardBusses();

	/*bool ExecuteBus(Time currTime);*/
	~Company();




	void AutoPromotePassengers(Time CurrTime);
	void OutputSimulationResult(ostream& out);//h
	void MovingBusesfromCheckup(Time CurrTime);
};


