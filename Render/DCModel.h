//===============================================================================
// Copyright 2007, ZJUGDA
//===============================================================================
#pragma once

class DCMaterial;
class DCAnimationManager;


/**
	DCModel----represent a model
	-- hold data of texture&vertex, and the sub will get data through index of the data.
	-- hold animation manager,
	-- every specific render work will based on DCSubModel data structure
*/

class RENDER_DLL DCModel:public RefObject
{
public:
	DCModel();
	virtual ~DCModel();

	virtual void			Draw(uint32 ndx);
	virtual void			Animate(uint32 anim);
	void					RenderBoneLevel();

	/*
	*	initialize vertex buffer, 
	*/
	virtual void			InitVertexBuffer(void* addr, DCVertexType type, uint32 count);

	DCSubModel*				GetSubModel(uint32 ndx)				{ return &mSubModels[ndx];	}
	uint32					GetSubModelCount()const				{ return mSubModelCount;	}
	void					SetSubModel(DCSubModel* val,uint32 count);
	
	uint32					GetVertexCount()					{ return mVertexCount;}

	void					SetTextureTableSize(uint32 size)	{ mTextureTable.resize(size);}
	void					SetTexture(DCTexturePtr ptr,uint32 index);
	DCTexturePtr			GetTexture(uint32 index);

	void					SetAnimManager(DCAnimationManager* mgr);
	
protected:

	DCAnimationManager*				mAnimMgr;

	DCSubModel*						mSubModels;
	uint32							mSubModelCount;

	VertexBufferPtr					mVertexBuffer;
	uint32							mVertexCount;

	std::vector<DCTexturePtr>		mTextureTable;
};

/**
	DCModelSys----the same with DCModel
	except: model animation done on cpu side
*/
class RENDER_DLL  DCModelSys:public DCModel
{
public:
	DCModelSys();
	virtual ~DCModelSys();

	virtual void			Draw(uint32 ndx);
	virtual void			InitVertexBuffer(void* addr, DCVertexType type, uint32 count);
	virtual void			Animate(uint32 anim);
protected:
	MDXVertArray					mOriginalVertArray;
	MDXVertArraySys					mAnimatedVertArray;
};

typedef ComPtr<DCModel> DCModelPtr;