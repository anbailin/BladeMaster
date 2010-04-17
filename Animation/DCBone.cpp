#include "Core.h"
#include "DCAnimHeader.h"

//------------------------------------------------------------------------------------------------
DCBone::DCBone()
:	mAnimManager(NULL)
,	mParentID(-1)
,	mAnimID(-1)
,	mCalculate(false)
,	mBoneLevel(0)
,	mParent(NULL)
,	mBoneID(0)
{}


//------------------------------------------------------------------------------------------------
DCBone::~DCBone()
{
	mAnimManager = NULL;
	mParent = NULL;
	mParentID = -1;
	mAnimID = -1;
	mCalculate = false;
	mBoneLevel = 0;
	mBoneID = 0;
}


//------------------------------------------------------------------------------------------------

void DCBone::Init(const MDXBoneDef& _block, MPQFile& _file, const int32* _GlobalSequence, MPQFile* animFile)
{
	mParentID = _block.mParent;
	mAnimID	= _block.mAnimID;

	mTrans.Init(_block.mTranslation, _file, _GlobalSequence, animFile);
	mRotate.Init(_block.mRotation, _file, _GlobalSequence, animFile);
	mScale.Init(_block.mScaling, _file, _GlobalSequence, animFile);
	
	mPivot = _block.mPivot;	
}


//------------------------------------------------------------------------------------------------
//the bone structure is from bottum to the top
//1st, it transformed back by mPivot
//2nd, do rotate or translate
//3rd, then transformed by mPivot
//4th, do the tree structured work
void DCBone::CalcMatrix(uint32 anim, uint32 time, uint32 _GlobalTime, XMMATRIX& out)
{
	if(mCalculate == true)
	{
		out = mMatrixCache;
		return;
	} 

	XMMATRIX pivotMatrix = XMMatrixTranslation(mPivot.x, mPivot.y, mPivot.z);
	XMMATRIX reversePivotMatrix = XMMatrixTranslation(-mPivot.x, -mPivot.y, -mPivot.z);

	XMMATRIX parentMatrix;

	if(mParent)//make sure the parent's bone matrix is calculated
	{
		mParent->CalcMatrix(anim,time,_GlobalTime,parentMatrix);
	}
	else
	{
		parentMatrix = XMMatrixIdentity();
	}
	
	out = XMMatrixIdentity();
	out = XMMatrixMultiply(out,reversePivotMatrix);		 

	if(mTrans.Use(anim))
	{		
		XMFLOAT3 trans_f3 = mTrans.GetValue(anim,time,_GlobalTime);
		XMMATRIX trans_m = XMMatrixTranslation(trans_f3.x, trans_f3.y, trans_f3.z);	
		out *= trans_m;
	}

	if(mRotate.Use(anim))
	{	
		XMFLOAT4 rotate_f4 = mRotate.GetValue(anim,time,_GlobalTime);
		XMVECTOR rot = XMLoadFloat4(&rotate_f4);
		XMMATRIX rot_m = XMMatrixRotationQuaternion(rot);		
		out *= rot_m;
	}
	
	if(mScale.Use(anim))
	{
		XMFLOAT3 scale_f3 = mScale.GetValue(anim,time,_GlobalTime);
		if(scale_f3.x==0.0f&&scale_f3.y==0.0f&&scale_f3.z==0.0f)
		{
			scale_f3.x = 1.0f;
			scale_f3.y = 1.0f;
			scale_f3.z = 1.0f;
		}		
		XMMATRIX scale_m = XMMatrixScaling(scale_f3.x,scale_f3.y,scale_f3.z);
		out *= scale_m;
	}		
		
	out *= pivotMatrix;
	out *= parentMatrix;	
	
	XMVECTOR pivot;
	pivot = XMLoadFloat3(&mPivot);
	pivot.m128_f32[3] = 1.0f;
	mTransPivot = XMVector4Transform(pivot, out);

	mCalculate = true;
	mMatrixCache = out;
}


//------------------------------------------------------------------------------------------------
void DCBone::ClearFamilyInfo()
{
	mParent = NULL;
	mChildren.clear();
}


//------------------------------------------------------------------------------------------------
void DCBone::AddChild(DCBone *ptr)
{
	std::vector<DCBone*>::iterator pos;

	pos = find(mChildren.begin(),mChildren.end(),ptr);

	if(pos == mChildren.end())
		mChildren.push_back(ptr);
}


//------------------------------------------------------------------------------------------------
void DCBone::SetParent(DCBone *ptr)
{
	if(mParent!=NULL)
		mParent->RemoveChild(this);

	mParent = ptr; 

	if(ptr!=NULL)
		ptr->AddChild(this);	
}


//------------------------------------------------------------------------------------------------
void DCBone::RemoveChild(DCBone *ptr)
{
	std::vector<DCBone*>::iterator pos;

	uint32 length = mChildren.size();
	for(uint32 i=0;i<length;i++)
	{
		pos = find(mChildren.begin(),mChildren.end(),ptr);
		if(pos == mChildren.end())
			mChildren.erase(pos);
		else
			return;
	}
}

//------------------------------------------------------------------------------------------------
void DCBone::SetCalculate(bool c)
{	
	mCalculate = c; 
	if(c==false) 
	{
		mMatrixCache = XMMatrixIdentity();
	}
}

//------------------------------------------------------------------------------------------------
namespace
{
	uint32 GetColor(uint32 maxLevel,uint32 level)
	{
		const uint32 delta = 24/maxLevel;
		const uint32 value0 = (1<<(delta * level + 1)) - 1;
		const uint32 value1 = (1<<(delta * (level-1) + 1)) - 1;
		const uint32 value = value0 - value1;
		return value|0xff000000;
	}
}


void DCBone::RenderBoneLevel(std::vector<BoneVert>& vtx,uint32 maxLevel,bool colorful)const
{
	const static uint32 sColorWite = 0xffffffff;

	if(mChildren.size() == 0)
		return;

	BoneVert bone;	
	XMStoreFloat3(&bone.pos, GetTransPivot());
	
	bone.color = colorful?GetColor(maxLevel,mBoneLevel):sColorWite;

	uint32 colorKid = colorful?GetColor(maxLevel,mBoneLevel+1):sColorWite;
	for(uint32 i=0;i<mChildren.size();i++)
	{
		BoneVert boneKid;
		boneKid.color = colorKid;		
		XMStoreFloat3(&boneKid.pos, mChildren[i]->GetTransPivot());
		vtx.push_back(bone);
		vtx.push_back(boneKid);
	}

	for(uint32 i=0;i<mChildren.size();i++)
	{
		mChildren[i]->RenderBoneLevel(vtx,maxLevel,colorful);
	}
}


//------------------------------------------------------------------------------------------------
void DCBone::GenerateBoneLevelInfo(uint32 level,uint32& maxLevel)
{
	mBoneLevel = level;

	maxLevel = (level>maxLevel)?level:maxLevel;

	for(uint32 i=0;i<mChildren.size();i++)
	{
		mChildren[i]->GenerateBoneLevelInfo(level+1, maxLevel);
	}
}