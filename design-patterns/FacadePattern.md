The **Facade Pattern** is a structural design pattern that provides a simplified interface to a complex system of classes, libraries, or frameworks. It acts as a high-level interface that shields the client from the complexities of the system and makes it easier to interact with.

The goal of the Facade pattern is to provide a simpler, unified interface that abstracts away the complexity of one or more subsystems. This is useful when a system has a large number of interdependent classes or interfaces, and you want to hide that complexity from the user.

---

### Key Concepts
- **Subsystems**: The set of classes or modules that form the complex system.
- **Facade**: The simplified interface that interacts with the subsystems on behalf of the client.
- **Client**: The user or object that interacts with the facade.

---

### Example 1: Home Theater System

In this example, we use the Facade pattern to simplify the process of turning on a home theater system, which involves several subsystems such as the projector, amplifier, and DVD player. Instead of having the client interact with each of these subsystems individually, the Facade pattern provides a simple interface.

#### Code Example:
```cpp
#include <iostream>

// Subsystem 1: Projector
class Projector {
public:
    void on() { std::cout << "Projector is now ON.\n"; }
    void off() { std::cout << "Projector is now OFF.\n"; }
};

// Subsystem 2: Amplifier
class Amplifier {
public:
    void on() { std::cout << "Amplifier is now ON.\n"; }
    void off() { std::cout << "Amplifier is now OFF.\n"; }
    void setVolume(int volume) { std::cout << "Amplifier volume set to " << volume << ".\n"; }
};

// Subsystem 3: DVD Player
class DVDPlayer {
public:
    void on() { std::cout << "DVD Player is now ON.\n"; }
    void off() { std::cout << "DVD Player is now OFF.\n"; }
    void play(const std::string& movie) { std::cout << "Playing movie: " << movie << ".\n"; }
};

// Facade: HomeTheaterFacade
class HomeTheaterFacade {
private:
    Projector* projector;
    Amplifier* amplifier;
    DVDPlayer* dvdPlayer;

public:
    HomeTheaterFacade(Projector* p, Amplifier* a, DVDPlayer* d) : projector(p), amplifier(a), dvdPlayer(d) {}

    void watchMovie(const std::string& movie) {
        std::cout << "Getting ready to watch a movie...\n";
        projector->on();
        amplifier->on();
        amplifier->setVolume(5);
        dvdPlayer->on();
        dvdPlayer->play(movie);
    }

    void endMovie() {
        std::cout << "Shutting down the home theater...\n";
        dvdPlayer->off();
        amplifier->off();
        projector->off();
    }
};

// Client code
int main() {
    Projector projector;
    Amplifier amplifier;
    DVDPlayer dvdPlayer;

    HomeTheaterFacade homeTheater(&projector, &amplifier, &dvdPlayer);

    // Simplified client interaction with the home theater system using the Facade
    homeTheater.watchMovie("Inception");
    std::cout << "\n--- After the movie ends ---\n";
    homeTheater.endMovie();

    return 0;
}
```

#### Explanation:
- **Subsystems**: The `Projector`, `Amplifier`, and `DVDPlayer` classes each have their own methods to turn on, turn off, and control the device.
- **Facade (HomeTheaterFacade)**: The `HomeTheaterFacade` class provides two methods, `watchMovie()` and `endMovie()`, which internally interact with the various subsystems to simplify the client’s task.
- **Client**: Instead of directly dealing with multiple subsystems, the client only calls the `watchMovie()` and `endMovie()` methods, thus interacting with a simplified interface.

---

### Example 2: Banking System

In this example, the banking system has multiple subsystems for checking accounts, credit systems, and loan approvals. Instead of exposing these complex interactions to the client, the Facade simplifies the process of requesting a loan.

