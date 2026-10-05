#include <iostream>
#include "staffmenu.h"
#include "scheduling.h"
#include "emergency.h"

using namespace std;


void staffMenu(vector<Hospital> &hospitals, int cur)
{
    int choice;
    do
    {
        cout << "\nStaff Menu:\n";
        cout << "1. Register Emergency Patient\n";
        cout << "2. Show Patients\n"; 
        cout << "3. Show Resources\n";
        cout << "4. Change Resources\n";
        cout << "5. Emergency Scheduling\n";
        cout << "6. FCFS\n";
        cout << "7. SJF\n";
        cout << "8. Priority\n";
        cout << "9. Round Robin\n";
        cout << "10. Show All Hospitals\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        if(choice == 1)
        {
            registerEmergency(
                hospitals[cur].patients,
                hospitals[cur].id
            );
        }
        else if(choice == 2)
        {
            showPatients(hospitals[cur].patients);
        }
        else if(choice == 3)
        {
            cout << "\nResources:\n";
            showResources(hospitals[cur].res);
        }
        else if(choice == 4)
        {
            int quantity;

            for(int i = 0; i < NRES; i++)
            {
                cout << "Enter "
                     << resourceNames[i]
                     << ": ";

                cin >> quantity;

                setResource(
                    hospitals[cur].res,
                    i,
                    quantity
                );
            }
        }


        else if(choice == 5)
        {
            if(hospitals[cur].patients.size() == 0)
            {
                cout << "No patients.\n";
            }
            else
            {
                runEmergency(hospitals, cur);
            }
        }


        else if(choice == 6)
        {
            if(hospitals[cur].patients.size() == 0)
                cout << "No patients.\n";
            else
                runNonPreemptive(
                    hospitals[cur].patients,
                    MODE_FCFS,
                    "FCFS"
                );
        }


        else if(choice == 7)
        {
            if(hospitals[cur].patients.size() == 0)
                cout << "No patients.\n";
            else
                runNonPreemptive(
                    hospitals[cur].patients,
                    MODE_SJF,
                    "SJF"
                );
        }


        else if(choice == 8)
        {
            if(hospitals[cur].patients.size() == 0)
                cout << "No patients.\n";
            else
                runNonPreemptive(
                    hospitals[cur].patients,
                    MODE_PRIORITY,
                    "Priority"
                );
        }


        else if(choice == 9)
        {
            if(hospitals[cur].patients.size() == 0)
                cout << "No patients.\n";
            else
                runRoundRobin(hospitals[cur].patients);
        }


        else if(choice == 10)
        {
            showHospitals(hospitals);
        }


        else if(choice == 0)
        {
            cout << "Logged out.\n";
        }


        else
        {
            cout << "Wrong choice.\n";
        }

    } while(choice != 0);
}