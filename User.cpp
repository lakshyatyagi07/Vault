#include "User.h"

// Default Constructor
User::User()
{
    name = "";
    email = "";
    masterPassword = "";
}

// Parameterized Constructor
User::User(const std::string& name,
           const std::string& email,
           const std::string& masterPassword)
{
    this->name = name;
    this->email = email;
    this->masterPassword = masterPassword;
}

// Setters
void User::setName(const std::string& name)
{
    this->name = name;
}

void User::setEmail(const std::string& email)
{
    this->email = email;
}

void User::setMasterPassword(const std::string& masterPassword)
{
    this->masterPassword = masterPassword;
}

// Getters
std::string User::getName() const
{
    return name;
}

std::string User::getEmail() const
{
    return email;
}

std::string User::getMasterPassword() const
{
    return masterPassword;
}