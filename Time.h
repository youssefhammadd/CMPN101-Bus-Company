#pragma once
#include <iostream>
using namespace std;
class Time
{
	int HH;
	int MM;
public:
	Time(int Hours = 0, int Minutes = 0);
	void SetTime(int Hour, int Min);
	int GetHours();
	int GetMin();
	void Print();
	Time IncrementTime();
	Time operator - (Time T);
	void operator = (Time T);
	bool operator==(Time T);
	bool operator>=(Time T);
	~Time();
};

