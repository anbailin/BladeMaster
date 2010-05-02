#include "CorePrivate.h"

namespace BM
{
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

    const UInt64  Timer::TicksPerSecond = g_TimerPrivate.Frequency.QuadPart;
    const Float64 Timer::SecondsPerTick = 1.0 / Timer::TicksPerSecond;
}
