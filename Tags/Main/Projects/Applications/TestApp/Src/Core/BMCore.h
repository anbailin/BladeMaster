#pragma once

#include "Core.h"

using namespace BM;

//#pragma warning( disable : 4995 )
//#pragma warning( disable : 4131 )

#define CORE_DLL
#define UTIL_DLL
#define RENDER_DLL
#define ANIM_DLL
#define FILESYS_DLL
#define ENGINE_DLL

//math
#include "xnamath.h"
#include "MathBasic.h"

//container
#include "AlignedContainerAllocator.h"

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
