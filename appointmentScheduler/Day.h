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
	vector<TimeSlot> getTimeSlots() const;
	void setTimeSlots(vector<TimeSlot> times);
private:
	vector<TimeSlot> times;
};