#ifndef TIMED_SPIN_GUARD_HPP
#define TIMED_SPIN_GUARD_HPP

#include "spin_lock.hpp"
#include <chrono>

using Time = std::chrono::high_resolution_clock;

template <typename T, typename U>
class TimedSpinGuard {
public:
    explicit TimedSpinGuard(SpinLock& lock, std::chrono::duration<T, U>& duration) noexcept
        : m_lock{lock} {
        
        const auto endTime = Time::now() + duration;
        while (!m_locked && Time::now() <= endTime)
        {
            if(m_lock.tryLock()) m_locked = true;       
        }
    }
    
    ~TimedSpinGuard() noexcept {
        if (m_locked) m_lock.unlock();
    }

    TimedSpinGuard(const TimedSpinGuard&) = delete;
    TimedSpinGuard& operator=(const TimedSpinGuard&) = delete;

    bool hasLock() const noexcept { return m_locked; }

private:
    SpinLock& m_lock;
    bool m_locked{false};
};

#endif
