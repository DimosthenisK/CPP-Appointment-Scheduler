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
	
}

Appointment* Scheduler::scheduleOneAppointment() {
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
	cout << put_time(&t, "%d-%m-%Y") << endl;
	
	showHeader("Νέο Ραντεβού - Επιλογή ώρας");
	cout << "Εισάγετε μια από τις παρακάτω διαθέσιμες ώρες: " << endl;

	for (int i = 0; i < possibleTimes.size(); i++) {
		//doctor->getSchedule();
		cout << possibleTimes.at(i) << endl;
	}

	return new Appointment();
}

void Scheduler::scheduleAllAppointments() {
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
		case 2:
			scheduleOneAppointment();
			break;
		case 3:
		case 4:
			break;
		}

	} while (action != 5);
}

void Scheduler::showHeader() {
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