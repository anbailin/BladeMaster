#pragma once

class DCCharacter;
class DCModel;
class DCBone;
struct MDXAnimSequence;


class ENGINE_DLL DCAnimationManager
{
public:
	DCAnimationManager();
	~DCAnimationManager();

	void	Animate(u32 anim);

	//void	SetShader();
	void	GetShaderConstantInfo(float*& dataAddr, u32& constantSize)const
	{
		dataAddr = (float*)&(mBoneMatrixPool[0]);
		constantSize = 4*mBones.size();
	}
	
	void	SetAnimSeqInfo(const MDXAnimSequence* seq, u32 num);	
	void    SetAnimSeqInfo(const MDXAnimSequenceWLK* seq,u32 num);
	void	SetBoneInfo(const MDXModelHeader& header, MPQFile& file, MPQFile* animFiles);

	const	MDXAnimSequence& GetAnimSeqInfo(u32 index)const	{ return mAnimSeqInfo[index]; }

	const	DCBone&	GetBone(u32 index)const				{ return mBones[index];	}
	u32  GetBoneNum()const						{ return mBones.size(); }
	
	const std::vector<u32>&  GetBoneIDVector()const						{ return mRootBoneIDs; }
	const	MatrixPool& GetMatrixPool()const			{ return mBoneMatrixPool;	}

	void	SetModel(DCModel* m)									{ mModel = m;	}
	const	DCModel* GetModel()const								{ return mModel;	}

	u32  GetBoneLevel()const										{ return mBoneLevel; }

private:
	void	GenerateBoneFamilyTree();
	void	GenerateBoneLevelInfo();

	//attributes
private:
	DCModel*						mModel;
	std::vector<DCBone, AlignmentAllocator<DCBone, 16>>				mBones;
	u32							mBoneLevel;			//how many levels in the bone tree structure
	std::vector<u32>				mRootBoneIDs;
	std::vector<MDXAnimSequence>	mAnimSeqInfo;
	s32*							mAnimDuration;		//need to keep the duration infomation;
	MatrixPool						mBoneMatrixPool;
};