#include "Authentication.h"

Authentication::Authentication()
{
}

void Authentication::registerUser(const User& user)
{
    registeredUser = user;
}

bool Authentication::login(const std::string& email,
                           const std::string& masterPassword)
{
    if (registeredUser.getEmail() == email &&
        registeredUser.getMasterPassword() == masterPassword)
    {
        return true;
    }

    return false;
}