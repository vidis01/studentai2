// Studentai.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// v1.0.cpp : // This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <time.h>
#include <chrono>

using namespace std;

struct StudentData {
	string name;
	string surname;
	int egzamResult;
	list<int> homeworksGrades;
	float finalResult = 0;
};

void AnalyzeSpeedWithLists(int fileId, int dataCount);
void AnalyzeSpeedWithVectors(int fileId, int dataCount);
list<StudentData> GenerateStudentsListData(int count);
vector<StudentData> GenerateStudentsVectorData(int count);
double GenerateStudentsFileFromStudentsList(int fileId, int count, list<StudentData>& studentList);
double GenerateStudentsFileFromStudentsVector(int fileId, int count, vector<StudentData>& studentList);

double ReadFromFileToStudentsList(int fileId, list<StudentData>& studentsList);

double ReadFromFileToStudentsVector(int fileId, vector<StudentData>& studentsVector);

double SortStudentsList(list<StudentData>& studentsList);
double SortStudentsVector(vector<StudentData>& studentsVector);
double DivideStudentsInTwoNewVectors(vector<StudentData>& studentsVector);
double DivideSudentsInTwoNewLists(list<StudentData>& studentsList);
double DivedeStudentsInSameVectorAndOnlyOneNewVector(vector<StudentData>& studentsVector);
double DivedeStudentsInSameListAndOnlyOneNewList(list<StudentData>& studentsList);
bool IsLessThan5(StudentData studentData);
//------------------------------------------------------
void WriteTelemetryToConsole(int count);
void TestSpeed();
bool CompareFunc(StudentData studentData0, StudentData studentData1);
list<StudentData> ReadDataFromFile(string fileName);
void GenerateFile(int fileId, int count);
list <StudentData> GenerateData(int count);
float finalGrade(StudentData studentsData);
void RandomGradesGenerator(StudentData& studentsData);
bool IsNumber(string s);
float FindMedian(vector<int> homeworksGrades);
void ReadGradesFromConsole(StudentData& studentsData);
float Average(list<int> homeworksGrades);
void GetData(vector<StudentData>& data);

//Speed analysis data
int fileCreateStart = 0;
int fileCreateEnd = 0;
int fileReadStart = 0;
int fileReadEnd = 0;
int dataSortStart = 0;
int dataSortEnd = 0;
int dataSplitStart = 0;
int dataSplitEnd = 0;
int fileWriteLowGradesStart = 0;
int fileWriteLowGradesEnd = 0;
int fileWriteHighGradesStart = 0;
int fileWriteHighGradesEnd = 0;


//int main()
//{
//	AnalyzeSpeedWithLists(0, 1000);
//	AnalyzeSpeedWithVectors(0, 1000);
//
//	AnalyzeSpeedWithLists(1, 10000);
//	AnalyzeSpeedWithVectors(1, 10000);
//
//	AnalyzeSpeedWithLists(2, 100000);
//	AnalyzeSpeedWithVectors(2, 100000);
//
//	AnalyzeSpeedWithLists(3, 1000000);
//	AnalyzeSpeedWithVectors(3, 1000000);
//
//	return 0;
//}

void GetData(vector<StudentData>& data)
{
	int numberOfStudents;
	cout << "Kiek studentu nuskaityti? " << endl;
	cin >> numberOfStudents;

	for (int i = 0; i < numberOfStudents; i++)
	{
		StudentData studentsData; // laikinas kintamasis vieno studento duomenims saugoti
		cout << "Vardas is pavarde: " << endl;
		cin >> studentsData.name >> studentsData.surname;

		string gradesType; // ar bus ivedami ranka, ar generuojami atsitiktinai
		cout << "Jei norite ivesti i konsole veskite 'konsole' - jei sugeneruoti, iveskite 'generuoti'" << endl;
		cin >> gradesType;

		if (gradesType == "konsole")
		{
			ReadGradesFromConsole(studentsData);
		}
		else if (gradesType == "generuoti")
		{
			RandomGradesGenerator(studentsData);
		}
		else
		{
			cout << "Pasirinktas budas neegzistuoja - skaitoma is konsoles" << endl;
			ReadGradesFromConsole(studentsData);
		}

		data.push_back(studentsData);
	}
}

