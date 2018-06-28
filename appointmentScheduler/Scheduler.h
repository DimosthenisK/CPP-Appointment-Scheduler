#pragma once
#include <vector>
#include <fstream>
#include <json.h>
#include <Doctor.h>
#include <Patient.h>

using namespace std;
class Scheduler {
public:
	Scheduler(vector<Doctor*> *doctors, vector<Patient*> *patients);
	void printAllAppointments();
	Appointment* scheduleOneAppointment();
	void scheduleAllAppointments();
private:
	void showHeader();
	void showHeader(string heading);
	vector<Doctor*>* doctors;
	vector<Patient*>* patients;
	vector<string> possibleTimes;
};