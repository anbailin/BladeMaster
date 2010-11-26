#include "GraphicsPrivate.h"
#include "D3D9Renderer.h"
#include "DXUT.h"

namespace BM
{
    D3D9Renderer::D3D9Renderer()
    {
    }

    D3D9Renderer::~D3D9Renderer()
    {
    }

    void D3D9Renderer::Init(QWidget* pRenderWidget)
    {
        Renderer::Init(pRenderWidget);

        InitDXUT();
    }

    void D3D9Renderer::Exit()
    {
    }

    void D3D9Renderer::Tick(f32 fDeltaTime)
    {
        m_fDeltaTime = fDeltaTime;

        Update(fDeltaTime);

        DXUTRender3DEnvironment();
    }

    void D3D9Renderer::Update(f32 fDeltaTime)
    {

    }

    void D3D9Renderer::Draw(f32 fDeltaTime)
    {
        //GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR( 0.0f, 0.25f, 0.25f, 0.55f ), 1.0f, 0);
    }

    void D3D9Renderer::InitDXUT()
    {
        // Set DXUT callbacks
        DXUTSetCallbackD3D9DeviceAcceptable(D3D9Renderer::DXUT_IsDeviceAcceptable, this);
        DXUTSetCallbackD3D9DeviceCreated(D3D9Renderer::DXUT_OnCreateDevice, this);
        DXUTSetCallbackD3D9DeviceReset(D3D9Renderer::DXUT_OnResetDevice, this);
        DXUTSetCallbackD3D9DeviceLost(D3D9Renderer::DXUT_OnLostDevice, this);
        DXUTSetCallbackD3D9DeviceDestroyed(D3D9Renderer::DXUT_OnDestroyDevice, this);
        DXUTSetCallbackD3D9FrameRender(D3D9Renderer::DXUT_OnFrameRender, this);

        HRESULT hr;
        hr = DXUTInit(false, true, NULL, false);
        BM_AssertHr(hr);

        HWND hwnd = m_pRenderWidget->winId();
        hr = DXUTSetWindow(hwnd, hwnd, hwnd);
        BM_AssertHr(hr);

        hr = DXUTCreateDevice(true, m_pRenderWidget->width(), m_pRenderWidget->height(), DXUT_D3D9_DEVICE);
        BM_AssertHr(hr);
    }

    bool D3D9Renderer::IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed)
    {
        return true;
    }

    void D3D9Renderer::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc)
    {
    }

    void D3D9Renderer::OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc)
    {
    }

    void D3D9Renderer::OnLostDevice()
    {
    }

    void D3D9Renderer::OnDestroyDevice()
    {
    }

    bool CALLBACK D3D9Renderer::DXUT_IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext)
    {
        D3D9Renderer* pInstance = (D3D9Renderer*)pUserContext;
        return pInstance->IsDeviceAcceptable(pCaps, AdapterFormat, BackBufferFormat, bWindowed);
    }

    HRESULT CALLBACK D3D9Renderer::DXUT_OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
    {	
        D3D9Renderer* pInstance = (D3D9Renderer*)pUserContext;
        pInstance->OnCreateDevice(pd3dDevice, pBackBufferSurfaceDesc);
        return S_OK;
    }

    HRESULT CALLBACK D3D9Renderer::DXUT_OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
    {	
        D3D9Renderer* pInstance = (D3D9Renderer*)pUserContext;
        pInstance->OnResetDevice(pd3dDevice, pBackBufferSurfaceDesc);
        return S_OK;
    }

    void CALLBACK D3D9Renderer::DXUT_OnLostDevice(void* pUserContext)
    {
        D3D9Renderer* pInstance = (D3D9Renderer*)pUserContext;
        pInstance->OnLostDevice();
    }

    void CALLBACK D3D9Renderer::DXUT_OnDestroyDevice(void* pUserContext)
    {
        D3D9Renderer* pInstance = (D3D9Renderer*)pUserContext;
        pInstance->OnDestroyDevice();
    }

    void CALLBACK D3D9Renderer::DXUT_OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
    {
        D3D9Renderer* pInstance = (D3D9Renderer*)pUserContext;
        pInstance->Draw(pInstance->m_fDeltaTime);
    }
}
