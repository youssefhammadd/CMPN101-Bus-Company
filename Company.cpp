
#include "Company.h"
#include"Event.h"
#include<random>
Company::Company()
{
	ArrayofStations = nullptr;
	EventList = new Queue<Event*>;
	//FinishPassengerList = nullptr;
	pUI = new UI(this);
	NumberofStations = 0;
	Timer.SetTime(4, 0);
	TimeBetween2Stations = 0;
	ON_OFFTime = 0;
}

void Company::SetON_OFFTime(int x)
{
	ON_OFFTime = x;//in seconds
}

int Company::GetON_OFFTime()
{
	return ON_OFFTime;
}

Time Company::GetCurrTime()
{
	return Timer;
}
Queue<Passenger*>* Company::GetFinsihPassengerList()
{
	return &FinishPassengerList;
}

void Company::LoadFile()
{
	pUI->PrintMessagetoUser("Enter file name:");
	string FileName = pUI->GetFileNameFromUser();
	ifstream Filein; // object of class fstream to read from file
	Filein.open( FileName+".txt");//get the file name from the user and add .txt
	pUI->PrintMessagetoUser("Enter Mode(InterActive,Silent):");// ask the user to choose between silent mode or interactive mode
	pUI->GetModefromUser(); 
	int NumofStation, timeBetweentwoStations;//in seconds
	int NumofWBus, NumofMBus;
	int CapacityofWBus, CapacityofMBus;
	int TripstoCheckUp, CheckUpTimeWBus, CheckUpTimeMBus;//in hours
	char EventType;
	int NumofEvents;
	int MaxWait;//in mins
	int Geton_off;//per seconds
	Bus* pBus;
	if (Filein.is_open())//if file is opened
	{

		Filein >> NumofStation >> timeBetweentwoStations;//loading line 1 from the file  :time is in minutes
		Filein >> NumofWBus >> NumofMBus;//loading line 2 from the file 
		Filein >> CapacityofWBus >> CapacityofMBus; //loading line 3 from the file
		Filein >> TripstoCheckUp >> CheckUpTimeWBus >> CheckUpTimeMBus;//loading line 4 from the file 
		Filein >> MaxWait >> Geton_off;//loading line 5 from the file 
		Filein>> NumofEvents;//loading line 6 from the file
		NumberofStations = NumofStation+1; //setting the number of stations i have (+1) because we ignore station 0 in this array
		ArrayofStations = new Station[NumberofStations]; //making an array of stations with the number of stations i have
		TimeBetween2Stations = timeBetweentwoStations;
		
		

		ON_OFFTime = Geton_off;
		



		
		
		//function to set this data to buses
		Queue<Bus*>* pQueueWBus = new Queue<Bus*>();
		Queue<Bus*>* pQueueMBus = new Queue<Bus*>();
		for (int i = 0; i < NumofWBus; i++)//Creating all buses to Load them to station 0
		{
			pBus = new Bus();
			pBus->SetType("WBus");
			pBus->SetBusCapacity(CapacityofWBus);
			pBus->SetCheckUpDuration(CheckUpTimeWBus);
			pBus->setTripsToCheckUp(TripstoCheckUp);
			pBus->SetCurrentStation(0);
			pBus->SetLastStation(NumofStation);
			pBus->SetNextStation(1);
			pBus->SetBusID(i + 1);
			
			pBus->SetON_OFFTime(Geton_off);

			pQueueWBus->enqueue(pBus);
			pBus = nullptr;
		}
		for (int i = 0; i < NumofMBus; i++)//Creating all buses to Load them to station 0
		{
			pBus = new Bus();
			pBus->SetType("MBus");
			pBus->SetBusCapacity(CapacityofMBus);
			pBus->SetCheckUpDuration(CheckUpTimeMBus);
			pBus->setTripsToCheckUp(TripstoCheckUp);
			pBus->SetCurrentStation(0);
			pBus->SetLastStation(NumofStation);
			pBus->SetBusID(NumofWBus + i + 1);
			pBus->SetNextStation(1);
			
			pBus->SetON_OFFTime(Geton_off);


			pQueueMBus->enqueue(pBus);
			pBus = nullptr;
		}
		int getMaxType;
		if (NumofMBus >= NumofWBus)
			getMaxType = NumofMBus;
		else
			getMaxType = NumofWBus;

		for (int i = 0; i < getMaxType; i++)//Creating all buses and Loaded them to station 0 in station zero list not in the array 
		{
			if (pQueueMBus->dequeue(pBus))
				StationZeroBuses.enqueue(pBus);


			if (pQueueWBus->dequeue(pBus))
				StationZeroBuses.enqueue(pBus);
			pBus = nullptr;
		}
		delete pQueueMBus;
		delete pQueueWBus;
		pQueueMBus = nullptr;
		pQueueWBus = nullptr;


		
		//function to set all the events
	
		//line 6

		Event* pEvent;

		for (int i = 0; i < NumofEvents; i++)
		{
			Filein >> EventType;

			if (EventType == 'A')
			{
				int id, startstation, endstation, hours, minutes;
				string PassengerType, ExtraType;
				char colon;
				Filein >> PassengerType;
				if (PassengerType == "SP")
				{
					Filein >> hours >> colon >> minutes >> id >> startstation >> endstation >> ExtraType;
				}
				else
				{
					Filein >> hours >> colon >> minutes >> id >> startstation >> endstation;
					ExtraType = "NULL";
				}
				pEvent = new ArrivalEvent(EventType, PassengerType, ExtraType, hours, minutes, id, startstation, endstation, Geton_off);
				EventList->enqueue(pEvent);
				pEvent = nullptr;
			}
			else if (EventType == 'L') {
				int id, StartStation, hours, minutes;
				char colon;
				Filein >> hours >> colon >> minutes >> id >> StartStation;
				pEvent = new LeaveEvent(EventType, hours, minutes, id, StartStation);


				EventList->enqueue(pEvent);
				pEvent = nullptr;
			}
		}
	}
	else
	{
		pUI->PrintMessagetoUser("File doesn't exist or can't be opened");
		return;
	}

}

