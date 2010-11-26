#pragma once

struct DCVertPosWNTC
{
	XMFLOAT3	pos;
	u8		weight[4];
	u8		bone[4];
	XMFLOAT3	normal;
	XMFLOAT2	texcoord;
	u32		color0;
	u32		color1;
};

struct DCVertPosWNTC2
{
	XMFLOAT3	pos;
	float		weight[4];
	u8		bone[4];
	XMFLOAT3	normal;
	XMFLOAT2	texcoord;
	u32		color0;
	u32		color1;
};

struct DCVertPosColor
{
	XMFLOAT3	pos;
	u32		color;
};

struct DCVertPosNorTex
{
	XMFLOAT3	pos;
	XMFLOAT3	normal;
	XMFLOAT2	tex;
};

typedef DCVertPosWNTC	MDXModelVert;
typedef DCVertPosNorTex MDXModelVertSys;
typedef DCVertPosColor	BoneVert;

//--------------------------------------------------------------------------------------------
typedef ComPtr<IDirect3DVertexBuffer9>	VertexBufferPtr;
typedef ComPtr<IDirect3DIndexBuffer9>	IndexBufferPtr;

typedef ComPtr<IDirect3DPixelShader9>	PixelShaderPtr;
typedef ComPtr<IDirect3DVertexShader9>  VertexShaderPtr;

typedef ComPtr<IDirect3DVertexDeclaration9> VertexDeclPtr;

typedef ComPtr<IDirect3DSurface9>       SurfacePtr;
typedef ComPtr<IDirect3DTexture9>       TexturePtr;
//--------------------------------------------------------------------------------------------
typedef std::vector<MDXModelVertSys>	MDXVertArraySys;
typedef std::vector<DCVertPosWNTC2>		MDXVertArray;

typedef std::vector<XMMATRIX,AlignmentAllocator<XMMATRIX,16>> MatrixPool;