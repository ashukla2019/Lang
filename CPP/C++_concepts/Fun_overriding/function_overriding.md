# C++ Function Overriding (Runtime Polymorphism) - Interview Notes

---

# What is Function Overriding?

Function overriding occurs when a **derived class provides its own implementation** of a function that is already defined in the **base class**.

The base class function **must be declared `virtual`**.

It is the foundation of **Runtime Polymorphism**.

---

# Requirements for Function Overriding

For overriding to happen:

- Same function name
- Same parameter list
- Same return type (or covariant return type)
- Base class function must be `virtual`
- Function must be inherited

---

# Basic Example

```cpp
#include <iostream>
using namespace std;

class Animal
{
public:

    virtual void sound()
    {
        cout << "Animal makes sound\n";
    }
};

class Dog : public Animal
{
public:

    void sound() override
    {
        cout << "Dog barks\n";
    }
};

int main()
{
    Dog d;

    d.sound();
}
```

Output

```text
Dog barks
```

---

# Why use virtual?

Without `virtual`

```cpp
class Animal
{
public:

    void sound()
    {
        cout << "Animal\n";
    }
};

class Dog : public Animal
{
public:

    void sound()
    {
        cout << "Dog\n";
    }
};
```

```cpp
Animal* ptr = new Dog;

ptr->sound();
```

Output

```text
Animal
```

Because

```
Compile-time Binding
```

---

# With virtual

```cpp
class Animal
{
public:

    virtual void sound()
    {
        cout << "Animal\n";
    }
};

class Dog : public Animal
{
public:

    void sound() override
    {
        cout << "Dog\n";
    }
};
```

```cpp
Animal* ptr = new Dog;

ptr->sound();
```

Output

```text
Dog
```

Because

```
Runtime Binding
```

---

# Runtime Polymorphism

```text
Animal*

      │

      ▼

+-----------+
|   Dog     |
+-----------+

ptr->sound()

↓

Calls Dog::sound()
```

The function is selected at **runtime** based on the actual object.

---

# What does virtual do internally?

The compiler creates a

```
Virtual Table (vtable)
```

Each object contains a hidden pointer called

```
vptr
```

which points to the class's vtable.

---

## Example

```cpp
class Animal
{
public:

    virtual void sound();
    virtual void eat();
};

class Dog : public Animal
{
public:

    void sound() override;
    void eat() override;
};
```

---

### Animal vtable

```text
Animal vtable

sound() ---> Animal::sound()

eat() -----> Animal::eat()
```

---

### Dog vtable

```text
Dog vtable

sound() ---> Dog::sound()

eat() -----> Dog::eat()
```

When

```cpp
Animal* ptr = new Dog;

ptr->sound();
```

Flow

```text
ptr

↓

Dog Object

↓

vptr

↓

Dog vtable

↓

Dog::sound()
```

---

# Using override Keyword

```cpp
class Dog : public Animal
{
public:

    void sound() override
    {
        cout << "Dog";
    }
};
```

Benefits

- Compile-time checking
- Prevents accidental mistakes
- Improves readability

---

# Example of Mistake

```cpp
class Animal
{
public:

    virtual void sound();
};

class Dog : public Animal
{
public:

    void sound(int x);
};
```

Without

```cpp
override
```

This becomes a **new function**, not an override.

With

```cpp
override
```

Compiler error:

```text
error: 'sound(int)' marked override but does not override
```

---

# Accessing Base Class Function

```cpp
class Animal
{
public:

    virtual void sound()
    {
        cout << "Animal\n";
    }
};

class Dog : public Animal
{
public:

    void sound() override
    {
        Animal::sound();

        cout << "Dog\n";
    }
};
```

Output

```text
Animal
Dog
```

---

# Can Constructors be Overridden?

No.

Constructors are **not inherited**, so they cannot be overridden.

```cpp
class Base
{
public:

    Base() {}
};

class Derived : public Base
{
public:

    Derived() {}
};
```

