The **Adapter Pattern** is a structural design pattern that allows objects with incompatible interfaces to work together. It acts as a bridge between two incompatible interfaces, enabling them to communicate by translating one interface into another.

The **Adapter** class implements the target interface and wraps the adaptee (the incompatible class) to make it compatible with the client.

---

### Key Concepts
- **Target Interface**: The interface expected by the client.
- **Adaptee**: The existing interface that needs adapting.
- **Adapter**: The class that adapts the Adaptee to the Target interface by implementing the Target interface and internally calling methods on the Adaptee.
- **Client**: The class that uses the Target interface.

---

### Example 1: Simple Adapter (Adapting a Third-Party Library)

In this example, we have a client that expects to work with a simple audio player, but the actual implementation uses a more advanced library with a different interface. The Adapter pattern bridges the gap between the two.

#### Code Example:
```cpp
#include <iostream>
#include <string>

// Target Interface
class MediaPlayer {
public:
    virtual void play(const std::string& audioType, const std::string& fileName) = 0;
    virtual ~MediaPlayer() = default;
};

// Adaptee (Existing, incompatible interface)
class AdvancedMediaPlayer {
public:
    void playMp4(const std::string& fileName) {
        std::cout << "Playing mp4 file: " << fileName << "\n";
    }
    void playVlc(const std::string& fileName) {
        std::cout << "Playing vlc file: " << fileName << "\n";
    }
};

// Adapter that makes AdvancedMediaPlayer compatible with MediaPlayer
class MediaAdapter : public MediaPlayer {
private:
    AdvancedMediaPlayer* advancedPlayer;

public:
    MediaAdapter(const std::string& audioType) {
        advancedPlayer = new AdvancedMediaPlayer();
    }

    ~MediaAdapter() {
        delete advancedPlayer;
    }

    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp4") {
            advancedPlayer->playMp4(fileName);
        } else if (audioType == "vlc") {
            advancedPlayer->playVlc(fileName);
        }
    }
};

// Client (works with Target Interface)
class AudioPlayer : public MediaPlayer {
private:
    MediaAdapter* mediaAdapter;

public:
    void play(const std::string& audioType, const std::string& fileName) override {
        if (audioType == "mp3") {
            std::cout << "Playing mp3 file: " << fileName << "\n";
        } else if (audioType == "mp4" || audioType == "vlc") {
            mediaAdapter = new MediaAdapter(audioType);
            mediaAdapter->play(audioType, fileName);
            delete mediaAdapter;
        } else {
            std::cout << "Invalid media. " << audioType << " format not supported\n";
        }
    }
};

int main() {
    AudioPlayer audioPlayer;
    
    audioPlayer.play("mp3", "song.mp3");
    audioPlayer.play("mp4", "movie.mp4");
    audioPlayer.play("vlc", "documentary.vlc");
    audioPlayer.play("avi", "unknown.avi");

    return 0;
}
```

#### Explanation:
- **Target Interface**: `MediaPlayer` defines the interface the client (`AudioPlayer`) expects.
- **Adaptee**: `AdvancedMediaPlayer` has an incompatible interface with methods like `playMp4()` and `playVlc()`.
- **Adapter**: `MediaAdapter` implements `MediaPlayer` and adapts the methods of `AdvancedMediaPlayer` to be compatible with `MediaPlayer`.
- **Client**: `AudioPlayer` uses the `MediaPlayer` interface and can seamlessly work with both `mp3` files and the `AdvancedMediaPlayer` formats (`mp4` and `vlc`).

---

### Example 2: Class Adapter (Multiple Inheritance)

C++ supports multiple inheritance, allowing for an alternate implementation of the Adapter pattern using inheritance. The Adapter can inherit from both the Target and Adaptee classes to adapt the interfaces.

#### Code Example:
```cpp
#include <iostream>
#include <string>

// Target Interface
class Target {
public:
    virtual void request() const {
        std::cout << "Target: Default behavior\n";
    }
    virtual ~Target() = default;
};

// Adaptee (Incompatible Interface)
class Adaptee {
public:
    void specificRequest() const {
        std::cout << "Adaptee: Specific behavior\n";
    }
};

// Adapter using Multiple Inheritance
class Adapter : public Target, private Adaptee {
public:
    void request() const override {
        std::cout << "Adapter: Translating call...\n";
        this->specificRequest();
    }
};

// Client code
void clientCode(const Target& target) {
    target.request();
}

int main() {
    Target target;
    clientCode(target);  // Output: Target: Default behavior

    Adapter adapter;
    clientCode(adapter);  // Output: Adapter: Translating call... Adaptee: Specific behavior

    return 0;
}
```

#### Explanation:
- **Target Interface**: The `Target` class has a `request()` method, which is expected by the client.
- **Adaptee**: The `Adaptee` class has a different interface (`specificRequest()`).
- **Adapter**: The `Adapter` class inherits both the `Target` interface and `Adaptee` and adapts the `specificRequest()` method to the `request()` method expected by the client.

---

### Example 3: Adapting Legacy Code with Adapter Pattern

Sometimes, legacy code needs to be integrated into new systems, but the interfaces are incompatible. The Adapter pattern can help in these scenarios.

#### Code Example:
```cpp
#include <iostream>
#include <string>

// Target Interface
class ModernPayment {
public:
    virtual void pay(int amount) = 0;
    virtual ~ModernPayment() = default;
};

// Adaptee (Legacy code with a different interface)
class LegacyPayment {
public:
    void processPayment(float dollars) {
        std::cout << "Processing payment of $" << dollars << " through legacy system\n";
    }
};

// Adapter
class PaymentAdapter : public ModernPayment {
private:
    LegacyPayment* legacyPayment;

public:
    PaymentAdapter(LegacyPayment* legacy) : legacyPayment(legacy) {}

    void pay(int amount) override {
        // Convert the modern interface call to the legacy interface
        float amountInDollars = static_cast<float>(amount);
        legacyPayment->processPayment(amountInDollars);
    }
};

// Client code
int main() {
    LegacyPayment legacyPayment;
    PaymentAdapter adapter(&legacyPayment);

    // Client calls the ModernPayment interface, but it is adapted to the legacy system
    adapter.pay(100);

    return 0;
}
```

#### Explanation:
- **Target Interface**: The `ModernPayment` interface defines a `pay(int)` method.
- **Adaptee**: The `LegacyPayment` class has a `processPayment(float)` method, which is incompatible with the client interface.
- **Adapter**: `PaymentAdapter` adapts the `LegacyPayment` system to be compatible with the `ModernPayment` interface by implementing `pay()` and internally calling `processPayment()`.

---

### Key Points:
- **Adapter Pattern** is used to bridge the gap between incompatible interfaces, making two classes work together.
- It can be implemented using **composition** (where the Adapter contains an instance of the Adaptee) or **inheritance** (where the Adapter inherits from both the Target and Adaptee).
- The **Adapter** translates the client’s calls into calls the Adaptee understands.
- This pattern is particularly useful when integrating legacy code or external libraries with new systems.
