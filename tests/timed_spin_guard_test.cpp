#include <gtest/gtest.h>
#include "spin_lock.hpp"
#include "spin_guard.hpp"
#include "timed_spin_guard.hpp"
#include <thread>
#include <chrono>

TEST(TimedSpinGuardTest, AquiresWhenFree) {
    SpinLock lock;
    std::chrono::milliseconds timeout(100);
    TimedSpinGuard guard(lock, timeout);
    EXPECT_TRUE(guard.hasLock());
}

TEST(TimedSpinGuardTest, TimesOutWhenBlocked) {
    SpinLock lock;

    std::thread blocker([&]() {
            SpinGuard guard(lock);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::chrono::milliseconds timeout(50);
    TimedSpinGuard guard(lock, timeout);
    EXPECT_FALSE(guard.hasLock());

    blocker.join();
}
