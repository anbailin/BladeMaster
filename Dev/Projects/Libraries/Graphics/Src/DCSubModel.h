#pragma once

class DCMaterial;
class DCModel;

class RENDER_DLL DCSubModel:public RefObject
{
public:
	DCSubModel();

	virtual ~DCSubModel();

	void Draw();

	void					InitIndexBuffer(const u16* addr, u32 count);
	IndexBufferPtr&			GetIndexBuffer()						{ return mIndexbuffer;	}

	void					SetGeometryTableSize(u32 size)		{ mGeometryTable.resize(size);	}
	void					SetGeometry(const DCGeometryPtr& geo, u32 index) { mGeometryTable[index] = geo;	}
	const DCGeometryPtr		GetGeometry(u32 index)				{ assert( index < mGeometryTable.size()); return mGeometryTable[index];	}

	void					SetMaterial(const DCMaterialPtr& material, u32 index) { assert(index<mMaterials.size()); mMaterials[index] = material;}
	void					SetMaterialNum(u32 num)				{ mMaterials.resize(num);}
	const std::vector<DCMaterialPtr>& GetMaterials()const			{ return mMaterials;	}
	const DCMaterialPtr		GetMaterial(u32 index)const			{ assert(index<mMaterials.size()); return mMaterials[index];}

	void					SetParent(DCModel* arg)					{mParent = arg;	}
	DCModel*				GetParent()								{return mParent;}

private:
	DCModel*						mParent;

	IndexBufferPtr					mIndexbuffer;
	u32							mIndexCount;

	std::vector<DCGeometryPtr>		mGeometryTable;

	std::vector<DCMaterialPtr>		mMaterials;

	s32							mLod;
};

typedef ComPtr<DCSubModel> DCSubModelPtr;