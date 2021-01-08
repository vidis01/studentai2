#pragma once
#include <string>

using namespace std;

class Zmogus_Class {
protected:
	std::string name;
	std::string surname;
public:
	Zmogus_Class(std::string name, std::string surname) {
		this->name = name;
		this->surname = surname;
	}

	virtual std::string getFullName() = 0;

	void set_name(std::string name) {
		this->name = name;
	}

	void set_surname(std::string surname) {
		this->surname = surname;
	}

	std::string get_name() {
		return name;
	}

	std::string get_surname() {
		return surname;
	}
};