#include "Doctor.h"


Doctor::Doctor(string code, string name, string specialty, int age, DailySchedule schedule)
	: Person(code, name, age, schedule){
	this->specialty = specialty;
}

Doctor::Doctor(string code, string name, string specialty, int age)
	: Doctor(code, name, specialty, age, DailySchedule()){}

Doctor::Doctor() {};

void Doctor::setSpecialty(string specialty) {
	string possibleSpecialties[] = {
		"AGGEIOLOGOS",
		"AKTINOLOGOS",
		"ANDROLOGOS",
		"GASTRENTEROLOGOS",
		"GUNAIKOLOGOS",
		"DERMATOLOGOS",
		"KARDIOLOGOS",
		"NEFROLOGOS",
		"ODONTIATROS",
		"OUROLOGOS",
		"PAIDIATROS",
		"OFTHALMIATROS",
		"PSUXOLOGOS",
		"PATHOLOGOS"
	}; 

	if (find(begin(possibleSpecialties), end(possibleSpecialties), specialty) != end(possibleSpecialties)) {
		this->specialty = specialty;
	}
	else throw "SpecialtyNotValid";
}

string Doctor::getSpecialty() const {
	return this->specialty;
}