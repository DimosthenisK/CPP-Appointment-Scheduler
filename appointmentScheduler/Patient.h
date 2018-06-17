#pragma once
#include <string>
#include <Person.h>
#include <json.h>

using namespace std;
using json = nlohmann::json;

class Patient : public Person {
public:
	Patient();
	Patient(string code, string name, int age, DailySchedule schedule);
	Patient(string code, string name, int age);
};

