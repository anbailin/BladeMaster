#pragma once

namespace BM
{
    class CORE_DLL Matrix44
    {
    public:
        Vector4 V[4];

    public:
#pragma region Constructors

        inline Matrix44();
        inline Matrix44(f32 m11, f32 m12, f32 m13, f32 m14, f32 m21, f32 m22, f32 m23, f32 m24, f32 m31, f32 m32, f32 m33, f32 m34, f32 m41, f32 m42, f32 m43, f32 m44);
        inline Matrix44(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4);
        inline Matrix44(const Matrix44& m);
        inline Matrix44(const D3DXMATRIX& m);

#pragma endregion

#pragma region Operators

        inline operator D3DXMATRIX& ();
        inline operator const D3DXMATRIX& () const;

        inline operator D3DXMATRIX* ();
        inline operator const D3DXMATRIX* () const;

        inline operator f32* ();
        inline operator const f32* () const;

        inline f32& operator () (int row, int col);
        inline f32 operator () (int row, int col) const;

		inline Vector4& operator [] (int row);
		inline const Vector4& operator [] (int row) const;

        inline Vector4 operator () (int col) const;

        inline bool operator == (const Matrix44& m) const;
        inline bool operator != (const Matrix44& m) const;

        inline Matrix44& operator = (const Matrix44& m);

        inline Matrix44& operator += (const Matrix44& m);
        inline Matrix44& operator -= (const Matrix44& m);
        inline Matrix44& operator *= (const Matrix44& m);

        inline Matrix44& operator *= (f32 f);
        inline Matrix44& operator /= (f32 f);

        inline Matrix44 operator + () const;
        inline Matrix44 operator - () const;

        inline Matrix44 operator + (const Matrix44& m) const;
        inline Matrix44 operator - (const Matrix44& m) const;
        inline Matrix44 operator * (const Matrix44& m) const;

        inline Matrix44 operator * (f32 f) const;
        inline Matrix44 operator / (f32 f) const;

#pragma endregion

#pragma region Utilitis

        inline f32& Get(int row, int col);
        inline f32 Get(int row, int col) const;

        inline Vector4& GetRow(int row);
        inline const Vector4& GetRow(int row) const;

        inline Vector4 GetColumn(int col) const;

        inline void Set(f32 m11, f32 m12, f32 m13, f32 m14, f32 m21, f32 m22, f32 m23, f32 m24, f32 m31, f32 m32, f32 m33, f32 m34, f32 m41, f32 m42, f32 m43, f32 m44);

        inline void SetRows(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4);
        inline void SetColumns(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4);

        inline Matrix44& Multiply(const Matrix44& m);

#pragma endregion

    public:
        static const Matrix44 Zero;
        static const Matrix44 Identity;
    };

    typedef Matrix44 Matrix;
}

#include "Matrix44.inl"
