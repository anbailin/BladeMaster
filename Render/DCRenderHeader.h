#pragma once
#pragma warning (disable:4819)
#pragma warning (disable:4275)
#pragma warning (disable:4251)

//--------------c includes
#include <assert.h>
//--------------d3d9 includes
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

//--------------DC includes

#include "Core.h"//core

#include "dxut/dxstdafx.h"

#include "DCRenderType.h"
#include "DCRenderState.h"
#include "DCRenderSetter.h"

#include "DCRenderer.h"

#include "DCSurface.h"
#include "DCTexture.h"

#include "DCGeometry.h"

#include "DCMaterial.h"

#include "DCSubModel.h"
#include "DCModel.h"

#include "Terrain.h"

#include "DCShaderManager.h"

#include "DCTranslator.h"
#include "DCModelInstance.h"

#include "Guard.h"
#include "DCDef.h"
#include "DCRenderUtils.h"
#include "QuadGeometry.h"
#include "DCMapTile.h"
#include "DCWMO.h"

//post fx
#include "PostFXRenderer.h"

//Utility
#include "ShaderLoader.h"
#include "VertexDeclarationManager.h"