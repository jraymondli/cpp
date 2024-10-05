In C++, **static data members** and **static member functions** are used to share information and behavior across all instances of a class, rather than being tied to any specific object. Here's how they work:

### 1. **Static Data Members**
   - **Shared among all objects**: A static data member belongs to the class itself, rather than any individual instance. All objects of that class share the same copy of the static data member.
   - **Defined outside the class**: A static data member must be defined outside the class definition, even if it is initialized within the class.
   - **Usage**: It is useful when you want to maintain a common value across all instances, such as a counter tracking how many objects have been created.

   Example:
   ```cpp
   #include <iostream>
   
   class MyClass {
   public:
       static int count;  // Declaration of static member

       MyClass() {
           ++count;  // Increment static member in constructor
       }

       static int getCount() {
           return count;  // Access static member in static function
       }
   };

   int MyClass::count = 0;  // Definition of static member

   int main() {
       MyClass obj1, obj2, obj3;
       std::cout << "Count: " << MyClass::getCount() << std::endl;  // Output: Count: 3
       return 0;
   }
   ```

### 2. **Static Member Functions**
   - **Called without an object**: Static member functions do not need an object of the class to be called. They can be invoked using the class name.
   - **No access to non-static members**: Static member functions can only access static data members and other static member functions. They cannot access non-static members of the class since they are not tied to any object instance.
   
   Example:
   ```cpp
   class Example {
   public:
       static int staticVar;  // Static data member
       
       static void staticFunc() {  // Static member function
           std::cout << "Static variable value: " << staticVar << std::endl;
       }
   };

   int Example::staticVar = 42;  // Defining static data member

   int main() {
       Example::staticFunc();  // Calling static function without creating an object
       return 0;
   }
   ```

### Key Points:
- **Static data members** are shared across all instances of the class.
- **Static member functions** can be called without creating an object of the class.
- Static member functions **cannot** access non-static data members.

These are useful for managing shared data or functions that don’t depend on object-specific data, and they provide a way to access or modify shared states at the class level.
