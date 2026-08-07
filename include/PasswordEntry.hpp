#ifndef PASSWORD_ENTRY_HPP
#define PASSWORD_ENTRY_HPP

#include <string>

class PasswordEntry {
private:
    std::string website;
    std::string username;
    std::string password;
    std::string notes;

public:
    PasswordEntry();
    PasswordEntry(const std::string& website,
                  const std::string& username,
                  const std::string& password,
                  const std::string& notes);

    // Getters
    std::string getWebsite() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getNotes() const;

    // Setters
    void setWebsite(const std::string& website);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setNotes(const std::string& notes);
};

#endif // PASSWORD_ENTRY_HPP
