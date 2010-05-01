#pragma once
#include "IDCTimeSource.h"

class DCTimeSource_win:public IDCTimeSource
{
public:
	DCTimeSource_win();
	virtual double GetTime() const;
private:
	double GetSecondsPerTick()const;
	double mdSecsPerTick;
};