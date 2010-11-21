#include "stdafx.h"


Test::Test (const SimpleString& testName, const SimpleString& testGroup, bool bIsSetup, bool bIsTearDown) //guyu, my setup,teardown extension
	: name_ (testName) , group_(testGroup), m_bIsSetup( bIsSetup ), m_bIsTearDown(bIsTearDown), next_(0), runNext_(0)
{	
	TestRegistry::addTest (this);
}


Test *Test::getNext() const
{
	return next_;
}


void Test::setNext(Test *test)
{	
	next_ = test;
}

bool Test::check(long expected, long actual, TestResult& result, const SimpleString& fileName, long lineNumber)
{
	if (expected == actual)
		return true;
	result.addFailure (
		Failure (
			name_, 
			StringFrom (TEXT(__FILE__)), 
			__LINE__, 
			StringFrom (expected), 
			StringFrom (actual)));

	return false;

}


bool Test::check(const SimpleString& expected, const SimpleString& actual, TestResult& result, const SimpleString& fileName, long lineNumber)
{
	if (expected == actual)
		return true;
	result.addFailure (
		Failure (
			name_, 
			StringFrom (TEXT(__FILE__)), 
			__LINE__, 
			expected, 
			actual));

	return false;

}

