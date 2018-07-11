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
	cout << put_time(&t, "%d-%m-%Y") << endl;
	
	showHeader("��� �������� - ������� ����");
	cout << "�������� ��� ��� ��� �������� ���������� ����: " << endl;

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
		cout << "�������� ��������: " << endl << endl;
		cout << "1. �������� ���� ��� ��������" << endl;
		cout << "2. ��� ��������" << endl;
		cout << "3. �������� ������" << endl;
		cout << "4. �������� ���� ��� �������� ���� �������" << endl;
		cout << "5. ���������� ��� ������" << endl << endl;

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