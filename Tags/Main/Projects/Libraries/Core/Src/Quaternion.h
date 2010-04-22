#pragma once

#include "CorePublic.h"

namespace BM
{
    class Quaternion
    {
    public:
        Float32 X;
        Float32 Y;
        Float32 Z;
        Float32 W;

    public:
#pragma region Constructors

        inline Quaternion();
        inline Quaternion(Float32 x, Float32 y, Float32 z, Float32 w);
        inline Quaternion(const Quaternion& q);
        inline Quaternion(const D3DXQUATERNION& q);

#pragma endregion

#pragma region Operators

        inline operator D3DXQUATERNION& ();
        inline operator const D3DXQUATERNION& () const;

        inline operator D3DXQUATERNION* ();
        inline operator const D3DXQUATERNION* () const;

        inline operator Float32* ();
        inline operator const Float32* () const;

        inline Float32& operator [] (int i);
        inline Float32 operator [] (int i) const;

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

        inline Quaternion& operator += (Float32 f);
        inline Quaternion& operator -= (Float32 f);
        inline Quaternion& operator *= (Float32 f);
        inline Quaternion& operator /= (Float32 f);

        inline Quaternion operator + () const;
        inline Quaternion operator - () const;

        inline Quaternion operator + (const Quaternion& q) const;
        inline Quaternion operator - (const Quaternion& q) const;
        inline Quaternion operator * (const Quaternion& q) const;

        inline Quaternion operator + (Float32 f) const;
        inline Quaternion operator - (Float32 f) const;
        inline Quaternion operator * (Float32 f) const;
        inline Quaternion operator / (Float32 f) const;

        inline friend Quaternion operator + (Float32 f, const Quaternion& q);
        inline friend Quaternion operator - (Float32 f, const Quaternion& q);
        inline friend Quaternion operator * (Float32 f, const Quaternion& q);
        inline friend Quaternion operator / (Float32 f, const Quaternion& q);

        inline Float32 operator | (const Quaternion& q) const; // dot product

#pragma endregion

#pragma region Utilities

        inline void Get(Float32& x, Float32& y, Float32& z, Float32& w) const;
        inline void Set(Float32 x, Float32 y, Float32 z, Float32 w);

        inline Float32 Dot(const Quaternion& q) const;

        inline Float32 GetLength() const;
        inline Float32 GetSquareLength() const;

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

        inline bool IsNearlyEqual(const Quaternion& q, Float32 epsilon = Math32::Epsilon) const;

        inline bool IsZero() const;
        inline bool IsNearlyZero() const;

        inline bool IsLengthZero() const;
        inline bool IsLengthNearlyZero() const;

        inline Quaternion& Inverse();
        inline Quaternion GetInversed() const;

        inline Quaternion& Conjugate();
        inline Quaternion GetConjugated() const;

        inline void FromAngleAxis(const Vector3& vAxis, Float32 fAngle);
        inline void ToAngleAxis(Vector3& vAxis, Float32& fAngle) const;

#pragma endregion

    public:
        static const Quaternion Zero;
        static const Quaternion Identity;
    };
}

#include "Quaternion.inl"
