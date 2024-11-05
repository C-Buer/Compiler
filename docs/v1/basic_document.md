# C Buer Programming Language - Basic Documentation

## Introduction

C Buer is a compiled programming language that combines features from **C++**, **C#**, and **Rust**. It is designed for high performance while incorporating modern programming paradigms. The language emphasizes a clear separation of data and methods. Key features include:

- **Structs**: For public data grouping.
- **Classes**: Structs with private members, but **do not support inheritance**.
- **Interfaces**: Define contracts for methods, separate from data.
- **Enums with Pattern Matching**: Similar to Rust, with clear syntax for variant definitions and usage.
- **Composite Types**: Use `{}` for initialization on the right-hand side and `[]` for type declarations on the left-hand side.
- **For Loops**: Utilize C++-style range-based loops.

In C Buer, you can declare a type to use an interface, and another type can contain the first type. The containing type can implement the same interface by directly utilizing the interface of the contained type, promoting composition over inheritance.

Function and variable syntax is modeled after C++, providing familiarity for developers experienced with C-style languages.

---

## Language Features

### Variables and Data Types

C Buer supports a variety of data types:

- **Primitive Types**: `int`, `float`, `double`, `char`, `bool`
- **Composite Types**: Denoted by `[]` on the left-hand side and `{}` on the right-hand side.
- **Compound Types**: `struct`, `class`
- **Special Types**: `string`, `array`, `enum`

Variables are declared similarly to C++:

```c++
int count = 10;
float pi = 3.14;
bool isActive = true;
char letter = 'A';
```

#### Composite Types (`[]` and `{}`)

- **Left-Hand Side (Declaration)**: Use `[]` to declare composite types.
- **Right-Hand Side (Initialization)**: Use `{}` to initialize composite types.

**Example:**

```c++
[int, float] coordinates;
coordinates = {10, 20.5};
```

Assigning composite types to structs:

```c++
struct Point {
    int x;
    float y;
};

Point p = {10, 20.5};
```

**Composite Types in Function Returns:**

- Using `auto` return type:

  ```c++
  auto getCoordinates() {
      return {10, 20.5};
  }
  ```

- Specifying the return type with composite types:

  ```c++
  [int, float] getCoordinates() {
      return {10, 20.5};
  }
  ```

**Note:** If `{}` contains a `;`, it is interpreted as a code block. Otherwise, `{}` represents a composite value.

### Functions

Functions are defined using a syntax similar to C++ and are separate from data structures:

```c++
return_type function_name(parameter_list) {
    // Function body
}
```

**Example:**

```c++
int add(int a, int b) {
    return a + b;
}
```

### Structs

Structs are used for grouping public data without methods:

```c++
struct Point {
    int x;
    float y;
};
```

Structs can be initialized using composite types:

```c++
Point p = {10, 20.5};
```

### Classes

Classes are similar to structs but have private members by default. They are used for encapsulating data with controlled access but **do not support inheritance**.

```c++
class Person {
private:
    string name;
    int age;

public:
    string getName() {
        return name;
    }

    void setName(string newName) {
        name = newName;
    }

    int getAge() {
        return age;
    }

    void setAge(int newAge) {
        age = newAge;
    }
};
```

Usage:

```c++
Person person = {"Alice", 30};
string name = person.getName();
int age = person.getAge();
```

### Interfaces and Composition

Interfaces define contracts for methods without implementation. They specify what methods should be available but are not tied to any data structure.

```c++
interface ILogger {
    void log(string message);
}
```

Implementing an interface involves defining functions that match the interface's method signatures.

**Example Implementation:**

```c++
class ConsoleLogger : ILogger {
public:
    void log(string message) {
        // Implementation code
        print("Log: " + message);
    }
};
```

#### Composition with Interfaces

Although types do not support inheritance, you can compose types by containing instances of other types.

**Example:**

```c++
class FileLogger : ILogger {
private:
    ConsoleLogger logger;

public:
    void log(string message) {
        logger.log(message); // Delegating to the contained type
        // Additional file logging logic
    }
};
```

In this example, `FileLogger` contains a `ConsoleLogger` and implements the `ILogger` interface by utilizing the methods of the contained `ConsoleLogger` instance.

### Enums and Pattern Matching

#### Enums

C Buer supports enums similar to Rust, allowing enums to hold associated data. Enums are defined using the following syntax, with variants separated by semicolons `;`:

```c++
enum Result {
    Success: {
        int value;
    };
    Error: {
        string message;
    };
}
```

Each variant of the enum can have associated data defined inside `{}`.

**Usage:**

```c++
Result res = Result::Success {42};
```

Or:

```c++
res = Result::Error {"An error occurred"};
```

#### Pattern Matching

