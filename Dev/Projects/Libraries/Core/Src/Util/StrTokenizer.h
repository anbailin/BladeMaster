#pragma once

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

    BMStr Next();                                 // return the Next token, return "" if it ends
    void GetSubStr(TArray<BMStr>& subStr);

private:
    void SkipDelimiter();                               // ignore leading delimiters
    bool IsDelimiter(char c);                           // check if the current char is delimiter

    BMStr mBuffer;                                 // input string
    BMStr mToken;                                  // output string
    BMStr mDelimiter;                              // delimiter string
    BMStr::iterator mCurrPos;                // string iterator pointing the current position
};