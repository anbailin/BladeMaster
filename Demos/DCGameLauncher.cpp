#include "DCRenderHeader.h"
#include "EnginePCH.h"
#include "DCGameFrame_Base.h"
#include "DCWOWLoader.h"
#include "SimpleDemo.h"

#define ROCKET SimpleDemo

namespace
{
	bool pause = false;
}
//----------------------------------------------------------------------------------------------------------------------------------
bool    CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
bool    CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext );
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
void    CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
void    CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext );
void    CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
void    CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
void    CALLBACK OnLostDevice( void* pUserContext );
void    CALLBACK OnDestroyDevice( void* pUserContext );
//----------------------------------------------------------------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	DXUTSetCallbackDeviceCreated( OnCreateDevice );
	DXUTSetCallbackDeviceReset( OnResetDevice );
	DXUTSetCallbackDeviceLost( OnLostDevice );
	DXUTSetCallbackDeviceDestroyed( OnDestroyDevice );
	DXUTSetCallbackMsgProc( MsgProc );
	DXUTSetCallbackKeyboard( KeyboardProc );
	DXUTSetCallbackFrameRender( OnFrameRender );
	DXUTSetCallbackFrameMove( OnFrameMove );	
	ROCKET::Create();
	DXUTMainLoop();
	return DXUTGetExitCode();
}
//----------------------------------------------------------------------------------------------------------------------------------
bool CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, 
								 D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
	return ROCKET::Get()->IsDeviceAcceptable(pCaps, AdapterFormat,BackBufferFormat, bWindowed, pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext )
{
	return ROCKET::Get()->ModifyDeviceSettings(pDeviceSettings,pCaps,pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
//the places we create engine
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	return ROCKET::Get()->OnCreateDevice(pd3dDevice,pBackBufferSurfaceDesc,pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
							   const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	return ROCKET::Get()->OnResetDevice(pd3dDevice,pBackBufferSurfaceDesc,pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{	
	if(pause == false)
	{	
		DXUTTimer::SetTime(fTime);
		DXUTTimer::SetElapsedTime(fElapsedTime);
	}

	ROCKET::Get()->OnFrameMove(pd3dDevice,fTime,fElapsedTime,pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	ROCKET::Get()->OnFrameRender(pd3dDevice,fTime,fElapsedTime,pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )
{
	return ROCKET::Get()->MsgProc(hWnd, uMsg, wParam, lParam, pbNoFurtherProcessing, pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
void CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
	ROCKET::Get()->KeyboardProc(nChar,bKeyDown,bAltDown,pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	ROCKET::Get()->OnGUIEvent(nEvent, nControlID, pControl, pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
void CALLBACK OnLostDevice( void* pUserContext )
{
   ROCKET::Get()->OnLostDevice(pUserContext);
}
//----------------------------------------------------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
	ROCKET::Get()->OnDestroyDevice(pUserContext);
	DCRenderer::DestroyInstance();
}