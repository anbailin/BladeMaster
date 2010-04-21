#ifndef CORE_H
#define CORE_H

#ifndef UNICODE
#define UNICODE 1
#endif

#include <string>
#include <memory>

//--------system-------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

#include <mmsystem.h>
#include <stdio.h>

//---------public lib--------------
#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>

//--------stl-----------------------
#include <algorithm>
#include <string>
#include <xstring>
#include <vector>
#include <map>
#include <Utility>
#include <complex>


//using namespace std;
#pragma warning( disable : 4995 )
#pragma warning( disable : 4131 )
//--------core-----------------------
//common
#include "TypeDefine.h"
//#include "Singleton.h"

//math
#include "xnamath.h"
#include "MathBasic.h"
#include "Matrix.h"
//string
#include "BMString.h"
//container
#include "AlignedContainerAllocator.h"
#include "Container.h"
#include "mpq_lib.h"
#include "BMMemory.h"
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

//--------tinyxml-------------------
#define TIXML_USE_STL
#include "TinyXML/tinyxml.h"
#include "TinyXML/tinystr.h"

#endif