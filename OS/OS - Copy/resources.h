#ifndef RESOURCES_H
#define RESOURCES_H
#include <string>
#include "patient.h"

struct Resources
{
    int total[NRES];
    int freeq[NRES];
};

void clearResources(Resources &r);
void setResource(Resources &r, int index, int qty);
bool canAllocate(Resources &r, Patient &p);
void allocate(Resources &r, Patient &p);
void release(Resources &r, Patient &p);
void showResources(Resources &r);
std::string freeText(Resources &r);

#endif
