#pragma once

namespace BM
{
    class CORE_DLL Vector4
    {
    public:
        f32 X;
        f32 Y;
        f32 Z;
        f32 W;

    public:
#pragma region Constructors

        inline Vector4();
        inline Vector4(f32 x, f32 y, f32 z, f32 w);
        inline Vector4(const Vector3& v, f32 w);
        inline Vector4(const Vector4& v);
        inline Vector4(const D3DXVECTOR4& v);
        inline explicit Vector4(f32 s);

#pragma endregion

#pragma region Operators

        inline operator D3DXVECTOR4& ();
        inline operator const D3DXVECTOR4& () const;

        inline operator D3DXVECTOR4* ();
        inline operator const D3DXVECTOR4* () const;

        inline operator f32* ();
        inline operator const f32* () const;

		inline f32& operator [] (int i);
		inline f32 operator [] (int i) const;

        inline bool operator == (const Vector4& v) const;
        inline bool operator != (const Vector4& v) const;

        inline bool operator < (const Vector4& v) const;
        inline bool operator <= (const Vector4& v) const;
        inline bool operator > (const Vector4& v) const;
        inline bool operator >= (const Vector4& v) const;

        inline Vector4& operator = (const Vector4& v);
		inline Vector4& operator = (f32 s);

        inline Vector4& operator += (const Vector4& v);
        inline Vector4& operator -= (const Vector4& v);
        inline Vector4& operator *= (const Vector4& v);
        inline Vector4& operator /= (const Vector4& v);

        inline Vector4& operator += (f32 f);
        inline Vector4& operator -= (f32 f);
        inline Vector4& operator *= (f32 f);
        inline Vector4& operator /= (f32 f);

        inline Vector4 operator + () const;
        inline Vector4 operator - () const;

        inline Vector4 operator + (const Vector4& v) const;
        inline Vector4 operator - (const Vector4& v) const;
        inline Vector4 operator * (const Vector4& v) const;
        inline Vector4 operator / (const Vector4& v) const;

        inline Vector4 operator + (f32 f) const;
        inline Vector4 operator - (f32 f) const;
        inline Vector4 operator * (f32 f) const;
        inline Vector4 operator / (f32 f) const;

        inline friend Vector4 operator + (f32 f, const Vector4& v);
        inline friend Vector4 operator - (f32 f, const Vector4& v);
        inline friend Vector4 operator * (f32 f, const Vector4& v);
        inline friend Vector4 operator / (f32 f, const Vector4& v);

        inline f32 operator | (const Vector4& v) const; // dot product
        inline Vector4 operator ^ (const Vector4& v) const; // cross product

#pragma endregion

#pragma region Utilities

        inline void Get(f32& x, f32& y, f32& z, f32& w) const;
        inline void Set(f32 x, f32 y, f32 z, f32 w);

        inline void Set(const Vector3& v);
        inline void Set(const Vector3& v, f32 w);

        inline f32 Dot(const Vector4& v) const;
        inline Vector4 Cross(const Vector4& v) const;

        inline f32 Dot2D(const Vector4& v) const;
        inline f32 Dot3D(const Vector4& v) const;

        inline f32 GetLength() const;
        inline f32 GetSquareLength() const;

        inline f32 GetLength2D() const;
        inline f32 GetSquareLength2D() const;

        inline f32 GetLength3D() const;
        inline f32 GetSquareLength3D() const;

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

        inline bool IsNearlyEqual(const Vector4& v, f32 epsilon = Math32::Epsilon) const;

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
