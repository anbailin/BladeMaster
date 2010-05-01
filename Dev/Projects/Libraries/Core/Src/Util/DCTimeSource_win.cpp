#include "DCTimeSource_win.h"
#include <windows.h>

DCTimeSource_win::DCTimeSource_win()
{
	LARGE_INTEGER freq;
	::QueryPerformanceFrequency(&freq);
	mdSecsPerTick=1.0/freq.QuadPart;
}

double DCTimeSource_win::GetTime() const
{
	LARGE_INTEGER time;
	::QueryPerformanceCounter(&time);
	return time.QuadPart*mdSecsPerTick;
}