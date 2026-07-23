# Aggregation vs Composition (Ownership)

The easiest way to understand the difference is to ask:

> **Who created the object?**

If the class creates the object, it **owns** it.

If someone else creates the object and only passes a pointer/reference, the class **does not own** it.

---

# Example 1 : Aggregation (Person does NOT own Car)

In Aggregation, the `Car` is created outside the `Person`.

`Person` only stores its address.

## Code

```cpp
#include <iostream>
#include <string>

using namespace std;

class Car
{
    string name;
    int model;

public:

    Car(string name, int model)
        : name(name), model(model)
    {
        cout << "Car Constructor\n";
    }

    ~Car()
    {
        cout << "Car Destructor\n";
    }

    void display()
    {
        cout << name << " " << model << endl;
    }
};

class Person
{
    string name;
    Car* myCar;      // Borrowed pointer

public:

    Person(string name, Car* car)
        : name(name), myCar(car)
    {
        cout << "Person Constructor\n";
    }

    ~Person()
    {
        cout << "Person Destructor\n";

        // DON'T delete myCar.
        // Person doesn't own it.
    }

    void showCar()
    {
        myCar->display();
    }
};

int main()
{
    Car c("BMW", 101);

    Person p("Ankit", &c);

    p.showCar();

    return 0;
}
```

---

## Output

```text
Car Constructor
Person Constructor
BMW 101
Person Destructor
Car Destructor
```

---

## Memory Diagram

```
Stack

+----------------------+
| Car c                |
+----------------------+
           ^
           |
           |
+----------------------+
| Person p             |
| myCar -------------- |
+----------------------+
```

Notice

- `Person` did **not** create the `Car`.
- `Person` only stores the address.
- Therefore **Person must not delete the Car**.

---

# Example 2 : Composition (Person owns Car)

Now `Person` creates the `Car`.

Since it creates it, it owns it.

## Code

```cpp
#include <iostream>
#include <string>

using namespace std;

class Car
{
    string name;
    int model;

public:

    Car(string name, int model)
        : name(name), model(model)
    {
        cout << "Car Constructor\n";
    }

    ~Car()
    {
        cout << "Car Destructor\n";
    }

    void display()
    {
        cout << name << " " << model << endl;
    }
};

class Person
{
    string name;
    Car* myCar;

public:

    Person(string name)
        : name(name)
    {
        cout << "Person Constructor\n";

        myCar = new Car("BMW", 101);
    }

    ~Person()
    {
        cout << "Person Destructor\n";

        delete myCar;      // Person owns the Car
    }

    void showCar()
    {
        myCar->display();
    }
};

int main()
{
    Person p("Ankit");

    p.showCar();

    return 0;
}
```

---

## Output

```text
Person Constructor
Car Constructor
BMW 101
Person Destructor
Car Destructor
```

---

## Memory Diagram

```
Stack

+----------------------+
| Person p             |
| myCar --------------+------------------+
+----------------------+                  |
                                          |
                                          V
                                   Heap
                               +-------------+
                               | Car         |
                               +-------------+
```

Notice

- `Person` creates the `Car` using `new`.
- Therefore `Person` owns the `Car`.
- `Person` must delete the `Car`.

---

# Why?

## Aggregation

```cpp
Car c("BMW",101);

Person p("Ankit",&c);
```

Who created the Car?

```
main()
```

Who destroys the Car?

```
main()
```

`Person` only borrows it.

---

## Composition

```cpp
Person p("Ankit");
```

Inside `Person`

```cpp
myCar = new Car("BMW",101);
```

Who created the Car?

```
Person
```

Who destroys the Car?

```
Person
```

---

# Rule

### Aggregation

```cpp
Person(Car* c)
{
    myCar = c;
}
```

✔ Borrowed object

✔ Do NOT delete

---

### Composition

```cpp
Person()
{
    myCar = new Car(...);
}
```

✔ Owned object

✔ Must delete

---

# Interview Trick

Ask only one question:

> **Who called `new`?**

If **Person** called `new`

```
↓

Person owns Car

↓

Person deletes Car
```

If **main()** (or someone else) called `new` or created it on the stack

```
↓

Person only borrows Car

↓

Person must NOT delete Car
```

---

# Modern C++ Version (Recommended)

Instead of raw pointers, use `std::unique_ptr` for composition.

```cpp
class Person
{
    unique_ptr<Car> myCar;

public:

    Person()
    {
        myCar = make_unique<Car>("BMW",101);
    }
};
```

Now you don't need to write:

```cpp
delete myCar;
```

because `unique_ptr` automatically destroys the `Car` when `Person` is destroyed.

This is the recommended approach in modern C++.
