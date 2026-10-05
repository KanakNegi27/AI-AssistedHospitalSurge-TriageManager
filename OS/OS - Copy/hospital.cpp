#include <iostream>
#include "hospital.h"
using namespace std;

void createDefaultHospitals(vector<Hospital> &h)
{
    int a[NRES] = {5, 15, 6, 5, 2, 6};
    int b[NRES] = {6, 11, 5, 8, 3, 5};
    int c[NRES] = {2, 5, 2, 5, 1, 4};
    string names[3] = {"City Hospital", "Central Hospital", "GreenValley Hospital"};
    int *data[3] = {a, b, c};

    for(int i=0;i<3;i++)
    {
        Hospital x;
        x.id=i+1;
        x.name=names[i];
        x.password="staff123";
        clearResources(x.res);
        for(int j=0;j<NRES;j++){
            setResource(x.res, j, data[i][j]);
        }
        h.push_back(x);
    }
}

int selectHospital(vector<Hospital>&h)
{
    int choice;
    cout << "\nHospitals:\n";
    for(int i=0;i<h.size();i++)
        {
            cout<<h[i].id<<":"<<h[i].name<<"\n";
        }
    do
    {
        cout<<"Enter hospital number:";
        cin>>choice;
    }while(choice<1 || choice>h.size());
    return choice - 1;
}

void showHospitals(vector<Hospital> &h)
{
    cout << "\nALL HOSPITALS\n";
    for(int i=0;i<h.size();i++)
    {
        cout<<h[i].id<<". "<< h[i].name
             << "   (patients registered: " << h[i].patients.size() << ")\n";
        showResources(h[i].res);
    }
}

int findOtherHospital(vector<Hospital> &h, int current, Patient &p)
{
    for(int i=0;i<h.size();i++)
        if(i!=current && canAllocate(h[i].res,p))
            return i;
    return -1;
}
