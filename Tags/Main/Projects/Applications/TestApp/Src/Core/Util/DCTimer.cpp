#include "BMCore.h"

DCTimer::DCTimer(DCTimerManager& manager):
mManager(manager),
mdCurrentTime(0),
mdFrameTime(0),
mbPaused(0),
mfScale(1.0f)
{
  mManager.AddTimer(this);
}

//forbid using operator =
const DCTimer& DCTimer::operator = (const DCTimer& _arg)
{
	assert(0);
	return *this;
}

DCTimer::~DCTimer()
{
	mManager.RemoveTimer(this);
}

void DCTimer::Notify()
{
	if(mbPaused!=false)
	{
		mdFrameTime=mManager.GetFrameDuration()*mfScale;
		mdCurrentTime+=mdFrameTime;
	}
}

