The **Prototype Pattern** is a creational design pattern that allows you to clone existing objects instead of creating new instances from scratch. This is especially useful when the process of object creation is complex or costly. The idea is to create new objects by copying or cloning a prototype instance.

In C++, the **Prototype Pattern** can be implemented using a clone function, which creates a copy of the object.

---

### Key Concepts
- **Prototype**: A base class that defines a method for cloning objects.
- **Concrete Prototype**: A subclass that implements the cloning method to create copies of itself.
- **Client**: The object that requires a new instance and requests a copy of the prototype.

---

### Example 1: Simple Object Cloning

This example demonstrates how to clone simple objects using the Prototype pattern.

```cpp
#include <iostream>
#include <string>
#include <memory>

// Prototype Interface
class Shape {
public:
    virtual ~Shape() {}
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
};

// Concrete Prototype: Circle
class Circle : public Shape {
private:
    int radius;

public:
    Circle(int r) : radius(r) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this); // Clone a Circle
    }

    void draw() const override {
        std::cout << "Drawing a Circle with radius: " << radius << "\n";
    }
};

// Concrete Prototype: Rectangle
class Rectangle : public Shape {
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this); // Clone a Rectangle
    }

    void draw() const override {
        std::cout << "Drawing a Rectangle with width: " << width << " and height: " << height << "\n";
    }
};

// Client code
int main() {
    // Create prototype instances
    std::unique_ptr<Shape> circlePrototype = std::make_unique<Circle>(5);
    std::unique_ptr<Shape> rectanglePrototype = std::make_unique<Rectangle>(10, 20);

    // Clone the objects
    std::unique_ptr<Shape> clonedCircle = circlePrototype->clone();
    std::unique_ptr<Shape> clonedRectangle = rectanglePrototype->clone();

    // Draw the cloned objects
    clonedCircle->draw();
    clonedRectangle->draw();

    return 0;
}
```

#### Explanation:
- **Prototype Interface**: The `Shape` class defines the `clone()` method that must be implemented by concrete classes.
- **Concrete Prototypes**: The `Circle` and `Rectangle` classes implement `clone()` to create copies of themselves.
- **Client**: The client code creates prototypes of `Circle` and `Rectangle`, then clones them to create new instances.

---

### Example 2: Prototype with a Registry

In this example, we add a **prototype registry** that stores predefined prototypes and allows the client to retrieve and clone them on demand.

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// Prototype Interface
class Animal {
public:
    virtual ~Animal() {}
    virtual std::unique_ptr<Animal> clone() const = 0;
    virtual void makeSound() const = 0;
};

// Concrete Prototype: Dog
class Dog : public Animal {
public:
    std::unique_ptr<Animal> clone() const override {
        return std::make_unique<Dog>(*this); // Clone a Dog
    }

    void makeSound() const override {
        std::cout << "Woof! Woof!\n";
    }
};

// Concrete Prototype: Cat
class Cat : public Animal {
public:
    std::unique_ptr<Animal> clone() const override {
        return std::make_unique<Cat>(*this); // Clone a Cat
    }

    void makeSound() const override {
        std::cout << "Meow! Meow!\n";
    }
};

// Prototype Registry
class AnimalRegistry {
private:
    std::unordered_map<std::string, std::unique_ptr<Animal>> prototypes;

public:
    void addPrototype(const std::string& type, std::unique_ptr<Animal> prototype) {
        prototypes[type] = std::move(prototype);
    }

    std::unique_ptr<Animal> createAnimal(const std::string& type) const {
        if (prototypes.find(type) != prototypes.end()) {
            return prototypes.at(type)->clone();
        } else {
            return nullptr;
        }
    }
};

// Client code
int main() {
    AnimalRegistry registry;

    // Add prototypes to the registry
    registry.addPrototype("dog", std::make_unique<Dog>());
    registry.addPrototype("cat", std::make_unique<Cat>());

    // Clone and use prototypes
    std::unique_ptr<Animal> clonedDog = registry.createAnimal("dog");
    std::unique_ptr<Animal> clonedCat = registry.createAnimal("cat");

    clonedDog->makeSound();
    clonedCat->makeSound();

    return 0;
}
```

#### Explanation:
- **Prototype Interface**: The `Animal` class defines the `clone()` and `makeSound()` methods.
- **Concrete Prototypes**: `Dog` and `Cat` implement the prototype interface.
- **Prototype Registry**: The `AnimalRegistry` class stores prototypes in a map and allows the client to retrieve and clone them by type.
- **Client**: The client uses the `AnimalRegistry` to create instances of `Dog` and `Cat` by cloning prototypes.

---

### Example 3: Deep Copy with Prototype

In some cases, you may need a **deep copy** when cloning an object. Here’s how the Prototype pattern handles this.

```cpp
#include <iostream>
#include <string>

// Complex Object with Deep Copy
class Address {
public:
    std::string street;
    std::string city;

    Address(const std::string& street, const std::string& city) : street(street), city(city) {}

    Address(const Address& other) : street(other.street), city(other.city) {} // Copy constructor

    void showAddress() const {
        std::cout << street << ", " << city << "\n";
    }
};

// Prototype Interface
class Person {
public:
    virtual ~Person() {}
    virtual Person* clone() const = 0;
    virtual void showPerson() const = 0;
};

// Concrete Prototype: Employee
class Employee : public Person {
private:
    std::string name;
    Address* address;

public:
    Employee(const std::string& name, Address* addr) : name(name), address(new Address(*addr)) {}

    Employee(const Employee& other) : name(other.name), address(new Address(*other.address)) {} // Deep copy

    Employee* clone() const override {
        return new Employee(*this); // Deep clone
    }

    void showPerson() const override {
        std::cout << "Name: " << name << "\nAddress: ";
        address->showAddress();
    }

    ~Employee() { delete address; } // Clean up
};

// Client code
int main() {
    Address address1("123 Main St", "New York");
    Employee original("John Doe", &address1);

    // Clone the original employee (deep copy)
    Employee* clone = original.clone();

    std::cout << "Original Employee:\n";
    original.showPerson();

    std::cout << "\nCloned Employee:\n";
    clone->showPerson();

    delete clone; // Clean up

    return 0;
}
```

#### Explanation:
- **Deep Copy**: In this example, the `Employee` class contains a pointer to an `Address` object. The `clone()` method creates a **deep copy** of the `Employee` object, including its `Address`.
- **Copy Constructor**: The `Address` and `Employee` classes define copy constructors to facilitate deep copying.
- **Client**: The client clones the `Employee` object, which includes copying the `Address` object to ensure that the original and cloned objects are independent.

---

### Key Points of the Prototype Pattern:
- **Cloning**: Objects are created by copying an existing prototype rather than by direct instantiation.
- **Shallow vs. Deep Copy**: Depending on the use case, you may need either shallow copies (default copy constructor) or deep copies (custom copy constructor).
- **Registry**: You can maintain a registry of prototypes and clone them based on client requests, making the process efficient for creating new objects with slight variations.
- **Flexibility**: It’s useful when creating new objects is expensive or when object construction involves many steps.
