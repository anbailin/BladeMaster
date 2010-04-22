#pragma once

#include "Build.h"

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

// DirectX
#include <dxerr.h>
#include <dxdiag.h>
#if BM_USE_D3D9
#   include <d3d9.h>
#   include <d3dx9.h>
#elif BM_USE_D3D10
#   include <d3d10.h>
#   include <d3dx10.h>
#elif BM_USE_D3D11
#   include <d3d11.h>
#   include <d3dx11.h>
#endif

// Qt
#include <QtCore/QtCore>
#include <QtGui/QtGui>
