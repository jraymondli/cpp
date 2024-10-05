### Builder Pattern in C++

The **Builder Pattern** is a creational design pattern that lets you construct complex objects step by step. Unlike other creational patterns that return the product right away, the Builder Pattern constructs the object through a series of methods, typically chainable, so the final product can be created in a controlled and flexible manner.

It is particularly useful when an object has many optional fields or when the construction process is complex and requires multiple steps.

---

### Example 1: Building a Pizza

Let's say you want to create a Pizza object with various optional ingredients like cheese, pepperoni, and mushrooms.

#### Step-by-Step Code Example:
```cpp
#include <iostream>
#include <string>

class Pizza {
private:
    std::string dough;
    std::string sauce;
    std::string topping;

public:
    void setDough(const std::string& d) { dough = d; }
    void setSauce(const std::string& s) { sauce = s; }
    void setTopping(const std::string& t) { topping = t; }

    void showPizza() const {
        std::cout << "Pizza with " << dough << " dough, " << sauce << " sauce, and " << topping << " topping.\n";
    }
};

// Abstract Builder
class PizzaBuilder {
public:
    virtual ~PizzaBuilder() = default;
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
    virtual Pizza* getPizza() = 0;
};

// Concrete Builder
class HawaiianPizzaBuilder : public PizzaBuilder {
private:
    Pizza* pizza;

public:
    HawaiianPizzaBuilder() { pizza = new Pizza(); }
    ~HawaiianPizzaBuilder() { delete pizza; }

    void buildDough() override { pizza->setDough("cross"); }
    void buildSauce() override { pizza->setSauce("mild"); }
    void buildTopping() override { pizza->setTopping("ham+pineapple"); }
    
    Pizza* getPizza() override { return pizza; }
};

// Concrete Builder
class SpicyPizzaBuilder : public PizzaBuilder {
private:
    Pizza* pizza;

public:
    SpicyPizzaBuilder() { pizza = new Pizza(); }
    ~SpicyPizzaBuilder() { delete pizza; }

    void buildDough() override { pizza->setDough("pan baked"); }
    void buildSauce() override { pizza->setSauce("hot"); }
    void buildTopping() override { pizza->setTopping("pepperoni+salami"); }

    Pizza* getPizza() override { return pizza; }
};

// Director
class Cook {
private:
    PizzaBuilder* pizzaBuilder;

public:
    void setPizzaBuilder(PizzaBuilder* pb) { pizzaBuilder = pb; }
    Pizza* getPizza() { return pizzaBuilder->getPizza(); }

    void constructPizza() {
        pizzaBuilder->buildDough();
        pizzaBuilder->buildSauce();
        pizzaBuilder->buildTopping();
    }
};

int main() {
    Cook cook;
    HawaiianPizzaBuilder hawaiianPizzaBuilder;
    SpicyPizzaBuilder spicyPizzaBuilder;

    // Build Hawaiian Pizza
    cook.setPizzaBuilder(&hawaiianPizzaBuilder);
    cook.constructPizza();
    Pizza* hawaiianPizza = cook.getPizza();
    hawaiianPizza->showPizza();

    // Build Spicy Pizza
    cook.setPizzaBuilder(&spicyPizzaBuilder);
    cook.constructPizza();
    Pizza* spicyPizza = cook.getPizza();
    spicyPizza->showPizza();

    return 0;
}
```

#### Explanation:
1. **PizzaBuilder** is an abstract base class that defines the interface for building the parts of the product.
2. **HawaiianPizzaBuilder** and **SpicyPizzaBuilder** are concrete builders that implement the construction steps for different kinds of pizzas.
3. **Cook** is the director that manages the construction process by calling the builder's methods in a specific order.
4. **Pizza** is the product being constructed step by step.

---

### Example 2: Building a Car

This example builds a `Car` object with optional fields like engine type, wheels, and color.

