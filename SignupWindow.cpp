#include <iostream>
#include <string>

#include "SignupWindow.h"

using namespace std;

User SignupWindow::display()
{
    string name;
    string email;
    string password;
    string confirmPassword;

    cin.ignore();

    cout << "\n========== Sign Up ==========\n\n";

    cout << "Enter your Name: ";
    getline(cin, name);

    cout << "Enter your Email: ";
    getline(cin, email);

    while (true)
    {
        cout << "Enter Master Password: ";
        getline(cin, password);

        cout << "Confirm Master Password: ";
        getline(cin, confirmPassword);

        if (password == confirmPassword)
        {
            break;
        }

        cout << "\nPasswords do not match. Try again.\n\n";
    }

    cout << "\nAccount created successfully!\n";

    return User(name, email, password);
}