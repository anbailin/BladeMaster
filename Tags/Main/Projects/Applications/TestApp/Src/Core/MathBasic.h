#pragma once
#pragma warning (disable:4201)

class DCMatrix33;

#define kErrorTolerrence (1e-6f)
#define kPI 3.141592653589793 
#define kPIf 3.14159265f

typedef XMFLOAT4 XMQuaternion;

template< class T >
inline T Abs(const T& val)
{
	return (T>0)?T:-T;
}

inline float Abs(float val)
{
	return fabsf(val);
}

inline double Abs(double val)
{
	return fabs(val);
}

inline bool IsPowerOfTwo(uint32 val)
{
	return (val&(val-1))==0;
}

inline uint32 PowerOfTwo(uint32 val)
{
	//assert(IsPowerOfTwo(val)==true);
	uint32 result = 0;
	while(val>0)
	{
		val = val>>1;
		result++;
	}
	return result;
}


template< class T > inline T Max( const T A, const T B )
{
	return (A>=B) ? A : B;
}

template< class T > inline T Min( const T a, const T b)
{
	return a<b?a:b;
}

template< class T > 
inline T Interpolate(float ratio, const T& v0, const T& v1)
{
	return v0*(1-ratio) + v1*ratio;
}

template< class T > 
inline T Lerp(float ratio, const T& v0, const T& v1)
{
	return v0*(1-ratio) + v1*ratio;
}

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

template< class T >
inline void Swap(T& _first, T& _second)
{
	T temp;
	temp = _first;
	_first = _second;
	_second = temp;
}

template< class T >
inline T& Clamp(T& v, const T& down, const T& up)
{
	v = Min<T>(Max<T>(v,down),up);
	return v;
}

template< class T >
inline bool DeltaEqual(const T& v0,const T& v1)
{
	return Abs(v0 - v1)<=kErrorTolerrence;
}

template< class T >  
inline bool IsZero(T val)
{
	return Abs(val)<=kErrorTolerrence;
}

DCMatrix33 Adjoint(const DCMatrix33& mat);