#pragma once
class DCTimer;
#include "IDCTimer.h"
#include "DCTimerManager.h"

class DCTimer:public IDCTimer
{
public:
	DCTimer(DCTimerManager& manager);
	const DCTimer& operator = (const DCTimer& _arg);
	~DCTimer();

	double		GetTime() const { return mdCurrentTime; }
	double		GetFrameDuration() const { return mdFrameTime; }

	void		Pause (bool bOn){mbPaused=bOn;}
	void		SetScale (float fScale){mfScale=fScale;}   

	bool		IsPaused () const{return mbPaused;}
	float		GetScale () const{return mfScale;}

private:
//method------------------------------------------------------------------------
	virtual void Notify();
//data------------------------------------------------------------------------
	DCTimerManager& mManager;

	double			mdCurrentTime;
	double			mdFrameTime;

	bool			mbPaused;
	float			mfScale;
};