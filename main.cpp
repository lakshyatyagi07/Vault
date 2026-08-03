#include <iostream>

#include "HomeWindow.h"
#include "SignupWindow.h"
#include "LoginWindow.h"
#include "Authentication.h"

using namespace std;

int main()
{
    HomeWindow home;
    SignupWindow signup;
    LoginWindow login;
    Authentication auth;

    int choice;

    do
    {
        home.display();
        choice = home.getChoice();

        switch (choice)
        {
        case 1:
        {
            if (!auth.hasUser())
            {
                cout << "\nNo account found. Please sign up first.\n\n";
                break;
            }

            string email = login.getEmail();
            string password = login.getMasterPassword();

            if (auth.login(email, password))
            {
                cout << "\n==================================\n";
                cout << "Welcome, " << auth.getUser().getName() << "!\n";
                cout << "==================================\n";
            }
            else
            {
                cout << "\nInvalid email or password.\n";
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
            cout << "\nThank you for using Vault.\n";
            break;
        }

        default:
            cout << "\nInvalid Choice.\n";
        }

    } while (choice != 3);

    return 0;
}