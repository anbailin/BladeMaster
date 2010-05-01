//===============================================================================
// Copyright 2007, ZJUGDA
//===============================================================================

#pragma once

//class DCCamera
//{
//public:
//	DCCamera();
//	~DCCamera();
//
//	void LookAt(const DCVector3& eye, const DCVector3& point, const DCVector3& up);
//	void LookDir(const DCVector3& eye, const DCVector3& dir, const DCVector3& up);
//
//	void Transform(const DCMatrix44& mat);
//	void Rotate(const DCMatrix33& rotate);
//
//	void SetPerspectiveFov(float ratio, float fov, float near, float far);
//
//	const DCMatrix44& GetViewMatrix();
//	const DCMatrix44& GetProjectionMatrix();
//	const DCMatrix44& GetViewProjMatrix();
//
//	void	Update();
//private:
//	DCVector3	mPos;
//	DCVector3	mRight;
//	DCVector3	mUp;
//	DCVector3	mViewDir;
//
//	float		mAspectRatio;
//	float		mFieldOfView;
//	float		mNear;
//	float		mFar;
//
//	DCMatrix44	mViewMatrix;
//	DCMatrix44	mProjMatrix;
//	DCMatrix44	mViewProjMatrix;
//};
//
////--dc camera------------------------------------------------------------------
//void DCCamera::LookAt(const DCVector3& eye, const DCVector3& point, const DCVector3& up)
//{
//	mPos = eye;
//
//	mViewDir = point - eye;
//	mViewDir.Normalize();
//
//	mRight = Cross(up,mViewDir);
//	mRight.Normalize();
//
//	mUp = Cross(mViewDir,mRight);         
//}
//
//void DCCamera::LookDir(const DCVector3& eye, const DCVector3& dir, const DCVector3& up)
//{
//	mPos = eye;
//
//	mViewDir = dir;
//	mViewDir.Normalize();
//
//	mRight = Cross(up,mViewDir);
//	mRight.Normalize();
//
//	mUp = Cross(mViewDir,mRight); 
//}
//
//void DCCamera::Transform(const DCMatrix44 &mat)
//{
//	float a,b,c;
//
//	a = mPos.x * mat.m00 + mPos.y * mat.m10 + mPos.z * mat.m20 + mat.m30;
//	b = mPos.x * mat.m01 + mPos.y * mat.m11 + mPos.z * mat.m21 + mat.m31;
//	c = mPos.x * mat.m02 + mPos.y * mat.m12 + mPos.z * mat.m22 + mat.m32;
//	mPos.Set(a,b,c);
//
//	a = mViewDir.x * mat.m00 + mViewDir.y * mat.m10 + mViewDir.z * mat.m20;
//	b = mViewDir.x * mat.m01 + mViewDir.y * mat.m11 + mViewDir.z * mat.m21;
//	c = mViewDir.x * mat.m02 + mViewDir.y * mat.m12 + mViewDir.z * mat.m22;
//	mViewDir.Set(a,b,c);
//
//	a = mUp.x * mat.m00 + mUp.y * mat.m10 + mUp.z * mat.m20;
//	b = mUp.x * mat.m01 + mUp.y * mat.m11 + mUp.z * mat.m21;
//	c = mUp.x * mat.m02 + mUp.y * mat.m12 + mUp.z * mat.m22;
//	mUp.Set(a,b,c);
//
//	a = mRight.x * mat.m00 + mRight.y * mat.m10 + mRight.z * mat.m20;
//	b = mRight.x * mat.m01 + mRight.y * mat.m11 + mRight.z * mat.m21;
//	c = mRight.x * mat.m02 + mRight.y * mat.m12 + mRight.z * mat.m22;
//	mRight.Set(a,b,c);	
//}
//
//void DCCamera::Rotate(const DCMatrix33& mat)
//{
//	float a,b,c;
//
//	a = mViewDir.x * mat.m00 + mViewDir.y * mat.m10 + mViewDir.z * mat.m20;
//	b = mViewDir.x * mat.m01 + mViewDir.y * mat.m11 + mViewDir.z * mat.m21;
//	c = mViewDir.x * mat.m02 + mViewDir.y * mat.m12 + mViewDir.z * mat.m22;
//	mViewDir.Set(a,b,c);
//
//	a = mUp.x * mat.m00 + mUp.y * mat.m10 + mUp.z * mat.m20;
//	b = mUp.x * mat.m01 + mUp.y * mat.m11 + mUp.z * mat.m21;
//	c = mUp.x * mat.m02 + mUp.y * mat.m12 + mUp.z * mat.m22;
//	mUp.Set(a,b,c);
//
//	a = mRight.x * mat.m00 + mRight.y * mat.m10 + mRight.z * mat.m20;
//	b = mRight.x * mat.m01 + mRight.y * mat.m11 + mRight.z * mat.m21;
//	c = mRight.x * mat.m02 + mRight.y * mat.m12 + mRight.z * mat.m22;
//	mRight.Set(a,b,c);	
//}
//
//void DCCamera::Update()
//{
//	mViewMatrix.Set(
//		mRight.x,			mUp.x,			mViewDir.x,			0,
//		mRight.y,			mUp.y,			mViewDir.y,			0,
//		mRight.z,			mUp.z,			mViewDir.z,			0,
//		-dot(mPos,mRight),	-dot(mPos,mUp),	-dot(mPos,mViewDir),1
//		);
//
//
//	const float w = 1/tan(mFieldOfView);
//	const float h = mAspectRatio * w;
//	const float q = mFar/(mFar - mNear);
//	const float k = -q*mNear;
//	mProjMatrix.Set(
//		w,0,0,0,
//		0,h,0,0,
//		0,0,q,1,
//		0,0,k,0	);
//
//	mViewProjMatrix = mViewMatrix * mProjMatrix;
//}