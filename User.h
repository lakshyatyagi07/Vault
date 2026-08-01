#pragma once

#include <string>

class User
{
private:
    std::string name;
    std::string email;
    std::string masterPassword;

public:
    User();
    User(const std::string& name,
         const std::string& email,
         const std::string& masterPassword);

    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setMasterPassword(const std::string& masterPassword);

    std::string getName() const;
    std::string getEmail() const;
    std::string getMasterPassword() const;
};