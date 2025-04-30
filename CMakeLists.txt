cmake_minimum_required(VERSION 3.14)
project(cpp-raii)

# 1) Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2) Add Executable
add_executable(cpp-raii
    src/main.cpp
    src/file_guard.cpp
)



# 3) Includes
target_include_directories(cpp-raii
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)
