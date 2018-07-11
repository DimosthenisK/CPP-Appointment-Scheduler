#pragma once
#include <string>
#include <Appointment.h>
#include <iostream>
#include <json.h>

using namespace std;
using json = nlohmann::json;

class DailySchedule {
public:
	DailySchedule();
	struct timeSlot {
		Appointment appointment;
		string date;
		string time;
	};
	vector<timeSlot> getAppointments() const;
	void setAppointments(vector<timeSlot> appointments);
	bool isAvailableOnDateTime(string date, string time);
	void createAppointment(string date, string time, Doctor* doctor, Patient* patient);
private:
	vector<timeSlot> appointments;
};

