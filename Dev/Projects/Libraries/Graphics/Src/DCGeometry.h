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

	void			SetVertexStart(u32 val)	{ mVertexStart = val; }
	u32			GetVertexStart()const		{ return mVertexStart;}

	void			SetVertexCount(u32 val)	{ mVertexCount = val; }
	u32			GetVertexCount()const		{ return mVertexCount;}

	void			SetIndexStart(u32 val)	{ mIndexStart = val; }
	u32			GetIndexStart()const		{ return mIndexStart;}

	void			SetIndexCount(u32 val)	{ mIndexCount = val; }
	u32			GetIndexCount()const		{ return mIndexCount;}

	void			SetID(u32 val)			{ mID = val;  }
	u32			GetID()const				{ return mID; }
private:
	DCSubModel*		mParent;

	u32			mID;
	u32			mVertexStart;
	u32			mVertexCount;
	u32			mIndexStart;
	u32			mIndexCount;
};

typedef ComPtr<DCGeometry> DCGeometryPtr;