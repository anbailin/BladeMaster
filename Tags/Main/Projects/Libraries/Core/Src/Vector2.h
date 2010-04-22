#pragma once

#include "CorePublic.h"

namespace BM
{
    class CORE_API Vector2
    {
    public:
        Float32 X;
        Float32 Y;

    public:
#pragma region Constructors

        inline Vector2();
        inline Vector2(Float32 x, Float32 y);
        inline Vector2(const Vector2& v);
        inline Vector2(const D3DXVECTOR2& v);
        inline explicit Vector2(Float32 s);

#pragma endregion

#pragma region Operators

        inline operator D3DXVECTOR2& ();
        inline operator const D3DXVECTOR2& () const;

        inline operator D3DXVECTOR2* ();
        inline operator const D3DXVECTOR2* () const;

        inline operator Float32* ();
        inline operator const Float32* () const;

        inline Float32& operator [] (int i);
        inline Float32 operator [] (int i) const;

        inline bool operator == (const Vector2& v) const;
        inline bool operator != (const Vector2& v) const;

        inline bool operator < (const Vector2& v) const;
        inline bool operator <= (const Vector2& v) const;
        inline bool operator > (const Vector2& v) const;
        inline bool operator >= (const Vector2& v) const;

        inline Vector2& operator = (const Vector2& v);
        inline Vector2& operator = (Float32 s);

        inline Vector2& operator += (const Vector2& v);
        inline Vector2& operator -= (const Vector2& v);
        inline Vector2& operator *= (const Vector2& v);
        inline Vector2& operator /= (const Vector2& v);

        inline Vector2& operator += (Float32 f);
        inline Vector2& operator -= (Float32 f);
        inline Vector2& operator *= (Float32 f);
        inline Vector2& operator /= (Float32 f);

        inline Vector2 operator + () const;
        inline Vector2 operator - () const;

        inline Vector2 operator + (const Vector2& v) const;
        inline Vector2 operator - (const Vector2& v) const;
        inline Vector2 operator * (const Vector2& v) const;
        inline Vector2 operator / (const Vector2& v) const;

        inline Vector2 operator + (Float32 f) const;
        inline Vector2 operator - (Float32 f) const;
        inline Vector2 operator * (Float32 f) const;
        inline Vector2 operator / (Float32 f) const;

        inline friend Vector2 operator + (Float32 f, const Vector2& v);
        inline friend Vector2 operator - (Float32 f, const Vector2& v);
        inline friend Vector2 operator * (Float32 f, const Vector2& v);
        inline friend Vector2 operator / (Float32 f, const Vector2& v);

        inline Float32 operator | (const Vector2& v) const;   // dot product
        inline Float32 operator ^ (const Vector2& v) const;   // cross product

#pragma endregion

#pragma region Utilities

        inline void Get(Float32& x, Float32& y) const;
        inline void Set(Float32 x, Float32 y);

        inline Float32 Dot(const Vector2& v) const;
        inline Float32 Cross(const Vector2& v) const;

        inline Float32 GetLength() const;
        inline Float32 GetSquareLength() const;

        inline Vector2& Normalize();
        inline Vector2 GetNormalized() const;

        inline Vector2& Clamp(const Vector2& min, const Vector2& max);
        inline Vector2 GetClamped(const Vector2& min, const Vector2& max) const;

        inline Vector2& Saturate();
        inline Vector2 GetSaturated() const;

        inline Vector2& Min(const Vector2& v);
        inline Vector2 GetMin(const Vector2& v) const;

        inline Vector2& Max(const Vector2& v);
        inline Vector2 GetMax(const Vector2& v) const;

        inline Vector2& Mid(const Vector2& v);
        inline Vector2 GetMid(const Vector2& v) const;

        inline bool IsNearlyEqual(const Vector2& v, Float32 epsilon = Math32::Epsilon) const;

        inline bool IsZero() const;
        inline bool IsNearlyZero() const;

        inline bool IsLengthZero() const;
        inline bool IsLengthNearlyZero() const;

        inline Float32 GetDistance(const Vector2& v) const;
        inline Float32 GetSquareDistance(const Vector2& v) const;

#pragma endregion

    public:
        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 BaseX;
        static const Vector2 BaseY;
    };
}

#include "Vector2.inl"
