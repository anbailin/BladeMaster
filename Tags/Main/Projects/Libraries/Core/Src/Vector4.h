#pragma once

#include "CorePublic.h"

namespace BM
{
    class Vector4
    {
    public:
        Float32 X;
        Float32 Y;
        Float32 Z;
        Float32 W;

    public:
#pragma region Constructors

        inline Vector4();
        inline Vector4(Float32 x, Float32 y, Float32 z, Float32 w);
        inline Vector4(const Vector3& v, Float32 w);
        inline Vector4(const Vector4& v);
        inline Vector4(const D3DXVECTOR4& v);
        inline explicit Vector4(Float32 s);

#pragma endregion

#pragma region Operators

        inline operator D3DXVECTOR4& ();
        inline operator const D3DXVECTOR4& () const;

        inline operator D3DXVECTOR4* ();
        inline operator const D3DXVECTOR4* () const;

        inline operator Float32* ();
        inline operator const Float32* () const;

		inline Float32& operator [] (int i);
		inline Float32 operator [] (int i) const;

        inline bool operator == (const Vector4& v) const;
        inline bool operator != (const Vector4& v) const;

        inline bool operator < (const Vector4& v) const;
        inline bool operator <= (const Vector4& v) const;
        inline bool operator > (const Vector4& v) const;
        inline bool operator >= (const Vector4& v) const;

        inline Vector4& operator = (const Vector4& v);
		inline Vector4& operator = (Float32 s);

        inline Vector4& operator += (const Vector4& v);
        inline Vector4& operator -= (const Vector4& v);
        inline Vector4& operator *= (const Vector4& v);
        inline Vector4& operator /= (const Vector4& v);

        inline Vector4& operator += (Float32 f);
        inline Vector4& operator -= (Float32 f);
        inline Vector4& operator *= (Float32 f);
        inline Vector4& operator /= (Float32 f);

        inline Vector4 operator + () const;
        inline Vector4 operator - () const;

        inline Vector4 operator + (const Vector4& v) const;
        inline Vector4 operator - (const Vector4& v) const;
        inline Vector4 operator * (const Vector4& v) const;
        inline Vector4 operator / (const Vector4& v) const;

        inline Vector4 operator + (Float32 f) const;
        inline Vector4 operator - (Float32 f) const;
        inline Vector4 operator * (Float32 f) const;
        inline Vector4 operator / (Float32 f) const;

        inline friend Vector4 operator + (Float32 f, const Vector4& v);
        inline friend Vector4 operator - (Float32 f, const Vector4& v);
        inline friend Vector4 operator * (Float32 f, const Vector4& v);
        inline friend Vector4 operator / (Float32 f, const Vector4& v);

        inline Float32 operator | (const Vector4& v) const; // dot product
        inline Vector4 operator ^ (const Vector4& v) const; // cross product

#pragma endregion

#pragma region Utilities

        inline void Get(Float32& x, Float32& y, Float32& z, Float32& w) const;
        inline void Set(Float32 x, Float32 y, Float32 z, Float32 w);

        inline void Set(const Vector3& v);
        inline void Set(const Vector3& v, Float32 w);

        inline Float32 Dot(const Vector4& v) const;
        inline Vector4 Cross(const Vector4& v) const;

        inline Float32 Dot2D(const Vector4& v) const;
        inline Float32 Dot3D(const Vector4& v) const;

        inline Float32 GetLength() const;
        inline Float32 GetSquareLength() const;

        inline Float32 GetLength2D() const;
        inline Float32 GetSquareLength2D() const;

        inline Float32 GetLength3D() const;
        inline Float32 GetSquareLength3D() const;

        inline Vector4& Normalize();
        inline Vector4 GetNormalized() const;

        inline Vector4& Normalize2D();
        inline Vector4 GetNormalized2D() const;

        inline Vector4& Normalize3D();
        inline Vector4 GetNormalized3D() const;

        inline Vector4& Clamp(const Vector4& min, const Vector4& max);
        inline Vector4 GetClamped(const Vector4& min, const Vector4& max) const;

        inline Vector4& Saturate();
        inline Vector4 GetSaturated() const;

        inline Vector4& Min(const Vector4& v);
        inline Vector4 GetMin(const Vector4& v) const;

        inline Vector4& Max(const Vector4& v);
        inline Vector4 GetMax(const Vector4& v) const;

        inline bool IsNearlyEqual(const Vector4& v, Float32 epsilon = Math32::Epsilon) const;

        inline bool IsZero() const;
        inline bool IsNearlyZero() const;

        inline bool IsLengthZero() const;
        inline bool IsLengthNearlyZero() const;

#pragma endregion

    public:
        static const Vector4 Zero;
        static const Vector4 One;
        static const Vector4 BaseX;
        static const Vector4 BaseY;
        static const Vector4 BaseZ;
        static const Vector4 BaseW;
    };
}

#include "Vector4.inl"
