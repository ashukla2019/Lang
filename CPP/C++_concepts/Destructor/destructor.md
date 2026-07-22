# C++ Destructor

A **destructor** is a special member function that is invoked **automatically** whenever an object is about to be destroyed.

It is the **last function** called before an object is destroyed and is mainly used to **release resources** (memory, files, sockets, etc.).

---

# Features of Destructor

1. A destructor is a **special member function**, just like a constructor.
2. It **destroys objects** created by the constructor.
3. The destructor has the **same name as the class**, preceded by a tilde (`~`).

   ```cpp
   ~ClassName();
   ```

4. A class can have **only one destructor**.
5. A destructor **cannot be overloaded**.
6. It **takes no arguments**.
7. It **returns no value** (not even `void`).
8. It is **called automatically** when an object goes out of scope.
9. It releases resources occupied by the object.
10. Objects are destroyed in the **reverse order of their creation**.

---

# Syntax

```cpp
class ClassName
{
public:
    ~ClassName()
    {
        // Cleanup code
    }
};
```

---

# Example 1: Constructor and Destructor

```cpp
#include <iostream>
using namespace std;

class Test
{
public:
    // Constructor
    Test()
    {
        cout << "Constructor executed\n";
    }

    // Destructor
    ~Test()
    {
        cout << "Destructor executed\n";
    }
};

int main()
{
    Test t;

    return 0;
}
```

## Output

```text
Constructor executed
Destructor executed
```

### Explanation

- Object `t` is created.
- Constructor is called automatically.
- At the end of `main()`, object goes out of scope.
- Destructor is called automatically.

---

# Example 2: Multiple Objects

```cpp
#include <iostream>
using namespace std;

class Test
{
public:
    Test()
    {
        cout << "Constructor executed\n";
    }

    ~Test()
    {
        cout << "Destructor executed\n";
    }
};

int main()
{
    Test t, t1, t2, t3;

    return 0;
}
```

## Output

```text
Constructor executed
Constructor executed
Constructor executed
Constructor executed

Destructor executed
Destructor executed
Destructor executed
Destructor executed
```

### Explanation

Objects are created in this order:

```text
t
t1
t2
t3
```

Objects are destroyed in **reverse order**:

```text
t3
t2
t1
t
```

---

# Example 3: Counting Objects

```cpp
#include <iostream>
using namespace std;

static int Count = 0;

class Test
{
public:

    Test()
    {
        Count++;
        cout << "Objects Created : " << Count << endl;
    }

    ~Test()
    {
        cout << "Objects Destroyed : " << Count << endl;
        Count--;
    }
};

int main()
{
    Test t, t1, t2, t3;

    return 0;
}
```

## Output

```text
Objects Created : 1
Objects Created : 2
Objects Created : 3
Objects Created : 4

Objects Destroyed : 4
Objects Destroyed : 3
Objects Destroyed : 2
Objects Destroyed : 1
```

### Explanation

The static variable `Count` is shared by all objects.

Creation order:

```text
1
2
3
4
```

Destruction order:

```text
4
3
2
1
```

---

# Properties of Destructor

- Automatically invoked when an object is destroyed.
- Cannot be declared `static`.
- Cannot be declared `const`.
- Takes **no parameters**.
- Has **no return type**.
- Cannot be overloaded.
- Usually declared in the **public** section.
- Cannot take the address of a destructor directly.
- Objects containing destructors cannot be members of a `union`.

---

# When is a Destructor Called?

A destructor is called automatically when:

1. A function ends.
2. The program terminates.
3. A block containing local objects ends.
4. `delete` is used on an object created using `new`.

Example:

```cpp
{
    Test t;
}   // Destructor called here
```

---

# Calling Destructor Explicitly

Although rarely needed, a destructor can be called explicitly.

```cpp
objectName.~ClassName();
```

Example

```cpp
Test t;

t.~Test();
```

> **Warning**
>
> Explicitly calling a destructor on a stack object is generally **unsafe** because it will be called again automatically when the object goes out of scope.

---

# Destructor vs Normal Member Function

| Destructor | Normal Function |
|------------|-----------------|
| Same name as class prefixed with `~` | Any valid name |
| No arguments | Can have arguments |
| No return type | Can return values |
| Automatically called | Called explicitly |
| Only one per class | Can overload multiple functions |

---

# Default Destructor

If you do **not** write a destructor, the compiler generates one automatically.

```cpp
class Test
{
};
```

Compiler generates something equivalent to:

```cpp
~Test()
{
}
```

This works fine if the class does **not** allocate dynamic memory.

---

