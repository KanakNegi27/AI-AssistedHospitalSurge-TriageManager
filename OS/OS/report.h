#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include "patient.h"
using namespace std;

void printReport(string title, vector<Patient> &p,vector<Slot> &gantt);

#endif
