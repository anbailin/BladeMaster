#pragma once

namespace BM
{
#pragma region Constructors

    inline Color::Color()
    {
        R = 0.0f;
        G = 0.0f;
        B = 0.0f;
        A = 0.0f;
    }

    inline Color::Color(Float32 r, Float32 g, Float32 b, Float32 a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }

    inline Color::Color(const Vector3& c, Float32 a)
    {
        R = c.X;
        G = c.Y;
        B = c.Z;
        A = a;
    }

    inline Color::Color(const Vector4& c)
    {
        R = c.X;
        G = c.Y;
        B = c.Z;
        A = c.W;
    }

    inline Color::Color(const Color& c)
    {
        R = c.R;
        G = c.G;
        B = c.B;
        A = c.A;
    }

    inline Color::Color(const D3DXCOLOR& c)
    {
        R = c.r;
        G = c.g;
        B = c.b;
        A = c.a;
    }

#pragma endregion

#pragma region Operators

    inline Color::operator D3DXCOLOR& ()
    {
        return *((D3DXCOLOR*)&R);
    }

    inline Color::operator const D3DXCOLOR& () const
    {
        return *((const D3DXCOLOR*)&R);
    }

    inline Color::operator D3DXCOLOR* ()
    {
        return (D3DXCOLOR*)&R;
    }

    inline Color::operator const D3DXCOLOR* () const
    {
        return (const D3DXCOLOR*)&R;
    }

    inline Color::operator Float32* ()
    {
        return (Float32*)&R;
    }

    inline Color::operator const Float32* () const
    {
        return (const Float32*)&R;
    }

    inline Float32 Color::operator [] (int i) const
    {
        BM_Assert(i >= 0 && i < 4);
        return *(&R + i);
    }

    inline Float32& Color::operator [] (int i)
    {
        BM_Assert(i >= 0 && i < 4);
        return *(&R + i);
    }

    inline bool Color::operator == (const Color& c) const
    {
        return (R == c.R && G == c.G && B == c.B && A == c.A);
    }

    inline bool Color::operator != (const Color& c) const
    {
        return (R != c.R || G != c.G || B != c.B || A != c.A);
    }

    inline Color& Color::operator = (const Color& c)
    {
        R = c.R;
        G = c.G;
        B = c.B;
        A = c.A;
        return *this;
    }

    inline Color& Color::operator += (const Color& c)
    {
        R += c.R;
        G += c.G;
        B += c.B;
        A += c.A;
        return *this;
    }

    inline Color& Color::operator -= (const Color& c)
    {
        R -= c.R;
        G -= c.G;
        B -= c.B;
        A -= c.A;
        return *this;
    }

    inline Color& Color::operator *= (const Color& c)
    {
        R *= c.R;
        G *= c.G;
        B *= c.B;
        A *= c.A;
        return *this;
    }

    inline Color& Color::operator /= (const Color& c)
    {
        R /= c.R;
        G /= c.G;
        B /= c.B;
        A /= c.A;
        return *this;
    }

    inline Color& Color::operator *= (Float32 f)
    {
        R *= f;
        G *= f;
        B *= f;
        A *= f;
        return *this;
    }

    inline Color& Color::operator /= (Float32 f)
    {
        R /= f;
        G /= f;
        B /= f;
        A /= f;
        return *this;
    }

    inline Color Color::operator + () const
    {
        return *this;
    }

    inline Color Color::operator - () const
    {
        return Color(-R, -G, -B, -A);
    }

    inline Color Color::operator + (const Color& c) const
    {
        return Color(R + c.R, G + c.G, B + c.B, A + c.A);
    }

    inline Color Color::operator - (const Color& c) const
    {
        return Color(R - c.R, G - c.G, B - c.B, A - c.A);
    }

    inline Color Color::operator * (const Color& c) const
    {
        return Color(R * c.R, G * c.G, B * c.B, A * c.A);
    }

    inline Color Color::operator / (const Color& c) const
    {
        return Color(R / c.R, G / c.G, B / c.B, A / c.A);
    }

    inline Color Color::operator * (Float32 f) const
    {
        return Color(R * f, G * f, B * f, A * f);
    }

    inline Color Color::operator / (Float32 f) const
    {
        return Color(R / f, G / f, B / f, A / f);
    }

    inline /*friend*/ Color operator * (Float32 f, const Color& c)
    {
        return Color(f * c.R, f * c.G, f * c.B, f * c.A);
    }

#pragma endregion

#pragma region Utilitis

    inline void Color::Get(Float32& r, Float32& g, Float32& b, Float32& a) const
    {
        r = R;
        g = G;
        b = B;
        a = A;
    }

    inline void Color::Set(Float32 r, Float32 g, Float32 b, Float32 a)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }

    inline Color& Color::Saturate()
    {
        R = BM::Clamp(R, 0.0f, 1.0f);
        G = BM::Clamp(G, 0.0f, 1.0f);
        B = BM::Clamp(B, 0.0f, 1.0f);
        A = BM::Clamp(A, 0.0f, 1.0f);
        return *this;
    }

    inline Color Color::GetSaturated() const
    {
        return Color(*this).Saturate();
    }

    inline UInt32 Color::ToARGB() const
    {
        UInt32 r = (R >= 1.0f ? 0xff : R <= 0.0f ? 0x00 : (UInt32) (R * 255.0f + 0.5f));
        UInt32 g = (G >= 1.0f ? 0xff : G <= 0.0f ? 0x00 : (UInt32) (G * 255.0f + 0.5f));
        UInt32 b = (B >= 1.0f ? 0xff : B <= 0.0f ? 0x00 : (UInt32) (B * 255.0f + 0.5f));
        UInt32 a = (A >= 1.0f ? 0xff : A <= 0.0f ? 0x00 : (UInt32) (A * 255.0f + 0.5f));
        return ((a << 24) | (r << 16) | (g << 8) | b);
    }

    inline UInt32 Color::ToRGBA() const
    {
        UInt32 r = (R >= 1.0f ? 0xff : R <= 0.0f ? 0x00 : (UInt32) (R * 255.0f + 0.5f));
        UInt32 g = (G >= 1.0f ? 0xff : G <= 0.0f ? 0x00 : (UInt32) (G * 255.0f + 0.5f));
        UInt32 b = (B >= 1.0f ? 0xff : B <= 0.0f ? 0x00 : (UInt32) (B * 255.0f + 0.5f));
        UInt32 a = (A >= 1.0f ? 0xff : A <= 0.0f ? 0x00 : (UInt32) (A * 255.0f + 0.5f));
        return ((r << 24) | (g << 16) | (b << 8) | a);
    }

    inline Color Color::FromARGB(UInt32 argb)
    {
        Float32 a = (UInt8)(argb >> 24) * (1.0f / 255.0f);
        Float32 r = (UInt8)(argb >> 16) * (1.0f / 255.0f);
        Float32 g = (UInt8)(argb >>  8) * (1.0f / 255.0f);
        Float32 b = (UInt8)(argb >>  0) * (1.0f / 255.0f);
        return Color(r, g, b, a);
    }

    inline Color Color::FromRGBA(UInt32 rgba)
    {
        Float32 r = (UInt8)(rgba >> 24) * (1.0f / 255.0f);
        Float32 g = (UInt8)(rgba >> 16) * (1.0f / 255.0f);
        Float32 b = (UInt8)(rgba >>  8) * (1.0f / 255.0f);
        Float32 a = (UInt8)(rgba >>  0) * (1.0f / 255.0f);
        return Color(r, g, b, a);
    }

#pragma endregion
}