Pattern matching allows you to deconstruct enums and perform actions based on the matched variant. The syntax does not use the `=>` symbol, and the code block is directly enclosed within `{}`.

**Syntax:**

```c++
match (expression) {
    Variant1: {
        // Code block
    }
    Variant2: {
        // Code block
    }
}
```

**Example with Enums:**

```c++
Result process() {
    // Some processing logic
    return Result::Success {100};
}

Result res = process();

match (res) {
    Result::Success: {
        int value = res.value;
        print("Success with value: " + value);
    }
    Result::Error: {
        string message = res.message;
        print("Error occurred: " + message);
    }
}
```

**Note:** In pattern matching, we match on the enum variant using `VariantName:`, and directly write the code to be executed within the `{}`.

### For Loops

C Buer uses C++-style range-based loops for iterating over collections.

**Syntax:**

```c++
for (Type item : collection) {
    // Code using item
}
```

**Example with Arrays:**

```c++
int[] numbers = {1, 2, 3, 4, 5};

for (int num : numbers) {
    print("Number: " + num);
}
```

### Data and Method Separation

In C Buer, data structures (`struct` and `class`) do not contain method implementations. Methods (functions) operate on data structures but are defined separately.

**Example:**

```c++
struct Rectangle {
    float width;
    float height;
};

float calculateArea(Rectangle rect) {
    return rect.width * rect.height;
}

Rectangle rect = {5.0, 10.0};
float area = calculateArea(rect);
```

### Access Modifiers in Classes

Classes allow you to control access to their members using access modifiers:

- `public`: Accessible from outside the class.
- `private`: Accessible only within the class.

**Example:**

```c++
class BankAccount {
private:
    float balance;

public:
    void deposit(float amount) {
        balance += amount;
    }

    float getBalance() {
        return balance;
    }
};

BankAccount account = {0.0};
account.deposit(100.0);
float currentBalance = account.getBalance();
```

---

## Syntax Overview

### Comments

- Single-line comments: `// This is a comment`
- Multi-line comments: `/* This is a multi-line comment */`

### Control Structures

- **Conditional Statements:**

  ```c++
  if (condition) {
      // Code
  } else if (condition) {
      // Code
  } else {
      // Code
  }
  ```

- **Loops:**

  - **For Loop (C-Style):**

    ```c++
    for (int i = 0; i < 10; i++) {
        // Code
    }
    ```

  - **While Loop:**

    ```c++
    while (condition) {
        // Code
    }
    ```

  - **Do-While Loop:**

    ```c++
    do {
        // Code
    } while (condition);
    ```

  - **Range-Based For Loop:**

    ```c++
    for (Type item : collection) {
        // Code using item
    }
    ```

- **Switch Statement:**

  ```c++
  switch (variable) {
      case value1:
          // Code
          break;
      case value2:
          // Code
          break;
      default:
          // Code
  }
  ```

- **Pattern Matching:**

  ```c++
  match (expression) {
      Variant1: {
          // Code
      }
      Variant2: {
          // Code
      }
  }
  ```

### Operators

- Arithmetic: `+`, `-`, `*`, `/`, `%`
- Comparison: `==`, `!=`, `<`, `>`, `<=`, `>=`
- Logical: `&&`, `||`, `!`
- Assignment: `=`, `+=`, `-=`, `*=`, `/=`

---

## Examples

### Composite Types in Function Returns

**Using `auto` Return Type:**

```c++
auto getPoint() {
    return {10, 20.5};
}

Point p = getPoint();
```

**Specifying Return Type:**

```c++
[int, float] getPoint() {
    return {10, 20.5};
}
```

Where `Point` is a struct:

```c++
struct Point {
    int x;
    float y;
};
```

### Defining and Using a Struct with Composite Types

```c++
struct Point {
    int x;
    float y;
};

Point p = {10, 20.5};
print("Point coordinates: (" + p.x + ", " + p.y + ")");
```

### Array Declarations and Usage

**Fixed-Size Array:**

```c++
int[5] fixedArray; // Declaration with size 5
fixedArray = {10, 20, 30, 40, 50};

for (int i = 0; i < 5; i++) {
    print("fixedArray[" + i + "] = " + fixedArray[i]);
}
```

**Variable-Size Array (Size Determined by Initialization):**

```c++
int[] dynamicArray = {5, 10, 15, 20};

for (int num : dynamicArray) {
    print("Number: " + num);
}
```

### Using a Class with Access Control and Composite Assignment

```c++
class Counter {
private:
    int count;

public:
    void increment() {
        count += 1;
    }

    int getCount() {
        return count;
    }
};

Counter counter = {0};
counter.increment();
int currentCount = counter.getCount();
print("Count: " + currentCount);
```

### Implementing an Interface and Composition

Define the interface:

