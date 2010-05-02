#include "GraphicsPrivate.h"

namespace
{
    const D3DVERTEXELEMENT9 dcl_PosColor[] = 
    {
        { 0,  0,   D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
        { 0, 12,   D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,			0 },
        D3DDECL_END()
    };

    const D3DVERTEXELEMENT9 dcl_PosWNTC[] = 
    {
        { 0, 0,   D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
        { 0, 12,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT ,	0 },
        { 0, 16,  D3DDECLTYPE_UBYTE4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES,	0 },
        { 0, 20,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,			0 },
        { 0, 32,  D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
        { 0, 40,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,			0 },
        { 0, 44,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,			1 },
        D3DDECL_END()
    };

    const D3DVERTEXELEMENT9 dcl_PosNorTex[] = 
    {
        { 0, 0,   D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
        { 0, 12,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,			0 },
        { 0, 24,  D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
        D3DDECL_END()
    };

    D3DVERTEXELEMENT9 dcl_PosNorColor[] = 
    {
        { 0, 0,   D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
        { 0, 12,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,			0 },
        { 0, 24,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		    0 },        
        D3DDECL_END()
    };
}

BM_SINGLETON_DEFINE(VertexDeclareManager);

void VertexDeclareManager::CreateResource()
{
    BM_AssertHr(DEVICEPTR->CreateVertexDeclaration(dcl_PosColor, &mDeclarations[VertexTypePosColor]));
    BM_AssertHr(DEVICEPTR->CreateVertexDeclaration(dcl_PosWNTC, &mDeclarations[VertexTypePosWNTC]));
    BM_AssertHr(DEVICEPTR->CreateVertexDeclaration(dcl_PosNorTex, &mDeclarations[VertexTypePosNorTex]));
    BM_AssertHr(DEVICEPTR->CreateVertexDeclaration(dcl_PosNorColor, &mDeclarations[VertexTypePosNorColor]));
}

void VertexDeclareManager::ReleaseResource()
{
    for(uint32 i=0; i<VertexTypeCount; i++)
    {
        mDeclarations[i] = NULL;
    }
}

void VertexDeclareManager::ApplyVertexDeclaration(DCVertexType type)
{
    BM_AssertHr(DEVICEPTR->SetVertexDeclaration(mDeclarations[type]));
}

VertexDeclareManager::VertexDeclareManager()
{

}

VertexDeclareManager::~VertexDeclareManager()
{
    ReleaseResource();
}