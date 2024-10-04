### Introduction to C++ Lambda Expressions

In C++, **lambda expressions** provide a concise way to define anonymous (unnamed) functions directly within your code. Lambdas are particularly useful when you need small, short-lived functions that are used only in a limited scope, such as in algorithms or event handling. They were introduced in C++11 and have evolved with newer versions of C++.

A lambda expression can capture variables from the surrounding scope, execute code, and return results, all in a compact syntax.

### Syntax of Lambda Expressions

The basic syntax of a lambda expression is:

```cpp
[capture](parameters) -> return_type {
    // function body
};
```

- **Capture**: Specifies how variables from the surrounding scope should be captured (by value or by reference).
- **Parameters**: Specifies input parameters, like any other function.
- **Return Type** (optional): Specifies the return type of the lambda. If omitted, the compiler tries to deduce the return type automatically.
- **Function Body**: Contains the code to be executed when the lambda is called.

#### Example: Simple Lambda Expression

```cpp
auto myLambda = []() {
    std::cout << "Hello from a lambda!" << std::endl;
};

int main() {
    myLambda(); // Calling the lambda
    return 0;
}
```

### Capture Clause

The capture clause `[capture]` allows lambdas to capture variables from the surrounding scope. There are several ways to capture variables:

- **Capture by value (`[x]`)**: Captures the variable by making a copy.
- **Capture by reference (`[&x]`)**: Captures the variable by reference, allowing modification.
- **Capture all by value (`[=]`)**: Captures all variables in the surrounding scope by value.
- **Capture all by reference (`[&]`)**: Captures all variables by reference.
- **Mixed capture (`[x, &y]`)**: You can mix value and reference captures for specific variables.

#### Example: Capture by Value and Reference

```cpp
int x = 10;
int y = 20;

auto lambda = [x, &y]() {
    // x is captured by value, y is captured by reference
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    y = 50;  // modifying y, since it's captured by reference
};

lambda();
std::cout << "y after lambda = " << y << std::endl;
```

### Returning Values from a Lambda

By default, the compiler deduces the return type of the lambda from the `return` statement. However, you can explicitly specify the return type using the `-> return_type` syntax.

#### Example: Lambda with Return Type

```cpp
auto add = [](int a, int b) -> int {
    return a + b;
};

int result = add(3, 4);  // result = 7
std::cout << "Result: " << result << std::endl;
```

If the lambda is a single-expression function, the return type can often be automatically deduced by the compiler, so specifying the return type is not necessary in simple cases.

### Lambda with Parameters

Lambdas can take parameters, just like regular functions. These parameters are passed when the lambda is invoked.

#### Example: Lambda with Parameters

```cpp
auto multiply = [](int a, int b) {
    return a * b;
};

int result = multiply(5, 6);  // result = 30
std::cout << "Result: " << result << std::endl;
```

### Lambda in Algorithms

Lambdas are often used with STL algorithms such as `std::for_each`, `std::transform`, and `std::sort`, where you need to pass a small function to manipulate data.

#### Example: Using Lambda with `std::for_each`

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Using lambda to print each element
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n << " ";
    });

    return 0;
}
```

### Mutable Lambdas

By default, lambdas capture variables by value, making the captured variables immutable within the lambda. However, you can modify captured values by marking the lambda as `mutable`.

#### Example: Mutable Lambda

```cpp
int count = 0;

auto increment = [count]() mutable {
    count++;  // modifying captured value
    std::cout << "Count inside lambda: " << count << std::endl;
};

increment();
std::cout << "Count outside lambda: " << count << std::endl;  // Original count remains unchanged
```

In this case, `count` is modified only inside the lambda, but the original `count` outside the lambda remains unchanged because it was captured by value.

### Generic Lambdas (C++14 and Later)

Starting with C++14, lambdas can be made **generic** by using `auto` in the parameter list. This allows the lambda to accept parameters of any type.

#### Example: Generic Lambda

```cpp
auto genericAdd = [](auto a, auto b) {
    return a + b;
};

int intResult = genericAdd(3, 4);       // Works with integers
double doubleResult = genericAdd(2.5, 3.5);  // Works with doubles

std::cout << "intResult: " << intResult << std::endl;
std::cout << "doubleResult: " << doubleResult << std::endl;
```

### Summary

- **Lambda expressions** are anonymous functions that can capture variables from their surrounding scope.
- **Capture clause** allows capturing variables by value or by reference.
- Lambdas are commonly used with **STL algorithms** and for quick, localized function definitions.
- **Mutable lambdas** allow modifying captured values even when captured by value.
- **Generic lambdas** (C++14 and later) can accept arguments of any type using `auto`.

Lambdas are a powerful feature of modern C++, especially useful when you need a quick, simple function without the overhead of defining a full function.
