#ifndef VAULT_HPP
#define VAULT_HPP

#include <vector>
#include <string>
#include "PasswordEntry.hpp"

class Vault {
private:
    std::vector<PasswordEntry> passwords;

public:
    void addPassword(const PasswordEntry& entry, bool silent = false);
    void viewPasswords() const;
    void searchPassword(const std::string& query) const;
    void editPassword(int index);
    void deletePassword(int index);

    // Additional helper getter
    const std::vector<PasswordEntry>& getPasswords() const;
};

#endif // VAULT_HPP
