#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <limits>
#include "Vault.hpp"

// Helper to convert a string to lowercase for case-insensitive search
static std::string toLowerCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return str;
}

void Vault::addPassword(const PasswordEntry& entry, bool silent) {
    passwords.push_back(entry);
    if (!silent) {
        std::cout << "\nPassword entry added successfully.\n";
    }
}

void Vault::viewPasswords() const {
    if (passwords.empty()) {
        std::cout << "\nVault is empty. No passwords saved.\n";
        return;
    }

    // Print a beautifully formatted table
    std::cout << "\n" << std::string(88, '=') << "\n";
    std::cout << "                             SAVED PASSWORDS IN VAULT\n";
    std::cout << std::string(88, '=') << "\n";
    
    // Table Headers
    std::cout << std::left 
              << std::setw(8)  << "Index"
              << std::setw(22) << "Website"
              << std::setw(22) << "Username"
              << std::setw(18) << "Password"
              << std::setw(20) << "Notes"
              << "\n";
    std::cout << std::string(88, '-') << "\n";

    for (size_t i = 0; i < passwords.size(); ++i) {
        std::cout << std::left
                  << std::setw(8)  << i
                  << std::setw(22) << passwords[i].getWebsite()
                  << std::setw(22) << passwords[i].getUsername()
                  << std::setw(18) << passwords[i].getPassword()
                  << std::setw(20) << passwords[i].getNotes()
                  << "\n";
    }
    std::cout << std::string(88, '=') << "\n";
}

void Vault::searchPassword(const std::string& query) const {
    if (passwords.empty()) {
        std::cout << "\nVault is empty. Nothing to search.\n";
        return;
    }

    std::string lowerQuery = toLowerCase(query);
    bool found = false;
    bool headerPrinted = false;

    for (size_t i = 0; i < passwords.size(); ++i) {
        std::string lowerWebsite = toLowerCase(passwords[i].getWebsite());
        std::string lowerUsername = toLowerCase(passwords[i].getUsername());

        if (lowerWebsite.find(lowerQuery) != std::string::npos ||
            lowerUsername.find(lowerQuery) != std::string::npos) {
            
            if (!headerPrinted) {
                std::cout << "\n" << std::string(88, '=') << "\n";
                std::cout << "                              SEARCH RESULTS FOR \"" << query << "\"\n";
                std::cout << std::string(88, '=') << "\n";
                std::cout << std::left 
                          << std::setw(8)  << "Index"
                          << std::setw(22) << "Website"
                          << std::setw(22) << "Username"
                          << std::setw(18) << "Password"
                          << std::setw(20) << "Notes"
                          << "\n";
                std::cout << std::string(88, '-') << "\n";
                headerPrinted = true;
            }

            std::cout << std::left
                      << std::setw(8)  << i
                      << std::setw(22) << passwords[i].getWebsite()
                      << std::setw(22) << passwords[i].getUsername()
                      << std::setw(18) << passwords[i].getPassword()
                      << std::setw(20) << passwords[i].getNotes()
                      << "\n";
            found = true;
        }
    }

    if (found) {
        std::cout << std::string(88, '=') << "\n";
    } else {
        std::cout << "\nNo matching password entries found for \"" << query << "\".\n";
    }
}

void Vault::editPassword(int index) {
    if (index < 0 || static_cast<size_t>(index) >= passwords.size()) {
        std::cerr << "Error: Invalid index " << index << ". Valid range: [0, " << (passwords.size() - 1) << "]\n";
        return;
    }

    // Consume any leftover newline in the input buffer (from cin >> choice/index)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string input;
    std::cout << "\n--- Edit Password Entry ---\n";
    std::cout << "Leave blank and press Enter to keep current values.\n\n";

    // Website
    std::cout << "Website [" << passwords[index].getWebsite() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        passwords[index].setWebsite(input);
    }

    // Username
    std::cout << "Username [" << passwords[index].getUsername() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        passwords[index].setUsername(input);
    }

    // Password
    std::cout << "Password [" << passwords[index].getPassword() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        passwords[index].setPassword(input);
    }

    // Notes
    std::cout << "Notes [" << passwords[index].getNotes() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        passwords[index].setNotes(input);
    }

    std::cout << "\nPassword entry updated successfully.\n";
}

void Vault::deletePassword(int index) {
    if (index < 0 || static_cast<size_t>(index) >= passwords.size()) {
        std::cerr << "Error: Invalid index " << index << ". Valid range: [0, " << (passwords.size() - 1) << "]\n";
        return;
    }

    passwords.erase(passwords.begin() + index);
    std::cout << "\nPassword entry deleted successfully.\n";
}

const std::vector<PasswordEntry>& Vault::getPasswords() const {
    return passwords;
}
