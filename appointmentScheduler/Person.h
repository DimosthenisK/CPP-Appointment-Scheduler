#pragma once
#include <json.h>
#include <string>
#include <iostream>
#include "DailySchedule.h"

using namespace std;
using json = nlohmann::json;

class Person {
public:
	Person();
	Person(string code, string name, int age, DailySchedule schedule);
	DailySchedule getSchedule() const;
	DailySchedule& getSchedule(bool returnPtr);
	bool operator==(string r) { //allow equality operator to work with person's code
		return r == getCode();
	}
	void setSchedule(DailySchedule schedule);
	string getName() const;
	void setName(string name);
	string getCode() const;
	void setCode(string code);
	int getAge() const;
	void setAge(int age);
	void display();
protected:
	string code;
	string name;
	int age;
	DailySchedule schedule;
};

