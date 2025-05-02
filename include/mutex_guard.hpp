#ifndef MUTEX_GUARD_HPP
#define MUTEX_GUARD_HPP

#include <mutex>

class MutexGuard {
public:
    explicit MutexGuard(std::mutex& m); // Lock during construction
    ~MutexGuard();                      // Release during destruction

    MutexGuard(const MutexGuard&) = delete;
    MutexGuard& operator=(const MutexGuard&) = delete;
    MutexGuard(const MutexGuard&&) = delete;
    MutexGuard& operator=(const MutexGuard&&) = delete;

private:
    std::mutex& m_mutex;
};

#endif
