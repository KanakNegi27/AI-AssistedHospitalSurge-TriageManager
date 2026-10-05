#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <vector>
#include "patient.h"
#include "hospital.h"
using namespace std;

void runEmergency(vector<Hospital> &all, int cur);
int expectedStart(vector<Hospital> &all, int cur, Patient newPatient);

#endif
