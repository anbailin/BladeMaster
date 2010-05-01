#include "Graphics.h"
#include "DCAnimHeader.h"

//---------DCModel------------------------------------------------------------------------------

DCModel::DCModel()
:	mAnimMgr(NULL)
,	mSubModels(NULL)
,	mSubModelCount(0)
{}


void DCModel::Draw(uint32 ndx)
{
	assert( ndx<mSubModelCount );

	//pix_event g( DXUT_PERFEVENTCOLOR, L"render model" );	

    VertexDeclareManager::Instance().ApplyVertexDeclaration(VertexTypePosWNTC);
    ShaderLoader::Instance().ApplyShader(ShaderLoader::Instance().skin_vs_id, ShaderLoader::Instance().skin_ps_id);
	
	float* constAddr = NULL;
	uint32 constSize = 0;
	
	mAnimMgr->GetShaderConstantInfo(constAddr,constSize);
	DEVICEPTR->SetVertexShaderConstantF(9,constAddr,constSize);

	BM_AssertHr( DEVICEPTR->SetStreamSource( 0,mVertexBuffer,0,sizeof(DCVertPosWNTC) ) );

	mSubModels[ndx].Draw();	
}

void DCModel::InitVertexBuffer(void* addr, DCVertexType type, uint32 count)
{
	VertexBufferPtr ptr;
	uint32 length = GetTypeSize(type) * count;
	BM_AssertHr(DEVICEPTR->CreateVertexBuffer(length,0,0,D3DPOOL_MANAGED, &ptr,0 ) );
	
	void* lockPtr;
	BM_AssertHr(ptr->Lock(0,0,&lockPtr,NULL));
	memcpy(lockPtr,addr,length);
	ptr->Unlock();

	mVertexBuffer = ptr;//this will cause the calling of original vertex buffer's Release();
	mVertexCount = count;
}

void DCModel::SetSubModel(DCSubModel* val,uint32 count)
{
	SafeDeleteArray( mSubModels);

	mSubModelCount = count;
	mSubModels = val;

	for(uint32 i=0;i<count;i++)
	{
		mSubModels[i].SetParent(this);
	}
}

void DCModel::SetTexture(DCTexturePtr ptr,uint32 index)
{	
	assert(index < mTextureTable.size());

	mTextureTable[index] = ptr;   
}

DCTexturePtr DCModel::GetTexture(uint32 index)
{
	assert(index < mTextureTable.size());

	return mTextureTable[index];
}

DCModel::~DCModel()
{
	SafeDelete(mAnimMgr);
	SafeDeleteArray(mSubModels);
}

void DCModel::RenderBoneLevel()
{ 
	GUARD_RENDERSTATE(D3DRS_ZENABLE,false);

    VertexDeclareManager::Instance().ApplyVertexDeclaration(VertexTypePosColor);
    ShaderLoader::Instance().ApplyShader(ShaderLoader::Instance().bone_vs_id, ShaderLoader::Instance().bone_ps_id);
	
	const uint32 boneNum = mAnimMgr->GetBoneNum();

	//log code begin-------------------------------------------------------------
	//for(uint32 i=0;i<boneNum; i++)
	//{
	//	const DCBone& bone = mAnimMgr->GetBone(i);
	//	const XMFLOAT3& transPivot = bone.GetTransPivot();
	//	const XMFLOAT3& pivot = bone.GetPivot();
	//	wchar_t c_str[256];

	//	_snwprintf_s(c_str, 256, L"transPivot at %d is %f, %f, %f\n ", i, transPivot.x, transPivot.y, transPivot.z);
	//	OutputDebugStr(c_str);

	//	_snwprintf_s(c_str, 256, L"Pivot at %d is %f, %f, %f\n ", i, pivot.x, pivot.y, pivot.z);
	//	OutputDebugStr(c_str);
	//}
	//log code end-------------------------------------------------------------

	const std::vector<uint32>& boneIdVec = mAnimMgr->GetBoneIDVector(); 
	for(uint32 i=0;i<boneIdVec.size();i++)
	{
		const uint32 rootID = boneIdVec[i];
		const DCBone& root = mAnimMgr->GetBone(rootID);
		const uint32 boneLevel = mAnimMgr->GetBoneLevel(); 

		assert(root.GetParentPtr() == NULL);
		std::vector<BoneVert> vtx;
		vtx.reserve(boneNum*2);
		
		static bool boneColor = false;

		root.RenderBoneLevel(vtx,boneLevel,boneColor);

		if(vtx.size() == 0)
		{
			continue;
		}
		else
		{
			BM_AssertHr( DEVICEPTR->DrawPrimitiveUP( D3DPT_LINELIST,vtx.size()/2,&(vtx[0]),sizeof(BoneVert) ) );
		}
	}	
}

