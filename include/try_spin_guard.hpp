#ifndef TRY_SPIN_GUARD_HPP
#define TRY_SPIN_GUARD_HPP

#include "spin_lock.hpp"

class TrySpinGuard {
public:
    explicit TrySpinGuard(SpinLock& lock) noexcept;
    ~TrySpinGuard();

    TrySpinGuard(const TrySpinGuard&) = delete;
    TrySpinGuard& operator=(const TrySpinGuard&) = delete;

    bool ownsLock() const noexcept { return m_locked; }

private:
    SpinLock& m_lock;
    bool m_locked{false};
};

#endif // TRY_SPIN_GUARD_HPP
