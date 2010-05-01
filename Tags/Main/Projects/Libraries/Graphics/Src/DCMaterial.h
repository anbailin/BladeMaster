#pragma once

class DCMesh;

class RENDER_DLL DCMaterial:public RefObject
{
public:
	DCMaterial();
	virtual ~DCMaterial(){}

	void	SetTexturePtr(const DCTexturePtr& _ptr)		{ mTexPtr = _ptr; }
	const DCTexturePtr&  GetTexturePtr()const			{ return mTexPtr; }

	void	SetColor(const DCRGBAColor8& _color)		{ mColor = _color; }
	const	DCRGBAColor8 GetColor()const				{ return mColor;}

	void	SetGeometryPtr(const DCGeometryPtr& _ptr)			{ mGeometryPtr = _ptr; }
	const DCGeometryPtr&	GetGeometryPtr()const				{ return mGeometryPtr;}

	void	SetAlphaBlendState(const DCAlphaBlendState& _state)	{ mAlphaBlend = _state;	}
	const DCAlphaBlendState& GetAlphaBlendState()const			{ return mAlphaBlend;	}

	void    SetAlphaTestState(const DCAlphaTestState& _state)   { mAlphaTest = _state;	}
	const DCAlphaTestState&  GetAlphaTestState()const			{ return mAlphaTest;	}

private:
	DCTexturePtr				mTexPtr;	
	DCGeometryPtr				mGeometryPtr;
	DCRGBAColor8				mColor;

	DCAlphaBlendState			mAlphaBlend;
	DCAlphaTestState			mAlphaTest;
};

typedef ComPtr<DCMaterial> DCMaterialPtr;