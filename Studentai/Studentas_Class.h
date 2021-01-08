#pragma once
#include <string>
#include <list>
#include  "Zmogus_Class.h"

using namespace std;

class Studentas_Class : public Zmogus_Class {
private:
	int egzamResult = 0;
	std::list<int> homeworksGrades;
	float finalResult = 0;
	bool isNumber(string);
public:
	//constructors
	Studentas_Class(std::string, std::string, int, std::list<int>&);
	Studentas_Class() : Zmogus_Class("", "") {};
	// copy constructor
	Studentas_Class(const Studentas_Class& stud)
		: Zmogus_Class(stud.name, stud.surname),
		homeworksGrades { stud.homeworksGrades },
		egzamResult { stud.egzamResult },
		finalResult { stud.finalResult }  { }
	// copy assignment operator
	Studentas_Class& operator=(const Studentas_Class& stud) {
		if (&stud == this) return *this;
		homeworksGrades.clear();
		name = stud.name;
		surname = stud.surname;
		homeworksGrades = stud.homeworksGrades;
		egzamResult = stud.egzamResult;
		finalResult = stud.finalResult;
		return *this;
	}
	//destructor
	~Studentas_Class() { };
	//setters
	void set_egzamResult(int);
	void set_homeworksGrades(std::list<int>&);
	void set_finalResult(float);
	//getters
	int get_egzamResult();
	std::list<int>& get_homeworksGrades();
	inline std::string getFullName() {
		return name + " " + surname;
	}
	float get_finalResult();
	//other member functions
	float findMedian();
	float average();
	float finalGrade(std::string);
	void readGradesFromConsole();
	void randomGradesGenerator();
};
