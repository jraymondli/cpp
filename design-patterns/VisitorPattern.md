The **Visitor Pattern** is a behavioral design pattern that allows you to add further operations to objects without modifying them. It lets you define a new operation without changing the classes of the elements on which it operates. The pattern allows you to separate the algorithm from the object structure, making it easier to add new operations by extending the visitor, rather than modifying the object itself.

### Key Components:
1. **Visitor**: Declares a visit method for each type of object (element) that can be visited.
2. **Concrete Visitor**: Implements the visitor interface, defining specific behavior for each element type it can visit.
3. **Element**: Defines an `accept` method that accepts a visitor object and calls the appropriate visitor method.
4. **Concrete Element**: Implements the `Element` interface, providing a method to accept a visitor.
5. **Client**: The client code that executes the visitor on the elements.

### Example: Object Structure with Different Shape Objects

Let’s consider a scenario where we have different shape objects (Circle, Rectangle) and we want to add operations like calculating area and drawing the shape without modifying the shapes themselves. We'll use the **Visitor Pattern** to allow new operations without changing the shape classes.

#### Code Example

```cpp
#include <iostream>
#include <cmath>

// Forward declarations
class Circle;
class Rectangle;

// Visitor interface
class Visitor {
public:
    virtual void visitCircle(Circle* circle) = 0;
    virtual void visitRectangle(Rectangle* rectangle) = 0;
};

// Element interface
class Shape {
public:
    virtual void accept(Visitor* visitor) = 0;
};

// Concrete Element: Circle
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getRadius() const {
        return radius;
    }

    void accept(Visitor* visitor) override {
        visitor->visitCircle(this);
    }
};

// Concrete Element: Rectangle
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }

    void accept(Visitor* visitor) override {
        visitor->visitRectangle(this);
    }
};

// Concrete Visitor: Calculate Area
class AreaVisitor : public Visitor {
public:
    void visitCircle(Circle* circle) override {
        double area = M_PI * circle->getRadius() * circle->getRadius();
        std::cout << "Area of Circle: " << area << std::endl;
    }

    void visitRectangle(Rectangle* rectangle) override {
        double area = rectangle->getWidth() * rectangle->getHeight();
        std::cout << "Area of Rectangle: " << area << std::endl;
    }
};

// Concrete Visitor: Draw Shape
class DrawVisitor : public Visitor {
public:
    void visitCircle(Circle* circle) override {
        std::cout << "Drawing Circle with radius " << circle->getRadius() << std::endl;
    }

    void visitRectangle(Rectangle* rectangle) override {
        std::cout << "Drawing Rectangle with width " << rectangle->getWidth() 
                  << " and height " << rectangle->getHeight() << std::endl;
    }
};

// Client code
int main() {
    Shape* circle = new Circle(5.0);
    Shape* rectangle = new Rectangle(4.0, 6.0);

    // Create visitors
    AreaVisitor areaVisitor;
    DrawVisitor drawVisitor;

    // Apply visitors to shapes
    circle->accept(&areaVisitor);
    rectangle->accept(&areaVisitor);

    circle->accept(&drawVisitor);
    rectangle->accept(&drawVisitor);

    // Clean up
    delete circle;
    delete rectangle;

    return 0;
}
```

### Explanation:
1. **Visitor (`Visitor`)**: The interface that defines the visit methods for each type of `Element` it can visit.
2. **Concrete Visitors (`AreaVisitor`, `DrawVisitor`)**: Implement the visitor interface, providing the specific behavior for each type of shape (circle, rectangle). For instance, `AreaVisitor` calculates the area, and `DrawVisitor` draws the shape.
3. **Element (`Shape`)**: The abstract class for shapes. Each shape can accept a visitor.
4. **Concrete Elements (`Circle`, `Rectangle`)**: These classes implement the `accept` method, which allows the shape to be visited by a `Visitor`.
5. **Client**: Creates the shapes and applies visitors to them.

### Output:
```
Area of Circle: 78.5398
Area of Rectangle: 24
Drawing Circle with radius 5
Drawing Rectangle with width 4 and height 6
```

### Example 2: File System with Visitor for File Operations

