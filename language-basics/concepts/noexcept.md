In C++, `noexcept` is a specifier that indicates whether a function can throw exceptions. It was introduced in C++11 to help developers explicitly declare that a function does not throw exceptions, enabling better performance optimizations by the compiler.

### Key Points of `noexcept`
1. **Guarantees No Exceptions**: Declaring a function as `noexcept` tells the compiler and the programmer that the function will not throw any exceptions. If an exception is thrown from a `noexcept` function, the program will terminate via `std::terminate()`.
2. **Performance Optimization**: When the compiler knows a function is `noexcept`, it can generate more optimized code since it doesn't need to account for exception handling mechanisms.
3. **Conditional `noexcept`**: You can also use a conditional form of `noexcept` where the `noexcept` guarantee depends on some condition.

### Syntax

```cpp
// Declare a function as noexcept
void foo() noexcept { /* function body */ }
```

- A function declared with `noexcept` cannot throw any exceptions. If an exception is thrown from such a function, the program will call `std::terminate()` and exit.

### Examples of Using `noexcept`

#### 1. **Basic `noexcept` Function**
A function that doesn't throw exceptions can be marked as `noexcept`.

```cpp
void print() noexcept {
    std::cout << "This function is guaranteed not to throw exceptions.\n";
}
```

Here, the function `print()` is guaranteed not to throw any exceptions.

#### 2. **Conditional `noexcept`**
You can use the conditional version of `noexcept` by passing a condition (typically a constexpr expression) that evaluates to `true` or `false` at compile time.

```cpp
template <typename T>
void swap(T& a, T& b) noexcept(noexcept(T(std::declval<T&>()))) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}
```

In this example, the `swap` function is declared `noexcept` only if the move constructor and assignment operator of `T` are `noexcept`. This ensures that `swap` will only be considered `noexcept` if the underlying operations are guaranteed not to throw exceptions.

#### 3. **Checking if a Function is `noexcept`**
You can use the `noexcept` operator to check if a function is `noexcept` at compile-time. It returns a boolean value (`true` or `false`).

```cpp
void may_throw() {
    throw std::runtime_error("Error");
}

void no_throw() noexcept {
    // No exceptions thrown here
}

int main() {
    std::cout << std::boolalpha;
    std::cout << "may_throw() noexcept? " << noexcept(may_throw()) << "\n";  // Output: false
    std::cout << "no_throw() noexcept? " << noexcept(no_throw()) << "\n";    // Output: true
}
```

Here, `noexcept(may_throw())` returns `false` because `may_throw()` can throw an exception, while `noexcept(no_throw())` returns `true` because `no_throw()` is marked `noexcept`.

#### 4. **`noexcept` with Move Constructor**
`noexcept` is often used with move constructors and move assignment operators to guarantee that these operations won't throw exceptions, which is important for standard containers like `std::vector`.

```cpp
struct MyClass {
    MyClass() = default;
    MyClass(const MyClass&) = default;
    MyClass(MyClass&&) noexcept = default;  // Move constructor marked as noexcept
};

int main() {
    MyClass obj1, obj2;
    obj2 = std::move(obj1);  // Optimized move if noexcept
}
```

Marking the move constructor as `noexcept` allows certain optimizations, such as avoiding unnecessary copies when resizing containers.

#### 5. **Interaction with `std::vector` and Other Containers**
Standard library containers like `std::vector` rely on `noexcept` to perform optimizations. If the move constructor of a type is `noexcept`, `std::vector` can use moves instead of copies when resizing or re-allocating memory, improving performance.

```cpp
#include <vector>
#include <iostream>

struct NoexceptClass {
    NoexceptClass() = default;
    NoexceptClass(NoexceptClass&&) noexcept { std::cout << "Move constructor (noexcept)\n"; }
};

struct MayThrowClass {
    MayThrowClass() = default;
    MayThrowClass(MayThrowClass&&) { std::cout << "Move constructor (may throw)\n"; }
};

int main() {
    std::vector<NoexceptClass> vec1;
    vec1.push_back(NoexceptClass());  // Uses noexcept move constructor

    std::vector<MayThrowClass> vec2;
    vec2.push_back(MayThrowClass());  // May fallback to copy if move is not noexcept
}
```

In this example, the `NoexceptClass` will use the move constructor for efficient operations, while `MayThrowClass` might use a copy operation if the move constructor is not guaranteed to be `noexcept`.

### `noexcept` vs `throw()`
- **`noexcept`**: Introduced in C++11, it is the modern way to specify that a function does not throw exceptions. It is more powerful because it allows conditional expressions.
- **`throw()`**: A deprecated syntax from older C++ standards to specify that a function doesn’t throw exceptions. It was less flexible and removed in C++17.

Example of deprecated `throw()`:
```cpp
void old_func() throw(); // Deprecated, replaced by noexcept
```

### Summary of `noexcept`
- **Use `noexcept`** to declare that a function won’t throw exceptions.
- **Conditional `noexcept`** is useful for functions where the exception guarantee depends on the template parameter or some other condition.
- It **helps with performance optimizations**, especially in move operations in STL containers.
- **Mark move constructors and assignment operators `noexcept`** to enable optimizations in standard containers.

Would you like more examples on specific use cases of `noexcept`?
