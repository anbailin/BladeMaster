#include "stdafx.h"
#include "SimpleString.h"


static const int DEFAULT_SIZE = 512;

SimpleString::SimpleString ()
: buffer(new TCHAR [1])
{
	buffer [0] = '\0';
}


SimpleString::SimpleString (const TCHAR *otherBuffer)
: buffer (new TCHAR [_tcslen (otherBuffer) + 1])
{
	_tcscpy_s (buffer, _tcslen (otherBuffer) + 1, otherBuffer);
}

SimpleString::SimpleString (const SimpleString& other)
{
	buffer = new TCHAR [other.size() + 1];
	_tcscpy_s(buffer, other.size() + 1, other.buffer);
}


SimpleString SimpleString::operator= (const SimpleString& other)
{
	delete buffer;
	buffer = new TCHAR [other.size() + 1];
	_tcscpy_s(buffer, other.size() + 1, other.buffer);	
	return *this;
}


TCHAR *SimpleString::asCharString () const
{
	return buffer;
}

int SimpleString::size() const
{
	return (int)_tcslen (buffer);
}

SimpleString::~SimpleString ()
{
	delete [] buffer;
}


bool operator== (const SimpleString& left, const SimpleString& right)
{
	return !_tcscmp (left.asCharString (), right.asCharString ());
}


SimpleString StringFrom (bool value)
{
	TCHAR buffer [sizeof ("false") + 1];
	_stprintf_s (buffer, sizeof ("false") + 1, TEXT("%s"), value ? TEXT("true") : TEXT("false"));
	return SimpleString(buffer);
}

SimpleString StringFrom (const TCHAR *value)
{
	return SimpleString(value);
}

SimpleString StringFrom (long value)
{
	TCHAR buffer [DEFAULT_SIZE];
	_stprintf_s (buffer, DEFAULT_SIZE, TEXT("%ld"), value);

	return SimpleString(buffer);
}

SimpleString StringFrom (int value)
{
	TCHAR buffer [DEFAULT_SIZE];
	_stprintf_s (buffer, DEFAULT_SIZE, TEXT("%ld"), value);

	return SimpleString(buffer);
}


SimpleString StringFrom (double value)
{
	TCHAR buffer [DEFAULT_SIZE];
	_stprintf_s (buffer, DEFAULT_SIZE, TEXT("%lf"), value);

	return SimpleString(buffer);
}

SimpleString StringFrom (const SimpleString& value)
{
	return SimpleString(value);
}

SimpleString StringFrom (const std::wstring& other)
{
	return SimpleString(other.c_str());
}