float Average(list<int> homeworksGrades)
{
	int sum = 0;

	if (homeworksGrades.size() < 1)
	{
		return 0;
	}

	for (list<int>::iterator it = homeworksGrades.begin(); it != homeworksGrades.end(); ++it) {
		sum += *it;
	}

	return sum * 1.0f / homeworksGrades.size();
}

void ReadGradesFromConsole(StudentData& studentsData)
{
	string egzamResultString;
	string invalidEgzamResultMessage = "Ivertinimas klaidingas, bus naudojamas 0";

	bool gradesExist = true; // ar ivestas dar vienas pazymys 
	string gradeString;
	bool isNull = true;

	cout << "Egzamino ivertinimas: " << endl;
	cin >> egzamResultString;

	bool number = IsNumber(egzamResultString);

	if (number == true)
	{
		int egzamResult = stoi(egzamResultString);

		if (egzamResult >= 0 && egzamResult <= 10)
		{
			studentsData.egzamResult = egzamResult;
		}
		else
		{
			cout << invalidEgzamResultMessage << endl;
			studentsData.egzamResult = 0;
		}
	}
	else
	{
		cout << invalidEgzamResultMessage << endl;
		studentsData.egzamResult = 0;
	}

	cout << "Iveskite pazymius atskirtus tarpais, baigus ivestite -1 ir paspauskite enter" << endl;
	while (gradesExist == true)
	{
		cin >> gradeString;

		int number = IsNumber(gradeString);

		if ((number == true) || (gradeString == "-1"))
		{
			int grade = std::stoi(gradeString);
			if (grade >= 0 && grade <= 10)
			{
				studentsData.homeworksGrades.push_back(grade);
				isNull = false;
			}
			else if (grade == -1 && isNull == true)
			{
				cout << "Pazymiai neivesti" << endl;
				continue;
			}
			else if (grade == -1)
			{
				gradesExist = false; // ivestas jau ne pazymys, o ivedimo stabdymo zenklas
			}
			else
			{
				cout << "Pazymiai turi buti desimtbaleje sistemoje" << endl;
				continue;
			}
		}
		else
		{
			cout << "Ivestas ne skaicius" << endl;
			continue;
		}
	}
}

float FindMedian(vector<int> homeworksGrades)
{
	if (homeworksGrades.size() < 1)
	{
		return 0;
	}
	// First we sort the array 
	sort(homeworksGrades.begin(), homeworksGrades.end());

	// check for even case 
	if (homeworksGrades.size() % 2 != 0)
		return (float)homeworksGrades[homeworksGrades.size() / 2];

	return (float)(homeworksGrades[(homeworksGrades.size() - 1) / 2] + homeworksGrades[homeworksGrades.size() / 2]) / 2.0f;
}

bool IsNumber(string s)
{
	try {
		int number = stoi(s);
	}
	catch (exception e)
	{
		return false;
	}
	return true;
}

//Updated this to generate grades without console input
void RandomGradesGenerator(StudentData& studentsData)
{
	studentsData.egzamResult = rand() % 10 + 1;
	//cout << "Egzamino pazimys: \n" << studentsData.egzamResult << endl;

	int numberOfGradesToGenerate = 10;
	//cout << "Kiek pazimiu sugeneruoti?" << endl;
	//cin >> numberOfGradesToGenerate;

	if (numberOfGradesToGenerate < 1) numberOfGradesToGenerate = 1;

	//cout << "Namu darbu pazymiai\n";
	for (int i = 0; i < numberOfGradesToGenerate; i++)
	{
		int random = rand() % 10 + 1;
		//cout << random << " ";
		studentsData.homeworksGrades.push_back(random);
	}
	//cout << endl;
}

//Updated this to work without console input
float finalGrade(StudentData studentsData)//, string howToCalculate)
{
	float results;

	//if (howToCalculate == "vid") // naudojamas vidurkis
	//{
	results = Average(studentsData.homeworksGrades);
	//}
	//else if (howToCalculate == "med") // naudojama mediana
	//{
	//	results = FindMedian(studentsData.homeworksGrades);
	/*}
	else
	{
		cout << "Pasirinktas skaiciavimo budas neegzistuoja, bus naudojamas vidurkis." << endl;
		results = Average(studentsData.homeworksGrades);
	}*/

	studentsData.finalResult = results * 0.4 + studentsData.egzamResult * 0.6;

	return studentsData.finalResult;
}

