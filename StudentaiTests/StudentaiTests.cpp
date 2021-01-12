#include "pch.h"
#include "CppUnitTest.h"
#include <list>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StudentaiTests
{
	TEST_CLASS(StudentaiTests)
	{
	public:
		
		TEST_METHOD(TestStudentSetName)
		{
			Studentas_Class stud;
			std::string name = "Jonas";
			stud.set_name("Jonas");
			Assert::AreEqual(name, stud.get_name());
		}

		TEST_METHOD(AverageTest)
		{
			Studentas_Class stud;
			float average = 8.5;
			std::list<int> grades = { 10, 9, 8, 7 };
			stud.set_homeworksGrades(grades);
			Assert::IsTrue(stud.average() == average);
		}

		TEST_METHOD(MedianaTest)
		{
			Studentas_Class stud;
			float mediana = 8;
			std::list<int> grades = { 10, 9, 8, 7 };
			stud.set_homeworksGrades(grades);
			Assert::AreNotEqual(stud.findMedian(), mediana);
		}
	};
}