# When Should We Write Our Own Destructor?

Write a destructor whenever the class manages resources such as:

- Dynamic memory (`new`)
- File handles
- Database connections
- Network sockets
- Mutexes
- Locks

Example

```cpp
class Test
{
    int *ptr;

public:

    Test()
    {
        ptr = new int[100];
    }

    ~Test()
    {
        delete[] ptr;
    }
};
```

Without the destructor:

```text
Memory Leak
```

With the destructor:

```text
Memory is released correctly.
```

---

# Can a Destructor be Virtual?

**Yes.**

Whenever a class is intended to be used as a **base class** and contains **virtual functions**, its destructor should also be **virtual**.

---

# Virtual Destructor

Suppose we delete a derived object using a base class pointer.

If the base destructor is **not virtual**, only the base destructor executes.

This causes:

- Undefined behavior
- Resource leaks
- Derived destructor never runs

---

## Example Without Virtual Destructor

```cpp
#include <iostream>
using namespace std;

class Base
{
public:

    Base()
    {
        cout << "Constructing Base\n";
    }

    ~Base()
    {
        cout << "Destructing Base\n";
    }
};

class Derived : public Base
{
public:

    Derived()
    {
        cout << "Constructing Derived\n";
    }

    ~Derived()
    {
        cout << "Destructing Derived\n";
    }
};

int main()
{
    Derived *d = new Derived;

    Base *b = d;

    delete b;
}
```

## Output

```text
Constructing Base
Constructing Derived

Destructing Base
```

### Problem

`Derived` destructor never executes.

Resources owned by `Derived` may leak.

This is **Undefined Behavior**.

---

# Correct Way: Virtual Destructor

```cpp
#include <iostream>
using namespace std;

class Base
{
public:

    Base()
    {
        cout << "Constructing Base\n";
    }

    virtual ~Base()
    {
        cout << "Destructing Base\n";
    }
};

class Derived : public Base
{
public:

    Derived()
    {
        cout << "Constructing Derived\n";
    }

    ~Derived()
    {
        cout << "Destructing Derived\n";
    }
};

int main()
{
    Derived *d = new Derived;

    Base *b = d;

    delete b;
}
```

## Output

```text
Constructing Base
Constructing Derived

Destructing Derived
Destructing Base
```

---

# Why Virtual Destructor Works

When executing

```cpp
delete b;
```

where

```cpp
Base *b = new Derived;
```

The compiler checks whether `Base` destructor is virtual.

If it is virtual:

```text
delete b
      │
      ▼
Derived::~Derived()
      │
      ▼
Base::~Base()
```

Both destructors execute correctly.

---

# Constructor vs Destructor

| Constructor | Destructor |
|-------------|------------|
| Initializes object | Cleans up object |
| Same name as class | Same name prefixed with `~` |
| Can be overloaded | Cannot be overloaded |
| Can have parameters | No parameters |
| Called during object creation | Called during object destruction |
| Can allocate memory | Should release memory |
| Runs in base → derived order | Runs in derived → base order |

---

# Order of Constructor and Destructor Calls

For inheritance:

```cpp
class A {};
class B : public A {};
```

Creation:

```text
A Constructor
↓
B Constructor
```

Destruction:

```text
B Destructor
↓
A Destructor
```

Remember:

> **Constructors execute from Base → Derived**  
> **Destructors execute from Derived → Base**

---

# Interview Questions

### Q1. Can a destructor be overloaded?

**No.** A class can have only one destructor.

---

### Q2. Can a destructor have parameters?

**No.**

---

### Q3. Can a destructor return a value?

**No.**

---

### Q4. Can a destructor be virtual?

**Yes.** It should be virtual for polymorphic base classes.

---

### Q5. Can a destructor be static?

**No.**

---

### Q6. Can we call a destructor manually?

Yes.

```cpp
obj.~ClassName();
```

But it is rarely required and should be used carefully.

---

### Q7. Why do we write user-defined destructors?

To release resources such as:

- Dynamic memory
- Files
- Sockets
- Database connections
- Locks

---

### Q8. What happens if we don't write a destructor?

The compiler generates a default destructor.

It is sufficient unless the class owns dynamically allocated resources.

---

# Key Points to Remember

- Destructor is called automatically.
- Only one destructor per class.
- Destructor name is `~ClassName()`.
- No arguments.
- No return type.
- Cannot be overloaded.
- Releases allocated resources.
- Objects are destroyed in reverse order of creation.
- Always use **virtual destructors** in polymorphic base classes.
- Helps prevent memory leaks and ensures proper cleanup.