#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SwimDecide/ValChecker.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(DateValidityCheck)
		{
			bool isValid = false;
			std::string date = "  12/12/1998";
			//Assert::AreEqual(isValid, ValChecker::dateIsValid(date));
			Assert::AreEqual(true, ValidityChecker::dateIsValid(date));
		}

		TEST_METHOD(CheckTester) {
			std::deque<std::string> swimmerDets = { "1", "John", "12/12/2222", "1", "12M","1.23", "Q"};
			Assert::AreEqual(true, ValidityChecker::check(swimmerDets).size() < 1);
		}

	};
}