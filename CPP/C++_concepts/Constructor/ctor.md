# C++ Copy Constructor, Move Constructor, Copy Assignment, Move Assignment (Rule of Five)

This example demonstrates:

- Parameterized Constructor
- Copy Constructor (Deep Copy)
- Copy Assignment Operator
- Move Constructor
- Move Assignment Operator
- Destructor
- Return Value Optimization (RVO)
- Named Return Value Optimization (NRVO)

> **Note:** This example has a few issues (`sizeof(src)` and `sizeof(src.name)` are incorrect for allocating strings). The corrected version below uses `strlen()` and properly handles resource management.

---

# Complete Example

```cpp
#include <iostream>
#include <cstring>

class MyCtr
{
    int id;
    char* name;

public:

    // Default Constructor
    MyCtr() : id(0), name(nullptr)
    {
        std::cout << "Default Constructor\n";
    }

    // Parameterized Constructor
    MyCtr(int id, const char* src)
        : id(id)
    {
        name = new char[strlen(src) + 1];
        strcpy(name, src);

        std::cout << "Parameterized Constructor\n";
    }

    // Copy Constructor (Deep Copy)
    MyCtr(const MyCtr& src)
        : id(src.id)
    {
        if (src.name)
        {
            name = new char[strlen(src.name) + 1];
            strcpy(name, src.name);
        }
        else
        {
            name = nullptr;
        }

        std::cout << "Copy Constructor\n";
    }

    // Copy Assignment Operator
    MyCtr& operator=(const MyCtr& src)
    {
        if (this == &src)
            return *this;

        delete[] name;

        id = src.id;

        if (src.name)
        {
            name = new char[strlen(src.name) + 1];
            strcpy(name, src.name);
        }
        else
        {
            name = nullptr;
        }

        std::cout << "Copy Assignment Operator\n";

        return *this;
    }

    // Move Constructor
    MyCtr(MyCtr&& src) noexcept
        : id(src.id), name(src.name)
    {
        src.name = nullptr;

        std::cout << "Move Constructor\n";
    }

    // Move Assignment Operator
    MyCtr& operator=(MyCtr&& src) noexcept
    {
        if (this == &src)
            return *this;

        delete[] name;

        id = src.id;
        name = src.name;

        src.name = nullptr;

        std::cout << "Move Assignment Operator\n";

        return *this;
    }

    // Destructor
    ~MyCtr()
    {
        delete[] name;

        std::cout << "Destructor\n";
    }
};


//----------------------
// RVO Example
//----------------------

MyCtr fun()
{
    return MyCtr(2, "A");

    // RVO (Return Value Optimization)
    // Compiler constructs the object directly in the caller.
}


//----------------------
// NRVO Example
//----------------------

MyCtr test(MyCtr obj)
{
    MyCtr temp(3, "B");

    return temp;

    // NRVO (Named Return Value Optimization)
    // Compiler may construct temp directly in the caller.
}


int main()
{
    MyCtr obj1(1, "ABC");

    // Copy Constructor
    MyCtr obj2 = obj1;

    // Default Constructor
    MyCtr obj3;

    // Copy Assignment Operator
    obj3 = obj2;

    // Move Constructor
    MyCtr obj4 = std::move(obj3);

    // RVO
    MyCtr obj5 = fun();

    // NRVO
    MyCtr obj6 = test(MyCtr());

    return 0;
}
```

---

# What Each Function Does

## 1. Default Constructor

```cpp
MyCtr() : id(0), name(nullptr)
{
}
```

Creates an empty object.

---

## 2. Parameterized Constructor

```cpp
MyCtr(int id, const char* src)
```

Allocates memory and copies the string.

```text
obj1
 │
 ▼
ABC
```

---

## 3. Copy Constructor

```cpp
MyCtr(const MyCtr& src)
```

Creates a **new object** from an existing object.

Performs **deep copy**.

```text
obj1 ---> ABC

obj2 ---> ABC
```

Both objects own different memory.

---

## 4. Copy Assignment Operator

```cpp
obj3 = obj2;
```

Copies data into an **already existing object**.

```text
Before

obj3 ---> nullptr

After

obj3 ---> ABC
```

Always:

- Check self-assignment.
- Delete old memory.
- Allocate new memory.
- Copy data.

---

## 5. Move Constructor

```cpp
MyCtr obj4 = std::move(obj3);
```

Transfers ownership instead of copying.

Before

```text
obj3

 └──► ABC
```

