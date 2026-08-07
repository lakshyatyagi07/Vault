#include "User.hpp"
#include <openssl/crypto.h>

// Default Constructor
User::User() {
    name = "";
    email = "";
    masterPassword = "";
}

// Parameterized Constructor
User::User(const std::string& name,
           const std::string& email,
           const std::string& masterPassword) {
    this->name = name;
    this->email = email;
    this->masterPassword = masterPassword;
}

// Destructor
User::~User() {
    if (!masterPassword.empty()) {
        OPENSSL_cleanse(&masterPassword[0], masterPassword.size());
    }
}

// Setters
void User::setName(const std::string& name) {
    this->name = name;
}

void User::setEmail(const std::string& email) {
    this->email = email;
}

void User::setMasterPassword(const std::string& masterPassword) {
    if (!this->masterPassword.empty()) {
        OPENSSL_cleanse(&this->masterPassword[0], this->masterPassword.size());
    }
    this->masterPassword = masterPassword;
}

// Getters
const std::string& User::getName() const {
    return name;
}

const std::string& User::getEmail() const {
    return email;
}

const std::string& User::getMasterPassword() const {
    return masterPassword;
}
