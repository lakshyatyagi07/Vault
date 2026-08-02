#pragma once

#include <string>
#include "User.h"

class Authentication
{
private:
    User registeredUser;

public:
    Authentication();

    void registerUser(const User& user);

    bool login(const std::string& email,
               const std::string& masterPassword);
};