#include "Station.h"



Station::Station()
{
	TotalNumberOfStations = 0;
	
}

bool Station::FindingPassenger(Passenger* p)
{
	if (ForwardWaitingNormalPassenger.Find(p) || BackwardWaitingNormalPassenger.Find(p))
	{
		return true;
	}
	else
		return false;
}
//Passenger* Station::GetRandomPassenger(int Num)
//{
//	Passenger* p;
//	if (Num >= 1 && Num <= 25)
//	{
//		if (ForwardSpecialPassenger.dequeue(p))
//		{
//			return p;
//		}
//		else if (BackwardSpecialPassenger.dequeue(p))
//		{
//			return p;
//		}
//	}
//	if (Num >= 35 && Num <= 45)
//	{
//		if (ForwardWheelPassenger.dequeue(p))
//		{
//			return p;
//		}
//		else if (BackwardWheelPassenger.dequeue(p))
//		{
//			return p;
//		}
//	}
//	if (Num >= 50 && Num <= 60)
//	{
//		if (ForwardNormalPassenger.count())
//		{
//			p = ForwardNormalPassenger.DeleteFirst();
//			return p;
//		}
//		else if (BackwardNormalPassenger.count())
//		{
//			p = BackwardNormalPassenger.DeleteFirst();
//			return p;
//		}
//	}
//	return nullptr;
//}
Passenger* Station::RemovePassengerfromStation(Passenger* p)
{

		if (ForwardWaitingNormalPassenger.Deleteitem(p))
			return p;
		if (BackwardWaitingNormalPassenger.Deleteitem(p))
			return p;
	else
		return nullptr;
}


void Station::SetTotalNumberOfStations(int s)
{
	if (s > 0)
		TotalNumberOfStations = s;
}


int Station::GetTotalNumberOfStations()
{
	return TotalNumberOfStations;
}

void Station::SetTimeBetweenStations(Time t)
{
	TimeBetweenStations = t;
}

Time Station::GetTimeBetweenStations()
{
	return TimeBetweenStations;
}

bool Station::ArrivingPassenger(Passenger* p)
{
	if (p->GetType() == "NP" && p->Determine_Destination() == "Forward") {
		ForwardWaitingNormalPassenger.InsertEnd(p);
	}
	else if (p->GetType() == "NP" && p->Determine_Destination() == "Backward") {
		BackwardWaitingNormalPassenger.InsertEnd(p);
	}
	else if (p->GetType() == "WP" && p->Determine_Destination() == "Backward") {
		BackwardWaitingWheelPassenger.enqueue(p);
	}
	else if (p->GetType() == "WP" && p->Determine_Destination() == "Forward") {
		ForwardWaitingWheelPassenger.enqueue(p);
	}
	else if (p->GetType() == "SPaged" && p->Determine_Destination() == "Forward") {
		ForwardWaitingSpecialPassenger.enqueue(p, 1);
	}
	else if (p->GetType() == "SPPOD" && p->Determine_Destination() == "Forward") {
		ForwardWaitingSpecialPassenger.enqueue(p, 2);
	}
	else if (p->GetType() == "SPpregnent" && p->Determine_Destination() == "Forward") {
		ForwardWaitingSpecialPassenger.enqueue(p, 3);
	}
	else if (p->GetType() == "SPaged" && p->Determine_Destination() == "Backward") {
		BackwardWaitingSpecialPassenger.enqueue(p, 1);
	}
	else if (p->GetType() == "SPPOD" && p->Determine_Destination() == "Backward") {
		BackwardWaitingSpecialPassenger.enqueue(p, 2);
	}
	else if (p->GetType() == "SPpregnent" && p->Determine_Destination() == "Backward") {
		BackwardWaitingSpecialPassenger.enqueue(p, 3);
	}
	else
	{
		return 0;
	}
	return 1;
}
Passenger* Station::LeavingStationEvent(Passenger* p)//before Going on the bus
{
	if (p->GetType() == "NP" && p->Determine_Destination() == "Forward") {
		
		if (ForwardWaitingNormalPassenger.Deleteitem(p))
			return p;
	}
	else if (p->GetType() == "NP" && p->Determine_Destination() == "Backward")
	{
		if (BackwardWaitingNormalPassenger.Deleteitem(p))
			return p;
	}
	else
		return nullptr;
	
}

