The **State Pattern** is a behavioral design pattern that allows an object to alter its behavior when its internal state changes. This pattern is useful for managing state transitions in a clean and organized way, enabling objects to appear as if they changed their class.

### Key Components
- **Context**: The class that maintains an instance of a `State` subclass that defines the current state.
- **State**: An interface or abstract class that declares methods related to the state-specific behavior.
- **ConcreteState**: Classes that implement the `State` interface and define specific behaviors for each state.

### Example: TCP Connection

In this example, we will implement a simple TCP connection using the State Pattern. The connection can be in one of three states: **Closed**, **Listening**, and **Established**.

#### Code Example
```cpp
#include <iostream>
#include <memory>

// Forward declaration of Context
class TCPConnection;

// State Interface
class TCPState {
public:
    virtual void open(TCPConnection* connection) = 0;
    virtual void close(TCPConnection* connection) = 0;
    virtual void listen(TCPConnection* connection) = 0;
    virtual void send(TCPConnection* connection, const std::string& message) = 0;
    virtual ~TCPState() {}
};

// Context Class
class TCPConnection {
private:
    std::unique_ptr<TCPState> state;

public:
    TCPConnection(std::unique_ptr<TCPState> initialState) : state(std::move(initialState)) {}

    void setState(std::unique_ptr<TCPState> newState) {
        state = std::move(newState);
    }

    void open() {
        state->open(this);
    }

    void close() {
        state->close(this);
    }

    void listen() {
        state->listen(this);
    }

    void send(const std::string& message) {
        state->send(this, message);
    }
};

// Concrete States
class ClosedState : public TCPState {
public:
    void open(TCPConnection* connection) override {
        std::cout << "Opening connection..." << std::endl;
        connection->setState(std::make_unique<ListeningState>());
    }

    void close(TCPConnection* connection) override {
        std::cout << "Connection is already closed." << std::endl;
    }

    void listen(TCPConnection* connection) override {
        std::cout << "Can't listen, the connection is closed." << std::endl;
    }

    void send(TCPConnection* connection, const std::string& message) override {
        std::cout << "Can't send message, the connection is closed." << std::endl;
    }
};

class ListeningState : public TCPState {
public:
    void open(TCPConnection* connection) override {
        std::cout << "Connection is already open." << std::endl;
    }

    void close(TCPConnection* connection) override {
        std::cout << "Closing connection..." << std::endl;
        connection->setState(std::make_unique<ClosedState>());
    }

    void listen(TCPConnection* connection) override {
        std::cout << "Listening for incoming connections..." << std::endl;
        connection->setState(std::make_unique<EstablishedState>());
    }

    void send(TCPConnection* connection, const std::string& message) override {
        std::cout << "Can't send message, the connection is in listening state." << std::endl;
    }
};

class EstablishedState : public TCPState {
public:
    void open(TCPConnection* connection) override {
        std::cout << "Connection is already established." << std::endl;
    }

    void close(TCPConnection* connection) override {
        std::cout << "Closing connection..." << std::endl;
        connection->setState(std::make_unique<ClosedState>());
    }

    void listen(TCPConnection* connection) override {
        std::cout << "Can't listen, the connection is already established." << std::endl;
    }

    void send(TCPConnection* connection, const std::string& message) override {
        std::cout << "Sending message: " << message << std::endl;
    }
};

// Client code
int main() {
    TCPConnection connection(std::make_unique<ClosedState>());

    connection.open();               // Transition to Listening State
    connection.listen();             // Transition to Established State
    connection.send("Hello!");      // Send message
    connection.close();              // Transition back to Closed State

    return 0;
}
```

### Explanation
1. **Context (`TCPConnection`)**: Maintains a reference to the current state and allows state transitions.
2. **State Interface (`TCPState`)**: Declares methods that represent actions (`open`, `close`, `listen`, `send`).
3. **Concrete States**: 
   - **ClosedState**: Defines behavior when the connection is closed. It can open the connection and transition to `ListeningState`.
   - **ListeningState**: Defines behavior when the connection is listening. It can close the connection or establish it.
   - **EstablishedState**: Defines behavior when the connection is established. It can close the connection or send messages.
