#pragma once
#include <string>
#include <list>

using namespace std;

class Studentas_Class {
private:
	std::string name;
	std::string surname;
	int egzamResult;
	std::list<int> homeworksGrades;
	float finalResult = 0;
public:
	//setters
	Studentas_Class(std::string, std::string, int, std::list<int>&);
	void set_name(std::string);
	void set_surname(std::string);
	void set_egzamResult(int);
	void set_homeworksGrades(std::list<int>&);
	void set_finalResult(float);
	//getters
	std::string get_name();
	std::string get_surname();
	int get_egzamResult();
	std::list<int>& get_homeworksGrades();
	float get_finalResult();
	//other member functions
	float findMedian();
	float average();
	float finalGrade(std::string);
};
