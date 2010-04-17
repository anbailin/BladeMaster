#include "DCRenderHeader.h"

QuadGeometry::QuadGeometry()
{

}

QuadGeometry::~QuadGeometry()
{
    ReleaseResource();
}

namespace QuadGeoUtil
{
    struct QuadVertex
    {
        XMFLOAT3 pos;
        XMFLOAT2 texcoord;     
    };

    D3DVERTEXELEMENT9 quad_dcl[] = 
    {
        { 0, 0,   D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
        { 0, 12,  D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },       
        D3DDECL_END()
    };
}

void QuadGeometry::Init()
{
    //declaration
    FAIL_ASSERT(DEVICEPTR->CreateVertexDeclaration(QuadGeoUtil::quad_dcl, &mVertexDelcaration));

    //vertex buffer
    uint32 size = sizeof(QuadGeoUtil::QuadVertex) * 4;
    FAIL_ASSERT(DEVICEPTR->CreateVertexBuffer(size,0,0,D3DPOOL_MANAGED, &mVertexBuffer,0 ) );
    
    QuadGeoUtil::QuadVertex* lockPtr;
    FAIL_ASSERT(mVertexBuffer->Lock(0,0,(void**)&lockPtr,NULL));
    lockPtr[0].pos = XMFLOAT3(-1.0f, 1.0f, 1.0f);
    lockPtr[0].texcoord = XMFLOAT2(0.0f,0.0f);
    lockPtr[1].pos = XMFLOAT3(1.0f, 1.0f, 1.0f);
    lockPtr[1].texcoord = XMFLOAT2(1.0f,0.0f);
    lockPtr[2].pos = XMFLOAT3(-1.0f, -1.0f, 1.0f);
    lockPtr[2].texcoord = XMFLOAT2(0.0f,1.0f);
    lockPtr[3].pos = XMFLOAT3(1.0f, -1.0f, 1.0f);
    lockPtr[3].texcoord = XMFLOAT2(1.0f,1.0f);
    mVertexBuffer->Unlock();
}

void QuadGeometry::Render()const
{
    DEVICEPTR->SetVertexDeclaration(mVertexDelcaration);
    FAIL_ASSERT( DEVICEPTR->SetStreamSource( 0,mVertexBuffer,0,sizeof(QuadGeoUtil::QuadVertex) ) );
#ifdef RELEASE
    DEVICEPTR->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
#else
    FAIL_ASSERT(DEVICEPTR->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2));
#endif
}

void QuadGeometry::ReleaseResource()
{
    mVertexBuffer = NULL;
    mVertexDelcaration = NULL;
}