#include "Day.h"

Day::Day() {

}

vector<TimeSlot> Day::getTimeSlots() const {
	return this->times;
}

void Day::setTimeSlots(vector <TimeSlot> times) {
	this->times = times;
}