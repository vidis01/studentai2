#include <iostream>
#include "Studentas_Class.h"
#include <list>

using namespace std;

int main()
{
	cout << "Hello." << endl;

	std::list<int> homeGrades = { 4, 5, 8, 2, 1, 10};

	Studentas_Class studentas("Jonas", "Jonaitis", 6, homeGrades);

	cout << studentas.finalGrade("med") << endl;
	cout << studentas.finalGrade("vid") << endl;

	return 0;
}