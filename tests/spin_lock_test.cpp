#include <gtest/gtest.h>
#include "spin_lock.hpp"

TEST(SpinLockTest, TryLockSucceeds) {
    SpinLock lock;
    EXPECT_TRUE(lock.tryLock());
    lock.unlock();
}

TEST(SpinLockTest, TryLockFailsWhenLocked) {
    SpinLock lock;
    EXPECT_TRUE(lock.tryLock());
    EXPECT_FALSE(lock.tryLock());
    lock.unlock();
}
