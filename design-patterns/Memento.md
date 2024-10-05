The **Memento Pattern** is a behavioral design pattern that allows an object to capture and store its internal state so that it can be restored to that state later without exposing its internal details. This pattern is useful for implementing undo/redo functionality, saving checkpoints in a system, or persisting snapshots of an object’s state.

### Key Components:
1. **Originator**: The object whose state you want to save and restore. It creates a memento representing its current state and can restore its state from a memento.
2. **Memento**: This object stores the state of the `Originator`. It is opaque and should not allow direct access to the saved state by any external object, maintaining encapsulation.
3. **Caretaker**: Responsible for keeping track of mementos, but does not modify or inspect the mementos' content. It simply stores and retrieves mementos for the `Originator`.

### Example: Text Editor with Undo/Redo Functionality

Let’s implement a simple text editor that allows saving and restoring its content using the Memento pattern.

#### Code Example

```cpp
#include <iostream>
#include <string>
#include <stack>

// Memento: Stores the state of the TextEditor
class TextEditorMemento {
private:
    std::string state;

public:
    TextEditorMemento(const std::string& state) : state(state) {}
    std::string getState() const { return state; }
};

// Originator: The TextEditor which creates and restores its state
class TextEditor {
private:
    std::string content;

public:
    void write(const std::string& text) {
        content += text;
    }

    std::string getContent() const {
        return content;
    }

    // Save the current state in a Memento
    TextEditorMemento save() const {
        return TextEditorMemento(content);
    }

    // Restore the state from a Memento
    void restore(const TextEditorMemento& memento) {
        content = memento.getState();
    }
};

// Caretaker: Maintains a stack of Mementos for undo functionality
class Caretaker {
private:
    std::stack<TextEditorMemento> history;

public:
    void save(const TextEditor& editor) {
        history.push(editor.save());
    }

    void undo(TextEditor& editor) {
        if (!history.empty()) {
            editor.restore(history.top());
            history.pop();
        }
    }
};

// Client code
int main() {
    TextEditor editor;
    Caretaker caretaker;

    // Write some text and save state
    editor.write("Hello, ");
    caretaker.save(editor);

    editor.write("World!");
    caretaker.save(editor);

    std::cout << "Current content: " << editor.getContent() << std::endl;  // Output: Hello, World!

    // Undo the last change
    caretaker.undo(editor);
    std::cout << "After undo: " << editor.getContent() << std::endl;  // Output: Hello,

    // Undo again
    caretaker.undo(editor);
    std::cout << "After second undo: " << editor.getContent() << std::endl;  // Output: Hello,

    return 0;
}
```

### Explanation:
1. **Memento (`TextEditorMemento`)**: Stores the state (content) of the `TextEditor`. It provides a method to access the saved state, which is used by the originator for restoration.
2. **Originator (`TextEditor`)**: The object whose state we want to save and restore. It provides a `save()` method to create a memento, and a `restore()` method to return to a previously saved state.
3. **Caretaker (`Caretaker`)**: Responsible for managing the mementos. It stores them in a stack, which allows undo functionality by popping the last memento and restoring the state.
4. **Client**: Uses the text editor to write content and utilizes the caretaker to save and restore states.

### Example 2: Game Save and Load System

In this example, a video game stores its player’s state (level and health) and allows the player to load previous states using the Memento pattern.

#### Code Example

```cpp
#include <iostream>
#include <string>
#include <stack>

// Memento: Stores the player's state
class PlayerMemento {
private:
    int level;
    int health;

public:
    PlayerMemento(int level, int health) : level(level), health(health) {}

    int getLevel() const { return level; }
    int getHealth() const { return health; }
};

// Originator: The player who can save and restore their state
class Player {
private:
    int level;
    int health;

public:
    Player(int level, int health) : level(level), health(health) {}

    void setLevel(int newLevel) {
        level = newLevel;
    }

    void setHealth(int newHealth) {
        health = newHealth;
    }

    void displayState() const {
        std::cout << "Player Level: " << level << ", Health: " << health << std::endl;
    }

    // Save the current state in a Memento
    PlayerMemento save() const {
        return PlayerMemento(level, health);
    }

    // Restore the state from a Memento
    void restore(const PlayerMemento& memento) {
        level = memento.getLevel();
        health = memento.getHealth();
    }
};

// Caretaker: Manages the saved game states
class GameSaveManager {
private:
    std::stack<PlayerMemento> saveHistory;

public:
    void saveGame(const Player& player) {
        saveHistory.push(player.save());
    }

    void loadGame(Player& player) {
        if (!saveHistory.empty()) {
            player.restore(saveHistory.top());
            saveHistory.pop();
        } else {
            std::cout << "No saved states to load." << std::endl;
        }
    }
};

// Client code
int main() {
    Player player(1, 100);
    GameSaveManager saveManager;

    // Display initial state
    player.displayState();

    // Progress the game
    player.setLevel(2);
    player.setHealth(80);
    player.displayState();
    
    // Save the game state
    saveManager.saveGame(player);

    // Further progress the game
    player.setLevel(3);
    player.setHealth(50);
    player.displayState();

    // Load the saved game state
    saveManager.loadGame(player);
    player.displayState();  // Output: Player Level: 2, Health: 80

    return 0;
}
```

### Explanation:
1. **Memento (`PlayerMemento`)**: Stores the player's state, including their level and health. It allows the `Player` to save and restore these values.
2. **Originator (`Player`)**: Represents the player object, which has attributes like level and health. It provides methods to save and restore its state.
3. **Caretaker (`GameSaveManager`)**: Manages the player’s save history by storing the mementos. It can restore the player’s state to a previous save.
4. **Client**: Simulates a video game where the player’s state changes, is saved, and can be restored.

### Key Points:
- The **Memento Pattern** is useful for capturing and restoring an object's state without violating encapsulation. It allows an object to rollback or undo changes.
- Care must be taken to avoid storing excessive or unnecessary state in the memento, as this can increase memory usage.
- This pattern is often used in systems requiring undo/redo functionality, game save/load systems, or any situation where state needs to be checkpointed and restored later.

