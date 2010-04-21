#pragma once

class CORE_DLL DXUTTimer
{
public:
	static void SetTime(double _t)		{	mTime = _t;	}
	static void SetElapsedTime(float _t){	mElapsedTime = _t;	}

	static float GetElapsedTime()		{return mElapsedTime;	}
	static double GetTime()				{return mTime;	}
private:
	static double	mTime;
	static float	mElapsedTime;
};