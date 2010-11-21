
///////////////////////////////////////////////////////////////////////////////
//
// SIMPLESTRING.H
//
// One of the design goals of CppUnitLite is to compilation with very old C++
// compilers.  For that reason, I've added a simple string class that provides
// only the operations needed in CppUnitLite.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SIMPLE_STRING
#define SIMPLE_STRING



class SimpleString
{
	friend bool	operator== (const SimpleString& left, const SimpleString& right);

public:
						SimpleString ();
						SimpleString (const TCHAR *value);
						SimpleString (const SimpleString& other);
						~SimpleString ();

	SimpleString		operator= (const SimpleString& other);

	TCHAR				*asCharString () const;
	int					size() const;

private:
	TCHAR				*buffer;
};



SimpleString StringFrom (bool value);
SimpleString StringFrom (const TCHAR *value);
SimpleString StringFrom (long value);
SimpleString StringFrom (int value);//guyu add
SimpleString StringFrom (double value);
SimpleString StringFrom (const SimpleString& other);
SimpleString StringFrom (const std::wstring& other);//guyu add



#endif
