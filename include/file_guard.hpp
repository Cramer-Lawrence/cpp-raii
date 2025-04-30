#ifndef FILE_GUARD_HPP
#define FILE_GUARD_HPP

#include <cstdio>
#include <string>

class FileGuard {
public:
    FileGuard(const std::string& path, const std::string& mode);

    // Delete the copy ctor and opr
    FileGuard(const FileGuard&) = delete;
    FileGuard& operator=(const FileGuard&) = delete;

    // Create Move ctor and opr
    FileGuard(FileGuard&& other) noexcept;
    FileGuard& operator=(FileGuard&& other) noexcept;

    // Make sure to close the file
    ~FileGuard();

    FILE* get() const { return m_file; }

private:
    FILE* m_file;
};

#endif // FILE_GUARD_HPP
