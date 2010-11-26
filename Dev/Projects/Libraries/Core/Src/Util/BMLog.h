#pragma once
#include "Singleton.h"
void CORE_DLL LogToDebug(const wchar_t* str);
extern "C" void CORE_DLL LogToDebugW(const TCHAR* fmt, ... );
extern "C" void CORE_DLL LogToDebugA(const char* fmt, ... );
void CORE_DLL LogToDebug(const char* str);

enum ELogType
{
    ELT_None,
    ELT_Render,
    ELT_Num
};

class CORE_DLL BMLog
{
public:
    BMLog(){}
    SINGLETON_DECLARE(BMLog);

public:
    /*
     *	interface
     */
    void LogToDebug(const wchar_t* str);
    void LogToDebug(const wchar_t* fmt, ... );
    void LogToDebug(const char* str);
    void LogToDebug(const char* fmt, ... );
    void LogToDebug(ELogType type,const wchar_t* str);
    void LogToDebug(ELogType type,const wchar_t* fmt, ... );
    void LogToDebug(ELogType type,const char* str);
    void LogToDebug(ELogType type,const char* fmt, ... );    
};

//#define RENDER_LOG(param) BMLog::GetInstance()->LogToDebug(ELT_Render, param)
#define RENDER_LOG(...) BMLog::GetInstance()->LogToDebug(ELT_Render, __VA_ARGS__)