#pragma once

#include "GraphicsPublic.h"
#include "Renderer.h"

IDirect3DDevice9* WINAPI DXUTGetD3D9Device();

namespace BM
{
    class D3D9RenderDeviceManager;

    class RENDER_DLL D3D9Renderer : public Renderer
    {
        Q_OBJECT

    public:
        D3D9Renderer();
        ~D3D9Renderer();

    public:
        virtual void Init(QWidget* pRenderWidget);
        virtual void Exit();
        virtual void Tick(Float32 fDeltaTime);
        virtual void Update(Float32 fDeltaTime);
        virtual void Draw(Float32 fDeltaTime);

        IDirect3DDevice9* GetDevice() { return DXUTGetD3D9Device(); }

    protected:
        void InitDXUT();

        virtual bool IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed);
        virtual void OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc);
        virtual void OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc);
        virtual void OnLostDevice();
        virtual void OnDestroyDevice();

    private:
        Float32 m_fDeltaTime;

    public:
        static bool    CALLBACK DXUT_IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext);
        static HRESULT CALLBACK DXUT_OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
        static HRESULT CALLBACK DXUT_OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
        static void    CALLBACK DXUT_OnLostDevice(void* pUserContext);
        static void    CALLBACK DXUT_OnDestroyDevice(void* pUserContext);
        static void    CALLBACK DXUT_OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
    };

    BM_CLASS_FACTORY_REGISTER(D3D9Renderer);
}
