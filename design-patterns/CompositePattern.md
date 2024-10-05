The **Composite Pattern** is a structural design pattern that allows you to compose objects into tree-like structures to represent part-whole hierarchies. This pattern enables clients to treat individual objects and compositions of objects uniformly.

The Composite Pattern is useful when you want to:
- Represent a hierarchy of objects (like a tree structure).
- Allow clients to interact with individual objects and groups of objects in the same way.
- Simplify client code by abstracting away the complexity of handling individual and composite objects.

---

### Key Concepts
- **Component**: An interface or abstract class that defines the common operations for both individual objects and compositions.
- **Leaf**: A concrete class that implements the `Component` interface and represents individual objects in the hierarchy.
- **Composite**: A class that implements the `Component` interface and can contain leaf objects or other composite objects.

---

### Example 1: File System

In this example, we create a file system structure where both files and directories can be treated uniformly.

#### Code Example:
```cpp
#include <iostream>
#include <vector>
#include <string>

// Component Interface
class FileSystemComponent {
public:
    virtual void showDetails() = 0;
    virtual ~FileSystemComponent() {}
};

// Leaf Class: File
class File : public FileSystemComponent {
private:
    std::string name;

public:
    File(const std::string& name) : name(name) {}

    void showDetails() override {
        std::cout << "File: " << name << std::endl;
    }
};

// Composite Class: Directory
class Directory : public FileSystemComponent {
private:
    std::string name;
    std::vector<FileSystemComponent*> components;

public:
    Directory(const std::string& name) : name(name) {}

    void add(FileSystemComponent* component) {
        components.push_back(component);
    }

    void showDetails() override {
        std::cout << "Directory: " << name << std::endl;
        for (auto component : components) {
            component->showDetails();
        }
    }

    ~Directory() {
        for (auto component : components) {
            delete component; // Clean up
        }
    }
};

// Client code
int main() {
    Directory* root = new Directory("root");
    Directory* subdir1 = new Directory("subdir1");
    Directory* subdir2 = new Directory("subdir2");

    File* file1 = new File("file1.txt");
    File* file2 = new File("file2.txt");
    File* file3 = new File("file3.txt");

    root->add(file1);
    root->add(subdir1);
    subdir1->add(file2);
    root->add(subdir2);
    subdir2->add(file3);

    // Show the entire file system structure
    root->showDetails();

    delete root; // Clean up

    return 0;
}
```

#### Explanation:
- **Component**: The `FileSystemComponent` interface defines the method `showDetails()`.
- **Leaf (File)**: The `File` class implements the `FileSystemComponent` interface and represents individual files.
- **Composite (Directory)**: The `Directory` class implements the `FileSystemComponent` interface and can contain both files and other directories. It manages its child components and provides the implementation for `showDetails()`.
- **Client**: The client creates a composite structure representing a file system and calls `showDetails()` to display the hierarchy.

---

### Example 2: Graphic Objects

In this example, we create a graphics system where shapes can be individual shapes or groups of shapes.

#### Code Example:
```cpp
#include <iostream>
#include <vector>
#include <string>

// Component Interface
class Graphic {
public:
    virtual void draw() = 0;
    virtual ~Graphic() {}
};

// Leaf Class: Circle
class Circle : public Graphic {
public:
    void draw() override {
        std::cout << "Drawing Circle.\n";
    }
};

// Leaf Class: Rectangle
class Rectangle : public Graphic {
public:
    void draw() override {
        std::cout << "Drawing Rectangle.\n";
    }
};

// Composite Class: GraphicGroup
class GraphicGroup : public Graphic {
private:
    std::vector<Graphic*> graphics;

public:
    void add(Graphic* graphic) {
        graphics.push_back(graphic);
    }

    void draw() override {
        std::cout << "Drawing Graphic Group:\n";
        for (auto graphic : graphics) {
            graphic->draw();
        }
    }

    ~GraphicGroup() {
        for (auto graphic : graphics) {
            delete graphic; // Clean up
        }
    }
};

// Client code
int main() {
    GraphicGroup* group = new GraphicGroup();

    Graphic* circle = new Circle();
    Graphic* rectangle = new Rectangle();
    GraphicGroup* innerGroup = new GraphicGroup();

    innerGroup->add(new Circle());
    innerGroup->add(new Rectangle());

    group->add(circle);
    group->add(rectangle);
    group->add(innerGroup);

    // Draw the entire graphic structure
    group->draw();

    delete group; // Clean up

    return 0;
}
```

#### Explanation:
- **Component**: The `Graphic` interface defines the method `draw()`.
- **Leaf (Circle, Rectangle)**: The `Circle` and `Rectangle` classes implement the `Graphic` interface and represent individual shapes.
- **Composite (GraphicGroup)**: The `GraphicGroup` class implements the `Graphic` interface and can contain individual shapes or other graphic groups. It manages its child graphics and provides the implementation for `draw()`.
- **Client**: The client creates a composite structure representing a group of graphics and calls `draw()` to render the entire hierarchy.

---

### Example 3: Organization Structure

In this example, we model an organization with employees and departments, where departments can contain both employees and other departments.

#### Code Example:
```cpp
#include <iostream>
#include <vector>
#include <string>

// Component Interface
class OrganizationComponent {
public:
    virtual void showInfo() = 0;
    virtual ~OrganizationComponent() {}
};

// Leaf Class: Employee
class Employee : public OrganizationComponent {
private:
    std::string name;
    std::string position;

public:
    Employee(const std::string& name, const std::string& position) : name(name), position(position) {}

    void showInfo() override {
        std::cout << "Employee: " << name << ", Position: " << position << std::endl;
    }
};

// Composite Class: Department
class Department : public OrganizationComponent {
private:
    std::string name;
    std::vector<OrganizationComponent*> members;

public:
    Department(const std::string& name) : name(name) {}

    void add(OrganizationComponent* member) {
        members.push_back(member);
    }

    void showInfo() override {
        std::cout << "Department: " << name << std::endl;
        for (auto member : members) {
            member->showInfo();
        }
    }

    ~Department() {
        for (auto member : members) {
            delete member; // Clean up
        }
    }
};

// Client code
int main() {
    Department* root = new Department("Head Office");
    Department* salesDept = new Department("Sales Department");
    Department* devDept = new Department("Development Department");

    Employee* emp1 = new Employee("Alice", "Sales Manager");
    Employee* emp2 = new Employee("Bob", "Sales Associate");
    Employee* emp3 = new Employee("Charlie", "Software Engineer");

    salesDept->add(emp1);
    salesDept->add(emp2);
    devDept->add(emp3);
    root->add(salesDept);
    root->add(devDept);

    // Show the organization structure
    root->showInfo();

    delete root; // Clean up

    return 0;
}
```

#### Explanation:
- **Component**: The `OrganizationComponent` interface defines the method `showInfo()`.
- **Leaf (Employee)**: The `Employee` class implements the `OrganizationComponent` interface and represents individual employees.
- **Composite (Department)**: The `Department` class implements the `OrganizationComponent` interface and can contain both employees and other departments. It manages its members and provides the implementation for `showInfo()`.
- **Client**: The client creates a composite structure representing an organization and calls `showInfo()` to display the entire hierarchy.

---

### Key Points:
- The **Composite Pattern** allows you to treat individual objects and compositions uniformly, enabling clients to work with complex tree structures easily.
- It simplifies client code by providing a single interface for both individual and composite objects, allowing operations to be performed without concern for the specific types of components.
- The pattern promotes the design principle of "composing objects" to achieve flexibility and reuse in code, making it easier to manage and extend.
