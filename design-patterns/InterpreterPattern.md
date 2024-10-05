The **Interpreter Pattern** is a behavioral design pattern used to define a grammatical representation of a language and provide an interpreter to deal with this grammar. It is useful when you want to evaluate sentences or expressions in a language, making it easier to interpret and process complex language syntax.

### Key Concepts:
1. **Context**: Contains information that is global to the interpreter, which is used during the interpretation process.
2. **Abstract Expression**: Declares an interface for interpreting context.
3. **Terminal Expression**: Implements an interpretation operation for terminal symbols in the grammar.
4. **Non-terminal Expression**: Implements an interpretation operation for non-terminal symbols, usually combining or operating on other expressions.
5. **Client**: Builds the abstract syntax tree that represents a specific sentence in the language defined by the grammar.

### Example: Simple Mathematical Expression Interpreter

In this example, we will create an interpreter for simple mathematical expressions that involve addition and subtraction. The grammar can be defined as:

- **Expression** → **Number** | **Expression + Expression** | **Expression - Expression**
- **Number** → any valid integer

#### Code Example

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// Context class to hold variable values
class Context {
private:
    std::unordered_map<std::string, int> variables;

public:
    void setVariable(const std::string& name, int value) {
        variables[name] = value;
    }

    int getVariable(const std::string& name) const {
        return variables.at(name);
    }
};

// Abstract Expression class
class Expression {
public:
    virtual int interpret(const Context& context) const = 0;
    virtual ~Expression() = default;
};

// Terminal Expression: Number
class Number : public Expression {
private:
    int value;

public:
    explicit Number(int value) : value(value) {}

    int interpret(const Context& context) const override {
        return value;
    }
};

// Terminal Expression: Variable
class Variable : public Expression {
private:
    std::string name;

public:
    explicit Variable(const std::string& name) : name(name) {}

    int interpret(const Context& context) const override {
        return context.getVariable(name);
    }
};

// Non-terminal Expression: Addition
class Add : public Expression {
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    Add(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    int interpret(const Context& context) const override {
        return left->interpret(context) + right->interpret(context);
    }
};

// Non-terminal Expression: Subtraction
class Subtract : public Expression {
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:
    Subtract(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    int interpret(const Context& context) const override {
        return left->interpret(context) - right->interpret(context);
    }
};

// Client code
int main() {
    // Context to hold variable values
    Context context;
    context.setVariable("x", 5);
    context.setVariable("y", 10);

    // Build the expression "x + y - 3"
    std::unique_ptr<Expression> expression = std::make_unique<Subtract>(
        std::make_unique<Add>(
            std::make_unique<Variable>("x"),
            std::make_unique<Variable>("y")
        ),
        std::make_unique<Number>(3)
    );

    // Interpret the expression in the given context
    std::cout << "Result of expression (x + y - 3): " << expression->interpret(context) << std::endl;

    return 0;
}
```

### Explanation:
1. **Context**: Holds the variable values that can be referenced in the expressions. In this case, `x = 5` and `y = 10` are stored in the context.
2. **Abstract Expression (`Expression`)**: An abstract class defining the `interpret` method for expressions.
3. **Terminal Expressions (`Number`, `Variable`)**: Represent simple values or variables in the expression. `Number` returns a fixed value, and `Variable` retrieves its value from the `Context`.
4. **Non-terminal Expressions (`Add`, `Subtract`)**: Combine other expressions and perform operations on them.
5. **Client**: The client builds a syntax tree representing the expression `x + y - 3` and interprets it within the given context.

### Output:
```
Result of expression (x + y - 3): 12
```

### Example 2: Boolean Expression Interpreter

In this example, we create a simple boolean expression interpreter for evaluating logical statements.

#### Code Example

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// Context class
class Context {
private:
    std::unordered_map<std::string, bool> variables;

public:
    void setVariable(const std::string& name, bool value) {
        variables[name] = value;
    }

    bool getVariable(const std::string& name) const {
        return variables.at(name);
    }
};

// Abstract Expression
class BooleanExpression {
public:
    virtual bool interpret(const Context& context) const = 0;
    virtual ~BooleanExpression() = default;
};

// Terminal Expression: Variable
class Variable : public BooleanExpression {
private:
    std::string name;

public:
    explicit Variable(const std::string& name) : name(name) {}

    bool interpret(const Context& context) const override {
        return context.getVariable(name);
    }
};

// Non-terminal Expression: And
class AndExpression : public BooleanExpression {
private:
    std::unique_ptr<BooleanExpression> left;
    std::unique_ptr<BooleanExpression> right;

public:
    AndExpression(std::unique_ptr<BooleanExpression> left, std::unique_ptr<BooleanExpression> right)
        : left(std::move(left)), right(std::move(right)) {}

    bool interpret(const Context& context) const override {
        return left->interpret(context) && right->interpret(context);
    }
};

// Non-terminal Expression: Or
class OrExpression : public BooleanExpression {
private:
    std::unique_ptr<BooleanExpression> left;
    std::unique_ptr<BooleanExpression> right;

public:
    OrExpression(std::unique_ptr<BooleanExpression> left, std::unique_ptr<BooleanExpression> right)
        : left(std::move(left)), right(std::move(right)) {}

    bool interpret(const Context& context) const override {
        return left->interpret(context) || right->interpret(context);
    }
};

// Non-terminal Expression: Not
class NotExpression : public BooleanExpression {
private:
    std::unique_ptr<BooleanExpression> expression;

public:
    explicit NotExpression(std::unique_ptr<BooleanExpression> expression)
        : expression(std::move(expression)) {}

    bool interpret(const Context& context) const override {
        return !expression->interpret(context);
    }
};

// Client code
int main() {
    // Context to hold variable values
    Context context;
    context.setVariable("A", true);
    context.setVariable("B", false);

    // Build the expression (A AND (NOT B))
    std::unique_ptr<BooleanExpression> expression = std::make_unique<AndExpression>(
        std::make_unique<Variable>("A"),
        std::make_unique<NotExpression>(
            std::make_unique<Variable>("B")
        )
    );

    // Interpret the expression in the given context
    std::cout << "Result of expression (A AND (NOT B)): " << std::boolalpha << expression->interpret(context) << std::endl;

    return 0;
}
```

### Explanation:
1. **Context**: Stores boolean variables such as `A = true` and `B = false`.
2. **Abstract Expression (`BooleanExpression`)**: Defines the interface for boolean expressions.
3. **Terminal Expressions (`Variable`)**: Retrieves the value of a variable from the context.
4. **Non-terminal Expressions (`AndExpression`, `OrExpression`, `NotExpression`)**: Perform logical operations on other expressions.
5. **Client**: Constructs a boolean expression `(A AND (NOT B))` and evaluates it in the given context.

### Output:
```
Result of expression (A AND (NOT B)): true
```

### Benefits of the Interpreter Pattern:
- **Extensible Grammar**: Easy to extend the language grammar by adding new terminal and non-terminal expressions without modifying the existing code.
- **Readable and Maintainable**: The pattern makes it easier to define a clear and maintainable solution for parsing and interpreting expressions.

### Use Cases:
- **Compilers/Interpreters**: For interpreting languages or expressions in programming languages.
- **Mathematical Expressions**: For interpreting and evaluating mathematical expressions.
- **Boolean/Logical Expressions**: For evaluating logical statements.
- **Parsers**: For parsing and interpreting structured text like configuration files.

In summary, the **Interpreter Pattern** provides a clear and structured way to define and evaluate a language's grammar or expressions, making it particularly useful for scenarios where dynamic interpretation is needed.
