#include <iostream>
#include "patient.h"
#include<algorithm>
using namespace std;

string severityName(int s)
{
    if (s == 1) return "Critical";
    if (s == 2) return "High";
    if (s == 3) return "Medium";
    if (s == 4) return "Low";
    return "Normal";
}

string typeName(int t)
{
    if (t == EMERGENCY) return "Emergency";
    return "Appointment";
}

string needsText(Patient &p)
{
    string text = "";
    for (int i=0;i<NRES;i++)
        if (p.need[i] > 0)
        {
            if (text.length()>0)
                text=text+", ";
            text+=resourceNames[i] + " x" + to_string(p.need[i]);
        }
    if (text.length()==0)
        return "None";
    return text;
}
bool compareArrival(Patient a,Patient b){
    return a.arrival<b.arrival;
}
void sortByArrival(vector<Patient> &p)
{
    sort(p.begin(),p.end(),compareArrival);
}

void registerEmergency(vector<Patient>&list, int hospitalId)
{
    Patient p;
    p.id=list.size()+1;
    p.type=EMERGENCY;
    p.hospital=hospitalId;
    p.st=p.ct=p.tat=p.wt=0;

    cout << "\nRegister Emergency Patient:" << p.id << "\n";
    cout << "Name: ";
    cin >> p.name;
    cout << "Age: ";
    cin >> p.age;
    do{
        cout<<"Severity(1=Critical 2=High 3=Medium 4=Low): ";
        cin>>p.severity;
    }while(p.severity<1 || p.severity>4);
    cout << "Arrival time: ";
    cin >> p.arrival;
    cout << "Treatment time: ";
    cin >> p.burst;

    cout << "How many of each resource does the patient need?\n";
    for (int i=0;i<NRES;i++)
    {
        cout << "" << resourceNames[i] << "(0 if none): ";
        cin >> p.need[i];
    }
    p.need[DOCTOR] = 1;
    list.push_back(p);
    cout << "Emergency patient P" << p.id << " registered.\n";
}


void showPatients(vector<Patient>&list)
{
    if(list.empty())
    {
        cout<<"No patients registered yet.\n";
        return;
    }
    cout << "\nPatient List:\n";

    for (int i=0;i<list.size();i++)
    {
        cout <<"\nPatient P" << list[i].id << endl;
        cout <<"Name: " << list[i].name << endl;
        cout <<"Age: " << list[i].age << endl;
        cout <<"Type: " << typeName(list[i].type) << endl;
        cout << "Severity: " << severityName(list[i].severity) << endl;
        cout << "Arrival Time: " << list[i].arrival << " minutes" << endl;
        cout << "Treatment Time: " << list[i].burst << " minutes" << endl;
        cout << "Resources Needed: " << needsText(list[i]) << endl;
    }
}