After

```text
obj4

 └──► ABC


obj3

 └──► nullptr
```

No memory allocation occurs.

---

## 6. Move Assignment Operator

```cpp
obj2 = std::move(obj1);
```

Transfers resources to an existing object.

Steps:

1. Delete current memory.
2. Steal pointer.
3. Set source pointer to `nullptr`.

---

## 7. Destructor

```cpp
~MyCtr()
{
    delete[] name;
}
```

Automatically releases allocated memory.

Without this destructor:

```text
Memory Leak
```

---

# Why Deep Copy?

Suppose we write:

```cpp
name = src.name;
```

Then

```text
obj1 ----\
          \
           ---> ABC

obj2 ----/
```

Both objects point to the same memory.

When destructors execute:

```cpp
delete[] name;
delete[] name;
```

Same memory deleted twice.

Result:

```text
Double Free
Undefined Behavior
```

Deep copy avoids this.

---

# Why Move Constructor?

Copying:

```text
Allocate Memory

Copy Characters

Delete Later
```

Moving:

```text
Take Pointer

Set Source = nullptr
```

No allocation.

No copy.

Very fast.

---

# Rule of Five

Whenever a class manages dynamic resources, define:

```cpp
Destructor

Copy Constructor

Copy Assignment Operator

Move Constructor

Move Assignment Operator
```

These five together are known as the **Rule of Five**.

---

# RVO (Return Value Optimization)

Example

```cpp
MyCtr fun()
{
    return MyCtr(2, "A");
}
```

Without RVO

```text
Create Temporary

↓

Move Constructor

↓

Destroy Temporary
```

With RVO

```text
Construct object directly
inside caller.
```

No move constructor.

No copy constructor.

---

# NRVO (Named Return Value Optimization)

Example

```cpp
MyCtr temp(3, "B");

return temp;
```

Compiler constructs `temp` directly in the caller.

Again,

No copy.

No move.

---

# Disable Copy Elision

To observe copy/move constructors, compile with:

```bash
g++ -fno-elide-constructors file.cpp
```

Then RVO/NRVO are disabled and move constructors become visible.

---

# Constructor Calls in `main()`

```cpp
MyCtr obj1(1, "ABC");
```

Calls:

```text
Parameterized Constructor
```

---

```cpp
MyCtr obj2 = obj1;
```

Calls:

```text
Copy Constructor
```

---

```cpp
MyCtr obj3;
```

Calls:

```text
Default Constructor
```

---

```cpp
obj3 = obj2;
```

Calls:

```text
Copy Assignment Operator
```

---

```cpp
MyCtr obj4 = std::move(obj3);
```

Calls:

```text
Move Constructor
```

---

```cpp
MyCtr obj5 = fun();
```

Normally:

```text
RVO
```

Move constructor is usually **not** called.

---

```cpp
MyCtr obj6 = test(MyCtr());
```

Normally:

```text
NRVO
```

Move constructor is usually **not** called.

---

# Expected Output (Typical Compiler)

```text
Parameterized Constructor
Copy Constructor
Default Constructor
Copy Assignment Operator
Move Constructor
Parameterized Constructor
Default Constructor
Parameterized Constructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
```

> The exact output may vary depending on whether the compiler performs **RVO/NRVO**.

---

# Important Mistakes in the Original Code

### ❌ Incorrect

```cpp
new char[sizeof(src) + 1]
```

`sizeof(src)` returns the **size of the pointer**, **not** the string length.

### ✅ Correct

```cpp
new char[strlen(src) + 1]
```

---

### ❌ Incorrect

```cpp
new char[sizeof(src.name) + 1]
```

Again, this allocates memory equal to the pointer size.

### ✅ Correct

```cpp
new char[strlen(src.name) + 1]
```

---

### ❌ Missing Self-Assignment Check

```cpp
obj = obj;
```

Should be handled as:

```cpp
if (this == &src)
    return *this;
```

---

### ❌ Memory Leak in Assignment Operator

Always free existing memory before allocating new memory:

```cpp
delete[] name;
```

---

# Key Takeaways

- Use **deep copy** for dynamically allocated memory.
- Implement the **Rule of Five** when managing resources.
- Prefer `std::string` over raw `char*` in modern C++.
- Use **move semantics** to avoid unnecessary copies.
- RVO and NRVO optimize object returns by eliminating copies/moves.
- Use `-fno-elide-constructors` to observe copy and move operations during learning.