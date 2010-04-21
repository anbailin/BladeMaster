#pragma once

#include "Game.h"
#include "MainWindow.h"
#include "DCRenderHeader.h"

class CBaseCamera;

class App : public BM::GameApplication
{
    Q_OBJECT

public:
    App(int argc, char* argv[]);

private:
    virtual bool Init();
    virtual void Tick();
    virtual void Exit();

    void ReleaseResource();

private:
    MainWindow      m_MainWindow;
    CBaseCamera*    m_pCamera;

public:
    static App& Instance() { return *(qobject_cast<App*>(instance())); }

public:
    static bool     CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
    static bool     CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext );
    static HRESULT  CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
    static HRESULT  CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
    static void     CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
    static void     CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
    static LRESULT  CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext );
    static void     CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext ){}
    static void     CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext ){}
    static void     CALLBACK OnLostDevice( void* pUserContext );
    static void     CALLBACK OnDestroyDevice( void* pUserContext );

public:
    static bool Pause;
};
