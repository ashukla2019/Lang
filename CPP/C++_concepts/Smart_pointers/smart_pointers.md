# Smart Pointers in C++ (Complete Notes)

---

# Why Smart Pointers?

Before C++11, memory was managed manually.

```cpp
Sample* p = new Sample();

// use p

delete p;
```

Problems:

- Forgetting `delete` → Memory Leak
- Calling `delete` twice → Undefined Behavior
- Exception before `delete` → Memory Leak
- Difficult ownership management

To solve these problems C++11 introduced **Smart Pointers**.

Smart pointers automatically delete dynamically allocated memory.

Header:

```cpp
#include <memory>
```

Available smart pointers:

1. `unique_ptr`
2. `shared_ptr`
3. `weak_ptr`
4. (Deprecated) `auto_ptr`

---

# auto_ptr (Deprecated)

Before C++11 there was:

```cpp
auto_ptr<int> p1(new int(10));
auto_ptr<int> p2 = p1;
```

Ownership transfers.

After assignment:

```
p1 ----> NULL
p2 ----> Memory
```

So:

```cpp
p1->...
```
An auto_ptr does not become a dangling pointer after ownership is transferred. Instead, it becomes a null pointer.
will crash.

Because of this confusing behavior, `auto_ptr` was removed in C++17.

Never use it.

---

# unique_ptr

A `unique_ptr` has **exclusive ownership**.

Only one pointer owns the object.

```
unique_ptr
      |
      V
   Sample Object
```

No copying allowed.

Ownership can only be transferred using `std::move()`.

---

## Example Class

```cpp
class Sample
{
public:

    Sample()
    {
        cout<<"Sample Constructor\n";
    }

    ~Sample()
    {
        cout<<"Sample Destructor\n";
    }

    void publicFn()
    {
        cout<<"Public Function\n";
    }
};
```

---

# 1. Memory is Automatically Released

```cpp
void TestUniquePtr_ReleaseMemory()
{
    unique_ptr<Sample> up(new Sample);

    up->publicFn();

}   // destructor automatically called
```

Output

```
Sample Constructor
Public Function
Sample Destructor
```

Flow

```
Create object
      |

unique_ptr owns object
      |

Function ends
      |

unique_ptr destructor
      |

delete object automatically
```

No explicit

```cpp
delete
```

required.

---

# 2. Copying is NOT Allowed

```cpp
unique_ptr<Sample> up(new Sample);

unique_ptr<Sample> up2 = up;
```

Compiler Error

Reason

Two unique pointers cannot own the same object.

```
      X

up -------> Object
up2 ------> Object
```

Not allowed.

---

# 3. Ownership Transfer using std::move()

```cpp
unique_ptr<Sample> up(new Sample);

unique_ptr<Sample> up2 = std::move(up);
```

Before move

```
up -----> Object
```

After move

```
up ------> NULL

up2 -----> Object
```

Ownership transferred.

No object copied.

No new allocation.

Only pointer ownership changes.

---

# Why std::move()?

Because copying is forbidden.

`std::move()` converts an lvalue into an rvalue.

Then the move constructor of `unique_ptr` transfers ownership.

---

# 4. Returning unique_ptr from Function

```cpp
unique_ptr<Sample> AFunc()
{
    unique_ptr<Sample> up(new Sample);

    return up;
}
```

Calling

```cpp
unique_ptr<Sample> p = AFunc();
```

Flow

```
AFunc()

create object

↓

return unique_ptr

↓

Ownership transferred

↓

Caller owns object
```

No copying occurs.

Move constructor (or copy elision) is used.

---

# 5. Returning Without Taking Ownership

```cpp
AFunc();
```

Nobody stores returned pointer.

Flow

```
AFunc()

↓

create object

↓

return unique_ptr

↓

temporary destroyed

↓

object deleted
```

Memory is freed automatically.

---

# 6. make_unique()

Instead of

```cpp
unique_ptr<Sample> up(new Sample);
```

Prefer

```cpp
auto up = make_unique<Sample>();
```

Advantages

- Safer
- Cleaner
- Exception-safe
- Recommended in Modern C++

