#include <iostream>
#include <limits>
#include <iomanip>
#include "Dashboard.hpp"
#include "FileManager.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include <openssl/crypto.h>

using namespace std;

Dashboard::Dashboard(const Vault& initialVault, const string& key)
    : vault(initialVault), masterPassword(key) {}

Dashboard::~Dashboard() {
    if (!masterPassword.empty()) {
        OPENSSL_cleanse(&masterPassword[0], masterPassword.size());
    }
}

string Dashboard::getMaskedInput(const string& prompt) {
    cout << prompt;
    string input;

#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    // Disable console input character echoing
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    getline(cin, input);
    // Restore original console mode
    SetConsoleMode(hStdin, mode);
#else
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    // Disable ECHO flag in local modes
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    getline(cin, input);
    // Restore original termios settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    cout << endl; // Print newline since Enter is not echoed
    return input;
}

int Dashboard::getValidIndexInput(const string& prompt, size_t maxIndex) const {
    if (maxIndex == 0) {
        cout << "\nError: The vault is currently empty. There are no entries to select.\n";
        return -1;
    }

    int index;
    while (true) {
        cout << prompt << " (0 to " << (maxIndex - 1) << ", or -1 to cancel): ";
        if (cin >> index) {
            if (index == -1) {
                return -1;
            }
            if (index >= 0 && static_cast<size_t>(index) < maxIndex) {
                // Consume the remaining newline in the input stream buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return index;
            }
            cout << "Error: Index out of bounds. Valid range: [0, " << (maxIndex - 1) << "]\n";
        } else {
            cout << "Error: Invalid numeric input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Dashboard::display() const {
    cout << "\n==================================" << endl;
    cout << "          Vault Dashboard         " << endl;
    cout << "==================================" << endl;
    cout << "[1] Add Password" << endl;
    cout << "[2] View All Passwords (Masked)" << endl;
    cout << "[3] Reveal Password" << endl;
    cout << "[4] Search Password" << endl;
    cout << "[5] Edit Password" << endl;
    cout << "[6] Delete Password" << endl;
    cout << "[7] Save & Logout" << endl;
    cout << "==================================" << endl;
}

int Dashboard::getChoice() const {
    int choice;
    while (true) {
        cout << "\nEnter your choice (1-7): ";
        if (cin >> choice) {
            if (choice >= 1 && choice <= 7) {
                return choice;
            }
            cout << "Error: Choice must be between 1 and 7." << endl;
        } else {
            cout << "Error: Invalid input. Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
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
                
                // Mask password keyboard entry
                password = getMaskedInput("Password: ");
                
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
                int index = getValidIndexInput("\nEnter password index to reveal", vault.getPasswords().size());
                if (index != -1) {
                    vault.revealPassword(index);
                }
                break;
            }
            case 4: {
                string query;
                cout << "\nEnter search query (website/username): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, query);
                vault.searchPassword(query);
                break;
            }
            case 5: {
                int index = getValidIndexInput("\nEnter password index to edit", vault.getPasswords().size());
                if (index != -1) {
                    vault.editPassword(index);
                }
                break;
            }
            case 6: {
                int index = getValidIndexInput("\nEnter password index to delete", vault.getPasswords().size());
                if (index != -1) {
                    vault.deletePassword(index);
                }
                break;
            }
            case 7: {
                cout << "\nSaving passwords to file..." << endl;
                if (FileManager::saveToFile("data/vault_data.txt", vault.getPasswords(), masterPassword)) {
                    cout << "Vault saved and encrypted securely." << endl;
                } else {
                    cout << "Warning: Failed to save password data." << endl;
                }
                cout << "Logged out successfully. Goodbye!" << endl;
                running = false;
                break;
            }
            default:
                break;
        }
    }
}
