#pragma once

//#include "Build.h"
//
////////////////////////////////////////////////////////////////////////////
//// DLL Import / Export
//#ifdef CORE_LIB
//#   define CORE_DLL __declspec(dllexport)
//#else
//#   define CORE_DLL __declspec(dllimport)
//#endif
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
//// STD
//#include <stdlib.h>
//#include <stdio.h>
//#include <assert.h>
//#include <memory>
//#include <memory.h>
//#include <math.h>
//#include <float.h>
//#include <algorithm>
//#include <vector>
//#include <map>
//#include <Utility>
//#include <complex>
//#include <string>
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
//// Windows
//#include <windows.h>
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
//// DirectX
//#include <dxerr.h>
//#include <dxdiag.h>
//#include <d3d9.h>
//#include <d3dx9.h>
//#include <d3d11.h>
//#include <d3dx11.h>
//#pragma comment(lib, "dxerr.lib")
//#pragma comment(lib, "dxguid.lib")
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3d11.lib")
//#if BM_DEBUG
//#   pragma comment(lib, "d3dx9d.lib")
//#   pragma comment(lib, "d3dx11d.lib")
//#else
//#   pragma comment(lib, "d3dx9.lib")
//#   pragma comment(lib, "d3dx11.lib")
//#endif
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
//// Qt
//#include <QtCore/QtCore>
//#include <QtGui/QtGui>
////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////
//// Core part
//
////#pragma warning( disable : 4995 )
////#pragma warning( disable : 4131 )
//using namespace BM;
//
//#include "Types.h"
//#include "Utilities.h"
//#include "Maths.h"
//
////container
//#include "AlignedContainerAllocator.h"
//
////#define CORE_DLL
////#define UTIL_DLL
////#define RENDER_DLL
////#define ENGINE_DLL
////#define FILESYS_DLL
////#define ENGINE_DLL
//
////math
//#include "xnamath.h"
//#include "MathBasic.h"
//#include "mpq_lib.h"
//
////--------utils---------------------
//#include "Util/BMLog.h"
//#include "Util/DCCoreUtils.h"
//#include "Util/RefObject.h"
//#include "Util/DCComPtr.h"
//#include "Util/IDCTimer.h"
//#include "Util/IDCTimeSource.h"
//#include "Util/DCTimer.h"
//#include "Util/DCTimerManager.h"
//#include "Util/DCTimeSource_win.h"
//#include "Util/DXUTTimer.h"
//#include "Util/DCTypeDef.h"
//#include "Util/DCRGBAColor8.h"
//
//#include "Singleton.h"
//////////////////////////////////////////////////////////////////////////
