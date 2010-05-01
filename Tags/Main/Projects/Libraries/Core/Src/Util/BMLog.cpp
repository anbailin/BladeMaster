#include "Core.h"

void LogToDebug(const wchar_t* str)
{
    OutputDebugStringW(str);
}

void LogToDebug(const char* str)
{
    OutputDebugStringA(str);
}
