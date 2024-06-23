#include "UI.h"

#include"Company.h"

UI::UI(Company* pC)
{
	pCompany = pC;
}

string UI::GetFileNameFromUser()
{
	std::string Filename;
	cin >> Filename;
	return Filename;
}
string UI::GetMode()
{
	return Mode;
}
void UI::PrintMessagetoUser(string Mess)
{
	cout << Mess << endl;
}
void UI::PrintLinkedListofPassenger(LinkedList<Passenger*>* p)
{
	int temp;
	Passenger* pPassenger;
	for (int i = 0; i < p->count(); i++)
	{
		pPassenger=p->traverse(i);
		temp = pPassenger->GetID();
		cout << temp<< " ";
	}
}
void UI::PrintPriorityQueueofPassenger(PriorityQueue<Passenger*>* p)
{
	p->printpq();
}
void UI::PrintQueueofPassenger(Queue<Passenger*>* p)
{
	p->printq();

}





void UI::PrintStations(Time CurrTime, Station* pStation, int NumberofStations, int index)
{
	cout << "Current time(Hour:Min)==>";
	CurrTime.Print();
	for (int i = 1; i < NumberofStations; i++)
	{
		cout << "\n============== Station #" << index << "=============="<<endl;
		int Forward = pStation[index].GetNormalForwardPassengerList()->count();
		int BackWard = pStation[index].GetNormalBackwardPassengerList()->count();
		int TotalNumber = Forward + BackWard;
		cout << TotalNumber << " " << "Waiting NP: FWD[ ";
		PrintLinkedListofPassenger(pStation[index].GetNormalForwardPassengerList());

		cout<<"]   BCK[ ";
		PrintLinkedListofPassenger(pStation[index].GetNormalBackwardPassengerList());
		cout << "] "<<endl;

		Forward = pStation[index].GetSpecialForwardPassengerList()->getCount();
		BackWard = pStation[index].GetSpecialBackwardPassengerList()->getCount();
		TotalNumber = Forward + BackWard;
		

		cout << TotalNumber << " Waiting SP: FWD[ ";
		PrintPriorityQueueofPassenger(pStation[index].GetSpecialForwardPassengerList());
		cout << "]   BCK[ ";
		PrintPriorityQueueofPassenger(pStation[index].GetSpecialBackwardPassengerList());
		cout << "] \n";

		Forward = pStation[index].GetWheelForwardPassengerList()->getCount();
		BackWard = pStation[index].GetWheelBackwardPassengerList()->getCount();
		TotalNumber = Forward + BackWard;
		cout << TotalNumber <<" " << "Waiting WP: FWD[ ";
		
		PrintQueueofPassenger(pStation[index].GetWheelForwardPassengerList());
		cout << "]   BCK[ ";
		PrintQueueofPassenger(pStation[index].GetWheelBackwardPassengerList());
		cout << "] " << endl;
		Forward = pStation[index].GetForwardBusesinStation()->getCount();
		BackWard = pStation[index].GetBackwardBusesinStation()->getCount();
		TotalNumber = Forward + BackWard; 
		cout << TotalNumber << " " << "Buses at this Station: \n";

		PrintQueueofBus(*pStation[index].GetForwardBusesinStation());
		PrintQueueofBus(*pStation[index].GetBackwardBusesinStation());

		cout <<  "Moving Forward Busses: \n";

		PrintQueueofBus(pCompany->MovingForwardBusses());

		cout << "\nMoving Forward Busses: \n";

		PrintQueueofBus(pCompany->MovingBackwardBusses()); 
		cout << endl;


		cout << "-------------------------------------------------------------------------------------" << endl;
		cout << pCompany->GetFinsihPassengerList()->getCount() << " Finished Passengers:";
		PrintQueueofPassenger(pCompany->GetFinsihPassengerList());
		cout << endl;
		//cout << endl << "Press any key to display next station" << endl;
		index++;
	}
}

void UI::PrintQueueofBus(Queue<Bus*> pBus)
{
	pBus.printq();

}

void UI::PrintAll(Time currTime, Station* ArrayofStations, int NumofStations)
{
	PrintStations(currTime, ArrayofStations, NumofStations, 1);
}

void UI::GetModefromUser()
{
	cin >> Mode;
}