list<StudentData> GenerateStudentsListData(int count) {

	list <StudentData> studentlist;
	for (int i = 0; i < count; i++) {
		StudentData studentdata;
		studentdata.name = "vardas" + to_string(i);
		studentdata.surname = "pavarde" + to_string(i);

		RandomGradesGenerator(studentdata);
		studentdata.finalResult = finalGrade(studentdata);
		studentlist.push_back(studentdata);
	}

	return studentlist;
}

vector<StudentData> GenerateStudentsVectorData(int count) {

	vector <StudentData> studentlist;
	for (int i = 0; i < count; i++) {
		StudentData studentdata;
		studentdata.name = "vardas" + to_string(i);
		studentdata.surname = "pavarde" + to_string(i);

		RandomGradesGenerator(studentdata);
		studentdata.finalResult = finalGrade(studentdata);
		studentlist.push_back(studentdata);
	}

	return studentlist;
}

double GenerateStudentsFileFromStudentsList(int fileId, int count, list<StudentData>& studentList) {

	auto start = std::chrono::high_resolution_clock::now();

	ofstream file("file" + to_string(fileId) + ".txt");
	fileCreateEnd = time(0);

	for (list<StudentData>::iterator it = studentList.begin(); it != studentList.end(); ++it) {
		file << (*it).name << " " << (*it).surname << " " << (*it).finalResult << endl;
	}

	file.close();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

double GenerateStudentsFileFromStudentsVector(int fileId, int count, vector<StudentData>& studentList) {

	auto start = std::chrono::high_resolution_clock::now();

	ofstream file("file" + to_string(fileId) + ".txt");
	fileCreateEnd = time(0);

	for (vector<StudentData>::iterator it = studentList.begin(); it != studentList.end(); ++it) {
		file << (*it).name << " " << (*it).surname << " " << (*it).finalResult << endl;
	}

	file.close();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

double ReadFromFileToStudentsList(int fileId, list<StudentData>& studentsList) {

	ifstream file;
	file.open("file" + to_string(fileId) + ".txt", ifstream::in);

	auto start = std::chrono::high_resolution_clock::now();

	while (true) {
		StudentData studentData;

		file >> studentData.name;
		if (file.eof()) break;
		file >> studentData.surname;
		if (file.eof()) break;
		file >> studentData.finalResult;
		if (file.eof()) break;

		studentsList.push_back(studentData);
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	file.close();

	return diff.count();
}

double ReadFromFileToStudentsVector(int fileId, vector<StudentData>& studentsVector) {

	ifstream file;
	file.open("file" + to_string(fileId) + ".txt", ifstream::in);

	auto start = std::chrono::high_resolution_clock::now();

	while (true) {
		StudentData studentData;

		file >> studentData.name;
		if (file.eof()) break;
		file >> studentData.surname;
		if (file.eof()) break;
		file >> studentData.finalResult;
		if (file.eof()) break;
		studentsVector.push_back(studentData);
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	file.close();

	return diff.count();
}

double SortStudentsList(list<StudentData>& studentsList) {

	auto start = std::chrono::high_resolution_clock::now();
	studentsList.sort(CompareFunc);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

double SortStudentsVector(vector<StudentData>& studentsVector) {

	auto start = std::chrono::high_resolution_clock::now();
	sort(studentsVector.begin(), studentsVector.end(), CompareFunc);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

double DivideStudentsInTwoNewVectors(vector<StudentData>& studentsVector) {

	auto start = std::chrono::high_resolution_clock::now();
	vector<StudentData> lowGradeStudentsVector;
	vector<StudentData> highGradeStudentsVector;

	for (vector<StudentData>::iterator it = studentsVector.begin(); it != studentsVector.end(); ++it) {
		if ((*it).finalResult < 5.0) {
			lowGradeStudentsVector.push_back((*it));
		}
		else {
			highGradeStudentsVector.push_back((*it));
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

double DivideSudentsInTwoNewLists(list<StudentData>& studentsList) {

	auto start = std::chrono::high_resolution_clock::now();
	list<StudentData> lowGradeStudentsList;
	list<StudentData> highGradeStudentsList;

	for (list<StudentData>::iterator it = studentsList.begin(); it != studentsList.end(); ++it) {
		if ((*it).finalResult < 5.0) {
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

double DivedeStudentsInSameVectorAndOnlyOneNewVector(vector<StudentData>& studentsVector) {

	auto start = std::chrono::high_resolution_clock::now();
	vector<StudentData> lowGradeStudentsVector;

	for (vector<StudentData>::iterator it = studentsVector.begin(); it != studentsVector.end(); ++it) {
		if ((*it).finalResult < 5.0) {
			lowGradeStudentsVector.push_back((*it));
		}
	}
	//std::remove_if(studentsVector.begin(), studentsVector.end(), IsLessThan5);
	studentsVector.erase(
		std::remove_if(
			studentsVector.begin(), studentsVector.end(),
			IsLessThan5),
		studentsVector.end());

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

double DivedeStudentsInSameListAndOnlyOneNewList(list<StudentData>& studentsList) {

	auto start = std::chrono::high_resolution_clock::now();
	list<StudentData> lowGradeStudentsList;

	for (list<StudentData>::iterator it = studentsList.begin(); it != studentsList.end(); ++it) {
		if ((*it).finalResult < 5.0) {
			lowGradeStudentsList.push_back((*it));
		}
	}
	studentsList.remove_if(IsLessThan5);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	return diff.count();
}

bool IsLessThan5(StudentData studentData) { return studentData.finalResult < 5; }

list<StudentData> GenerateData(int count) {
	list<StudentData> studentlist;
	for (int i = 0; i < count; i++) {
		StudentData studentdata;
		studentdata.name = "vardas" + to_string(i);
		studentdata.surname = "pavarde" + to_string(i);

		RandomGradesGenerator(studentdata);
		studentdata.finalResult = finalGrade(studentdata);
		studentlist.push_back(studentdata);
	}

	return studentlist;
}

void GenerateFile(int fileId, int count) {
	fileCreateStart = time(0);
	ofstream file("file" + to_string(fileId) + ".txt");
	ofstream lowGrade("fileLowGrade" + to_string(fileId) + ".txt");
	ofstream highGrade("fileHighGrade" + to_string(fileId) + ".txt");
	fileCreateEnd = time(0);

	//Data generation and writing to file
	list<StudentData> studentlist = GenerateData(count);

	for (list<StudentData>::iterator it = studentlist.begin(); it != studentlist.end(); ++it) {
		file << (*it).name << " " << (*it).surname << " " << (*it).finalResult << endl;
	}

	file.close();
	studentlist.clear();

	//Data reading from file
	fileReadStart = time(0);
	studentlist = ReadDataFromFile("file" + to_string(fileId) + ".txt");
	fileReadEnd = time(0);

	//Data sorting
	dataSortStart = time(0);
	studentlist.sort(CompareFunc);
	dataSortEnd = time(0);

	//Data splitting into two groups
	dataSplitStart = time(0);
	list<StudentData> lowGradeStudentList;
	list<StudentData> highGradeStudentList;

	for (list<StudentData>::iterator it = studentlist.begin(); it != studentlist.end(); ++it) {
		if ((*it).finalResult < 5.0) {
			lowGradeStudentList.push_back((*it));
		}
		else {
			highGradeStudentList.push_back((*it));
		}
	}
	dataSplitEnd = time(0);

	//Data write file
	fileWriteLowGradesStart = time(0);
	for (list<StudentData>::iterator it = lowGradeStudentList.begin(); it != lowGradeStudentList.end(); ++it) {
		lowGrade << (*it).name << " " << (*it).surname << " " << (*it).finalResult << endl;
	}
	fileWriteLowGradesEnd = time(0);

	fileWriteHighGradesStart = time(0);
	for (list<StudentData>::iterator it = highGradeStudentList.begin(); it != highGradeStudentList.end(); ++it) {
		highGrade << (*it).name << " " << (*it).surname << " " << (*it).finalResult << endl;
	}
	fileWriteHighGradesEnd = time(0);

	lowGrade.close();
	highGrade.close();
}

list <StudentData> ReadDataFromFile(string fileName) {
	list <StudentData> studentsDataList;

	ifstream file;
	file.open(fileName, ifstream::in);

	while (true) {
		StudentData studentData;

		file >> studentData.name;
		if (file.eof()) break;
		file >> studentData.surname;
		if (file.eof()) break;
		file >> studentData.finalResult;
		if (file.eof()) break;
		studentsDataList.push_back(studentData);
	}

	file.close();

	return studentsDataList;
}

bool CompareFunc(StudentData studentData0, StudentData studentData1) {
	return studentData0.finalResult > studentData1.finalResult;
}

void TestSpeed() {

	GenerateFile(0, 1000);
	WriteTelemetryToConsole(1000);
	GenerateFile(1, 10000);
	WriteTelemetryToConsole(10000);
	GenerateFile(2, 100000);
	WriteTelemetryToConsole(100000);
	GenerateFile(3, 1000000);
	WriteTelemetryToConsole(1000000);
	GenerateFile(4, 10000000);
	WriteTelemetryToConsole(10000000);
}

void AnalyzeSpeedWithLists(int fileId, int dataCount)
{
	list<StudentData> studentsList = GenerateStudentsListData(dataCount);
	double timeSpentToGenerateStudentsFile = GenerateStudentsFileFromStudentsList(fileId, dataCount, studentsList);
	studentsList.clear();

	double timeSpentToReadStudentsFile = ReadFromFileToStudentsList(fileId, studentsList);

	double timeSpentToSortStudentsList = SortStudentsList(studentsList);
	double timeSpentToDivideStudentsInTwoNewLists = DivideSudentsInTwoNewLists(studentsList);
	double timeSpentToDivedeStudentsInSameListAndOnlyOneNewList =
		DivedeStudentsInSameListAndOnlyOneNewList(studentsList);

	cout << "list: Failo su " << dataCount << " irasu nuskaitymo laikas: " << timeSpentToReadStudentsFile << endl;

	cout << "list: Failo su " << dataCount << " irasu rusiavimas su sort funkcija laikas: " << timeSpentToSortStudentsList << endl;
	cout << "list: Failo su " << dataCount << " irasu dalijimo i dvi grupes laikas pagal 1 strategija: " << timeSpentToDivideStudentsInTwoNewLists << endl;
	cout << "list: Failo su " << dataCount << " irasu dalijimo i dvi grupes laikas pagal 2 strategija: " << timeSpentToDivedeStudentsInSameListAndOnlyOneNewList << endl;
	cout << "----------------------" << endl;

}

void AnalyzeSpeedWithVectors(int fileId, int dataCount)
{
	vector<StudentData> studentsVector = GenerateStudentsVectorData(dataCount);
	double timeSpentToGenerateStudentsFile = GenerateStudentsFileFromStudentsVector(fileId, dataCount, studentsVector);
	studentsVector.clear();
	double timeSpentToReadStudentsFile = ReadFromFileToStudentsVector(fileId, studentsVector);
	double timeSpentToSortStudentsVector = SortStudentsVector(studentsVector);
	double timeSpentToDivideStudentsInTwoNewVectors = DivideStudentsInTwoNewVectors(studentsVector);
	double timeSpentToDivedeStudentsInSameVectorAndOnlyOneNewVector =
		DivedeStudentsInSameVectorAndOnlyOneNewVector(studentsVector);

	cout << "vector: Failo su " << dataCount << " irasu nuskaitymo laikas: " << timeSpentToReadStudentsFile << endl;
	cout << "vector: Failo su " << dataCount << " irasu rusiavimas su sort funkcija laikas: " << timeSpentToSortStudentsVector << endl;
	cout << "vector: Failo su " << dataCount << " irasu dalijimo i dvi grupes laikas pagal 1 strategija: " << timeSpentToDivideStudentsInTwoNewVectors << endl;
	cout << "vector: Failo su " << dataCount << " irasu dalijimo i dvi grupes laikas pagal 2 strategija: " << timeSpentToDivedeStudentsInSameVectorAndOnlyOneNewVector << endl;
	cout << "----------------------" << endl;

}

void WriteTelemetryToConsole(int count) {
	cout << "Failo su " << count << " irasu nuskaitymo laikas: " << fileReadEnd - fileReadStart << endl;
	cout << "Failo su " << count << " irasu rusiavimas su sort funkcija laikas: " << dataSortEnd - dataSortStart << endl;
	cout << "Failo su " << count << " irasu dalijimo i dvi grupes laikas: " << dataSplitEnd - dataSplitStart << endl;
	cout << "Failo su " << count << " irasu nelaimingu irasymo i faila laikas: " << fileWriteLowGradesEnd - fileWriteLowGradesStart << endl;
	cout << "Failo su " << count << " irasu kietu su sort funkcija laikas: " << fileWriteHighGradesEnd - fileWriteHighGradesStart << endl;
	cout << endl;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
