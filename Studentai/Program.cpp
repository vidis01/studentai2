#include <iostream>
#include "Studentai_Class.h"
#include <list>

using namespace std;

int main()
{
	Studentas_Class stud;
	float average = 9;
	std::list<int> grades = { 10, 9, 8, 7 };
	stud.set_homeworksGrades(grades);

	return 0;
}

