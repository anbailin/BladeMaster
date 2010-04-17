#pragma once

#include "DCDef.h"



D3DXVECTOR3 FixCoordSystem(const D3DXVECTOR3 v);

D3DXVECTOR3 FixCoordSystem2(const D3DXVECTOR3 v);

D3DXQUATERNION FixCoordSystemQuat(D3DXQUATERNION v);

void ColorAssign(D3DCOLORVALUE& outColor,const D3DXVECTOR4& inColor);

void V4ToV3Assign(D3DXVECTOR3& vOut, const D3DXVECTOR4& vIn);

//struct pix_event
//{
//	pix_event(D3DCOLOR col,LPCWSTR wszName){D3DPERF_BeginEvent(col,wszName);}
//	~pix_event(){D3DPERF_EndEvent();}
//};