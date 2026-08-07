#include <iostream>
#include <limits>
#include "Dashboard.hpp"
#include "FileManager.hpp"

using namespace std;

Dashboard::Dashboard(const Vault& initialVault, const std::string& key)
    : vault(initialVault), masterPassword(key) {}

void Dashboard::display() const {
    cout << "\n==================================" << endl;
    cout << "          Vault Dashboard         " << endl;
    cout << "==================================" << endl;
    cout << "[1] Add Password" << endl;
    cout << "[2] View All Passwords" << endl;
    cout << "[3] Search Password" << endl;
    cout << "[4] Edit Password" << endl;
    cout << "[5] Delete Password" << endl;
    cout << "[6] Save & Logout" << endl;
    cout << "==================================" << endl;
}

int Dashboard::getChoice() const {
    int choice;
    cout << "\nEnter your choice: ";
    if (cin >> choice) {
        return choice;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return -1;
}

void Dashboard::run() {
    bool running = true;
    while (running) {
        display();
        int choice = getChoice();
        switch (choice) {
            case 1: {
                string website, username, password, notes;
                cout << "\n========== Add Password ==========\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "Website: ";
                getline(cin, website);
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                cout << "Notes: ";
                getline(cin, notes);

                PasswordEntry entry(website, username, password, notes);
                vault.addPassword(entry);
                break;
            }
            case 2:
                vault.viewPasswords();
                break;
            case 3: {
                string query;
                cout << "\nEnter search query (website/username): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, query);
                vault.searchPassword(query);
                break;
            }
            case 4: {
                int index;
                cout << "\nEnter password index to edit: ";
                if (cin >> index) {
                    vault.editPassword(index);
                } else {
                    cout << "Invalid input index.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            case 5: {
                int index;
                cout << "\nEnter password index to delete: ";
                if (cin >> index) {
                    vault.deletePassword(index);
                } else {
                    cout << "Invalid input index.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            case 6: {
                cout << "\nSaving passwords to file..." << endl;
                if (FileManager::saveToFile("data/vault_data.txt", vault.getPasswords(), masterPassword)) {
                    cout << "Data saved successfully." << endl;
                } else {
                    cout << "Warning: Failed to save password data." << endl;
                }
                cout << "Logged out. Goodbye!" << endl;
                running = false;
                break;
            }
            default:
                cout << "\nInvalid choice. Please enter a number between 1 and 6.\n";
                break;
        }
    }
}
