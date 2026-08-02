#pragma once

#include <string>

class PasswordEntry
{
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

    void setWebsite(const std::string& website);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setNotes(const std::string& notes);

    std::string getWebsite() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getNotes() const;
};