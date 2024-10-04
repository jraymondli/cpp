### Conditional Variables in C++

In multithreaded programming, **condition variables** allow threads to efficiently **wait** for some condition to be true before proceeding. They are used to block one or more threads until another thread signals that a condition has changed (for example, that some shared data has been modified).

A condition variable works in conjunction with a **mutex** to ensure that the shared data is accessed safely. Threads typically wait for a condition to be met and are notified (or "signaled") when the condition becomes true.

#### Key Components
- **`std::condition_variable`**: A synchronization primitive that blocks a thread until notified by another thread.
- **`wait()`**: Makes a thread wait for a condition to be met.
- **`notify_one()`**: Wakes up one thread waiting on the condition variable.
- **`notify_all()`**: Wakes up all threads waiting on the condition variable.

### Basic Usage of `std::condition_variable`

1. **One or more threads wait** on the condition variable.
2. Another thread **signals** or **notifies** the waiting threads when a certain condition is met.
3. Condition variables are always used with a `std::mutex` to ensure that waiting and notifying occur in a thread-safe manner.

### Example: Simple Producer-Consumer Problem

In this classic example, one thread (the producer) generates data and notifies another thread (the consumer) when the data is ready to be processed.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::queue<int> dataQueue;  // Shared data
std::mutex mtx;
std::condition_variable cv;
bool done = false;  // Signals when producer is done producing data

// Producer function
void producer() {
    for (int i = 1; i <= 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simulate work
        std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex
        dataQueue.push(i);  // Add data to the shared queue
        std::cout << "Produced: " << i << std::endl;
        cv.notify_one();  // Notify the consumer that data is available
    }

    // Indicate that the producer is done
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();  // Notify the consumer that production is finished
}

// Consumer function
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex

        // Wait until notified and ensure there's data or producer is done
        cv.wait(lock, [] { return !dataQueue.empty() || done; });

        if (!dataQueue.empty()) {
            int value = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << value << std::endl;
        } else if (done) {
            break;  // Exit if production is done and queue is empty
        }
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();

    return 0;
}
```

### Explanation:
- **Producer Thread**:
  - Produces data by pushing values into the shared queue (`dataQueue`).
  - After producing each item, it calls `cv.notify_one()` to wake the consumer thread.
  - After the last item, it sets `done = true` and calls `cv.notify_all()` to signal that the producer is finished.

- **Consumer Thread**:
  - Waits for data by calling `cv.wait(lock, predicate)` inside a loop.
  - The predicate is a lambda function that returns true if the queue has data or if the producer has finished producing.
  - If the queue has data, the consumer consumes it. If no more data is coming and the queue is empty, the consumer exits.

### Detailed Breakdown of Key Components:

#### `std::condition_variable::wait`
- `cv.wait(lock, predicate);`:
  - The **`wait()`** function blocks the thread until the predicate becomes true.
  - The mutex is automatically unlocked while waiting, and then re-locked once the thread is awakened.
  - The **predicate** is a lambda function that checks if the condition is true (for example, if the queue is not empty or the producer has finished).

#### `std::condition_variable::notify_one`
- `cv.notify_one();`:
  - This function wakes up **one thread** that is waiting on the condition variable. If multiple threads are waiting, only one of them is chosen to be awakened.

#### `std::condition_variable::notify_all`
- `cv.notify_all();`:
  - This function wakes up **all threads** that are waiting on the condition variable. This is useful when multiple threads may need to respond to a change in the condition.

---

### Example: Thread Pool Using Condition Variables

Another useful application of condition variables is in a **thread pool**. Here, a thread pool assigns tasks to worker threads from a queue. If there are no tasks, workers wait until a new task is enqueued.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    
    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> workers;           // Worker threads
    std::queue<std::function<void()>> tasks;    // Task queue
    std::mutex queueMutex;                      // Protects task queue
    std::condition_variable cv;                 // Condition variable for synchronization
    bool stop;                                  // Signal to stop the thread pool

    void workerThread();
};

// Constructor: Initializes the thread pool and creates worker threads
ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] { workerThread(); });
    }
}

// Destructor: Stops all worker threads and joins them
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;  // Set stop signal
    }
    cv.notify_all();  // Wake up all workers
    for (std::thread &worker : workers) {
        worker.join();  // Join all worker threads
    }
}

// Function to add a new task to the pool
void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push(task);  // Add task to the queue
    }
    cv.notify_one();  // Notify one waiting worker
}

// Worker thread function: Fetch tasks from the queue and execute them
void ThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            // Wait for tasks or stop signal
            cv.wait(lock, [this] { return !tasks.empty() || stop; });

            if (stop && tasks.empty())
                return;  // Exit thread if stopping and no tasks left

            task = std::move(tasks.front());
            tasks.pop();
        }
        task();  // Execute the task
    }
}

int main() {
    ThreadPool pool(4);  // Create a thread pool with 4 worker threads

    // Enqueue 8 tasks
    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i] {
            std::cout << "Task " << i << " is being processed by thread "
                      << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));  // Wait for tasks to finish

    return 0;
}
```

### Explanation:
- **ThreadPool**: A pool of worker threads that wait for tasks to be enqueued. If the queue is empty, worker threads block on the condition variable `cv`.
- **Worker threads**: Call `cv.wait(lock, predicate);` to wait for new tasks. They wake up when `cv.notify_one()` is called after a new task is added.
- **Task Queue**: Tasks are stored in a queue and distributed among the worker threads.
- **Graceful Shutdown**: When the thread pool is destroyed, it signals the workers to stop by setting `stop = true;` and calling `cv.notify_all()`.

---

### Summary
- **Condition variables** allow threads to wait until a specific condition is met.
- They are used in combination with **mutexes** to ensure thread-safe access to shared data.
- **Key Functions**:
  - `wait(lock, predicate)`: Waits until the condition is met.
  - `notify_one()`: Wakes up one waiting thread.
  - `notify_all()`: Wakes up all waiting threads.
  
Would you like to explore more advanced use cases for condition variables, such as multi-stage synchronization between threads?
