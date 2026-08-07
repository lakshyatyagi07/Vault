#include <fstream>
#include <sstream>
#include <iostream>
#include "Authentication.hpp"
#include "FileManager.hpp"

// Master password config encryption/decryption default key
static const std::string AUTH_CRYPT_KEY = "VaultDefaultAuthKey";

Authentication::Authentication() {
    userExists = false;
    
    // Check if configuration file exists and load it
    std::ifstream inFile("data/user_config.txt");
    if (inFile.is_open()) {
        std::string line;
        if (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string name, email, encryptedPassword;
            if (std::getline(ss, name, '|') &&
                std::getline(ss, email, '|') &&
                std::getline(ss, encryptedPassword)) {
                
                std::string decryptedPassword = FileManager::decryptXOR(encryptedPassword, AUTH_CRYPT_KEY);
                registeredUser = User(name, email, decryptedPassword);
                userExists = true;
            }
        }
        inFile.close();
    }
}

bool Authentication::signUp(const std::string& name,
                            const std::string& email,
                            const std::string& masterPassword) {
    registeredUser = User(name, email, masterPassword);
    userExists = true;

    // Create the data folder if it doesn't exist
    // (It's already created, but we write directly to data/user_config.txt)
    std::ofstream outFile("data/user_config.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not save user configuration to file.\n";
        return false;
    }

    std::string encryptedPassword = FileManager::encryptXOR(masterPassword, AUTH_CRYPT_KEY);
    outFile << name << "|" << email << "|" << encryptedPassword << "\n";
    outFile.close();
    return true;
}

bool Authentication::login(const std::string& email,
                           const std::string& masterPassword) {
    if (!userExists) {
        return false;
    }
    return (registeredUser.getEmail() == email &&
            registeredUser.getMasterPassword() == masterPassword);
}

User Authentication::getUser() const {
    return registeredUser;
}

bool Authentication::hasUser() const {
    return userExists;
}
