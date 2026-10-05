#ifndef SCHEDULING_H
#define SCHEDULING_H
#include<string>
#include<vector>
#include "patient.h"
using namespace std;

const int MODE_FCFS = 0;
const int MODE_SJF = 1;
const int MODE_PRIORITY = 2;

void runNonPreemptive(vector<Patient> p, int mode, string title);
void runRoundRobin(vector<Patient> p);

#endif
