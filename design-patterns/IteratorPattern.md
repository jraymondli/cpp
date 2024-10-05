The **Iterator Pattern** is a behavioral design pattern that provides a way to access elements of a collection (such as an array or a list) sequentially without exposing the underlying representation. This pattern allows for the iteration over a collection's elements in a unified manner, regardless of the collection's type.

### Key Components
- **Iterator**: Defines the interface for accessing and traversing elements.
- **Concrete Iterator**: Implements the `Iterator` interface, providing specific implementation for iterating over the collection.
- **Aggregate**: Defines an interface for creating an `Iterator`.
- **Concrete Aggregate**: Implements the `Aggregate` interface and creates an instance of the concrete iterator for the collection.

### Example: Custom List Iterator

Let’s implement a custom list class that allows iteration using the iterator pattern.

#### Code Example

```cpp
#include <iostream>
#include <vector>

// Iterator Interface
template <typename T>
class Iterator {
public:
    virtual ~Iterator() {}
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};

// Concrete Iterator for a vector
template <typename T>
class VectorIterator : public Iterator<T> {
private:
    const std::vector<T>& data;
    size_t index = 0;

public:
    VectorIterator(const std::vector<T>& vec) : data(vec) {}

    bool hasNext() const override {
        return index < data.size();
    }

    T next() override {
        return data[index++];
    }
};

// Aggregate Interface
template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() {}
    virtual Iterator<T>* createIterator() const = 0;
};

// Concrete Aggregate (Collection)
template <typename T>
class CustomList : public Aggregate<T> {
private:
    std::vector<T> elements;

public:
    void add(const T& element) {
        elements.push_back(element);
    }

    Iterator<T>* createIterator() const override {
        return new VectorIterator<T>(elements);
    }

    size_t size() const {
        return elements.size();
    }
};

// Client Code
int main() {
    // Create a collection
    CustomList<int> myList;
    myList.add(1);
    myList.add(2);
    myList.add(3);
    myList.add(4);

    // Get an iterator for the collection
    Iterator<int>* it = myList.createIterator();

    // Iterate through the collection using the iterator
    while (it->hasNext()) {
        std::cout << it->next() << " ";
    }
    std::cout << std::endl;

    // Clean up
    delete it;

    return 0;
}
```

### Explanation
1. **Iterator Interface (`Iterator`)**: Defines the interface for accessing elements with the methods `hasNext()` and `next()`. This allows the client to traverse elements without exposing the underlying collection structure.
2. **Concrete Iterator (`VectorIterator`)**: Implements the `Iterator` interface for a `std::vector`, managing the current index and retrieving elements.
3. **Aggregate Interface (`Aggregate`)**: Defines a method for creating an `Iterator`.
4. **Concrete Aggregate (`CustomList`)**: A custom list collection that stores elements in a `std::vector`. It implements the `Aggregate` interface to return an iterator (`VectorIterator`).
5. **Client**: The client uses the `CustomList` and its iterator to traverse and print elements without knowing how the list is implemented internally.

### Example 2: Iterator for a Custom Linked List

We can also use the Iterator pattern with a custom `LinkedList` data structure.

#### Code Example

```cpp
#include <iostream>

// Node structure for LinkedList
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T data) : data(data), next(nullptr) {}
};

// Iterator Interface
template <typename T>
class Iterator {
public:
    virtual ~Iterator() {}
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};

// Concrete Iterator for LinkedList
template <typename T>
class LinkedListIterator : public Iterator<T> {
private:
    Node<T>* currentNode;

public:
    LinkedListIterator(Node<T>* head) : currentNode(head) {}

    bool hasNext() const override {
        return currentNode != nullptr;
    }

    T next() override {
        T value = currentNode->data;
        currentNode = currentNode->next;
        return value;
    }
};

// Aggregate Interface
template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() {}
    virtual Iterator<T>* createIterator() const = 0;
};

// Concrete Aggregate (LinkedList)
template <typename T>
class LinkedList : public Aggregate<T> {
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

public:
    void add(const T& element) {
        Node<T>* newNode = new Node<T>(element);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    Iterator<T>* createIterator() const override {
        return new LinkedListIterator<T>(head);
    }

    ~LinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Client Code
int main() {
    // Create a LinkedList
    LinkedList<int> linkedList;
    linkedList.add(10);
    linkedList.add(20);
    linkedList.add(30);

    // Get an iterator for the LinkedList
    Iterator<int>* iterator = linkedList.createIterator();

    // Iterate through the LinkedList
    while (iterator->hasNext()) {
        std::cout << iterator->next() << " ";
    }
    std::cout << std::endl;

    // Clean up
    delete iterator;

    return 0;
}
```

### Explanation
1. **Iterator Interface (`Iterator`)**: The same interface as the previous example, allowing us to define `hasNext()` and `next()` for any collection.
2. **Concrete Iterator (`LinkedListIterator`)**: Implements `Iterator` for a custom `LinkedList`. The `next()` method traverses the linked list node by node.
3. **Aggregate Interface (`Aggregate`)**: Defines the `createIterator()` method to get an iterator for a custom collection.
4. **Concrete Aggregate (`LinkedList`)**: A custom linked list that implements `Aggregate`. It maintains a list of nodes (`Node`), adding elements at the tail. It provides an iterator that traverses the list from head to tail.
5. **Client**: The client code uses the `LinkedList` and its iterator to traverse the linked list in sequence.

### Key Points
- The **Iterator Pattern** abstracts the traversal of a collection, making it easy to iterate over various collection types without exposing their internal structure.
- It helps reduce the complexity of managing collections and improves maintainability by decoupling iteration logic from collection logic.
- The pattern supports multiple traversal strategies, allowing the implementation of different iterators for the same collection.
