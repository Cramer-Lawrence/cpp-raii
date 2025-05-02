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
- RAII wrapper around `std::mutex`
- Locks on construction, unlocks on destruction
- Prevents forgetting to unlock a mutex
- Equivalent to `std::lock_guard`

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

### 🌀 `SpinGuard`
- RAII wrapper around `SpinLock`
- Locks on construction, unlocks on destruction

```cpp
SpinGuard guard(lock);
// guarantees unlock at scope exit
```

---

### 💡 `TrySpinGuard`
- RAII wrapper around `SpinLock` that attempts a non-blocking lock
- Only enters critical section if the lock was free at construction time

```cpp
TrySpinGuard tryGuard(lock);
if (tryGuard.ownsLock()) {
    // safe access
}
```

---

### ⏱️ `TimedSpinGuard`
- RAII wrapper around `SpinLock` that tries to acquire the lock within a timeout window
- If lock is not acquired before the timeout, it fails gracefully

```cpp
std::chrono::milliseconds timeout{100};
TimedSpinGuard guard(lock, timeout);

if (guard.hasLock()) {
    // acquired within timeout
}
```

---

## 🧪 Tests

We use **GoogleTest** to validate all RAII and lock behaviors.

### ✅ Tested Components:
- `SpinLock`: `tryLock()` succeeds and fails appropriately
- `SpinGuard`: correctly unlocks after scope exit
- `TrySpinGuard`: acquires only when available
- `TimedSpinGuard`: times out if lock is busy

### 🏃‍♂️ To Run the Tests:

From your project root:

```bash
mkdir -p build && cd build
cmake ..
make
ctest --output-on-failure
```

Or add a convenience script like:

```bash
#!/bin/bash
cd build && ctest --output-on-failure
```

---

## 🚧 In Progress

- `TryMutexGuard`, `TimedMutexGuard`
- `ThreadGuard`, `SocketGuard`, `TempFileGuard`
- Microbenchmarks: SpinLock vs std::mutex
- Multithreaded contention simulation tests

---

## 📜 License

MIT License