void Company::AddPassengertoStationList(Passenger* p)//add created passenger to his start station  used by arrival event class
{
	ArrayofStations[p->GetStartStation()].ArrivingPassenger(p);
}

void Company::AddFinishedPassenger(Passenger* p)//passenger arrived to his end station or leaved the station
{ 
	
	FinishPassengerList.enqueue(p);
	
}

Passenger* Company::LeavePassengerEvent(int ID, int StationNumber)//this function is used by leaveEvent to remove a passenger from his start station
{
	Passenger PassengertobeFound;
	PassengertobeFound.SetID(ID);
	Passenger* PassengerFound = FindPassengerinLinkedList(*ArrayofStations[StationNumber].GetNormalForwardPassengerList(), &PassengertobeFound);//find if passenger is in the forwardList 
	if (PassengerFound == nullptr) //if the passenger isn't in the forward
		PassengerFound = FindPassengerinLinkedList(*ArrayofStations[StationNumber].GetNormalBackwardPassengerList(), &PassengertobeFound);//then look if he is found in the backward
	if (PassengerFound !=nullptr)
	{
		PassengerFound = ArrayofStations[StationNumber].RemovePassengerfromStation(PassengerFound);//to remove the passenger from the station list
		AddFinishedPassenger(PassengerFound);//put him in the finish list
		return PassengerFound;
	}

	return nullptr;
}




bool Company::notEndOfSimulation() {
	return	!EventList->isEmpty();
}
bool Company::inWorkingHours(Time currTime)
{
	return currTime.GetHours() <= 22 && currTime.GetHours() >= 4;
}
bool Company::executeCurrEvents(Time currTime) {

	if (!inWorkingHours(currTime) && !EventList->isEmpty()) return false;

	Event* frontEvent;
	while (EventList->peekFront(frontEvent) && currTime >= frontEvent->getEventTime()) {//&& currTime >= frontEvent->getEventTime() must be added just for debugging
		EventList->dequeue(frontEvent);

		if (!(frontEvent->getEventTime() == currTime))
			frontEvent->setEventTime(currTime);

		frontEvent->Execute(this);
		delete frontEvent;
		frontEvent = nullptr;
	}
	return true;
}

//bool Company::ExecuteAll(Time currTime)
//{
//	if (!inWorkingHours(currTime) && EventList->isEmpty()) return false;
//
//	executeCurrEvents(currTime);
//	Bus* pBus;
//	int check=0;
//	
//	
//	if (MovingForwardBus.peekFront(pBus) && currTime >= pBus->GetArriveTime())
//	{
//			
//			
//			ArrivingBustoStation(currTime);  
//			DropOffPassenger(currTime); 
//			BoardingPassengers(currTime); 
//			LeavingBusFromStation(currTime); 
//			check++; 
//	}
//	
//
//
//
//	if (MovingBackwardBus.peekFront(pBus) && currTime >= pBus->GetArriveTime()) 
//	{
//		ArrivingBustoStation(currTime); 
//		DropOffPassenger(currTime); 
//		BoardingPassengers(currTime); 
//		LeavingBusFromStation(currTime); 
//		check++; 
//	}
//	return true;
//}


