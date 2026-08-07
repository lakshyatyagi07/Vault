#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>
#include "PasswordEntry.hpp"

class FileManager {
public:
    static bool saveToFile(const std::string& filepath,
                           const std::vector<PasswordEntry>& entries,
                           const std::string& key);

    static bool loadFromFile(const std::string& filepath,
                             std::vector<PasswordEntry>& entries,
                             const std::string& key);

    static std::string encryptXOR(const std::string& data,
                                  const std::string& key);

    static std::string decryptXOR(const std::string& data,
                                  const std::string& key);
};

#endif // FILE_MANAGER_HPP
