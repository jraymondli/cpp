### `try-catch-throw` in C++

In C++, the **exception handling mechanism** is used to handle errors and unexpected situations in a controlled way. The keywords involved in exception handling are:

- **`throw`**: Used to signal an exception, i.e., to throw an error.
- **`try`**: Block of code where exceptions might occur.
- **`catch`**: Block of code that handles the exception.

### How It Works:
1. **Throwing an Exception**: When an error occurs, an exception is "thrown" using the `throw` keyword. This can be any object, typically an error message or some form of error data.
2. **Try Block**: The `try` block contains code that might throw an exception. It attempts to execute this code.
3. **Catch Block**: If an exception is thrown, control is transferred to the `catch` block. The `catch` block then handles the exception, preventing the program from crashing.

### Syntax:
```cpp
try {
    // Code that might throw an exception
} catch (exception_type& e) {
    // Code to handle the exception
}
```

### Example 1: Basic Exception Handling

This example shows a function that checks for a division-by-zero error.

```cpp
#include <iostream>

double divide(double numerator, double denominator) {
    if (denominator == 0) {
        throw "Division by zero error";  // Throwing an exception (a C-string in this case)
    }
    return numerator / denominator;
}

int main() {
    double num = 10, den = 0;
    
    try {
        double result = divide(num, den);  // Try block for exception-prone code
        std::cout << "Result: " << result << std::endl;
    } catch (const char* e) {  // Catch block to handle exception
        std::cout << "Caught an exception: " << e << std::endl;
    }

    return 0;
}
```

### Explanation:
- The `divide()` function throws an exception if the denominator is zero.
- The `main()` function attempts to call `divide()` inside a `try` block.
- If an exception is thrown, control jumps to the `catch` block, which prints an error message.

---

### Example 2: Catching Standard Exceptions

C++ provides a standard library of exceptions, all of which are derived from `std::exception`. You can throw and catch these standard exceptions.

```cpp
#include <iostream>
#include <stdexcept>

void checkAge(int age) {
    if (age < 0) {
        throw std::invalid_argument("Invalid age: Age cannot be negative");  // Throwing a standard exception
    }
    std::cout << "Age is valid: " << age << std::endl;
}

int main() {
    try {
        checkAge(-5);  // This will throw an exception
    } catch (const std::invalid_argument& e) {  // Catching the exception by reference
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    return 0;
}
```

### Explanation:
- The function `checkAge()` throws an `std::invalid_argument` exception if the age is negative.
- The `main()` function calls `checkAge(-5)` inside a `try` block, and if an exception is thrown, it is caught in the `catch` block, where the error message is printed using `e.what()`.

---

### Example 3: Multiple Catch Blocks

C++ supports multiple `catch` blocks to handle different types of exceptions. Each `catch` block catches a different exception type.

```cpp
#include <iostream>
#include <stdexcept>

void testException(int type) {
    if (type == 1) throw std::runtime_error("Runtime error");
    if (type == 2) throw std::invalid_argument("Invalid argument error");
    if (type == 3) throw "Unknown error";
}

int main() {
    try {
        testException(2);  // Throw different types of exceptions
    } catch (const std::runtime_error& e) {  // Catch runtime error
        std::cout << "Caught runtime_error: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {  // Catch invalid argument error
        std::cout << "Caught invalid_argument: " << e.what() << std::endl;
    } catch (const char* e) {  // Catch C-string exception
        std::cout << "Caught generic error: " << e << std::endl;
    }

    return 0;
}
```

### Explanation:
- The `testException()` function throws different types of exceptions based on the input `type`.
- Multiple `catch` blocks are used to handle each specific exception type. If a `std::runtime_error` is thrown, it is caught by the first `catch` block. If an `std::invalid_argument` is thrown, it is caught by the second, and a generic `const char*` is caught by the third.

---

### Example 4: Catching All Exceptions

You can catch **all types** of exceptions using an ellipsis (`...`), which acts as a catch-all handler. However, it does not provide any information about the type or details of the exception.

```cpp
#include <iostream>

void testFunction(int value) {
    if (value == 0) throw 0;   // Throw an integer
    if (value == 1) throw 1.0; // Throw a double
    if (value == 2) throw "Some error";  // Throw a string
}

int main() {
    try {
        testFunction(1);  // Will throw a double
    } catch (const char* e) {
        std::cout << "Caught string exception: " << e << std::endl;
    } catch (...) {  // Catch all other exceptions
        std::cout << "Caught an unknown exception" << std::endl;
    }

    return 0;
}
```

### Explanation:
- The `testFunction()` throws different types of exceptions.
- The `catch (...)` block catches all other exceptions that aren’t caught by specific `catch` blocks. This is useful when you want to handle any unexpected exceptions generically.

---

### Example 5: Rethrowing Exceptions

You can rethrow an exception in the `catch` block to pass it further up the call stack using the `throw` statement without any arguments.

```cpp
#include <iostream>

void functionA() {
    try {
        throw std::runtime_error("Error from functionA");
    } catch (...) {
        std::cout << "Caught in functionA, rethrowing..." << std::endl;
        throw;  // Rethrow the exception
    }
}

void functionB() {
    try {
        functionA();
    } catch (const std::runtime_error& e) {
        std::cout << "Caught in functionB: " << e.what() << std::endl;
    }
}

int main() {
    functionB();
    return 0;
}
```

### Explanation:
- **`functionA()`** catches an exception but decides to rethrow it using `throw;`.
- **`functionB()`** then catches the rethrown exception from `functionA()` and handles it.

---

### Summary
- **`throw`**: Used to signal an exception. Can through object of different types, like char *, or std::invalid_arugement etc. In the rethrow case, it takes no argument and throws the existing exception (See example 5)
- **`try`**: Used to define a block of code where exceptions might occur.
- **`catch`**: Used to handle exceptions. You can catch specific exceptions or use `catch(...)` to handle all types.
- **Multiple `catch` blocks** allow handling different types of exceptions in different ways.
- **Rethrowing exceptions** is useful when you want to let higher-level code handle the error.

This covers the basics of exception handling in C++. Would you like to dive into more advanced concepts, like custom exceptions or exception safety?
