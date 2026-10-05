#include<iostream>
#include "report.h"
using namespace std;

void printReport(string title,vector<Patient>&p,vector<Slot>&gantt){
    float totalWT=0;
    float totalTAT=0;
    cout<<title<<"\n";
    cout<<"Gantt Chart:\n";
    for(int i=0;i<gantt.size();i++){
        cout<<"P"<<gantt[i].id
             <<"("<<gantt[i].from
             <<"-"<<gantt[i].to<<")";
    }
    cout<<"|\n";
    cout<<"\nPatient Details:\n";
    for(int i=0;i<p.size();i++)
    {
        p[i].tat=p[i].ct-p[i].arrival;
        p[i].wt=p[i].tat-p[i].burst;

        totalTAT+=p[i].tat;
        totalWT+=p[i].wt;

        cout << "\nPatient P" << p[i].id << endl;
        cout << "Name: " << p[i].name << endl;
        cout << "Severity: " << severityName(p[i].severity) << endl;
        cout << "Arrival Time: " << p[i].arrival << endl;
        cout << "Treatment Time: " << p[i].burst << endl;
        cout << "Completion Time: " << p[i].ct << endl;
        cout << "Turnaround Time: " << p[i].tat << endl;
        cout << "Waiting Time: " << p[i].wt << endl;
    }

    cout << "\nAverage Waiting Time: "
         << totalWT / p.size() << " minutes\n";

    cout << "Average Turnaround Time: "
         << totalTAT / p.size() << " minutes\n";
}