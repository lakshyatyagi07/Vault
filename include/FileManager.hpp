#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>
#include "PasswordEntry.hpp"

class FileManager {
public:
    static bool saveToFile(const std::string& filepath,
                           const std::vector<PasswordEntry>& entries,
                           const std::string& masterKey);

    static bool loadFromFile(const std::string& filepath,
                             std::vector<PasswordEntry>& entries,
                             const std::string& masterKey);

    // Cryptographic Helpers using OpenSSL PBKDF2 and AES-256-GCM
    static std::string deriveKey(const std::string& password,
                                 const std::string& salt,
                                 int iterations);

    static bool encryptAES(const std::string& plaintext,
                           const std::string& key,
                           std::string& ciphertext,
                           std::string& iv,
                           std::string& tag);

    static bool decryptAES(const std::string& ciphertext,
                           const std::string& key,
                           const std::string& iv,
                           const std::string& tag,
                           std::string& plaintext);
};

#endif // FILE_MANAGER_HPP
