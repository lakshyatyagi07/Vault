#include <fstream>
#include <sstream>
#include <iostream>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include "Authentication.hpp"
#include "FileManager.hpp"

// Utility to convert hex to binary string
static std::string fromHex(const std::string& input) {
    if (input.length() % 2 != 0) return "";
    std::string output;
    output.reserve(input.length() / 2);
    for (size_t i = 0; i < input.length(); i += 2) {
        std::string byteString = input.substr(i, 2);
        char byte = static_cast<char>(std::strtol(byteString.c_str(), nullptr, 16));
        output.push_back(byte);
    }
    return output;
}

// Utility to convert binary string to hex
static std::string toHex(const std::string& input) {
    static const char hex_chars[] = "0123456789ABCDEF";
    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input) {
        output.push_back(hex_chars[c >> 4]);
        output.push_back(hex_chars[c & 15]);
    }
    return output;
}

// Struct to store loaded credential data locally
struct AuthData {
    std::string name;
    std::string email;
    std::string salt;
    std::string hash;
};

static AuthData loadedAuthData;

Authentication::Authentication() {
    userExists = false;
    std::ifstream inFile("data/user_config.txt");
    if (inFile.is_open()) {
        std::string line;
        if (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string name, email, saltHex, hashHex;
            if (std::getline(ss, name, '|') &&
                std::getline(ss, email, '|') &&
                std::getline(ss, saltHex, '|') &&
                std::getline(ss, hashHex)) {
                
                loadedAuthData.name = name;
                loadedAuthData.email = email;
                loadedAuthData.salt = fromHex(saltHex);
                loadedAuthData.hash = fromHex(hashHex);
                
                // Do NOT store raw master password in the User object. Set it to empty.
                registeredUser = User(name, email, "");
                userExists = true;
            }
        }
        inFile.close();
    }
}

bool Authentication::signUp(const std::string& name,
                            const std::string& email,
                            const std::string& masterPassword) {
    // Generate a secure, random 16-byte salt using OpenSSL RAND
    std::string salt(16, '\0');
    if (1 != RAND_bytes(reinterpret_cast<unsigned char*>(&salt[0]), 16)) {
        return false;
    }

    // Derive a 32-byte key/hash of the master password using PBKDF2 (100,000 iterations)
    std::string hash = FileManager::deriveKey(masterPassword, salt, 100000);

    // Save configuration pipe-delimited with hex-encoded salt and hash
    std::ofstream outFile("data/user_config.txt");
    if (!outFile.is_open()) {
        OPENSSL_cleanse(&hash[0], hash.size());
        return false;
    }

    outFile << name << "|"
            << email << "|"
            << toHex(salt) << "|"
            << toHex(hash) << "\n";
    outFile.close();

    // Cache locally
    loadedAuthData.name = name;
    loadedAuthData.email = email;
    loadedAuthData.salt = salt;
    loadedAuthData.hash = hash;

    registeredUser = User(name, email, "");
    userExists = true;

    // Securely cleanse sensitive variables
    OPENSSL_cleanse(&hash[0], hash.size());
    return true;
}

bool Authentication::login(const std::string& email,
                           const std::string& masterPassword) {
    if (!userExists) {
        return false;
    }

    // Verify email matches first
    if (loadedAuthData.email != email) {
        return false;
    }

    // Compute the hash of the entered password using the saved salt
    std::string computedHash = FileManager::deriveKey(masterPassword, loadedAuthData.salt, 100000);

    // Constant-time comparison using OpenSSL CRYPTO_memcmp to prevent timing attacks
    bool match = false;
    if (computedHash.size() == loadedAuthData.hash.size()) {
        if (0 == CRYPTO_memcmp(computedHash.data(), loadedAuthData.hash.data(), computedHash.size())) {
            match = true;
        }
    }

    // Securely cleanse computed hash
    OPENSSL_cleanse(&computedHash[0], computedHash.size());
    return match;
}

const User& Authentication::getUser() const {
    return registeredUser;
}

bool Authentication::hasUser() const {
    return userExists;
}
