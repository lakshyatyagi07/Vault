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

    void showAllPasswords() const;

    int searchPassword(const std::string& website) const;

    void deletePassword(int index);

    void editPassword(int index, const PasswordEntry& updatedEntry);
};