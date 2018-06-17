#pragma once
#include <string>
#include <Day.h>
#include <json.h>

using namespace std;
using json = nlohmann::json;

class DailySchedule {
public:
	DailySchedule();
	vector<Day> getDays() const;
	void setDays(vector<Day> days);
	bool isAvailableOnDateTime(string date, string time);
	Appointment getAppointmentByDateTime(string date, string time);
	void createAppointment(string date, string time);
private:
	vector<Day> days;
};

