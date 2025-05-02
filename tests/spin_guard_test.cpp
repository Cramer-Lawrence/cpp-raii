#include <gtest/gtest.h>
#include "spin_lock.hpp"
#include "spin_guard.hpp"

TEST(SpinGuardTest, LocksAndUnlocks) {
    SpinLock lock;
    {
        SpinGuard guard(lock);
        EXPECT_TRUE(true);
    }
    EXPECT_TRUE(lock.tryLock());
    lock.unlock();
}
