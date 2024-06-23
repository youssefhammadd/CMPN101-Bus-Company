#pragma once

#include"Time.h"
#include"LinkedList.h"
#include"Station.h"


class Company;
using namespace std;

class UI
{
	Company* pCompany;
	string Mode;
public:
	void PrintAll(Time currTime, Station* ArrayofStations, int NumofStations);
	UI(Company* pC);
	string GetFileNameFromUser();
	string GetMode();
	void PrintMessagetoUser(string Mess);
	void GetModefromUser();

	void PrintStation(int Index);
	void PrintStations(Time CurrTime, Station* pStation, int, int index = 1);

	void PrintLinkedListofPassenger(LinkedList<Passenger*>* p);
	void PrintPriorityQueueofPassenger(PriorityQueue<Passenger*>* p);
	void PrintQueueofPassenger(Queue<Passenger*>* p);
	void PrintQueueofBus(Queue<Bus*> pBus);
	template<class t>
	void PrintAny(t msg)
	{
		cout << msg;
	}


};
