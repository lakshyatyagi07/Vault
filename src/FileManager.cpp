#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "FileManager.hpp"

// Header marker for cryptographic schema versioning
static const std::string VAULT_HEADER = "VAULT_GCM_V1";
static const int PBKDF2_ITERATIONS = 100000;

std::string FileManager::deriveKey(const std::string& password, const std::string& salt, int iterations) {
    std::string key(32, '\0');
    PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                      reinterpret_cast<const unsigned char*>(salt.data()), salt.length(),
                      iterations, EVP_sha256(),
                      32, reinterpret_cast<unsigned char*>(&key[0]));
    return key;
}

bool FileManager::encryptAES(const std::string& plaintext,
                             const std::string& key,
                             std::string& ciphertext,
                             std::string& iv,
                             std::string& tag) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    // Initialize encryption context
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    // Set IV length explicitly to GCM standard 12 bytes
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    // Set Key and IV parameters
    if (1 != EVP_EncryptInit_ex(ctx, NULL, NULL,
                                reinterpret_cast<const unsigned char*>(key.data()),
                                reinterpret_cast<const unsigned char*>(iv.data()))) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    ciphertext.resize(plaintext.size());
    int len = 0;
    int ciphertext_len = 0;

    // Encrypt plaintext stream
    if (1 != EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(&ciphertext[0]), &len,
                               reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size())) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len = len;

    // Finalize encryption
    if (1 != EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&ciphertext[0]) + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext_len += len;
    ciphertext.resize(ciphertext_len);

    // Retrieve authentication tag
    tag.resize(16);
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, &tag[0])) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    EVP_CIPHER_CTX_free(ctx);
    return true;
}

bool FileManager::decryptAES(const std::string& ciphertext,
                             const std::string& key,
                             const std::string& iv,
                             const std::string& tag,
                             std::string& plaintext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    // Initialize decryption context
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    // Set IV length
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), NULL)) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    // Set Key and IV parameters
    if (1 != EVP_DecryptInit_ex(ctx, NULL, NULL,
                                reinterpret_cast<const unsigned char*>(key.data()),
                                reinterpret_cast<const unsigned char*>(iv.data()))) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    plaintext.resize(ciphertext.size());
    int len = 0;
    int plaintext_len = 0;

    // Decrypt data block
    if (1 != EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(&plaintext[0]), &len,
                               reinterpret_cast<const unsigned char*>(ciphertext.data()), ciphertext.size())) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    plaintext_len = len;

    // Set expected authentication tag
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 16, const_cast<char*>(tag.data()))) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    // Finalize decryption (validates authentication tag)
    int ret = EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&plaintext[0]) + len, &len);
    EVP_CIPHER_CTX_free(ctx);

    if (ret > 0) {
        plaintext_len += len;
        plaintext.resize(plaintext_len);
        return true;
    } else {
        // Integrity check failed: either tag mismatch, bad key, or corrupted payload
        return false;
    }
}

