#pragma once

#include "CorePublic.h"

namespace BM
{
    class CORE_API Timer
    {
    public:
        inline Timer();

    public:
        inline void     Start();
        inline void     Stop();

        inline void     Reset(UInt64 iTicks = 0);
        inline void     Restart(UInt64 iTicks = 0);

        inline bool     IsStarted() const   { return m_bStarted;}
        inline bool     IsStopped() const   { return !m_bStarted; }

        inline UInt64   Ticks() const;
        inline Float64  Seconds() const     { return TicksToSeconds(Ticks()); }

        inline UInt64   TicksSinceStart() const;

    private:
        bool    m_bStarted;
        UInt64  m_iStartTick;
        UInt64  m_iTotalTick;

    public:
        inline static UInt64  CpuTicks();
        inline static Float64 CpuSeconds()  { return TicksToSeconds(CpuTicks()); }

        inline static UInt64  DeltaTicks(UInt64 iStart, UInt64 iEnd);

        inline static Float64 TicksToSeconds(UInt64 iTicks);
        inline static UInt64  SecondsToTicks(Float64 fSeconds);

    public:
        static const UInt64  TicksPerSecond;
        static const Float64 SecondsPerTick;
    };

    inline Timer::Timer()
    {
        m_bStarted = false;
        m_iStartTick = 0;
        m_iTotalTick = 0;
    }

    inline void Timer::Start()
    {
        BM_Assert(!m_bStarted);
        m_iStartTick = CpuTicks();
        m_bStarted = true;
    }

    inline void Timer::Stop()
    {
        BM_Assert(m_bStarted);
        m_iTotalTick += DeltaTicks(CpuTicks(), m_iStartTick);
        m_bStarted = false;
    }

    inline void Timer::Reset(UInt64 iTicks)
    {
        m_bStarted = false;
        m_iTotalTick = iTicks;
    }

    inline void Timer::Restart(UInt64 iTicks)
    {
        Reset(iTicks);
        Start();
    }

    inline UInt64 Timer::Ticks() const
    {
        return m_iTotalTick + TicksSinceStart();
    }

    inline UInt64 Timer::TicksSinceStart() const
    {
        return (m_bStarted ? DeltaTicks(m_iStartTick, CpuTicks()) : 0);
    }

    inline UInt64 Timer::CpuTicks()
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return counter.QuadPart;
    }

    inline UInt64 Timer::DeltaTicks(UInt64 iStart, UInt64 iEnd)
    {
        return ((iEnd >= iStart) ? (iEnd - iStart): ((UInt64_Max - iStart) + iEnd + 1));
    }

    inline Float64 Timer::TicksToSeconds(UInt64 iTicks)
    {
        return (Float64)(iTicks * SecondsPerTick);
    }

    inline UInt64 Timer::SecondsToTicks(Float64 fSeconds)
    {
        return (UInt64)(fSeconds * TicksPerSecond);
    }
}