void Company::Simulate()
 {
	LoadFile();
	Bus* pBus=nullptr;
	
	while (!EventList->isEmpty() || inWorkingHours(Timer))
	{
		MovingBusesfromStation0(Timer);
		if (executeCurrEvents(Timer)) 
		{

			ArrivingBustoStation(Timer);
			
				DropOffPassenger(Timer);
				BoardingPassengers(Timer);
				pUI->PrintAll(Timer, ArrayofStations, NumberofStations);
				LeavingBusFromStation(Timer);
			
		}
		cin.get();//clicking enter to continue
		//pUI->PrintAny("Press any key to display next station\n");
		Timer.IncrementTime();

	}

}
bool Company::FindPassengerinQueue(Queue<Passenger*> PassengerList, Passenger* p)
{
	if(PassengerList.isEmpty())
	return false;
	Passenger* Passenger;
	while(PassengerList.dequeue(Passenger))
	{
		if (Passenger->GetID() == p->GetID())
		{
			return true;
		}
	}
	return false;
}
Passenger* Company::FindPassengerinLinkedList(LinkedList<Passenger*> PassengerList, Passenger* p)//finding the passenger in the waiting list of the station
{
	if(!PassengerList.count())//if the list is empty return null
	return nullptr;

	Passenger* Passenger;
	while (PassengerList.count())
	{
		Passenger = PassengerList.DeleteFirst();//checking if the passenger is in the list
		if (Passenger->GetID() == p->GetID())
			return Passenger;
	}
	return nullptr;
}

void Company::MovingBusesfromStation0(Time CurrTime)//moving all buses from station zero 1 by 1 every 15 minutes  
{
	Bus *pBus;
	if (!StationZeroBuses.isEmpty() && CurrTime.GetMin() % 2 == 0)//every 15 minutes 1 bus is out from station zero
	{
		if (StationZeroBuses.dequeue(pBus)) {
			pBus->SetNextStation(1);
			pBus->SetLeaveTime(Timer.GetHours(), Timer.GetMin());
			pBus->SetArriveTime(Timer.GetHours(), Timer.GetMin() + TimeBetween2Stations);
			MovingForwardBus.enqueue(pBus);
		}
	}
}

void Company::ArrivingBustoStation(Time CurrTime)//arriving bus to a certain station at specific time
{                                                  //setting all the buses in the forward and the backward to their arrival station if their arrival time has came 
	Bus* pBus=nullptr;

		while(MovingForwardBus.peekFront(pBus) && CurrTime >= pBus->GetArriveTime())//check whether there is a bus in the moving forward bus list or not and if it's time to enter a certain station
		{
				if (MovingForwardBus.dequeue(pBus))//remove this bus from the moving list to his arrivial station and check if the bus is removed successfully
				{
					pBus->SettingBusStations();       //setting the current and next station of the bus
					ArrayofStations[pBus->GetCurrentStation()].ArrivingBus(pBus);//add this bus to the queue of waiting buses in this station
					
					
				}
		}

		while(MovingBackwardBus.peekFront(pBus) && CurrTime == pBus->GetArriveTime())
		{
			
				if (MovingBackwardBus.dequeue(pBus))
				{
					ArrayofStations[pBus->GetNextStation()].ArrivingBus(pBus);//add this bus to the queue of waiting buses in this station
					pBus->SettingBusStations();      //setting the new current and new next station of the bus
					
				}
		}
	

}


bool Company::BoardingPassengers(Time CurrTime)//a sub-function to Board Passengers and set only leave time of the bus
{
	int TimeTakenToBoardBus=0;
	bool Check=false;
	Bus* pBus=nullptr;
	Queue<Bus*> TempforwardBuses, TempBackwardBuses; 
	for (int i = 1; i < NumberofStations; i++)
	{
		if (ArrayofStations[i].GetForwardBusesinStation()->dequeue(pBus) )//&& CurrTime >= pBus->GetArriveTime()
		{
			Check = ArrayofStations[pBus->GetCurrentStation()].BoardingPassengers(pBus, TimeTakenToBoardBus); 
			pBus->SetLeaveTime(pBus->GetArriveTime().GetHours(), pBus->GetArriveTime().GetMin() + TimeTakenToBoardBus);
			TempforwardBuses.enqueue(pBus);
		}
		while (TempforwardBuses.dequeue(pBus)) 
			ArrayofStations[i].GetForwardBusesinStation()->enqueue(pBus); 

		while (ArrayofStations[i].GetBackwardBusesinStation()->peekFront(pBus) ) //&& CurrTime >= pBus->GetArriveTime()
		{
			Check = ArrayofStations[pBus->GetCurrentStation()].BoardingPassengers(pBus, TimeTakenToBoardBus);
			pBus->SetLeaveTime(pBus->GetArriveTime().GetHours(), pBus->GetArriveTime().GetMin() + TimeTakenToBoardBus);
		}

		while (TempBackwardBuses.dequeue(pBus)) 
			ArrayofStations[i].GetBackwardBusesinStation()->enqueue(pBus); 


	}
	return true;
}

