#pragma once
#include "Core.h"
#include "DXUT\dxstdafx.h"
#include <vector>
class DCGameFrame_Base{
public://method	
	virtual ~DCGameFrame_Base(){}
	//----------------------------------------------------------------------------------------------------------------------------------
	virtual bool    IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )=0;
	virtual bool    ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext )=0;
	virtual void    OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )=0;
	virtual void    OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )=0;	
	virtual void    KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )=0;
	virtual void    OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )=0;
	virtual void    OnLostDevice( void* pUserContext )=0;
	virtual void    OnDestroyDevice( void* pUserContext )=0;
	virtual HRESULT OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )=0;
	virtual HRESULT OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )=0;
	virtual LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext )=0;
	//----------------------------------------------------------------------------------------------------------------------------------
	void								Init();
	virtual void						InitApp()=0;	
	static DCGameFrame_Base*			Get(){return mInstance;}	
public://data
	static DCGameFrame_Base				*mInstance;		
};