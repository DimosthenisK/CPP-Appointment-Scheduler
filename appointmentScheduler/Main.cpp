#include <iostream>
#include <string>
#include <vector>
#include <json.h>
#include "Patient.h"
#include "Doctor.h"
#include "DataHandler.h"
#include "Scheduler.h"


using namespace std;
using json = nlohmann::json;

int main() {
	vector<Doctor*> doctors;
	vector<Patient*> patients;
	DataHandler dh = DataHandler(&doctors, &patients);
	
	if (doctors.empty()) {
		cout << "No doctors found" << endl;
	}
	if (patients.empty()) {
		cout << "No patients found" << endl;
	}

	doctors.push_back(new Doctor("23", "Mparmpamhtsos", "OFTHALMIATROS", 24));
	patients.push_back(new Patient("23", "Mparmpagiannhs", 24));

	dh.save(&doctors, &patients);

	system("PAUSE");
	return 0;
}

/*int main() {
	json j;

	time_t today = time(0);
	int dayCounter = 1;
	do {
		time_t desirable = today + 60 * 60 * 24 * dayCounter;
		struct tm desirableTM;
		localtime_s(&desirableTM, &desirable);

		stringstream cDate, cTime;
		int hour = 8;
		string minutes = "00";

		cDate << desirableTM.tm_year + 1900 << "/" << desirableTM.tm_mon + 1 << "/" << desirableTM.tm_mday;
		cTime << hour << ":" << minutes;

		while (cTime.str() != "18:00") {
			j[cDate.str()][cTime.str()] = { {"available", true} };

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

		cDate.str(string());
		cDate.clear();
		dayCounter++;
	} while (dayCounter <= 30);

	cout << j.dump(2);

	json::iterator index = j.find("2018/6/8");
	if (index != j.end()) {
		cout << index.value().find("16:00").value().at("available").get<bool>();
	}

	fstream fs;

	fs.open("C:/Users/demos/Desktop/doctors.json", fstream::out);
	fs << j;
	fs.close();

	system("PAUSE");
	return 0;
}*/