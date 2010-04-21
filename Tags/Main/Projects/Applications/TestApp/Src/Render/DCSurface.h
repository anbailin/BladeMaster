#pragma once

class RENDER_DLL DCSurface:public RefObject
{
public:
	static DCSurface* Create(const std::string& filename);

	DCSurface(ComPtr<IDirect3DTexture9>& _tex);
	virtual ~DCSurface(){}

	uint32		GetWidth()const  {return mWidth;}
	uint32		GetHeight()const {return mHeight;}	
	uint32		GetMipMapLevel() {return mMipMapLevel;}
	D3DFORMAT	GetFormat()const {return mFormat;}

	ComPtr<IDirect3DTexture9 > GetTexture() {return mTexture;}
private:
	ComPtr<IDirect3DTexture9 >	  mTexture;
	uint32						  mWidth;
	uint32						  mHeight;
	uint32						  mMipMapLevel;
	D3DFORMAT					  mFormat;
};

typedef ComPtr<DCSurface> DCSurfacePtr;

