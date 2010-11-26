#pragma once

typedef char            s8;
typedef unsigned char   u8;
typedef short           s16;
typedef unsigned short  u16;
typedef long            s32;
typedef unsigned long   u32;
typedef long long       s64;
typedef unsigned long long u64;
typedef float           f32;
typedef double          f64;
typedef int             sword;
typedef unsigned int    word;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Min/Max values for each numeric types
const s8          Int8_Min                = -128;
const s8          Int8_Max                = 127;
const u8         UInt8_Min               = 0;
const u8         UInt8_Max               = 255;
const s16         Int16_Min               = -32768;
const s16         Int16_Max               = 32767;
const u16        UInt16_Min              = 0;
const u16        UInt16_Max              = 65535;
const s32         Int32_Min               = 0x80000000;
const s32         Int32_Max               = 0x7FFFFFFF;
const u32        UInt32_Min              = 0x00000000;
const u32        UInt32_Max              = 0xFFFFFFFF;
const s64         Int64_Min               = 0x8000000000000000ll;
const s64         Int64_Max               = 0x7FFFFFFFFFFFFFFFll;
const u64        UInt64_Min              = 0x0000000000000000ull;
const u64        UInt64_Max              = 0xFFFFFFFFFFFFFFFFull;

const f32       Float32_Min             = -3.402823466e+38f;
const f32       Float32_Max             = 3.402823466e+38f;
const f32       Float32_Positive_Min    = 1.175494351e-38f;
const f32       Float32_Positive_Max    = 3.402823466e+38f;
const s32         Float32_MinExp          = -126;
const s32         Float32_MaxExp          = 127;

const f64       Float64_Min             = -1.7976931348623158e+308;
const f64       Float64_Max             = 1.7976931348623158e+308;
const f64       Float64_Positive_Min    = 2.2250738585072014e-308;
const f64       Float64_Positive_Max    = 1.7976931348623158e+308;
const s32         Float64_MinExp          = -1022;
const s32         Float64_MaxExp          = 1023;

const u8          Byte_Min                = UInt8_Min;
const u8          Byte_Max                = UInt8_Max;

