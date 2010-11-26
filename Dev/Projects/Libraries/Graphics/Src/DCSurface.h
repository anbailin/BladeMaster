#pragma once

class RENDER_DLL DCSurface:public RefObject
{
public:
	static DCSurface* Create(const std::string& filename);

	DCSurface(ComPtr<IDirect3DTexture9>& _tex);
	virtual ~DCSurface(){}

	u32		GetWidth()const  {return mWidth;}
	u32		GetHeight()const {return mHeight;}	
	u32		GetMipMapLevel() {return mMipMapLevel;}
	D3DFORMAT	GetFormat()const {return mFormat;}

	ComPtr<IDirect3DTexture9 > GetTexture() {return mTexture;}
private:
	ComPtr<IDirect3DTexture9 >	  mTexture;
	u32						  mWidth;
	u32						  mHeight;
	u32						  mMipMapLevel;
	D3DFORMAT					  mFormat;
};

typedef ComPtr<DCSurface> DCSurfacePtr;