```cpp
#include <iostream>
#include <string>

class Car {
private:
    std::string engine;
    std::string wheels;
    std::string color;

public:
    void setEngine(const std::string& engine) { this->engine = engine; }
    void setWheels(const std::string& wheels) { this->wheels = wheels; }
    void setColor(const std::string& color) { this->color = color; }

    void showCar() const {
        std::cout << "Car with " << engine << " engine, " << wheels << " wheels, and " << color << " color.\n";
    }
};

// Abstract Builder
class CarBuilder {
public:
    virtual ~CarBuilder() = default;
    virtual void buildEngine() = 0;
    virtual void buildWheels() = 0;
    virtual void paintCar() = 0;
    virtual Car* getCar() = 0;
};

// Concrete Builder
class SedanCarBuilder : public CarBuilder {
private:
    Car* car;

public:
    SedanCarBuilder() { car = new Car(); }
    ~SedanCarBuilder() { delete car; }

    void buildEngine() override { car->setEngine("V4"); }
    void buildWheels() override { car->setWheels("16 inch alloy"); }
    void paintCar() override { car->setColor("Black"); }
    
    Car* getCar() override { return car; }
};

// Concrete Builder
class SUVCarBuilder : public CarBuilder {
private:
    Car* car;

public:
    SUVCarBuilder() { car = new Car(); }
    ~SUVCarBuilder() { delete car; }

    void buildEngine() override { car->setEngine("V6"); }
    void buildWheels() override { car->setWheels("18 inch alloy"); }
    void paintCar() override { car->setColor("White"); }

    Car* getCar() override { return car; }
};

// Director
class Director {
private:
    CarBuilder* carBuilder;

public:
    void setCarBuilder(CarBuilder* cb) { carBuilder = cb; }
    Car* getCar() { return carBuilder->getCar(); }

    void constructCar() {
        carBuilder->buildEngine();
        carBuilder->buildWheels();
        carBuilder->paintCar();
    }
};

int main() {
    Director director;
    SedanCarBuilder sedanCarBuilder;
    SUVCarBuilder suvCarBuilder;

    // Build Sedan
    director.setCarBuilder(&sedanCarBuilder);
    director.constructCar();
    Car* sedan = director.getCar();
    sedan->showCar();

    // Build SUV
    director.setCarBuilder(&suvCarBuilder);
    director.constructCar();
    Car* suv = director.getCar();
    suv->showCar();

    return 0;
}
```

#### Explanation:
- **SedanCarBuilder** and **SUVCarBuilder** create different types of cars by implementing the `CarBuilder` interface.
- The **Director** coordinates the car-building process.
- The **Car** object is built with various components, such as engine, wheels, and color, set one by one.

---

### Fluent Builder Example (Method Chaining)

A common variation of the Builder pattern in modern C++ is using *method chaining*, where the builder methods return a reference to the builder object itself, allowing chained calls.

```cpp
#include <iostream>
#include <string>

class House {
private:
    std::string walls;
    std::string roof;
    std::string windows;

public:
    House& setWalls(const std::string& w) { walls = w; return *this; }
    House& setRoof(const std::string& r) { roof = r; return *this; }
    House& setWindows(const std::string& win) { windows = win; return *this; }

    void showHouse() const {
        std::cout << "House with " << walls << " walls, " << roof << " roof, and " << windows << " windows.\n";
    }
};

int main() {
    House house;
    house.setWalls("Brick")
         .setRoof("Tile")
         .setWindows("Double-glazed");

    house.showHouse();

    return 0;
}
```

#### Explanation:
- In this example, methods `setWalls()`, `setRoof()`, and `setWindows()` return a reference to the `House` object (`*this`), enabling method chaining.
- The object `house` is built with a fluent interface, allowing the building steps to be combined into a single chain of method calls.

---

### Key Points:
- The **Builder Pattern** is useful when constructing complex objects step by step.
- It improves **readability** and **flexibility** when many fields are optional or when the construction process is complicated.
- **Directors** manage the construction process, ensuring that steps are executed in a controlled order.
- **Method chaining** (fluent interfaces) are a popular variation of the Builder Pattern in modern C++ for improving code clarity.
