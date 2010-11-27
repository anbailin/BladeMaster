#include "AppPrivate.h"
#include "MainWindow.h"
#include "App.h"

bool App::Pause = false;

App::App(int argc, char* argv[])
    : GameApplication("TestApp", argc, argv)
{
}

App::~App()
{
    SAFE_DELETE(m_pMainWindow);
}

bool App::InitApp()
{
    if (!GameApplication::InitApp())
    {
        return false;
    }

    m_pMainWindow = new MainWindow();
    m_pMainWindow->show();

    QWidget* widget = m_pMainWindow->GetRenderWidget();	
	assert(widget);
	SetRenderWidget(widget);

    return true;
}

bool App::InitEngine()
{
    DCSetupUtil::CreateInstance();
    DCSetupUtil::GetInstance()->SetGamePath();
    DCSetupUtil::GetInstance()->SetDataPath();

    //wow file related init
    DCWOWLoader::CreateInstance();
    DCWOWLoader::GetInstance()->Init();

    if (!GameApplication::InitEngine())
    {
        return false;
    }

    return true;
}

void App::Exit()
{
    //DCRenderer::GetInstance()->ReleaseResource();
    //BMEngine::GetInstance()->ReleaseResource();

    //SAFE_DELETE(m_pCamera);

    GameApplication::Exit();
}

void App::Tick(f32 fDeltaTime)
{
    GameApplication::Tick(fDeltaTime);

    //// Render a frame during idle time (no messages are waiting)
    //DXUTRender3DEnvironment();
}

void App::ReleaseResource()
{
    //DCRenderer::GetInstance()->ReleaseResource();
    //BMEngine::GetInstance()->ReleaseResource();
}

//bool CALLBACK App::IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
//{
//    IDirect3D9* pD3D = DXUTGetD3DObject(); 
//    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
//        AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
//        D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
//    {
//        return false;
//    }
//
//     Must support pixel shader 1.1
//    if( pCaps->PixelShaderVersion < D3DPS_VERSION( 1, 1 ) )
//    {
//        return false;
//    }
//
//    return true;
//}
//
//
//bool CALLBACK App::ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext )
//{
//    if( (pCaps->DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
//        pCaps->VertexShaderVersion < D3DVS_VERSION(1,1) )
//    {
//        pDeviceSettings->BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
//    }
//
//    static bool s_bFirstTime = true;
//    if( s_bFirstTime )
//    {
//        s_bFirstTime = false;
//        if( pDeviceSettings->DeviceType == D3DDEVTYPE_REF )
//            DXUTDisplaySwitchingToREFWarning();
//    }
//
//    return true;
//}
//
//HRESULT CALLBACK App::OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
//{	
//    return S_OK;
//}
//
//HRESULT CALLBACK App::OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
//{	
//    static bool FirstReset = true;
//
//    //if(FirstReset)
//    //{
//    //    FirstReset = false;
//    //    return S_OK;
//    //}
//
//    DCRenderer::GetInstance()->InitResource(pd3dDevice);
//    LevelManager::GetInstance()->LoadMap("map");
//
//    float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;
//    App::GetInstance()->m_pCamera->SetProjParams( D3DX_PI/3, fAspectRatio, 0.001f, 100.0f );	
//
//    return S_OK;
//}
//
//void CALLBACK App::OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
//{
//    if(Pause == false)
//    {	
//        DXUTTimer::SetTime(fTime);
//        DXUTTimer::SetElapsedTime(fElapsedTime);
//    }
//
//    App::GetInstance()->m_pCamera->FrameMove(fElapsedTime);
//
//    BMEngine::GetInstance()->Tick((float)fTime);	
//}
//
//void CALLBACK App::OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
//{
//
//    // For our world matrix, we will just rotate the object about the y-axis.
//    D3DXMATRIXA16 mxView, mxProj;
//
//    mxView = *Instance().m_pCamera->GetViewMatrix();
//    mxProj = *Instance().m_pCamera->GetProjMatrix();
//
//    SceneRenderer::GetInstance()->SetViewMatrix(mxView);
//    SceneRenderer::GetInstance()->SetProjMatrix(mxProj);
//
//    SceneRenderer::GetInstance()->RenderScene(*(LevelManager::GetInstance()->GetLevelInstance()));
//}
//
//LRESULT CALLBACK App::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )
//{
//    App::GetInstance()->m_pCamera->HandleMessages(hWnd,uMsg,wParam,lParam);
//    return 0;
//}
//
//
//void CALLBACK App::OnDestroyDevice( void* pUserContext )
//{    
//    App::GetInstance()->ReleaseResource();
//    DCRenderer::DeleteInstance();
//}
//
//void CALLBACK App::OnLostDevice( void* pUserContext )
//{
//    static bool firstLostDevice = true;
//    if(firstLostDevice)
//    {
//        firstLostDevice = false;
//        return;
//    }
//
//    App::GetInstance()->ReleaseResource();
//}
