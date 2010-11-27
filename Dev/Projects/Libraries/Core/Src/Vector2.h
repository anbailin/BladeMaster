#pragma once

class CORE_DLL Vector2
{
public:
    f32 X;
    f32 Y;

public:
#pragma region Constructors

    inline Vector2();
    inline Vector2(f32 x, f32 y);
    inline Vector2(const Vector2& v);
    inline Vector2(const D3DXVECTOR2& v);
    inline explicit Vector2(f32 s);

#pragma endregion

#pragma region Operators

    inline operator D3DXVECTOR2& ();
    inline operator const D3DXVECTOR2& () const;

    inline operator D3DXVECTOR2* ();
    inline operator const D3DXVECTOR2* () const;

    inline operator f32* ();
    inline operator const f32* () const;

    inline f32& operator [] (int i);
    inline f32 operator [] (int i) const;

    inline bool operator == (const Vector2& v) const;
    inline bool operator != (const Vector2& v) const;

    inline bool operator < (const Vector2& v) const;
    inline bool operator <= (const Vector2& v) const;
    inline bool operator > (const Vector2& v) const;
    inline bool operator >= (const Vector2& v) const;

    inline Vector2& operator = (const Vector2& v);
    inline Vector2& operator = (f32 s);

    inline Vector2& operator += (const Vector2& v);
    inline Vector2& operator -= (const Vector2& v);
    inline Vector2& operator *= (const Vector2& v);
    inline Vector2& operator /= (const Vector2& v);

    inline Vector2& operator += (f32 f);
    inline Vector2& operator -= (f32 f);
    inline Vector2& operator *= (f32 f);
    inline Vector2& operator /= (f32 f);

    inline Vector2 operator + () const;
    inline Vector2 operator - () const;

    inline Vector2 operator + (const Vector2& v) const;
    inline Vector2 operator - (const Vector2& v) const;
    inline Vector2 operator * (const Vector2& v) const;
    inline Vector2 operator / (const Vector2& v) const;

    inline Vector2 operator + (f32 f) const;
    inline Vector2 operator - (f32 f) const;
    inline Vector2 operator * (f32 f) const;
    inline Vector2 operator / (f32 f) const;

    inline friend Vector2 operator + (f32 f, const Vector2& v);
    inline friend Vector2 operator - (f32 f, const Vector2& v);
    inline friend Vector2 operator * (f32 f, const Vector2& v);
    inline friend Vector2 operator / (f32 f, const Vector2& v);

    inline f32 operator | (const Vector2& v) const;   // dot product
    inline f32 operator ^ (const Vector2& v) const;   // cross product

#pragma endregion

#pragma region Utilities

    inline void Get(f32& x, f32& y) const;
    inline void Set(f32 x, f32 y);

    inline f32 Dot(const Vector2& v) const;
    inline f32 Cross(const Vector2& v) const;

    inline f32 GetLength() const;
    inline f32 GetSquareLength() const;

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

    inline bool IsNearlyEqual(const Vector2& v, f32 epsilon = Math32::Epsilon) const;

    inline bool IsZero() const;
    inline bool IsNearlyZero() const;

    inline bool IsLengthZero() const;
    inline bool IsLengthNearlyZero() const;

    inline f32 GetDistance(const Vector2& v) const;
    inline f32 GetSquareDistance(const Vector2& v) const;

#pragma endregion

public:
    static const Vector2 Zero;
    static const Vector2 One;
    static const Vector2 BaseX;
    static const Vector2 BaseY;
};

#include "Vector2.inl"