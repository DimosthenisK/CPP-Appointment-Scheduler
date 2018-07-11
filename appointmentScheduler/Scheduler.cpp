#include "Scheduler.h"

string genCode(size_t length) {
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

Scheduler::Scheduler(vector<Doctor*>* doctors, vector<Patient*>* patients) {
	this->doctors = doctors;
	this->patients = patients;

	time_t desirable = time(0) + 60 * 60 * 24;
	struct tm desirableTM;
	localtime_s(&desirableTM, &desirable);

	stringstream cTime;
	int hour = 8;
	string minutes = "00";
	cTime << hour << ":" << minutes;

	while (cTime.str() != "18:00") {
		this->possibleTimes.push_back(cTime.str());

		if (minutes == "00") minutes = "15";
		else if (minutes == "15") minutes = "30";
		else if (minutes == "30") minutes = "45";
		else if (minutes == "45") {
			hour++;
			minutes = "00";
		}

		cTime.str(string());
		cTime.clear();
		cTime << hour << ":" << minutes;
	}							
}

void Scheduler::printAllAppointments() {
	showHeader();
	for (int i = 0; i < doctors->size(); i++) {
		cout << "Γιατρός: " << doctors->at(i)->getName() << endl;
		vector<DailySchedule::timeSlot> ds = doctors->at(i)->getSchedule(true).getAppointments();
		if (ds.size() == 0) cout << "\tΔεν βρέθηκαν ραντεβού." << endl;
		else {
			map<string, vector<DailySchedule::timeSlot>> appMap;

			for (int j = 0; j < ds.size(); j++) {
				appMap[ds[j].date].push_back(ds[j]);
			}

			for (map<string, vector<DailySchedule::timeSlot>>::iterator it = appMap.begin(); it != appMap.end(); ++it) {
				cout << "\t" << it->first << endl;
				for (int k = 0; k < it->second.size(); k++) {
					cout << "\t\t" << it->second.at(k).time << ": ";
					for (int l = 0; l < patients->size(); l++) {
						if (*patients->at(l) == it->second.at(k).appointment.getPatientId()) cout << patients->at(l)->getName();
					}
					cout << endl;
				}
			}
		}
		cout << endl;
	}
	system("pause");
}

void Scheduler::scheduleOneAppointment() {
	string buffer;
	Patient* patient;
	Doctor* doctor;
	showHeader("Νέο Ραντεβού");

	cout << "Έχετε ξαναχρησιμοποιήσει αυτήν την εφαρμογή? (Y/Yes/yes/N/No/no) ";
	cin >> buffer;
	while (
		buffer != "Y" && buffer != "Yes" && buffer != "yes" &&
		buffer != "N" && buffer != "No"  && buffer != "no") {
		cout << "Λάθος είσοδος. Παρακαλώ εισάγετε κάτι μεταξύ Y/Yes/yes για ναι, ή N/No/no για όχι.";
		cout << "Έχετε ξαναχρησιμοποιήσει αυτήν την εφαρμογή? (Y/Yes/yes/N/No/no) ";
		cin >> buffer;
	}

	showHeader("Νέο Ραντεβού - Επιλογή ασθενή");

	if (buffer == "Y" || buffer == "Yes" || buffer == "yes") {
		int selection;

		for (int i = 0; i < patients->size(); i++) {
			cout << i + 1 << ". " << patients->at(i)->getName() << endl;
		}

		cout << "Επιλέξτε τον αριθμό ασθενή σας: ";
		cin >> selection;

		while (selection < 1 || selection >> patients->size()) {
			cout << "Παρακαλώ εισάγετε έναν σωστό αριθμό ασθενή: ";
			cin >> selection;
		}

		patient = patients->at(selection - 1);
	}
	else {
		string name;
		string code = genCode(4);
		int age;
		cout << "Εισαγωγή ονόματος ασθενή: ";
		cin.clear();
		cin.ignore();
		getline(cin, name);
		cout << "Εισαγωγή ηλικίας: ";
		cin >> age;

		patient = new Patient(code, name, age);
		patients->push_back(patient);
	}

	showHeader("Νέο Ραντεβού - Επιλογή Ιατρού");

	int selection;

	for (int i = 0; i < doctors->size(); i++) {
		cout << i + 1 << ". " << doctors->at(i)->getName() << " (" << doctors->at(i)->getSpecialty() << ")" << endl;
	}

	cout << "Επιλέξτε τον αριθμό Ιατρού σας: ";
	cin >> selection;

	while (selection < 1 || selection >> doctors->size()) {
		cout << "Παρακαλώ εισάγετε έναν σωστό αριθμό Ιατρού: ";
		cin >> selection;
	}

	doctor = doctors->at(selection - 1);

	showHeader("Νέο Ραντεβού - Επιλογή ημερομηνίας");
	cout << "Εισάγετε την επιθυμητή ημερομηνία του ραντεβού σας στην μορφη DD-MM-ΥΥΥΥ: " ;
	tm t = {};
	cin >> get_time(&t, "%d-%m-%Y");
	while (cin.fail()) {
		cin.clear();
		cin.ignore();

		cout << "Παρακαλώ εισάγετε μια έγκυρη ημερομηνία για το ραντεβού σας στην μορφη DD-MM-ΥΥΥΥ: " ;
		cin >> get_time(&t, "%d-%m-%Y");
	}
	stringstream appointmentDate;
	appointmentDate << put_time(&t, "%d-%m-%Y") << endl;

	cin.clear();
	cin.ignore();
	
	showHeader("Νέο Ραντεβού - Επιλογή ώρας");
	cout << "Εισάγετε μια από τις παρακάτω διαθέσιμες ώρες: " << endl;
	
	DailySchedule& ds = doctor->getSchedule(true);

	for (int i = 0; i < possibleTimes.size(); i++) {
		if (!ds.isAvailableOnDateTime(appointmentDate.str(), possibleTimes.at(i))) continue;
		cout << possibleTimes.at(i) << endl;
	}

	string wantedTime;
	cout << "Επιθυμητή ώρα: ";
	getline(cin, wantedTime);
	while (find(begin(possibleTimes), end(possibleTimes), wantedTime) == end(possibleTimes) || !ds.isAvailableOnDateTime(appointmentDate.str(), wantedTime)) {
		cout << "Παρακαλώ εισάγετε μια σωστή ώρα για το ραντεβού σας: ";
		getline(cin, wantedTime);
	}

	ds.createAppointment(appointmentDate.str(), wantedTime, doctor, patient);
	patient->getSchedule().createAppointment(appointmentDate.str(), wantedTime, doctor, patient);

	showHeader("Νέο Ραντεβού");
	cout << "Επιτυχής καταχώρηση!" << endl;
	system("pause");
}

void Scheduler::printDoctorAppointments(Doctor& doctor) {
	vector<DailySchedule::timeSlot> ds = doctor.getSchedule().getAppointments();

	showHeader();

	cout << "Γιατρός: " << doctor.getName() << endl;
	if (ds.size() == 0) cout << "\tΔεν βρέθηκαν ραντεβού." << endl;
	else {
		map<string, vector<DailySchedule::timeSlot>> appMap;

		for (int j = 0; j < ds.size(); j++) {
			appMap[ds[j].date].push_back(ds[j]);
		}
		for (map<string, vector<DailySchedule::timeSlot>>::iterator it = appMap.begin(); it != appMap.end(); ++it) {
			cout << "\t" << it->first << endl;
			for (int k = 0; k < it->second.size(); k++) {
				cout << "\t\t" << it->second.at(k).time << ": ";
				for (int l = 0; l < patients->size(); l++) {
					if (*patients->at(l) == it->second.at(k).appointment.getPatientId()) cout << patients->at(l)->getName();
				}
				cout << endl;
			}
		}
	}	
	system("pause");
}

void Scheduler::showDoctorAppointments() {
	int selection;
	showHeader();

	for (int i = 0; i < doctors->size(); i++) {
		cout << i + 1 << ". " << doctors->at(i)->getName() << " (" << doctors->at(i)->getSpecialty() << ")" << endl;
	}

	cout << "Επιλέξτε τον αριθμό Ιατρού: ";
	cin >> selection;

	while (selection < 1 || selection >> doctors->size()) {
		cout << "Παρακαλώ εισάγετε έναν σωστό αριθμό Ιατρού: ";
		cin >> selection;
	}

	printDoctorAppointments(*doctors->at(selection - 1));
}

void Scheduler::addDoctor() {
	cin.clear();
	cin.ignore();

	showHeader("Προσθήκη Ιατρού");
	array<string, 14> possibleSpecialties = {
		"AGGEIOLOGOS",
		"AKTINOLOGOS",
		"ANDROLOGOS",
		"GASTRENTEROLOGOS",
		"GUNAIKOLOGOS",
		"DERMATOLOGOS",
		"KARDIOLOGOS",
		"NEFROLOGOS",
		"ODONTIATROS",
		"OUROLOGOS",
		"PAIDIATROS",
		"OFTHALMIATROS",
		"PSUXOLOGOS",
		"PATHOLOGOS"
	};
	string name, code, specialty;
	int age;

	cout << "Όνομα γιατρού: ";
	getline(cin, name);

	cout << "Ειδικότητα γιατρού: " << endl;
	cout << "Υποστηριζόμενες ειδικότητες: ";
	for (int i = 0; i < possibleSpecialties.size(); i++) {
		cout << possibleSpecialties[i];
		if (i != possibleSpecialties.size() - 1) cout << ",";
		else cout << endl;
	}
	cout << "Ειδικότητα: ";
	getline(cin, specialty);
	while (find(begin(possibleSpecialties), end(possibleSpecialties), specialty) == end(possibleSpecialties)) {
		cout << "Παρακαλώ εισάγετε μια υποστηριζόμενη ειδικότητα γιατρού: ";
		getline(cin, specialty);
	}

	cout << "Ηλικία Ιατρού: ";
	cin >> age;

	showHeader("Προσθήκη Ιατρού");
	doctors->push_back(new Doctor(genCode(4), name, specialty, age));
	cout << "Επιτυχής καταχώρηση. " << endl;

	system("pause");
}

void Scheduler::scheduleAllAppointments() {
	srand(time(NULL));
	int action = 0;
	do {
		showHeader();
		cout << "Επιλέξτε ενέργεια: " << endl << endl;
		cout << "1. Εμφάνιση όλων των ραντεβού" << endl;
		cout << "2. Νέο ραντεβού" << endl;
		cout << "3. Προσθήκη Ιατρού" << endl;
		cout << "4. Εμφάνιση όλων των ραντεβού ενός γιατρού" << endl;
		cout << "5. Αποθήκευση και έξοδος" << endl << endl;

		cin >> action;

		switch (action) {
		case 1:
			printAllAppointments();
			break;
		case 2:
			scheduleOneAppointment();
			break;
		case 3:
			addDoctor();
			break;
		case 4:
			showDoctorAppointments();
			break;
		}

	} while (action != 5);
}

void Scheduler::showHeader() {
	system("CLS");
	cout << "---------------------------------" << endl << endl;
	cout << "Doctor Appointment Scheduler" << endl << endl;
	cout << "---------------------------------" << endl << endl;
}

void Scheduler::showHeader(string heading) {
	system("CLS");
	cout << "---------------------------------" << endl << endl;
	cout << "Doctor Appointment Scheduler" << endl << endl;
	cout << "---------------------------------" << endl << endl;

	cout << heading << endl << endl;
}