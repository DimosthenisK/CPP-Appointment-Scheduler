#pragma once
#include <string>
#include <Person.h>
#include <json.h>

using namespace std;
using json = nlohmann::json;

class Doctor : public Person {
public:
	string specialty;
public:
	Doctor();
	Doctor(string code, string name, string specialty, int age);
	Doctor(string code, string name, string specialty, int age, DailySchedule schedule);
	void setSpecialty(string specialty);
	string getSpecialty() const;
};

