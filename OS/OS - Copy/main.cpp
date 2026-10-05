#include <iostream>
#include <vector>
#include "hospital.h"
#include "login.h"
#include "patientmenu.h"
#include "staffmenu.h"

using namespace std;

int main()
{
    vector<Hospital> hospitals;

    int choice;
    int cur;

    // Create hospitals
    createDefaultHospitals(hospitals);

    do
    {
        cout << "\n";
        cout << "HOSPITAL RESOURCE SYSTEM\n";
        cout << "\n";

        cout << "1. Patient\n";
        cout << "2. Staff Login\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;


        if(choice == 1)
        {
            patientMenu(hospitals);
        }

        else if(choice == 2)
        {
            cur = staffLogin(hospitals);

            if(cur != -1)
            {
                staffMenu(hospitals, cur);
            }
            else
            {
                cout << "Login failed.\n";
            }
        }

        else if(choice == 0)
        {
            cout << "Goodbye.\n";
        }

        else
        {
            cout << "Wrong choice.\n";
        }

    } while(choice != 0);


    return 0;
}