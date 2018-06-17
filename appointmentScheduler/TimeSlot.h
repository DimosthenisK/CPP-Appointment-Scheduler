#pragma once
#include <json.h>
#include <string>
#include "Appointment.h"

using namespace std;
using json = nlohmann::json;

class TimeSlot {
public:
	TimeSlot();
	Appointment getAppointment() const;
	void setAppointment(Appointment appointment);
	bool isAvailable() const;
private:
	Appointment appointment;
	bool available;
};

