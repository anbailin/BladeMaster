#pragma once

#include "Build.h"

//////////////////////////////////////////////////////////////////////////
// DLL Import / Export
#ifdef CORE_LIB
#   define CORE_API __declspec(dllexport)
#else
#   define CORE_API __declspec(dllimport)
#endif
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// STD
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory>
#include <memory.h>
#include <math.h>
#include <float.h>
#include <algorithm>
#include <vector>
#include <map>
#include <Utility>
#include <complex>
#include <string>
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Windows
#include <windows.h>
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// DirectX
#include <dxerr.h>
#include <dxdiag.h>
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")
#if BM_USE_D3D9
#   include <d3d9.h>
#   include <d3dx9.h>
#   pragma comment(lib, "d3d9.lib")
#   if BM_DEBUG
#       pragma comment( lib, "d3dx9d.lib" )
#   else
#       pragma comment( lib, "d3dx9.lib" )
#   endif
#elif BM_USE_D3D10
#   include <d3d10.h>
#   include <d3dx10.h>
#   pragma comment(lib, "d3d10.lib")
#   if BM_DEBUG
#       pragma comment( lib, "d3dx10d.lib" )
#   else
#       pragma comment( lib, "d3dx10.lib" )
#   endif
#elif BM_USE_D3D11
#   include <d3d11.h>
#   include <d3dx11.h>
#   pragma comment(lib, "d3d11.lib")
#   if BM_DEBUG
#       pragma comment( lib, "d3dx11d.lib" )
#   else
#       pragma comment( lib, "d3dx11.lib" )
#   endif
#else
#   error "Invalid DirectX Configuration"
#endif
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Qt
#include <QtCore/QtCore>
#include <QtGui/QtGui>
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// BM
#include "Types.h"
#include "Utilities.h"
#include "Maths.h"
//////////////////////////////////////////////////////////////////////////
