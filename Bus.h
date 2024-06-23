#pragma once
#include"Passenger.h"
#include"PriorityQueue.h"

class Bus
{
	string Type;
	int ID;
	int Bus_Capacity;
	int Bus_Size = 0;
	int J;//number of trips bus made to checkup
	int CurrentStation;
	int NextStation;
	int LastStation;
	int TotalTrips;
	int TimeBetweenTwoStations;
	string Direction;
	PriorityQueue<Passenger*> PassengerList;
	Time BusBusyTime;
	int TotalTransportedPassenger = 0;
	int TotalBusyTime;
	int TotalSimulationTime;
	int BusUtilization;
	Time currentTime;
	int startingHours = 4;
	int endingHours = 22;
	int BusSpeed;
	Time CheckupStart;
	float CheckupDuration;
	Time CheckupEnd;

	Time LeaveTime;//the time the bus leave the station
	Time ArriveTime;//the time the bus arrive to the station
	int GETON_OFFTime;

public:
	//function to check if the bus is in maintenance or not to us it in compamy->MovingBusFromStation0



	Bus();
	void SetBusID(int x);
	int GetBusID();
	void SetON_OFFTime(int x);
	int GetON_OFFTime();
	void SetArriveTime(int Hour,int Minute);
	Time GetArriveTime();
	void SetLeaveTime(int Hour, int Minute);
	Time GetLeaveTime();
	void SetBusCapacity(int BC);
	int GetBusCapacity();
	bool isfull();
	void setTripsToCheckUp(int);
	int getTripsToCheckUp();
	void SetTimeBetweenTwoStations(int);
	int GetTimeBetweenTwoStations();
	void SetType(string);
	void SetBusSpeed(int x);
	int GetBusSpeed();
	void SetCheckUpDuration(float x);
	float GetCheckUpDuration();
	string getType();
	void SetCurrentStation(int);
	void SetNextStation(int);
	void SetLastStation(int);
	void SettingBusStations();
	string GetDirection();
	bool PassengerGetOn(Passenger*);//send to the function Pointer of passenger Node to link it to the list
	/*bool BoardingPassengertoBus(Passenger* p);*/

	PriorityQueue<Passenger*>* GetPassengerListInsideBus();

	bool BusIsBusy();
	Passenger* PassengerDropOff(int index);
	void CalculateBusUtilization();
	int GetBusUtilizatiion();
	int GetCurrentStation();
	int GetNextStation();
	float revertToHours(Time);
	friend std::ostream& operator<<(ostream& output, Bus* pBus);
	
	~Bus();
};

