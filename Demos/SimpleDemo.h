class SimpleDemo:public DCGameFrame_Base
{
public:
	static DCGameFrame_Base*			Create();

	virtual bool     IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
	virtual bool     ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext );
	virtual HRESULT  OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
	virtual HRESULT  OnResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
	virtual void     OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
	virtual void     OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
	virtual LRESULT  MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext );
	virtual void     KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext ){}
	virtual void     OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext ){}
	virtual void     OnLostDevice( void* pUserContext );
	virtual void     OnDestroyDevice( void* pUserContext );

	virtual void	 InitApp();

	SimpleDemo();
	~SimpleDemo();

protected:
    void ReleaseResource();

private:
	std::vector<CBaseCamera*>	mvCameras;
	std::string					mParentPath;
	std::string					mFileName;
};