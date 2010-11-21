///////////////////////////////////////////////////////////////////////////////
//
// TESTREGISTRY.H
// 
// TestRegistry is a singleton collection of all the tests to run in a system.  
// 
///////////////////////////////////////////////////////////////////////////////

#ifndef TESTREGISTRY_H
#define TESTREGISTRY_H
class Test;
class TestResult;

class TestRegistry
{
public:
	static void addTest (Test *test);
	static void runAllTests (TestResult& result, TCHAR *TestNameArray[], int Number);//guyu extension
	static void CleanAllTests(TestResult& result);//guyu extension, destroy all test case to prevent memory leak
	TestRegistry() {}
private:

	static TestRegistry&	instance ();
	void					add (Test *test);
	void					run (TestResult& result, TCHAR *TestNameArray[], int Number);

	Test	*tests;
};




#endif