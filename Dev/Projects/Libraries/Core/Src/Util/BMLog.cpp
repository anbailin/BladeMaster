#include "CorePrivate.h"

void LogToDebug(const wchar_t* str)
{
    OutputDebugStringW(str);
}

void LogToDebug(const char* str)
{
    OutputDebugStringA(str);
}

void LogToDebug( const TCHAR* fmt, ... )
{
    TCHAR TempStr[4096];
    va_list ArgPtr;	
    va_start( ArgPtr, fmt );
    int LastChar = _vstprintf_s(TempStr, sizeof(TempStr) / sizeof(TCHAR), fmt, ArgPtr);
    va_end( ArgPtr );
    TempStr[LastChar] = '\n';
    TempStr[LastChar+1] = 0;
    _tprintf(TempStr);
    OutputDebugString(TempStr);
}