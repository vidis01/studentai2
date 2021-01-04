#pragma once
#include <string>
#include <list>
#include "Studentas_Class.h"

using namespace std;

class Studentai_Class {
private:
	std::list<Studentas_Class> students;
	bool compareFunc(Studentas_Class&, Studentas_Class&);
	bool isLessThan5(Studentas_Class&);
public:
	void getData();
	void generateStudentsData(int);
	double generateStudentsFileFromStudentsList(int, int);
	double readFromFileToStudentsList(int);
	double sortStudentsList();
	double divideSudentsInTwoNewLists();
	double divedeStudentsInSameListAndOnlyOneNewList();
	void analyzeSpeedWithLists(int, int);
};

