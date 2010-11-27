#pragma once

//////////////////////////////////////////////////////////////////////////
// Constants
namespace Math64
{
    const f64 Epsilon       = 0.000001;
    const f64 Pi            = 3.1415926535897932384626433832795;
    const f64 HalfPi        = Pi * 0.5;
    const f64 TwoPi         = Pi * 2.0;
    const f64 Degree2Radian = Pi / 180.0;
    const f64 Radian2Degree = 180.0 / Pi;
}
namespace Math32
{
    const f32 Epsilon       = (f32)Math64::Epsilon;
    const f32 Pi            = (f32)Math64::Pi;
    const f32 HalfPi        = (f32)Math64::HalfPi;
    const f32 TwoPi         = (f32)Math64::TwoPi;
    const f32 Degree2Radian = (f32)Math64::Degree2Radian;
    const f32 Radian2Degree = (f32)Math64::Radian2Degree;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Functions
template<typename T> inline T    Min(const T& a, const T& b)                           { return (a < b ? a : b); }
template<typename T> inline T    Max(const T& a, const T& b)                           { return (a > b ? a : b); }
template<typename T> inline T    Min(const T& a, const T& b, const T& c)               { return (a < b ? (a < c ? a : c) : (b < c ? b : c)); }
template<typename T> inline T    Max(const T& a, const T& b, const T& c)               { return (a > b ? (a > c ? a : c) : (b > c ? b : c)); }
template<typename T> inline T    Sign(const T& a)                                      { return (a >= T(0) ? T(1) : T(-1)); }
template<typename T> inline T    Sqr(const T& a)                                       { return a * a; }
template<typename T> inline T    Clamp(const T& a, const T& min, const T& max)         { return (a < min ? min : (a > max ? max : a)); }
template<typename T> inline void Swap(T& a, T& b)                                      { T t = a; a = b; b = t; }
template<typename T> inline bool IsPowerOf2(const T& a)                                { return !((a - 1) & a); }
template<typename T> inline bool IsInRange(const T& value, const T& min, const T& max) { return (min <= value) && (value <= max); }
template<typename T> inline bool IsInRange(const T& value, const T& range)             { return IsInRange(value, -range, range); }

template<typename T, typename U> inline T Lerp(const T& a, const T& b, const U& t)     { return (a + (b - a) * t); }

inline s32   Abs(s32 a)                 { return abs(a); }
inline s64   Abs(s64 a)                 { return _abs64(a); }
inline f32 Abs(f32 a)               { return fabsf(a); }
inline f64 Abs(f64 a)               { return fabs(a); }

inline f32 Pow(f32 a, f32 e)    { return powf(a, e); }
inline f64 Pow(f64 a, f64 e)    { return pow(a, e); }

inline f32 Exp(f32 a)               { return expf(a); }
inline f64 Exp(f64 a)               { return exp(a); }

inline f32 Ln(f32 a)                { return logf(a); }
inline f64 Ln(f64 a)                { return log(a); }

inline u32  Log2(u32 a)               { u32 l = 0; while(a > 0) { a >>= 1; l++; } return l; }
inline u32  Log2(u64 a)               { u32 l = 0; while(a > 0) { a >>= 1; l++; } return l; }
inline f32 Log2(f32 a)              { return logf(a) / logf(2.0f); }
inline f64 Log2(f64 a)              { return log(a) / log(2.0); }

inline f32 Log10(f32 a)             { return log10f(a); }
inline f64 Log10(f64 a)             { return log10(a); }

inline f32 LogN(f32 a, f32 b)   { return logf(a) / logf(b); }
inline f64 LogN(f64 a, f64 b)   { return log(a) / log(b); }

inline f32 Modulo(f32 a, f32 b) { return fmodf(a, b); }
inline f64 Modulo(f64 a, f64 b) { return fmod(a, b); }

inline f32 Sqrt(f32 a)              { return sqrtf(a); }
inline f64 Sqrt(f64 a)              { return sqrt(a); }

inline f32 Ceil(f32 a)              { return ceilf(a); }
inline f64 Ceil(f64 a)              { return ceil(a); }

inline f32 Floor(f32 a)             { return floorf(a); }
inline f64 Floor(f64 a)             { return floor(a); }

inline f32 Round(f32 a)             { return (f32)((int)(a + (a > 0.0f ? 0.5f : -0.5f))); }
inline f64 Round(f64 a)             { return (f64)((int)(a + (a > 0.0 ? 0.5 : -0.5))); }

inline f32 Sin(f32 x)               { return sinf(x); }
inline f64 Sin(f64 x)               { return sin(x); }

inline f32 Cos(f32 x)               { return cosf(x); }
inline f64 Cos(f64 x)               { return cos(x); }

inline f32 Tan(f32 x)               { return tanf(x); }
inline f64 Tan(f64 x)               { return tan(x); }

inline f32 ASin(f32 x)              { return asinf(x); }
inline f64 ASin(f64 x)              { return asin(x); }

inline f32 ACos(f32 x)              { return acosf(x); }
inline f64 ACos(f64 x)              { return acos(x); }

inline f32 ATan(f32 x)              { return atanf(x); }
inline f64 ATan(f64 x)              { return atan(x); }

inline f32 ATan(f32 y, f32 x)   { return atan2f(y, x); }
inline f64 ATan(f64 y, f64 x)   { return atan2(y, x); }

inline bool IsNearlyEqual(f32 a, f32 b, f32 epsilon = Math32::Epsilon) { return fabsf(a - b) <= epsilon; }
inline bool IsNearlyEqual(f64 a, f64 b, f64 epsilon = Math64::Epsilon) { return fabs(a - b) <= epsilon; }
inline bool IsNearlyZero(f32 a, f32 epsilon = Math32::Epsilon)             { return IsNearlyEqual(a, 0.0f, epsilon); }
inline bool IsNearlyZero(f64 a, f64 epsilon = Math64::Epsilon)             { return IsNearlyEqual(a, 0.0, epsilon); }

inline f32 DegreeToRadian(f32 a) { return a * Math32::Degree2Radian; }
inline f64 DegreeToRadian(f64 a) { return a * Math64::Degree2Radian; }
inline f32 RadianToDegree(f32 a) { return a * Math32::Radian2Degree; }
inline f64 RadianToDegree(f64 a) { return a * Math64::Radian2Degree; }
//////////////////////////////////////////////////////////////////////////