4. **Client**: The client code creates a `TCPConnection` in the `ClosedState` and performs various operations, transitioning through the states as defined.

### Example 2: Vending Machine

Here’s a simple example of a vending machine using the State Pattern. The vending machine can be in three states: **NoCoin**, **HasCoin**, and **Sold**.

#### Code Example
```cpp
#include <iostream>
#include <memory>

// Forward declaration of VendingMachine
class VendingMachine;

// State Interface
class State {
public:
    virtual void insertCoin(VendingMachine* machine) = 0;
    virtual void ejectCoin(VendingMachine* machine) = 0;
    virtual void selectProduct(VendingMachine* machine) = 0;
    virtual void dispenseProduct(VendingMachine* machine) = 0;
    virtual ~State() {}
};

// Context Class
class VendingMachine {
private:
    std::unique_ptr<State> state;

public:
    VendingMachine(std::unique_ptr<State> initialState) : state(std::move(initialState)) {}

    void setState(std::unique_ptr<State> newState) {
        state = std::move(newState);
    }

    void insertCoin() {
        state->insertCoin(this);
    }

    void ejectCoin() {
        state->ejectCoin(this);
    }

    void selectProduct() {
        state->selectProduct(this);
    }

    void dispenseProduct() {
        state->dispenseProduct(this);
    }
};

// Concrete States
class NoCoinState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "Coin inserted. You can select a product." << std::endl;
        machine->setState(std::make_unique<HasCoinState>());
    }

    void ejectCoin(VendingMachine* machine) override {
        std::cout << "No coin to eject." << std::endl;
    }

    void selectProduct(VendingMachine* machine) override {
        std::cout << "You need to insert a coin first." << std::endl;
    }

    void dispenseProduct(VendingMachine* machine) override {
        std::cout << "No product dispensed. Insert a coin." << std::endl;
    }
};

class HasCoinState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "Coin already inserted." << std::endl;
    }

    void ejectCoin(VendingMachine* machine) override {
        std::cout << "Coin ejected." << std::endl;
        machine->setState(std::make_unique<NoCoinState>());
    }

    void selectProduct(VendingMachine* machine) override {
        std::cout << "Product selected." << std::endl;
        machine->setState(std::make_unique<SoldState>());
    }

    void dispenseProduct(VendingMachine* machine) override {
        std::cout << "You need to select a product first." << std::endl;
    }
};

class SoldState : public State {
public:
    void insertCoin(VendingMachine* machine) override {
        std::cout << "Please wait, we're already dispensing a product." << std::endl;
    }

    void ejectCoin(VendingMachine* machine) override {
        std::cout << "Can't eject, product is being dispensed." << std::endl;
    }

    void selectProduct(VendingMachine* machine) override {
        std::cout << "Already dispensing a product." << std::endl;
    }

    void dispenseProduct(VendingMachine* machine) override {
        std::cout << "Dispensing product." << std::endl;
        machine->setState(std::make_unique<NoCoinState>());
    }
};

// Client code
int main() {
    VendingMachine vendingMachine(std::make_unique<NoCoinState>());

    vendingMachine.insertCoin();          // Insert a coin
    vendingMachine.selectProduct();       // Select a product
    vendingMachine.dispenseProduct();     // Dispense the product

    vendingMachine.ejectCoin();           // Can't eject, product already dispensed
    vendingMachine.insertCoin();          // Insert a new coin

    return 0;
}
```

### Explanation
1. **Context (`VendingMachine`)**: Manages the current state of the vending machine and provides methods to interact with it.
2. **State Interface (`State`)**: Declares methods for the actions that can be performed in different states.
3. **Concrete States**:
   - **NoCoinState**: Defines behavior when no coin is inserted. It allows inserting a coin and provides appropriate responses for