Available from C++14.

---

# Complete Example

```cpp
#include <iostream>
#include <memory>

using namespace std;

class Sample
{
public:

    Sample()
    {
        cout<<"Sample Constructor\n";
    }

    ~Sample()
    {
        cout<<"Sample Destructor\n";
    }

    void publicFn()
    {
        cout<<"Public Function\n";
    }
};

void TestUniquePtr_ReleaseMemory()
{
    unique_ptr<Sample> up(new Sample);

    up->publicFn();

}

void TestUniquePtr_NoOwnershipTransfer()
{
    unique_ptr<Sample> up(new Sample);

    // Compiler Error

    // unique_ptr<Sample> up2 = up;
}

void TestUniquePtr_MoveOwnershipTransfer()
{
    unique_ptr<Sample> up(new Sample);

    unique_ptr<Sample> up2 = std::move(up);
}

unique_ptr<Sample> AFunc()
{
    cout<<"Enter AFunc\n";

    unique_ptr<Sample> up(new Sample);

    cout<<"Exit AFunc\n";

    return up;
}

void TestUniquePtr_ReturnFunction()
{
    unique_ptr<Sample> p = AFunc();
}

void TestUniquePtr_ReturnNoOwnership()
{
    AFunc();
}

void TestUniquePtr_MakeUnique()
{
    auto p = make_unique<Sample>();
}
```

---

# shared_ptr

Unlike `unique_ptr`, multiple pointers can own the same object.

```
sp1
   \
    \
     ---> Object
    /
   /
sp2
```

Memory is deleted only when the last owner disappears.

---

# Reference Count

Every shared pointer stores a reference count.

Example

```
shared_ptr p1

Reference Count = 1
```

Copy

```cpp
shared_ptr p2 = p1;
```

Now

```
p1 ----\
        \
         ---> Object

p2 ----/

Reference Count = 2
```

Destroy p2

```
Reference Count = 1
```

Destroy p1

```
Reference Count = 0

↓

delete object
```

---

# 1. Automatic Memory Release

```cpp
void TestSharedPtr_ReleaseMemory()
{
    shared_ptr<Sample> sp(new Sample);

    sp->publicFn();
}
```

Output

```
Constructor

Public Function

Destructor
```

Destructor is automatically called.

---

# 2. Returning shared_ptr

```cpp
shared_ptr<Sample> AFunc()
{
    shared_ptr<Sample> sp(new Sample);

    return sp;
}
```

Calling

```cpp
shared_ptr<Sample> p = AFunc();
```

Ownership is shared.

Reference count remains correct.

---

# 3. use_count()

```cpp
shared_ptr<Sample> p = AFunc();

cout<<p.use_count();
```

Output

```
1
```

Copy

```cpp
shared_ptr<Sample> p2 = p;

cout<<p.use_count();
```

Output

```
2
```

Destroy p2

```
Reference Count = 1
```

Destroy p

```
Reference Count = 0

↓

delete object
```

---

# 4. make_shared()

Instead of

```cpp
shared_ptr<Sample> p(new Sample);
```

Prefer

```cpp
auto p = make_shared<Sample>();
```

Advantages

- Faster
- One allocation
- Cleaner
- Exception-safe

---

# Complete Example

```cpp
#include <iostream>
#include <memory>

using namespace std;

class Sample
{
public:

    Sample()
    {
        cout<<"Constructor\n";
    }

    ~Sample()
    {
        cout<<"Destructor\n";
    }

    void publicFn()
    {
        cout<<"Public Function\n";
    }
};

void TestSharedPtr_ReleaseMemory()
{
    shared_ptr<Sample> sp(new Sample);

    sp->publicFn();
}

shared_ptr<Sample> AFunc()
{
    shared_ptr<Sample> sp(new Sample);

    return sp;
}

void TestSharedPtr_ReferenceCount()
{
    shared_ptr<Sample> p = AFunc();

    cout<<p.use_count()<<endl;

    shared_ptr<Sample> p2 = p;

    cout<<p.use_count()<<endl;
}

void TestSharedPtr_MakeShared()
{
    auto p = make_shared<Sample>();
}
```

