### Introduction to Design Patterns in C++

Design patterns are general reusable solutions to common software design problems. They are not finished pieces of code, but templates that help solve issues in a particular context. In C++, design patterns are especially powerful as they allow you to tackle issues related to performance, resource management, and modularity.

Design patterns can be grouped into three main categories:

1. **Creational Patterns**: Deal with object creation mechanisms.
2. **Structural Patterns**: Deal with object composition.
3. **Behavioral Patterns**: Deal with object interaction and communication.

Let’s explore some of the common design patterns in C++ with examples.

---

### 1. **Singleton Pattern (Creational Pattern)**

**Purpose**: Ensure a class has only one instance and provide a global point of access to that instance.

#### Example:
```cpp
#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex_;

    // Private constructor to prevent instantiation
    Singleton() {}

public:
    // Static method to access the single instance
    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    void showMessage() {
        std::cout << "Singleton Instance: Hello World!" << std::endl;
    }
};

// Initialize static members
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex_;

int main() {
    Singleton* s = Singleton::getInstance();
    s->showMessage();

    return 0;
}
```

#### Key Points:
- **Private constructor**: Prevents creating objects from outside the class.
- **Static method**: Provides global access to the instance.
- **Thread safety**: The `std::mutex` ensures the singleton instance is created in a thread-safe manner.

---

### 2. **Factory Pattern (Creational Pattern)**

**Purpose**: Define an interface for creating an object but let subclasses decide which class to instantiate.

#### Example:
```cpp
#include <iostream>
#include <memory>

// Product interface
class Product {
public:
    virtual void use() = 0;
};

// Concrete product A
class ConcreteProductA : public Product {
public:
    void use() override {
        std::cout << "Using ConcreteProductA" << std::endl;
    }
};

// Concrete product B
class ConcreteProductB : public Product {
public:
    void use() override {
        std::cout << "Using ConcreteProductB" << std::endl;
    }
};

// Factory
class ProductFactory {
public:
    static std::unique_ptr<Product> createProduct(const std::string& type) {
        if (type == "A") {
            return std::make_unique<ConcreteProductA>();
        } else if (type == "B") {
            return std::make_unique<ConcreteProductB>();
        } else {
            return nullptr;
        }
    }
};

int main() {
    auto product = ProductFactory::createProduct("A");
    if (product) product->use();

    product = ProductFactory::createProduct("B");
    if (product) product->use();

    return 0;
}
```

#### Key Points:
- The **factory method** allows creating objects without exposing the creation logic to the client.
- The **client code** is decoupled from the concrete class it uses.
- The factory method returns a **base class pointer** (`Product`), while the concrete classes (`ConcreteProductA`, `ConcreteProductB`) implement specific behavior.

---

### 3. **Observer Pattern (Behavioral Pattern)**

**Purpose**: Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

#### Example:
```cpp
#include <iostream>
#include <vector>
#include <string>

// Observer Interface
class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

// Concrete Observer
class ConcreteObserver : public Observer {
private:
    std::string name;
public:
    ConcreteObserver(const std::string& name) : name(name) {}
    void update(const std::string& message) override {
        std::cout << name << " received update: " << message << std::endl;
    }
};

// Subject (Observable)
class Subject {
private:
    std::vector<Observer*> observers;
    std::string message;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }

    void setMessage(const std::string& message) {
        this->message = message;
        notifyObservers();
    }
};

int main() {
    Subject subject;

    ConcreteObserver observer1("Observer 1");
    ConcreteObserver observer2("Observer 2");

    subject.addObserver(&observer1);
    subject.addObserver(&observer2);

    subject.setMessage("Hello Observers!");
    subject.setMessage("Another message!");

    return 0;
}
```

#### Key Points:
- **Observers** register with the **Subject** (the observable).
- When the state of the subject changes, all registered observers are notified using the `update()` method.
- This pattern is useful for implementing systems where a change in one object should trigger updates in others (e.g., GUIs, event-driven systems).

---

### 4. **Strategy Pattern (Behavioral Pattern)**

**Purpose**: Define a family of algorithms, encapsulate each one, and make them interchangeable. The strategy pattern allows the algorithm to vary independently from clients that use it.

#### Example:
```cpp
#include <iostream>
#include <memory>

// Strategy Interface
class Strategy {
public:
    virtual void execute() = 0;
};

// Concrete Strategies
class ConcreteStrategyA : public Strategy {
public:
    void execute() override {
        std::cout << "Executing Strategy A" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void execute() override {
        std::cout << "Executing Strategy B" << std::endl;
    }
};

// Context
class Context {
private:
    std::unique_ptr<Strategy> strategy;
public:
    void setStrategy(std::unique_ptr<Strategy> s) {
        strategy = std::move(s);
    }

    void executeStrategy() {
        strategy->execute();
    }
};

int main() {
    Context context;

    context.setStrategy(std::make_unique<ConcreteStrategyA>());
    context.executeStrategy();  // Outputs: Executing Strategy A

    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.executeStrategy();  // Outputs: Executing Strategy B

    return 0;
}
```

#### Key Points:
- The **context** holds a reference to a **strategy** and delegates the execution of behavior to it.
- The **strategy** can be changed at runtime, allowing flexible and interchangeable algorithms.
- This pattern is useful in systems where different methods are required to perform a task based on different conditions (e.g., payment strategies, sorting algorithms).

---

### 5. **Decorator Pattern (Structural Pattern)**

**Purpose**: Attach additional responsibilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending functionality.

#### Example:
```cpp
#include <iostream>
#include <memory>

// Component Interface
class Coffee {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Coffee() = default;
};

// Concrete Component
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }

    double cost() const override {
        return 5.0;
    }
};

// Base Decorator
class CoffeeDecorator : public Coffee {
protected:
    std::unique_ptr<Coffee> coffee;
public:
    CoffeeDecorator(std::unique_ptr<Coffee> c) : coffee(std::move(c)) {}
};

// Concrete Decorators
class Milk : public CoffeeDecorator {
public:
    Milk(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }

    double cost() const override {
        return coffee->cost() + 1.5;
    }
};

class Sugar : public CoffeeDecorator {
public:
    Sugar(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}

    std::string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }

    double cost() const override {
        return coffee->cost() + 0.5;
    }
};

int main() {
    std::unique_ptr<Coffee> myCoffee = std::make_unique<SimpleCoffee>();
    myCoffee = std::make_unique<Milk>(std::move(myCoffee));
    myCoffee = std::make_unique<Sugar>(std::move(myCoffee));

    std::cout << myCoffee->getDescription() << " costs $" << myCoffee->cost() << std::endl;

    return 0;
}
```

#### Key Points:
- The **decorator** dynamically adds responsibilities (like `Milk` or `Sugar`) to the **component** (`SimpleCoffee`).
- This pattern provides a flexible and extensible way to add functionality without modifying the original class.

---

### Summary of Key Patterns:

| Pattern        | Category        | Purpose                                                                                  |
| -------------- | --------------- | ---------------------------------------------------------------------------------------- |
| Singleton      | Creational      | Ensure only one instance of a class exists.                                               |
| Factory        |
