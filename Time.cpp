#include "Time.h"


Time::Time(int Hours, int Minutes)
{
	SetTime(Hours, Minutes);
}
void Time::SetTime(int Hour, int Min)
{
	if (Hour < 0 || Hour>24)
		HH = 0;
	if (Min < 0)
		MM = 0;

	if (Min >= 60 )
	{
		HH = Hour+1;
		Hour = HH;
		MM = Min - 60;
		Min = MM;
	}
	if ((Min >= 0 || Min < 60) && (Hour >= 0 || Hour < 24))
	{
		HH = Hour;
		MM = Min;
	}

}
int Time::GetHours()
{
	return HH;

}
int Time::GetMin()
{
	return MM;
}
void Time::Print()
{
	cout << " " << HH << ":" << MM << endl;
}
Time Time::IncrementTime()
{
	MM = MM + 1;
	if (MM >= 60)
	{
		MM = MM - 60;
		HH = HH + 1;
	}

	
	
	return Time(HH,MM);
}

Time Time::operator - (Time T)
{
	Time Temp;
	if (MM - T.GetMin() < 0)
	{
		Temp.MM = (MM - T.GetMin()) + 60;

		if (T.GetHours() - HH < 0)
		{
			Temp.HH = abs(HH - T.GetHours());
			Temp.HH--;
		}
		else
		{
			Temp.HH = abs(HH - T.GetHours());
			Temp.HH--;
		}
	}
	else
	{
		Temp.MM = MM - T.GetMin();
		if (HH - T.GetHours() < 0)
		{
			Temp.HH = abs(HH - T.GetHours());
		}
		else
		{
			Temp.HH = abs(HH - T.GetHours());
		}
	}
	return Temp;
}
void Time::operator = (Time T)
{
	SetTime(T.GetHours(), T.GetMin());
}


bool Time::operator==(Time T)
{
	if (HH == T.GetHours() && MM == T.GetMin())
	{
		return true;
	}
	else
		return false;
}
bool Time::operator>=(Time T)
{
	if (HH > T.GetHours())
	{
		return true;
	}
	else if (HH == T.GetHours() && MM >= T.GetMin())
	{
		return true;
	}
	else
		return false;
}
Time::~Time()
{

}
