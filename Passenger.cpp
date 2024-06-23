#include"Passenger.h"


Passenger::Passenger()
{
	ID = 0;
	End_station = -1;
	Start_station = -1;
	GetONorOFF_Time = 0;
	Priority = 0;
	Type = "NULL";


	



	GetONorOFF_Time=0; //in seconds 
	AutoPromotion = 0;
}

Passenger ::~Passenger() {}

void Passenger::SetID(int x)
{
	ID = x;
}
///////////////////////////////////////////////////////////////////////////////////////////
void Passenger::SetArrTime(int hours, int minutes)
{
	Arr_Time.SetTime(hours, minutes);
}
///////////////////////////////////////////////////////////////////////////////////////////
void Passenger::SetMovTime(int hours, int minutes)
{
	Mov_Time.SetTime(hours, minutes);
}
///////////////////////////////////////////////////////////////////////////////////////////
void Passenger::SetWaitTime()
{
	Waiting_Time = Arr_Time - Mov_Time;
}
///////////////////////////////////////////////////////////////////////////////////////////
void Passenger::SetTripTime()
{
	Trip_Time=Finish_Time-Mov_Time;
}
///////////////////////////////////////////////////////////////////////////////////////////
void Passenger::SetFinishTime(int hours, int minutes, int number_of_Passenger_get_off_before_me)
{
	int Time_to_Get_OFF = GetONorOFF_Time * (number_of_Passenger_get_off_before_me + 1);//time taken to get off the bus

	if (Time_to_Get_OFF > 60)
	{
		minutes = minutes + (Time_to_Get_OFF / 60);
	}
	Finish_Time.SetTime(hours, minutes);//set the of finishing the trip which is = time the bus arrive to the station+time taken to left the bus
}
///////////////////////////////////////////////////////////////////////////////////////////

void Passenger::SetType(string Typ)
{
	Type = Typ;


}
///////////////////////////////////////////////////////////////////////////////////////////
void Passenger::SetEndStation(int x)
{
	End_station = x;
}
///////////////////////////////////////////////////////////////////////////////////////////
void Passenger::SetStartStation(int x)
{
	Start_station = x;
}

int Passenger::GetEndStation()
{

	return End_station;
}
void Passenger::SetDirection(int start,int End)
{
	if (start < End)
	{
		Direction = "Forward";
	}
	else
		Direction = "Backward";
}
///////////////////////////////////////////////////////////////////////////////////////////
int Passenger::GetStartStation()
{
	return Start_station;
}
///////////////////////////////////////////////////////////////////////////////////////////
void Passenger::SetGetONorOFF_Time(int Seconds)
{
		GetONorOFF_Time = Seconds;
}
///////////////////////////////////////////////////////////////////////////////////////////
void Passenger::SetMaxWaitTime(int minutes)
{
	MaxWait.SetTime(0,minutes);
}
///////////////////////////////////////////////////////////////////////////////////////////
int Passenger::GetID()
{
	return ID;
}
///////////////////////////////////////////////////////////////////////////////////////////
string Passenger::GetType()
{
	return Type;
}
Time Passenger::GetArrTime()
{
	return Time(Arr_Time.GetHours(), Arr_Time.GetMin());
}
///////////////////////////////////////////////////////////////////////////////////////////
Time Passenger::GetMovTime()
{
	return Time(Mov_Time.GetHours(), Mov_Time.GetMin());
}
///////////////////////////////////////////////////////////////////////////////////////////
Time Passenger::GetWaitTime()
{
	return Time(Waiting_Time.GetHours(), Waiting_Time.GetMin());
}
///////////////////////////////////////////////////////////////////////////////////////////
Time Passenger::GetTripTime()
{
	return Time(Trip_Time.GetHours(), Trip_Time.GetMin());
}
///////////////////////////////////////////////////////////////////////////////////////////
Time Passenger::GetFinishTime()
{
	return Time(Finish_Time.GetHours(), Finish_Time.GetMin());
}

///////////////////////////////////////////////////////////////////////////////////////////
string Passenger::Determine_Destination()
{
	if (Start_station - End_station < 0)
		return "Forward";
	else
		return "Backward";

}//returns Forward or Backward




void Passenger::operator=(Passenger&p)
{
	Type = p.GetType();
	Arr_Time = p.GetArrTime();
	ID = p.GetID();
	Start_station = p.GetStartStation();
	End_station = p.GetEndStation();
}

bool Passenger::operator==(const Passenger* other) const
{
		// Check if the pointer is not nullptr and compare IDs
		return other && this->ID == other->ID;
}


std::ostream& operator<<(ostream& output, Passenger* p)
{
	int temp;
	if (p->GetType() == "SPaged")
	{
		temp = p->GetID();
		output << temp << "(AGED) ";
	}
	else if (p->GetType() == "SPPOD")
	{
		temp = p->GetID();
		output << temp << "(POD) ";
	}
	else if (p->GetType() == "SPpregnent")
	{
		temp = p->GetID();
		output << temp << "(Pregnent) ";
	}
	else
		output << p->GetID() << " ";

	return output;
}


bool Passenger::GetAutoPromotion()
{
	return AutoPromotion;
}

void Passenger::SetAutoPromotion(bool promoted)
{
	AutoPromotion = promoted;
}


int Passenger::GetMaxWaitMinutes()
{
	return MaxWait.GetMin() + MaxWait.GetHours() * 60;
}





