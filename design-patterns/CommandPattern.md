The **Command Pattern** is a behavioral design pattern that encapsulates a request as an object, thereby allowing for parameterization of clients with queues, requests, and operations. This pattern is useful for implementing features like undo/redo functionality, logging, and queuing of operations.

The Command Pattern consists of the following components:
- **Command**: An interface that declares a method for executing a command.
- **ConcreteCommand**: Implements the Command interface and defines the binding between a receiver and an action.
- **Receiver**: The object that performs the actual work when the command is executed.
- **Invoker**: The object that holds the command and invokes it when needed.
- **Client**: The object that creates and configures the commands.

---

### Example 1: Simple Remote Control

In this example, we create a simple remote control system that can turn on and off a light.

#### Code Example:
```cpp
#include <iostream>
#include <memory>

// Receiver
class Light {
public:
    void turnOn() {
        std::cout << "Light is ON" << std::endl;
    }

    void turnOff() {
        std::cout << "Light is OFF" << std::endl;
    }
};

// Command Interface
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

// Concrete Commands
class TurnOnCommand : public Command {
private:
    Light* light;

public:
    TurnOnCommand(Light* l) : light(l) {}

    void execute() override {
        light->turnOn();
    }
};

class TurnOffCommand : public Command {
private:
    Light* light;

public:
    TurnOffCommand(Light* l) : light(l) {}

    void execute() override {
        light->turnOff();
    }
};

// Invoker
class RemoteControl {
private:
    Command* command;

public:
    void setCommand(Command* cmd) {
        command = cmd;
    }

    void pressButton() {
        command->execute();
    }
};

// Client code
int main() {
    Light light;

    TurnOnCommand turnOn(&light);
    TurnOffCommand turnOff(&light);

    RemoteControl remote;

    // Turn on the light
    remote.setCommand(&turnOn);
    remote.pressButton();

    // Turn off the light
    remote.setCommand(&turnOff);
    remote.pressButton();

    return 0;
}
```

#### Explanation:
- **Receiver**: The `Light` class has methods to turn the light on and off.
- **Command Interface**: The `Command` interface declares the `execute()` method.
- **Concrete Commands**: `TurnOnCommand` and `TurnOffCommand` implement the `Command` interface, encapsulating the actions to turn the light on and off, respectively.
- **Invoker**: The `RemoteControl` class holds a command and invokes it when the button is pressed.
- **Client**: The client creates instances of `Light`, `TurnOnCommand`, and `TurnOffCommand`, and sets the commands on the remote to control the light.

---

### Example 2: Text Editor with Undo/Redo

In this example, we create a simple text editor that can execute and undo commands for typing text.

#### Code Example:
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Command Interface
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// Receiver
class TextEditor {
private:
    std::string text;

public:
    void addText(const std::string& newText) {
        text += newText;
        std::cout << "Current Text: " << text << std::endl;
    }

    void removeText(size_t length) {
        if (length > text.length()) {
            length = text.length();
        }
        text.erase(text.length() - length);
        std::cout << "Current Text: " << text << std::endl;
    }
};

// Concrete Command to Add Text
class AddTextCommand : public Command {
private:
    TextEditor* editor;
    std::string text;

public:
    AddTextCommand(TextEditor* e, const std::string& t) : editor(e), text(t) {}

    void execute() override {
        editor->addText(text);
    }

    void undo() override {
        editor->removeText(text.length());
    }
};

// Invoker
class CommandManager {
private:
    std::vector<std::shared_ptr<Command>> history;

public:
    void executeCommand(const std::shared_ptr<Command>& cmd) {
        cmd->execute();
        history.push_back(cmd);
    }

    void undoLastCommand() {
        if (!history.empty()) {
            history.back()->undo();
            history.pop_back();
        }
    }
};

// Client code
int main() {
    TextEditor editor;
    CommandManager manager;

    // Execute some commands
    manager.executeCommand(std::make_shared<AddTextCommand>(&editor, "Hello "));
    manager.executeCommand(std::make_shared<AddTextCommand>(&editor, "World!"));

    // Undo the last command
    manager.undoLastCommand(); // Removes "World!"

    // Execute another command
    manager.executeCommand(std::make_shared<AddTextCommand>(&editor, "Flyweight Pattern"));

    return 0;
}
```

#### Explanation:
- **Receiver**: The `TextEditor` class manages the text and has methods for adding and removing text.
- **Command Interface**: The `Command` interface declares `execute()` and `undo()` methods.
- **Concrete Command**: The `AddTextCommand` class implements the `Command` interface, encapsulating the action of adding text and the action of removing text when undoing.
- **Invoker**: The `CommandManager` class executes commands and keeps track of the command history for undoing.
- **Client**: The client code creates a `TextEditor` and a `CommandManager`, executing commands to manipulate text and undoing the last command when needed.

---

### Key Points:
- The **Command Pattern** decouples the sender of a request from its receiver, allowing for flexible command management.
- It enables features like undo/redo, queuing of commands, and logging of operations.
- The pattern encapsulates commands as objects, promoting encapsulation and extensibility in applications.
