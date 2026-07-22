# SOLID Principles in C++ (Interview Notes)

---

# What is SOLID?

**SOLID** is a set of five Object-Oriented Design (OOD) principles that help write:

- Maintainable code
- Scalable code
- Reusable code
- Testable code
- Loosely coupled code

It stands for:

| Letter | Principle |
|---------|-----------|
| **S** | Single Responsibility Principle |
| **O** | Open/Closed Principle |
| **L** | Liskov Substitution Principle |
| **I** | Interface Segregation Principle |
| **D** | Dependency Inversion Principle |

---

# Cohesion

## Definition

Cohesion refers to **how focused a class or module is on doing one job.**

It measures the relationship between the responsibilities inside a class.

---

## Low Cohesion

A class performs many unrelated tasks.

Example:

```text
User class
├── Login
├── Register
├── Send Email
├── Generate Report
├── Save Database
├── Print PDF
```

Problems:

- Hard to understand
- Hard to maintain
- Hard to test
- Difficult to reuse

---

## High Cohesion

A class performs only one related task.

Example:

```text
UserService
    ├── Login
    └── Register

EmailService
    └── Send Email

ReportService
    └── Generate Report
```

Advantages:

- Easy maintenance
- Easy testing
- Better readability
- Better reuse

---

# Coupling

## Definition

Coupling measures **how dependent one class is on another.**

---

## High Coupling

Changing one class forces changes in another.

```text
A ---> B ---> C ---> D
```

If B changes,

A also changes.

Problems:

- Difficult maintenance
- Difficult testing
- Difficult extension

---

## Low Coupling

Classes communicate through interfaces instead of concrete implementations.

```text
A ---> Interface <--- B
```

Advantages:

- Easy replacement
- Better testing
- Flexible design
- Reusable code

---

# S - Single Responsibility Principle (SRP)

## Definition

> **A class should have only one reason to change.**

OR

> **One class should have one responsibility.**

This naturally leads to **High Cohesion**.

---

## Bad Example

One class downloads files, parses them, and stores them.

```cpp
class ProcessFile
{
public:
    void downloadFile(string location);
    void parseFile(File file);
    void persistData(Data data);
};
```

Responsibilities:

- Download
- Parse
- Save

Three different responsibilities.

This violates SRP.

---

## Better Design

```cpp
class FileDownloader
{
public:
    void downloadFile(string location);
};

class FileParser
{
public:
    Data parseFile(File file);
};

class DatabaseSaver
{
public:
    void persistData(Data data);
};
```

Now each class has only one responsibility.

---

## Real-world Example

Instead of

```text
UserManager
├── Login
├── Register
├── Send Email
├── Write Logs
```

Use

```text
AuthenticationService
EmailService
Logger
```

---

## Advantages

- High Cohesion
- Easy maintenance
- Easy testing
- Loose coupling
- Reusable classes

---

# O - Open/Closed Principle (OCP)

## Definition

> **Software entities should be open for extension but closed for modification.**

Meaning:

You should be able to add new behavior **without modifying existing code.**

Usually achieved using

- Inheritance
- Polymorphism
- Interfaces

---

## Problematic Code

```cpp
enum Vendor
{
    Dominos,
    Mozo
};

class Pizza
{
public:

    void getOrder(Vendor vendor)
    {
        switch(vendor)
        {
            case Dominos:
                prepareDominos();
                break;

            case Mozo:
                prepareMozo();
                break;
        }
    }
};
```

Problem:

Adding

```text
PizzaHut
```

requires modifying

```cpp
switch()
```

This violates OCP.

---

## Better Design

```cpp
class Pizza
{
public:
    virtual void preparePizza() = 0;

    virtual ~Pizza() = default;
};
```

---

### Dominos

```cpp
class Dominos : public Pizza
{
public:

    void preparePizza() override
    {
        cout << "Preparing Dominos Pizza";
    }
};
```

---

### Mozo

```cpp
class Mozo : public Pizza
{
public:

    void preparePizza() override
    {
        cout << "Preparing Mozo Pizza";
    }
};
```

---

### New Vendor

```cpp
class PizzaHut : public Pizza
{
public:

    void preparePizza() override
    {
        cout << "Preparing Pizza Hut";
    }
};
```

Notice:

No existing class was modified.

Only extended.

---

## Advantages

- Easy extension
- No risk of breaking old code
- Better maintainability
- Supports plugins

---

# L - Liskov Substitution Principle (LSP)

## Definition

> **Objects of derived classes should be replaceable with objects of the base class without changing program correctness.**

Simply,

Wherever a parent object is expected,

a child object should work correctly.

---

## Bad Design

```cpp
class Bird
{
public:

    virtual void fly() = 0;
};
```

---

### Crow

```cpp
class Crow : public Bird
{
public:

    void fly() override
    {
        cout << "Crow flying";
    }
};
```

---

### Ostrich

```cpp
class Ostrich : public Bird
{
public:

    void fly() override
    {
        throw runtime_error("Ostrich can't fly");
    }
};
```

