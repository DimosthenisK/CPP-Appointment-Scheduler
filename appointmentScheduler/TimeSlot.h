#pragma once
#include <json.h>
#include <string>
#include "Appointment.h"

using namespace std;
using json = nlohmann::json;

class TimeSlot {
public:
	void setAppointment(Appointment appointment);
	bool isAvailable();
	TimeSlot();
	void to_json(json& j, const TimeSlot& TimeSlot);
	void from_json(const json& j, TimeSlot& TimeSlot);
private:
	Appointment appointment;
	bool available;
};

