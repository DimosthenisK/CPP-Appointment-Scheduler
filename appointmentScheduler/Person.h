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
	string getName() const;
	void setName(string name);
	string getCode() const;
	void setCode(string code);
	int getAge() const;
	void setAge(int age);
	void display();
protected:
	string name;
	string code;
	int age;
	DailySchedule schedule;
};

