#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Studentas_Class.h"

using namespace std;

bool Studentas_Class::isNumber(string s)
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

Studentas_Class::Studentas_Class(std::string name, std::string surname, int egzamResult, list<int>& homeworksGrades) {
	this->name = name;
	this->surname = surname;
	this->egzamResult = egzamResult;
	this->homeworksGrades = homeworksGrades;
}

Studentas_Class::Studentas_Class() { };

void Studentas_Class::set_name(std::string name ) {
	this->name = name;
}

void Studentas_Class::set_surname(std::string surname) {
	this->surname = surname;
}

void Studentas_Class::set_egzamResult(int egzamResult) {
	this->egzamResult = egzamResult;
}

void Studentas_Class::set_homeworksGrades(std::list<int>& homeworksGrades) {
	this->homeworksGrades = homeworksGrades;
}

void Studentas_Class::set_finalResult(float finalResult) {
	this->finalResult = finalResult;
}

std::string Studentas_Class::get_name() {
	return name;
}

std::string Studentas_Class::get_surname() {
	return surname;
}

int Studentas_Class::get_egzamResult() {
	return egzamResult;
}

std::list<int>& Studentas_Class::get_homeworksGrades() {
	return homeworksGrades;
}

float Studentas_Class::get_finalResult() {
	return finalResult;
}

float Studentas_Class::average() {

	int sum = 0;

	for (int grade : homeworksGrades)
	{
		sum += grade;
	}

	return (float)sum/homeworksGrades.size();
}

float Studentas_Class::findMedian() {

	if (homeworksGrades.size() < 1) {
		return 0;
	}
	//First we sort grades. 
	homeworksGrades.sort();

	// Check for odd case.
	auto front = homeworksGrades.begin();
	int midle = homeworksGrades.size() / 2;

	if (homeworksGrades.size() % 2 != 0) {		

		std::advance(front, midle);

		return (float)*front;
	}
	else {

		std::advance(front, midle);
		int middle_b = *front;
		std::advance(front, -1);
		int middle_a = *front;

		return (float)(middle_b + middle_a) / 2;
	}
}

float Studentas_Class::finalGrade(std::string howToCalculate) {

	float results;

	if (howToCalculate == "vid") //naudojamas vidurkis
	{
		results = average();
	}
	else if (howToCalculate == "med") //naudojama mediana
	{
		results = findMedian();
	}
	else
	{
		cout << "Pasirinktas skaiciavimo budas neegzistuoja, bus naudojamas vidurkis." << endl;
		results = average();
	}

	finalResult = results * 0.4 + egzamResult * 0.6;

	return finalResult;
}

void Studentas_Class::readGradesFromConsole()
{
	string egzamResultString;
	string invalidEgzamResultMessage = "Ivertinimas klaidingas, bus naudojamas 0";

	bool gradesExist = true; // ar ivestas dar vienas pazymys 
	string gradeString;
	bool isNull = true;

	cout << "Egzamino ivertinimas: " << endl;
	cin >> egzamResultString;

	bool number = isNumber(egzamResultString);

	if (number == true)
	{
		int egzamResult = stoi(egzamResultString);

		if (egzamResult >= 0 && egzamResult <= 10)
		{
			this->egzamResult = egzamResult;
		}
		else
		{
			cout << invalidEgzamResultMessage << endl;
			this->egzamResult = 0;
		}
	}
	else
	{
		cout << invalidEgzamResultMessage << endl;
		this->egzamResult = 0;
	}

	cout << "Iveskite pazymius atskirtus tarpais, baigus ivestite -1 ir paspauskite enter" << endl;
	while (gradesExist == true)
	{
		cin >> gradeString;

		int number = isNumber(gradeString);

		if ((number == true) || (gradeString == "-1"))
		{
			int grade = std::stoi(gradeString);
			if (grade >= 0 && grade <= 10)
			{
				homeworksGrades.push_back(grade);
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

void Studentas_Class::randomGradesGenerator()
{
	egzamResult = rand() % 10 + 1;

	int numberOfGradesToGenerate = 10;
	for (int i = 0; i < numberOfGradesToGenerate; i++)
	{
		int random = rand() % 10 + 1;
		homeworksGrades.push_back(random);
	}
}

