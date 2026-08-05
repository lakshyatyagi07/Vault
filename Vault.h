#pragma once

#include <vector>
#include <string>

#include "PasswordEntry.h"

class Vault
{
private:
    std::vector<PasswordEntry> passwords;

public:
    void addPassword(const PasswordEntry& entry);

    void viewPasswords() const;

    void searchPassword(const std::string& website) const;

    void deletePassword(const std::string& website);

    void editPassword(const std::string& website);
};