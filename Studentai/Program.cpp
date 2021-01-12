#include <iostream>
#include "Studentai_Class.h"
#include "Studentas_Class.h"

using namespace std;

int main()
{
    srand(time(0));

    Studentai_Class studentai;
    Studentas_Class studentas;

    int n;
    cout << "Iveskite studentu skaicius: " << endl;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        studentas = Studentas_Class();
        studentas.set_name("Vardenis" + i);
        studentas.set_surname("Pavardenis" + i);
        studentas.set_egzamResult(rand() % 10 + 1);
        studentas.randomGradesGenerator();
        studentas.finalGrade("vid");
        studentai.get_studentai().push_back(studentas);
    }

	return 0;
}

