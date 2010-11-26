#include "CorePrivate.h"
#include "Utilities.h"
#include "TArray.h"
#include "BMString.h"

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

/*
 *	string tokenizer
 */

StrTokenizer::StrTokenizer() : mBuffer(""), mToken(""), mDelimiter(DEFAULT_DELIMITER)
{
    mCurrPos = mBuffer.begin();
}

StrTokenizer::StrTokenizer(const BMStr& str, const BMStr& delimiter) : mBuffer(str), mToken(""), mDelimiter(delimiter)
{
    mCurrPos = mBuffer.begin();
}

StrTokenizer::~StrTokenizer()
{
}

void StrTokenizer::Set(const BMStr& str, const BMStr& delimiter)
{
    mBuffer = str;                      
    mDelimiter = delimiter;
    mCurrPos = mBuffer.begin();
}

void StrTokenizer::SetString(const BMStr& str)
{
    mBuffer = str;
    mCurrPos = mBuffer.begin();
}

void StrTokenizer::SetDelimiter(const BMStr& delimiter)
{
    mDelimiter = delimiter;
    mCurrPos = mBuffer.begin();
}



bool StrTokenizer::Next(BMStr& str)
{
    if(mBuffer.size() <= 0 || mCurrPos==mBuffer.end()) 
    {
        return false;           // skip if buffer is empty
    }

    mToken.clear();                              // reset token string

    SkipDelimiter();                      // skip leading delimiters

    // append each char to token string until it meets delimiter
    while(mCurrPos != mBuffer.end() && !IsDelimiter(*mCurrPos))
    {
        mToken += *mCurrPos;
        ++mCurrPos;
    }
    str = mToken;
    return true;
}



///////////////////////////////////////////////////////////////////////////////
// skip ang leading delimiters
///////////////////////////////////////////////////////////////////////////////
void StrTokenizer::SkipDelimiter()
{
    while(mCurrPos != mBuffer.end() && IsDelimiter(*mCurrPos))
    {
        ++mCurrPos;
    }
}



///////////////////////////////////////////////////////////////////////////////
// return true if the current character is delimiter
///////////////////////////////////////////////////////////////////////////////
bool StrTokenizer::IsDelimiter(char c)
{
    return (mDelimiter.find(c) != BMStr::npos);
}

void StrTokenizer::GetSubStr(TArray<BMStr>& subStr)
{
    mCurrPos = mBuffer.begin();
    BMStr token;
    while(Next(token))
    {
        subStr.push_back(token);        
    }
}