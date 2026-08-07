#include <iostream>
#include "Dashboard.h"

using namespace std;

void Dashboard::display()
{
    cout << "\n==================================" << endl;
    cout << "          Vault Dashboard         " << endl;
    cout << "==================================" << endl;

    cout << "1. Add Password" << endl;
    cout << "2. View Passwords" << endl;
    cout << "3. Search Password" << endl;
    cout << "4. Edit Password" << endl;
    cout << "5. Delete Password" << endl;
    cout << "6. Logout" << endl;
}

int Dashboard::getChoice()
{
    int choice;

    cout << "\nEnter your choice: ";
    cin >> choice;

    return choice;
}