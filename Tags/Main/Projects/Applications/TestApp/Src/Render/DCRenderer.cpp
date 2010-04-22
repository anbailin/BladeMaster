#include "DCRenderHeader.h"

BM_SINGLETON_DEFINE(DCRenderer);

namespace RendererConfig
{
    const uint32 BackBufferSizeX = 800;
    const uint32 BackBufferSizeY = 600;
}

DCRenderer::DCRenderer()
:   mBackBufferSizeX(RendererConfig::BackBufferSizeX)
,   mBackBufferSizeY(RendererConfig::BackBufferSizeY)
{	
}

DCRenderer::~DCRenderer()
{
    ShaderLoader::DeleteInstance();
	SafeRelease(mDevice);
}

bool DCRenderer::ApplyTexture(uint32 stage, const DCTexture* tex)
{
    mDevice->SetSamplerState(stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    mDevice->SetSamplerState(stage, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    mDevice->SetSamplerState(stage, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	return SUCCEEDED(mDevice->SetTexture(stage,(IDirect3DBaseTexture9*)(tex->GetSurfacePtr()->GetTexture().GetPointer())) );
}

void DCRenderer::Init()
{
	DCRenderSetter::Init();
    
    BMPostFXRenderer::CreateInstance();    
    BMPostFXRenderer::Instance().Init();

    ShaderLoader::CreateInstance();
    ShaderLoader::Instance().Init();

    VertexDeclareManager::CreateInstance();
}

uint32 aa,bb;
void DCRenderer::BeginRender()
{
    BMPostFXRenderer::Instance().StoreBackBuffer();

    //set lighting rt
	IDirect3DSurface9* surface;
	HRESULT result = mLightingRT->GetSurfaceLevel(0, &surface);
	assert(SUCCEEDED(result));

	result = DEVICEPTR->SetRenderTarget(0, surface);
	assert(SUCCEEDED(result));

    DEVICEPTR->GetDepthStencilSurface(&surface);
    D3DSURFACE_DESC pDesc;
    surface->GetDesc(&pDesc);
    //std::string str("size");
    //str += (char)pDesc.Width;
    //str += (char)pDesc.Height;
    //LogToDebug(str.c_str());
    aa = pDesc.Width;
    bb = pDesc.Height;
}


//render lighting buffer into back to backbuffer
void DCRenderer::EndRender()
{
    BMPostFXRenderer::Instance().RenderToBackBuffer(mLightingRT);
}

//can be called on onresetdevice
void DCRenderer::InitResource(IDirect3DDevice9* deivce)
{
    mDevice = deivce;   
    //render target
    HRESULT result = DEVICEPTR->CreateTexture(
        mBackBufferSizeX,
        mBackBufferSizeY, 
        1, 
        D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8, 
        D3DPOOL_DEFAULT, 
        &mLightingRT, 
        NULL
        );

    assert(SUCCEEDED(result));

    ShaderLoader::Instance().CreateShaderCache();
    BMPostFXRenderer::Instance().InitResource();
    VertexDeclareManager::Instance().CreateResource();
}

//release graphics driver related resource including shader/texture
void DCRenderer::ReleaseResource()
{
    mLightingRT = NULL;

    BMPostFXRenderer::Instance().ReleaseResource();
    ShaderLoader::Instance().DestroyShaderCache();
    VertexDeclareManager::Instance().ReleaseResource();
}