bool Station::BoardingPassengers(Bus* B,int& TimetoBoardPassengers)// a function that takes a bus to load the passengers waiting in the station
{
	
	int BoardingTime ,CountofPassengerGetonTheBus=0;
	//this part is for boarding on the passengers
	if (B->isfull())
		return 0;
	Passenger* P=nullptr;
	if (B->getType() == "MBus" && B->GetDirection() == "Forward")//if the bus was MBus and forward then board the waiting passengers from the forward waiting list
	{                                                            
		while (!B->isfull() && ForwardWaitingSpecialPassenger.peek(P) )//load first the special passengers 
		{
			ForwardWaitingSpecialPassenger.dequeue(P); 
			CountofPassengerGetonTheBus++;
			P->SetMovTime(B->GetArriveTime().GetHours(), B->GetArriveTime().GetMin() + (CountofPassengerGetonTheBus * B->GetON_OFFTime())/60); 
			B->PassengerGetOn(P);
			P = nullptr;

		}
		while (!B->isfull() && ForwardWaitingNormalPassenger.count())//after finishing the special passenger start loading the normal passengers
		{
			CountofPassengerGetonTheBus++;
			P = ForwardWaitingNormalPassenger.DeleteFirst();
			P->SetMovTime(B->GetArriveTime().GetHours(), B->GetArriveTime().GetMin() + (CountofPassengerGetonTheBus * B->GetON_OFFTime())/60); 
			B->PassengerGetOn(P);
			P = nullptr;
			
		}

	}
	else if (B->getType() == "MBus" && B->GetDirection() == "BackWard") // if the bus was MBus and backward then board the waiting passengers from the forward waiting list
	{
		while (BackwardWaitingSpecialPassenger.peek(P) && !B->isfull())//load first the special passengers
		{
			BackwardWaitingSpecialPassenger.dequeue(P);
			CountofPassengerGetonTheBus++; 
			P->SetMovTime(B->GetArriveTime().GetHours(), B->GetArriveTime().GetMin() + (CountofPassengerGetonTheBus * B->GetON_OFFTime())/60);  
			B->PassengerGetOn(P);
			P = nullptr;
			
		}
		while (!B->isfull() && BackwardWaitingNormalPassenger.count())//after finishing the special passenger start loading the normal passengers
		{
			CountofPassengerGetonTheBus++; 
			P = BackwardWaitingNormalPassenger.DeleteFirst();
			P->SetMovTime(B->GetArriveTime().GetHours(), B->GetArriveTime().GetMin() + (CountofPassengerGetonTheBus * B->GetON_OFFTime())/60); 
			B->PassengerGetOn(P); 
			P = nullptr;
		} 
	
	}
	else if (B->getType() == "WBus" && B->GetDirection() == "Forward")// if the bus was WBus and forward then board the waiting passengers from the forward waiting list
	{
		while (ForwardWaitingWheelPassenger.peekFront(P) && !B->isfull())//load the wheel chair passengers
		{
			ForwardWaitingWheelPassenger.dequeue(P);
			CountofPassengerGetonTheBus++; 
			P->SetMovTime(B->GetArriveTime().GetHours(), B->GetArriveTime().GetMin() + (CountofPassengerGetonTheBus * B->GetON_OFFTime())/60);
			B->PassengerGetOn(P);
			P = nullptr;
		}
	}
	else if (B->getType() == "WBus" && B->GetDirection() == "BackWard")// if the bus was WBus and backward then board the waiting passengers from the forward waiting list
	{
		while (BackwardWaitingWheelPassenger.peekFront(P) && !B->isfull())//load the wheel chair passengers
		{
			BackwardWaitingWheelPassenger.dequeue(P);
			CountofPassengerGetonTheBus++; 
			P->SetMovTime(B->GetArriveTime().GetHours(), B->GetArriveTime().GetMin() + (CountofPassengerGetonTheBus * B->GetON_OFFTime())/60);
			B->PassengerGetOn(P);
		}
	}
	BoardingTime = CountofPassengerGetonTheBus*B->GetON_OFFTime();
	if (BoardingTime >= 60)
	{
		TimetoBoardPassengers = BoardingTime / 60;//if time in seconds is more than minute convert it into minutes
	}
	return 1;
}
//bool Station::DropOffPassenger(Bus* pBus,int& TimeTaken)
//{
//	int BoardingTime, CountofPassengerGetoffTherBus = 0;
//	Passenger* p;
//	if (pBus->GetDirection() == "Forward" && pBus->GetPassengerListInsideBus()->peek(p))
//	{
//		
//	}
//
//}
bool Station::ArrivingBus(Bus* B)
{
	if (B->GetDirection() == "Forward")
	{
		ForwardWaitingBus.enqueue(B);
		return 1;
	}
	else if (B->GetDirection() == "Backward")
	{
		BackwardWaitingBus.enqueue(B);
		return 1;
	}
	return 0;
}
Bus* Station::LeavingBus(Bus* B)
{
	if (B->GetDirection() == "Forward")
	{
		ForwardWaitingBus.dequeue(B);
		return B;
	}
	else if (B->GetDirection() == "Backward")
	{
		BackwardWaitingBus.dequeue(B);
		return B;
	}
	return nullptr;

}

