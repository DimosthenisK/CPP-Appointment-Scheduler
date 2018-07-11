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
		cout << "�������: " << doctors->at(i)->getName() << endl;
		vector<DailySchedule::timeSlot> ds = doctors->at(i)->getSchedule(true).getAppointments();
		if (ds.size() == 0) cout << "\t��� �������� ��������." << endl;
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
	showHeader("��� ��������");

	cout << "����� ������������������ ����� ��� ��������? (Y/Yes/yes/N/No/no) ";
	cin >> buffer;
	while (
		buffer != "Y" && buffer != "Yes" && buffer != "yes" &&
		buffer != "N" && buffer != "No"  && buffer != "no") {
		cout << "����� �������. �������� �������� ���� ������ Y/Yes/yes ��� ���, � N/No/no ��� ���.";
		cout << "����� ������������������ ����� ��� ��������? (Y/Yes/yes/N/No/no) ";
		cin >> buffer;
	}

	showHeader("��� �������� - ������� ������");

	if (buffer == "Y" || buffer == "Yes" || buffer == "yes") {
		int selection;

		for (int i = 0; i < patients->size(); i++) {
			cout << i + 1 << ". " << patients->at(i)->getName() << endl;
		}

		cout << "�������� ��� ������ ������ ���: ";
		cin >> selection;

		while (selection < 1 || selection >> patients->size()) {
			cout << "�������� �������� ���� ����� ������ ������: ";
			cin >> selection;
		}

		patient = patients->at(selection - 1);
	}
	else {
		string name;
		string code = genCode(4);
		int age;
		cout << "�������� �������� ������: ";
		cin.clear();
		cin.ignore();
		getline(cin, name);
		cout << "�������� �������: ";
		cin >> age;

		patient = new Patient(code, name, age);
		patients->push_back(patient);
	}

	showHeader("��� �������� - ������� ������");

	int selection;

	for (int i = 0; i < doctors->size(); i++) {
		cout << i + 1 << ". " << doctors->at(i)->getName() << " (" << doctors->at(i)->getSpecialty() << ")" << endl;
	}

	cout << "�������� ��� ������ ������ ���: ";
	cin >> selection;

	while (selection < 1 || selection >> doctors->size()) {
		cout << "�������� �������� ���� ����� ������ ������: ";
		cin >> selection;
	}

	doctor = doctors->at(selection - 1);

	showHeader("��� �������� - ������� �����������");
	cout << "�������� ��� ��������� ���������� ��� �������� ��� ���� ����� DD-MM-����: " ;
	tm t = {};
	cin >> get_time(&t, "%d-%m-%Y");
	while (cin.fail()) {
		cin.clear();
		cin.ignore();

		cout << "�������� �������� ��� ������ ���������� ��� �� �������� ��� ���� ����� DD-MM-����: " ;
		cin >> get_time(&t, "%d-%m-%Y");
	}
	stringstream appointmentDate;
	appointmentDate << put_time(&t, "%d-%m-%Y") << endl;

	cin.clear();
	cin.ignore();
	
	showHeader("��� �������� - ������� ����");
	cout << "�������� ��� ��� ��� �������� ���������� ����: " << endl;
	
	DailySchedule& ds = doctor->getSchedule(true);

	for (int i = 0; i < possibleTimes.size(); i++) {
		if (!ds.isAvailableOnDateTime(appointmentDate.str(), possibleTimes.at(i))) continue;
		cout << possibleTimes.at(i) << endl;
	}

	string wantedTime;
	cout << "��������� ���: ";
	getline(cin, wantedTime);
	while (find(begin(possibleTimes), end(possibleTimes), wantedTime) == end(possibleTimes) || !ds.isAvailableOnDateTime(appointmentDate.str(), wantedTime)) {
		cout << "�������� �������� ��� ����� ��� ��� �� �������� ���: ";
		getline(cin, wantedTime);
	}

	ds.createAppointment(appointmentDate.str(), wantedTime, doctor, patient);
	patient->getSchedule().createAppointment(appointmentDate.str(), wantedTime, doctor, patient);

	showHeader("��� ��������");
	cout << "�������� ����������!" << endl;
	system("pause");
}

void Scheduler::printDoctorAppointments(Doctor& doctor) {
	vector<DailySchedule::timeSlot> ds = doctor.getSchedule().getAppointments();

	showHeader();

	cout << "�������: " << doctor.getName() << endl;
	if (ds.size() == 0) cout << "\t��� �������� ��������." << endl;
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

	cout << "�������� ��� ������ ������: ";
	cin >> selection;

	while (selection < 1 || selection >> doctors->size()) {
		cout << "�������� �������� ���� ����� ������ ������: ";
		cin >> selection;
	}

	printDoctorAppointments(*doctors->at(selection - 1));
}

void Scheduler::addDoctor() {
	cin.clear();
	cin.ignore();

	showHeader("�������� ������");
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

	cout << "����� �������: ";
	getline(cin, name);

	cout << "���������� �������: " << endl;
	cout << "��������������� �����������: ";
	for (int i = 0; i < possibleSpecialties.size(); i++) {
		cout << possibleSpecialties[i];
		if (i != possibleSpecialties.size() - 1) cout << ",";
		else cout << endl;
	}
	cout << "����������: ";
	getline(cin, specialty);
	while (find(begin(possibleSpecialties), end(possibleSpecialties), specialty) == end(possibleSpecialties)) {
		cout << "�������� �������� ��� �������������� ���������� �������: ";
		getline(cin, specialty);
	}

	cout << "������ ������: ";
	cin >> age;

	showHeader("�������� ������");
	doctors->push_back(new Doctor(genCode(4), name, specialty, age));
	cout << "�������� ����������. " << endl;

	system("pause");
}

void Scheduler::scheduleAllAppointments() {
	srand(time(NULL));
	int action = 0;
	do {
		showHeader();
		cout << "�������� ��������: " << endl << endl;
		cout << "1. �������� ���� ��� ��������" << endl;
		cout << "2. ��� ��������" << endl;
		cout << "3. �������� ������" << endl;
		cout << "4. �������� ���� ��� �������� ���� �������" << endl;
		cout << "5. ���������� ��� ������" << endl << endl;

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