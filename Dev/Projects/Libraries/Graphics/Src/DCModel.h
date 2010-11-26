//===============================================================================
// Copyright 2007, ZJUGDA
//===============================================================================
#pragma once

class DCMaterial;

/**
	DCModel----represent a model
	-- hold data of texture&vertex, and the sub will get data through index of the data.
	-- hold animation manager,
	-- every specific render work will based on DCSubModel data structure
*/

class RENDER_DLL  __declspec(align(16)) DCModel:public RefObject
{
public:
	DCModel();
	virtual ~DCModel();

	virtual void			Draw(u32 ndx);	
	void					RenderBoneLevel();

	/*
	*	initialize vertex buffer, 
	*/
	virtual void			InitVertexBuffer(void* addr, DCVertexType type, u32 count);

	DCSubModel*				GetSubModel(u32 ndx)				{ return &mSubModels[ndx];	}
	u32					GetSubModelCount()const				{ return mSubModelCount;	}
	void					SetSubModel(DCSubModel* val,u32 count);
	
	u32					GetVertexCount()					{ return mVertexCount;}

	void					SetTextureTableSize(u32 size)	{ mTextureTable.resize(size);}
	void					SetTexture(DCTexturePtr ptr,u32 index);
	DCTexturePtr			GetTexture(u32 index);
	
	//attr access
public:
	void					SetWorldMatrix(const D3DXMATRIXA16& matrix) { mWorld = matrix; }
	void					SetSkinningData(const float* skin, u32 size)			{ mSkinData = skin; mSkinConstNum = size; }
	virtual void			SetSkinningData(const MatrixPool& skinData);

protected:
	DCSubModel*						mSubModels;
	u32							mSubModelCount;

	D3DXMATRIXA16					mWorld;

	VertexBufferPtr					mVertexBuffer;
	u32							mVertexCount;

	std::vector<DCTexturePtr>		mTextureTable;	
	const float*					mSkinData;//data of the skinning animation
	u32							mSkinConstNum;//how many float4 of the skinning data

    ShaderId                        mShaderId;
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

	virtual void			Draw(u32 ndx);
	virtual void			InitVertexBuffer(void* addr, DCVertexType type, u32 count);	
	virtual void			SetSkinningData(const MatrixPool& skinData);

protected:
	MDXVertArray					mOriginalVertArray;
	MDXVertArraySys					mAnimatedVertArray;    
};

typedef ComPtr<DCModel> DCModelPtr;