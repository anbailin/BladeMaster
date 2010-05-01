#pragma once

//#include "Graphics.h"

//void ColorAssign(D3DCOLORVALUE& outColor,const D3DXVECTOR4& inColor);
//
//void V4ToV3Assign(D3DXVECTOR3& vOut, const D3DXVECTOR4& vIn);

struct pix_event
{
	pix_event(D3DCOLOR col,LPCWSTR wszName){	D3DPERF_BeginEvent(col,wszName);	}
	~pix_event(){	D3DPERF_EndEvent();	}
};


void fixname(char *name, size_t len);

void fixname(std::string &name);