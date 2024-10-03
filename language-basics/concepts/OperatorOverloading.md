### Introduction to Operator Overloading in C++

**Operator overloading** in C++ allows you to define custom behavior for operators (such as `+`, `-`, `*`, etc.) when they are applied to user-defined types (like classes or structs). This feature enables you to use operators with objects in a way that is intuitive and similar to built-in types.

### Key Points of Operator Overloading:
1. **Customizing Operator Behavior**: You can define how operators work with instances of your classes, making your code more readable and expressive.

2. **Syntax**: Operator overloading is done using the `operator` keyword followed by the operator symbol. It can be defined as a member function or a non-member function.

3. **Overloading Restrictions**: Not all operators can be overloaded. For example, you cannot overload:
   - The scope resolution operator (`::`)
   - The member selector operator (`.`)
   - The pointer-to-member operator (`.*`)

### Basic Syntax

The general syntax for operator overloading is:

```cpp
ReturnType operator OperatorSymbol (ParameterList) {
    // Custom behavior
}
```

### Example: Operator Overloading for a Complex Number Class

Let's create a simple `Complex` class to demonstrate operator overloading for addition and output.

```cpp
#include <iostream>

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Overload the + operator
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overload the << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};

int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);

    Complex c3 = c1 + c2;  // Calls overloaded + operator
    std::cout << "c1 + c2 = " << c3 << std::endl;  // Calls overloaded << operator

    return 0;
}
```

### Explanation:
1. **Class Definition**:
   - The `Complex` class represents a complex number with `real` and `imag` parts.
   - It has a constructor that initializes these values.

2. **Overloading the `+` Operator**:
   - The `operator+` function takes another `Complex` object and returns a new `Complex` object that represents the sum of the two complex numbers.

3. **Overloading the `<<` Operator**:
   - The `operator<<` function is defined as a friend function so it can access the private members of `Complex`. This function outputs the complex number in a readable format.

4. **Usage in `main`**:
   - Two `Complex` objects are created, and the overloaded `+` operator is used to add them together. The result is printed using the overloaded `<<` operator.

### Example: Overloading Other Operators

You can also overload other operators, such as the `-` operator, `*` operator, or assignment operator (`=`). Here’s an example of overloading the `-` and `*` operators:

```cpp
class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Overload the + operator
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overload the - operator
    Complex operator-(const Complex& other) {
        return Complex(real - other.real, imag - other.imag);
    }

    // Overload the * operator
    Complex operator*(const Complex& other) {
        return Complex(real * other.real - imag * other.imag, 
                       real * other.imag + imag * other.real);
    }

    // Overload the << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};

int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);

    Complex c3 = c1 + c2;  // Addition
    Complex c4 = c1 - c2;  // Subtraction
    Complex c5 = c1 * c2;  // Multiplication

    std::cout << "c1 + c2 = " << c3 << std::endl;
    std::cout << "c1 - c2 = " << c4 << std::endl;
    std::cout << "c1 * c2 = " << c5 << std::endl;

    return 0;
}
```

### Explanation:
- The `-` operator subtracts the real and imaginary parts of the complex numbers.
- The `*` operator multiplies two complex numbers according to the formula:
  \[
  (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
  \]

### Conclusion:
Operator overloading in C++ enhances the expressiveness of your code by allowing you to use operators with user-defined types. It provides a natural syntax for performing operations on complex objects, making the code cleaner and more intuitive. However, it’s essential to use operator overloading judiciously to maintain code clarity and prevent confusion.

Let me know if you have any questions or need further examples!
