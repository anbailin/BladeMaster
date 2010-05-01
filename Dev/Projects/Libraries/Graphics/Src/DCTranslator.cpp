#include "Graphics.h"
//
//void DCTranslator::CalculateWorldToLocalMatrix()
//{
//	//const DCVector3& v0 = reinterpret_cast<const DCVector3&>(mRotate.mm[0]);
//	//const DCVector3& v1 = reinterpret_cast<const DCVector3&>(mRotate.mm[3]);
//	//const DCVector3& v2 = reinterpret_cast<const DCVector3&>(mRotate.mm[6]);
//
//	//const float inv = 1.0f/mScale;
//	//const float inv_neg = -inv;
//	//
//	//float x40 = dot( mTranslation , v0)*inv_neg;
//	//float x41 = dot( mTranslation , v1)*inv_neg;
//	//float x42 = dot( mTranslation , v2)*inv_neg;
//
//	//mMatrixCacheToLocal = DCMatrix44(
//	//	v0.x*inv, v1.x*inv, v2.x*inv, 0.0f,
//	//	v0.y*inv, v1.y*inv, v2.y*inv, 0.0f,
//	//	v0.z*inv, v1.z*inv, v2.z*inv, 0.0f,
//	//	x40,      x41,      x42,      1.0f
//	//	);
//
//	//mUpdatedToLocal = true;
//}
//
//
//DCVector3 DCTranslator::TransformDirectionToLocal(const DCVector3 &vec)const
//{
//	DCVector3 result;
//	DCMatrix33Multiply(vec, mRotate, result);
//	return result;
//}
//
//
//DCVector3 DCTranslator::TransformDirectionToWorld(const DCVector3 &vec)const
//{
//	DCVector3 result;
//	DCMatrix33Multiply(vec, mRotate, result);
//	return result;
//}
//
//
//DCTranslator::DCTranslator():
//mUpdatedToLocal(false),mUpdatedToWorld(false)
//{
//}
//
//
//DCTranslator::DCTranslator(const DCMatrix33 &_rotate, const DCVector3 &_vec, float _scale):
//mUpdatedToLocal(false),mUpdatedToWorld(false),
//mRotate(_rotate),mTranslation(_vec),mScale(_scale)
//{
//}
//
//
//void DCTranslator::CalculateLocalToWorldMatrix()
//{
//	mMatrixCacheToWorld = DCMatrix44(
//		mRotate.m[0] * mScale, mRotate.m[1] * mScale, mRotate.m[2] * mScale, 0.f,
//		mRotate.m[3] * mScale, mRotate.m[4] * mScale, mRotate.m[5] * mScale, 0.f,
//		mRotate.m[6] * mScale, mRotate.m[7] * mScale, mRotate.m[8] * mScale, 0.f,
//		mTranslation.x, mTranslation.y, mTranslation.z, 1.f
//		);
//	mUpdatedToWorld = true;
//}

//-----------------------------------------------------------------------------------------