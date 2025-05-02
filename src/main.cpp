#include "spin_lock.hpp"
#include "timed_spin_guard.hpp"
#include <iostream>


int main() {

    SpinLock sL{};
    std::chrono::duration<int, std::ratio<1, 1000>> timeOut {1000};
    TimedSpinGuard tSG{sL, timeOut};

    if (tSG.hasLock()){
        std::cout << "Lock Obtained!" << std::endl;
    } else {
        std::cout << "No lock..." << std::endl;
    }
    
    return 0;
}

