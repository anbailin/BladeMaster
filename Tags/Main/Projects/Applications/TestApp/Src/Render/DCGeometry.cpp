#include "DCRenderHeader.h"
#include "EnginePCH.h"

#pragma optimize("",off)

DCGeometry::DCGeometry():
mID(0),mVertexCount(0),mVertexStart(0),mIndexCount(0)
{ }

DCGeometry::DCGeometry(const MDXGeometry& geo)
{
	Init(geo);
}

inline void DCGeometry::Init(const MDXGeometry& geo)
{
	mID = geo.mID;
	mVertexStart = geo.mVertexStart;
	mVertexCount = geo.mVertexCount;
	mIndexCount = geo.mIndexCount;
	mIndexStart = geo.mIndexStart;
}

void DCGeometry::Draw()
{
#ifdef RELEASE
	HRESULT hr = DEVICEPTR->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,mVertexStart,mVertexCount,mIndexStart,mIndexCount/3);
	BM_AssertHr(hr);
#else
    DEVICEPTR->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,mVertexStart,mVertexCount,mIndexStart,mIndexCount/3);
#endif
}

#pragma optimize("",on)