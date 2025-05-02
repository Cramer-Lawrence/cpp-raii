cmake_minimum_required(VERSION 3.14)
project(cpp-raii)

# set c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add include path
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# googletest setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# build the raii library
add_library(raii_lib
    src/file_guard.cpp
    src/mutex_guard.cpp
    src/spin_lock.cpp
    src/spin_guard.cpp
    src/try_spin_guard.cpp
)

target_include_directories(raii_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(cpp-raii
    src/main.cpp
)

target_link_libraries(cpp-raii
    raii_lib
)

add_subdirectory(tests)
