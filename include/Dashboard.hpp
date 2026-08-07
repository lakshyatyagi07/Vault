#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <string>
#include "Vault.hpp"

class Dashboard {
private:
    Vault vault;
    std::string masterPassword;

    // Helper for secure numeric index validation loops
    int getValidIndexInput(const std::string& prompt, size_t maxIndex) const;

public:
    Dashboard(const Vault& initialVault, const std::string& key);
    ~Dashboard(); // Destructor to cleanse masterPassword

    void run();
    void display() const;
    int getChoice() const;

    // Cross-platform static helper to read terminal inputs without character echo
    static std::string getMaskedInput(const std::string& prompt);
};

#endif // DASHBOARD_HPP
