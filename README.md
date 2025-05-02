# cpp-raii

A modern C++20 project demonstrating safe, exception-proof resource management using the **RAII** (Resource Acquisition Is Initialization) design pattern.

This project includes reusable utilities for handling files, mutexes, and custom spinlocks with clear ownership semantics and minimal runtime overhead.

---

## 🔐 What is RAII?

**RAII (Resource Acquisition Is Initialization)** is a C++ programming principle where resource management is tied to object lifetime.  
Resources (like file handles, locks, and memory) are acquired in a constructor and released in the destructor — ensuring safety, even during exceptions.

---

## 📦 Components

### 📁 `FileGuard`
- Wraps a C-style `FILE*` (via `fopen`)
- Automatically closes the file with `fclose()` on destruction
- Prevents file handle leaks, even if exceptions occur
- Move-only, non-copyable

```cpp
FileGuard file("log.txt", "a");
std::fprintf(file.get(), "Hello, RAII!\n");
```

---

### 🔒 `MutexGuard`
- RAII wrapper around a `std::mutex`
- Locks on construction, unlocks on destruction
- Prevents forgetting to unlock a mutex
- Equivalent to `std::lock_guard` (reimplemented for understanding)

```cpp
MutexGuard guard(my_mutex);
// critical section
```

---

### 🔁 `SpinLock`
- A low-level **busy-wait lock** built with `std::atomic_flag`
- Uses C++20 `wait()`/`notify_one()` to reduce CPU spinning
- Useful for short, high-frequency critical sections where OS mutexes are too heavyweight

```cpp
SpinLock lock;
lock.lock();
// critical section
lock.unlock();
```

---

### 🧠 `SpinGuard` and `TrySpinGuard`

These are RAII-style wrappers around a shared `SpinLock` implementation:

- `SpinGuard` **blocks** until the lock is acquired
- `TrySpinGuard` attempts to acquire the lock **without blocking**, allowing conditional logic if the lock isn't immediately available

Both guard types use the same `SpinLock` class, promoting **code reuse**, **clean separation of concerns**, and **modular synchronization logic**. This pattern mirrors the philosophy behind `std::lock_guard` and `std::unique_lock`.

```cpp
SpinGuard guard(lock); // always acquires the lock

TrySpinGuard tryGuard(lock);
if (tryGuard.ownsLock()) {
    // safe access
} else {
    // fallback logic
}
```
---

## 🧪 Why This Matters

- Helps avoid common concurrency bugs (like forgetting to unlock or double-closing)
- Demonstrates best practices for safe resource management
- Forms the foundation for systems programming, low-latency design, and quant/dev work

---

## 🚧 In Progress

- `ThreadGuard`, `SocketGuard`, `TempFileGuard`, etc.
- GoogleTest-based unit tests
- Benchmarks comparing spinlocks vs std::mutex
  
---

## 📜 License

MIT License

