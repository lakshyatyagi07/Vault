#include <fstream>
#include <sstream>
#include <iostream>
#include "FileManager.hpp"

std::string FileManager::encryptXOR(const std::string& input, const std::string& key) {
    if (key.empty()) {
        return input;
    }
    std::string output = input;
    for (size_t i = 0; i < input.length(); ++i) {
        output[i] = input[i] ^ key[i % key.length()];
    }
    return output;
}

std::string FileManager::decryptXOR(const std::string& input, const std::string& key) {
    // XOR is symmetric, so decryption is identical to encryption
    return encryptXOR(input, key);
}

bool FileManager::saveToFile(const std::string& filepath,
                             const std::vector<PasswordEntry>& entries,
                             const std::string& key) {
    std::ofstream outFile(filepath, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filepath << std::endl;
        return false;
    }

    // 1. Serialize entries: website|username|password|notes\n
    std::stringstream ss;
    for (const auto& entry : entries) {
        ss << entry.getWebsite() << "|"
           << entry.getUsername() << "|"
           << entry.getPassword() << "|"
           << entry.getNotes() << "\n";
    }
    std::string payload = ss.str();

    // 2. Encrypt the entire payload string
    std::string encrypted = encryptXOR(payload, key);

    // 3. Write binary data
    outFile.write(encrypted.data(), encrypted.size());
    outFile.close();
    return true;
}

bool FileManager::loadFromFile(const std::string& filepath,
                               std::vector<PasswordEntry>& entries,
                               const std::string& key) {
    entries.clear();

    // Open file in binary mode and check size using seek-to-end
    std::ifstream inFile(filepath, std::ios::binary | std::ios::ate);
    if (!inFile.is_open()) {
        // File doesn't exist yet, which is expected on first launch
        return false;
    }

    std::streamsize size = inFile.tellg();
    if (size <= 0) {
        // File is empty
        inFile.close();
        return true;
    }

    // Seek back to the beginning of the file
    inFile.seekg(0, std::ios::beg);

    // Read the entire file content
    std::string encryptedPayload(static_cast<size_t>(size), '\0');
    if (!inFile.read(&encryptedPayload[0], size)) {
        std::cerr << "Error: Could not read data from file: " << filepath << std::endl;
        inFile.close();
        return false;
    }
    inFile.close();

    // 2. Decrypt the payload
    std::string decryptedPayload = decryptXOR(encryptedPayload, key);

    // 3. Deserialize line-by-line
    std::stringstream ss(decryptedPayload);
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream lineStream(line);
        std::string website, username, password, notes;

        if (std::getline(lineStream, website, '|') &&
            std::getline(lineStream, username, '|') &&
            std::getline(lineStream, password, '|')) {
            // Notes is the remainder of the line
            std::getline(lineStream, notes);
            entries.emplace_back(website, username, password, notes);
        }
    }

    return true;
}
