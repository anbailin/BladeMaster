#pragma once

#include "DCSurface.h"
#include "DCRenderType.h"

class DCTexture:public RefObject
{
public:
	DCTexture(DCSurfacePtr _surface, TexWrapState _wrap = kTexWrapUWrapV, TexFilterState _filter = kTexFilterLinear):
	  mSurface(_surface), mWrapState(_wrap), mFilterState(_filter)
	{}

	virtual ~DCTexture(){}

	TexWrapState		GetWrapState()const				{ return mWrapState; }
	void				SetWrapState(TexWrapState _wrap){ mWrapState = _wrap; }

	TexFilterState		GetFilterState()const			{ return mFilterState; }
	void				SetFilterState(TexFilterState _filter){mFilterState = _filter;}

	DCSurfacePtr    	GetSurfacePtr()const				{return mSurface;}
	void				SetSurfacePtr(DCSurfacePtr _surface){mSurface = _surface;}
private:
	DCSurfacePtr		mSurface;
	TexWrapState		mWrapState;
	TexFilterState		mFilterState;
};

typedef ComPtr<DCTexture>			   DCTexturePtr;