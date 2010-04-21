#pragma once

//////////////////////////////////////////////////////////////////////////
// DLL Import / Export
#ifdef GRAPHICS_LIB
#   define GRAPHICS_API __declspec(dllexport)
#else
#   define GRAPHICS_API __declspec(dllimport)
#endif
//////////////////////////////////////////////////////////////////////////

// Qt
#include <QtCore/QtCore>
#include <QtGui/QtGui>

// BM
#include "Core.h"
