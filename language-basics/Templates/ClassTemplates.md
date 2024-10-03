### Introduction to Class Templates in C++

**Class templates** in C++ allow you to create generic classes that can work with any data type. Instead of writing separate classes for each type (e.g., for `int`, `double`, etc.), you can write a single class template and specify the type when instantiating objects.

### Key Points of Class Templates:
1. **Generic Classes**: Class templates enable you to write a generic class that can handle different data types. This reduces code duplication and increases flexibility.

2. **Template Parameters**: Class templates use template parameters, just like function templates. The type is provided as a parameter to the template when an object is created.

3. **Type Deduction**: When an object is created from a class template, the type is specified in angle brackets, and the compiler generates the appropriate class for that type.

### Syntax of a Class Template

The general syntax for a class template is as follows:

```cpp
template <typename T>
class ClassName {
    // Class implementation using type T
};
```

You can also use `class` instead of `typename`, both are valid.

```cpp
template <class T>
class ClassName {
    // Class implementation using type T
};
```

### Example 1: Simple Class Template for a Box

Here's a simple example of a class template that represents a box for storing values of any type.

```cpp
#include <iostream>

// Class template
template <typename T>
class Box {
private:
    T value;

public:
    // Constructor
    Box(T val) : value(val) {}

    // Function to get the value
    T getValue() {
        return value;
    }

    // Function to set a new value
    void setValue(T val) {
        value = val;
    }
};

int main() {
    // Create a Box for int
    Box<int> intBox(10);
    std::cout << "intBox value: " << intBox.getValue() << std::endl;

    // Create a Box for double
    Box<double> doubleBox(3.14);
    std::cout << "doubleBox value: " << doubleBox.getValue() << std::endl;

    // Create a Box for std::string
    Box<std::string> stringBox("Hello, world!");
    std::cout << "stringBox value: " << stringBox.getValue() << std::endl;

    return 0;
}
```

### Explanation:
1. **Class Template Definition**:
   - The class `Box` is a template class that stores a single value of type `T`. The type `T` is specified when creating an object of the class.

2. **Template Parameters**:
   - `T` can be any type, and the compiler generates the appropriate version of the `Box` class for the specified type.

3. **Usage**:
   - In `main()`, three `Box` objects are created, each with a different type: `int`, `double`, and `std::string`. The appropriate version of the class is instantiated based on the type.

4. **Output**:
   - The program prints the values stored in each box, demonstrating the flexibility of the template.

### Example 2: Class Template with Multiple Template Parameters

You can also create class templates with multiple template parameters.

```cpp
#include <iostream>

// Class template with two template parameters
template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    // Constructor
    Pair(T1 f, T2 s) : first(f), second(s) {}

    // Function to get the first value
    T1 getFirst() const {
        return first;
    }

    // Function to get the second value
    T2 getSecond() const {
        return second;
    }
};

int main() {
    // Create a Pair of int and double
    Pair<int, double> p1(10, 20.5);
    std::cout << "p1: (" << p1.getFirst() << ", " << p1.getSecond() << ")" << std::endl;

    // Create a Pair of string and int
    Pair<std::string, int> p2("Age", 30);
    std::cout << "p2: (" << p2.getFirst() << ", " << p2.getSecond() << ")" << std::endl;

    return 0;
}
```

### Explanation:
1. **Multiple Template Parameters**:
   - The class `Pair` has two template parameters: `T1` and `T2`. This allows the class to hold a pair of values with different types.

2. **Template Parameter Usage**:
   - The types `T1` and `T2` are specified when the `Pair` object is created.

3. **Usage**:
   - In `main()`, a `Pair` object is created for an `int` and `double`, and another is created for a `std::string` and `int`.

4. **Output**:
   - The program prints the pairs, demonstrating how the class template can handle different types for each parameter.

### Example 3: Class Template Specialization

Sometimes you need to define a different implementation for specific types. This is known as **template specialization**.

```cpp
#include <iostream>

// Generic class template
template <typename T>
class Calculator {
public:
    T add(T a, T b) {
        return a + b;
    }
};

// Specialized version for const char*
template <>
class Calculator<const char*> {
public:
    const char* add(const char* a, const char* b) {
        std::string result = std::string(a) + std::string(b);
        return result.c_str();
    }
};

int main() {
    // Using generic template for integers
    Calculator<int> intCalc;
    std::cout << "Sum of 3 and 5: " << intCalc.add(3, 5) << std::endl;

    // Using specialized template for const char*
    Calculator<const char*> strCalc;
    std::cout << "Concatenation of 'Hello' and ' World': " << strCalc.add("Hello", " World") << std::endl;

    return 0;
}
```

### Explanation:
1. **Generic Class Template**:
   - The generic `Calculator` class template handles any type `T` and provides an `add` function that adds two values.

2. **Specialization**:
   - The specialized version for `const char*` handles the concatenation of C-style strings, converting them to `std::string` and returning the result.

3. **Usage**:
   - In `main()`, two `Calculator` objects are created: one for integers and another for C-strings. The appropriate version of the class template is used based on the type.

4. **Output**:
   - The program prints the sum for integers and concatenates C-strings for the specialized version.

### Conclusion

Class templates in C++ provide a powerful way to write generic code that can operate on different data types. By using class templates, you can avoid code duplication, write more flexible and reusable code, and handle a wide range of data types without having to rewrite class definitions for each one.

Let me know if you need further examples or clarification!
