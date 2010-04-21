#pragma once

class WMOInstance;
class WMOGroup;
class WMOModel;
class WMOGeometry;

//#include "Maps.h"

typedef ComPtr<WMOGroup>	WMOGroupPtr;
typedef ComPtr<WMOModel>	WMOModelPtr;
typedef ComPtr<WMOGeometry> WMOGeometryPtr;

//
//class WMO:public RefObject
//{
//public:
//
//	void Init(std::string name);
//
//	const std::string&  GetName()const			{ return mName; }
//	void				Draw();
//	void				SetWMOGroupNum(uint32 num) { mGroups.resize(num); }
//	void				SetWMOGroup(const WMOGroupPtr& ptr, uint32 ndx){ mGroups[ndx] = ptr; }
//	const WMOGroupPtr&	GetWMOGroup(uint32 ndx) { return mGroups[ndx];	}
//	
//	void				SetMaterialNum(uint32 num) { mMaterials.resize(num);}
//	void				SetMaterial(const DCMaterialPtr& ptr, uint32 ndx) { mMaterials[ndx] = ptr;	}
//	const DCMaterialPtr& GetMaterial(uint32 ndx) { return mMaterials[ndx]; }
//
//	void				SetModelInstanceNum(uint32 num) { mModelInstances.resize(num);	}
//	void				SetModelInstance(const DCModelInstancePtr& ptr, uint32 ndx) { mModelInstances[ndx] = ptr;	}
//    const DCModelInstancePtr& GetModelInstance(uint32 ndx) { return mModelInstances[ndx];	}
//private:
//	std::string						mName;
//	std::vector<WMOGroupPtr>		mGroups;
//	std::vector<DCMaterialPtr>		mMaterials;
//	std::vector<DCModelInstancePtr> mModelInstances;
//
//	WMOHeader						mHeader;
//};
//
//typedef ComPtr<WMO> WMOPtr;
//
//class WMOInstance:public RefObject
//{
//public:
//	void Init(const WMOPtr& ptr, const ADTMODFChunk& chunk);
//private:
//	WMOPtr			mWMO;
//	DCTranslator	mTranslator;
//	uint32			mDoodadSet;
//	uint32			mGUID;
//};
//typedef ComPtr<WMOInstance> WMOInstancePtr;
//
//class MPQFile;
//class WMOGroup:public RefObject
//{
//public:
//	void Init(WMO* _wmo, MPQFile &f, int num, char *names);
//	void InitRender();
//	void Draw();
//private:
//	WMO*						mWMO;
//	WMOModelPtr					mModelPtr;
//	std::string					mName;
//	DCAABoundingBox				mBoundingBox;
//	uint32						mFlag;
//	uint32						mNum;
//};
//
//
//
//class WMOModel:public RefObject
//{
//public:
//	void SetVertexBufferPtr(VertexBufferPtr& ptr)			{ mVtxBuffer = ptr;	}
//	const VertexBufferPtr&	GetVertexBufferPtr()const		{ return mVtxBuffer;}
//
//	void SetIndexBufferPtr(IndexBufferPtr& ptr)				{ mNdxBuffer = ptr; }
//	const IndexBufferPtr&	GetIndexBufferPtr()const		{ return mNdxBuffer;}
//
//	void SetMaterialNum(uint32 num)							{ mMaterials.resize(num);}
//	uint32 GetMaterialNum()const							{ return mMaterials.size();}
//	void SetMaterialPtr(const DCMaterialPtr& ptr,uint32 ndx){ mMaterials[ndx] = ptr; }
//	const DCMaterialPtr& GetMaterialPtr(uint32 ndx)const	{ return mMaterials[ndx];}
//
//	void SetGeometryNum(uint32 num)							{ mGeometries.resize(num);}
//	uint32 GetGeometryNum()const								{ return mGeometries.size();}
//	void SetGeometryPtr(const WMOGeometryPtr& ptr, uint32 ndx) { mGeometries[ndx] = ptr; }
//	WMOGeometryPtr  GetGeometryPtr(uint32 ndx)const							{ return mGeometries[ndx];	}
//
//	void SetVertexInfo(const void* addr, uint32 count,uint32 stride);
//	void Draw();
//private:
//	VertexBufferPtr				mVtxBuffer;
//	IndexBufferPtr				mNdxBuffer;
//	std::vector<DCMaterialPtr>	mMaterials;
//	std::vector<WMOGeometryPtr> mGeometries;
//
//	uint32						mVertexCount;
//};
//
//class WMOGeometry:public RefObject
//{
//public:
//	void SetBasicInfo(const WMOBatch& batch);
//	void Draw();
//
//	void SetMaterialPtr(const DCMaterialPtr& m)	{ mMaterial = m;	}
//	const DCMaterialPtr& GetMaterialPtr()const  { return mMaterial;}
//private:
//	DCMaterialPtr	mMaterial;
//	uint32			mIndexStart;
//	uint32			mIndexCount;
//	uint32			mVertexStart;
//	uint32			mVertexEnd;
//};

