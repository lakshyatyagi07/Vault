#include "PasswordEntry.hpp"

// Default Constructor
PasswordEntry::PasswordEntry() {
    website = "";
    username = "";
    password = "";
    notes = "";
}

// Parameterized Constructor
PasswordEntry::PasswordEntry(const std::string& website,
                             const std::string& username,
                             const std::string& password,
                             const std::string& notes) {
    this->website = website;
    this->username = username;
    this->password = password;
    this->notes = notes;
}

// Setters
void PasswordEntry::setWebsite(const std::string& website) {
    this->website = website;
}

void PasswordEntry::setUsername(const std::string& username) {
    this->username = username;
}

void PasswordEntry::setPassword(const std::string& password) {
    this->password = password;
}

void PasswordEntry::setNotes(const std::string& notes) {
    this->notes = notes;
}

// Getters
std::string PasswordEntry::getWebsite() const {
    return website;
}

std::string PasswordEntry::getUsername() const {
    return username;
}

std::string PasswordEntry::getPassword() const {
    return password;
}

std::string PasswordEntry::getNotes() const {
    return notes;
}
