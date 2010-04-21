#pragma once

//////////////////////////////////////////////////////////////////////////
// DLL Import / Export
#ifdef GAME_LIB
#   define GAME_API __declspec(dllexport)
#else
#   define GAME_API __declspec(dllimport)
#endif
//////////////////////////////////////////////////////////////////////////

// Qt
#include <QtCore/QtCore>
#include <QtGui/QtGui>

// BM
#include "Core.h"
#include "Graphics.h"
#include "Engine.h"
