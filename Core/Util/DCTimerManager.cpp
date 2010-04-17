#include "Core.h"



DCTimerManager::DCTimerManager(const IDCTimeSource * pSource):
mpTimeSource (NULL),
mdCurrentTime (0),
mdFrameDuration (0),
mnFrameNumber (0),
mdSourceStartVal (0),
mdSourceLastValue (0)
{
	SetTimeSource(pSource);
	SetFiltering(1);
	mdFrameDuration = GetPredictedFrameDuration();
}

DCTimerManager::~DCTimerManager(){
	delete this->mpTimeSource;
}
//set time source and the according source last/start value
void DCTimerManager::SetTimeSource(const IDCTimeSource * pSource)
{
	delete mpTimeSource;
	mpTimeSource = pSource;
	if (mpTimeSource != NULL)
	{
		mdSourceStartVal = mpTimeSource->GetTime ();        
		mdSourceLastValue = mdSourceStartVal;
	}
}

void DCTimerManager::FrameStep()
{
	double exactLastFrameDuration = GetExactLastFrameDuration();
	AddToFrameHistory(exactLastFrameDuration);

	mdFrameDuration = GetPredictedFrameDuration();
	mdCurrentTime += mdFrameDuration;

	mnFrameNumber++;

	TimerList::iterator it;
	for (it = this->mvTimers.begin(); it != mvTimers.end(); ++it)
		(*it)->Notify();
}

double DCTimerManager::GetExactLastFrameDuration ()
{
	double sourceTime;
	if (mpTimeSource == NULL)
		sourceTime = 0;
	else    
		sourceTime = mpTimeSource->GetTime();

	double frameDuration = sourceTime - mdSourceLastValue;
	if (frameDuration > 0.200)
		frameDuration = mvFrameDurationHistory.back();
	mdSourceLastValue = sourceTime;
	return frameDuration;
}

void DCTimerManager::AddToFrameHistory (double exactFrameDuration)
{
	this->mvFrameDurationHistory.push_back (exactFrameDuration);
	if (mvFrameDurationHistory.size () > (unsigned int) mnFrameHistoryUpperSize)
		mvFrameDurationHistory.pop_front ();
}


double DCTimerManager::GetPredictedFrameDuration () const
{
	double totalFrameTime = 0;

	std::deque<double>::const_iterator it;
	for (it = mvFrameDurationHistory.begin(); it != mvFrameDurationHistory.end(); ++it)
		totalFrameTime += *it;
	return totalFrameTime/mvFrameDurationHistory.size();
}



void DCTimerManager::AddTimer (IDCTimer * pTimer)
{
	if (pTimer != NULL)
		mvTimers.push_back(pTimer);
}

void DCTimerManager::RemoveTimer (IDCTimer * pObserver)
{
	mvTimers.erase(std::remove(mvTimers.begin(),mvTimers.end(), pObserver),	mvTimers.end());

}


float DCTimerManager::GetFrameRate () const
{
	return 1.0f/(float)mdFrameDuration;
}


void DCTimerManager::SetFiltering (int frameWindow, double frameDefault)
{
	//m_frameFilteringWindow = std::max(1, frameWindow);
	mnFrameHistoryUpperSize = frameWindow > 1 ? frameWindow : 1;
	mdFrameDefaultTime = frameDefault;
	mvFrameDurationHistory.clear ();
	mvFrameDurationHistory.push_back(mdFrameDefaultTime);
}