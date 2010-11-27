#pragma once

#include "Shader.h"

class QuadGeometry;

class RENDER_DLL BMPostFXRenderer
{
    SINGLETON_DECLARE(BMPostFXRenderer);

    /*
    *   types
    */
public:
    enum EPostFXType
    {
        EPF_Bloom
    };

    //funcs-interface
public:
    void Init();
    void Render();
    void InitResource();
    void ReleaseResource();

protected:
    BMPostFXRenderer();
    ~BMPostFXRenderer();

	void InitBloom();

    //attributes access
public:
    TexturePtr          GetBloomRenderTarget(u32 idx)    { assert(idx<msBloomBufferCount); return mBloomRenderTarget[idx]; }
    TexturePtr          GetBloomRT(u32 idx)              { assert(idx<msBloomBufferCount); return mBloomRenderTarget[idx]; }
    const QuadGeometry* GetQuadGeometry()const              { return mQuadGeometry; }
    void                StoreBackBuffer();
    void                RenderToBackBuffer(TexturePtr tex);

    //attributes
protected:
    const static u32 msBloomBufferCount = 3;

    //render targets
    TexturePtr          mBloomRenderTarget[msBloomBufferCount];
    SurfacePtr          mBloomSurface[msBloomBufferCount];

    SurfacePtr          mBackBuffer;

    //utility to render full screen quad
    QuadGeometry*       mQuadGeometry;

    ShaderId            mBloomFilter;
    ShaderId            mBloomBlurV;
    ShaderId            mBloomBlurH;
    ShaderId            mBloomMerge;
    ShaderId            mCopy;
};