```c++
interface ILogger {
    void log(string message);
}
```

Implement the interface:

```c++
class ConsoleLogger : ILogger {
public:
    void log(string message) {
        print("Console Log: " + message);
    }
};
```

Using composition to implement an interface:

```c++
class FileLogger : ILogger {
private:
    ConsoleLogger consoleLogger;

public:
    void log(string message) {
        consoleLogger.log(message); // Delegating to ConsoleLogger
        // Additional file logging logic
    }
};
```

### Enums and Pattern Matching Example

Define the enum:

```c++
enum Option {
    Some: {
        int value;
    };
    None: {};
}
```

Function that returns an `Option`:

```c++
Option find(int[] array, int target) {
    for (int index = 0; index < array.length; index++) {
        if (array[index] == target) {
            return Option::Some {index};
        }
    }
    return Option::None {};
}
```

Usage with pattern matching:

```c++
int[] numbers = {10, 20, 30, 40};
Option result = find(numbers, 30);

match (result) {
    Option::Some: {
        int index = result.value;
        print("Found at index: " + index);
    }
    Option::None: {
        print("Not found");
    }
}
```

### For Loop Example

Iterating over an array:

```c++
string[] fruits = {"Apple", "Banana", "Cherry"};

for (string fruit : fruits) {
    print("Fruit: " + fruit);
}
```

### Assigning Composite Types to Structs

```c++
struct Employee {
    int id;
    string name;
    string[] skills;
};

Employee emp = {123, "John Doe", {"C++", "C#", "Rust"}};

print("Employee ID: " + emp.id);
print("Name: " + emp.name);
print("Skills:");

for (string skill : emp.skills) {
    print("- " + skill);
}
```

---

## Compilation

Assuming you have the C Buer compiler installed, you can compile your code using:

```bash
cbuerc MyProgram.cbuer -o MyProgram
```

Run the compiled program:

```bash
./MyProgram
```

---

## Conclusion

C Buer blends the efficiency of C++, the modern features of C#, and the safety mechanisms of Rust to create a versatile programming language. By strictly separating data (`struct`, `class`) and methods (functions), it encourages clean code architecture and clarity in program design.

The use of `[]` and `{}` for composite types allows for clear and concise declarations and initializations. The adjustments in syntax for function returns and pattern matching enhance the language's expressiveness and consistency. **Rust-like enums** and **pattern matching** bring powerful abstraction capabilities, allowing developers to write more expressive and safer code. **C++-style range-based for loops** simplify the process of traversing collections, making code more readable and concise.

By not supporting inheritance but allowing types to implement interfaces and utilize composition, C Buer promotes a design that favors composition over inheritance, leading to more maintainable and flexible code.

The familiar C++-like syntax for functions and variables makes it accessible for developers, while the modern features promote better code maintainability and readability.

---

## Further Resources

As you continue exploring C Buer, consider experimenting with the language's features and contributing to its development. Since the language is still in progress, your feedback and contributions can help shape its future.

If you have any questions or need more detailed guidance on specific features, feel free to reach out or consult the language's official documentation (once available).

---

## Appendix

### Composite Types and Struct Assignment

The use of `[]` and `{}` for composite types allows for succinct and clear initialization of structs and other data structures.

**Example:**

```c++
struct Config {
    string host;
    int port;
    bool useSSL;
};

Config config = {"localhost", 8080, true};

print("Connecting to " + config.host + ":" + config.port);
if (config.useSSL) {
    print("SSL is enabled.");
} else {
    print("SSL is disabled.");
}
```

### Advanced Pattern Matching with Enums

Pattern matching can be used with enums for deconstructing data structures.

**Example:**

```c++
enum Shape {
    Circle: {
        float radius;
    };
    Rectangle: {
        float width;
        float height;
    };
}

Shape shape = Shape::Circle {5.0};

match (shape) {
    Shape::Circle: {
        float radius = shape.radius;
        print("Circle with radius: " + radius);
    }
    Shape::Rectangle: {
        float width = shape.width;
        float height = shape.height;
        print("Rectangle with width: " + width + " and height: " + height);
    }
}
```

### Implementing Interfaces with Composition

By composing types that implement interfaces, you can build complex behaviors without inheritance.

**Example:**

```c++
interface IMovable {
    void move(int x, int y);
}

struct Position {
    int x;
    int y;
};

void move(Position* pos, int dx, int dy) {
    pos->x += dx;
    pos->y += dy;
}

class Player : IMovable {
private:
    Position position;

public:
    void move(int x, int y) {
        ::move(&position, x, y); // Using the global move function
    }

    Position getPosition() {
        return position;
    }
};
```

In this example, `Player` implements `IMovable` by containing a `Position` and using the global `move` function, demonstrating how composition and interfaces can be used together.
