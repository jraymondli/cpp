The **Mediator Pattern** is a behavioral design pattern that defines an object, called the **mediator**, which encapsulates how a set of objects interact. Instead of allowing objects to communicate directly with each other (which creates dependencies between them), they communicate through the mediator. This reduces the dependencies between interacting objects, promoting loose coupling.

### Key Components
- **Mediator**: An interface that defines how the objects communicate with each other.
- **Concrete Mediator**: Implements the mediator interface and handles the communication between different objects.
- **Colleague**: These are the objects (components) that interact with each other indirectly through the mediator.
- **Concrete Colleague**: Implements the colleague objects that communicate via the mediator.

### Example: A Chatroom System

In this example, we'll create a simple chatroom system where users communicate via a **ChatMediator**. Instead of users sending messages directly to each other, the messages go through the mediator.

#### Code Example

```cpp
#include <iostream>
#include <string>
#include <vector>

// Mediator Interface
class ChatMediator {
public:
    virtual void sendMessage(const std::string& message, class User* user) = 0;
    virtual void addUser(User* user) = 0;
};

// Colleague (User)
class User {
protected:
    ChatMediator* mediator;
    std::string name;

public:
    User(ChatMediator* mediator, const std::string& name) : mediator(mediator), name(name) {}
    virtual void send(const std::string& message) = 0;
    virtual void receive(const std::string& message) = 0;
    std::string getName() const { return name; }
};

// Concrete Mediator (Chat Room)
class ChatRoomMediator : public ChatMediator {
private:
    std::vector<User*> users;

public:
    void addUser(User* user) override {
        users.push_back(user);
    }

    void sendMessage(const std::string& message, User* user) override {
        for (User* u : users) {
            if (u != user) { // Don't send message to the sender
                u->receive(message);
            }
        }
    }
};

// Concrete Colleague (User Implementation)
class ConcreteUser : public User {
public:
    ConcreteUser(ChatMediator* mediator, const std::string& name) : User(mediator, name) {}

    void send(const std::string& message) override {
        std::cout << name << " sends message: " << message << std::endl;
        mediator->sendMessage(message, this);
    }

    void receive(const std::string& message) override {
        std::cout << name << " received message: " << message << std::endl;
    }
};

// Client Code
int main() {
    // Create the mediator (chatroom)
    ChatMediator* chatMediator = new ChatRoomMediator();

    // Create users and register them to the chatroom
    User* user1 = new ConcreteUser(chatMediator, "Alice");
    User* user2 = new ConcreteUser(chatMediator, "Bob");
    User* user3 = new ConcreteUser(chatMediator, "Charlie");

    chatMediator->addUser(user1);
    chatMediator->addUser(user2);
    chatMediator->addUser(user3);

    // Users send messages through the mediator
    user1->send("Hello everyone!");
    user2->send("Hi Alice!");

    // Clean up
    delete user1;
    delete user2;
    delete user3;
    delete chatMediator;

    return 0;
}
```

### Explanation
1. **Mediator Interface (`ChatMediator`)**: Defines how users will communicate with each other via the mediator. It has methods for sending messages and adding users.
2. **Concrete Mediator (`ChatRoomMediator`)**: Implements the `ChatMediator` interface, providing the logic for broadcasting messages to all users except the sender.
3. **Colleague (`User`)**: Represents a user who can send and receive messages. Instead of communicating directly with other users, a user interacts via the mediator.
4. **Concrete Colleague (`ConcreteUser`)**: Implements the `User` interface and uses the mediator to send messages. It also defines how the user will receive messages.
5. **Client**: In the client code, users are created and added to the chatroom (mediator). Messages are sent and received through the mediator, ensuring loose coupling between users.

### Example 2: Air Traffic Control System

In this example, an air traffic control system serves as a mediator between aircraft. Instead of communicating directly with each other, aircraft send messages to the mediator, which coordinates safe landings and take-offs.

#### Code Example

```cpp
#include <iostream>
#include <string>
#include <vector>

// Mediator Interface (Control Tower)
class ATCMediator {
public:
    virtual void notify(const std::string& message, class Aircraft* aircraft) = 0;
};

// Colleague (Aircraft)
class Aircraft {
protected:
    ATCMediator* mediator;
    std::string id;

public:
    Aircraft(ATCMediator* mediator, const std::string& id) : mediator(mediator), id(id) {}
    virtual void land() = 0;
    virtual void takeOff() = 0;
    std::string getId() const { return id; }
};

// Concrete Mediator (Air Traffic Control)
class ControlTower : public ATCMediator {
private:
    std::vector<Aircraft*> aircrafts;

public:
    void addAircraft(Aircraft* aircraft) {
        aircrafts.push_back(aircraft);
    }

    void notify(const std::string& message, Aircraft* aircraft) override {
        for (Aircraft* a : aircrafts) {
            if (a != aircraft) {
                std::cout << a->getId() << " received: " << message << std::endl;
            }
        }
    }
};

// Concrete Colleague (Aircraft Implementation)
class PassengerPlane : public Aircraft {
public:
    PassengerPlane(ATCMediator* mediator, const std::string& id) : Aircraft(mediator, id) {}

    void land() override {
        std::cout << id << " requests landing permission." << std::endl;
        mediator->notify(id + " is landing.", this);
    }

    void takeOff() override {
        std::cout << id << " requests takeoff permission." << std::endl;
        mediator->notify(id + " is taking off.", this);
    }
};

// Client Code
int main() {
    // Create the mediator (Control Tower)
    ATCMediator* controlTower = new ControlTower();

    // Create aircrafts
    Aircraft* plane1 = new PassengerPlane(controlTower, "Flight A123");
    Aircraft* plane2 = new PassengerPlane(controlTower, "Flight B456");
    Aircraft* plane3 = new PassengerPlane(controlTower, "Flight C789");

    // Add aircrafts to the control tower
    controlTower->addAircraft(plane1);
    controlTower->addAircraft(plane2);
    controlTower->addAircraft(plane3);

    // Planes request landing and takeoff via the control tower
    plane1->land();
    plane2->takeOff();

    // Clean up
    delete plane1;
    delete plane2;
    delete plane3;
    delete controlTower;

    return 0;
}
```

### Explanation
1. **Mediator Interface (`ATCMediator`)**: Defines how aircraft will communicate with the control tower. It has a method `notify` for broadcasting messages to all aircraft.
2. **Concrete Mediator (`ControlTower`)**: Implements the mediator interface. It handles messages from aircraft and notifies other aircraft about landing and takeoff statuses.
3. **Colleague (`Aircraft`)**: Represents an aircraft. Instead of communicating directly with other aircraft, it interacts with the mediator.
4. **Concrete Colleague (`PassengerPlane`)**: Implements the `Aircraft` interface. It requests landing and takeoff permissions from the control tower (mediator).
5. **Client**: In the client code, aircraft are created and added to the control tower. Landing and takeoff requests are handled via the control tower, ensuring no direct communication between planes.

### Key Points
- The **Mediator Pattern** reduces coupling between interacting objects by introducing a mediator that coordinates the communication.
- It centralizes complex communication logic into one class, making the system easier to maintain and extend.
- The mediator can coordinate multiple types of interactions, ensuring that objects remain decoupled and focused on their primary responsibilities.

This pattern is often used in scenarios where multiple objects need to communicate, such as user interfaces, chat systems, or control systems.
