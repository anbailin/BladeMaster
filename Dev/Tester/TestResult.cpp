#include "stdafx.h"


TestResult::TestResult ()
	: failureCount (0),testCount(0)
{
}


void TestResult::testsStarted () 
{
}

void TestResult::addFailure (const Failure& failure) 
{
	LogToDebug(TEXT("%s(%ld) : Failure: \"%s\""),
		failure.fileName.asCharString (),
		failure.lineNumber,
		failure.message.asCharString ()
		);
		
	failureCount++;
}

void TestResult::addTestCount()//guyu extension
{
	testCount++;
}

void TestResult::testsEnded () 
{
	if (failureCount > 0)
		LogToDebug( TEXT("There were %ld failures(%d total)"), failureCount, testCount);
	else
		LogToDebug( TEXT("%d tests succeed"), testCount);
}
