#ifndef Animation_DCBone_h
#define Animation_DCBone_h

class DCAnimationManager;

class ANIM_DLL __declspec(align(16)) DCBone
{
public:
	DCBone();
	~DCBone();
	void	Init(const MDXBoneDef& _block, MPQFile& _file, const int32* _GlobalSequence, MPQFile* animFile);

	void	CalcMatrix(uint32 anim, uint32 time, uint32 _GlobalTime,XMMATRIX& out);
	void	SetCalculate(bool c);

	//--bone family tree structure---------------------------------
	void	ClearFamilyInfo();
	void	AddChild(DCBone* ptr);
	void	RemoveChild(DCBone* ptr);

	void	SetParent(DCBone* ptr);
	int32	GetParentID()const							{	return mParentID; }
	const	DCBone*	GetParentPtr()const					{	return mParent;	}

	void	SetBoneID(int32 id)							{	mBoneID = id;	}
	const   std::vector<DCBone*>& GetChildren()const	{	return mChildren; }

	void	RenderBoneLevel(std::vector<BoneVert>& vtx, uint32 maxLevel, bool colorful)const
	{
		const static uint32 sColorWite = 0xffffffff;

		if(mChildren.size() == 0)
			return;

		BoneVert bone;	
		XMStoreFloat3(&bone.pos, GetTransPivot());

		bone.color = sColorWite;

		uint32 colorKid = sColorWite;
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
	void	GenerateBoneLevelInfo(uint32 level,uint32& maxLevel);

	//--get and set---------------------------------
	void	SetAnimManager(DCAnimationManager* _p)		{   mAnimManager = _p;}
	const	DCAnimationManager*	GetAnimManager()const	{   return mAnimManager;	}

	const	XMFLOAT3& GetPivot()const					{	return mPivot;	}		

	const	XMMATRIX& GetTransformMatrixCache()const  {	return mMatrixCache;	}
	const   AnimData<XMQuaternion, PACK_QUATERNION, Quat16ToQuat32>& GetRotateData()		{	return mRotate;	}
	const   XMVECTOR& GetTransPivot()const {return mTransPivot; }

private:
	XMVECTOR				mTransPivot;
	XMMATRIX				mMatrixCache;
	XMFLOAT3				mPivot;

	//owner
	DCAnimationManager*		mAnimManager;
	//basic data
	int32					mParentID;
	int32					mAnimID;
	AnimData<XMFLOAT3>		mTrans;
	AnimData<XMFLOAT3>		mScale;
	AnimData<XMQuaternion, PACK_QUATERNION, Quat16ToQuat32>	mRotate;

	//for calculation
	bool					mCalculate;	
	//family tree
	std::vector<DCBone*>	mChildren;
	DCBone*					mParent;
	uint32					mBoneID;
	uint32					mBoneLevel;//lv0 is initial and unavailable, from 1 is available;
};

#endif