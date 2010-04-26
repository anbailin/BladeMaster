#include "GraphicsPrivate.h"
#include "D3D9RenderWindow.h"
#include "D3D9Renderer.h"

namespace BM
{
    D3D9Renderer::D3D9Renderer()
    {
        m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
        BM_Assert(m_pD3D != NULL);

        m_pD3DDevice = NULL;
    }

    D3D9Renderer::~D3D9Renderer()
    {
        SafeRelease(m_pD3DDevice);
        SafeRelease(m_pD3D);
    }

    void D3D9Renderer::Init(QWidget* pRenderWidget)
    {
        Renderer::Init(pRenderWidget);

        //m_pRenderWindow = new D3D9RenderWindow(pRenderWidget);

        //CreateD3DDevice();
    }

    void D3D9Renderer::Exit()
    {
    }

    void D3D9Renderer::Tick()
    {
    }

    void D3D9Renderer::CreateD3DDevice()
    {
        Application& app = Application::Instance();

        bool full_screen = app.GetSetting("Graphics", "Renderer/FullScreen", false).toBool();

        ZeroMemory(&m_PresentParameters, sizeof(D3DPRESENT_PARAMETERS));

        m_PresentParameters.Windowed                        = !app.GetSetting("Graphics", "Renderer/FullScreen", false).toBool();
        if (m_PresentParameters.Windowed)
        {
            m_PresentParameters.BackBufferWidth             = m_pRenderWindow->Width();
            m_PresentParameters.BackBufferHeight            = m_pRenderWindow->Height();
            m_PresentParameters.FullScreen_RefreshRateInHz  = 0;
        }
        else
        {
            m_PresentParameters.BackBufferWidth             = app.GetSetting("Graphics", "Renderer/FullScreenResX", 1280).toInt();
            m_PresentParameters.BackBufferHeight            = app.GetSetting("Graphics", "Renderer/FullScreenResY", 1024).toInt();
            m_PresentParameters.FullScreen_RefreshRateInHz  = app.GetSetting("Graphics", "Renderer/FullScreenRefreshRate", 60).toInt();
        }
        m_PresentParameters.BackBufferCount                 = 1;
        m_PresentParameters.BackBufferFormat                = D3DFMT_X8R8G8B8;
        m_PresentParameters.EnableAutoDepthStencil          = TRUE; 
        m_PresentParameters.AutoDepthStencilFormat          = D3DFMT_D24S8;
        m_PresentParameters.SwapEffect                      = D3DSWAPEFFECT_DISCARD; 
        m_PresentParameters.PresentationInterval            = D3DPRESENT_INTERVAL_IMMEDIATE;
        m_PresentParameters.MultiSampleType                 = D3DMULTISAMPLE_NONE;
        m_PresentParameters.MultiSampleQuality              = 0;

        HRESULT hr = m_pD3D->CreateDevice
            (
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            m_pRenderWindow->Handle(),
            D3DCREATE_HARDWARE_VERTEXPROCESSING,
            &m_PresentParameters,
            &m_pD3DDevice
            );
        BM_Assert(SUCCEEDED(hr));
    }
}
