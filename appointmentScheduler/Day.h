#pragma once
#include <json.h>
#include <string>
#include "Appointment.h"
#include "TimeSlot.h"

using namespace std;
using json = nlohmann::json;

class Day {
public:
	Day();
	bool isTimeAvailable(string time);
	Appointment* getAppointmentByTime(string time);
	void to_json(json& j, const Day& day);
	void from_json(const json& j, Day& day);
private:
	vector<TimeSlot> times;
};