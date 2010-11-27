#include "Utilities.h"

#pragma region Constructors

inline Vector3::Vector3()
{
    X = 0.0f;
    Y = 0.0f;
    Z = 0.0f;
}

inline Vector3::Vector3(f32 x, f32 y, f32 z)
{
    X = x;
    Y = y;
    Z = z;
}

inline Vector3::Vector3(const Vector3& v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
}

inline Vector3::Vector3(const D3DXVECTOR3& v)
{
    X = v.x;
    Y = v.y;
    Z = v.z;
}

inline Vector3::Vector3(f32 s)
{
    X = s;
    Y = s;
    Z = s;
}

#pragma endregion

#pragma region Operators

inline Vector3::operator D3DXVECTOR3& ()
{
    return *(D3DXVECTOR3*)&X;
}

inline Vector3::operator const D3DXVECTOR3& () const
{
    return *(const D3DXVECTOR3*)&X;
}

inline Vector3::operator D3DXVECTOR3* ()
{
    return (D3DXVECTOR3*)&X;
}

inline Vector3::operator const D3DXVECTOR3* () const
{
    return (const D3DXVECTOR3*)&X;
}

inline Vector3::operator f32* ()
{
    return (f32*)&X;
}

inline Vector3::operator const f32* () const
{
    return (const f32*)&X;
}

inline f32& Vector3::operator [] (int i)
{
    BM_Assert(i >= 0 && i < 3);
    return *(&X + i);
}

inline f32 Vector3::operator [] (int i) const
{
    BM_Assert(i >= 0 && i < 3);
    return *(&X + i);
}

inline bool Vector3::operator == (const Vector3& v) const
{
    return (X == v.X && Y == v.Y && Z == v.Z);
}

inline bool Vector3::operator != (const Vector3& v) const
{
    return (X != v.X || Y != v.Y || Z != v.Z);
}

inline bool Vector3::operator < (const Vector3& v) const
{
    return (X < v.X && Y < v.Y && Z < v.Z);
}

inline bool Vector3::operator <= (const Vector3& v) const
{
    return (X <= v.X && Y <= v.Y && Z <= v.Z);
}

inline bool Vector3::operator > (const Vector3& v) const
{
    return (X > v.X && Y > v.Y && Z > v.Z);
}

inline bool Vector3::operator >= (const Vector3& v) const
{
    return (X >= v.X && Y >= v.Y && Z >= v.Z);
}

inline Vector3& Vector3::operator = (const Vector3& v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
    return *this;
}

inline Vector3& Vector3::operator = (f32 s)
{
    X = s;
    Y = s;
    Z = s;
    return *this;
}

inline Vector3& Vector3::operator += (const Vector3& v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    return *this;
}

inline Vector3& Vector3::operator -= (const Vector3& v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    return *this;
}

inline Vector3& Vector3::operator *= (const Vector3& v)
{
    X *= v.X;
    Y *= v.Y;
    Z *= v.Z;
    return *this;
}

inline Vector3& Vector3::operator /= (const Vector3& v)
{
    X /= v.X;
    Y /= v.Y;
    Z /= v.Z;
    return *this;
}

inline Vector3& Vector3::operator += (f32 f)
{
    X += f;
    Y += f;
    Z += f;
    return *this;
}

inline Vector3& Vector3::operator -= (f32 f)
{
    X -= f;
    Y -= f;
    Z -= f;
    return *this;
}

inline Vector3& Vector3::operator *= (f32 f)
{
    X *= f;
    Y *= f;
    Z *= f;
    return *this;
}

inline Vector3& Vector3::operator /= (f32 f)
{
    X /= f;
    Y /= f;
    Z /= f;
    return *this;
}

inline Vector3 Vector3::operator + () const
{
    return *this;
}

inline Vector3 Vector3::operator - () const
{
    return Vector3(-X, -Y, -Z);
}

inline Vector3 Vector3::operator + (const Vector3& v) const
{
    return Vector3(X + v.X, Y + v.Y, Z + v.Z);
}

inline Vector3 Vector3::operator - (const Vector3& v) const
{
    return Vector3(X - v.X, Y - v.Y, Z - v.Z);
}

inline Vector3 Vector3::operator * (const Vector3& v) const
{
    return Vector3(X * v.X, Y * v.Y, Z * v.Z);
}

inline Vector3 Vector3::operator / (const Vector3& v) const
{
    return Vector3(X / v.X, Y / v.Y, Z / v.Z);
}

inline Vector3 Vector3::operator + (f32 f) const
{
    return Vector3(X + f, Y + f, Z + f);
}

inline Vector3 Vector3::operator - (f32 f) const
{
    return Vector3(X - f, Y - f, Z - f);
}

inline Vector3 Vector3::operator * (f32 f) const
{
    return Vector3(X * f, Y * f, Z * f);
}

inline Vector3 Vector3::operator / (f32 f) const
{
    return Vector3(X / f, Y / f, Z / f);
}

inline /*friend*/ Vector3 operator + (f32 f, const Vector3& v)
{
    return Vector3(f + v.X, f + v.Y, f + v.Z);
}

inline /*friend*/ Vector3 operator - (f32 f, const Vector3& v)
{
    return Vector3(f - v.X, f - v.Y, f - v.Z);
}

inline /*friend*/ Vector3 operator * (f32 f, const Vector3& v)
{
    return Vector3(f * v.X, f * v.Y, f * v.Z);
}

