#include "CorePrivate.h"

void StrToWStr(const std::string& src, std::wstring& dst)
{
    size_t size = src.size();
    dst.resize(size);
    MultiByteToWideChar(0, 0, src.c_str(), size, &dst[0], size);
}

void WStrToStr(const std::wstring& src, std::string& dst)
{
    size_t size = src.size();
    dst.resize(size);
    BOOL useDefaultChar = 0;    
    WideCharToMultiByte(0, 0, src.c_str(), size, &dst[0], size,"", &useDefaultChar);
    BM_Assert(useDefaultChar==0);

}

void StrSplit(const char* src, const char* split, std::vector<std::string>& output)
{
    
}