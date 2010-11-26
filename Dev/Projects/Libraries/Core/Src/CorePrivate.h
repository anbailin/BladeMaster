/**
 *  served as pch inside core proj
 */

#pragma once
//warning disable
#pragma warning( disable : 4995 )
#pragma warning( disable : 4131 )
#pragma warning( disable : 4251 )


#include "Build.h"

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
#include <hash_map>
#include <Utility>
#include <complex>
#include <string>
#include <windows.h>
#include <winbase.h>
#include <assert.h>
#include <stack>

#include <tchar.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Windows
#include <windows.h>
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// DirectX
#include <dxerr.h>
#include <dxdiag.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3d11.h>
#include <d3dx11.h>
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3d11.lib")
#if BM_DEBUG
#   pragma comment(lib, "d3dx9d.lib")
#   pragma comment(lib, "d3dx11d.lib")
#else
#   pragma comment(lib, "d3dx9.lib")
#   pragma comment(lib, "d3dx11.lib")
#endif

//basic part inside core
#include "Build.h"
#include "Types.h"
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Qt
#pragma warning( push )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4512 )
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#pragma warning( pop )

//tiny xml
#ifndef TIXML_USE_STL
    #define TIXML_USE_STL
#endif