void Company::DropOffPassenger(Time CurrTime)//a function that takes a bus and let the passengers who arrived to there stations to get off the bus
{                                            //setting the finish time of the passengers and put them in the finish list
	                                           //set the arrival time of the the bus with the time after the passenger getoff the bus because this function be called first


		Passenger* p=nullptr;
		int count = 1;
		int Checker=0;
		Bus* pBus;
		Queue<Bus*> TempforwardBuses,TempBackwardBuses;
		for (int i = 1; i < NumberofStations; i++)
		{
			count = 1;
			while (ArrayofStations[i].GetForwardBusesinStation()->dequeue(pBus) ) //getting the forward waiting bus in the station
			{

				p = pBus->PassengerDropOff(i);
				if (p != nullptr)
				{
					p->SetFinishTime(pBus->GetArriveTime().GetHours(), pBus->GetArriveTime().GetMin(), count);
					FinishPassengerList.enqueue(p);
					count++;
					
				}
				TempforwardBuses.enqueue(pBus); 
				
			}
			while (TempforwardBuses.dequeue(pBus))
				ArrayofStations[i].GetForwardBusesinStation()->enqueue(pBus);

			if (count > 1)
			{
				pBus->SetArriveTime(pBus->GetArriveTime().GetHours(), pBus->GetArriveTime().GetMin() + count * ON_OFFTime);//calculating time and put it in the arrival time of the bus to follow up in boarding function
				Checker++;
			}

			count = 1;
			while (ArrayofStations[i].GetBackwardBusesinStation()->dequeue(pBus) && CurrTime >= pBus->GetArriveTime()) //getting the backward waiting bus in the station
			{
				p = pBus->PassengerDropOff(i); 
				if (p != nullptr)
				{
					p->SetFinishTime(pBus->GetArriveTime().GetHours(), pBus->GetArriveTime().GetMin(), count); 
					FinishPassengerList.enqueue(p); 
					count++;
					
				}
				TempBackwardBuses.enqueue(pBus);
			}
			while (TempBackwardBuses.dequeue(pBus)) 
				ArrayofStations[i].GetBackwardBusesinStation()->enqueue(pBus); 


			if (count > 1)
			{
				pBus->SetArriveTime(pBus->GetArriveTime().GetHours(), pBus->GetArriveTime().GetMin() + count * ON_OFFTime);//calculating time and put it in the arrival time of the bus to follow up in boarding function
				Checker++;
			}
		}
		//this is called before boardingPassengers

}

void Company::LeavingBusFromStation(Time CurrTime) 
{
	
	bool Check;
	Bus* pBus;
	for (int i = 0; i < NumberofStations; i++)
	{
		while (ArrayofStations[i].GetForwardBusesinStation()->peekFront(pBus) && CurrTime >= pBus->GetLeaveTime())
		{  //check whether if there is bus in the forward waiting buses list in each station or not
			
			//get the bus in the front of the forward waiting buses list in each station and check whether if the time to leave has reached or not
            //if it's the time to bus to move and in the accurate station

				ArrayofStations[i].GetForwardBusesinStation()->dequeue(pBus); 
				 // remove them from the station 
				pBus->SetArriveTime(pBus->GetLeaveTime().GetHours(), pBus->GetLeaveTime().GetMin() + TimeBetween2Stations); //set their arrival time to the next station
				if (pBus->GetDirection() == "Forward")
					MovingForwardBus.enqueue(pBus);//put them back into the moving buses list in his direction
				else
					MovingBackwardBus.enqueue(pBus);//if the bus has arrived to the last station then put him in the moving backward busses
			
		}
		while (ArrayofStations[i].GetBackwardBusesinStation()->peekFront(pBus) && CurrTime >= pBus->GetLeaveTime()) //same for the waiting backward buses in the station 
		{
			
				ArrayofStations[i].GetBackwardBusesinStation()->dequeue(pBus);
				pBus->SetArriveTime(pBus->GetLeaveTime().GetHours(), pBus->GetLeaveTime().GetMin() + TimeBetween2Stations);
				if (pBus->GetDirection() == "Backward")//which moving list the bus will join
					MovingBackwardBus.enqueue(pBus);
				else
					MovingForwardBus.enqueue(pBus);
			
		}

	}

}



