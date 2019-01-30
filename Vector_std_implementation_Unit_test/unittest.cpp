#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Vector_std_implementation/vector.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vector_std_implementation_Unit_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(push_back_test){
			Vector<int> vec;
			vec.push_back(20);
			vec.push_back(21);
            vec.push_back(22);

		}

	};
}