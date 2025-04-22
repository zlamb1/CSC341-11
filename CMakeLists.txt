cmake_minimum_required(VERSION 3.28.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable Clang-Tidy
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

project(CSC341_11 VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(src/app)