bool FileManager::saveToFile(const std::string& filepath,
                             const std::vector<PasswordEntry>& entries,
                             const std::string& masterKey) {
    // 1. Serialize all entries: website|username|password|notes\n
    std::stringstream ss;
    for (const auto& entry : entries) {
        ss << entry.getWebsite() << "|"
           << entry.getUsername() << "|"
           << entry.getPassword() << "|"
           << entry.getNotes() << "\n";
    }
    std::string plaintext = ss.str();

    // 2. Generate random 16-byte salt for key derivation
    std::string salt(16, '\0');
    if (1 != RAND_bytes(reinterpret_cast<unsigned char*>(&salt[0]), 16)) {
        OPENSSL_cleanse(&plaintext[0], plaintext.size());
        return false;
    }

    // 3. Derive 32-byte AES-256 key using PBKDF2
    std::string derivedKey = deriveKey(masterKey, salt, PBKDF2_ITERATIONS);

    // 4. Generate random 12-byte IV for AES-GCM
    std::string iv(12, '\0');
    if (1 != RAND_bytes(reinterpret_cast<unsigned char*>(&iv[0]), 12)) {
        OPENSSL_cleanse(&derivedKey[0], derivedKey.size());
        OPENSSL_cleanse(&plaintext[0], plaintext.size());
        return false;
    }

    // 5. Encrypt using AES-256-GCM
    std::string ciphertext;
    std::string tag;
    if (!encryptAES(plaintext, derivedKey, ciphertext, iv, tag)) {
        OPENSSL_cleanse(&derivedKey[0], derivedKey.size());
        OPENSSL_cleanse(&plaintext[0], plaintext.size());
        return false;
    }

    // 6. Write out binary structure: [Header "VAULT_GCM_V1"] [Salt] [IV] [Tag] [Ciphertext]
    std::ofstream outFile(filepath, std::ios::binary);
    if (!outFile.is_open()) {
        OPENSSL_cleanse(&derivedKey[0], derivedKey.size());
        OPENSSL_cleanse(&plaintext[0], plaintext.size());
        return false;
    }

    outFile.write(VAULT_HEADER.data(), VAULT_HEADER.size());
    outFile.write(salt.data(), salt.size());
    outFile.write(iv.data(), iv.size());
    outFile.write(tag.data(), tag.size());
    outFile.write(ciphertext.data(), ciphertext.size());
    outFile.close();

    // Memory Sanity: zero-out sensitive keys and plaintext buffers
    OPENSSL_cleanse(&derivedKey[0], derivedKey.size());
    OPENSSL_cleanse(&plaintext[0], plaintext.size());

    return true;
}

bool FileManager::loadFromFile(const std::string& filepath,
                               std::vector<PasswordEntry>& entries,
                               const std::string& masterKey) {
    entries.clear();

    // Open file in binary mode and check size
    std::ifstream inFile(filepath, std::ios::binary | std::ios::ate);
    if (!inFile.is_open()) {
        // File does not exist yet (normal on new vaults)
        return false;
    }

    std::streamsize size = inFile.tellg();
    if (size <= 0) {
        inFile.close();
        return true;
    }

    // Minimum size check: Header (12) + Salt (16) + IV (12) + Tag (16) = 56 bytes
    if (size < 56) {
        inFile.close();
        return false;
    }

    inFile.seekg(0, std::ios::beg);

    // Read Header
    std::string header(VAULT_HEADER.size(), '\0');
    inFile.read(&header[0], VAULT_HEADER.size());
    if (header != VAULT_HEADER) {
        inFile.close();
        return false;
    }

    // Read Salt
    std::string salt(16, '\0');
    inFile.read(&salt[0], 16);

    // Read IV
    std::string iv(12, '\0');
    inFile.read(&iv[0], 12);

    // Read Tag
    std::string tag(16, '\0');
    inFile.read(&tag[0], 16);

    // Read Ciphertext
    size_t ciphertext_len = static_cast<size_t>(size) - VAULT_HEADER.size() - 16 - 12 - 16;
    std::string ciphertext(ciphertext_len, '\0');
    inFile.read(&ciphertext[0], ciphertext_len);
    inFile.close();

    // Derive AES key
    std::string derivedKey = deriveKey(masterKey, salt, PBKDF2_ITERATIONS);

    // Decrypt
    std::string plaintext;
    if (!decryptAES(ciphertext, derivedKey, iv, tag, plaintext)) {
        OPENSSL_cleanse(&derivedKey[0], derivedKey.size());
        std::cerr << "\n[CRITICAL ERROR] Failed to decrypt Vault! The master password may be incorrect, or the database has been tampered with.\n";
        return false;
    }

    // Parse the plaintext payload
    std::stringstream ss(plaintext);
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty()) continue;
        std::stringstream lineStream(line);
        std::string website, username, password, notes;
        if (std::getline(lineStream, website, '|') &&
            std::getline(lineStream, username, '|') &&
            std::getline(lineStream, password, '|')) {
            std::getline(lineStream, notes);
            entries.emplace_back(website, username, password, notes);
        }
    }

    // Memory Sanity: zero-out sensitive keys and plaintext buffers
    OPENSSL_cleanse(&derivedKey[0], derivedKey.size());
    OPENSSL_cleanse(&plaintext[0], plaintext.size());

    return true;
}
