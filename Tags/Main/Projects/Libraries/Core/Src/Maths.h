// Included in CorePublic.h

namespace BM
{
    //////////////////////////////////////////////////////////////////////////
    // Constants
    namespace Math64
    {
        const Float64 Epsilon       = 0.000001;
        const Float64 Pi            = 3.1415926535897932384626433832795;
        const Float64 HalfPi        = Pi * 0.5;
        const Float64 TwoPi         = Pi * 2.0;
        const Float64 Degree2Radian = Pi / 180.0;
        const Float64 Radian2Degree = 180.0 / Pi;
    }
    namespace Math32
    {
        const Float32 Epsilon       = (Float32)Math64::Epsilon;
        const Float32 Pi            = (Float32)Math64::Pi;
        const Float32 HalfPi        = (Float32)Math64::HalfPi;
        const Float32 TwoPi         = (Float32)Math64::TwoPi;
        const Float32 Degree2Radian = (Float32)Math64::Degree2Radian;
        const Float32 Radian2Degree = (Float32)Math64::Radian2Degree;
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

    inline Int32   Abs(Int32 a)                 { return abs(a); }
    inline Int64   Abs(Int64 a)                 { return _abs64(a); }
    inline Float32 Abs(Float32 a)               { return fabsf(a); }
    inline Float64 Abs(Float64 a)               { return fabs(a); }

    inline Float32 Pow(Float32 a, Float32 e)    { return powf(a, e); }
    inline Float64 Pow(Float64 a, Float64 e)    { return pow(a, e); }

    inline Float32 Exp(Float32 a)               { return expf(a); }
    inline Float64 Exp(Float64 a)               { return exp(a); }

    inline Float32 Ln(Float32 a)                { return logf(a); }
    inline Float64 Ln(Float64 a)                { return log(a); }
    
    inline Float32 Log2(Float32 a)              { return logf(a) / logf(2.0f); }
    inline Float64 Log2(Float64 a)              { return log(a) / log(2.0); }
    
    inline Float32 Log10(Float32 a)             { return log10f(a); }
    inline Float64 Log10(Float64 a)             { return log10(a); }
    
    inline Float32 LogN(Float32 a, Float32 b)   { return logf(a) / logf(b); }
    inline Float64 LogN(Float64 a, Float64 b)   { return log(a) / log(b); }
    
    inline Float32 Modulo(Float32 a, Float32 b) { return fmodf(a, b); }
    inline Float64 Modulo(Float64 a, Float64 b) { return fmod(a, b); }
    
    inline Float32 Sqrt(Float32 a)              { return sqrtf(a); }
    inline Float64 Sqrt(Float64 a)              { return sqrt(a); }

    inline Float32 Ceil(Float32 a)              { return ceilf(a); }
    inline Float64 Ceil(Float64 a)              { return ceil(a); }
    
    inline Float32 Floor(Float32 a)             { return floorf(a); }
    inline Float64 Floor(Float64 a)             { return floor(a); }

    inline Float32 Round(Float32 a)             { return (Float32)((int)(a + (a > 0.0f ? 0.5f : -0.5f))); }
    inline Float64 Round(Float64 a)             { return (Float64)((int)(a + (a > 0.0 ? 0.5 : -0.5))); }

    inline Float32 Sin(Float32 x)               { return sinf(x); }
    inline Float64 Sin(Float64 x)               { return sin(x); }

    inline Float32 Cos(Float32 x)               { return cosf(x); }
    inline Float64 Cos(Float64 x)               { return cos(x); }

    inline Float32 Tan(Float32 x)               { return tanf(x); }
    inline Float64 Tan(Float64 x)               { return tan(x); }

    inline Float32 ASin(Float32 x)              { return asinf(x); }
    inline Float64 ASin(Float64 x)              { return asin(x); }

    inline Float32 ACos(Float32 x)              { return acosf(x); }
    inline Float64 ACos(Float64 x)              { return acos(x); }

    inline Float32 ATan(Float32 x)              { return atanf(x); }
    inline Float64 ATan(Float64 x)              { return atan(x); }

    inline Float32 ATan(Float32 y, Float32 x)   { return atan2f(y, x); }
    inline Float64 ATan(Float64 y, Float64 x)   { return atan2(y, x); }

    inline bool IsNearlyEqual(Float32 a, Float32 b, Float32 epsilon = Math32::Epsilon) { return fabsf(a - b) <= epsilon; }
    inline bool IsNearlyEqual(Float64 a, Float64 b, Float64 epsilon = Math64::Epsilon) { return fabs(a - b) <= epsilon; }
    inline bool IsNearlyZero(Float32 a, Float32 epsilon = Math32::Epsilon)             { return IsNearlyEqual(a, 0.0f, epsilon); }
    inline bool IsNearlyZero(Float64 a, Float64 epsilon = Math64::Epsilon)             { return IsNearlyEqual(a, 0.0, epsilon); }

    inline Float32 DegreeToRadian(Float32 a) { return a * Math32::Degree2Radian; }
    inline Float64 DegreeToRadian(Float64 a) { return a * Math64::Degree2Radian; }
    inline Float32 RadianToDegree(Float32 a) { return a * Math32::Radian2Degree; }
    inline Float64 RadianToDegree(Float64 a) { return a * Math64::Radian2Degree; }
    //////////////////////////////////////////////////////////////////////////
}
