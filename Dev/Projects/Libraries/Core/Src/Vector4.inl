namespace BM
{
#pragma region Constructors

    inline Vector4::Vector4()
    {
        X = 0.0f;
        Y = 0.0f;
        Z = 0.0f;
        W = 0.0f;
    }

    inline Vector4::Vector4(Float32 x, Float32 y, Float32 z, Float32 w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

    inline Vector4::Vector4(const Vector3& v, Float32 w)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        W = w;
    }

    inline Vector4::Vector4(const Vector4& v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        W = v.W;
    }

    inline Vector4::Vector4(const D3DXVECTOR4& v)
    {
        X = v.x;
        Y = v.y;
        Z = v.z;
        W = v.w;
    }

    inline Vector4::Vector4(Float32 s)
    {
        X = s;
        Y = s;
        Z = s;
        W = s;
    }

#pragma endregion

#pragma region Operators

    inline Vector4::operator D3DXVECTOR4& ()
    {
        return *(D3DXVECTOR4*)&X;
    }

    inline Vector4::operator const D3DXVECTOR4& () const
    {
        return *(const D3DXVECTOR4*)&X;
    }

    inline Vector4::operator D3DXVECTOR4* ()
    {
        return (D3DXVECTOR4*)&X;
    }

    inline Vector4::operator const D3DXVECTOR4* () const
    {
        return (const D3DXVECTOR4*)&X;
    }

    inline Vector4::operator Float32* ()
    {
        return (Float32*)&X;
    }

    inline Vector4::operator const Float32* () const
    {
        return (const Float32*)&X;
    }

    inline Float32& Vector4::operator [] (int i)
    {
        BM_Assert(i >= 0 && i < 4);
        return *(&X + i);
    }

    inline Float32 Vector4::operator [] (int i) const
    {
        BM_Assert(i >= 0 && i < 4);
        return *(&X + i);
    }

    inline bool Vector4::operator == (const Vector4& v) const
    {
        return (X == v.X && Y == v.Y && Z == v.Z && W == v.W);
    }

    inline bool Vector4::operator != (const Vector4& v) const
    {
        return (X != v.X || Y != v.Y || Z != v.Z || W != v.W);
    }

    inline bool Vector4::operator < (const Vector4& v) const
    {
        return (X < v.X && Y < v.Y && Z < v.Z && W < v.W);
    }

    inline bool Vector4::operator <= (const Vector4& v) const
    {
        return (X <= v.X && Y <= v.Y && Z <= v.Z && W <= v.W);
    }

    inline bool Vector4::operator > (const Vector4& v) const
    {
        return (X > v.X && Y > v.Y && Z > v.Z && W > v.W);
    }

    inline bool Vector4::operator >= (const Vector4& v) const
    {
        return (X >= v.X && Y >= v.Y && Z >= v.Z && W >= v.W);
    }

    inline Vector4& Vector4::operator = (const Vector4& v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        W = v.W;
        return *this;
    }

    inline Vector4& Vector4::operator = (Float32 s)
    {
        X = s;
        Y = s;
        Z = s;
        W = s;
        return *this;
    }

    inline Vector4& Vector4::operator += (const Vector4& v)
    {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        W += v.W;
        return *this;
    }

    inline Vector4& Vector4::operator -= (const Vector4& v)
    {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        W -= v.W;
        return *this;
    }

    inline Vector4& Vector4::operator *= (const Vector4& v)
    {
        X *= v.X;
        Y *= v.Y;
        Z *= v.Z;
        W *= v.W;
        return *this;
    }

    inline Vector4& Vector4::operator /= (const Vector4& v)
    {
        X /= v.X;
        Y /= v.Y;
        Z /= v.Z;
        W /= v.W;
        return *this;
    }

    inline Vector4& Vector4::operator += (Float32 f)
    {
        X += f;
        Y += f;
        Z += f;
        W += f;
        return *this;
    }

    inline Vector4& Vector4::operator -= (Float32 f)
    {
        X -= f;
        Y -= f;
        Z -= f;
        W -= f;
        return *this;
    }

    inline Vector4& Vector4::operator *= (Float32 f)
    {
        X *= f;
        Y *= f;
        Z *= f;
        W *= f;
        return *this;
    }

    inline Vector4& Vector4::operator /= (Float32 f)
    {
        X /= f;
        Y /= f;
        Z /= f;
        W /= f;
        return *this;
    }

    inline Vector4 Vector4::operator + () const
    {
        return *this;
    }

    inline Vector4 Vector4::operator - () const
    {
        return Vector4(-X, -Y, -Z, -W);
    }

    inline Vector4 Vector4::operator + (const Vector4& v) const
    {
        return Vector4(X + v.X, Y + v.Y, Z + v.Z, W + v.W);
    }

    inline Vector4 Vector4::operator - (const Vector4& v) const
    {
        return Vector4(X - v.X, Y - v.Y, Z - v.Z, W - v.W);
    }

    inline Vector4 Vector4::operator * (const Vector4& v) const
    {
        return Vector4(X * v.X, Y * v.Y, Z * v.Z, W * v.W);
    }

    inline Vector4 Vector4::operator / (const Vector4& v) const
    {
        return Vector4(X / v.X, Y / v.Y, Z / v.Z, W / v.W);
    }

    inline Vector4 Vector4::operator + (Float32 f) const
    {
        return Vector4(X + f, Y + f, Z + f, W + f);
    }

    inline Vector4 Vector4::operator - (Float32 f) const
    {
        return Vector4(X - f, Y - f, Z - f, W - f);
    }

    inline Vector4 Vector4::operator * (Float32 f) const
    {
        return Vector4(X * f, Y * f, Z * f, W * f);
    }

    inline Vector4 Vector4::operator / (Float32 f) const
    {
        return Vector4(X / f, Y / f, Z / f, W / f);
    }

    inline /*friend*/ Vector4 operator + (Float32 f, const Vector4& v)
    {
        return Vector4(f + v.X, f + v.Y, f + v.Z, f + v.W);
    }

    inline /*friend*/ Vector4 operator - (Float32 f, const Vector4& v)
    {
        return Vector4(f - v.X, f - v.Y, f - v.Z, f - v.W);
    }

    inline /*friend*/ Vector4 operator * (Float32 f, const Vector4& v)
    {
        return Vector4(f * v.X, f * v.Y, f * v.Z, f * v.W);
    }

    inline /*friend*/ Vector4 operator / (Float32 f, const Vector4& v)
    {
        return Vector4(f / v.X, f / v.Y, f / v.Z, f / v.W);
    }

    inline Float32 Vector4::operator | (const Vector4& v) const
    {
        return Dot(v);
    }

    inline Vector4 Vector4::operator ^ (const Vector4& v) const
    {
        return Cross(v);
    }

#pragma endregion

#pragma region Utilities

    inline void Vector4::Get(Float32& x, Float32& y, Float32& z, Float32& w) const
    {
        x = X;
        y = Y;
        z = Z;
        w = W;
    }

    inline void Vector4::Set(Float32 x, Float32 y, Float32 z, Float32 w)
    {
        X = x;
        Y = y;
        Z = z;
        W = w;
    }

    inline void Vector4::Set(const Vector3& v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
    }

    inline void Vector4::Set(const Vector3& v, Float32 w)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        W = w;
    }

    inline Float32 Vector4::Dot(const Vector4& v) const
    {
        return X * v.X +  Y * v.Y + Z * v.Z + W * v.W;
    }

    inline Vector4 Vector4::Cross(const Vector4& v) const
    {
        return Vector4(Y * v.Z - Z * v.Y, Z * v.X - X * v.Z, X * v.Y - Y * v.X, 0.0f);
    }

    inline Float32 Vector4::Dot2D(const Vector4& v) const
    {
        return X * v.X +  Y * v.Y;
    }

    inline Float32 Vector4::Dot3D(const Vector4& v) const
    {
        return X * v.X +  Y * v.Y + Z * v.Z;
    }

    inline Float32 Vector4::GetLength() const
    {
        return Sqrt(GetSquareLength());
    }

    inline Float32 Vector4::GetSquareLength() const
    {
        return X * X + Y * Y + Z * Z + W * W;
    }

    inline Float32 Vector4::GetLength2D() const
    {
        return Sqrt(GetSquareLength2D());
    }

    inline Float32 Vector4::GetSquareLength2D() const
    {
        return X * X + Y * Y;
    }

    inline Float32 Vector4::GetLength3D() const
    {
        return Sqrt(GetSquareLength3D());
    }

    inline Float32 Vector4::GetSquareLength3D() const
    {
        return X * X + Y * Y + Z * Z;
    }

    inline Vector4& Vector4::Normalize()
    {
        Float32 l = GetLength();
        if (!BM::IsNearlyZero(l))
        {
            X /= l;
            Y /= l;
            Z /= l;
            W /= l;
        }
        return *this;
    }

    inline Vector4 Vector4::GetNormalized() const
    {
        return Vector4(*this).Normalize();
    }

    inline Vector4& Vector4::Normalize2D()
    {
        Float32 l = GetLength2D();
        if (!BM::IsNearlyZero(l))
        {
            X /= l;
            Y /= l;
        }
        Z = 0.0f;
        W = 0.0f;
        return *this;
    }

    inline Vector4 Vector4::GetNormalized2D() const
    {
        return Vector4(*this).Normalize2D();
    }

    inline Vector4& Vector4::Normalize3D()
    {
        Float32 l = GetLength3D();
        if (!BM::IsNearlyZero(l))
        {
            X /= l;
            Y /= l;
            Z /= l;
        }
        W = 0.0f;
        return *this;
    }

    inline Vector4 Vector4::GetNormalized3D() const
    {
        return Vector4(*this).Normalize3D();
    }

    inline Vector4& Vector4::Clamp(const Vector4& min, const Vector4& max)
    {
        X = BM::Clamp(X, min.X, max.X);
        Y = BM::Clamp(Y, min.Y, max.Y);
        Z = BM::Clamp(Z, min.Z, max.Z);
        W = BM::Clamp(W, min.W, max.W);
        return *this;
    }

    inline Vector4 Vector4::GetClamped(const Vector4& min, const Vector4& max) const
    {
        return Vector4(*this).Clamp(min, max);
    }

    inline Vector4& Vector4::Saturate()
    {
        X = BM::Clamp(X, 0.0f, 1.0f);
        Y = BM::Clamp(Y, 0.0f, 1.0f);
        Z = BM::Clamp(Z, 0.0f, 1.0f);
        W = BM::Clamp(W, 0.0f, 1.0f);
        return *this;
    }

    inline Vector4 Vector4::GetSaturated() const
    {
        return Vector4(*this).Saturate();
    }

    inline Vector4& Vector4::Min(const Vector4& v)
    {
        X = BM::Min(X, v.X);
        Y = BM::Min(Y, v.Y);
        Z = BM::Min(Z, v.Z);
        W = BM::Min(W, v.W);
        return *this;
    }

    inline Vector4 Vector4::GetMin(const Vector4& v) const
    {
        return Vector4(*this).Min(v);
    }

    inline Vector4& Vector4::Max(const Vector4& v)
    {
        X = BM::Max(X, v.X);
        Y = BM::Max(Y, v.Y);
        Z = BM::Max(Z, v.Z);
        W = BM::Max(W, v.W);
        return *this;
    }

    inline Vector4 Vector4::GetMax(const Vector4& v) const
    {
        return Vector4(*this).Max(v);
    }

    inline bool Vector4::IsNearlyEqual(const Vector4& v, Float32 epsilon) const
    {
        return (BM::IsNearlyEqual(X, v.X, epsilon) && BM::IsNearlyEqual(Y, v.Y, epsilon) && BM::IsNearlyEqual(Z, v.Z, epsilon));
    }

    inline bool Vector4::IsZero() const
    {
        return (*this == Zero);
    }

    inline bool Vector4::IsNearlyZero() const
    {
        return IsNearlyEqual(Zero);
    }

    inline bool Vector4::IsLengthZero() const
    {
        return (GetSquareLength() == 0.0f);
    }

    inline bool Vector4::IsLengthNearlyZero() const
    {
        return (GetSquareLength() < Sqr(Math32::Epsilon));
    }

#pragma endregion
}
