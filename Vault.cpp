#include <iostream>
#include <limits>

#include "Vault.h"

using namespace std;

void Vault::addPassword(const PasswordEntry& entry)
{
    passwords.push_back(entry);

    cout << "\nPassword added successfully.\n";
}

void Vault::addPasswordFromInput()
{
    string website;
    string username;
    string password;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n========== Add Password ==========\n";

    cout << "Website: ";
    getline(cin, website);

    cout << "Username: ";
    getline(cin, username);

    cout << "Password: ";
    getline(cin, password);

    PasswordEntry entry(website, username, password);

    passwords.push_back(entry);

    cout << "\nPassword saved successfully!\n";
}

void Vault::viewPasswords() const
{
    if (passwords.empty())
    {
        cout << "\nVault is empty.\n";
        return;
    }

    cout << "\n========== Saved Passwords ==========\n";

    for (const auto& entry : passwords)
    {
        cout << "Website : " << entry.getWebsite() << endl;
        cout << "Username: " << entry.getUsername() << endl;
        cout << "Password: " << entry.getPassword() << endl;
        cout << "-------------------------------------\n";
    }
}

void Vault::searchPassword(const string& website) const
{
    bool found = false;

    for (const auto& entry : passwords)
    {
        if (entry.getWebsite() == website)
        {
            cout << "\nWebsite : " << entry.getWebsite() << endl;
            cout << "Username: " << entry.getUsername() << endl;
            cout << "Password: " << entry.getPassword() << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo password found.\n";
    }
}

void Vault::deletePassword(const string& website)
{
    for (auto it = passwords.begin(); it != passwords.end(); ++it)
    {
        if (it->getWebsite() == website)
        {
            passwords.erase(it);

            cout << "\nPassword deleted successfully.\n";
            return;
        }
    }

    cout << "\nPassword not found.\n";
}

void Vault::editPassword(const string& website)
{
    for (auto& entry : passwords)
    {
        if (entry.getWebsite() == website)
        {
            string username;
            string password;

            cout << "Enter new username: ";
            getline(cin >> ws, username);

            cout << "Enter new password: ";
            getline(cin, password);

            entry.setUsername(username);
            entry.setPassword(password);

            cout << "\nPassword updated successfully.\n";
            return;
        }
    }

    cout << "\nPassword not found.\n";
}