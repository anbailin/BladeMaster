#pragma once

class QuadGeometry;

class RENDER_DLL BMPostFXRenderer
{
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
    SINGLETON_DECLARE(BMPostFXRenderer);
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
    TexturePtr          GetBloomRenderTarget(uint32 idx)    { assert(idx<msBloomBufferCount); return mBloomRenderTarget[idx]; }
    TexturePtr          GetBloomRT(uint32 idx)              { assert(idx<msBloomBufferCount); return mBloomRenderTarget[idx]; }
    const QuadGeometry* GetQuadGeometry()const              { return mQuadGeometry; }
    void                StoreBackBuffer();
    void                RenderToBackBuffer(TexturePtr tex);

    //attributes
protected:
    const static uint32 msBloomBufferCount = 3;

    //render targets
    TexturePtr          mBloomRenderTarget[msBloomBufferCount];
    SurfacePtr          mBloomSurface[msBloomBufferCount];

    SurfacePtr          mBackBuffer;

    //utility to render full screen quad
    QuadGeometry*       mQuadGeometry;
};