#include "CorePrivate.h"
#include "Utilities.h"
#include "Timer.h"


class TimerPrivate
{
public:
    TimerPrivate()
    {
        QueryPerformanceFrequency(&Frequency);
    }

public:
    LARGE_INTEGER Frequency;
} ;

TimerPrivate g_TimerPrivate;

const u64  Timer::TicksPerSecond = g_TimerPrivate.Frequency.QuadPart;
const f64 Timer::SecondsPerTick = 1.0 / Timer::TicksPerSecond;