#### Code Example:
```cpp
#include <iostream>
#include <string>

// Subsystem 1: Account
class Account {
public:
    bool hasSufficientBalance(int amount) {
        std::cout << "Checking if the account has sufficient balance...\n";
        return true;  // Assume the account has enough balance
    }
};

// Subsystem 2: Credit System
class CreditSystem {
public:
    bool hasGoodCredit(const std::string& customer) {
        std::cout << "Checking credit score for customer " << customer << "...\n";
        return true;  // Assume the credit score is good
    }
};

// Subsystem 3: Loan Approval
class LoanApproval {
public:
    bool approveLoan(const std::string& customer, int amount) {
        std::cout << "Approving loan for customer " << customer << " of amount $" << amount << "...\n";
        return true;
    }
};

// Facade: LoanFacade
class LoanFacade {
private:
    Account* account;
    CreditSystem* creditSystem;
    LoanApproval* loanApproval;

public:
    LoanFacade(Account* a, CreditSystem* c, LoanApproval* l) : account(a), creditSystem(c), loanApproval(l) {}

    bool requestLoan(const std::string& customer, int amount) {
        std::cout << "Processing loan request for " << customer << "...\n";

        if (account->hasSufficientBalance(amount) &&
            creditSystem->hasGoodCredit(customer) &&
            loanApproval->approveLoan(customer, amount)) {
            std::cout << "Loan approved for " << customer << ".\n";
            return true;
        } else {
            std::cout << "Loan request denied for " << customer << ".\n";
            return false;
        }
    }
};

// Client code
int main() {
    Account account;
    CreditSystem creditSystem;
    LoanApproval loanApproval;

    LoanFacade loanFacade(&account, &creditSystem, &loanApproval);

    // Client requests a loan without knowing the internal details
    loanFacade.requestLoan("John Doe", 50000);

    return 0;
}
```

#### Explanation:
- **Subsystems**: The `Account`, `CreditSystem`, and `LoanApproval` classes each handle a specific aspect of loan processing.
- **Facade (LoanFacade)**: The `LoanFacade` simplifies the loan request process by interacting with these subsystems internally and exposing only a single method `requestLoan()`.
- **Client**: The client interacts only with the `LoanFacade`, making the process of requesting a loan simpler and abstracted from the internal complexities of the banking system.

---

### Example 3: Computer Startup System

In this example, turning on a computer involves starting various subsystems such as the CPU, memory, and hard drive. The Facade pattern provides a unified interface to simplify the process of turning on the computer.

#### Code Example:
```cpp
#include <iostream>

// Subsystem 1: CPU
class CPU {
public:
    void freeze() {
        std::cout << "CPU freezing...\n";
    }
    void jump(long position) {
        std::cout << "CPU jumping to position " << position << ".\n";
    }
    void execute() {
        std::cout << "CPU executing...\n";
    }
};

// Subsystem 2: Memory
class Memory {
public:
    void load(long position, std::string data) {
        std::cout << "Memory loading data \"" << data << "\" at position " << position << ".\n";
    }
};

// Subsystem 3: HardDrive
class HardDrive {
public:
    std::string read(long lba, int size) {
        std::cout << "HardDrive reading " << size << " bytes from LBA " << lba << ".\n";
        return "BOOT_DATA";
    }
};

// Facade: Computer
class Computer {
private:
    CPU* cpu;
    Memory* memory;
    HardDrive* hardDrive;

public:
    Computer(CPU* c, Memory* m, HardDrive* h) : cpu(c), memory(m), hardDrive(h) {}

    void start() {
        std::cout << "Starting computer...\n";
        cpu->freeze();
        memory->load(0, hardDrive->read(0, 1024));
        cpu->jump(0);
        cpu->execute();
    }
};

// Client code
int main() {
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;

    Computer computer(&cpu, &memory, &hardDrive);
    computer.start();  // Simplified interaction to start the computer

    return 0;
}
```

#### Explanation:
- **Subsystems**: The `CPU`, `Memory`, and `HardDrive` classes handle specific aspects of the computer startup process.
- **Facade (Computer)**: The `Computer` class provides a simplified `start()` method that interacts with the CPU, Memory, and HardDrive to boot up the system.
- **Client**: Instead of dealing with each subsystem directly, the client simply calls `start()` on the `Computer` facade.

---

### Key Points:
- The **Facade Pattern** simplifies interactions with complex systems by providing a unified, high-level interface.
- It hides the complexity of subsystems from the client, making it easier to use the system without needing to understand or manage the details.
- The Facade doesn’t add functionality to the subsystems; it only simplifies access to them.
- **Benefits