---

### Function

```cpp
void makeBirdFly(Bird& bird)
{
    bird.fly();
}
```

Works for

```cpp
Crow crow;

makeBirdFly(crow);
```

Fails for

```cpp
Ostrich ostrich;

makeBirdFly(ostrich);
```

Output

```text
Runtime Exception
```

This violates LSP because an Ostrich cannot behave like every Bird in this hierarchy.

---

## Better Design

Separate flying behavior.

```text
Bird

FlyingBird

Crow
Eagle

NonFlyingBird

Ostrich
Penguin
```

Now

```cpp
makeBirdFly(FlyingBird&);
```

Only flying birds are accepted.

LSP is preserved.

---

## Advantages

- Reliable polymorphism
- Safe inheritance
- Better maintainability
- Avoids runtime surprises

---

# I - Interface Segregation Principle (ISP)

## Definition

> **Clients should not be forced to depend on methods they do not use.**

Instead of one huge interface,

create multiple small interfaces.

---

## Bad Design

```cpp
class Printer
{
public:

    virtual void print() = 0;

    virtual void scan() = 0;

    virtual void fax() = 0;
};
```

Suppose

```text
Home Printer
```

supports only printing.

Still,

it must implement

```cpp
scan()

fax()
```

even though they are unused.

Violation of ISP.

---

## Better Design

### Printer

```cpp
class Printer
{
public:

    virtual void print() = 0;
};
```

---

### Scanner

```cpp
class Scanner
{
public:

    virtual void scan() = 0;
};
```

---

### Fax

```cpp
class Fax
{
public:

    virtual void fax() = 0;
};
```

Now,

A home printer implements only

```cpp
Printer
```

A multifunction printer can implement

```cpp
Printer
Scanner
Fax
```

Each client depends only on what it needs.

---

## Advantages

- Small interfaces
- Cleaner code
- Easier implementation
- Better maintainability

---

# D - Dependency Inversion Principle (DIP)

## Definition

> **High-level modules should not depend on low-level modules.**

Both should depend on **abstractions (interfaces).**

---

## Bad Design

```cpp
class MyCloud
{
public:

    void upload(string filepath);
};
```

```cpp
class FileUploader
{
public:

    FileUploader(MyCloud& cloud)
    {
    }
};
```

Problem:

```
FileUploader

depends directly on

MyCloud
```

If cloud provider changes,

FileUploader also changes.

High coupling.

---

## Better Design

### Abstract Interface

```cpp
class Cloud
{
public:

    virtual void upload(string filepath) = 0;

    virtual ~Cloud() = default;
};
```

---

### Azure

```cpp
class AzureCloud : public Cloud
{
public:

    void upload(string filepath) override
    {
        cout << "Uploading to Azure";
    }
};
```

---

### AWS

```cpp
class AWSCloud : public Cloud
{
public:

    void upload(string filepath) override
    {
        cout << "Uploading to AWS";
    }
};
```

---

### FileUploader

```cpp
class FileUploader
{
private:

    Cloud& cloud;

public:

    FileUploader(Cloud& c)
        : cloud(c)
    {
    }

    void uploadFile(string path)
    {
        cloud.upload(path);
    }
};
```

Now

```cpp
AzureCloud azure;

FileUploader uploader(azure);
```

or

```cpp
AWSCloud aws;

FileUploader uploader(aws);
```

No code changes are needed in `FileUploader`.

---

## Advantages

- Low Coupling
- Easy testing (Mock objects)
- Replace implementations easily
- Better maintainability
- Better scalability

---

# SOLID Summary

| Principle | One-Line Definition | Goal |
|------------|---------------------|------|
| **SRP** | One class should have one responsibility. | High Cohesion |
| **OCP** | Open for extension, closed for modification. | Easy Extension |
| **LSP** | Child classes should replace parent classes safely. | Correct Inheritance |
| **ISP** | Don't force clients to implement unused methods. | Small Interfaces |
| **DIP** | Depend on abstractions, not implementations. | Low Coupling |

---

# Easy Interview Memory Trick

```text
S → Single Job

O → Extend, Don't Modify

L → Child behaves like Parent

I → Small Interfaces

D → Depend on Interface
```

---

# Cohesion vs Coupling

| Cohesion | Coupling |
|----------|----------|
| Inside one class | Between multiple classes |
| Measures responsibilities | Measures dependency |
| High is good | Low is good |
| Related methods together | Classes independent |
| Improves readability | Improves maintainability |

### Ideal Design

```text
High Cohesion
        +
Low Coupling
        =
Good Software Design
```

---

# Interview Tips

- **SRP:** One class → One responsibility.
- **OCP:** Add new features using inheritance/interfaces, not by modifying existing code.
- **LSP:** A child class must be usable wherever its parent is expected.
- **ISP:** Split large interfaces into smaller, focused ones.
- **DIP:** High-level modules depend on abstractions, not concrete implementations.
