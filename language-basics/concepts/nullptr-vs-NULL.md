In C++, both `nullptr` and `NULL` represent null pointers, but there are important differences between them. `nullptr` was introduced in C++11 to address some of the limitations of `NULL` and provide better type safety.

### Key Differences

1. **Type Safety**:
   - **`nullptr`**: It is a keyword introduced in C++11, and it has a specific type: `std::nullptr_t`. It can only be used to represent null pointers.
   - **`NULL`**: It is typically defined as `0` or `((void*)0)` in C, and it doesn't have a specific type. This can lead to ambiguity and errors in certain situations because `NULL` is just an integer constant with a value of zero.

2. **Explicitly a Null Pointer**:
   - **`nullptr`**: It is explicitly a null pointer. There is no ambiguity when passing `nullptr` to a function or comparing it to a pointer. The compiler knows that `nullptr` represents a pointer type.
   - **`NULL`**: Since `NULL` is just `0`, it can cause ambiguity when used in overloaded functions, where the type of `0` might not clearly indicate whether it's an integer or a pointer.

3. **Function Overloading**:
   - With **`nullptr`**, the compiler can correctly resolve overloaded functions based on whether you’re passing a pointer or an integer.
   
   Example of ambiguity with `NULL`:
   ```cpp
   void f(int i) { std::cout << "int overload"; }
   void f(void* p) { std::cout << "void* overload"; }

   f(NULL);   // Calls f(int), because NULL is just 0 (an integer)
   f(nullptr); // Calls f(void*), because nullptr is a pointer
   ```

4. **Usage in Modern C++**:
   - **`nullptr`**: Preferred in modern C++ code because it avoids the ambiguities of `NULL` and provides clear type safety.
   - **`NULL`**: Mainly kept for backward compatibility with C and older C++ codebases. In modern C++ code, `nullptr` is the better choice.

### Example

```cpp
int* p1 = NULL;       // NULL is just 0 (potentially error-prone)
int* p2 = nullptr;    // nullptr is explicitly a null pointer

if (p1 == p2) {
    std::cout << "Both are null pointers";
}
```

### Summary
- **`nullptr`**: Introduced in C++11, it has its own type (`std::nullptr_t`), provides better type safety, and is preferred in modern C++ code.
- **`NULL`**: Historically used, defined as `0` in C/C++, but can lead to ambiguity and type-safety issues. It is mostly used for backward compatibility.

In modern C++, it is recommended to use `nullptr` for null pointers. Would you like to see more examples or have specific questions about using `nullptr`?
