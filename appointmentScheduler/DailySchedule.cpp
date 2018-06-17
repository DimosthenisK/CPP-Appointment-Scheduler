#include "DailySchedule.h"

DailySchedule::DailySchedule() {
}

vector<Day> DailySchedule::getDays() const {
	return this->days;
}

void DailySchedule::setDays(vector<Day> days) {
	this->days = days;
}