#pragma once

#ifndef DEVICEPTR
#define DEVICEPTR DCRenderer::GetInstance()->GetDevice()
#endif

class DCTexture;
class QuadGeometry;
struct IDirect3DTexture9;
struct IDirect3DSurface9;
struct IDirect3DPixelShader9;
struct IDirect3DVertexShader9;

/**
*   global render resource holder
*   global render interface impl
*   render engine's manager

*   ps0 : Init for app resource, InitResource for render driver resource
*/
class RENDER_DLL DCRenderer
{
    //funcs--interface
public:
    SINGLETON_DECLARE(DCRenderer);
    void    Init();
	bool    ApplyTexture(uint32 stage, const DCTexture* tex);

	void    BeginRender();
	void    EndRender();

    void    InitResource(IDirect3DDevice9* deivce);  
    void    ReleaseResource();
protected:
    DCRenderer();
    ~DCRenderer();
	void InitCopy();

    //attribues access
public:
    IDirect3DDevice9* GetDevice(){return mDevice;}
    void              GetBackBufferSize(uint32& sizeX, uint32& sizeY)const { sizeX = mBackBufferSizeX; sizeY = mBackBufferSizeY; }    
	TexturePtr	      GetLightingRT() { return mLightingRT; }    

    //attribues
protected:
    IDirect3DDevice9* mDevice;    

    //resource
    QuadGeometry*       mQuadGeometry;
    //config
    uint32              mBackBufferSizeX;
    uint32              mBackBufferSizeY;
	TexturePtr      	mLightingRT;    
};