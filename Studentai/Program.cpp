#include <iostream>
#include "Studentai_Class.h"
#include <list>

using namespace std;

int main()
{
	list<int> grades = {5, 6, 7, 8};
	Studentas_Class studentas("Vardenis", "Pavardenis", 8, grades);

	Studentas_Class studentasKopija = studentas;

	studentas.set_name("Ignas");

	cout << studentasKopija.get_name() << endl;

	return 0;
}