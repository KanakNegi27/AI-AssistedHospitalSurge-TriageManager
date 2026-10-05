#include <iostream>
#include "patientmenu.h"
#include "emergency.h"

using namespace std;


void bookAppointment(vector<Hospital> &hospitals)
{
    Patient p;

    cout << "\nBook Appointment:\n";

    cout << "Name: ";
    cin >> p.name;

    cout << "Age: ";
    cin >> p.age;

    cout << "After how many minutes will you reach? ";
    cin >> p.arrival;

    cout << "Treatment time needed: ";
    cin >> p.burst;


    // Patient details
    p.type = APPOINTMENT;
    p.severity = 5;

    p.st = 0;
    p.ct = 0;
    p.tat = 0;
    p.wt = 0;


    // Appointment needs only one doctor
    for(int i = 0; i < NRES; i++)
    {
        p.need[i] = 0;
    }

    p.need[DOCTOR] = 1;


    // Show available hospitals
    cout << "\nAvailable Hospitals:\n";

    for(int i = 0; i < hospitals.size(); i++)
    {
        int start = expectedStart(hospitals, i, p);

        cout << "\n";
        cout << hospitals[i].id << ". "
             << hospitals[i].name << "\n";

        if(start == -1)
        {
            cout << "No doctor available\n";
        }
        else
        {
            cout << "Treatment starts at: "
                 << start << " minutes\n";

            cout << "Waiting time: "
                 << start - p.arrival << " minutes\n";
        }

        cout << "Patients: "
             << hospitals[i].patients.size() << "\n";
    }


    // Choose hospital
    int choice;

    do
    {
        cout << "\nChoose hospital (0 to cancel): ";
        cin >> choice;

    } while(choice < 0 || choice > hospitals.size());


    if(choice == 0)
    {
        cout << "Booking cancelled.\n";
        return;
    }


    // Convert choice into array index
    int i = choice - 1;


    // Give patient an ID
    p.id = hospitals[i].patients.size() + 1;

    p.hospital = hospitals[i].id;


    // Add patient to hospital
    hospitals[i].patients.push_back(p);


    cout << "\nAppointment booked at "
         << hospitals[i].name << ".\n";

    cout << "Your token is P"
         << p.id << "\n";
}


void patientMenu(vector<Hospital> &hospitals)
{
    int choice;

    do
    {
        cout << "\nPatient Menu:\n";

        cout << "1. Book Appointment\n";
        cout << "0. Back\n";

        cout << "Enter choice: ";
        cin >> choice;


        if(choice == 1)
        {
            bookAppointment(hospitals);
        }
        else if(choice == 0)
        {
            cout << "Going back...\n";
        }
        else
        {
            cout << "Wrong choice.\n";
        }

    } while(choice != 0);
}