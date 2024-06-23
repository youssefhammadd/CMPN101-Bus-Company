#pragma once
#include"Time.h"

class Passenger
{
	int ID;
	Time Arr_Time;//arrival time
	Time Mov_Time;//move time ,time the bus move from the station
	Time Waiting_Time;//time waited by the passenger in the station
	Time Trip_Time;//the time taken inside the bus  Finish time-Move time
	Time Finish_Time;
	Time MaxWait;
	int Start_station;
	int End_station;
	string Type;
	string Direction;
	int Priority;
	int GetONorOFF_Time;//in seconds
	bool AutoPromotion;
	

public:
	Passenger();
	
	void SetID(int x);

	void SetArrTime(int hours, int minutes);//set arrival time

	void SetMovTime(int hours, int minutes);

	void SetWaitTime();

	void SetTripTime();

	void SetFinishTime(int , int , int);

	void SetType(string Type);

	void SetGetONorOFF_Time(int Seconds);

	void SetStartStation(int);

	void SetEndStation(int);

	void SetMaxWaitTime(int minutes);//in minutes

	int GetID();

	int GetStartStation();

	int GetEndStation();
	void SetDirection(int Start,int End);

	string GetType();

	Time GetArrTime();

	Time GetMovTime();

	Time GetWaitTime();

	Time GetTripTime();

	Time GetFinishTime();

	string Determine_Destination();//returns Forward or Backward

	
	void operator=(Passenger&);
	
	friend std::ostream& operator<<(ostream& output,Passenger * p);
	bool operator==(const Passenger* other) const;// {

	

	~Passenger();



	bool GetAutoPromotion();

	void SetAutoPromotion(bool promoted);
	int GetMaxWaitMinutes();

};


