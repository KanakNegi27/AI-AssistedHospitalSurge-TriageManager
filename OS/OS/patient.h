#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>
#include "config.h"

/* A patient is a "process" of our OS. There are two kinds:
   EMERGENCY   - registered by hospital staff, severity 1 to 4
   APPOINTMENT - booked by a normal patient, severity is always 5 (lowest priority)
   Smaller severity number = served first. */
const int EMERGENCY = 1;
const int APPOINTMENT = 2;

struct Patient
{
    int id;
    int type;           // EMERGENCY or APPOINTMENT
    std::string name;
    int age;
    int severity;       // 1 = Critical, 2 = High, 3 = Medium, 4 = Low, 5 = Normal (appointment)
    int arrival;        // AT: minute when the patient reaches the hospital
    int burst;          // BT: treatment / consultation time in minutes
    int need[NRES];     // how many of each resource the patient needs
    int hospital;       // id of the hospital
    int st, ct, tat, wt;
};

struct Slot             // one block of the Gantt chart
{
    int id, from, to;
};

std::string severityName(int s);
std::string typeName(int t);
std::string needsText(Patient &p);
void sortByArrival(std::vector<Patient> &p);
void registerEmergency(std::vector<Patient> &list, int hospitalId);   // STAFF only
void showPatients(std::vector<Patient> &list);

#endif
