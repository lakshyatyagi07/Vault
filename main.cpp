#include <iostream>
#include <limits>
#include <string>
#include <openssl/crypto.h>
#include "Authentication.hpp"
#include "FileManager.hpp"
#include "Vault.hpp"
#include "Dashboard.hpp"

using namespace std;

int main() {
    Authentication auth;
    User user;
    string masterPassword;

    cout << "=====================================" << endl;
    cout << "          Welcome to Vault           " << endl;
    cout << "=====================================" << endl;

    if (!auth.hasUser()) {
        cout << "\n[No existing master account found]" << endl;
        cout << "Please Sign Up to create your Master Account." << endl;

        string name, email, password;
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        
        while (true) {
            // Read master password with keyboard echoing disabled
            password = Dashboard::getMaskedInput("Enter Master Password: ");
            if (password.empty()) {
                cout << "Password cannot be empty. Try again.\n";
            } else {
                break;
            }
        }

        if (auth.signUp(name, email, password)) {
            cout << "\nAccount created successfully!" << endl;
            user = auth.getUser();
            masterPassword = password;
        } else {
            cerr << "Fatal Error: Sign up failed. Exiting." << endl;
            OPENSSL_cleanse(&password[0], password.size());
            return 1;
        }

        // Cleanse temporary password string from memory
        OPENSSL_cleanse(&password[0], password.size());
    } else {
        cout << "\n[Existing master account detected]" << endl;
        string email, password;
        
        // Loop login attempts
        bool loggedIn = false;
        while (!loggedIn) {
            cout << "Enter Email: ";
            getline(cin, email);
            
            // Read password with keyboard echoing disabled
            password = Dashboard::getMaskedInput("Enter Master Password: ");

            if (auth.login(email, password)) {
                cout << "\nAuthentication successful!" << endl;
                user = auth.getUser();
                masterPassword = password;
                loggedIn = true;
            } else {
                cout << "\nInvalid credentials. Please try again.\n" << endl;
                OPENSSL_cleanse(&password[0], password.size());
            }
        }
        
        // Cleanse temporary password string from memory
        OPENSSL_cleanse(&password[0], password.size());
    }

    // Load saved password entries
    Vault vault;
    vector<PasswordEntry> loadedEntries;
    cout << "Loading saved password entries..." << endl;
    
    // Check and load from file using the master password as key
    if (FileManager::loadFromFile("data/vault_data.txt", loadedEntries, masterPassword)) {
        for (const auto& entry : loadedEntries) {
            vault.addPassword(entry, true);
        }
        cout << "Loaded " << loadedEntries.size() << " passwords successfully." << endl;
    } else {
        cout << "No existing password vault entries found or failed to load. Starting fresh." << endl;
    }

    // Launch the interactive dashboard loop
    Dashboard dashboard(vault, masterPassword);
    
    // Cleanse local copy of the master password, since Dashboard constructor copied it
    OPENSSL_cleanse(&masterPassword[0], masterPassword.size());
    
    dashboard.run();

    return 0;
}