inline /*friend*/ Vector3 operator / (f32 f, const Vector3& v)
{
    return Vector3(f / v.X, f / v.Y, f / v.Z);
}

inline f32 Vector3::operator | (const Vector3& v) const
{
    return Dot(v);
}

inline Vector3 Vector3::operator ^ (const Vector3& v) const
{
    return Cross(v);
}

inline f32 Vector3::operator % (const Vector3& v) const
{
    return Dot2D(v);
}

#pragma endregion

#pragma region Utilities

inline void Vector3::Get(f32& x, f32& y, f32& z) const
{
    x = X;
    y = Y;
    z = Z;
}

inline void Vector3::Set(f32 x, f32 y, f32 z)
{
    X = x;
    Y = y;
    Z = z;
}

inline f32 Vector3::Dot(const Vector3& v) const
{
    return X * v.X +  Y * v.Y + Z * v.Z;
}

inline Vector3 Vector3::Cross(const Vector3& v) const
{
    return Vector3(Y * v.Z - Z * v.Y, Z * v.X - X * v.Z, X * v.Y - Y * v.X);
}

inline f32 Vector3::Dot2D(const Vector3& v) const
{
    return X * v.X +  Y * v.Y;
}

inline f32 Vector3::GetLength() const
{
    return Sqrt(GetSquareLength());
}

inline f32 Vector3::GetSquareLength() const
{
    return X * X + Y * Y + Z * Z;
}

inline f32 Vector3::GetLength2D() const
{
    return Sqrt(GetSquareLength2D());
}

inline f32 Vector3::GetSquareLength2D() const
{
    return X * X + Y * Y;
}

inline Vector3& Vector3::Normalize()
{
    f32 l = GetLength();
    if (!::IsNearlyZero(l))
    {
        X /= l;
        Y /= l;
        Z /= l;
    }
    return *this;
}

inline Vector3 Vector3::GetNormalized() const
{
    return Vector3(*this).Normalize();
}

inline Vector3& Vector3::Normalize2D()
{
    f32 l = GetLength2D();
    if (!::IsNearlyZero(l))
    {
        X /= l;
        Y /= l;
    }
    Z = 0.0f;
    return *this;
}

inline Vector3 Vector3::GetNormalized2D() const
{
    return Vector3(*this).Normalize2D();
}

inline Vector3& Vector3::Clamp(const Vector3& min, const Vector3& max)
{
    X = ::Clamp(X, min.X, max.X);
    Y = ::Clamp(Y, min.Y, max.Y);
    Z = ::Clamp(Z, min.Z, max.Z);
    return *this;
}

inline Vector3 Vector3::GetClamped(const Vector3& min, const Vector3& max) const
{
    return Vector3(*this).Clamp(min, max);
}

inline Vector3& Vector3::Saturate()
{
    X = ::Clamp(X, 0.0f, 1.0f);
    Y = ::Clamp(Y, 0.0f, 1.0f);
    Z = ::Clamp(Z, 0.0f, 1.0f);
    return *this;
}

inline Vector3 Vector3::GetSaturated() const
{
    return Vector3(*this).Saturate();
}

inline Vector3& Vector3::Min(const Vector3& v)
{
    X = ::Min(X, v.X);
    Y = ::Min(Y, v.Y);
    Z = ::Min(Z, v.Z);
    return *this;
}

inline Vector3 Vector3::GetMin(const Vector3& v) const
{
    return Vector3(*this).Min(v);
}

inline Vector3& Vector3::Max(const Vector3& v)
{
    X = ::Max(X, v.X);
    Y = ::Max(Y, v.Y);
    Z = ::Max(Z, v.Z);
    return *this;
}

inline Vector3 Vector3::GetMax(const Vector3& v) const
{
    return Vector3(*this).Max(v);
}

inline Vector3& Vector3::Mid(const Vector3& v)
{
    X = (X + v.X) * 0.5f;
    Y = (Y + v.Y) * 0.5f;
    Z = (Z + v.Z) * 0.5f;
    return *this;
}

inline Vector3 Vector3::GetMid(const Vector3& v) const
{
    return Vector3(*this).Mid(v);
}

inline bool Vector3::IsNearlyEqual(const Vector3& v, f32 epsilon) const
{
    return (::IsNearlyEqual(X, v.X, epsilon) && ::IsNearlyEqual(Y, v.Y, epsilon) && ::IsNearlyEqual(Z, v.Z, epsilon));
}

inline bool Vector3::IsZero() const
{
    return (*this == Zero);
}

inline bool Vector3::IsNearlyZero() const
{
    return IsNearlyEqual(Zero);
}

inline bool Vector3::IsLengthZero() const
{
    return (GetSquareLength() == 0.0f);
}

inline bool Vector3::IsLengthNearlyZero() const
{
    return (GetSquareLength() < Sqr(Math32::Epsilon));
}

inline f32 Vector3::GetDistance(const Vector3& v) const
{
    return Sqrt(GetSquareDistance(v));
}

inline f32 Vector3::GetSquareDistance(const Vector3& v) const
{
    return (*this - v).GetSquareLength();
}

inline f32 Vector3::GetDistance2D(const Vector3& v) const
{
    return Sqrt(GetSquareDistance2D(v));
}

inline f32 Vector3::GetSquareDistance2D(const Vector3& v) const
{
    return (*this - v).GetSquareLength2D();
}

#pragma endregion
