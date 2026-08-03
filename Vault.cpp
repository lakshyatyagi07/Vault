#include <iostream>

#include "Vault.h"

using namespace std;

void Vault::addPassword(const PasswordEntry& entry)
{
    passwords.push_back(entry);
}

void Vault::showAllPasswords() const
{
    if (passwords.empty())
    {
        cout << "\nNo passwords stored.\n";
        return;
    }

    cout << "\n========== STORED PASSWORDS ==========\n";

    for (int i = 0; i < passwords.size(); i++)
    {
        cout << "\nEntry " << i + 1 << endl;
        cout << "Website : " << passwords[i].getWebsite() << endl;
        cout << "Username: " << passwords[i].getUsername() << endl;
        cout << "Password: " << passwords[i].getPassword() << endl;
        cout << "Notes   : " << passwords[i].getNotes() << endl;
    }
}

int Vault::searchPassword(const string& website) const
{
    for (int i = 0; i < passwords.size(); i++)
    {
        if (passwords[i].getWebsite() == website)
        {
            return i;
        }
    }

    return -1;
}

void Vault::deletePassword(int index)
{
    if (index >= 0 && index < passwords.size())
    {
        passwords.erase(passwords.begin() + index);
    }
}

void Vault::editPassword(int index, const PasswordEntry& updatedEntry)
{
    if (index >= 0 && index < passwords.size())
    {
        passwords[index] = updatedEntry;
    }
}