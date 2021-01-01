#pragma once
#include <string>
#include <list>
#include "Studentas_Class.h"

using namespace std;

Studentas_Class::Studentas_Class(std::string name, std::string surname, int egzamResult, list<int>& homeworksGrades, float finalResult)
{
	this->name = name;
	this->surname = surname;
	this->egzamResult = egzamResult;
	this->homeworksGrades = homeworksGrades;
	this->finalResult = finalResult;
}

void Studentas_Class::set_name(std::string name )
{
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
