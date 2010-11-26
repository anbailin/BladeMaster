#pragma once

namespace BM
{
    class CORE_DLL Timer
    {
    public:
        inline Timer();

    public:
        inline void     Start();
        inline void     Stop();

        inline void     Reset(u64 iTicks = 0);
        inline void     Restart(u64 iTicks = 0);

        inline bool     IsStarted() const   { return m_bStarted;}
        inline bool     IsStopped() const   { return !m_bStarted; }

        inline u64   Ticks() const;
        inline f64  Seconds() const     { return TicksToSeconds(Ticks()); }

        inline u64   TicksSinceStart() const;

    private:
        bool    m_bStarted;
        u64  m_iStartTick;
        u64  m_iTotalTick;

    public:
        inline static u64  CpuTicks();
        inline static f64 CpuSeconds()  { return TicksToSeconds(CpuTicks()); }

        inline static u64  DeltaTicks(u64 iStart, u64 iEnd);

        inline static f64 TicksToSeconds(u64 iTicks);
        inline static u64  SecondsToTicks(f64 fSeconds);

    public:
        static const u64  TicksPerSecond;
        static const f64 SecondsPerTick;
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

    inline void Timer::Reset(u64 iTicks)
    {
        m_bStarted = false;
        m_iTotalTick = iTicks;
    }

    inline void Timer::Restart(u64 iTicks)
    {
        Reset(iTicks);
        Start();
    }

    inline u64 Timer::Ticks() const
    {
        return m_iTotalTick + TicksSinceStart();
    }

    inline u64 Timer::TicksSinceStart() const
    {
        return (m_bStarted ? DeltaTicks(m_iStartTick, CpuTicks()) : 0);
    }

    inline u64 Timer::CpuTicks()
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return counter.QuadPart;
    }

    inline u64 Timer::DeltaTicks(u64 iStart, u64 iEnd)
    {
        return ((iEnd >= iStart) ? (iEnd - iStart): ((UInt64_Max - iStart) + iEnd + 1));
    }

    inline f64 Timer::TicksToSeconds(u64 iTicks)
    {
        return (f64)(iTicks * SecondsPerTick);
    }

    inline u64 Timer::SecondsToTicks(f64 fSeconds)
    {
        return (u64)(fSeconds * TicksPerSecond);
    }
}
