// Included in CorePublic.h

namespace BM
{
    //////////////////////////////////////////////////////////////////////////
    // Types
    typedef	qint8       Int8;
    typedef	qint16      Int16;
    typedef	qint32      Int32;
    typedef	qint64      Int64;

    typedef	quint8      UInt8;
    typedef	quint16     UInt16;
    typedef	quint32     UInt32;
    typedef	quint64     UInt64;

    typedef float       Float32;
    typedef double      Float64;

    typedef UInt8       Byte;

    typedef QChar       Char;
    typedef QString     String;

    typedef Int8        int8;
    typedef Int16       int16;
    typedef Int32       int32;
    typedef Int64	    int64;

    typedef UInt8       uint8;
    typedef UInt16      uint16;
    typedef UInt32      uint32;
    typedef UInt64      uint64;
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // Min/Max values for each numeric types
    const Int8          Int8_Min                = -128;
    const Int8          Int8_Max                = 127;
    const UInt8         UInt8_Min               = 0;
    const UInt8         UInt8_Max               = 255;
    const Int16         Int16_Min               = -32768;
    const Int16         Int16_Max               = 32767;
    const UInt16        UInt16_Min              = 0;
    const UInt16        UInt16_Max              = 65535;
    const Int32         Int32_Min               = 0x80000000;
    const Int32         Int32_Max               = 0x7FFFFFFF;
    const UInt32        UInt32_Min              = 0x00000000;
    const UInt32        UInt32_Max              = 0xFFFFFFFF;
    const Int64         Int64_Min               = 0x8000000000000000ll;
    const Int64         Int64_Max               = 0x7FFFFFFFFFFFFFFFll;
    const UInt64        UInt64_Min              = 0x0000000000000000ull;
    const UInt64        UInt64_Max              = 0xFFFFFFFFFFFFFFFFull;

    const Float32       Float32_Min             = -3.402823466e+38f;
    const Float32       Float32_Max             = 3.402823466e+38f;
    const Float32       Float32_Positive_Min    = 1.175494351e-38f;
    const Float32       Float32_Positive_Max    = 3.402823466e+38f;
    const Int32         Float32_MinExp          = -126;
    const Int32         Float32_MaxExp          = 127;

    const Float64       Float64_Min             = -1.7976931348623158e+308;
    const Float64       Float64_Max             = 1.7976931348623158e+308;
    const Float64       Float64_Positive_Min    = 2.2250738585072014e-308;
    const Float64       Float64_Positive_Max    = 1.7976931348623158e+308;
    const Int32         Float64_MinExp          = -1022;
    const Int32         Float64_MaxExp          = 1023;

    const Byte          Byte_Min                = UInt8_Min;
    const Byte          Byte_Max                = UInt8_Max;
    //////////////////////////////////////////////////////////////////////////
}
