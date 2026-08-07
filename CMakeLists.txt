cmake_minimum_required(VERSION 3.15)
project(Vault VERSION 1.0.0 LANGUAGES CXX)

# Set C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Find all source files under src/
file(GLOB SRC_FILES src/*.cpp)

# Define executable targeting main.cpp and all sources in src/
add_executable(Vault main.cpp ${SRC_FILES})
