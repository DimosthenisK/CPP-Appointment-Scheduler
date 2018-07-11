#include "Person.h"

Person::Person(string code, string name, int age, DailySchedule schedule) {
	this->code = code;
	this->name = name;
	this->age = age;
	this->schedule = schedule;
}

Person::Person() {};

string Person::getName() const {
	return name;
}

string Person::getCode() const {
	return this->code;
}

int Person::getAge() const {
	return this->age;
}

void Person::setName(string name) {
	this->name = name;
}

void Person::setCode(string code) {
	this->code = code;
}

void Person::setAge(int age) {
	this->age = age;
}

void Person::display() {
	cout << this->name << endl;
}

DailySchedule Person::getSchedule() const {
	return this->schedule;
}

DailySchedule& Person::getSchedule(bool returnPtr) {
	return this->schedule;
}

void Person::setSchedule(DailySchedule schedule) {
	this->schedule = schedule;
}