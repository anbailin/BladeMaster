#pragma once
/*
*	basic camera smiple impl
*/
class ENGINE_DLL BMCamera : public RefObject
{
public:
	BMCamera();
	~BMCamera();

public:
	void Move(const Vector3& delta);
	void Turn(float yaw, float roll);
	void Tick(float deltaTime);

	//attr access
public:
	XMMATRIX* GetViewMatrix() {return mViewMatrix; }
	XMMATRIX* GetProjMatrix() {return mProjMatrix; }
	XMMATRIX* GetViewProjMatrix() { return mViewProjMatrix; }

	//attr
protected:
	float	mNear;
	float   mFar;
	float   mFovAngle;
	float   mAspectRatio;
	float   mWidth;
	float   mHeight;

	Vector3 mPos;
	Vector3 mDir;
	Vector3 mUp;

	Vector3 mDeltaMove;
	float   mDeltaYaw;
	float   mDeltaRoll;

	XMMATRIX* mViewMatrix;
	XMMATRIX* mProjMatrix;
	XMMATRIX* mViewProjMatrix;
};

typedef ComPtr<BMCamera> BMCameraPtr;