#include "file_guard.hpp"
#include <iostream>


int main() {

    try {
        FileGuard fg("example.txt", "w");
        std::fprintf(fg.get(), "Hello RAII world!\n");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}

