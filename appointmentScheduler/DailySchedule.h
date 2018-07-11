#pragma once
#include <string>
#include <Day.h>
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
	vector<Day> getAppointments() const;
	void setDays(vector<timeSlot> appointments);
	bool isAvailableOnDateTime(string date, string time);
	Appointment getAppointmentByDateTime(string date, string time);
	void createAppointment(string date, string time);
private:
	vector<timeSlot> appointments;
};

