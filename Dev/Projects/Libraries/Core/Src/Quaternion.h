#pragma once

namespace BM
{
    class CORE_DLL Quaternion
    {
    public:
        f32 X;
        f32 Y;
        f32 Z;
        f32 W;

    public:
#pragma region Constructors

        inline Quaternion();
        inline Quaternion(f32 x, f32 y, f32 z, f32 w);
        inline Quaternion(const Quaternion& q);
        inline Quaternion(const D3DXQUATERNION& q);

#pragma endregion

#pragma region Operators

        inline operator D3DXQUATERNION& ();
        inline operator const D3DXQUATERNION& () const;

        inline operator D3DXQUATERNION* ();
        inline operator const D3DXQUATERNION* () const;

        inline operator f32* ();
        inline operator const f32* () const;

        inline f32& operator [] (int i);
        inline f32 operator [] (int i) const;

        inline bool operator == (const Quaternion& q) const;
        inline bool operator != (const Quaternion& q) const;

        inline bool operator < (const Quaternion& q) const;
        inline bool operator <= (const Quaternion& q) const;
        inline bool operator > (const Quaternion& q) const;
        inline bool operator >= (const Quaternion& q) const;

        inline Quaternion& operator = (const Quaternion& q);

        inline Quaternion& operator += (const Quaternion& q);
        inline Quaternion& operator -= (const Quaternion& q);
        inline Quaternion& operator *= (const Quaternion& q);

        inline Quaternion& operator += (f32 f);
        inline Quaternion& operator -= (f32 f);
        inline Quaternion& operator *= (f32 f);
        inline Quaternion& operator /= (f32 f);

        inline Quaternion operator + () const;
        inline Quaternion operator - () const;

        inline Quaternion operator + (const Quaternion& q) const;
        inline Quaternion operator - (const Quaternion& q) const;
        inline Quaternion operator * (const Quaternion& q) const;

        inline Quaternion operator + (f32 f) const;
        inline Quaternion operator - (f32 f) const;
        inline Quaternion operator * (f32 f) const;
        inline Quaternion operator / (f32 f) const;

        inline friend Quaternion operator + (f32 f, const Quaternion& q);
        inline friend Quaternion operator - (f32 f, const Quaternion& q);
        inline friend Quaternion operator * (f32 f, const Quaternion& q);
        inline friend Quaternion operator / (f32 f, const Quaternion& q);

        inline f32 operator | (const Quaternion& q) const; // dot product

#pragma endregion

#pragma region Utilities

        inline void Get(f32& x, f32& y, f32& z, f32& w) const;
        inline void Set(f32 x, f32 y, f32 z, f32 w);

        inline f32 Dot(const Quaternion& q) const;

        inline f32 GetLength() const;
        inline f32 GetSquareLength() const;

        inline Quaternion& Normalize();
        inline Quaternion GetNormalized() const;

        inline Quaternion& Clamp(const Quaternion& min, const Quaternion& max);
        inline Quaternion GetClamped(const Quaternion& min, const Quaternion& max) const;

        inline Quaternion& Saturate();
        inline Quaternion GetSaturated() const;

        inline Quaternion& Min(const Quaternion& q);
        inline Quaternion GetMin(const Quaternion& q) const;

        inline Quaternion& Max(const Quaternion& q);
        inline Quaternion GetMax(const Quaternion& q) const;

        inline bool IsNearlyEqual(const Quaternion& q, f32 epsilon = Math32::Epsilon) const;

        inline bool IsZero() const;
        inline bool IsNearlyZero() const;

        inline bool IsLengthZero() const;
        inline bool IsLengthNearlyZero() const;

        inline Quaternion& Inverse();
        inline Quaternion GetInversed() const;

        inline Quaternion& Conjugate();
        inline Quaternion GetConjugated() const;

        inline void FromAngleAxis(const Vector3& vAxis, f32 fAngle);
        inline void ToAngleAxis(Vector3& vAxis, f32& fAngle) const;

#pragma endregion

    public:
        static const Quaternion Zero;
        static const Quaternion Identity;
    };
}

#include "Quaternion.inl"
