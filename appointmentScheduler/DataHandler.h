#pragma once
#include <vector>
#include <fstream>
#include <json.h>
#include <Doctor.h>
#include <Patient.h>

using namespace std;
using json = nlohmann::json;


class DataHandler {
public:
	DataHandler();
	DataHandler(vector<Doctor*> *doctors, vector<Patient*> *patients);
};

