#include <iostream>
#include "resources.h"
using namespace std;

void clearResources(Resources &r)
{
    for(int i=0;i<NRES;i++){
        r.total[i]=r.freeq[i]=0;
    }
}

void setResource(Resources &r, int index, int qty)
{
    r.total[index] = qty;
    r.freeq[index] = qty;
}

bool canAllocate(Resources &r, Patient &p)
{
    for (int i = 0; i < NRES; i++)
        if (p.need[i] > r.freeq[i])
            return false;
    return true;
}

void allocate(Resources &r, Patient &p)
{
    for (int i=0;i<NRES;i++)
        r.freeq[i]-=p.need[i];
}

void release(Resources &r, Patient &p)
{
    for (int i=0;i<NRES;i++){
        r.freeq[i]+=p.need[i];
    }
}

void showResources(Resources &r)
{
    for (int i=0;i<NRES;i++)
        cout << "  " << resourceNames[i] << ": " << r.freeq[i] << "/" << r.total[i] << "\n";
}

string freeText(Resources &r)
{
    string text="";
    for (int i=0;i<NRES;i++)
    {
        if (i>0)
            text+=', ';
        text = text + resourceNames[i] + " " + to_string(r.freeq[i]);
    }
    return text;
}
