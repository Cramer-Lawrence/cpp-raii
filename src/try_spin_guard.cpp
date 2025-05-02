#include "try_spin_guard.hpp"

TrySpinGuard::TrySpinGuard(SpinLock& lock) noexcept 
    : m_lock{lock} {
    m_locked = m_lock.tryLock();
}

TrySpinGuard::~TrySpinGuard() {
    if (m_locked) m_lock.unlock();
}
