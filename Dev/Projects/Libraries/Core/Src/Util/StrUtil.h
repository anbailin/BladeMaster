#pragma once

typedef std::string BMStr;
typedef std::wstring BMStrW;

void CORE_DLL StrToWStr(const std::string& src, std::wstring& dst);
void CORE_DLL WStrToStr(const std::wstring& src, std::string& dst);

