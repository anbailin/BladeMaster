#pragma once

struct GuardRenderState
{
	GuardRenderState(D3DRENDERSTATETYPE state, DWORD value)
	{
		mCacheState = state;
		DEVICEPTR->GetRenderState(state,&mCacheValue);
		DEVICEPTR->SetRenderState(state,value);
	}

	~GuardRenderState()
	{
		DEVICEPTR->SetRenderState(mCacheState,mCacheValue);
	}

	D3DRENDERSTATETYPE mCacheState;
	DWORD			   mCacheValue;
};


#define GUARD_RENDERSTATE(state,value)	GuardRenderState _guard##state(state,value)