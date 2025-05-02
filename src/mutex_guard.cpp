#include "mutex_guard.hpp"

MutexGuard::MutexGuard(std::mutex& m)
    : m_mutex{m} {
    m_mutex.lock();
}

MutexGuard::~MutexGuard() {
    m_mutex.unlock();
}
