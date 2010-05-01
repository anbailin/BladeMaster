#pragma once

class DCCharacter;
class DCModel;
class DCBone;
struct MDXAnimSequence;

typedef std::vector<XMMATRIX,AlignmentAllocator<XMMATRIX,16>> MatrixPool;
class ANIM_DLL DCAnimationManager
{
public:
	DCAnimationManager();
	~DCAnimationManager();

	void	Animate(uint32 anim);

	//void	SetShader();
	void	GetShaderConstantInfo(float*& dataAddr, uint32& constantSize)const
	{
		dataAddr = (float*)&(mBoneMatrixPool[0]);
		constantSize = 4*mBones.size();
	}
	
	void	SetAnimSeqInfo(const MDXAnimSequence* seq, uint32 num);	
	void    SetAnimSeqInfo(const MDXAnimSequenceWLK* seq,uint32 num);
	void	SetBoneInfo(const MDXModelHeader& header, MPQFile& file, MPQFile* animFiles);

	const	MDXAnimSequence& GetAnimSeqInfo(uint32 index)const	{ return mAnimSeqInfo[index]; }
	const	DCBone&	GetBone(uint32 index)const				{ return mBones[index];	}
	uint32  GetBoneNum()const						{ return mBones.size(); }
	const std::vector<uint32>&  GetBoneIDVector()const						{ return mRootBoneIDs; }
	const	MatrixPool& GetMatrixPool()const			{ return mBoneMatrixPool;	}

	void	SetModel(DCModel* m)									{ mModel = m;	}
	const	DCModel* GetModel()const								{ return mModel;	}

	uint32  GetBoneLevel()const										{ return mBoneLevel; }

private:
	void	GenerateBoneFamilyTree();
	void	GenerateBoneLevelInfo();

	//attributes
private:
	DCModel*						mModel;
	std::vector<DCBone, AlignmentAllocator<DCBone, 16>>				mBones;
	uint32							mBoneLevel;			//how many levels in the bone tree structure
	std::vector<uint32>				mRootBoneIDs;
	std::vector<MDXAnimSequence>	mAnimSeqInfo;
	int32*							mAnimDuration;		//need to keep the duration infomation;
	MatrixPool						mBoneMatrixPool;
};