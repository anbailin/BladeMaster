#pragma once
#include "Vector3.h"
#include "Vector4.h"

namespace BM
{
    class CORE_DLL Color
    {
    public:
        f32 R;
        f32 G;
        f32 B;
        f32 A;

    public:
#pragma region Constructors

        inline Color();
        inline Color(f32 r, f32 g, f32 b, f32 a = 1.0f);
        inline Color(const Vector3& c, f32 a = 1.0f);
        inline Color(const Vector4& c);
        inline Color(const Color& c);
        inline Color(const D3DXCOLOR& c);

#pragma endregion

#pragma region Operators

        inline operator D3DXCOLOR& ();
        inline operator const D3DXCOLOR& () const;

        inline operator D3DXCOLOR* ();
        inline operator const D3DXCOLOR* () const;

        inline operator f32* ();
        inline operator const f32* () const;

		inline f32 operator [] (int i) const;
		inline f32& operator [] (int i);

        inline f32 operator () (int i) const;
        inline f32& operator () (int i);

        inline bool operator == (const Color& c) const;
        inline bool operator != (const Color& c) const;

        inline Color& operator = (const Color& c);

        inline Color& operator += (const Color& c);
        inline Color& operator -= (const Color& c);
        inline Color& operator *= (const Color& c);
        inline Color& operator /= (const Color& c);

        inline Color& operator *= (f32 f);
        inline Color& operator /= (f32 f);

        inline Color operator + () const;
        inline Color operator - () const;

        inline Color operator + (const Color& c) const;
        inline Color operator - (const Color& c) const;
        inline Color operator * (const Color& c) const;
        inline Color operator / (const Color& c) const;

        inline Color operator * (f32 f) const;
        inline Color operator / (f32 f) const;

        inline friend Color operator * (f32 f, const Color& c);

#pragma endregion

#pragma region Utilitis

        inline void Get(f32& r, f32& g, f32& b, f32& a) const;
        inline void Set(f32 r, f32 g, f32 b, f32 a);

        inline Color& Saturate();
        inline Color GetSaturated() const;

        inline u32 ToARGB() const;
        inline u32 ToRGBA() const;

        inline static Color FromARGB(u32 argb);
        inline static Color FromRGBA(u32 rgba);

#pragma endregion

    public:
        static const Color Zero;
        static const Color One;
        static const Color Black;
        static const Color White;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
    };
}

#include "Color.inl"
