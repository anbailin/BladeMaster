#include "stdafx.h"
#include "Failure.h"

Failure::Failure (const SimpleString&	theTestName, 
				  const SimpleString&	theFileName, 
		          long	 				theLineNumber,
		          const SimpleString&	theCondition) 
: message (theCondition), 
  testName (theTestName), 
  fileName (theFileName), 
  lineNumber (theLineNumber)
{
}


Failure::Failure (const SimpleString&	theTestName, 
			 	  const SimpleString&	theFileName, 
				  long					theLineNumber,
				  const SimpleString&	expected,
				  const SimpleString&	actual) 
: testName (theTestName), 
  fileName (theFileName), 
  lineNumber (theLineNumber)
{
	TCHAR *part1 = TEXT("expected ");
	TCHAR *part3 = TEXT(" but was: ");

	//[guyu modify
	size_t buflen = _tcslen (part1) 
					+ expected.size () 
					+ _tcslen (part3)
					+ actual.size ()
					+ 1;
	TCHAR *stage = new TCHAR [buflen];

	_stprintf_s (stage, buflen, TEXT("%s%s%s%s"), 
		part1, 
		expected.asCharString(), 
		part3, 
		actual.asCharString());
	//]guyu

	message = SimpleString(stage);

	delete stage;
}


