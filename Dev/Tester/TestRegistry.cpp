#include "stdafx.h"


void TestRegistry::addTest (Test *test) 
{
	instance ().add (test);
}


void TestRegistry::runAllTests (TestResult& result, TCHAR *GroupNameArray[], int Number) //guyu extension, enable to run a list of tests
{
	instance ().run (result, GroupNameArray, Number);
}


TestRegistry& TestRegistry::instance () 
{
	static TestRegistry registry;
	return registry;
}


void TestRegistry::add (Test *test) 
{
	if (tests == 0) {
		tests = test;
		return;
	}
	test->setNext (tests);
	tests = test;	
}


void TestRegistry::run (TestResult& result, TCHAR *GroupNameArray[], int Number) 
{
	result.testsStarted ();
	
	//if( setup )
	//{
	//	setup->run(result);//guyu extension
	//	result.addTestCount();//guyu extension
	//}
	//Test *setup[] = new Test*[Number];
	//Test *teardown[] = new Test*[Number];
	//scan all test, and constructor the execution list
	
	for(int i = 0; i < Number; i++)
	{
		Test *setup = NULL;
		Test *teardown = NULL;
		Test *normal = NULL;
		Test *finallist = NULL;

		//collect all test for this group, store them in setup, teardown & normal
		for (Test *test = tests; test != 0; test = test->getNext ())
		{
			if(!_tcscmp( test->GetGroupName(), GroupNameArray[i] ))
			{
				if(test->IsSetup())
				{
					if(setup)
						assert(0 && TEXT("Only 1 setup is allowed in each test group"));
					else
						setup = test;
				}else if(test->IsTearDown())
				{
					if(teardown)
						assert(0 && TEXT("Only 1 teardown is allowed in each test group"));
					else
						teardown = test;
				}else
				{
					normal = test->linkRunNext(normal);
				}
			}
		}

		//construct the final running list
		if(setup)
			finallist = setup;
		if(normal)
		{
			if(finallist)
				finallist->setRunNext(normal);
			else
				finallist = normal;
		}
		if(teardown)
		{
			if(!finallist)
				finallist = teardown;
			else
			{
				Test* p = finallist;
				while(p)
				{
					if(!p->getRunNext())
						break;
					p = p->getRunNext();
				}
				p->setRunNext(teardown);
			}
		}

		if(finallist != NULL)
			LogToDebugW(TEXT("  Test group:%s"), finallist->GetGroupName());
		//run all tests
		for(Test* t = finallist; t; t=t->getRunNext())
		{			
			t->run(result);
			result.addTestCount();
		}
	}

	//for (Test *test = tests; test != 0; test = test->getNext ())
	//{
	//	bool bRunTest = true;
	//	if( Number != 0 )
	//	{
	//		int i;
	//		for( i = 0; i < Number; i++ )
	//		{
	//			if( !_tcscmp( test->GetGroupName(), GroupNameArray[i] ) )
	//				break;					
	//		}
	//		if( i >= Number )
	//			bRunTest = false;
	//	}
	//	
	//	if( bRunTest )
	//	{
	//		test->run (result);
	//		result.addTestCount();//guyu extension
	//	}
	//}

	//if( teardown )
	//{
	//	teardown->run(result);//guyu extension
	//	result.addTestCount();//guyu extension
	//}

	result.testsEnded ();
}

void TestRegistry::CleanAllTests(TestResult& result)
{
	TestRegistry &t = instance();
	Test *nexttest;
	for (Test *test = t.tests; test != 0; test = nexttest)
	{
		nexttest = test->getNext();
		delete test;
	}


}