# Vault: Secure C++17 CLI Password Manager

Vault is a command-line password manager written in C++17. It allows users to securely register an account, authenticate via a master password, and manage their credentials (website, username, password, and notes) in an encrypted data file.

---

## Key Tech Stack Highlights

- **Modern C++17 & STL**: Built on modern C++ principles using robust standard containers (`std::vector`), streams, formatting manipulators (`std::setw`, `std::left`), and algorithms.
- **Symmetric XOR Encryption**: Vault secures stored credentials using a byte-by-byte symmetric XOR cipher with dynamic modulo key wrapping.
- **Hex-Encoded File I/O**: Encrypted database files are hex-encoded to guarantee text file carriage return safety, null-byte resistance, and ease of cross-platform porting.
- **Robust OOP Architecture**: Modularity is maintained by strictly decoupling data models (`User`, `PasswordEntry`), collection managers (`Vault`), persistence utilities (`FileManager`), access control (`Authentication`), and the user interface (`Dashboard`).

---

## Project Directory Architecture

```
Vault/
│
├── include/                 # Standard Header Files (.hpp)
│   ├── User.hpp             # User credentials model
│   ├── PasswordEntry.hpp    # Single credential record representation
│   ├── Vault.hpp            # Password collection class and CRUD method declarations
│   ├── FileManager.hpp      # Cryptographic XOR and File Persistence utilities
│   ├── Authentication.hpp   # SignUp/Login authorization manager
│   └── Dashboard.hpp        # Interactive CLI menu loop engine
│
├── src/                     # Implementation Source Files (.cpp)
│   ├── User.cpp             
│   ├── PasswordEntry.cpp    
│   ├── Vault.cpp            
│   ├── FileManager.cpp      
│   ├── Authentication.cpp   
│   └── Dashboard.cpp        
│
├── data/                    # Storage Folder
│   ├── user_config.txt      # Authenticated user details (auth XOR encrypted)
│   └── vault_data.txt       # Password database file (vault XOR encrypted)
│
├── CMakeLists.txt           # CMake build system config
├── main.cpp                 # Application entry point
├── README.md                # Project documentation
└── LICENSE                  # Project license
```

---

## Compilation and Run Instructions

Ensure you have a C++17 compiler (`g++` or `clang++`) or `CMake` installed.

### Option A: Standard GCC/Clang Build (Recommended)
Compile the project directly via shell:
```bash
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o Vault
```
Launch the program:
```bash
./Vault
```

### Option B: CMake Build
Create a build directory, configure, and build the project:
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```
Launch the compiled binary:
```bash
./Vault
```

---

## Resume Bullet Points (Tailored for CS Portfolios)

Here are three high-impact resume bullet points tailored for a 3rd-year CS student portfolio:

* **Developed a secure CLI Password Manager in C++17**, decoupling data models, CLI dashboard loops, and storage controllers to implement strict Object-Oriented Design principles and ensure clean separation of concerns.
* **Engineered custom file serialization and symmetric cryptography engines** utilizing byte-level XOR encryption and hex-encoded database files to bypass platform carriage-return discrepancies and secure sensitive credential payload formats.
* **Implemented robust bounds verification and stream handling** in C++, ensuring graceful recovery from invalid indexing vectors and buffer sanitization of standard keyboard inputs.
