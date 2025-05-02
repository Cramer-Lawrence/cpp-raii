enable_testing()

add_executable(raii_tests
    spin_lock_test.cpp
    spin_guard_test.cpp
    try_spin_guard_test.cpp
    timed_spin_guard_test.cpp
)

target_link_libraries(raii_tests
    gtest_main
    raii_lib
)

include(GoogleTest)

gtest_discover_tests(raii_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DISCOVERY_TIMEOUT 10
)
