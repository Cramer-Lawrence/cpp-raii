#include "file_guard.hpp"
#include <stdexcept>

FileGuard::FileGuard(const std::string& path, const std::string& mode)
    : m_file(std::fopen(path.c_str(), mode.c_str())) {

    if (!m_file) {
        throw std::runtime_error("Failed to open file: " + path);
    }
}

FileGuard::FileGuard(FileGuard&& other) noexcept
    : m_file(other.m_file) {

    other.m_file = nullptr;
}

FileGuard& FileGuard::operator=(FileGuard&& other) noexcept {

    if (this != &other) {    
        if (m_file) std::fclose(m_file);
        m_file = other.m_file;
        other.m_file = nullptr;
    }

    return *this;
}

FileGuard::~FileGuard() {
    
    if (m_file) {
        std::fclose(m_file);
    }
}
