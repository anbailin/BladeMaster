#pragma once

//////////////////////////////////////////////////////////////////////////
// DLL Import / Export
#ifdef CORE_LIB
#   define CORE_API __declspec(dllexport)
#else
#   define CORE_API __declspec(dllimport)
#endif
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

// Windows
#include <windows.h>

// Qt
#include <QtCore/QtCore>
#include <QtGui/QtGui>

// BM
#include "Build.h"
#include "Types.h"
#include "Utilities.h"
