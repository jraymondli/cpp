The **Flyweight Pattern** is a structural design pattern that aims to minimize memory usage and improve performance by sharing objects instead of creating new instances. This pattern is particularly useful when dealing with a large number of objects that share common state, allowing for significant memory savings.

The Flyweight Pattern is most effective when:
- You have a large number of similar objects that can share common state (intrinsic state).
- You want to reduce memory consumption by reusing existing objects.

---

### Key Concepts
- **Flyweight**: An interface that defines methods for accessing the intrinsic state.
- **ConcreteFlyweight**: Implements the Flyweight interface and represents the shared state.
- **UnsharedConcreteFlyweight**: Represents the extrinsic state, which is not shared and is passed as an argument to the Flyweight methods.
- **FlyweightFactory**: Creates and manages Flyweight objects, ensuring that shared instances are reused.

---

### Example: Text Formatting

In this example, we create a text formatting system where each character can be represented by a shared Flyweight object, reducing memory usage.

#### Code Example:
```cpp
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

// Flyweight Interface
class Character {
public:
    virtual void display(int fontSize) = 0;
    virtual ~Character() {}
};

// ConcreteFlyweight Class: Shared Characters
class ConcreteCharacter : public Character {
private:
    char symbol;

public:
    ConcreteCharacter(char c) : symbol(c) {}

    void display(int fontSize) override {
        std::cout << "Character: " << symbol << ", Font Size: " << fontSize << std::endl;
    }
};

// Flyweight Factory
class CharacterFactory {
private:
    std::unordered_map<char, std::shared_ptr<Character>> characters;

public:
    std::shared_ptr<Character> getCharacter(char c) {
        // Check if character is already created
        if (characters.find(c) == characters.end()) {
            characters[c] = std::make_shared<ConcreteCharacter>(c);
        }
        return characters[c];
    }
};

// Client code
int main() {
    CharacterFactory factory;

    // Create a string using Flyweight pattern
    std::string text = "hello flyweight";
    int fontSize = 12;

    for (char c : text) {
        std::shared_ptr<Character> character = factory.getCharacter(c);
        character->display(fontSize);
    }

    return 0;
}
```

#### Explanation:
- **Flyweight Interface**: The `Character` interface defines the method `display()`, which takes the font size as an argument.
- **ConcreteFlyweight**: The `ConcreteCharacter` class implements the `Character` interface and represents individual characters that can be shared.
- **FlyweightFactory**: The `CharacterFactory` class manages the creation and reuse of `ConcreteCharacter` objects. If a character is already created, it returns the existing instance; otherwise, it creates a new one.
- **Client**: The client code uses the factory to create a string of characters. Instead of creating separate instances for each character, it reuses shared instances, thus saving memory.

---

### Example 2: Geometric Shapes

In this example, we implement a drawing application where different geometric shapes can be shared.

#### Code Example:
```cpp
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

// Flyweight Interface
class Shape {
public:
    virtual void draw(const std::string& color) = 0;
    virtual ~Shape() {}
};

// ConcreteFlyweight Class: Circle
class Circle : public Shape {
private:
    int radius;

public:
    Circle(int r) : radius(r) {}

    void draw(const std::string& color) override {
        std::cout << "Drawing Circle with radius " << radius << " and color " << color << std::endl;
    }
};

// Flyweight Factory
class ShapeFactory {
private:
    std::unordered_map<int, std::shared_ptr<Shape>> shapes;

public:
    std::shared_ptr<Shape> getCircle(int radius) {
        // Check if circle is already created
        if (shapes.find(radius) == shapes.end()) {
            shapes[radius] = std::make_shared<Circle>(radius);
        }
        return shapes[radius];
    }
};

// Client code
int main() {
    ShapeFactory factory;

    // Draw multiple circles with different colors but same radius
    std::shared_ptr<Shape> circle1 = factory.getCircle(5);
    circle1->draw("Red");

    std::shared_ptr<Shape> circle2 = factory.getCircle(5);
    circle2->draw("Blue"); // This will reuse the same Circle object

    std::shared_ptr<Shape> circle3 = factory.getCircle(10);
    circle3->draw("Green");

    return 0;
}
```

#### Explanation:
- **Flyweight Interface**: The `Shape` interface defines the method `draw()`, which takes color as an argument.
- **ConcreteFlyweight**: The `Circle` class implements the `Shape` interface and represents a circle with a specific radius.
- **FlyweightFactory**: The `ShapeFactory` class manages the creation and reuse of `Circle` objects. It checks if a circle with the specified radius already exists and returns it, otherwise creates a new one.
- **Client**: The client code draws multiple circles, reusing the shared `Circle` object with radius 5 for different colors.

---

### Key Points:
- The **Flyweight Pattern** minimizes memory usage by sharing common objects, especially useful when dealing with large collections of similar objects.
- It separates intrinsic (shared) and extrinsic (contextual) state, allowing for efficient memory management.
- The pattern encourages the reuse of objects, reducing the overhead of object creation and improving performance, especially in resource-constrained environments.
