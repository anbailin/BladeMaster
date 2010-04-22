#include "DCRenderHeader.h"
#include "EnginePCH.h"

//to do : to improve the loading process;
DCSurface* DCSurface::Create(const std::string& filename)
{
	BLPFile file(filename);
	if(file.Available()==false)
		return NULL;
	
	ComPtr<IDirect3DTexture9> tex;

	BM_AssertHr(
		D3DXCreateTexture(DCRenderer::Instance().GetDevice(),
		file.GetWidth(),
		file.GetHeight(),
		file.GetMipMapLevel(),
		0,
		file.GetFormat(),
		D3DPOOL_MANAGED,
		&tex)
		);
	
	//format should be dxt
	assert(file.GetFormat()!=D3DFMT_A8R8G8B8);

	D3DLOCKED_RECT rect;
	uint32 w = file.GetWidth();
	uint32 h = file.GetHeight();
	void* buffer = NULL;
	uint32 size = 0;
	for(uint32 i=0;i<file.GetMipMapLevel();i++)
	{
		buffer = file.GetMipMapAddr(i);
		size = file.GetMipMapSize(i);

		tex->LockRect(i,&rect,0,0);
		memcpy(rect.pBits,buffer,size);
		tex->UnlockRect(i);

		w=w>>1;
		h=h>>1;
	}

	DCSurface* result = new DCSurface(tex);
	result->mWidth = file.GetWidth();
	result->mHeight = file.GetHeight();
	result->mMipMapLevel = file.GetMipMapLevel();
	result->mFormat = file.GetFormat();

	return result;
}

DCSurface::DCSurface(ComPtr<IDirect3DTexture9>& _tex):
mTexture(_tex)
{

}