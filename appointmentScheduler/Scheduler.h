#pragma once
#include <vector>
#include <fstream>
#include <json.h>
#include <array>
#include <sstream>
#include <Doctor.h>
#include <Patient.h>
#include <iomanip>

using namespace std;
class Scheduler {
public:
	Scheduler(vector<Doctor*> *doctors, vector<Patient*> *patients);
	void printAllAppointments();
	void scheduleOneAppointment();
	void scheduleAllAppointments();
	void printDoctorAppointments(Doctor& doctor);
	void showDoctorAppointments();
	void addDoctor();
private:
	void showHeader();
	void showHeader(string heading);
	vector<Doctor*>* doctors;
	vector<Patient*>* patients;
	vector<string> possibleTimes;
};