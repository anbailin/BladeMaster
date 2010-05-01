#pragma once

class DCModel;
struct MDXGeometry;
class DCSubModel;

class RENDER_DLL DCGeometry :public RefObject
{
public:
	DCGeometry();
	DCGeometry(const MDXGeometry& geo);
	~DCGeometry(){}

	inline void		Init(const MDXGeometry& geo);
	void			Draw();


	void			SetParent(DCSubModel* val)	{ mParent = val;  }
	const DCSubModel*	GetParent()const		{ return mParent; }

	void			SetVertexStart(uint32 val)	{ mVertexStart = val; }
	uint32			GetVertexStart()const		{ return mVertexStart;}

	void			SetVertexCount(uint32 val)	{ mVertexCount = val; }
	uint32			GetVertexCount()const		{ return mVertexCount;}

	void			SetIndexStart(uint32 val)	{ mIndexStart = val; }
	uint32			GetIndexStart()const		{ return mIndexStart;}

	void			SetIndexCount(uint32 val)	{ mIndexCount = val; }
	uint32			GetIndexCount()const		{ return mIndexCount;}

	void			SetID(uint32 val)			{ mID = val;  }
	uint32			GetID()const				{ return mID; }
private:
	DCSubModel*		mParent;

	uint32			mID;
	uint32			mVertexStart;
	uint32			mVertexCount;
	uint32			mIndexStart;
	uint32			mIndexCount;
};

typedef ComPtr<DCGeometry> DCGeometryPtr;