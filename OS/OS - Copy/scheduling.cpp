#include <iostream>
#include "scheduling.h"
#include "report.h"
using namespace std;

bool comeFirst(Patient a,Patient b,int mode)
{
    if(mode==MODE_FCFS) return a.arrival < b.arrival;
    if (mode==MODE_SJF) return a.burst < b.burst;
    return a.severity < b.severity;
}

void runNonPreemptive(vector<Patient>p,int mode, string title)
{
    int n=p.size(),time=0,count=0,i,sel;
    vector<int>done(n, 0);
    vector<Slot>gantt;

    while (count < n)
    {
        sel=-1;
        for(i=0;i<n;i++)
            if(done[i]==0 && p[i].arrival<=time){
                if(sel==-1 || comeFirst(p[i], p[sel], mode))
                    sel = i;
    }
        if (sel == -1)
        {
            time++;
            continue;
        }
        Slot s = {p[sel].id, time, time + p[sel].burst};
        gantt.push_back(s);
        time +=p[sel].burst;
        p[sel].ct=time;
        done[sel]=1;
        count++;
    }
    printReport(title, p, gantt);
}

void runRoundRobin(vector<Patient> p)
{
    int n=p.size(),tq,time=0,count=0,i,worked;
    vector<int>rem(n);
    vector<Slot>gantt;

    cout << "Enter time quantum: ";
    cin >> tq;

    sortByArrival(p);
    for (i = 0; i < n; i++)
        rem[i]=p[i].burst;
    while (count < n)
    {
        worked=0;
        for(i=0;i<n;i++)
        {
            if(p[i].arrival<=time && rem[i]>0)
            {
                worked=1;
                int run=(rem[i] > tq) ? tq : rem[i];
                Slot s = {p[i].id, time, time + run};
                gantt.push_back(s);
                time = time + run;
                rem[i] = rem[i] - run;
                if (rem[i] == 0)
                {
                    p[i].ct = time;
                    count++;
                }
            }
        }
        if (worked == 0)
            time++;
    }
    printReport("Round Robin:", p, gantt);
}
