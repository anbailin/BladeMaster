#pragma once

typedef XMFLOAT4 XMQuaternion;

inline XMFLOAT3 Lerp(float ratio, const XMFLOAT3& v0, const XMFLOAT3& v1)
{
	XMVECTOR vv0 = XMLoadFloat3(&v0);
	XMVECTOR vv1 = XMLoadFloat3(&v1);
	XMVECTOR result = XMVectorLerp(vv0, vv1, ratio);
	XMFLOAT3 output;
	XMStoreFloat3(&output, result);
	return output;
}

inline XMFLOAT4 Lerp(float ratio, const XMFLOAT4& v0, const XMFLOAT4& v1)
{
	XMVECTOR vv0 = XMLoadFloat4(&v0);
	XMVECTOR vv1 = XMLoadFloat4(&v1);
	XMVECTOR result = XMVectorLerp(vv0, vv1, ratio);
	XMFLOAT4 output;
	XMStoreFloat4(&output, result);
	return output;
}