Queue<Bus*> Company::MovingForwardBusses()
{

	return MovingForwardBus;
}

Queue<Bus*> Company::MovingBackwardBusses()
{
	return MovingBackwardBus;
}

Company::~Company()
{
	delete[] ArrayofStations;
	delete EventList;
	Passenger* pPassenger;
	while (FinishPassengerList.dequeue(pPassenger))
	{
		delete pPassenger;
	}
	Bus* pBus;
	while (StationZeroBuses.dequeue(pBus))
	{
		delete pBus;
	}
}




void Company::AutoPromotePassengers(Time CurrTime)
{
	for (int i = 1; i < NumberofStations; ++i)
	{
		ArrayofStations[i].AutoPromotePassengers(CurrTime);
	}
}




//void Company::OutputSimulationResult(ostream& out) //h takes the output stream of the file
//{
//	Passenger* h;
//	out << left;
//	out.width(10);
//	out << "FT";
//	out.width(10);
//	out << "ID";;
//	out.width(10);
//	out << "AT";
//	out.width(10);
//	out << "WT";
//	out.width(10);
//	out << "TT" << endl;
//
//	Time t;
//	int c = FinishPassengerList.getCount();
//	int twt = 0;
//	int ttt = 0;
//	int pp = 0;
//	int np = 0;
//	int wp = 0;
//
//	while (FinishPassengerList.dequeue(h)) {
//		out.width(10);
//		t = h->GetFinishTime();
//		out << &t;//get crashed !!temprory object send by refrence
//		out.width(10);
//		out << h->GetID();
//		out.width(10);
//		t = h->GetArrTime();
//		out << &t;
//		out.width(10);
//		t = h->GetWaitTime();
//		out << &t;
//		out.width(10);
//		t = h->GetTripTime();
//		out << &t;
//
//		twt += h->GetWaitTime().GetTotalMinutes();
//		ttt += h->GetTripTime().GetTotalMinutes();
//		if (h->GetAutoPromotion())
//			pp++;
//		if (h->GetType() == "NP" || h->GetAutoPromotion())
//			np++;
//		else if (h->GetType() == "WP")
//			wp++;
//	}
//
//	int awt = twt / c;
//	int att = ttt / c;
//	int ppp = pp * 100 / c;
//	Time awT = Time(awt / 60, awt % 60);
//	Time atT = Time(att / 60, att % 60);
//	int sp = c - np - wp;
//
//	out << "passengers: " << c << "   [NP: " << np << ", SP: " << sp << ", WP: " << wp << "]" << endl;
//	out << "passenger Avg Wait time= " << &awT << endl;
//	out << "passenger Avg trip time= " << &atT << endl;
//	out << "Auto-promoted passengers: " << ppp << "%" << endl;
//
//	Bus* pBus;
//	int bc = AllBuses.count();
//	int wb = 0;
//	int mb = 0;
//	int tbt = 0;
//	int tu = 0;
//
//	while (pBus = AllBuses.DeleteFirst())
//	{
//		if (pBus->getType() == "MBus")
//			mb++;
//		else if (pBus->getType() == "WBus")
//			wb++;
//
//		tbt += pBus->GetBusBusyTime().GetTotalMinutes();
//		tu += pBus->CalculateBusUtilization();
//	}
//
//	int abt = tbt / c;
//	Time abT = Time(abt / 60, abt % 60);
//
//	out << "buses: " << c << "   [WBus: " << wb << ", MBus: " << mb << "]" << endl;
//	out << "Avg Busy time = " << &abT << endl; // TODO need to print in percentages
//	out << "Avg utilization = " << (tu / c) << "%" << endl;
//}
//
//void Company::MovingBusesfromCheckup(Time CurrTime) // H
//{
//	Bus* pBus;
//	while (CheckupMBusList.peekFront(pBus) && CurrTime == pBus->GetArriveTime())
//	{
//		if (CheckupMBusList.dequeue(pBus))
//		{
//			pBus->resetTripsToCheckUp();
//			StationZeroBuses.enqueue(pBus);
//		}
//	}
//
//	while (CheckupWBusList.peekFront(pBus) && CurrTime == pBus->GetArriveTime())
//	{
//		if (CheckupWBusList.dequeue(pBus))
//		{
//			pBus->resetTripsToCheckUp();
//			StationZeroBuses.enqueue(pBus);
//		}
//	}
//}