/*/Passenger* Station::FindPassengerinStation(int id)
{


}*/
LinkedList<Passenger*>* Station::GetNormalForwardPassengerList()
{

		return &ForwardWaitingNormalPassenger;

}

LinkedList<Passenger*>* Station::GetNormalBackwardPassengerList()
{
	return &BackwardWaitingNormalPassenger;
}


PriorityQueue<Passenger*>* Station::GetSpecialForwardPassengerList()
{
	return &ForwardWaitingSpecialPassenger;
}
PriorityQueue<Passenger*>* Station::GetSpecialBackwardPassengerList()
{
	return &BackwardWaitingSpecialPassenger;
}
Queue<Passenger*>* Station::GetWheelForwardPassengerList()
{
	return &ForwardWaitingWheelPassenger;
}
Queue<Passenger*>* Station::GetWheelBackwardPassengerList()
{
	return &BackwardWaitingWheelPassenger;
}

Queue<Bus*>* Station::GetForwardBusesinStation()
{
	return &ForwardWaitingBus;
}
Queue<Bus*>* Station::GetBackwardBusesinStation()
{
	return &BackwardWaitingBus;
}





void Station::AutoPromotePassengers(Time CurrTime)//h
{
	Passenger* pPassenger;
	for (int i = 0; i < ForwardWaitingNormalPassenger.count(); ++i)
	{
		pPassenger = ForwardWaitingNormalPassenger.traverse(i);
		if (CurrTime >= Time(pPassenger->GetArrTime().GetHours(), pPassenger->GetArrTime().GetMin() + pPassenger->GetMaxWaitMinutes()))
		{
			ForwardWaitingNormalPassenger.Deleteitem(pPassenger);
			--i;
			pPassenger->SetAutoPromotion(true);
			pPassenger->SetType("SPaged");
			ForwardWaitingSpecialPassenger.enqueue(pPassenger, 1);
		}
	}

	for (int i = 0; i < BackwardWaitingNormalPassenger.count(); ++i)
	{
		pPassenger = BackwardWaitingNormalPassenger.traverse(i);
		if (CurrTime >= Time(pPassenger->GetArrTime().GetHours(), pPassenger->GetArrTime().GetMin() + pPassenger->GetMaxWaitMinutes()))
		{
			BackwardWaitingNormalPassenger.Deleteitem(pPassenger);
			--i;
			pPassenger->SetAutoPromotion(true);
			pPassenger->SetType("SPaged");
			BackwardWaitingSpecialPassenger.enqueue(pPassenger, 1);
		}
	}
}


Station::~Station()
{
}