---

# Writing Your Own Smart Pointer

A simple smart pointer owns a raw pointer and deletes it in its destructor.

```cpp
template<typename T>
class SP
{
    T* pData;

public:

    SP(T* p)
        : pData(p)
    {
    }

    ~SP()
    {
        delete pData;
    }

    T& operator*()
    {
        return *pData;
    }

    T* operator->()
    {
        return pData;
    }
};
```

Usage

```cpp
SP<Person> p(new Person("Scott",25));

p->Display();
```

Flow

```
new Person

↓

SP owns Person

↓

Function ends

↓

SP destructor

↓

delete Person
```

---

# Another Custom Smart Pointer Example

```cpp
template<typename T>
class smart_ptr
{
    T* usr;

public:

    smart_ptr(T* p)
        : usr(p)
    {
    }

    T* operator->()
    {
        return usr;
    }

    ~smart_ptr()
    {
        delete usr;
    }
};
```

Usage

```cpp
smart_ptr<user> u(new user(1,"Ankit"));

auto [id,name] = u->getUserDetails();

cout<<id<<" "<<name;
```

---

# Why operator-> ?

Without operator overloading

```cpp
smart_ptr<user> p(...);

p->getUserDetails();
```

would not compile.

Implement

```cpp
T* operator->()
{
    return usr;
}
```

Compiler converts

```
p->func()
```

into

```
p.operator->()->func()
```

---

# Why operator* ?

Allows

```cpp
(*p).Display();
```

Implementation

```cpp
T& operator*()
{
    return *usr;
}
```

---

# Comparison

| Feature | unique_ptr | shared_ptr | weak_ptr |
|----------|------------|------------|-----------|
| Owners | One | Multiple | None |
| Copy | ❌ | ✅ | ✅ |
| Move | ✅ | ✅ | ✅ |
| Reference Count | ❌ | ✅ | Observes shared_ptr |
| Fast | ✅ | Slower | Fast |
| Memory Overhead | Low | Higher | Low |

---

# make_unique vs new

Instead of

```cpp
unique_ptr<Sample> p(new Sample);
```

Use

```cpp
auto p = make_unique<Sample>();
```

Better because

- Cleaner
- Exception-safe
- Recommended by Modern C++

---

# make_shared vs new

Instead of

```cpp
shared_ptr<Sample> p(new Sample);
```

Use

```cpp
auto p = make_shared<Sample>();
```

Benefits

- One memory allocation
- Faster
- Less fragmentation
- Exception-safe

---

# Interview Questions

## Why use smart pointers?

To automatically manage dynamic memory and avoid memory leaks.

---

## Why can't unique_ptr be copied?

Because it has exclusive ownership of the object.

---

## Why does std::move() work?

It transfers ownership instead of copying.

---

## When is shared_ptr memory released?

When the reference count becomes zero.

---

## What does use_count() return?

The number of `shared_ptr` objects currently owning the resource.

---

## Why prefer make_shared()?

- One allocation
- Faster
- Exception-safe

---

## Why prefer make_unique()?

- Cleaner syntax
- Exception-safe
- Recommended modern C++

---

## When should you use unique_ptr?

When only one object should own the resource.

---

## When should you use shared_ptr?

When multiple objects need to share ownership.

---

## When should you use weak_ptr?

To observe a `shared_ptr` object **without increasing the reference count**, and to break circular references.

---

# Summary

| Smart Pointer | Ownership | Copy | Move | Auto Delete |
|---------------|-----------|------|------|-------------|
| auto_ptr (Removed) | Single | Transfers ownership | Yes | Yes |
| unique_ptr | Single | ❌ | ✅ | ✅ |
| shared_ptr | Shared | ✅ | ✅ | ✅ |
| weak_ptr | No ownership | ✅ | ✅ | ❌ |

**Rule of thumb:**

- Use **`unique_ptr`** by default.
- Use **`shared_ptr`** only when ownership must truly be shared.
- Use **`weak_ptr`** to observe a shared object or to prevent circular references.
- Never use **`auto_ptr`** in modern C++.
