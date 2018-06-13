#include "Patient.h"

Patient::Patient(string code, string name, int age, DailySchedule schedule)
	: Person(code, name, age, schedule) {
}

Patient::Patient() {};

//Patient::Patient(const Patient &oldPatient) {
//
//}