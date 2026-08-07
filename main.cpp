#include <iostream>

#include "HomeWindow.h"
#include "SignupWindow.h"
#include "LoginWindow.h"
#include "Authentication.h"
#include "Dashboard.h"
#include "Vault.h"

using namespace std;

int main()
{
    HomeWindow home;
    SignupWindow signup;
    LoginWindow login;
    Authentication auth;
    Dashboard dashboard;
    Vault vault;

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
                cout << "\nNo account found. Please sign up first.\n";
                break;
            }

            string email = login.getEmail();
            string password = login.getMasterPassword();

            if (auth.login(email, password))
            {
                cout << "\nLogin Successful!\n";

                int dashboardChoice;

                do
                {
                    dashboard.display();
                    dashboardChoice = dashboard.getChoice();

                    switch (dashboardChoice)
                    {
                    case 1:
                        cout << "\nAdd Password (Coming Next)\n";
                        break;

                    case 2:
                        vault.viewPasswords();
                        break;

                    case 3:
                        cout << "\nSearch Password (Coming Next)\n";
                        break;

                    case 4:
                        cout << "\nEdit Password (Coming Next)\n";
                        break;

                    case 5:
                        cout << "\nDelete Password (Coming Next)\n";
                        break;

                    case 6:
                        cout << "\nLogged Out Successfully.\n";
                        break;

                    default:
                        cout << "\nInvalid Choice.\n";
                    }

                } while (dashboardChoice != 6);
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
            cout << "\nThank you for using Vault.\n";
            break;
        }

        default:
            cout << "\nInvalid Choice.\n";
        }

    } while (choice != 3);

    return 0;
}