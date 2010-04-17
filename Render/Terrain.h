#pragma once

/**
*	a simple terrain
*/
class RENDER_DLL BMTerrain:public RefObject
{
public:
	BMTerrain();
	virtual ~BMTerrain();

	void Draw(D3DXMATRIXA16* worldMtx,D3DXMATRIXA16* viewMtx, D3DXMATRIXA16* projMtx);
	void Init();

protected:
	VertexBufferPtr	mVB;
    IndexBufferPtr  mIB;
};

typedef ComPtr<BMTerrain> BMTerrainPtr;
