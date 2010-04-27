#include "DCRenderHeader.h"

BMTerrain::BMTerrain()
{
    Init();
}

namespace
{
    const WCHAR* g_terrain_shader_path = L"..\\Data\\Shader\\Terrain.hlsl";

    struct TerrainVertex
    {
        XMFLOAT3 pos;
        XMFLOAT3 normal;
        XMBYTE4  color;
    };

    D3DVERTEXELEMENT9 terrain_dcl[] = 
    {
        { 0, 0,   D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
        { 0, 12,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,			0 },
        { 0, 24,  D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		    0 },        
        D3DDECL_END()
    };

    IDirect3DVertexDeclaration9* terrain_declaration = NULL;
    IDirect3DPixelShader9* terrain_g_ps = NULL;
    IDirect3DVertexShader9* terrain_g_vs = NULL;

    const float kTerrainSize = 50.0f;
}

void BMTerrain::Init()
{
    //vertex buffer
    uint32 length = sizeof(TerrainVertex)*4;
    BM_AssertHr(DEVICEPTR->CreateVertexBuffer(length,0,0,D3DPOOL_MANAGED, &mVB,0 ) );

    TerrainVertex* vbLockPtr;
    BM_AssertHr(mVB->Lock(0,0,(void**)&vbLockPtr,NULL));
    vbLockPtr[0].pos = XMFLOAT3(-kTerrainSize,0,kTerrainSize);
    vbLockPtr[0].normal = XMFLOAT3(0,1,0);
    vbLockPtr[0].color = 0xff0000ff;

    vbLockPtr[1].pos = XMFLOAT3(kTerrainSize,0,kTerrainSize);
    vbLockPtr[1].normal = XMFLOAT3(0,1,0);
    vbLockPtr[1].color = 0xffff00ff;
    
    vbLockPtr[2].pos = XMFLOAT3(kTerrainSize,0,-kTerrainSize);
    vbLockPtr[2].normal = XMFLOAT3(0,1,0);
    vbLockPtr[2].color = 0xffffff00;

    vbLockPtr[3].pos = XMFLOAT3(-kTerrainSize,0,-kTerrainSize);
    vbLockPtr[3].normal = XMFLOAT3(0,1,0);
    vbLockPtr[3].color = 0xff00ff88;
    mVB->Unlock();

    //index buffer
    IndexBufferPtr ibPtr;
    BM_AssertHr(DEVICEPTR->CreateIndexBuffer(sizeof(uint16)*6, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ibPtr, 0));
    uint16* ibLockPtr;
    BM_AssertHr(ibPtr->Lock(0,0,(void**)&ibLockPtr,0));
    ibLockPtr[0] = 0;
    ibLockPtr[1] = 1;
    ibLockPtr[2] = 2;
    ibLockPtr[3] = 0;
    ibLockPtr[4] = 2;
    ibLockPtr[5] = 3;
    ibPtr->Unlock();
    mIB = ibPtr;
}

BMTerrain::~BMTerrain()
{
    SafeRelease(terrain_declaration);
    SafeRelease(terrain_g_ps);
    SafeRelease(terrain_g_vs);
}

void BMTerrain::Draw(D3DXMATRIXA16* worldMtx,D3DXMATRIXA16* viewMtx, D3DXMATRIXA16* projMtx)
{
    //pix_event g( DXUT_PERFEVENTCOLOR, L"terrain" );

    static float TimeStamp = 0.0f;
    //TimeStamp += 1.0f;

    VertexDeclareManager::Instance().ApplyVertexDeclaration(VertexTypePosNorColor);
    ShaderLoader::Instance().ApplyShader(ShaderLoader::Instance().terrain_vs_id, ShaderLoader::Instance().terrain_ps_id);
 
    DEVICEPTR->SetVertexShaderConstantF(0,(float*)(worldMtx),4);
    DEVICEPTR->SetVertexShaderConstantF(4,(float*)(viewMtx),4);
    DEVICEPTR->SetVertexShaderConstantF(8,(float*)(projMtx),4);
    DEVICEPTR->SetPixelShaderConstantF(0,(float*)(&TimeStamp),1);


    BM_AssertHr( DEVICEPTR->SetStreamSource( 0,mVB,0,sizeof(TerrainVertex) ) );
    BM_AssertHr( DEVICEPTR->SetIndices(mIB) );
#ifdef RELEASE
    DEVICEPTR->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4,0,2);
#else
    BM_AssertHr(DEVICEPTR->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,4,0,2));
#endif
}