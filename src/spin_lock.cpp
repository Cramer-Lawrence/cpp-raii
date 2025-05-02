#include "spin_lock.hpp"

void SpinLock::lock() noexcept {
    while (m_locked.test_and_set(std::memory_order_acquire)) {
        m_locked.wait(true, std::memory_order_relaxed);
    }
}

void SpinLock::unlock() noexcept {
    m_locked.clear(std::memory_order_release);
    m_locked.notify_one();
}

bool SpinLock::tryLock() noexcept {
    return !m_locked.test_and_set(std::memory_order_acquire);
}
