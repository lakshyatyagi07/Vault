#include <iostream>
#include <string>

#include "SignupWindow.h"

using namespace std;

User SignupWindow::display()
{
    string name;
    string email;
    string masterPassword;
    string confirmPassword;

    cout << "\n========== SIGN UP ==========\n\n";

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Master Password: ";
    getline(cin, masterPassword);

    cout << "Confirm Master Password: ";
    getline(cin, confirmPassword);

    while (masterPassword != confirmPassword)
    {
        cout << "\nPasswords do not match.\n";
        cout << "Confirm Master Password Again: ";
        getline(cin, confirmPassword);
    }

    cout << "\nAccount Created Successfully!\n";

    User user(name, email, masterPassword);

    return user;
}