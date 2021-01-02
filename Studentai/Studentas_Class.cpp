#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Studentas_Class.h"

using namespace std;

Studentas_Class::Studentas_Class(std::string name, std::string surname, int egzamResult, list<int>& homeworksGrades) {
	this->name = name;
	this->surname = surname;
	this->egzamResult = egzamResult;
	this->homeworksGrades = homeworksGrades;
}

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

