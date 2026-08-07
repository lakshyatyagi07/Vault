# Vault: Production-Grade C++17 CLI Password Manager

Vault is a command-line password manager written in C++17. It features industry-standard security primitives (OpenSSL AES-256-GCM and PBKDF2), interactive terminal input masking, robust verification loops, and secure in-memory buffer cleansing.

---

## Security & Architecture Highlights

- **AES-256-GCM Encryption**: Vault secures the local database (`data/vault_data.txt`) using the AES-256-GCM cryptographic cipher. Every write operation generates a random 12-byte initialization vector (IV) and a 16-byte authentication tag, ensuring confidentiality and validating data integrity on decryption.
- **Salted PBKDF2 Key Derivation**: Encryption keys and authentication hashes are derived from the master password using PBKDF2 (`PKCS5_PBKDF2_HMAC_SHA256`) with a cryptographically secure 16-byte random salt and 100,000 iterations.
- **Timing-Attack Resistance**: Verification of master credentials uses OpenSSL `CRYPTO_memcmp` to ensure constant-time comparisons, eliminating side-channel information leaks.
- **In-Memory Sanitization**: Destructors for models (`User`, `PasswordEntry`) and classes (`Dashboard`, `Authentication`) explicitly zero-out sensitive password buffers using `OPENSSL_cleanse` before releasing memory.
- **Terminal Masking**: Character echo is disabled during credential entries (utilizing `termios` on macOS/Linux and `GetConsoleMode` on Windows).
- **Tabular & Redacted Views**: Vault lists credentials in an aligned tabular structure, masking passwords by default. An explicit "Reveal Password" action allows users to selectively decrypt and view cleartext entries.

---

## Project Directory Architecture

```
Vault/
│
├── include/                 # Standard Header Files (.hpp)
│   ├── User.hpp             # User credentials model (with memory-cleansing)
│   ├── PasswordEntry.hpp    # Single credential record representation
│   ├── Vault.hpp            # Password collection class and CRUD method declarations
│   ├── FileManager.hpp      # OpenSSL AES-256-GCM and PBKDF2 utilities
│   ├── Authentication.hpp   # Hashed SignUp/Login access control
│   └── Dashboard.hpp        # Interactive CLI menu & terminal masking engine
│
├── src/                     # Implementation Source Files (.cpp)
│   ├── User.cpp             
│   ├── PasswordEntry.cpp    
│   ├── Vault.cpp            
│   ├── FileManager.cpp      
│   ├── Authentication.cpp   
│   └── Dashboard.cpp        
│
├── data/                    # Storage Folder (Ignored by Git)
│   ├── user_config.txt      # PBKDF2-hashed master credentials
│   └── vault_data.txt       # AES-256-GCM encrypted database
│
├── CMakeLists.txt           # CMake build configuration with OpenSSL linking
├── main.cpp                 # Boot manager and memory zero-out controller
├── .gitignore               # Excludes build logs, target binaries, and local data files
└── README.md                # Project documentation
```

---

## Compilation and Run Instructions

Ensure you have OpenSSL installed (`brew install openssl` on macOS).

### Option A: Standard GCC/Clang Build
Compile directly while referencing the OpenSSL headers and library paths (updated for Apple Silicon macOS brew locations):
```bash
g++ -std=c++17 -Iinclude -I/opt/homebrew/opt/openssl@3/include \
    main.cpp src/*.cpp \
    -L/opt/homebrew/opt/openssl@3/lib -lcrypto -lssl \
    -o Vault
```
Launch:
```bash
./Vault
```

### Option B: CMake Build
Configure and build using the provided CMakeLists:
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```
Launch:
```bash
./Vault
```

---

## Removing Sensitive Files from Git Tracking

If any local data configurations were previously tracked in your Git index, run the following commands to safely remove them from history **without** deleting the local files from your storage:

```bash
# 1. Untrack data files from the Git cache
git rm --cached data/user_config.txt data/vault_data.txt

# 2. Commit the changes
git commit -m "chore: remove sensitive configuration database tracking from Git"
```
Vault is configured with `.gitignore` to prevent these data files from being tracked in future commits.

---

## Resume Bullet Points (Tailored for CS Portfolios)

* **Developed a secure CLI Password Manager in C++17** using OpenSSL (`EVP` API), protecting user databases on disk via AES-256-GCM and verify-on-decrypt integrity tags.
* **Engineered robust access control using PBKDF2 password hashing** with 100,000 iterations and a random 16-byte salt, employing constant-time memory comparisons (`CRYPTO_memcmp`) to neutralize timing side-channel attacks.
* **Implemented memory sanitization and anti-leak techniques** by utilizing `OPENSSL_cleanse` in class destructors to zero-out plaintext keys and sensitive variables, and built cross-platform terminal masking loops to disable character echoing.
