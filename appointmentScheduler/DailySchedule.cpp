#include "DailySchedule.h"

DailySchedule::DailySchedule() {
}

vector<DailySchedule::timeSlot> DailySchedule::getAppointments() const {
	return this->appointments;
}

void DailySchedule::setAppointments(vector<DailySchedule::timeSlot> appointments) {
	this->appointments = appointments;
}

bool DailySchedule::isAvailableOnDateTime(string date, string time) {
	for (int i = 0; i < appointments.size(); i++) {
		if (date.back() == '\n') date.pop_back();
		if (appointments[i].date == date && appointments[i].time == time) return false;
	}
	return true;
}

void DailySchedule::createAppointment(string date, string time, Doctor * doctor, Patient* patient) {
	struct timeSlot newApp;
	if (date.back() == '\n') date.pop_back();
	newApp.date = date;
	newApp.time = time;
	newApp.appointment = Appointment(doctor, patient);
	appointments.push_back(newApp);
}
