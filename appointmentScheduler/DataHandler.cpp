#include "DataHandler.h"

#pragma region JSON_Methods
//Διαδικασίες που χρησιμοποιούνται από την βιβλιοθήκη json για γρήγορο parsing μεταξύ
//custom κλάσεων και δεδομένων json. Η βιβλιοθήκη δεν επιτρέπει να είναι μέλη μιας κλάσης,
//πρέπει να είναι στο ίδιο namespace όπου γίνεται η κλήση τους.
void to_json(json& j, const Patient& patient) {
	j = json{
		{ "code", patient.getCode() },
		{ "name", patient.getName() },
		{ "age", patient.getAge() },
		//{ "schedule", patient.schedule }
	};
}

//tempPatient γιατί διαγραφόντουσταν τα strings όταν έφευγε από το block.
Patient tempPatient;
void from_json(const json& j, Patient& patient) {
	patient.setCode(j.at("code").get<string>());
	patient.setName(j.at("name").get<string>());
	patient.setAge(j.at("age").get<int>());
	tempPatient = patient;
	//patient.schedule = j.at("schedule").get<DailySchedule>();
}

void to_json(json& j, const Doctor& doctor) {
	j = json{
		{ "code", doctor.getCode() },
		{ "name", doctor.getName() },
		{ "age", doctor.getAge() },
		{ "specialty", doctor.getSpecialty() },
		//{ "schedule", doctor.schedule }
	};
}

//tempDoctor γιατί διαγραφόντουσταν τα strings όταν έφευγε από το block.
Doctor tempDoctor;
void from_json(const json& j, Doctor& doctor) {
	doctor.setCode(j.at("code").get<string>());
	doctor.setName(j.at("name").get<string>());
	doctor.setAge(j.at("age").get<int>());
	doctor.setSpecialty(j.at("specialty").get<string>());
	tempDoctor = doctor;
	//doctor.schedule  = j.at("schedule").get<DailySchedule>();
}
#pragma endregion

DataHandler::DataHandler(vector<Doctor*> *doctors, vector<Patient*> *patients) {
	fstream fs;
	json scheduledData;

	fs.open("C:/Users/demos/Desktop/scheduledData.json", fstream::in);
	fs >> scheduledData;
	fs.close();

	json doctorsJ = scheduledData.find("doctors").value();
	json patientsJ = scheduledData.find("patients").value();

	for (json::iterator doctor = doctorsJ.begin(); doctor != doctorsJ.end(); ++doctor) {
		json newDoctorJ = doctor.value();
		newDoctorJ.get<Doctor>();
		doctors->push_back(&tempDoctor);
	}

	for (json::iterator patient = patientsJ.begin(); patient != patientsJ.end(); ++patient) {
		json newPatientJ = patient.value();
		&newPatientJ.get<Patient>();
		patients->push_back(&tempPatient);
	}
}