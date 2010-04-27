#include "DCRenderHeader.h"
#include "App.h"

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
    s_pInstance = this;
}

DCRenderer::~DCRenderer()
{
    ShaderLoader::DeleteInstance();
	//SafeRelease(DEVICEPTR);
}

bool DCRenderer::ApplyTexture(uint32 stage, const DCTexture* tex)
{
    DEVICEPTR->SetSamplerState(stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    DEVICEPTR->SetSamplerState(stage, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    DEVICEPTR->SetSamplerState(stage, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	return SUCCEEDED(DEVICEPTR->SetTexture(stage,(IDirect3DBaseTexture9*)(tex->GetSurfacePtr()->GetTexture().GetPointer())) );
}

void DCRenderer::Init(QWidget* pRenderWidget)
{
    DCRenderSetter::Init();

    BMPostFXRenderer::CreateInstance();
    BMPostFXRenderer::Instance().Init();

    ShaderLoader::CreateInstance();
    ShaderLoader::Instance().Init();

    VertexDeclareManager::CreateInstance();

    D3D9Renderer::Init(pRenderWidget);
}

void DCRenderer::Exit()
{
}

void DCRenderer::Update(Float32 fDeltaTime)
{

}

void DCRenderer::Draw(Float32 fDeltaTime)
{
    // For our world matrix, we will just rotate the object about the y-axis.
    D3DXMATRIXA16 mxView, mxProj;

    D3DXVECTOR3 vEye(0.0f, 5.0f,-5.0f);
    D3DXVECTOR3 vAt(0.0f,0.0f,1.0f);
    D3DXVECTOR3 vUp(0.0f,1.0f,0.0f);

    float fAspectRatio = m_pRenderWidget->width() / (FLOAT)m_pRenderWidget->height();

    D3DXMatrixLookAtLH(&mxView, &vEye, &vAt, &vUp);
    D3DXMatrixPerspectiveFovLH(&mxProj, D3DX_PI/3, fAspectRatio, 0.001f, 100.0f);

    SceneRenderer::Instance().SetViewMatrix(mxView);
    SceneRenderer::Instance().SetProjMatrix(mxProj);

    SceneRenderer::Instance().RenderScene(*(LevelManager::Instance().GetLevelInstance()));
}

void DCRenderer::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc)
{
    InitResource(pd3dDevice);

    //LevelManager::Instance().LoadMap("map");
}

void DCRenderer::OnLostDevice()
{
    ReleaseResource();
}

void DCRenderer::OnDestroyDevice()
{
    ReleaseResource();
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
    //DEVICEPTR = deivce;   
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

