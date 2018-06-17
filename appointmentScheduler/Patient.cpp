#include "Patient.h"

Patient::Patient(string code, string name, int age, DailySchedule schedule)
	: Person(code, name, age, schedule) {
}

Patient::Patient(string code, string name, int age)
	: Patient(code, name, age, DailySchedule()) {}

Patient::Patient() {};

