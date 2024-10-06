Object lifetime management refers to the process of controlling the creation, use, and destruction of objects in a programming environment, ensuring that resources are allocated and deallocated correctly. In C++, this is a critical topic, as it directly impacts the performance, correctness, and safety of a program.

### Key Concepts

1. **Construction and Destruction:**
   - **Constructor**: Called when an object is created. It initializes the object's state.
   - **Destructor**: Called when an object goes out of scope or is explicitly deleted. It is responsible for cleaning up resources like dynamic memory or file handles.

   Example:
   ```cpp
   class MyClass {
   public:
       MyClass() { 
           std::cout << "Constructor called" << std::endl; 
       }
       ~MyClass() { 
           std::cout << "Destructor called" << std::endl; 
       }
   };

   int main() {
       MyClass obj;  // Constructor is called here
   }  // Destructor is called when obj goes out of scope
   ```

2. **Stack vs. Heap Allocation:**
   - **Stack-allocated objects**: Created automatically and destroyed when the function they are in returns or the object goes out of scope. This is usually more efficient.
   - **Heap-allocated objects**: Created using `new` and destroyed using `delete`. You need to manually manage their lifetime, or else you risk memory leaks.

   Example:
   ```cpp
   MyClass* obj = new MyClass();  // Created on the heap
   delete obj;  // Manually delete it to free memory
   ```

3. **RAII (Resource Acquisition Is Initialization):**
   - RAII is a programming idiom that ties the lifetime of resources (like memory, file handles, etc.) to the lifetime of objects. When an object is created, it acquires the necessary resources, and when it is destroyed, the resources are automatically released.
   - C++ standard library uses RAII extensively (e.g., `std::unique_ptr`, `std::lock_guard`).

   Example:
   ```cpp
   {
       std::unique_ptr<MyClass> obj = std::make_unique<MyClass>();
       // No need to call delete, destructor will be automatically called
   }  // obj goes out of scope here and memory is freed
   ```

4. **Smart Pointers:**
   - **`std::unique_ptr`**: Manages a resource and ensures that it is deleted when the `unique_ptr` goes out of scope. No copying is allowed, ensuring unique ownership.
   - **`std::shared_ptr`**: Allows multiple pointers to share ownership of a resource. The resource is only freed when the last `shared_ptr` is destroyed.
   - **`std::weak_ptr`**: A non-owning reference to an object managed by `std::shared_ptr` to prevent circular dependencies.

   Example:
   ```cpp
   std::shared_ptr<MyClass> shared1 = std::make_shared<MyClass>();
   std::shared_ptr<MyClass> shared2 = shared1;  // Resource shared
   ```

5. **Move Semantics:**
   - Move semantics optimize resource management by transferring ownership rather than copying. This is useful for temporary objects or large resources like dynamic arrays.
   - **Move constructor** and **move assignment operator** are used to "steal" resources from one object to another without duplicating them.

   Example:
   ```cpp
   MyClass obj1;
   MyClass obj2 = std::move(obj1);  // Move resources from obj1 to obj2
   ```

6. **Avoiding Dangling Pointers:**
   Dangling pointers occur when a pointer still references a memory location that has been freed. To avoid this:
   - Use smart pointers (`std::unique_ptr`, `std::shared_ptr`) to handle deallocation automatically.
   - Ensure proper deletion of heap-allocated objects.

By understanding and applying these principles, you can effectively manage object lifetimes, avoid resource leaks, and write safer, more efficient C++ code.
