#include <iostream>
#include <iomanip>
#include "emergency.h"
#include "report.h"

using namespace std;

bool urgent(Patient &a, Patient &b)
{
    if(a.severity < b.severity)
        return true;

    if(a.severity == b.severity)
    {
        if(a.arrival < b.arrival)
            return true;
    }

    return false;
}

bool canStart(Resources &res, Patient &p)
{
    if(canAllocate(res, p) == false)
        return false;

    if(p.type == APPOINTMENT)
    {
        int reserve = 0;

        if(res.total[DOCTOR] > 1)
            reserve = 1;

        if(res.freeq[DOCTOR] <= reserve)
            return false;
    }

    return true;
}


bool simulate(vector<Patient> &p, Resources res,
              vector<Hospital> &all, int cur,
              bool show, vector<Slot> &gantt)
{
    int n = p.size();
    int time = 0;
    int finished = 0;

    vector<int> started(n, 0);
    vector<int> ended(n, 0);
    vector<int> told(n, 0);

    while(finished < n)
    {
        for(int i = 0; i < n; i++)
        {
            if(started[i] == 1 &&
               ended[i] == 0 &&
               p[i].ct == time)
            {
                ended[i] = 1;
                finished+=1;

                release(res, p[i]);

                if(show)
                {
                    cout << "Time " << time
                         << ": P" << p[i].id
                         << " finished.\n";
                }
            }
        }
        int selected = -1;

        for(int i = 0; i < n; i++)
        {
            if(started[i] == 0 &&
               p[i].arrival <= time &&
               canStart(res, p[i]))
            {
                if(selected == -1)
                {
                    selected = i;
                }
                else if(urgent(p[i], p[selected]))
                {
                    selected = i;
                }
            }
        }
        if(selected != -1)
        {
            started[selected] = 1;

            p[selected].st = time;
            p[selected].ct = time + p[selected].burst;

            allocate(res, p[selected]);

            Slot s;
            s.id = p[selected].id;
            s.from = p[selected].st;
            s.to = p[selected].ct;

            gantt.push_back(s);

            if(show)
            {
                cout << "Time " << time
                     << ": P" << p[selected].id
                     << " started.\n";
            }
        }
        for(int i = 0; i < n; i++)
        {
            if(started[i] == 0 &&
               p[i].arrival <= time &&
               told[i] == 0)
            {
                told[i] = 1;

                if(show)
                {
                    cout << "Time " << time
                         << ": P" << p[i].id
                         << " is waiting.\n";

                    if(p[i].type == EMERGENCY)
                    {
                        int other = findOtherHospital(
                            all, cur, p[i]);

                        if(other != -1)
                        {
                            cout << "Patient can go to "
                                 << all[other].name << ".\n";
                        }
                    }
                }
            }
        }


        time++;

        if(time > 1000)
            return false;
    }

    return true;
}
void runEmergency(vector<Hospital> &all, int cur)
{
    vector<Patient> p = all[cur].patients;
    vector<Slot> gantt;

    cout << "\nSCHEDULING - "
         << all[cur].name << "\n";

    cout << "Resources:\n";
    showResources(all[cur].res);

    bool result = simulate(
        p, all[cur].res, all, cur, true, gantt);

    if(result == false)
    {
        cout << "Scheduling stopped.\n";
        return;
    }

    printReport("RESULT", p, gantt);
}
int expectedStart(vector<Hospital> &all,
                  int cur, Patient newPatient)
{
    vector<Patient> p = all[cur].patients;
    vector<Slot> gantt;

    newPatient.id = p.size() + 1;

    p.push_back(newPatient);

    bool result = simulate(
        p, all[cur].res, all, cur, false, gantt);

    if(result == false)
        return -1;

    return p[p.size() - 1].st;
}
