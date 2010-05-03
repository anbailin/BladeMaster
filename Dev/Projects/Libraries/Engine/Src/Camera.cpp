#include "EnginePrivate.h"

BMCamera::BMCamera()
{
	mNear = 0.01f;
	mFar = 100.0f;
	mWidth = 1280;
	mHeight = 720;
	mFovAngle = D3DX_PI/2;
	mAspectRatio = mWidth/mHeight;

	mPos.Set(0,5,-5);
	Vector3 at(0,0,1);
	mDir = at - mPos;
	
	mUp.X = 0.0f; mUp.Y = 1.0f; mUp.Z=0.0f;
	
	mDeltaYaw = 0.0f;
	mDeltaRoll = 0.0f;
	
	mViewMatrix = (XMMATRIX*)_mm_malloc(sizeof(XMMATRIX), 16);
	mProjMatrix = (XMMATRIX*)_mm_malloc(sizeof(XMMATRIX), 16);;
	mViewProjMatrix = (XMMATRIX*)_mm_malloc(sizeof(XMMATRIX), 16);;
}

BMCamera::~BMCamera()
{
	SafeDelete(mViewMatrix);
	SafeDelete(mProjMatrix);
	SafeDelete(mViewProjMatrix);
}

void BMCamera::Move(const Vector3& delta)
{
	mDeltaMove = delta;		
}

void BMCamera::Turn(float yaw, float roll)
{
	mDeltaYaw = yaw;
	mDeltaRoll = roll;
}

void BMCamera::Tick(float deltaTime)
{
	mPos+=mDeltaMove;
	XMVECTOR vecPos = XMLoadFloat3((const XMFLOAT3*)&mPos);

	//update dir
	XMMATRIX matrix = XMMatrixRotationRollPitchYaw(
		0.0f,
		mDeltaYaw,
		mDeltaRoll
		);
	XMVECTOR vecDir = XMLoadFloat3((const XMFLOAT3*)&mDir);
	vecDir = XMVector3Transform(vecDir, matrix);
	vecDir = XMVector3Normalize(vecDir);
	XMStoreFloat3((XMFLOAT3*)&mDir, vecDir);

	XMVECTOR vecUp = XMLoadFloat3((const XMFLOAT3*)&mUp);
	vecUp = XMVector3Transform(vecUp, matrix);
	vecUp = XMVector3Normalize(vecUp);
	XMStoreFloat3((XMFLOAT3*)&mUp, vecUp);

	*mViewMatrix = XMMatrixLookToLH(
		vecPos,
		vecDir,
		vecUp
		);
	
	*mProjMatrix = XMMatrixPerspectiveLH(
		mWidth,
		mHeight,
		mNear,
		mFar
		);

	*mProjMatrix = XMMatrixPerspectiveFovLH(
		mFovAngle,
		mAspectRatio,
		mNear,
		mFar
		);

	*mViewProjMatrix = XMMatrixMultiply(*mViewMatrix, *mProjMatrix);	
}