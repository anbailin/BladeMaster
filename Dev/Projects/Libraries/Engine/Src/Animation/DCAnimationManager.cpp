#include "EnginePrivate.h"

//---------------------------------------------------------------------------------------
DCAnimationManager::DCAnimationManager()
:	mBoneLevel(0)
{

}

DCAnimationManager::~DCAnimationManager()
{
	mModel = NULL;
}

//---------------------------------------------------------------------------------------
void DCAnimationManager::SetAnimSeqInfo(const MDXAnimSequence *seq, u32 num)
{
	assert(seq && num);

	mAnimSeqInfo.resize(num);
	for(u32 i=0;i<num;i++)
	{
		mAnimSeqInfo[i] = seq[i];
	}
}

void DCAnimationManager::SetAnimSeqInfo(const MDXAnimSequenceWLK *seq, u32 num)
{
	assert(seq && num);

	mAnimSeqInfo.resize(num);
	for(u32 i=0;i<num;i++)
	{
		mAnimSeqInfo[i].mAnimID = seq[i].mAnimID;
		mAnimSeqInfo[i].mTimeStart = 0;
		mAnimSeqInfo[i].mTimeEnd = seq[i].mLength;
		mAnimSeqInfo[i].mMoveSpeed = seq[i].mMoveSpeed;
		mAnimSeqInfo[i].mFlag = seq[i].mFlags;
		mAnimSeqInfo[i].mPlaySpeed = seq[i].mPlaySpeed;
		mAnimSeqInfo[i].mRadius = seq[i].mRadius;		
	}
}

//---------------------------------------------------------------------------------------
void DCAnimationManager::SetBoneInfo(const MDXModelHeader& header, MPQFile& file, MPQFile* animFiles)
{
	assert(animFiles);

	const MDXBoneDef* boneDefPtr = (MDXBoneDef*)(file.getBuffer() + header.mBone.offset);
	const u32 boneNum = header.mBone.number;

	const s32* animDuration = (s32*)(file.getBuffer() + header.mAnimDuration.offset);
	const u32 animDurationNum = header.mAnimDuration.number;
	mAnimDuration = new s32[animDurationNum];
	memcpy(mAnimDuration, animDuration, animDurationNum*sizeof(s32));

	mBones.resize(boneNum);
	for(u32 i=0;i<boneNum;i++)
	{
		mBones[i].Init(boneDefPtr[i],file,mAnimDuration, animFiles);
		mBones[i].SetBoneID(i);
	}
	
	mBoneMatrixPool.resize(boneNum);

	GenerateBoneFamilyTree();
	GenerateBoneLevelInfo();
}


//---------------------------------------------------------------------------------------
void DCAnimationManager::Animate(u32 anim)
{
	const MDXAnimSequence& animSeq = mAnimSeqInfo[anim];
	const u32 globalTime = (u32)(DXUTTimer::GetTime()*500);
	const u32 deltaTime = animSeq.mTimeEnd - animSeq.mTimeStart;
	const u32 time = globalTime%deltaTime + animSeq.mTimeStart;

	const u32 boneNum = mBones.size();
	for(u32 i=0; i<boneNum; i++)
	{
		mBones[i].SetCalculate(false);
	}

	for(u32 i=0; i<boneNum; i++)
	{
		mBones[i].CalcMatrix(anim,time,globalTime,mBoneMatrixPool[i]);

		//debug code-------------------------------------------------------
		//mBones[i].CalcMatrix(anim,100,100,mBoneMatrixPool[i]);
		//mBoneMatrixPool[i] = XMMatrixIdentity();
		//debug code-------------------------------------------------------
		
		//log code---------------------------------------------------------
		//std::wstring str;
		//wchar_t idx_str[10];
		//_snwprintf_s(idx_str, 10, L"%d ", i);
		//str += L"index is ";		
		//str += idx_str;
		//str += L"matrix is:\n ";
		//for(u32 m_idx=0; m_idx<16; m_idx++)
		//{
		//	wchar_t floatV[256];
		//	_snwprintf_s(floatV, 256, L"%f ",mBones[i].GetTransformMatrixCache().m[m_idx]);
		//	str+=floatV;
		//	if(m_idx%4==3)
		//	{
		//		str+=L"\n";
		//	}
		//}
		//str+=L"\n";
		//OutputDebugString(str.c_str());
		//mBoneMatrixPool[i].Identity();
		//log code---------------------------------------------------------
	}
}

//---------------------------------------------------------------------------------------
void DCAnimationManager::GenerateBoneFamilyTree()
{
	const u32 boneNum = mBones.size();

	for(u32 i=0;i<boneNum;i++)
	{
		s32 parentID = mBones[i].GetParentID();
		if(parentID == -1)
		{
			mBones[i].SetParent(NULL);
			mRootBoneIDs.push_back(i);
		}else
		{
			DCBone& parentBone = mBones[parentID];
			mBones[i].SetParent(&parentBone);
		}
	}	
}

//---------------------------------------------------------------------------------------
void DCAnimationManager::GenerateBoneLevelInfo()
{
	for(u32 i=0;i<mRootBoneIDs.size();i++)
	{
		u32 rootID = mRootBoneIDs[i];
		DCBone& root = mBones[rootID];
		assert(root.GetParentPtr() == NULL);
		u32 maxLevel = 0;
		root.GenerateBoneLevelInfo(1,maxLevel);
		mBoneLevel = (maxLevel>mBoneLevel)?maxLevel:mBoneLevel;
	}
}

//---------------------------------------------------------------------------------------
