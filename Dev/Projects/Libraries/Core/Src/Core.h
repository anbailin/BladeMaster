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
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Qt
#pragma warning( push )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4512 )
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#pragma warning( pop )
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Core part

//using namespace BM;
#include "Singleton.h"
#include "Types.h"
#include "Utilities.h"
#include "Maths.h"

//container
#include "TArray.h"
#include "AlignedContainerAllocator.h"

//math
#include "xnamath.h"
#include "MathBasic.h"
#include "mpq_lib.h"

//--------utils---------------------
#include "Util/BMLog.h"
#include "Util/DCCoreUtils.h"
#include "Util/RefObject.h"
#include "Util/DCComPtr.h"
#include "Util/IDCTimer.h"
#include "Util/IDCTimeSource.h"
#include "Util/DCTimer.h"
#include "Util/DCTimerManager.h"
#include "Util/DCTimeSource_win.h"
#include "Util/DXUTTimer.h"
#include "Util/DCTypeDef.h"
#include "Util/DCRGBAColor8.h"
#include "Util/StrUtil.h"
#include "Util/StrTokenizer.h"


#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "Quaternion.h"

#include "Color.h"
#include "Angle.h"

#include "Point.h"
#include "Size.h"
#include "Rectangle.h"

#include "Timer.h"
#include "Singleton.h"
#include "Application.h"

//-------tinyxml-------------------

#ifndef TIXML_USE_STL
	#define TIXML_USE_STL
#endif

#include "TinyXML/tinyxml.h"
#include "TinyXML/tinystr.h"