---

# Can Static Functions be Overridden?

No.

Static functions belong to the class, not the object.

```cpp
class Base
{
public:

    static void fun();
};
```

Cannot override.

---

# Can Friend Functions be Overridden?

No.

Friend functions are not class members.

---

# Can Private Functions be Overridden?

Yes.

A private virtual function can still be overridden.

```cpp
class Base
{
private:

    virtual void fun()
    {
    }
};

class Derived : public Base
{
private:

    void fun() override
    {
    }
};
```

The derived class overrides it even though the base version is private.

---

# Virtual Destructor

Always make the base destructor virtual if deleting through a base pointer.

Wrong

```cpp
class Base
{
public:

    ~Base()
    {
    }
};
```

Correct

```cpp
class Base
{
public:

    virtual ~Base()
    {
    }
};
```

Example

```cpp
Base* ptr = new Derived;

delete ptr;
```

Without virtual destructor,

only

```
Base Destructor
```

runs.

With virtual,

```
Derived Destructor

↓

Base Destructor
```

Both execute correctly.

---

# Function Overriding vs Function Overloading

| Function Overriding | Function Overloading |
|----------------------|----------------------|
| Different classes | Same class |
| Runtime Polymorphism | Compile-time Polymorphism |
| Requires inheritance | No inheritance |
| Same signature | Different parameters |
| Uses virtual | Does not require virtual |

---

# Overriding vs Hiding

## Overriding

```cpp
class Base
{
public:

    virtual void fun();
};

class Derived : public Base
{
public:

    void fun() override;
};
```

Calls

```
Derived::fun()
```

through base pointer.

---

## Hiding

```cpp
class Base
{
public:

    void fun();
};

class Derived
{
public:

    void fun();
};
```

No virtual.

This hides the base function.

No runtime polymorphism.

---

# Covariant Return Type

Allowed

```cpp
class Base
{
public:

    virtual Base* clone();
};

class Derived : public Base
{
public:

    Derived* clone() override;
};
```

Derived pointer is acceptable.

---

# Pure Virtual Function

```cpp
class Animal
{
public:

    virtual void sound() = 0;
};
```

This makes

```
Animal
```

an **Abstract Class**.

Derived class must override.

```cpp
class Dog : public Animal
{
public:

    void sound() override
    {
        cout << "Dog";
    }
};
```

---

# Summary Table

| Feature | Function Overriding |
|----------|---------------------|
| Polymorphism | Runtime |
| Keyword | `virtual` |
| Recommended | `override` |
| Requires Inheritance | Yes |
| Same Function Signature | Yes |
| Base Pointer Calls Derived Function | Yes |
| Uses vtable | Yes |

---

# Interview Questions

### Q1. What is Function Overriding?

Derived class provides a new implementation of a virtual function of the base class.

---

### Q2. Why is virtual required?

To enable **runtime polymorphism (dynamic binding)**.

---

### Q3. Difference between Overloading and Overriding?

| Overloading | Overriding |
|--------------|------------|
| Same class | Different classes |
| Different parameters | Same parameters |
| Compile time | Runtime |
| No inheritance | Requires inheritance |

---

### Q4. Can constructors be overridden?

No.

---

### Q5. Can static functions be overridden?

No.

---

### Q6. Can friend functions be overridden?

No.

---

### Q7. Why use override keyword?

- Compiler checks correctness
- Prevents accidental function hiding
- Improves readability

---

# Memory Trick

```
Overloading
↓

Same Class

Different Parameters

Compile Time

-------------------------

Overriding
↓

Different Classes

Same Parameters

virtual

Runtime

-------------------------

override
↓

Compiler checks

-------------------------

virtual
↓

vtable

↓

vptr

↓

Runtime Binding
```

---

# One-Line Summary

> **Function Overriding allows a derived class to replace a base class's virtual function implementation, enabling runtime polymorphism through virtual dispatch (vtable/vptr).**