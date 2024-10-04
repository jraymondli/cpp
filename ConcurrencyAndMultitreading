In C++, threads are used to perform multiple tasks concurrently, which can significantly improve the performance of programs that perform CPU-bound tasks, or allow responsiveness in applications with I/O or network operations. C++11 introduced threading support as part of the Standard Library in `<thread>`, along with other concurrency-related utilities.

### Key Components of Threading in C++
- **`std::thread`**: Represents a single thread of execution.
- **`std::mutex`**: Used to protect shared data from being accessed concurrently by multiple threads.
- **`std::lock_guard`**: A wrapper to ensure that a mutex is properly released after locking.
- **`std::future` and `std::promise`**: Used to pass results between threads and synchronize their execution.
- **`std::async`**: Allows launching asynchronous tasks that automatically manage threads.

### Basic Example: Starting a Thread

Here's an example of creating and running a thread:

```cpp
#include <iostream>
#include <thread>

void print_hello() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(print_hello);  // Start a new thread that runs print_hello
    t.join();                    // Wait for the thread to finish
    return 0;
}
```

### Explanation:
- `std::thread t(print_hello);` creates a new thread and starts executing the `print_hello` function in parallel with the `main` thread.
- `t.join();` ensures that the `main` thread waits for the thread `t` to finish its execution before continuing.

### Example: Passing Arguments to Threads

You can pass arguments to the function that the thread will execute.

```cpp
#include <iostream>
#include <thread>

void print_message(const std::string& message, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << message << std::endl;
    }
}

int main() {
    std::thread t(print_message, "Hello from thread", 5);  // Passing arguments to the thread
    t.join();
    return 0;
}
```

### Explanation:
- `std::thread t(print_message, "Hello from thread", 5);` creates a thread that calls `print_message` with the arguments `"Hello from thread"` and `5`.

### Example: Detaching Threads

You can detach a thread, allowing it to run independently of the `main` thread. Detached threads cannot be joined.

```cpp
#include <iostream>
#include <thread>

void print_hello() {
    std::cout << "Hello from detached thread!" << std::endl;
}

int main() {
    std::thread t(print_hello);
    t.detach();  // Detach the thread, allowing it to run independently
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Give time for the detached thread to finish
    std::cout << "Main thread finished." << std::endl;
    return 0;
}
```

### Explanation:
- `t.detach();` makes the thread run in the background, independent of the `main` thread.
- `std::this_thread::sleep_for(std::chrono::seconds(1));` ensures the main thread doesn’t terminate too early and allows the detached thread to finish its execution.

### Example: Using a Mutex for Synchronization

When multiple threads access shared data, they must be synchronized to prevent data races. `std::mutex` is used to ensure that only one thread can access the critical section of the code at a time.

```cpp
#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);  // Automatically locks and unlocks the mutex
        ++counter;
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
- `std::mutex mtx;` is used to lock access to the shared variable `counter`.
- `std::lock_guard<std::mutex> lock(mtx);` ensures that the mutex is locked when entering the critical section and automatically unlocks when it goes out of scope.

Without the mutex, the two threads would race to increment the counter, causing unpredictable results. With the mutex, only one thread can increment the counter at a time.

### Example: Using `std::async` for Asynchronous Task Execution

`std::async` can be used to run tasks asynchronously without manually managing threads.

```cpp
#include <iostream>
#include <future>

int compute_sum(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> result = std::async(std::launch::async, compute_sum, 5, 10);
    
    std::cout << "Computing sum asynchronously..." << std::endl;
    std::cout << "Result: " << result.get() << std::endl;  // Waits for the result and gets it
    return 0;
}
```

### Explanation:
- `std::async` automatically launches a task in a new thread and returns a `std::future` object to retrieve the result.
- `result.get()` waits for the asynchronous task to finish and retrieves the computed sum.

### Example: Using `std::future` and `std::promise`

`std::future` and `std::promise` are used to pass results between threads and synchronize their execution.

```cpp
#include <iostream>
#include <thread>
#include <future>

void set_value(std::promise<int>& p) {
    std::this_thread::sleep_for(std::chrono::seconds(2));  // Simulate long task
    p.set_value(42);  // Set the promised value
}

int main() {
    std::promise<int> promise;
    std::future<int> result = promise.get_future();

    std::thread t(set_value, std::ref(promise));

    std::cout << "Waiting for result..." << std::endl;
    std::cout << "Result: " << result.get() << std::endl;  // Wait for the promise to be fulfilled

    t.join();
    return 0;
}
```

### Explanation:
- A `std::promise` is used to pass a value from one thread to another.
- `std::future<int> result = promise.get_future();` gets the `future` associated with the `promise`, allowing the main thread to wait for the result.
- The thread `t` sets the value using `p.set_value(42);`, which the main thread retrieves via `result.get()`.

### Example: Thread Pool (Advanced)

Although C++ Standard Library doesn't have built-in thread pools, you can implement a basic one.

```cpp
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    
    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;

    void workerThread();
};

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] { workerThread(); });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers) {
        worker.join();
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push(task);
    }
    condition.notify_one();
}

void ThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) return;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}

int main() {
    ThreadPool pool(4);

    for (int i = 0; i < 10; ++i) {
        pool.enqueue([i] {
            std::cout << "Task " << i << " is being processed by thread " 
                      << std::this_thread::get_id() << std::endl;
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));  // Give some time for threads to complete

    return 0;
}
```

### Explanation:
- A `ThreadPool` is created with 4 worker threads.
- Tasks are enqueued, and worker threads process them in parallel.
- `std::condition_variable` is used to synchronize task execution among the threads.

### Summary
- **`std::thread`**: Allows running tasks in parallel.
- **Synchronization**: Use `std::mutex` and `std::lock_guard` to prevent data races.
- **`std::async`**: Runs tasks asynchronously without managing threads directly.
- **`std::future` and
