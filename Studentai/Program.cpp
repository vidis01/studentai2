#include <iostream>
#include "Studentas_Class.h"
#include <list>

using namespace std;

int main()
{
	cout << "Hello." << endl;

	std::list<int> homeGrades;
	Studentas_Class studentas("Jonas", "Jonaitis", 6, homeGrades, 5.5);

	studentas.get_homeworksGrades().push_back(9);

	homeGrades.clear();

	studentas.set_homeworksGrades(homeGrades);

	cout << studentas.get_homeworksGrades().size() << endl;

	return 0;
}