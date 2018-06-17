#include "Person.h"
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"

Appointment::Appointment() {}

Appointment::Appointment(Doctor* doctor, Patient* patient) {
	this->doctorId = doctor->getCode();
	this->patientId = patient->getCode();
}

Appointment::Appointment(string code, string doctorId, string patientId) {
	this->code = code;
	this->doctorId = doctorId;
	this->patientId = patientId;
}

string Appointment::getCode() const {
	return this->code;
}

string Appointment::getDoctorId() const {
	return this->doctorId;
}

string Appointment::getPatientId() const {
	return this->patientId;
}