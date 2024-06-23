#include"Bus.h"



Bus::Bus()
{
	CurrentStation = 0;
	J = 0;
	NextStation = 1;
	Direction= "Forward";
	ID = 0;
}

void Bus::SetBusID(int x)
{
	ID = x;
}

int Bus::GetBusID()
{
	return ID;
}

void Bus::SetON_OFFTime(int x)
{
	GETON_OFFTime = x;
}

int Bus::GetON_OFFTime()
{
	return GETON_OFFTime;
}

void Bus::SetArriveTime(int Hour, int Minute)
{
	ArriveTime.SetTime(Hour, Minute);
}

Time Bus::GetArriveTime()
{

	return ArriveTime;
}

void Bus::SetLeaveTime(int Hour, int Minute)
{
	LeaveTime.SetTime(Hour, Minute);
}

Time Bus::GetLeaveTime()
{
	return LeaveTime;
}

void Bus::SetBusCapacity(int BC)
{
	if (BC > 0)
		Bus_Capacity = BC;
}

void Bus::SetLastStation(int L)//Station S and after that bus became backward
{
	LastStation = L;
}

int Bus::GetBusCapacity()
{
	return Bus_Capacity;
}

bool Bus::isfull()
{
	return (Bus_Size == Bus_Capacity);
}

void Bus::setTripsToCheckUp(int x)
{
	if (x >= 0)
		J = x;
}

int Bus::getTripsToCheckUp()
{
	return J;
}

void Bus::SetTimeBetweenTwoStations(int Time)
{
	if (Time < 0)
		TimeBetweenTwoStations = 10;//make it by default 10 mins if the time sended was wrong
	else
		TimeBetweenTwoStations = Time;
}

int Bus::GetTimeBetweenTwoStations()
{

	return TimeBetweenTwoStations;
}

PriorityQueue<Passenger*>* Bus::GetPassengerListInsideBus()
{
	return &PassengerList;
}

bool Bus::BusIsBusy() {
	if (Bus_Size > 0)
	{
		return true;
	}
	return false;
}

void Bus::SetType(string type) {
	if (type == "WBus" || type == "MBus")
	{
		Type = type;
	}
}

void Bus::SetBusSpeed(int x)
{
	if (x > 0)
		BusSpeed = x;
}

int Bus::GetBusSpeed()
{
	return BusSpeed;
}

void Bus::SetCheckUpDuration(float x)
{
	if (x > 0)
		CheckupDuration = x;
}

float Bus::GetCheckUpDuration()
{
	return CheckupDuration;
}

string Bus::getType()
{
	return Type;
}

void Bus::SetCurrentStation(int CS) {
	if (CS > 0)
		CurrentStation = CS;
}

void Bus::SettingBusStations()
{
	if (Direction == "Forward" && LastStation != CurrentStation)
	{
		CurrentStation++;
		NextStation++;
	}
	else if (Direction == "Forward" && LastStation == CurrentStation) //bus has arrived to the last station
	{
		CurrentStation++;// the current station is now the last station
		NextStation=NextStation-2;//bus start to move backward
		Direction = "Backward";
		J++;//bus make a complete trip
	}
	else if (Direction == "Backward" && NextStation != 0)
	{
		CurrentStation--;
		NextStation--;
	}
	else if (Direction == "Backward" && CurrentStation == 1) //bus has arrived to the start station
	{
		CurrentStation--;//now the current station will be equal to 1
		NextStation=NextStation+2;//next station be be equal to 2
		Direction = "Forward"; //change his direction
		J++;//bus make a complete trip
	}
}
string Bus::GetDirection()
{
	return Direction;
}

void Bus::SetNextStation(int NS) {
	if (NS > 0)
		NextStation = NS;
}

//bool Bus::PassengerGetOn(Passenger* p) {
//
//	if (Bus_Size < Bus_Capacity && p )
//	{
//		int hcurrent = currentTime.GetHours();
//		int mincurrent = currentTime.GetMin();
//		float currentTime = hcurrent + (float)mincurrent / 60;
//
//		int hcheckstart = CheckupStart.GetHours();
//		int mincheckstart = CheckupStart.GetMin();
//		float checkStartTime = hcheckstart + (float)mincheckstart / 60;
//
//		int hcheckend = CheckupEnd.GetHours();
//		int mincheckend = CheckupEnd.GetMin();
//		float checkEndTime = hcheckend + (float)mincheckend / 60;
//
//		if ((hcurrent >= startingHours) && (hcurrent < endingHours))
//		{
//			if (!(currentTime >= checkStartTime && currentTime < checkEndTime))
//			{
//				PassengerList.enqueue(p,p->GetEndStation());
//				Bus_Size++;
//				return 1;
//			}
//		}
//	}
//	return 0;
//}//send to the function Pointer of passenger Node to link it to the list


bool Bus::PassengerGetOn(Passenger* p)
{
	if (p)
	{
		PassengerList.enqueue(p, p->GetEndStation());
		Bus_Size++;
		return 1;
	}
	else
		return 0;

}

Passenger* Bus::PassengerDropOff(int index) {
	Passenger* p=nullptr;
	 
	if (PassengerList.peek(p)) 
	{
		//function GetThePriority() return the priority of the fornt element in the list
		if (index == p->GetEndStation())//checking if this station is his arrival station  by making the priority of the passenger is his endstation
		{
			PassengerList.dequeue(p);
			Bus_Size--;
			TotalTransportedPassenger++;
			return p;
		}
	}
	return nullptr;
}

float Bus::revertToHours(Time t)
{
	int h = t.GetHours();
	int m = t.GetMin();
	return (h + (float)m / 60);
}

void Bus::CalculateBusUtilization() {
	if (!(TotalTrips))
		BusUtilization = 0;
	else
		BusUtilization = TotalTransportedPassenger / (TotalTrips * Bus_Capacity) * (revertToHours(BusBusyTime)) * (revertToHours(TotalSimulationTime));
	BusUtilization *= 100;
}

int Bus::GetBusUtilizatiion()
{
	return BusUtilization;
}

int Bus::GetCurrentStation()
{
	return CurrentStation;
}

int Bus::GetNextStation()
{
	return NextStation;
}
std::ostream& operator<<(ostream& output, Bus* pBus)
{
	if (pBus->getType() == "MBus"&&pBus->GetDirection()=="Forward")
	{
		output << "B" << pBus->GetBusID() << "[" << "FWD , MBus ," << pBus->GetBusCapacity() << "]  "<<"{";

		
	}
	else if (pBus->getType() == "MBus" && pBus->GetDirection() == "Backward")
	{
		output << "B" << pBus->GetBusID() << "[" << "BCK , MBus ," << pBus->GetBusCapacity() << "]  " << "{";
		
	}
	else if (pBus->getType() == "WBus" && pBus->GetDirection() == "Forward")
	{
		output << "B" << pBus->GetBusID() << "[" << "FWD , WBus ," << pBus->GetBusCapacity() << "]  " << "{";
		
	}
	else if (pBus->getType() == "WBus" && pBus->GetDirection() == "Backward")
	{
		output << "B" << pBus->GetBusID() << "[" << "BCK , WBus ," << pBus->GetBusCapacity() << "]  " << "{";
		
	}
	pBus->PassengerList.printpq();
	output << "}"<<endl;
	return output;
}


Bus::~Bus() {}
