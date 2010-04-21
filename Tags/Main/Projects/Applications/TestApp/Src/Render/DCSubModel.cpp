#include "DCRenderHeader.h"

//---------DCSubModel------------------------------------------------------------------------------

DCSubModel::DCSubModel():
mLod(0)
{

}


void DCSubModel::Draw()
{
	FAIL_ASSERT( DEVICEPTR->SetIndices(mIndexbuffer) );
	
	uint32 size = mMaterials.size();
	for(uint32 i=0;i<size;i++)
	{
		DCMaterialPtr& mat = mMaterials[i];
		DCRenderer::GetInstance()->ApplyTexture(0,mat->GetTexturePtr());

		DCRenderSetter::Get()->ApplyAlphaBlend(mat->GetAlphaBlendState());
		DCRenderSetter::Get()->ApplyAlphaTest(mat->GetAlphaTestState());

		mat->GetGeometryPtr()->Draw();
	}
}


void DCSubModel::InitIndexBuffer(const uint16* addr, uint32 count)
{
	IndexBufferPtr ptr;

	FAIL_ASSERT(DEVICEPTR->CreateIndexBuffer(sizeof(uint16)*count, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ptr, 0));

	void* lockPtr;
	FAIL_ASSERT(ptr->Lock(0,0,(void**)&lockPtr,0));
	memcpy(lockPtr,addr,count*sizeof(uint16));	
	ptr->Unlock();

	mIndexbuffer = ptr;//this will cause the release of the original index buffer;
	mIndexCount = count;
}

DCSubModel::~DCSubModel()
{
}