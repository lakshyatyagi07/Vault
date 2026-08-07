#ifndef AUTHENTICATION_HPP
#define AUTHENTICATION_HPP

#include <string>
#include "User.hpp"

class Authentication {
private:
    User registeredUser;
    bool userExists;

public:
    Authentication();

    bool signUp(const std::string& name,
                const std::string& email,
                const std::string& masterPassword);

    bool login(const std::string& email,
               const std::string& masterPassword);

    // Getters
    User getUser() const;
    bool hasUser() const;
};

#endif // AUTHENTICATION_HPP
