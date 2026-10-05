#include <iostream>
#include "login.h"
using namespace std;

int staffLogin(vector<Hospital> &h)
{
    int cur = selectHospital(h);
    string pw;

    for (int tries = 1; tries <= 3; tries++)
    {
        cout << "Staff password: ";
        cin >> pw;
        if (pw == h[cur].password)
        {
            cout << "Login successful. Welcome, " << h[cur].name << " staff.\n";
            return cur;
        }
        cout << "Wrong password. Tries left: " << 3 - tries << "\n";
    }
    return -1;
}
