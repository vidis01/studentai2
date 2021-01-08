#include <iostream>
#include "Studentai_Class.h"
#include <list>

using namespace std;

int main()
{
	list<int> grades = {5, 6, 7, 8};
	Studentas_Class studentas("Vardenis", "Pavardenis", 8, grades);

	cout << studentas.getFullName() << endl;

	return 0;
}