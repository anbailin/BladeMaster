#pragma once

#pragma warning( disable : 4819 )
#include<d3dx9.h>
#pragma warning( default : 4819 )

// copied from the .mdl docs? this might be completely wrong
enum BlendModes 
{
	BM_OPAQUE,
	BM_TRANSPARENT,
	BM_ALPHA_BLEND,
	BM_ADDITIVE,
	BM_ADDITIVE_ALPHA,
	BM_MODULATE
};

//Vertex type definition--------------------------------------------------------------------------
#define D3DFVF_DC_POS_DIFFUSE_TEX1 (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
struct DCVERTEX_PDT
{
	D3DXVECTOR3 position; // The position
	D3DCOLOR    diffuse;    // The color
	FLOAT       tu, tv;   // The texture coordinates
};

