#pragma once
#include "DCRenderState.h"
class DCRenderSetter
{
public:
	static void Init();
	static DCRenderSetter*	Get(){return mInstance;	}

	void ApplyAlphaTest(DCAlphaTestState state);
	void ApplyAlphaBlend(DCAlphaBlendState state);
private:
	static DCRenderSetter*	mInstance;

	DCAlphaTestState	mAlphaTestCache;
	DCAlphaBlendState	mAlphaBlendCache;
};