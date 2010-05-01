#include "Core.h"
#include "DCAnimHeader.h"

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
void DCAnimationManager::SetAnimSeqInfo(const MDXAnimSequence *seq, uint32 num)
{
	assert(seq && num);

	mAnimSeqInfo.resize(num);
	for(uint32 i=0;i<num;i++)
	{
		mAnimSeqInfo[i] = seq[i];
	}
}

void DCAnimationManager::SetAnimSeqInfo(const MDXAnimSequenceWLK *seq, uint32 num)
{
	assert(seq && num);

	mAnimSeqInfo.resize(num);
	for(uint32 i=0;i<num;i++)
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
	const uint32 boneNum = header.mBone.number;

	const int32* animDuration = (int32*)(file.getBuffer() + header.mAnimDuration.offset);
	const uint32 animDurationNum = header.mAnimDuration.number;
	mAnimDuration = new int32[animDurationNum];
	memcpy(mAnimDuration, animDuration, animDurationNum*sizeof(int32));

	mBones.resize(boneNum);
	for(uint32 i=0;i<boneNum;i++)
	{
		mBones[i].Init(boneDefPtr[i],file,mAnimDuration, animFiles);
		mBones[i].SetBoneID(i);
	}
	
	mBoneMatrixPool.resize(boneNum);

	GenerateBoneFamilyTree();
	GenerateBoneLevelInfo();
}


//---------------------------------------------------------------------------------------
void DCAnimationManager::Animate(uint32 anim)
{
	const MDXAnimSequence& animSeq = mAnimSeqInfo[anim];
	const uint32 globalTime = (uint32)(DXUTTimer::GetTime()*500);
	const uint32 deltaTime = animSeq.mTimeEnd - animSeq.mTimeStart;
	const uint32 time = globalTime%deltaTime + animSeq.mTimeStart;

	const uint32 boneNum = mBones.size();
	for(uint32 i=0; i<boneNum; i++)
	{
		mBones[i].SetCalculate(false);
	}

	for(uint32 i=0; i<boneNum; i++)
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
		//for(uint32 m_idx=0; m_idx<16; m_idx++)
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
	const uint32 boneNum = mBones.size();

	for(uint32 i=0;i<boneNum;i++)
	{
		int32 parentID = mBones[i].GetParentID();
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
	for(uint32 i=0;i<mRootBoneIDs.size();i++)
	{
		uint32 rootID = mRootBoneIDs[i];
		DCBone& root = mBones[rootID];
		assert(root.GetParentPtr() == NULL);
		uint32 maxLevel = 0;
		root.GenerateBoneLevelInfo(1,maxLevel);
		mBoneLevel = (maxLevel>mBoneLevel)?maxLevel:mBoneLevel;
	}
}

//---------------------------------------------------------------------------------------
