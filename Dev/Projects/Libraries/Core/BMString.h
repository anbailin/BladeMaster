#pragma once

/*
 *	BMString redefiniton
 */
typedef std::string BMStr;
typedef std::wstring BMStrW;

/*
 *	crc utilB
 */
class CORE_DLL BMCrC
{
public:
    static u32 CreateCrc32(const char* str);
    static u32 CreateCrc32(const char* str, u32 size);
    static u32 CreateCrc32NoCase(const char* str);
    static u32 CreateCrc32NoCase(const char* str, u32 size);
    static u64 CreateCrc64(const char* str);
    static u64 CreateCrc64NoCase(const char* str);
};

/*
 *	string utils
 */

void CORE_DLL StrToWStr(const std::string& src, std::wstring& dst);
void CORE_DLL WStrToStr(const std::wstring& src, std::string& dst);

/*
 *	string tokenizer
 */

const BMStr DEFAULT_DELIMITER = " \t\v\n\r\f";

class CORE_DLL StrTokenizer
{
public:
    // ctor/dtor
    StrTokenizer();
    StrTokenizer(const BMStr& str, const BMStr& delimiter=DEFAULT_DELIMITER);
    ~StrTokenizer();

    // Set string and delimiter
    void Set(const BMStr& str, const BMStr& delimiter=DEFAULT_DELIMITER);
    void SetString(const BMStr& str);             // Set source string only
    void SetDelimiter(const BMStr& delimiter);    // Set delimiter string only

    bool Next(BMStr& str);
    void GetSubStr(TArray<BMStr>& subStr);

private:
    void SkipDelimiter();                               // ignore leading delimiters
    bool IsDelimiter(char c);                           // check if the current char is delimiter

    BMStr mBuffer;                                 // input string
    BMStr mToken;                                  // output string
    BMStr mDelimiter;                              // delimiter string
    BMStr::iterator mCurrPos;                // string iterator pointing the current position
};