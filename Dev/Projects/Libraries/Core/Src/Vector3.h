#pragma once

namespace BM
{
    class CORE_DLL Vector3
    {
    public:
        Float32 X;
        Float32 Y;
        Float32 Z;

    public:
#pragma region Constructors

        inline Vector3();
        inline Vector3(Float32 x, Float32 y, Float32 z);
        inline Vector3(const Vector3& v);
        inline Vector3(const D3DXVECTOR3& v);
        inline explicit Vector3(Float32 s);

#pragma endregion

#pragma region Operators

        inline operator D3DXVECTOR3& ();
        inline operator const D3DXVECTOR3& () const;

        inline operator D3DXVECTOR3* ();
        inline operator const D3DXVECTOR3* () const;

        inline operator Float32* ();
        inline operator const Float32* () const;

		inline Float32& operator [] (int i);
		inline Float32 operator [] (int i) const;

        inline bool operator == (const Vector3& v) const;
        inline bool operator != (const Vector3& v) const;

        inline bool operator < (const Vector3& v) const;
        inline bool operator <= (const Vector3& v) const;
        inline bool operator > (const Vector3& v) const;
        inline bool operator >= (const Vector3& v) const;

        inline Vector3& operator = (const Vector3& v);
		inline Vector3& operator = (Float32 s);

        inline Vector3& operator += (const Vector3& v);
        inline Vector3& operator -= (const Vector3& v);
        inline Vector3& operator *= (const Vector3& v);
        inline Vector3& operator /= (const Vector3& v);

        inline Vector3& operator += (Float32 f);
        inline Vector3& operator -= (Float32 f);
        inline Vector3& operator *= (Float32 f);
        inline Vector3& operator /= (Float32 f);

        inline Vector3 operator + () const;
        inline Vector3 operator - () const;

        inline Vector3 operator + (const Vector3& v) const;
        inline Vector3 operator - (const Vector3& v) const;
        inline Vector3 operator * (const Vector3& v) const;
        inline Vector3 operator / (const Vector3& v) const;

        inline Vector3 operator + (Float32 f) const;
        inline Vector3 operator - (Float32 f) const;
        inline Vector3 operator * (Float32 f) const;
        inline Vector3 operator / (Float32 f) const;

        inline friend Vector3 operator + (Float32 f, const Vector3& v);
        inline friend Vector3 operator - (Float32 f, const Vector3& v);
        inline friend Vector3 operator * (Float32 f, const Vector3& v);
        inline friend Vector3 operator / (Float32 f, const Vector3& v);

        inline Float32 operator | (const Vector3& v) const; // dot product
        inline Vector3 operator ^ (const Vector3& v) const; // cross product
        inline Float32 operator % (const Vector3& v) const; // 2D dot product

#pragma endregion

#pragma region Utilities

        inline void Get(Float32& x, Float32& y, Float32& z) const;
        inline void Set(Float32 x, Float32 y, Float32 z);

        inline Float32 Dot(const Vector3& v) const;
        inline Vector3 Cross(const Vector3& v) const;

        inline Float32 Dot2D(const Vector3& v) const;

        inline Float32 GetLength() const;
        inline Float32 GetSquareLength() const;

        inline Float32 GetLength2D() const;
        inline Float32 GetSquareLength2D() const;

        inline Vector3& Normalize();
        inline Vector3 GetNormalized() const;

        inline Vector3& Normalize2D();
        inline Vector3 GetNormalized2D() const;

        inline Vector3& Clamp(const Vector3& min, const Vector3& max);
        inline Vector3 GetClamped(const Vector3& min, const Vector3& max) const;

        inline Vector3& Saturate();
        inline Vector3 GetSaturated() const;

        inline Vector3& Min(const Vector3& v);
        inline Vector3 GetMin(const Vector3& v) const;

        inline Vector3& Max(const Vector3& v);
        inline Vector3 GetMax(const Vector3& v) const;

        inline Vector3& Mid(const Vector3& v);
        inline Vector3 GetMid(const Vector3& v) const;

        inline bool IsNearlyEqual(const Vector3& v, Float32 epsilon = Math32::Epsilon) const;

        inline bool IsZero() const;
        inline bool IsNearlyZero() const;

        inline bool IsLengthZero() const;
        inline bool IsLengthNearlyZero() const;

        inline Float32 GetDistance(const Vector3& v) const;
        inline Float32 GetSquareDistance(const Vector3& v) const;

        inline Float32 GetDistance2D(const Vector3& v) const;
        inline Float32 GetSquareDistance2D(const Vector3& v) const;

#pragma endregion

    public:
        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 BaseX;
        static const Vector3 BaseY;
        static const Vector3 BaseZ;
    };

    typedef Vector3 Vector;
}

#include "Vector3.inl"

#define dot2D   %
#define dot3D   |
#define cross   ^