Here’s another example where we have different types of file system objects (File and Directory), and we want to perform operations like calculating the size and printing the structure using the **Visitor Pattern**.

#### Code Example

```cpp
#include <iostream>
#include <vector>
#include <string>

// Forward declarations
class File;
class Directory;

// Visitor interface
class FileSystemVisitor {
public:
    virtual void visitFile(File* file) = 0;
    virtual void visitDirectory(Directory* directory) = 0;
};

// Element interface
class FileSystemElement {
public:
    virtual void accept(FileSystemVisitor* visitor) = 0;
};

// Concrete Element: File
class File : public FileSystemElement {
private:
    std::string name;
    int size;

public:
    File(const std::string& name, int size) : name(name), size(size) {}

    std::string getName() const {
        return name;
    }

    int getSize() const {
        return size;
    }

    void accept(FileSystemVisitor* visitor) override {
        visitor->visitFile(this);
    }
};

// Concrete Element: Directory
class Directory : public FileSystemElement {
private:
    std::string name;
    std::vector<FileSystemElement*> elements;

public:
    Directory(const std::string& name) : name(name) {}

    void addElement(FileSystemElement* element) {
        elements.push_back(element);
    }

    const std::vector<FileSystemElement*>& getElements() const {
        return elements;
    }

    std::string getName() const {
        return name;
    }

    void accept(FileSystemVisitor* visitor) override {
        visitor->visitDirectory(this);
    }
};

// Concrete Visitor: Calculate total size
class SizeVisitor : public FileSystemVisitor {
private:
    int totalSize = 0;

public:
    void visitFile(File* file) override {
        totalSize += file->getSize();
    }

    void visitDirectory(Directory* directory) override {
        for (auto element : directory->getElements()) {
            element->accept(this);
        }
    }

    int getTotalSize() const {
        return totalSize;
    }
};

// Concrete Visitor: Print file structure
class PrintVisitor : public FileSystemVisitor {
private:
    int indentLevel = 0;

public:
    void visitFile(File* file) override {
        for (int i = 0; i < indentLevel; ++i) {
            std::cout << "  ";
        }
        std::cout << file->getName() << " (" << file->getSize() << " KB)" << std::endl;
    }

    void visitDirectory(Directory* directory) override {
        for (int i = 0; i < indentLevel; ++i) {
            std::cout << "  ";
        }
        std::cout << "[" << directory->getName() << "]" << std::endl;
        indentLevel++;
        for (auto element : directory->getElements()) {
            element->accept(this);
        }
        indentLevel--;
    }
};

// Client code
int main() {
    // Create files
    File* file1 = new File("file1.txt", 100);
    File* file2 = new File("file2.txt", 200);

    // Create directories
    Directory* dir1 = new Directory("documents");
    dir1->addElement(file1);

    Directory* root = new Directory("root");
    root->addElement(dir1);
    root->addElement(file2);

    // Create visitors
    SizeVisitor sizeVisitor;
    PrintVisitor printVisitor;

    // Calculate total size
    root->accept(&sizeVisitor);
    std::cout << "Total size: " << sizeVisitor.getTotalSize() << " KB" << std::endl;

    // Print structure
    root->accept(&printVisitor);

    // Clean up
    delete file1;
    delete file2;
    delete dir1;
    delete root;

    return 0;
}
```

### Explanation:
1. **Visitor (`FileSystemVisitor`)**: Interface that defines operations for visiting files and directories.
2. **Concrete Visitors (`SizeVisitor`, `PrintVisitor`)**: Implement the behavior for visiting files and directories. `SizeVisitor` calculates the total size, and `PrintVisitor` prints the structure.
3. **Element (`FileSystemElement`)**: Abstract class for file system elements, providing an `accept` method for visitors.
4. **Concrete Elements (`File`, `Directory`)**: Implement the `accept` method to allow the visitor to operate on them.
5. **Client**: Creates the file system structure and applies visitors to perform operations.

### Output:
```
Total size: 300 KB
[root]
  [documents]
    file1.txt (100 KB)
  file2.txt (200 KB)
```

### Benefits of the Visitor Pattern:
- **Open/Closed Principle**: You can add new operations without changing the existing classes (by adding new visitors
