#ifndef SPIN_GUARD_HPP
#define SPIN_GUARD_HPP

#include "spin_lock.hpp"

class SpinGuard {
public:
    explicit SpinGuard(SpinLock& lock) noexcept;
    ~SpinGuard();

    SpinGuard(const SpinGuard&) = delete;
    SpinGuard& operator=(const SpinGuard&) = delete;

private:
    SpinLock& m_lock;
    bool m_hasLock {false};
};

#endif
