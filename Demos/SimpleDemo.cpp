#include "DCRenderHeader.h"
#include "EnginePCH.h"
#include "DCGameFrame_Base.h"
#include "DCWOWLoader.h"
#include "SimpleDemo.h"

namespace
{
    void LogDeviceReference(IDirect3DDevice9* device)
    {
        char str[256];
        sprintf_s(str,256,"reference count before reset is %d \n",device->Release());
        device->AddRef();
        LogToDebug(str);
    }
}

DCGameFrame_Base* SimpleDemo::Create()
{
    assert(mInstance==NULL);
    
    mInstance=new SimpleDemo();
    mInstance->Init();	

	return	mInstance;
}

SimpleDemo::SimpleDemo()
{

}


bool  SimpleDemo::IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
	IDirect3D9* pD3D = DXUTGetD3DObject(); 
	if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
		AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
		D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
	{
		return false;
	}

	// Must support pixel shader 1.1
	if( pCaps->PixelShaderVersion < D3DPS_VERSION( 1, 1 ) )
	{
		return false;
	}

	return true;
}


bool  SimpleDemo::ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext )
{
	if( (pCaps->DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		pCaps->VertexShaderVersion < D3DVS_VERSION(1,1) )
	{
		pDeviceSettings->BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	static bool s_bFirstTime = true;
	if( s_bFirstTime )
	{
		s_bFirstTime = false;
		if( pDeviceSettings->DeviceType == D3DDEVTYPE_REF )
			DXUTDisplaySwitchingToREFWarning();
	}

	return true;
}

HRESULT SimpleDemo::OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{	
	return S_OK;
}

HRESULT SimpleDemo::OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{	
    static bool FirstReset = true;

    //if(FirstReset)
    //{
    //    FirstReset = false;
    //    return S_OK;
    //}

    DCRenderer::GetInstance()->InitResource(pd3dDevice);
    LevelManager::GetInstance()->LoadMap("map");

	float fAspectRatio = pBackBufferSurfaceDesc->Width / (FLOAT)pBackBufferSurfaceDesc->Height;
	mvCameras[0]->SetProjParams( D3DX_PI/3, fAspectRatio, 0.001f, 100.0f );	

	return S_OK;
}

void SimpleDemo::OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	this->mvCameras[0]->FrameMove(fElapsedTime);
	this->mvCameras[1]->FrameMove(fElapsedTime);

    BMEngine::GetInstance()->Tick((float)fTime);	
}

void SimpleDemo::OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	
	// For our world matrix, we will just rotate the object about the y-axis.
	D3DXMATRIXA16 mxView, mxProj;
	
	mxView = (*this->mvCameras[0]->GetViewMatrix());
	mxProj = *this->mvCameras[0]->GetProjMatrix();
    
    SceneRenderer::GetInstance()->SetViewMatrix(mxView);
    SceneRenderer::GetInstance()->SetProjMatrix(mxProj);
    
    SceneRenderer::GetInstance()->RenderScene(*(LevelManager::GetInstance()->GetLevelInstance()));
}

LRESULT SimpleDemo::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )
{
	this->mvCameras[1]->HandleMessages(hWnd,uMsg,wParam,lParam);
	this->mvCameras[0]->HandleMessages(hWnd,uMsg,wParam,lParam);

	return 0;
}


void SimpleDemo::OnDestroyDevice( void* pUserContext )
{    
    ReleaseResource();
}


void SimpleDemo::OnLostDevice( void* pUserContext )
{
    static bool firstLostDevice = true;
    if(firstLostDevice)
    {
        firstLostDevice = false;
        return;
    }

    ReleaseResource();
}

void SimpleDemo::InitApp()
{
    //setup app config
	CFirstPersonCamera* pCamera=new CFirstPersonCamera;
	D3DXVECTOR3 vEye(  0.0f, 5.0f,-5.0f );
	D3DXVECTOR3 vAt(0.0f,0.0f,1.0f );
	pCamera->SetViewParams(&vEye,&vAt);
	pCamera->SetScalers(0.002f,5.0f);
	pCamera->SetRotateButtons(true,false,false,false);
	pCamera->SetResetCursorAfterMove(false);
	this->mvCameras.push_back(pCamera);

	CModelViewerCamera* pModelCamera=new CModelViewerCamera;
	pModelCamera->SetViewParams(&vEye,&vAt);
	pModelCamera->SetButtonMasks( MOUSE_RIGHT_BUTTON, MOUSE_WHEEL, MOUSE_MIDDLE_BUTTON );
	this->mvCameras.push_back(pModelCamera);
	
	DCSetupUtil::CreateInstance();
	DCSetupUtil::GetInstance()->SetGamePath();
	DCSetupUtil::GetInstance()->SetDataPath();

    //init engine
    BMEngine::CreateInstance();    
    BMEngine::GetInstance()->Init();    

    //wow file related init
    assert(DCWOWLoader::GetInstance() == NULL);
    DCWOWLoader::CreateInstance();
    DCWOWLoader::GetInstance()->Init();

	DXUTInit( true, true, true ); // Parse the command line, handle the default hotkeys, and show msgboxes
	DXUTCreateWindow( L"MODEL" );
	DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 1024, 576, NULL,NULL);
}

void SimpleDemo::ReleaseResource()
{
    DCRenderer::GetInstance()->ReleaseResource();
    BMEngine::GetInstance()->ReleaseResource();
}

SimpleDemo::~SimpleDemo()
{
    ReleaseResource();
    const u32 cameraNum = mvCameras.size();
    for(u32 i=0; i<cameraNum; i++)
    {
        SAFE_DELETE(mvCameras[i]);
    }

    mvCameras.clear();
}