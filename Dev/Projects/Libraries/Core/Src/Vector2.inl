namespace BM
{
#pragma region Constructors

    inline Vector2::Vector2()
    {
        X = 0.0f;
        Y = 0.0f;
    }

    inline Vector2::Vector2(Float32 x, Float32 y)
    {
        X = x;
        Y = y;
    }

    inline Vector2::Vector2(const Vector2& v)
    {
        X = v.X;
        Y = v.Y;
    }

    inline Vector2::Vector2(const D3DXVECTOR2& v)
    {
        X = v.x;
        Y = v.y;
    }

    inline Vector2::Vector2(Float32 s)
    {
        X = s;
        Y = s;
    }

#pragma endregion

#pragma region Operators

    inline Vector2::operator D3DXVECTOR2& ()
    {
        return *((D3DXVECTOR2*)&X);
    }

    inline Vector2::operator const D3DXVECTOR2& () const
    {
        return *(const D3DXVECTOR2*)&X;
    }

    inline Vector2::operator D3DXVECTOR2* ()
    {
        return (D3DXVECTOR2*)&X;
    }

    inline Vector2::operator const D3DXVECTOR2* () const
    {
        return (const D3DXVECTOR2*)&X;
    }

    inline Vector2::operator Float32* ()
    {
        return (Float32*)&X;
    }

    inline Vector2::operator const Float32* () const
    {
        return (const Float32*)&X;
    }

    inline Float32& Vector2::operator [] (int i)
    {
        BM_Assert(i >= 0 && i < 2);
        return *(&X + i);
    }

    inline Float32 Vector2::operator [] (int i) const
    {
        BM_Assert(i >= 0 && i < 2);
        return *(&X + i);
    }

    inline bool Vector2::operator == (const Vector2& v) const
    {
        return (X == v.X && Y == v.Y);
    }

    inline bool Vector2::operator != (const Vector2& v) const
    {
        return (X != v.X || Y != v.Y);
    }

    inline bool Vector2::operator < (const Vector2& v) const
    {
        return (X < v.X && Y < v.Y);
    }

    inline bool Vector2::operator <= (const Vector2& v) const
    {
        return (X <= v.X && Y <= v.Y);
    }

    inline bool Vector2::operator > (const Vector2& v) const
    {
        return (X > v.X && Y > v.Y);
    }

    inline bool Vector2::operator >= (const Vector2& v) const
    {
        return (X >= v.X && Y >= v.Y);
    }

    inline Vector2& Vector2::operator = (const Vector2& v)
    {
        X = v.X;
        Y = v.Y;
        return *this;
    }

    inline Vector2& Vector2::operator = (Float32 s)
    {
        X = s;
        Y = s;
        return *this;
    }

    inline Vector2& Vector2::operator += (const Vector2& v)
    {
        X += v.X;
        Y += v.Y;
        return *this;
    }

    inline Vector2& Vector2::operator -= (const Vector2& v)
    {
        X -= v.X;
        Y -= v.Y;
        return *this;
    }

    inline Vector2& Vector2::operator *= (const Vector2& v)
    {
        X *= v.X;
        Y *= v.Y;
        return *this;
    }

    inline Vector2& Vector2::operator /= (const Vector2& v)
    {
        X /= v.X;
        Y /= v.Y;
        return *this;
    }

    inline Vector2& Vector2::operator += (Float32 f)
    {
        X += f;
        Y += f;
        return *this;
    }

    inline Vector2& Vector2::operator -= (Float32 f)
    {
        X -= f;
        Y -= f;
        return *this;
    }

    inline Vector2& Vector2::operator *= (Float32 f)
    {
        X *= f;
        Y *= f;
        return *this;
    }

    inline Vector2& Vector2::operator /= (Float32 f)
    {
        X /= f;
        Y /= f;
        return *this;
    }

    inline Vector2 Vector2::operator + () const
    {
        return *this;
    }

    inline Vector2 Vector2::operator - () const
    {
        return Vector2(-X, -Y);
    }

    inline Vector2 Vector2::operator + (const Vector2& v) const
    {
        return Vector2(X + v.X, Y + v.Y);
    }

    inline Vector2 Vector2::operator - (const Vector2& v) const
    {
        return Vector2(X - v.X, Y - v.Y);
    }

    inline Vector2 Vector2::operator * (const Vector2& v) const
    {
        return Vector2(X * v.X, Y * v.Y);
    }

    inline Vector2 Vector2::operator / (const Vector2& v) const
    {
        return Vector2(X / v.X, Y / v.Y);
    }

    inline Vector2 Vector2::operator + (Float32 f) const
    {
        return Vector2(X + f, Y + f);
    }

    inline Vector2 Vector2::operator - (Float32 f) const
    {
        return Vector2(X - f, Y - f);
    }

    inline Vector2 Vector2::operator * (Float32 f) const
    {
        return Vector2(X * f, Y * f);
    }

    inline Vector2 Vector2::operator / (Float32 f) const
    {
        return Vector2(X / f, Y / f);
    }

    inline /*friend*/ Vector2 operator + (Float32 f, const Vector2& v)
    {
        return Vector2(f + v.X, f + v.Y);
    }

    inline /*friend*/ Vector2 operator - (Float32 f, const Vector2& v)
    {
        return Vector2(f - v.X, f - v.Y);
    }

    inline /*friend*/ Vector2 operator * (Float32 f, const Vector2& v)
    {
        return Vector2(f * v.X, f * v.Y);
    }

    inline /*friend*/ Vector2 operator / (Float32 f, const Vector2& v)
    {
        return Vector2(f / v.X, f / v.Y);
    }

    inline Float32 Vector2::operator | (const Vector2& v) const
    {
        return Dot(v);
    }

    inline Float32 Vector2::operator ^ (const Vector2& v) const
    {
        return Cross(v);
    }

#pragma endregion

#pragma region Utilities

    inline void Vector2::Get(Float32& x, Float32& y) const
    {
        x = X;
        y = Y;
    }

    inline void Vector2::Set(Float32 x, Float32 y)
    {
        X = x;
        Y = y;
    }

    inline Float32 Vector2::Dot(const Vector2& v) const
    {
        return X * v.X +  Y * v.Y;
    }

    inline Float32 Vector2::Cross(const Vector2& v) const
    {
        return X * v.Y - Y * v.X;
    }

    inline Float32 Vector2::GetLength() const
    {
        return Sqrt(GetSquareLength());
    }

    inline Float32 Vector2::GetSquareLength() const
    {
        return X * X + Y * Y;
    }

    inline Vector2& Vector2::Normalize()
    {
        Float32 l = GetLength();
        if (!BM::IsNearlyZero(l))
        {
            X /= l;
            Y /= l;
        }
        return *this;
    }

    inline Vector2 Vector2::GetNormalized() const
    {
        return Vector2(*this).Normalize();
    }

    inline Vector2& Vector2::Clamp(const Vector2& min, const Vector2& max)
    {
        X = BM::Clamp(X, min.X, max.X);
        Y = BM::Clamp(Y, min.Y, max.Y);
        return *this;
    }

    inline Vector2 Vector2::GetClamped(const Vector2& min, const Vector2& max) const
    {
        return Vector2(*this).Clamp(min, max);
    }

    inline Vector2& Vector2::Saturate()
    {
        X = BM::Clamp(X, 0.0f, 1.0f);
        Y = BM::Clamp(Y, 0.0f, 1.0f);
        return *this;
    }

    inline Vector2 Vector2::GetSaturated() const
    {
        return Vector2(*this).Saturate();
    }

    inline Vector2& Vector2::Min(const Vector2& v)
    {
        X = BM::Min(X, v.X);
        Y = BM::Min(Y, v.Y);
        return *this;
    }

    inline Vector2 Vector2::GetMin(const Vector2& v) const
    {
        return Vector2(*this).Min(v);
    }

    inline Vector2& Vector2::Max(const Vector2& v)
    {
        X = BM::Max(X, v.X);
        Y = BM::Max(Y, v.Y);
        return *this;
    }

    inline Vector2 Vector2::GetMax(const Vector2& v) const
    {
        return Vector2(*this).Max(v);
    }

    inline Vector2& Vector2::Mid(const Vector2& v)
    {
        X = (X + v.X) * 0.5f;
        Y = (Y + v.Y) * 0.5f;
        return *this;
    }

    inline Vector2 Vector2::GetMid(const Vector2& v) const
    {
        return Vector2(*this).Mid(v);
    }

    inline bool Vector2::IsNearlyEqual(const Vector2& v, Float32 epsilon) const
    {
        return (BM::IsNearlyEqual(X, v.X, epsilon) && BM::IsNearlyEqual(Y, v.Y, epsilon));
    }

    inline bool Vector2::IsZero() const
    {
        return (*this == Zero);
    }

    inline bool Vector2::IsNearlyZero() const
    {
        return IsNearlyEqual(Zero);
    }

    inline bool Vector2::IsLengthZero() const
    {
        return (GetSquareLength() == 0.0f);
    }

    inline bool Vector2::IsLengthNearlyZero() const
    {
        return (GetSquareLength() < Sqr(Math32::Epsilon));
    }

    inline Float32 Vector2::GetDistance(const Vector2& v) const
    {
        return Sqrt(GetSquareDistance(v));
    }

    inline Float32 Vector2::GetSquareDistance(const Vector2& v) const
    {
        return (*this - v).GetSquareLength();
    }

#pragma endregion
}