void DCModel::SetAnimManager(DCAnimationManager* mgr)
{ 
	mAnimMgr = mgr; mgr->SetModel(this);
}

void DCModel::Animate(uint32 anim)
{
	mAnimMgr->Animate(anim);	
}

//---------DCModelSys------------------------------------------------------------------------------

DCModelSys::DCModelSys()
{}

DCModelSys::~DCModelSys()
{}

void DCModelSys::InitVertexBuffer(void* addr, DCVertexType type, uint32 count)
{
	mOriginalVertArray.resize(count);

	const DCVertPosWNTC* verts = (DCVertPosWNTC*)addr;

	for(uint32 i=0;i<count;i++)
	{
		mOriginalVertArray[i].bone[0] = verts[i].bone[0];
		mOriginalVertArray[i].bone[1] = verts[i].bone[1];
		mOriginalVertArray[i].bone[2] = verts[i].bone[2];
		mOriginalVertArray[i].bone[3] = verts[i].bone[3];
		mOriginalVertArray[i].color0 = verts[i].color0;
		mOriginalVertArray[i].color1 = verts[i].color1;
		mOriginalVertArray[i].normal = verts[i].normal;
		mOriginalVertArray[i].pos = verts[i].pos;
		mOriginalVertArray[i].texcoord = verts[i].texcoord;
		mOriginalVertArray[i].weight[0] = ((float)(verts[i].weight[0]))/255.0f;
		mOriginalVertArray[i].weight[1] = ((float)(verts[i].weight[1]))/255.0f;
		mOriginalVertArray[i].weight[2] = ((float)(verts[i].weight[2]))/255.0f;
		mOriginalVertArray[i].weight[3] = ((float)(verts[i].weight[3]))/255.0f;
	}

	mAnimatedVertArray.resize(count);
	for(uint32 i=0;i<count;i++)
	{
		mAnimatedVertArray[i].tex = mOriginalVertArray[i].texcoord;
	}

	VertexBufferPtr ptr;
	uint32 length = GetTypeSize(type) * count;
	BM_AssertHr(DEVICEPTR->CreateVertexBuffer(length,0,0,D3DPOOL_MANAGED, &ptr,0 ) );

	mVertexBuffer = ptr;
	mVertexCount = count;
}


void DCModelSys::Animate(uint32 anim)
{
	mAnimMgr->Animate(anim);

	const MatrixPool& bones = mAnimMgr->GetMatrixPool();
	for(uint32 i=0;i<mVertexCount;i++)
	{
		const XMFLOAT3& pos = mOriginalVertArray[i].pos;
		const XMFLOAT3& norm = mOriginalVertArray[i].normal;
		const uint8* ndx = mOriginalVertArray[i].bone;
		const float* weight = mOriginalVertArray[i].weight;

		XMVECTOR animpos = {0,0,0,0};
		XMVECTOR animnorm= {0,0,0,0};

		for(uint32 k=0;k<4;k++)
		{
			XMVECTOR tpos = {pos.x, pos.y,pos.z,1.0f};
			XMVECTOR tnorm = XMLoadFloat3(&norm);

			tpos = XMVector4Transform(tpos, bones[ndx[k]]);
			tnorm = XMVector3TransformNormal(tnorm, bones[ndx[k]]);
			animpos += tpos*weight[k];
			animnorm += tnorm*weight[k];
		}
		
		XMStoreFloat3(&mAnimatedVertArray[i].pos, animpos);
        XMStoreFloat3(&mAnimatedVertArray[i].normal, animnorm);
		assert(mAnimatedVertArray[i].tex.x>=0 && mAnimatedVertArray[i].tex.y>=0 );
	}
}

void DCModelSys::Draw(uint32 ndx)
{
	assert(ndx<mSubModelCount);

	//pix_event g( DXUT_PERFEVENTCOLOR, L"render model" );
	
    VertexDeclareManager::Instance().ApplyVertexDeclaration(VertexTypePosNorTex);
    ShaderLoader::Instance().ApplyShader(ShaderLoader::Instance().static_vs_id, ShaderLoader::Instance().static_ps_id);

	uint32 length = mVertexCount*sizeof(MDXModelVertSys);
	void* lockPtr;
	BM_AssertHr(mVertexBuffer->Lock(0,0,&lockPtr,NULL));
	memcpy(lockPtr,(void*)&(mAnimatedVertArray[0]),length);
	mVertexBuffer->Unlock();

	BM_AssertHr( DEVICEPTR->SetStreamSource( 0,mVertexBuffer,0,sizeof(MDXModelVertSys) ) );

	mSubModels[ndx].Draw();	
}


