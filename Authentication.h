#pragma once

#include "User.h"

class Authentication
{
private:
    User registeredUser;
    bool userExists;

public:
    Authentication();

    bool registerUser(const User& user);

    bool login(const std::string& email,
               const std::string& masterPassword);

    User getUser() const;

    bool hasUser() const;
};