# Composition in C++ (Has-A Relationship)

## What is Composition?

Composition is an **Object-Oriented Programming (OOP)** concept where one class **contains another class as a member**.

It represents a **"Has-A"** relationship.

Example

```text
Car HAS-A Engine

House HAS-A Room

Computer HAS-A CPU

Human HAS-A Heart
```

Instead of inheriting from another class, a class **owns** another object.

---

# Why Composition?

Suppose we are designing a Car.

A car is **not** an engine.

A car **has** an engine.

Therefore,

```text
Car ----> Engine
```

This is Composition.

Inheritance would be incorrect.

```text
Car IS-A Engine ❌
```

---

# Basic Example

```cpp
#include <iostream>
using namespace std;

class Engine
{
public:

    void start()
    {
        cout << "Engine Started\n";
    }
};

class Car
{
private:

    Engine engine;      // Composition

public:

    void startCar()
    {
        cout << "Starting Car...\n";

        engine.start();
    }
};

int main()
{
    Car car;

    car.startCar();
}
```

Output

```text
Starting Car...
Engine Started
```

---

# Memory Layout

When Car object is created

```text
Stack

+-------------------------+
| Car                     |
|                         |
|  +------------------+   |
|  | Engine           |   |
|  +------------------+   |
+-------------------------+
```

The Engine object is created **inside** the Car object.

No separate allocation is required.

---

# Constructor Order

Example

```cpp
#include <iostream>
using namespace std;

class Engine
{
public:

    Engine()
    {
        cout << "Engine Constructor\n";
    }

    ~Engine()
    {
        cout << "Engine Destructor\n";
    }
};

class Car
{
private:

    Engine engine;

public:

    Car()
    {
        cout << "Car Constructor\n";
    }

    ~Car()
    {
        cout << "Car Destructor\n";
    }
};

int main()
{
    Car car;
}
```

Output

```text
Engine Constructor

Car Constructor

Car Destructor

Engine Destructor
```

---

# Why?

Construction order

```text
Member Objects

↓

Parent Class

↓

Current Class
```

Destruction happens in reverse order.

```text
Current Class

↓

Member Objects
```

---

# Composition with Parameterized Constructor

```cpp
#include <iostream>
using namespace std;

class Engine
{
    int hp;

public:

    Engine(int power)
    {
        hp = power;

        cout << "Engine HP : "
             << hp << endl;
    }
};

class Car
{
private:

    Engine engine;

public:

    Car() : engine(150)
    {
        cout << "Car Created\n";
    }
};

int main()
{
    Car car;
}
```

Output

```text
Engine HP : 150

Car Created
```

Notice

```cpp
Car() : engine(150)
```

Member objects are initialized using the **initializer list**.

---

# Composition with Multiple Objects

```cpp
#include <iostream>
using namespace std;

class Engine
{
public:

    void start()
    {
        cout << "Engine Started\n";
    }
};

class Steering
{
public:

    void turn()
    {
        cout << "Turning Steering\n";
    }
};

class Car
{
private:

    Engine engine;

    Steering steering;

public:

    void drive()
    {
        engine.start();

        steering.turn();

        cout << "Car Moving\n";
    }
};

int main()
{
    Car car;

    car.drive();
}
```

Output

```text
Engine Started

Turning Steering

Car Moving
```

---

# Real Life Examples

```text
Computer

↓

CPU

RAM

Hard Disk

Motherboard
```

---

```text
Mobile Phone

↓

Camera

Battery

Speaker

Screen
```

---

```text
School

↓

Classroom

Teacher

Student

Library
```

---

# Composition vs Inheritance

## Composition

```text
Car HAS-A Engine
```

Diagram

```text
Car

|

+----- Engine
```

---

## Inheritance

```text
Dog IS-A Animal
```

Diagram

```text
Animal

|

Dog
```

---

# Composition vs Aggregation

Composition

```text
Car HAS-A Engine
```

If Car is destroyed

```text
↓

Engine also destroyed
```

Ownership

```text
Car owns Engine
```

---

Aggregation

```text
School HAS Teachers
```

If School closes

```text
↓

Teacher still exists
```

Ownership

```text
School does NOT own Teacher
```

---

# Composition Example

```cpp
class Engine
{
};

class Car
{
    Engine engine;
};
```

Engine lifetime depends on Car.

---

# Aggregation Example

```cpp
class Teacher
{
};

class School
{
    Teacher* teacher;

public:

    School(Teacher* t)
    {
        teacher = t;
    }
};
```

Teacher exists independently.

---

# Advantages

- Code Reusability
- Low Coupling
- High Cohesion
- Better Encapsulation
- Easy Maintenance
- Flexible Design

---

# Disadvantages

- Tight ownership
- Object lifetime tied together
- Less flexible than aggregation

---

# Interview Questions

## Q1. What is Composition?

Composition is a **Has-A** relationship where one class contains another class as a member object.

---

## Q2. Difference between Composition and Inheritance?

| Composition | Inheritance |
|-------------|-------------|
| Has-A | Is-A |
| Reuse by objects | Reuse by inheritance |
| Flexible | Less flexible |
| Low coupling | Tight hierarchy |

---

## Q3. Difference between Composition and Aggregation?

| Composition | Aggregation |
|-------------|-------------|
| Strong ownership | Weak ownership |
| Child lifetime depends on parent | Child exists independently |
| Member object | Pointer/Reference |

---

## Q4. Why prefer Composition over Inheritance?

Composition provides

- Better flexibility
- Lower coupling
- Easier maintenance
- Better code reuse

Modern C++ follows the principle:

```text
Favor Composition

Over

Inheritance
```

---

# Memory Trick

```text
Inheritance

↓

IS-A

Dog IS-A Animal

------------------------

Composition

↓

HAS-A

Car HAS-A Engine

------------------------

Aggregation

↓

USES-A

School USES Teacher
```

---

# Summary

```text
Composition

↓

One class owns another

↓

Has-A Relationship

↓

Member Object

↓

Same Lifetime

↓

Destroyed Together

↓

Preferred over Inheritance
```