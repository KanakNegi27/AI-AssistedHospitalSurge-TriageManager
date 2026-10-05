#ifndef HOSPITAL_H
#define HOSPITAL_H
#include <string>
#include <vector>
#include "patient.h"
#include "resources.h"
using namespace std;

struct Hospital
{
    int id;
    string name;
    string password;
    Resources res;
    vector<Patient> patients;
};

void createDefaultHospitals(vector<Hospital> &h);
int selectHospital(vector<Hospital> &h);
void showHospitals(vector<Hospital> &h);
int findOtherHospital(vector<Hospital> &h, int current, Patient &p);

#endif
