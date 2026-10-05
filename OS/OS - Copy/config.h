#ifndef CONFIG_H
#define CONFIG_H
#include <string>

const int NRES = 6;
const int DOCTOR = 5;
const std::string resourceNames[NRES] = {
    "ICU Bed", "General Bed", "Ventilator", "Oxygen Cylinder", "Operation Theatre", "Doctor"};

#endif
