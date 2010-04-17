#pragma once

//class DCTranslator
//{
//public:
//	DCTranslator();
//	DCTranslator(const DCMatrix33& _rotate, const DCVector3& _vec, float _scale);
//
//	const DCMatrix44& GetLocalToWorldMatrix(){ if(mUpdatedToWorld==false) CalculateLocalToWorldMatrix(); return mMatrixCacheToWorld;}
//	const DCMatrix44& GetWorldToLocalMatrix(){ if(mUpdatedToLocal==false) CalculateWorldToLocalMatrix(); return mMatrixCacheToLocal;}
//
//	DCVector3	TransformPointToWorld(const DCVector3& point){ return TransformVectorToWorld(point) + mTranslation;	}
//	DCVector3	TransformPointToLocal(const DCVector3& point){ return TransformPointToLocal(point - mTranslation);	}
//
//	DCVector3	TransformVectorToWorld(const DCVector3& vec){ return TransformDirectionToWorld(vec) * mScale; }
//	DCVector3	TransformVectorToLocal(const DCVector3& vec){ return TransformDirectionToLocal(vec/mScale);	}
//
//	inline DCVector3	TransformDirectionToWorld(const DCVector3& vec)const;
//	inline DCVector3	TransformDirectionToLocal(const DCVector3& vec)const;
//
//	void	SetRotate(const DCMatrix33& _rotate)	{ mRotate = _rotate; Dirtylize();}
//	//void    SetRotate(const DCQuaternion& _rotate)  { mRotate = _rotate. }//todo
//	void	SetTranslation(const DCVector3& _trans)	{ mTranslation = _trans; Dirtylize();}
//	void	SetScale(float _scale)					{ mScale = _scale; Dirtylize();}
//private:
//	void	CalculateLocalToWorldMatrix();
//	void    CalculateWorldToLocalMatrix();
//	void	Dirtylize(){mUpdatedToWorld = mUpdatedToLocal = false;}
//
//	DCMatrix33		mRotate;
//	DCVector3		mTranslation;
//	float			mScale;
//
//	DCMatrix44		mMatrixCacheToWorld;
//	DCMatrix44		mMatrixCacheToLocal;
//	bool			mUpdatedToWorld;
//	bool			mUpdatedToLocal;
//};




