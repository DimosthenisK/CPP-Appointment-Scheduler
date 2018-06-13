#include "Person.h"
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"

Appointment::Appointment() {}

Appointment::Appointment(Doctor* doctor, Patient* patient) {
	this->doctorId = doctor->getCode();
	this->patientId = patient->getCode();
}

void to_json(json& j, const Appointment& Appointment) {}
void from_json(const json& j, Appointment& Appointment) {}