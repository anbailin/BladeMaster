#include "GraphicsPrivate.h"

//---------DCSubModel------------------------------------------------------------------------------

DCSubModel::DCSubModel():
mLod(0)
{

}


void DCSubModel::Draw()
{
	BM_AssertHr( DEVICEPTR->SetIndices(mIndexbuffer) );
	
	uint32 size = mMaterials.size();
	for(uint32 i=0;i<size;i++)
	{
		DCMaterialPtr& mat = mMaterials[i];
		DCRenderer::Instance().ApplyTexture(0,mat->GetTexturePtr());

		DCRenderSetter::Get()->ApplyAlphaBlend(mat->GetAlphaBlendState());
		DCRenderSetter::Get()->ApplyAlphaTest(mat->GetAlphaTestState());

		mat->GetGeometryPtr()->Draw();
	}
}


void DCSubModel::InitIndexBuffer(const uint16* addr, uint32 count)
{
	IndexBufferPtr ptr;

	BM_AssertHr(DEVICEPTR->CreateIndexBuffer(sizeof(uint16)*count, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ptr, 0));

	void* lockPtr;
	BM_AssertHr(ptr->Lock(0,0,(void**)&lockPtr,0));
	memcpy(lockPtr,addr,count*sizeof(uint16));	
	ptr->Unlock();

	mIndexbuffer = ptr;//this will cause the release of the original index buffer;
	mIndexCount = count;
}

DCSubModel::~DCSubModel()
{
}