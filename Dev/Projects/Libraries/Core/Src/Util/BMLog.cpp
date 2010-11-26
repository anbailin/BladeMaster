#include "CorePrivate.h"
#include "Singleton.h"
#include "BMLog.h"

void LogToDebug(const wchar_t* str)
{
    OutputDebugStringW(str);
}

void LogToDebug(const char* str)
{
    OutputDebugStringA(str);
}

void LogToDebugW( const TCHAR* fmt, ... )
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

void CORE_DLL LogToDebugA(const char* fmt, ... )
{
    char TempStr[4096];
    va_list ArgPtr;	
    va_start( ArgPtr, fmt );
    int LastChar = vsprintf_s(TempStr, sizeof(TempStr) / sizeof(char), fmt, ArgPtr);
    va_end( ArgPtr );
    TempStr[LastChar] = '\n';
    TempStr[LastChar+1] = 0;
    //_tprintf(TempStr);
    OutputDebugStringA(TempStr);
}

SINGLETON_DEFINE(BMLog);

void BMLog::LogToDebug(const wchar_t* str)
{
    OutputDebugStringW(str);
}
void BMLog::LogToDebug(const wchar_t* fmt, ... )
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
void BMLog::LogToDebug(const char* str)
{
    OutputDebugStringA(str);
}
void BMLog::LogToDebug(const char* fmt, ... )
{
    char TempStr[4096];
    va_list ArgPtr;	
    va_start( ArgPtr, fmt );
    int LastChar = vsprintf_s(TempStr, sizeof(TempStr) / sizeof(char), fmt, ArgPtr);
    va_end( ArgPtr );
    TempStr[LastChar] = '\n';
    TempStr[LastChar+1] = 0;
    //_tprintf(TempStr);
    OutputDebugStringA(TempStr);
}

namespace
{
    const char* debugTypeNameA[ELT_Num] = 
    {
        "",
        "[Render]"        
    };

    const wchar_t* debugTypeNameW[ELT_Num] = 
    {
        L"",
        L"[Render]"        
    };

    const u32 strMaxSize = 2048;

    void GetTypeName(ELogType name, const char*& result)
    {
        result = debugTypeNameA[name];
    }

    void GetTypeName(ELogType name, const wchar_t*& result)
    {
        result = debugTypeNameW[name];
    }
}

void BMLog::LogToDebug(ELogType type,const wchar_t* str)
{
    wchar_t tempStr[strMaxSize];
    const wchar_t* typeName = NULL;
    GetTypeName(type, typeName);
    swprintf_s(tempStr, strMaxSize, L"%s%s \n", typeName, str);    

    OutputDebugStringW(tempStr);
}

void BMLog::LogToDebug(ELogType type,const wchar_t* fmt, ... )
{
    wchar_t tempStr[strMaxSize];
    const wchar_t* typeName = NULL;
    GetTypeName(type, typeName);
    sword len = swprintf_s(tempStr, strMaxSize, typeName);    

    va_list ArgPtr;	
    va_start( ArgPtr, fmt );
    len += _vstprintf_s(tempStr+len, strMaxSize-len, fmt, ArgPtr);
    va_end( ArgPtr );

    tempStr[len] = 0;

    OutputDebugStringW(tempStr);
}

void BMLog::LogToDebug(ELogType type,const char* str)
{
    char tempStr[strMaxSize];
    const char* typeName = NULL;
    GetTypeName(type, typeName);

    sprintf_s(tempStr, strMaxSize, "%s%s\n", typeName, str);
    OutputDebugStringA(tempStr);
}

void BMLog::LogToDebug(ELogType type,const char* fmt, ... )
{
    char tempStr[strMaxSize];
    const char* typeName = NULL;
    GetTypeName(type, typeName);

    sword len = sprintf_s(tempStr, strMaxSize, typeName);
    
    va_list ArgPtr;	
    va_start( ArgPtr, fmt );
    len += vsprintf_s(tempStr+len, strMaxSize-len, fmt, ArgPtr);
    va_end( ArgPtr );
    tempStr[len] = 0;

    OutputDebugStringA(tempStr);
}