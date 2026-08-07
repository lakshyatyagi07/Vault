#include "PasswordEntry.hpp"
#include <openssl/crypto.h>

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

// Destructor
PasswordEntry::~PasswordEntry() {
    if (!password.empty()) {
        OPENSSL_cleanse(&password[0], password.size());
    }
}

// Setters
void PasswordEntry::setWebsite(const std::string& website) {
    this->website = website;
}

void PasswordEntry::setUsername(const std::string& username) {
    this->username = username;
}

void PasswordEntry::setPassword(const std::string& password) {
    if (!this->password.empty()) {
        OPENSSL_cleanse(&this->password[0], this->password.size());
    }
    this->password = password;
}

void PasswordEntry::setNotes(const std::string& notes) {
    this->notes = notes;
}

// Getters
const std::string& PasswordEntry::getWebsite() const {
    return website;
}

const std::string& PasswordEntry::getUsername() const {
    return username;
}

const std::string& PasswordEntry::getPassword() const {
    return password;
}

const std::string& PasswordEntry::getNotes() const {
    return notes;
}
