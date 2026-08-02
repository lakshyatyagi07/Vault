#include <iostream>
#include <string>

#include "HomeWindow.h"
#include "SignupWindow.h"
#include "Authentication.h"

using namespace std;

int main()
{
    HomeWindow home;
    SignupWindow signup;
    Authentication auth;

    while (true)
    {
        home.display();

        int choice = home.getChoice();

        switch (choice)
        {
        case 1:
        {
            string email;
            string masterPassword;

            cout << "\n========== LOGIN ==========\n\n";

            cin.ignore();

            cout << "Enter Email: ";
            getline(cin, email);

            cout << "Enter Master Password: ";
            getline(cin, masterPassword);

            if (auth.login(email, masterPassword))
            {
                cout << "\n=================================\n";
                cout << "Welcome " << email << "!\n";
                cout << "=================================\n";
            }
            else
            {
                cout << "\nInvalid Email or Password.\n";
            }

            break;
        }

        case 2:
        {
            User user = signup.display();

            auth.registerUser(user);

            break;
        }

        case 3:
        {
            cout << "\nThank you for using Vault!\n";
            return 0;
        }

        default:
        {
            cout << "\nInvalid Choice!\n";
        }
        }
    }

    return 0;
}