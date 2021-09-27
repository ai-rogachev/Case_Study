#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define PRIS 6

double get_answer(std::string fine_answer)
{
	std::ifstream infile(fine_answer);
	double answer = 0;
	infile >> answer;

	return answer;
}

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			double answer_ex = test_closestPoints("Test1.txt");
			double answer_ok = get_answer("Test1_Answ.txt");

			double answer = abs(answer_ex - answer_ok);
			Assert::IsTrue(answer < pow(10, PRIS));
		}

		TEST_METHOD(TestMethod2)
		{
			double answer_ex = test_closestPoints("Test2.txt");
			double answer_ok = get_answer("Test2_Answ.txt");

			double answer = abs(answer_ex - answer_ok);
			Assert::IsTrue(answer < pow(10, PRIS));
		}

		TEST_METHOD(TestMethod3)
		{
			double answer_ex = test_closestPoints("Test3.txt");
			double answer_ok = get_answer("Test3_Answ.txt");
			
			double answer = abs(answer_ex - answer_ok);
			Assert::IsTrue(answer < pow(10, PRIS));
		}

		TEST_METHOD(TestMethod4)
		{
			double answer_ex = test_closestPoints("Test4.txt");
			double answer_ok = get_answer("Test4_Answ.txt");

			double answer = abs(answer_ex - answer_ok);
			Assert::IsTrue(answer < pow(10, PRIS));
		}

		TEST_METHOD(TestMethod5)
		{
			double answer_ex = test_closestPoints("Test5.txt");
			double answer_ok = get_answer("Test5_Answ.txt");

			double answer = abs (answer_ex - answer_ok);
			Assert::IsTrue(answer < pow(10, PRIS));
		}

		TEST_METHOD(TestMethod6)
		{
			double answer_ex = test_closestPoints("Test6.txt");
			double answer_ok = get_answer("Test6_Answ.txt");

			double answer = abs(answer_ex - answer_ok);
			Assert::IsTrue(answer < pow(10, PRIS));
		}

		TEST_METHOD(TestMethod7)
		{
			double answer_ex = test_closestPoints("G:\\Êóðñ Ñ++ ÈÒÌÎ\\Stepik Online\\3 Week\\Code review\\UnitTest1\\Test7.txt");
			double answer_ok = get_answer("G:\\Êóðñ Ñ++ ÈÒÌÎ\\Stepik Online\\3 Week\\Code review\\UnitTest1\\Test7_Answ.txt");

			double answer = abs(answer_ex - answer_ok);
			Assert::IsTrue(answer < pow(10, PRIS));
		}

		TEST_METHOD(TestMethod8)
		{
			double answer_ex = test_closestPoints("G:\\Êóðñ Ñ++ ÈÒÌÎ\\Stepik Online\\3 Week\\Code review\\UnitTest1\\Test8.txt");
			double answer_ok = get_answer("G:\\Êóðñ Ñ++ ÈÒÌÎ\\Stepik Online\\3 Week\\Code review\\UnitTest1\\Test8_Answ.txt");

			double answer = abs(answer_ex - answer_ok);
			Assert::IsTrue(answer < pow(10, PRIS));
		}

	};
}