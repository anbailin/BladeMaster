#include "GraphicsPrivate.h"

SINGLETON_DEFINE(BMPostFXRenderer);

BMPostFXRenderer::BMPostFXRenderer()
{

}

BMPostFXRenderer::~BMPostFXRenderer()
{
    ReleaseResource();
    SafeDelete(mQuadGeometry);
}

namespace
{
	const WCHAR* postfx_shader_path = L"PostFX.hlsl";
    const WCHAR* copy_shader_path = L"Copy.hlsl";
}

void BMPostFXRenderer::Init()
{
    //resource init
    mQuadGeometry = new QuadGeometry;    
}

void BMPostFXRenderer::InitResource()
{
    mQuadGeometry->Init();

    //init bloom
    InitBloom();    
}

//only release render driver resource, no app resource
void BMPostFXRenderer::ReleaseResource()
{
    for(uint32 i=0; i<msBloomBufferCount; i++)
    {
        mBloomRenderTarget[i] = NULL;
        mBloomSurface[i] = NULL;
    }
}

void BMPostFXRenderer::InitBloom()
{
	//render targets
	uint32 sizeX, sizeY;
	DCRenderer::GetInstance()->GetBackBufferSize(sizeX,sizeY);
	HRESULT result = DEVICEPTR->CreateTexture(
		sizeX,
		sizeY, 
		1, 
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8, 
		D3DPOOL_DEFAULT, 
		&mBloomRenderTarget[0], 
		NULL
		);

	assert(SUCCEEDED(result));

    result = mBloomRenderTarget[0]->GetSurfaceLevel(0, &mBloomSurface[0]);
    assert(SUCCEEDED(result));

	const uint32 halfSizeX = sizeX/2;
	const uint32 halfSizeY = sizeY/2;
	result = DEVICEPTR->CreateTexture(
		halfSizeX,
		halfSizeY, 
		1, 
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8, 
		D3DPOOL_DEFAULT, 
		&mBloomRenderTarget[1], 
		NULL
		);
	assert(SUCCEEDED(result));
    
    result = mBloomRenderTarget[1]->GetSurfaceLevel(0, &mBloomSurface[1]);
    assert(SUCCEEDED(result));

	result = DEVICEPTR->CreateTexture(
		halfSizeX,
		halfSizeY, 
		1, 
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8, 
		D3DPOOL_DEFAULT, 
		&mBloomRenderTarget[2], 
		NULL
		);
	assert(SUCCEEDED(result));

    result = mBloomRenderTarget[2]->GetSurfaceLevel(0, &mBloomSurface[2]);
    assert(SUCCEEDED(result));
}

/*
*   bloom only
*/
void BMPostFXRenderer::Render()
{
    //pix_event g( DXUT_PERFEVENTCOLOR, L"PostFX" );
    //filter pass
    DEVICEPTR->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    DEVICEPTR->SetRenderTarget(0, mBloomSurface[0]);
    ShaderLoader::GetInstance()->ApplyShader(ShaderLoader::GetInstance()->postfx_bloom_filter_vs_id, ShaderLoader::GetInstance()->postfx_bloom_filter_ps_id);

    TexturePtr lightingRT = DCRenderer::GetInstance()->GetLightingRT();
    SurfacePtr lightingSurface;
    lightingRT->GetSurfaceLevel(0,&lightingSurface);
    DEVICEPTR->SetTexture(0, lightingRT);
    
    mQuadGeometry->Render();

    //blur v
    DEVICEPTR->SetRenderTarget(0, mBloomSurface[1]);
    ShaderLoader::GetInstance()->ApplyShader(ShaderLoader::GetInstance()->postfx_bloom_filter_vs_id, ShaderLoader::GetInstance()->postfx_bloom_blurv_ps_id);
    DEVICEPTR->SetTexture(0, mBloomRenderTarget[0]);
    mQuadGeometry->Render();

    //blur h
    DEVICEPTR->SetRenderTarget(0, mBloomSurface[2]);
    ShaderLoader::GetInstance()->ApplyShader(ShaderLoader::GetInstance()->postfx_bloom_filter_vs_id, ShaderLoader::GetInstance()->postfx_bloom_blurh_ps_id);
    DEVICEPTR->SetTexture(0, mBloomRenderTarget[1]);
    mQuadGeometry->Render();

    //debug code
    DEVICEPTR->SetRenderTarget(0, mBackBuffer);
    DEVICEPTR->SetTexture(0, lightingRT);
    DEVICEPTR->SetTexture(1, mBloomRenderTarget[2]);
    ShaderLoader::GetInstance()->ApplyShader(ShaderLoader::GetInstance()->postfx_bloom_filter_vs_id, ShaderLoader::GetInstance()->postfx_bloom_merge_ps_id);
    mQuadGeometry->Render();
}

void BMPostFXRenderer::StoreBackBuffer()
{
    HRESULT result = DEVICEPTR->GetRenderTarget(0, &mBackBuffer);
    assert(SUCCEEDED(result));
}

void BMPostFXRenderer::RenderToBackBuffer(TexturePtr tex)
{    
/*    ShaderLoader::GetInstance()->ApplyShader(ShaderLoader::GetInstance()->postfx_copy_vs_id, ShaderLoader::GetInstance()->postfx_copy_ps_id);
    DEVICEPTR->SetTexture(0, tex);    
    DEVICEPTR->SetRenderTarget(0,mBackBuffer);

    DEVICEPTR->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    mQuadGeometry->Render(); */   
}
