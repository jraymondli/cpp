#include <iostream>
#include <memory>

// Interface (abstract class)
class Shape {
public:
    // Pure virtual function (must be overridden by derived classes)
    virtual void draw() const = 0;
    virtual double area() const = 0;

    // Virtual destructor is needed to ensure proper cleanup of derived class objects
    virtual ~Shape() = default;
};

const double PI = 3.14159;

// Circle implements the Shape interface
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    // Implement the draw() function
    void draw() const override {
        std::cout << "Drawing a circle with radius: " << radius << std::endl;
    }

    // Implement the area() function
    double area() const override {
        return PI * radius * radius;
    }
};

// Rectangle implements the Shape interface
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    // Implement the draw() function
    void draw() const override {
        std::cout << "Drawing a rectangle with width: " << width << " and height: " << height << std::endl;
    }

    // Implement the area() function
    double area() const override {
        return width * height;
    }
};


int main() {
    // Create a Circle and a Rectangle using smart pointers
    std::unique_ptr<Shape> circle = std::make_unique<Circle>(5.0);
    std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(4.0, 6.0);

    // Drawing the shapes and calculating their areas
    circle->draw();
    std::cout << "Area of circle: " << circle->area() << std::endl;

    rectangle->draw();
    std::cout << "Area of rectangle: " << rectangle->area() << std::endl;

    return 0;
}
