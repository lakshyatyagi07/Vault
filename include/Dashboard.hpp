#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <string>
#include "Vault.hpp"

class Dashboard {
private:
    Vault vault;
    std::string masterPassword;

public:
    Dashboard(const Vault& initialVault, const std::string& key);
    
    void run();
    void display() const;
    int getChoice() const;
};

#endif // DASHBOARD_HPP
