#pragma once

class DCMaterial;
class DCModel;

class RENDER_DLL DCSubModel:public RefObject
{
public:
	DCSubModel();

	~DCSubModel();

	void Draw();

	void					InitIndexBuffer(const uint16* addr, uint32 count);
	IndexBufferPtr&			GetIndexBuffer()						{ return mIndexbuffer;	}

	void					SetGeometryTableSize(uint32 size)		{ mGeometryTable.resize(size);	}
	void					SetGeometry(const DCGeometryPtr& geo, uint32 index) { mGeometryTable[index] = geo;	}
	const DCGeometryPtr		GetGeometry(uint32 index)				{ assert( index < mGeometryTable.size()); return mGeometryTable[index];	}

	void					SetMaterial(const DCMaterialPtr& material, uint32 index) { assert(index<mMaterials.size()); mMaterials[index] = material;}
	void					SetMaterialNum(uint32 num)				{ mMaterials.resize(num);}
	const std::vector<DCMaterialPtr>& GetMaterials()const			{ return mMaterials;	}
	const DCMaterialPtr		GetMaterial(uint32 index)const			{ assert(index<mMaterials.size()); return mMaterials[index];}

	void					SetParent(DCModel* arg)					{mParent = arg;	}
	DCModel*				GetParent()								{return mParent;}

private:
	DCModel*						mParent;

	IndexBufferPtr					mIndexbuffer;
	uint32							mIndexCount;

	std::vector<DCGeometryPtr>		mGeometryTable;

	std::vector<DCMaterialPtr>		mMaterials;

	int32							mLod;
};

typedef ComPtr<DCSubModel> DCSubModelPtr;