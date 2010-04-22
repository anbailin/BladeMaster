#pragma once

#include "CorePublic.h"

namespace BM
{
    class CORE_API Color
    {
    public:
        Float32 R;
        Float32 G;
        Float32 B;
        Float32 A;

    public:
#pragma region Constructors

        inline Color();
        inline Color(Float32 r, Float32 g, Float32 b, Float32 a = 1.0f);
        inline Color(const Vector3& c, Float32 a = 1.0f);
        inline Color(const Vector4& c);
        inline Color(const Color& c);
        inline Color(const D3DXCOLOR& c);

#pragma endregion

#pragma region Operators

        inline operator D3DXCOLOR& ();
        inline operator const D3DXCOLOR& () const;

        inline operator D3DXCOLOR* ();
        inline operator const D3DXCOLOR* () const;

        inline operator Float32* ();
        inline operator const Float32* () const;

		inline Float32 operator [] (int i) const;
		inline Float32& operator [] (int i);

        inline Float32 operator () (int i) const;
        inline Float32& operator () (int i);

        inline bool operator == (const Color& c) const;
        inline bool operator != (const Color& c) const;

        inline Color& operator = (const Color& c);

        inline Color& operator += (const Color& c);
        inline Color& operator -= (const Color& c);
        inline Color& operator *= (const Color& c);
        inline Color& operator /= (const Color& c);

        inline Color& operator *= (Float32 f);
        inline Color& operator /= (Float32 f);

        inline Color operator + () const;
        inline Color operator - () const;

        inline Color operator + (const Color& c) const;
        inline Color operator - (const Color& c) const;
        inline Color operator * (const Color& c) const;
        inline Color operator / (const Color& c) const;

        inline Color operator * (Float32 f) const;
        inline Color operator / (Float32 f) const;

        inline friend Color operator * (Float32 f, const Color& c);

#pragma endregion

#pragma region Utilitis

        inline void Get(Float32& r, Float32& g, Float32& b, Float32& a) const;
        inline void Set(Float32 r, Float32 g, Float32 b, Float32 a);

        inline Color& Saturate();
        inline Color GetSaturated() const;

        inline UInt32 ToARGB() const;
        inline UInt32 ToRGBA() const;

        inline static Color FromARGB(UInt32 argb);
        inline static Color FromRGBA(UInt32 rgba);

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
