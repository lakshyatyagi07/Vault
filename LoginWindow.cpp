#include <iostream>
#include <string>

#include "LoginWindow.h"

using namespace std;

string LoginWindow::getEmail()
{
    string email;

    cin.ignore();

    cout << "\n========== Login ==========\n\n";
    cout << "Enter Email: ";
    getline(cin, email);

    return email;
}

string LoginWindow::getMasterPassword()
{
    string password;

    cout << "Enter Master Password: ";
    getline(cin, password);

    return password;
}