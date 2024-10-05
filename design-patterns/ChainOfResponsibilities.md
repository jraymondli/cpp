The **Chain of Responsibility Pattern** is a behavioral design pattern used to avoid coupling the sender of a request to its receiver. Instead of the sender explicitly specifying which object should handle the request, multiple objects are given the opportunity to handle it. These objects are linked in a chain, and the request is passed along the chain until one of the objects handles it.

### Key Components:
1. **Handler**: Defines an interface for handling requests. It also defines the link to the next handler in the chain.
2. **Concrete Handler**: Implements the handler interface and handles requests it is responsible for. If it can't handle the request, it passes it to the next handler in the chain.
3. **Client**: Sends the request to the chain of handlers.

### Example: Request Approval System

Let's consider an example where different levels of managers (Team Lead, Project Manager, and Director) can approve budget requests. Each manager has a certain threshold, and if they can't approve a request, they pass it to the next level.

#### Code Example

```cpp
#include <iostream>
#include <string>

// Handler Interface
class Approver {
protected:
    Approver* nextApprover;

public:
    Approver() : nextApprover(nullptr) {}

    void setNext(Approver* next) {
        nextApprover = next;
    }

    virtual void approveRequest(double amount) = 0;
};

// Concrete Handler 1: Team Lead
class TeamLead : public Approver {
public:
    void approveRequest(double amount) override {
        if (amount < 1000) {
            std::cout << "Team Lead approved the request of $" << amount << std::endl;
        } else if (nextApprover) {
            nextApprover->approveRequest(amount);
        }
    }
};

// Concrete Handler 2: Project Manager
class ProjectManager : public Approver {
public:
    void approveRequest(double amount) override {
        if (amount < 5000) {
            std::cout << "Project Manager approved the request of $" << amount << std::endl;
        } else if (nextApprover) {
            nextApprover->approveRequest(amount);
        }
    }
};

// Concrete Handler 3: Director
class Director : public Approver {
public:
    void approveRequest(double amount) override {
        if (amount < 20000) {
            std::cout << "Director approved the request of $" << amount << std::endl;
        } else {
            std::cout << "Request of $" << amount << " requires a board meeting!" << std::endl;
        }
    }
};

// Client code
int main() {
    // Create handlers
    Approver* teamLead = new TeamLead();
    Approver* projectManager = new ProjectManager();
    Approver* director = new Director();

    // Set up the chain of responsibility
    teamLead->setNext(projectManager);
    projectManager->setNext(director);

    // Test the chain with different amounts
    teamLead->approveRequest(500);   // Approved by Team Lead
    teamLead->approveRequest(3000);  // Approved by Project Manager
    teamLead->approveRequest(15000); // Approved by Director
    teamLead->approveRequest(25000); // Requires board meeting

    // Clean up
    delete teamLead;
    delete projectManager;
    delete director;

    return 0;
}
```

### Explanation:
1. **Handler (`Approver`)**: The `Approver` class defines the `approveRequest` method for handling requests. It also holds a reference to the next approver in the chain (`nextApprover`).
2. **Concrete Handlers (`TeamLead`, `ProjectManager`, `Director`)**: These classes handle requests within their limit. If they can't handle the request, they pass it to the next handler in the chain.
3. **Client**: The client code creates the handlers, links them in a chain, and then sends requests for approval.

### Output:
```
Team Lead approved the request of $500
Project Manager approved the request of $3000
Director approved the request of $15000
Request of $25000 requires a board meeting!
```

### Example 2: Customer Support System

In this example, we’ll create a customer support system where support requests are passed along a chain of support agents (Level 1, Level 2, and Level 3) until one of them resolves the issue.

#### Code Example

```cpp
#include <iostream>
#include <string>

// Handler Interface
class SupportAgent {
protected:
    SupportAgent* nextAgent;

public:
    SupportAgent() : nextAgent(nullptr) {}

    void setNext(SupportAgent* next) {
        nextAgent = next;
    }

    virtual void handleRequest(const std::string& issue) = 0;
};

// Concrete Handler 1: Level 1 Support
class Level1Support : public SupportAgent {
public:
    void handleRequest(const std::string& issue) override {
        if (issue == "password reset") {
            std::cout << "Level 1 Support resolved the issue: " << issue << std::endl;
        } else if (nextAgent) {
            nextAgent->handleRequest(issue);
        }
    }
};

// Concrete Handler 2: Level 2 Support
class Level2Support : public SupportAgent {
public:
    void handleRequest(const std::string& issue) override {
        if (issue == "software installation") {
            std::cout << "Level 2 Support resolved the issue: " << issue << std::endl;
        } else if (nextAgent) {
            nextAgent->handleRequest(issue);
        }
    }
};

// Concrete Handler 3: Level 3 Support
class Level3Support : public SupportAgent {
public:
    void handleRequest(const std::string& issue) override {
        std::cout << "Level 3 Support resolved the issue: " << issue << std::endl;
    }
};

// Client code
int main() {
    // Create support agents
    SupportAgent* level1 = new Level1Support();
    SupportAgent* level2 = new Level2Support();
    SupportAgent* level3 = new Level3Support();

    // Set up the chain of responsibility
    level1->setNext(level2);
    level2->setNext(level3);

    // Test the chain with different support issues
    level1->handleRequest("password reset");        // Resolved by Level 1 Support
    level1->handleRequest("software installation"); // Resolved by Level 2 Support
    level1->handleRequest("hardware failure");      // Resolved by Level 3 Support

    // Clean up
    delete level1;
    delete level2;
    delete level3;

    return 0;
}
```

### Explanation:
1. **Handler (`SupportAgent`)**: Defines the `handleRequest` method for handling support requests. It can pass unhandled requests to the next agent in the chain.
2. **Concrete Handlers (`Level1Support`, `Level2Support`, `Level3Support`)**: Each support level is responsible for resolving certain types of issues. If an issue is beyond the current level's capability, it passes it to the next level in the chain.
3. **Client**: The client code sets up the chain of support agents and sends different issues to be resolved by the appropriate level.

### Output:
```
Level 1 Support resolved the issue: password reset
Level 2 Support resolved the issue: software installation
Level 3 Support resolved the issue: hardware failure
```

### Benefits of Chain of Responsibility Pattern:
- **Decouples Senders and Receivers**: The sender of the request doesn't need to know which object in the chain will handle it.
- **Simplifies Object Responsibilities**: Objects in the chain handle only what they are responsible for and pass along requests they can't handle.
- **Dynamic Behavior**: The chain can be modified at runtime by changing the links between handlers, making it flexible.

### Use Cases:
- **Logging Systems**: Different log levels (info, warning, error) can be handled by different handlers.
- **Request Handling**: Approving requests based on different authority levels.
- **Event Handling**: UI components that pass events along a chain until one component handles it.

In summary, the **Chain of Responsibility Pattern** helps create a chain of objects that can process a request, ensuring that no object is overburdened with handling every type of request, and allowing for flexibility in how requests are passed and handled.
