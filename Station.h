#pragma once
#include "Queue.h"
#include "Bus.h"
#include"LinkedList.h"




class Station
{
	int TotalNumberOfStations;
	Time TimeBetweenStations;


	Queue<Bus*> ForwardWaitingBus; //for waiting buses in the station
	Queue<Bus*> BackwardWaitingBus;


	Queue<Passenger*> ForwardWaitingWheelPassenger;  //for waiting Wheel chair passengers forward and backward
	Queue<Passenger*> BackwardWaitingWheelPassenger;


	PriorityQueue<Passenger*> ForwardWaitingSpecialPassenger;  //for waiting special passengers forward and backward
	PriorityQueue<Passenger*> BackwardWaitingSpecialPassenger;


	LinkedList<Passenger*> ForwardWaitingNormalPassenger;     //for waiting normal passengers forward and backward
	LinkedList <Passenger*> BackwardWaitingNormalPassenger;

	
	
public:
	Station();
	void SetTotalNumberOfStations(int s);
	int GetTotalNumberOfStations();
	void SetTimeBetweenStations(Time t);
	Time GetTimeBetweenStations();
	bool ArrivingPassenger(Passenger* p);
	Passenger* LeavingStationEvent(Passenger* p);
	//bool ArrivedPassengertoEndStation(Passenger* p);

	bool BoardingPassengers(Bus* B,int&);
	/*bool DropOffPassenger(Bus* pBus, int&);*/
	bool ArrivingBus(Bus* B);
	Bus* LeavingBus(Bus* B);
	bool FindingPassenger(Passenger* p);
	Passenger* RemovePassengerfromStation(Passenger* p);



	//getters for all the lists i used in this class
	LinkedList<Passenger*>* GetNormalForwardPassengerList();
	LinkedList<Passenger*>* GetNormalBackwardPassengerList();
	PriorityQueue<Passenger*>* GetSpecialForwardPassengerList();
	PriorityQueue<Passenger*>* GetSpecialBackwardPassengerList();
	Queue<Passenger*>* GetWheelForwardPassengerList();
	Queue<Passenger*>* GetWheelBackwardPassengerList();
	Queue<Bus*>* GetForwardBusesinStation();
	Queue<Bus*>* GetBackwardBusesinStation();
	~Station();



	void AutoPromotePassengers(Time CurrTime);
};
