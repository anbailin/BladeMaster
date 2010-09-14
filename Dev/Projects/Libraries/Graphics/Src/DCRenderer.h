#pragma once

#include "D3D9Renderer.h"
#include "Core.h"

using namespace BM;

#ifndef DEVICEPTR
#define DEVICEPTR DCRenderer::GetInstance()->GetDevice()
#endif

class DCTexture;
class QuadGeometry;
struct IDirect3DTexture9;
struct IDirect3DSurface9;
struct IDirect3DPixelShader9;
struct IDirect3DVertexShader9;
class DCModel;
class BMTerrain;

/**
*   global render resource holder
*   global render interface impl
*   render engine's manager

*   ps0 : Init for app resource, InitResource for render driver resource
*/
class RENDER_DLL DCRenderer : public D3D9Renderer
{
    Q_OBJECT

    SINGLETON_DECLARE(DCRenderer);

public:
    DCRenderer();
    ~DCRenderer();

    //funcs--interface
public:
    virtual void Init(QWidget* pRenderWidget);
    virtual void Exit();
    virtual void Update(Float32 fDeltaTime);
    virtual void Draw(Float32 fDeltaTime);
	void	AddSceneNode(DCModel* modelPtr, const XMFLOAT3& translation);
	void    AddSceneTerrain(BMTerrain* terrain);
protected:
    virtual void OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc);
    virtual void OnLostDevice();
    virtual void OnDestroyDevice();

public:
    bool    ApplyTexture(uint32 stage, const DCTexture* tex);

	void    BeginRender();
	void    EndRender();

    void    InitResource(IDirect3DDevice9* deivce);  
    void    ReleaseResource();

protected:
	void InitCopy();

    //attribues access
public:
    void              GetBackBufferSize(uint32& sizeX, uint32& sizeY)const { sizeX = mBackBufferSizeX; sizeY = mBackBufferSizeY; }    
	TexturePtr	      GetLightingRT() { return mLightingRT; }    

	void			  SetViewProjMatrix(XMMATRIX* view, XMMATRIX* proj, XMMATRIX* viewProj);
    //attribues
protected:
    //resource
    QuadGeometry*       mQuadGeometry;
    //config
    uint32              mBackBufferSizeX;
    uint32              mBackBufferSizeY;
	TexturePtr      	mLightingRT;    
	XMMATRIX*			mViewMatrix;
	XMMATRIX*			mProjMatrix;
	XMMATRIX*			mViewProjMatrix;
};

BM_CLASS_FACTORY_REGISTER(DCRenderer);
