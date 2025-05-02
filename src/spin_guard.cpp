#include "spin_guard.hpp"

SpinGuard::SpinGuard(SpinLock& lock) noexcept 
    :m_lock{lock} {
        m_lock.lock();
        m_hasLock = true;
}

SpinGuard::~SpinGuard() {
    if (m_hasLock) m_lock.unlock();
}
