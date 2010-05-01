#pragma once

#include <cstddef>
#include <vector>
#include <deque>
class DCTimerManager;
#include "DCTimer.h"
#include "DCTimeSource_win.h"
class DCTimerManager{
private:
	//data--------------------------------------------------
	const IDCTimeSource *mpTimeSource;
	double				mdCurrentTime;
	double				mdFrameDuration;
	int					mnFrameNumber;
	double				mdSourceStartVal;
	double				mdSourceLastValue;

	int					mnFrameHistoryUpperSize;
	double				mdFrameDefaultTime;

	std::deque<double>  mvFrameDurationHistory;
	typedef std::vector<IDCTimer *> TimerList;
	TimerList			mvTimers;
	//method------------------------------------------------
	double	GetExactLastFrameDuration ();
	void	AddToFrameHistory (double exactFrameDuration);
	double	GetPredictedFrameDuration () const;
public:
	//method------------------------------------------------
	DCTimerManager(const IDCTimeSource * pSource = NULL);
	~DCTimerManager();

	void	SetTimeSource(const IDCTimeSource * pSource);

	void	FrameStep();

	double	GetTime() const { return mdCurrentTime; }
	double	GetFrameDuration() const { return mdFrameDuration; }
	int		GetFrameNumber() const { return mnFrameNumber; }
	float	GetFrameRate() const;

	void	AddTimer (IDCTimer * pObserver);
	void	RemoveTimer (IDCTimer * pObserver);
	void	SetFiltering (int frameWindow, double frameDefault = 0.030);
};