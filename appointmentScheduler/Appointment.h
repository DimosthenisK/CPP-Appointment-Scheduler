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
	void to_json(json& j, const Appointment& Appointment);
	void from_json(const json& j, Appointment& Appointment);
private:
	string doctorId;
	string patientId;
};

