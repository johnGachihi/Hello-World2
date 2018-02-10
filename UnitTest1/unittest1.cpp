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
			std::string date = "34/5/2222";
			Assert::AreEqual(isValid, ValChecker::dateIsValid(date));
			Assert::AreEqual(false, ValChecker::dateIsValid(date));
		}

		TEST_METHOD(AnotherOne) {

		}

	};
}