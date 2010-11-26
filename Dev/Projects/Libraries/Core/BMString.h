#pragma once

typedef std::string BMStr;
typedef std::wstring BMStrW;

class BMCrC
{
public:
    static u32 CreateCrc32(const char* str);
    static u32 CreateCrc32NoCase(const char* str);
    static u64 CreateCrc64(const char* str);
    static u64 CreateCrc64NoCase(const char* str);
};