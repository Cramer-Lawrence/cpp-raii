#ifndef SPIN_LOCK_HPP
#define SPIN_LOCK_HPP

#include <atomic>

class SpinLock {
public:
    SpinLock() = default;
    
    void lock() noexcept;
    void unlock() noexcept;
    bool tryLock() noexcept;

private:
    std::atomic_flag m_locked {};
};

#endif
