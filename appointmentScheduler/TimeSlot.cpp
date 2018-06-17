#include "TimeSlot.h"

TimeSlot::TimeSlot() {
	this->available = true;
}

bool TimeSlot::isAvailable() const {
	return this->available;
}

Appointment TimeSlot::getAppointment() const {
	return this->appointment;
}

void TimeSlot::setAppointment(Appointment appointment) {
	this->appointment = appointment;
	this->available = false;
}