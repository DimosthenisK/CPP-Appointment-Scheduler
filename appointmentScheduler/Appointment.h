#pragma once
#include <json.h>
#include <string>

using namespace std;
using json = nlohmann::json;

class Doctor;
class Patient;
class Appointment {
public:
	Appointment();
	Appointment(Doctor* doctor, Patient* patient);
	Appointment(string code, string doctorId, string patientId);
	string getCode() const;
	string getDoctorId() const;
	string getPatientId() const;
private:
	string doctorId;
	string patientId;
	string code;
};

