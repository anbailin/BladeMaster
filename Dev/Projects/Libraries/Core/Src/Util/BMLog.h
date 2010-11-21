#pragma once

void CORE_DLL LogToDebug(const wchar_t* str);
extern "C" void CORE_DLL LogToDebug(const TCHAR* fmt, ... );
void CORE_DLL LogToDebug(const char* str);