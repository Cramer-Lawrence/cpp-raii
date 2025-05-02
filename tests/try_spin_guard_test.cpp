#include <gtest/gtest.h>
#include "spin_lock.hpp"
#include "try_spin_guard.hpp"

TEST(TrySpinGuardTest, AquiresLockWhenFree) {
    SpinLock lock;
    TrySpinGuard guard(lock);
    EXPECT_TRUE(guard.ownsLock());
}

TEST(TrySpinGuardTest, FailsWhenAlreadyLocked) {
    SpinLock lock;
    TrySpinGuard g1(lock);
    TrySpinGuard g2(lock);
    EXPECT_TRUE(g1.ownsLock());
    EXPECT_FALSE(g2.ownsLock());
}
