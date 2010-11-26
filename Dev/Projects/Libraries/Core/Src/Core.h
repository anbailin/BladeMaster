#pragma once
/*
 *	core public interface for modules that depends on core proj
 */
#include "CorePrivate.h"
#include "Singleton.h"

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
#include "BMString.h"
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
#include "TinyXML/tinyxml.h"
#include "TinyXML/tinystr.h"