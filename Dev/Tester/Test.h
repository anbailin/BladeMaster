///////////////////////////////////////////////////////////////////////////////
//
// TEST.H
// 
// This file contains the Test class along with the macros which make effective
// in the harness.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TEST_H
#define TEST_H


#include <cmath>
#include "SimpleString.h"

class TestResult;



class Test
{
public:
	Test (const SimpleString& testName, const SimpleString& testGroup, bool bIsSetup, bool bIsTearDown);//guyu, my setup,teardown extension
	virtual ~Test()
	{
		//Log.debugf(TEXT("Test class %s is destructed."), name_.asCharString());
	}
	virtual void	run (TestResult& result) = 0;

	void			setNext(Test *test);
	Test			*getNext () const;
	Test*			linkRunNext(Test *test){runNext_=test; return this;}//guyu extension
	void			setRunNext(Test *test){runNext_=test; }//guyu extension
	Test			*getRunNext () const {return runNext_;}//guyu extension
	bool IsSetup(){return m_bIsSetup;}//guyu extension
	bool IsTearDown(){return m_bIsTearDown;}//guyu extension

	TCHAR* GetName() {return name_.asCharString();}//guyu extension
	TCHAR* GetGroupName() {return group_.asCharString();}//guyu extension
protected:

	bool check (long expected, long actual, TestResult& result, const SimpleString& fileName, long lineNumber);
	bool check (const SimpleString& expected, const SimpleString& actual, TestResult& result, const SimpleString& fileName, long lineNumber);

	SimpleString	name_;
	SimpleString	group_;
	Test			*next_;
	Test			*runNext_;
	bool			m_bIsSetup, m_bIsTearDown;//guyu, my extension
};

#define TEST(testName, testGroup)\
  class testGroup##testName##Test : public Test \
{ public: testGroup##testName##Test () : Test (TEXT(#testName) TEXT("Test"), TEXT(#testGroup), false, false) {} \
            void run (TestResult& result_); }; \
    testGroup##testName##Test* testGroup##testName##Instance = new testGroup##testName##Test(); \
	void testGroup##testName##Test::run (TestResult& result_) 

#define TEST_SETUP(testName, testGroup)\
	class testGroup##testName##Test : public Test \
	{ public: testGroup##testName##Test () : Test (TEXT(#testName) TEXT("Test"),TEXT(#testGroup), true, false) {} \
	void run (TestResult& result_); }; \
	testGroup##testName##Test* testGroup##testName##Instance = new testGroup##testName##Test(); \
	void testGroup##testName##Test::run (TestResult& result_) 

#define TEST_TEARDOWN(testName, testGroup)\
	class testGroup##testName##Test : public Test \
	{ public: testGroup##testName##Test () : Test (TEXT(#testName) TEXT("Test"), TEXT(#testGroup),false, true) {} \
	void run (TestResult& result_); }; \
	testGroup##testName##Test* testGroup##testName##Instance = new testGroup##testName##Test(); \
	void testGroup##testName##Test::run (TestResult& result_) 


#define CHECK(condition)\
{ if (!(condition)) \
{ result_.addFailure (Failure (name_, TEXT(__FILE__),__LINE__, TEXT(#condition))); return; } }



#define CHECK_EQUAL(expected,actual)\
{ if ((expected) == (actual)) return; result_.addFailure(Failure(name_, TEXT(__FILE__), __LINE__, StringFrom(expected), StringFrom(actual))); }


#define LONGS_EQUAL(expected,actual)\
{ long actualTemp = actual; \
  long expectedTemp = expected; \
  if ((expectedTemp) != (actualTemp)) \
{ result_.addFailure (Failure (name_, TEXT(__FILE__), __LINE__, StringFrom(expectedTemp), \
StringFrom(actualTemp))); return; } }



#define DOUBLES_EQUAL(expected,actual,threshold)\
{ double actualTemp = actual; \
  double expectedTemp = expected; \
  if (fabs ((expectedTemp)-(actualTemp)) > threshold) \
{ result_.addFailure (Failure (name_, TEXT(__FILE__), __LINE__, \
StringFrom((double)expectedTemp), StringFrom((double)actualTemp))); return; } }


#define ANYTHING_EQUAL(str1, str2)\
{\
	if( str1 != str2 )\
	{ result_.addFailure (Failure (name_, TEXT(__FILE__), __LINE__, \
	StringFrom(str1), StringFrom(str2); return; } }\
}

#define FAIL(text) \
{ result_.addFailure (Failure (name_, TEXT(__FILE__), __LINE__,(text))); return; }



#endif
