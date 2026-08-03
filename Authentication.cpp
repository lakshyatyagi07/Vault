#include "Authentication.h"

Authentication::Authentication()
{
    userExists = false;
}

bool Authentication::registerUser(const User& user)
{
    registeredUser = user;
    userExists = true;

    return true;
}

bool Authentication::login(const std::string& email,
                           const std::string& masterPassword)
{
    if (!userExists)
    {
        return false;
    }

    if (registeredUser.getEmail() == email &&
        registeredUser.getMasterPassword() == masterPassword)
    {
        return true;
    }

    return false;
}

User Authentication::getUser() const
{
    return registeredUser;
}

bool Authentication::hasUser() const
{
    return userExists;
}