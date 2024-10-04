In C++, the `constexpr` keyword is used to declare that a function or variable can be evaluated at compile-time. It was introduced in C++11 and has been significantly expanded in later versions of C++ (like C++14, C++17, and C++20). The primary purpose of `constexpr` is to enable computations to be done at compile-time, improving efficiency and allowing for more optimizations.

### Key Features of `constexpr`
1. **Compile-Time Evaluation**: If possible, the expression marked with `constexpr` will be evaluated at compile-time, making the result available during compilation.
2. **Immutable by Default**: Variables declared as `constexpr` are implicitly `const`.
3. **Expanded in C++14 and Later**: C++14 relaxed some restrictions, allowing more complex `constexpr` functions (e.g., loops and conditionals).

### Basic Usage of `constexpr`

#### 1. **`constexpr` Variables**

You can use `constexpr` to declare constant values that must be evaluated at compile-time.

```cpp
constexpr int max_size = 100; // Must be known at compile-time

int arr[max_size]; // Valid, as array size is known at compile-time
```

#### 2. **`constexpr` Functions**

A `constexpr` function can be evaluated at compile-time if its arguments are compile-time constants. If invoked with non-constant values, it will behave like a regular function at runtime.

```cpp
constexpr int square(int x) {
    return x * x;
}

int main() {
    constexpr int result = square(5); // Compile-time evaluation
    int non_const_result = square(7); // Runtime evaluation
}
```

In this example, `square(5)` is evaluated at compile-time, while `square(7)` is evaluated at runtime because `7` is passed in as a non-constant variable.

#### 3. **Conditional Expressions in `constexpr`**

You can use conditionals inside `constexpr` functions to allow for more complex compile-time computations.

```cpp
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

int main() {
    constexpr int fact5 = factorial(5);  // Compile-time evaluation
    int fact6 = factorial(6);            // Runtime evaluation
}
```

This recursive function computes the factorial of a number at compile-time if the input is constant, otherwise at runtime.

#### 4. **`constexpr` in C++14 and C++17**

C++14 relaxed restrictions on `constexpr` functions, allowing the use of loops, local variables, and more complex logic, making `constexpr` much more powerful.

```cpp
constexpr int sum_to_n(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

int main() {
    constexpr int sum10 = sum_to_n(10); // Compile-time
    int sum20 = sum_to_n(20);           // Runtime
}
```

In this example, a loop is used inside a `constexpr` function, which was not allowed in C++11 but is permitted starting from C++14.

#### 5. **`constexpr` and User-Defined Types (Classes)**

You can also use `constexpr` with class constructors, allowing objects of such types to be created at compile-time.

```cpp
struct Point {
    int x, y;

    constexpr Point(int x, int y) : x(x), y(y) {}

    constexpr int getX() const { return x; }
};

int main() {
    constexpr Point p(10, 20);  // Compile-time object creation
    static_assert(p.getX() == 10, "X should be 10"); // Static assertion
}
```

In this example, the `Point` class has a `constexpr` constructor, which allows `p` to be constructed at compile-time.

### `constexpr` vs `const`

- **`const`**: Declares a value that cannot be modified but can be determined at runtime.
- **`constexpr`**: Requires that the value is evaluated at compile-time (if possible).

Example:

```cpp
const int runtime_const = time(nullptr); // Initialized at runtime
constexpr int compile_time_const = 10;   // Must be evaluated at compile-time
```

### Summary of `constexpr` Rules:
1. **C++11**:
   - Only single-statement functions allowed.
   - No loops, conditionals, or local variables.

2. **C++14**:
   - Functions can contain multiple statements.
   - Loops, conditionals, and local variables are allowed.

3. **C++17**:
   - Added support for `if constexpr`, enabling compile-time branching.

4. **C++20**:
   - Introduced even more complex features like `constexpr` destructors.

### `if constexpr` in C++17

Starting from C++17, the `if constexpr` statement allows compile-time branching:

```cpp
template <typename T>
void foo(T t) {
    if constexpr (std::is_integral<T>::value) {
        std::cout << "Integral type\n";
    } else {
        std::cout << "Non-integral type\n";
    }
}
```

In this example, the branch is resolved at compile-time based on the type `T`.

---

Would you like more examples or further details on specific `constexpr` features?
