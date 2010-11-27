#pragma once
#include "Utilities.h"

#pragma region Constructors

inline Color::Color()
{
    R = 0.0f;
    G = 0.0f;
    B = 0.0f;
    A = 0.0f;
}

inline Color::Color(f32 r, f32 g, f32 b, f32 a)
{
    R = r;
    G = g;
    B = b;
    A = a;
}

inline Color::Color(const Vector3& c, f32 a)
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

inline Color::operator f32* ()
{
    return (f32*)&R;
}

inline Color::operator const f32* () const
{
    return (const f32*)&R;
}

inline f32 Color::operator [] (int i) const
{
    BM_Assert(i >= 0 && i < 4);
    return *(&R + i);
}

inline f32& Color::operator [] (int i)
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

inline Color& Color::operator *= (f32 f)
{
    R *= f;
    G *= f;
    B *= f;
    A *= f;
    return *this;
}

inline Color& Color::operator /= (f32 f)
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

inline Color Color::operator * (f32 f) const
{
    return Color(R * f, G * f, B * f, A * f);
}

inline Color Color::operator / (f32 f) const
{
    return Color(R / f, G / f, B / f, A / f);
}

inline /*friend*/ Color operator * (f32 f, const Color& c)
{
    return Color(f * c.R, f * c.G, f * c.B, f * c.A);
}

#pragma endregion

#pragma region Utilitis

inline void Color::Get(f32& r, f32& g, f32& b, f32& a) const
{
    r = R;
    g = G;
    b = B;
    a = A;
}

inline void Color::Set(f32 r, f32 g, f32 b, f32 a)
{
    R = r;
    G = g;
    B = b;
    A = a;
}

inline Color& Color::Saturate()
{
    R = Clamp(R, 0.0f, 1.0f);
    G = Clamp(G, 0.0f, 1.0f);
    B = Clamp(B, 0.0f, 1.0f);
    A = Clamp(A, 0.0f, 1.0f);
    return *this;
}

inline Color Color::GetSaturated() const
{
    return Color(*this).Saturate();
}

inline u32 Color::ToARGB() const
{
    u32 r = (R >= 1.0f ? 0xff : R <= 0.0f ? 0x00 : (u32) (R * 255.0f + 0.5f));
    u32 g = (G >= 1.0f ? 0xff : G <= 0.0f ? 0x00 : (u32) (G * 255.0f + 0.5f));
    u32 b = (B >= 1.0f ? 0xff : B <= 0.0f ? 0x00 : (u32) (B * 255.0f + 0.5f));
    u32 a = (A >= 1.0f ? 0xff : A <= 0.0f ? 0x00 : (u32) (A * 255.0f + 0.5f));
    return ((a << 24) | (r << 16) | (g << 8) | b);
}

inline u32 Color::ToRGBA() const
{
    u32 r = (R >= 1.0f ? 0xff : R <= 0.0f ? 0x00 : (u32) (R * 255.0f + 0.5f));
    u32 g = (G >= 1.0f ? 0xff : G <= 0.0f ? 0x00 : (u32) (G * 255.0f + 0.5f));
    u32 b = (B >= 1.0f ? 0xff : B <= 0.0f ? 0x00 : (u32) (B * 255.0f + 0.5f));
    u32 a = (A >= 1.0f ? 0xff : A <= 0.0f ? 0x00 : (u32) (A * 255.0f + 0.5f));
    return ((r << 24) | (g << 16) | (b << 8) | a);
}

inline Color Color::FromARGB(u32 argb)
{
    f32 a = (u8)(argb >> 24) * (1.0f / 255.0f);
    f32 r = (u8)(argb >> 16) * (1.0f / 255.0f);
    f32 g = (u8)(argb >>  8) * (1.0f / 255.0f);
    f32 b = (u8)(argb >>  0) * (1.0f / 255.0f);
    return Color(r, g, b, a);
}

inline Color Color::FromRGBA(u32 rgba)
{
    f32 r = (u8)(rgba >> 24) * (1.0f / 255.0f);
    f32 g = (u8)(rgba >> 16) * (1.0f / 255.0f);
    f32 b = (u8)(rgba >>  8) * (1.0f / 255.0f);
    f32 a = (u8)(rgba >>  0) * (1.0f / 255.0f);
    return Color(r, g, b, a);
}

#pragma endregion

