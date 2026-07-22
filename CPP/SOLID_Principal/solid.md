# SOLID Principles

SOLID is a set of five Object-Oriented Design (OOD) principles that help developers write software that is:

- Easy to maintain
- Easy to extend
- Easy to test
- Loosely coupled
- Highly cohesive

---

# SOLID Overview

| Principle | Meaning |
|-----------|---------|
| **S** | Single Responsibility Principle |
| **O** | Open Closed Principle |
| **L** | Liskov Substitution Principle |
| **I** | Interface Segregation Principle |
| **D** | Dependency Inversion Principle |

---

# Cohesion

Cohesion refers to **what a class (or module) is responsible for**.

- **Low Cohesion**
  - Class performs many unrelated tasks.
  - Broad and unfocused.
  - Difficult to maintain.

- **High Cohesion**
  - Class has a single well-defined responsibility.
  - Easy to understand.
  - Easy to modify.

Example

```text
High Cohesion

FileParser
    ↓
Only parses files

----------------------------

Low Cohesion

FileParser
    ↓
Download File
Parse File
Send Email
Log Errors
Upload Cloud
```

---

# Coupling

Coupling refers to **how dependent one class/module is on another**.

- **Low Coupling**
  - Classes are independent.
  - Changes in one class have minimal impact on others.
  - Easier maintenance.

- **High Coupling**
  - Classes depend heavily on each other.
  - Small changes may affect multiple classes.
  - Difficult to maintain.

---

# S - Single Responsibility Principle (SRP)

## Definition

A class should have **only one responsibility** (one reason to change).

High Cohesion:

```text
One Class

↓

One Responsibility
```

---

## Advantages

- Maintainability
- Testability
- Loose Coupling
- Easy to Extend
- Easy to Debug

---

## Example

Suppose a class performs:

- User Login
- User Registration
- Logging Errors
- Sending Email

This violates SRP because one class has multiple responsibilities.

### Example

```cpp
class processFile
{
public:

    void downloadFile(string location);

    void parseFile(File file);

    void persistData(Data data);
};
```

Better approach:

```text
FileDownloader

↓

FileParser

↓

DataPersistence
```

Each class performs only one task.

---

# O - Open Closed Principle (OCP)

## Definition

Software entities should be:

- **Open for Extension**
- **Closed for Modification**

Instead of modifying existing code, extend it using inheritance or abstraction.

---

## Problematic Code

```cpp
enum pizza
{
    Dominos,
    Mozo
};

class Pizza
{
public:

    void getOrder(string pizza_type)
    {
        switch(pizza_type)
        {
            case Dominos:
                preparePizza();
                break;

            case Mozo:
                preparePizza();
                break;
        }
    }
};
```

### Problem

Whenever a new vendor is added:

```text
Pizza Hut

Papa Johns

etc.
```

The `switch` statement must be modified.

This violates the Open Closed Principle.

---

## Solution

Create an abstract interface.

```cpp
class Pizza
{
public:

    virtual void preparePizza() = 0;
};
```

Dominos

```cpp
class Dominos : public Pizza
{
public:

    void preparePizza() override
    {

    }
};
```

Mozo

```cpp
class Mozo : public Pizza
{
public:

    void preparePizza() override
    {

    }
};
```

Now adding a new vendor only requires creating another derived class.

Existing code remains unchanged.

---

# L - Liskov Substitution Principle (LSP)

## Definition

Objects of a derived class should be replaceable with objects of the base class **without changing the correctness of the program**.

A subclass should honor the behavior expected from its parent.

---

## Example

```cpp
class Bird
{
public:

    virtual void fly() = 0;
};
```

Crow

```cpp
class Crow : public Bird
{
public:

    void fly() override
    {
        cout << "Crow is flying" << endl;
    }
};
```

Ostrich

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

Suppose we have

```cpp
void makeBirdFly(Bird& bird)
{
    bird.fly();
}
```

Usage

```cpp
Crow crow;
Ostrich ostrich;

makeBirdFly(crow);      // Works

makeBirdFly(ostrich);   // Throws exception
```

### Problem

The function expects **every Bird to fly**.

But Ostrich cannot fly.

Therefore

```text
Ostrich

↓

Cannot substitute Bird

↓

LSP Violated
```

---

# I - Interface Segregation Principle (ISP)

## Definition

Clients should **not be forced to depend on methods they do not use**.

Instead of one large interface, create multiple smaller interfaces.

---

## Problem

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

```cpp
class MyPrinter : public Printer
{

};
```

If `MyPrinter` only supports

```text
Print

Scan
```

it is still forced to implement

```text
Fax
```

which it does not need.

This violates ISP.

---

## Solution

Split the interface.

Printer Interface

```cpp
class Printer
{
public:

    virtual void print() = 0;

    virtual void scan() = 0;
};
```

Fax Interface

```cpp
class Fax
{
public:

    virtual void fax() = 0;
};
```

Now clients implement only the interfaces they require.

---

# D - Dependency Inversion Principle (DIP)

## Definition

High-level modules should **not depend on low-level modules**.

Both should depend on **abstractions** (interfaces).

This reduces coupling.

---

## Problematic Code

```cpp
class mycloud
{
public:

    void upload(string filepath);
};
```

```cpp
class fileUploader
{
public:

    fileUploader(mycloud& mcl);
};
```

### Problem

`fileUploader` depends directly on

```text
mycloud
```

If cloud provider changes,

the uploader must also change.

This creates tight coupling.

---

## Solution

Create an abstract interface.

```cpp
class cloud
{
public:

    virtual void upload(string filepath) = 0;
};
```

Cloud Implementation

```cpp
class mycloud : public cloud
{
public:

    void upload(string filepath) override
    {
        cout << "" << endl;
    }
};
```

Uploader

```cpp
class fileUploader
{
public:

    fileUploader(cloud& cl);
};
```

Now `fileUploader` depends only on the abstraction.

It can work with

- Azure
- AWS
- Google Cloud
- Dropbox

without any modification.

---

# SOLID Summary

| Principle | Description |
|-----------|-------------|
| **SRP** | One class should have one responsibility. |
| **OCP** | Open for extension, closed for modification. |
| **LSP** | Derived classes should replace base classes without breaking functionality. |
| **ISP** | Don't force clients to implement unnecessary methods. |
| **DIP** | Depend on abstractions, not concrete implementations. |

---

# Memory Trick

```text
S

Single Responsibility

↓

One Job

--------------------

O

Open Closed

↓

Extend

Don't Modify

--------------------

L

Liskov

↓

Derived Class

Should Behave Like

Base Class

--------------------

I

Interface Segregation

↓

Small Interfaces

--------------------

D

Dependency Inversion

↓

Depend on Interfaces

Not Implementations
```
