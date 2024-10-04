In C++, multithreading often requires access to shared resources, and when multiple threads try to modify or access shared data concurrently, **data races** can occur. To prevent this, you need synchronization mechanisms like `std::mutex` to control access to shared resources. Along with `std::mutex`, C++ provides **RAII (Resource Acquisition Is Initialization)** style wrappers such as `std::lock_guard` and `std::unique_lock` to manage the locking and unlocking of mutexes automatically and safely.

### `std::mutex`
A `std::mutex` (mutual exclusion) is a synchronization primitive used to protect shared data by ensuring that only one thread can access a critical section of the code at a time.

- **lock()**: Acquires the mutex lock. If another thread has already locked the mutex, the calling thread will block until the mutex becomes available.
- **unlock()**: Releases the mutex lock.
- **try_lock()**: Tries to lock the mutex without blocking. Returns `true` if the lock was acquired successfully, `false` otherwise.

### Example: Basic Mutex Usage

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock();  // Lock the mutex before modifying the shared data
        ++counter;
        mtx.unlock();  // Unlock the mutex after modification
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}
```

### Problems with Manual Locking and Unlocking
The manual `mtx.lock()` and `mtx.unlock()` pattern works, but it’s error-prone:
- If an exception is thrown after locking but before unlocking, the mutex remains locked, which can lead to **deadlocks**.
- Forgetting to unlock the mutex can also cause deadlocks.

To avoid such issues, C++ provides **RAII-style** classes like `std::lock_guard` and `std::unique_lock` to automatically manage the lock's lifecycle.

---

### `std::lock_guard`
`std::lock_guard` is a simple wrapper that acquires a mutex when it is constructed and automatically releases it when it goes out of scope (destruction). This guarantees that the mutex is always released, even if exceptions occur within the critical section.

#### Example: Using `std::lock_guard`

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);  // Locks the mutex automatically
        ++counter;
        // Mutex is automatically unlocked when 'lock' goes out of scope
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}
```

### Explanation:
- `std::lock_guard<std::mutex> lock(mtx);` locks the mutex `mtx` when the `lock_guard` object is created.
- The mutex is automatically unlocked when the `lock_guard` goes out of scope (e.g., when the function returns or an exception is thrown).

This pattern ensures exception safety and eliminates the need to manually unlock the mutex.

---

### `std::unique_lock`
`std::unique_lock` is a more flexible RAII-style lock than `std::lock_guard`. It can be locked and unlocked manually, deferred, or moved between scopes. This makes it more powerful, but also slightly more complex.

#### Key Features of `std::unique_lock`:
- **Manual Locking/Unlocking**: You can lock and unlock the mutex manually.
- **Defer Locking**: You can construct the `std::unique_lock` without locking the mutex immediately, then lock it later.
- **Move Semantics**: You can transfer ownership of a lock from one `std::unique_lock` to another.

#### Example: Using `std::unique_lock`

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void increment() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);  // Defer locking the mutex
    lock.lock();  // Manually lock the mutex when needed
    
    for (int i = 0; i < 100000; ++i) {
        ++counter;
    }

    lock.unlock();  // Manually unlock the mutex (optional)
    // Alternatively, the lock will automatically unlock when going out of scope
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}
```

### Explanation:
- `std::unique_lock<std::mutex> lock(mtx, std::defer_lock);` creates the lock but does not acquire the mutex immediately. The mutex is locked later using `lock.lock();`.
- You can manually unlock the mutex using `lock.unlock();`, but the mutex will still automatically unlock when the `unique_lock` object goes out of scope.

### `std::unique_lock` vs `std::lock_guard`:
- **`std::lock_guard`**: Simpler, automatically locks the mutex upon construction and unlocks upon destruction. It cannot unlock and re-lock the mutex.
- **`std::unique_lock`**: More flexible. You can manually lock and unlock the mutex, defer locking, and even transfer the lock between different scopes.

#### Example: Transferring Ownership of `std::unique_lock`

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void task1(std::unique_lock<std::mutex> lock) {
    std::cout << "Thread 1 owns the lock!" << std::endl;
    // Mutex is already locked when passed to task1
}

void task2() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Thread 2 owns the lock and passes it to Thread 1." << std::endl;
    std::thread t(task1, std::move(lock));  // Transfer lock ownership to thread t
    t.join();
}

int main() {
    std::thread t2(task2);
    t2.join();

    return 0;
}
```

### Explanation:
- In `task2`, the mutex `mtx` is locked using `std::unique_lock`.
- Ownership of the lock is transferred to `task1` using `std::move(lock)` when creating the new thread `t`. The mutex remains locked in the new thread, ensuring proper synchronization.

---

### Summary of `mutex`, `lock_guard`, and `unique_lock`

- **`std::mutex`**: Provides basic locking and unlocking for critical sections. Use it to control access to shared resources.
- **`std::lock_guard`**: Automatically acquires a lock when constructed and releases it when destroyed. It’s simple but doesn’t allow deferred or manual unlocking.
- **`std::unique_lock`**: A more flexible locking mechanism that supports deferred locking, manual unlocking, and transferring ownership of the lock.

Would you like more examples, like using condition variables with mutexes for thread synchronization?
