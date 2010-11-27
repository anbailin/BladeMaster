
#pragma region Constructors

inline Matrix44::Matrix44()
{
    V[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
    V[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
    V[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
    V[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix44::Matrix44(f32 m11, f32 m12, f32 m13, f32 m14, f32 m21, f32 m22, f32 m23, f32 m24, f32 m31, f32 m32, f32 m33, f32 m34, f32 m41, f32 m42, f32 m43, f32 m44)
{
    V[0].Set(m11, m12, m13, m14);
    V[1].Set(m21, m22, m23, m24);
    V[2].Set(m31, m32, m33, m34);
    V[3].Set(m41, m42, m43, m44);
}

inline Matrix44::Matrix44(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4)
{
    V[0] = row1;
    V[1] = row2;
    V[2] = row3;
    V[3] = row4;
}

inline Matrix44::Matrix44(const Matrix44& m)
{
    V[0] = m.V[0];
    V[1] = m.V[1];
    V[2] = m.V[2];
    V[3] = m.V[3];
}

inline Matrix44::Matrix44(const D3DXMATRIX& m)
{
    V[0].Set(m._11, m._12, m._13, m._14);
    V[1].Set(m._21, m._22, m._23, m._24);
    V[2].Set(m._31, m._32, m._33, m._34);
    V[3].Set(m._41, m._42, m._43, m._44);
}

#pragma endregion

#pragma region Operators

inline Matrix44::operator D3DXMATRIX& ()
{
    return *(D3DXMATRIX*)V;
}

inline Matrix44::operator const D3DXMATRIX& () const
{
    return *(const D3DXMATRIX*)V;
}

inline Matrix44::operator D3DXMATRIX* ()
{
    return (D3DXMATRIX*)V;
}

inline Matrix44::operator const D3DXMATRIX* () const
{
    return (const D3DXMATRIX*)V;
}

inline Matrix44::operator f32* ()
{
    return (f32*)V;
}

inline Matrix44::operator const f32* () const
{
    return (const f32*)V;
}

inline f32& Matrix44::operator () (int row, int col)
{
    return Get(row, col);
}

inline f32 Matrix44::operator () (int row, int col) const
{
    return Get(row, col);
}

inline Vector4& Matrix44::operator [] (int row)
{
    return GetRow(row);
}

inline const Vector4& Matrix44::operator [] (int row) const
{
    return GetRow(row);
}

inline Vector4 Matrix44::operator () (int col) const
{
    return GetColumn(col);
}

inline bool Matrix44::operator == (const Matrix44& m) const
{
    return (V[0] == m.V[0] && V[1] == m.V[1] && V[2] == m.V[2] && V[3] == m.V[3]);
}

inline bool Matrix44::operator != (const Matrix44& m) const
{
    return (V[0] != m.V[0] || V[1] != m.V[1] || V[2] != m.V[2] || V[3] != m.V[3]);
}

inline Matrix44& Matrix44::operator = (const Matrix44& m)
{
    V[0] = m.V[0];
    V[1] = m.V[1];
    V[2] = m.V[2];
    V[3] = m.V[3];
    return *this;
}

inline Matrix44& Matrix44::operator += (const Matrix44& m)
{
    V[0] += m.V[0];
    V[1] += m.V[1];
    V[2] += m.V[2];
    V[3] += m.V[3];
    return *this;
}

inline Matrix44& Matrix44::operator -= (const Matrix44& m)
{
    V[0] -= m.V[0];
    V[1] -= m.V[1];
    V[2] -= m.V[2];
    V[3] -= m.V[3];
    return *this;
}

inline Matrix44& Matrix44::operator *= (const Matrix44& m)
{
    Multiply(m);
    return *this;
}

inline Matrix44& Matrix44::operator *= (f32 f)
{
    V[0] *= f;
    V[1] *= f;
    V[2] *= f;
    V[3] *= f;
    return *this;
}

inline Matrix44& Matrix44::operator /= (f32 f)
{
    V[0] /= f;
    V[1] /= f;
    V[2] /= f;
    V[3] /= f;
    return *this;
}

inline Matrix44 Matrix44::operator + () const
{
    return *this;
}

inline Matrix44 Matrix44::operator - () const
{
    return Matrix44(-V[0], -V[1], -V[2], -V[3]);
}

inline Matrix44 Matrix44::operator + (const Matrix44& m) const
{
    return Matrix44(V[0] + m.V[1], V[1] + m.V[1], V[2] + m.V[2], V[3] + m.V[3]);
}

inline Matrix44 Matrix44::operator - (const Matrix44& m) const
{
    return Matrix44(V[0] - m.V[1], V[1] - m.V[1], V[2] - m.V[2], V[3] - m.V[3]);
}

inline Matrix44 Matrix44::operator * (const Matrix44& m) const
{
    return Matrix44(*this).Multiply(m);
}

inline Matrix44 Matrix44::operator * (f32 f) const
{
    return Matrix44(V[0] * f, V[1] * f, V[2] * f, V[3] * f);
}

inline Matrix44 Matrix44::operator / (f32 f) const
{
    return Matrix44(V[0] / f, V[1] / f, V[2] / f, V[3] / f);
}

#pragma endregion

#pragma region Utilitis

inline f32& Matrix44::Get(int row, int col)
{
    BM_Assert(row >= 0 && row < 4 && col >= 0 && col < 4);
    return V[row][col];
}

inline f32 Matrix44::Get(int row, int col) const
{
    BM_Assert(row >= 0 && row < 4 && col >= 0 && col < 4);
    return V[row][col];
}

inline Vector4& Matrix44::GetRow(int row)
{
    BM_Assert(row >= 0 && row < 4);
    return V[row];
}

inline const Vector4& Matrix44::GetRow(int row) const
{
    BM_Assert(row >= 0 && row < 4);
    return V[row];
}

inline Vector4 Matrix44::GetColumn(int col) const
{
    BM_Assert(col >= 0 && col < 4);
    return Vector4(V[0][col], V[1][col], V[2][col], V[3][col]);
}

inline void Matrix44::Set(f32 m11, f32 m12, f32 m13, f32 m14, f32 m21, f32 m22, f32 m23, f32 m24, f32 m31, f32 m32, f32 m33, f32 m34, f32 m41, f32 m42, f32 m43, f32 m44)
{
    V[0].Set(m11, m12, m13, m14);
    V[1].Set(m21, m22, m23, m24);
    V[2].Set(m31, m32, m33, m34);
    V[3].Set(m41, m42, m43, m44);
}

inline void Matrix44::SetRows(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4)
{
    V[0] = row1;
    V[1] = row2;
    V[2] = row3;
    V[3] = row4;
}

inline void Matrix44::SetColumns(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4)
{
    V[0].Set(col1.X, col2.X, col3.X, col4.X);
    V[1].Set(col1.Y, col2.Y, col3.Y, col4.Y);
    V[2].Set(col1.Z, col2.Z, col3.Z, col4.Z);
    V[3].Set(col1.W, col2.W, col3.W, col4.W);
}

inline Matrix44& Matrix44::Multiply(const Matrix44& m)
{
    D3DXMatrixMultiply(*this, *this, m);
    return *this;
}

#pragma endregion
