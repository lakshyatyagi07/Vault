#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
private:
    std::string name;
    std::string email;
    std::string masterPassword;

public:
    User();
    User(const std::string& name,
         const std::string& email,
         const std::string& masterPassword);
    
    ~User(); // Destructor to cleanse sensitive memory

    // Getters
    const std::string& getName() const;
    const std::string& getEmail() const;
    const std::string& getMasterPassword() const;

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setMasterPassword(const std::string& masterPassword);
};

#endif // USER_HPP
