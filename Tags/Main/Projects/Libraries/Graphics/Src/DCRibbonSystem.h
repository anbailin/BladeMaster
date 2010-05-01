#pragma once

#include <list>

#include "DCDef.h"
#include "DCAnimation.h"
#include "DCModelHeader.h"
#include "DCBone.h"
#include "DCTexture.h"

struct DCRibbonSegment {
	D3DXVECTOR3 pos, up, back;
	float len,len0;
};

class DCRibbonEmitter {
	Animated<D3DXVECTOR3>		mColor;
	Animatedint16				mOpacity;
	Animated<float>				mAbove, mBelow;

	DCBone						*mpParent;
	float						mfF1, mfF2;

	D3DXVECTOR3					mPos;

	int32						mnAnim, mnTime;
	float						mfLength, mfSeglen;
	int numsegs;

	D3DXVECTOR3					mTransPos;
	D3DXVECTOR4					mTransColor;
	float						mfTAbove, mfTBelow;

	DCTexture					*mpTexture;
	std::list<DCRibbonSegment>	mvSegs;

public:
	DCModel						*mpModel;

	void Init(MPQFile &f, ModelRibbonEmitterDef &mta, int *globals){}
	void Setup(int anim, int time){}
	void Draw(){}
};

