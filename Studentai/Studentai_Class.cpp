#include "Studentai_Class.h"
#include "Studentas_Class.h"
#include <iostream>
#include <string>
#include <list>
#include <chrono>
#include <fstream>

using namespace std;

bool Studentai_Class::compareFunc(Studentas_Class& studentData0, Studentas_Class& studentData1) {
	return studentData0.get_finalResult() > studentData1.get_finalResult();
}

bool Studentai_Class::isLessThan5(Studentas_Class &studentData) { return studentData.get_finalResult() < 5; }

void Studentai_Class::getData() {

	int numberOfStudents;
	std::string name, surname;
	cout << "Kiek studentu nuskaityti? " << endl;
	cin >> numberOfStudents;

	for (int i = 0; i < numberOfStudents; i++)
	{
		Studentas_Class studentsData; // laikinas kintamasis vieno studento duomenims saugoti
		cout << "Vardas is pavarde: " << endl;
		cin >> name >> surname;

		string gradesType; // ar bus ivedami ranka, ar generuojami atsitiktinai
		cout << "Jei norite ivesti i konsole veskite 'konsole' - jei sugeneruoti, iveskite 'generuoti'" << endl;
		cin >> gradesType;

		if (gradesType == "konsole")
		{
			studentsData.readGradesFromConsole();
		}
		else if (gradesType == "generuoti")
		{
			studentsData.randomGradesGenerator();
		}
		else
		{
			cout << "Pasirinktas budas neegzistuoja - skaitoma is konsoles" << endl;
			studentsData.readGradesFromConsole();
		}

		students.push_back(studentsData);
	}
}

void Studentai_Class::generateStudentsData(int count) {
		
	for (int i = 0; i < count; i++) {
		Studentas_Class studentdata;
		studentdata.set_name("vardas" + to_string(i));
		studentdata.set_surname("pavarde" + to_string(i));

		studentdata.randomGradesGenerator();
		studentdata.finalGrade("vid");
		students.push_back(studentdata);
	}
}

double Studentai_Class::generateStudentsFileFromStudentsList(int fileId, int count) {

	auto start = std::chrono::high_resolution_clock::now();

	ofstream file("file" + to_string(fileId) + ".txt");

	for (auto it = students.begin(); it != students.end(); ++it) {
		file << (*it).get_name() << " " << (*it).get_surname() << " " << (*it).get_finalResult() << endl;
	}

	file.close();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

double Studentai_Class::readFromFileToStudentsList(int fileId) {

	ifstream file;
	file.open("file" + to_string(fileId) + ".txt", ifstream::in);

	auto start = std::chrono::high_resolution_clock::now();

	while (true) {
		Studentas_Class studentData;
		std::string name, surname, finalResult;

		file >> name;
		studentData.set_name(name);
		if (file.eof()) break;
		file >> surname;
		studentData.set_surname(surname);
		if (file.eof()) break;
		file >> finalResult;
		studentData.set_finalResult(std::stof(finalResult));
		if (file.eof()) break;

		students.push_back(studentData);
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	file.close();

	return diff.count();
}

double Studentai_Class::sortStudentsList() {

	auto start = std::chrono::high_resolution_clock::now();
	//students.sort(compareFunc);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

double Studentai_Class::divideSudentsInTwoNewLists() {

	auto start = std::chrono::high_resolution_clock::now();
	list<Studentas_Class> lowGradeStudentsList;
	list<Studentas_Class> highGradeStudentsList;

	for (auto it = students.begin(); it != students.end(); ++it) {
		if ((*it).get_finalResult() < 5.0) {
			lowGradeStudentsList.push_back((*it));
		}
		else {
			highGradeStudentsList.push_back((*it));
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

double Studentai_Class::divedeStudentsInSameListAndOnlyOneNewList() {

	auto start = std::chrono::high_resolution_clock::now();
	list<Studentas_Class> lowGradeStudentsList;

	for (auto it = students.begin(); it != students.end(); ++it) {
		if ((*it).get_finalResult() < 5.0) {
			lowGradeStudentsList.push_back((*it));
		}
	}

	//students.remove_if(isLessThan5);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

void Studentai_Class::analyzeSpeedWithLists(int fileId, int dataCount)
{
	generateStudentsData(dataCount);
	double timeSpentToGenerateStudentsFile = generateStudentsFileFromStudentsList(fileId, dataCount);
	students.clear();

	double timeSpentToReadStudentsFile = readFromFileToStudentsList(fileId);

	double timeSpentToSortStudentsList = sortStudentsList();
	double timeSpentToDivideStudentsInTwoNewLists = divideSudentsInTwoNewLists();
	double timeSpentToDivedeStudentsInSameListAndOnlyOneNewList =
		divedeStudentsInSameListAndOnlyOneNewList();

	cout << "list: Failo su " << dataCount << " irasu nuskaitymo laikas: " << timeSpentToReadStudentsFile << endl;
	cout << "list: Failo su " << dataCount << " irasu rusiavimas su sort funkcija laikas: " << timeSpentToSortStudentsList << endl;
	cout << "list: Failo su " << dataCount << " irasu dalijimo i dvi grupes laikas pagal 1 strategija: " << timeSpentToDivideStudentsInTwoNewLists << endl;
	cout << "list: Failo su " << dataCount << " irasu dalijimo i dvi grupes laikas pagal 2 strategija: " << timeSpentToDivedeStudentsInSameListAndOnlyOneNewList << endl;
	cout << "----------------------" << endl;

}