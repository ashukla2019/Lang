# C++ RVO, NRVO & Copy Elision (Complete Interview Notes)

---

# Why do RVO/NRVO exist?

Returning an object by value could be expensive.

Without optimization:

```cpp
A fun()
{
    A obj;
    return obj;
}

int main()
{
    A a = fun();
}
```

Flow:

```
Construct obj

↓

Copy/Move obj

↓

Construct a
```

Extra copy/move is unnecessary.

To avoid this, the compiler performs **Copy Elision**.

---

# What is Copy Elision?

## Definition

**Copy Elision** is a compiler optimization that eliminates unnecessary copy and move constructor calls by constructing an object directly in its final destination.

Instead of

```
Temporary

↓

Copy

↓

Destination
```

the compiler does

```
Destination

↓

Construct directly
```

---

# Types of Copy Elision

```
Copy Elision
│
├── RVO (Return Value Optimization)
│
└── NRVO (Named Return Value Optimization)
```

---

# 1. Return Value Optimization (RVO)

## Definition

RVO occurs when a function returns an **unnamed temporary object (prvalue).**

Example

```cpp
class MyCtr
{
public:

    MyCtr(int id, const char* name)
    {
        cout << "Parameterized Constructor\n";
    }

    MyCtr(const MyCtr&)
    {
        cout << "Copy Constructor\n";
    }

    MyCtr(MyCtr&&)
    {
        cout << "Move Constructor\n";
    }
};

MyCtr fun()
{
    return MyCtr(2, "A");
}

int main()
{
    MyCtr obj = fun();
}
```

---

## Without RVO

```
Create Temporary

↓

Move/Copy Temporary

↓

Create obj
```

Constructor Calls

```
Parameterized

Move

or

Copy
```

---

## With RVO

```
obj

↓

Construct directly
```

Only

```
Parameterized Constructor
```

is called.

---

# C++17 Rule

Since C++17,

RVO is **mandatory**.

That means

```cpp
return MyCtr(2, "A");
```

**must not**

create a temporary.

Instead,

```
Caller Object

↓

Construct Directly
```

Therefore,

```
Copy Constructor

NOT called

Move Constructor

NOT called
```

Only

```
Parameterized Constructor
```

runs.

---

# Why?

The return expression

```cpp
MyCtr(2,"A")
```

is a **prvalue**.

Since C++17,

a prvalue does not need to create a temporary object.

It initializes the destination object directly.

---

# Memory Diagram

```
fun()

↓

return MyCtr()

↓

obj

Only ONE object exists.
```

---

# 2. Named Return Value Optimization (NRVO)

## Definition

NRVO occurs when returning a **named local variable**.

Example

```cpp
MyCtr fun()
{
    MyCtr temp(2,"A");

    return temp;
}
```

Here,

```
temp
```

is a named object.

---

# Without NRVO

```
temp

↓

Move Constructor

↓

obj
```

or

```
temp

↓

Copy Constructor

↓

obj
```

---

# With NRVO

Compiler constructs

```
temp
```

directly inside

```
obj
```

Memory

```
obj

↑

temp
```

They are actually the same object.

Only

```
Parameterized Constructor
```

is called.

---

# Is NRVO Guaranteed?

## No.

NRVO is **optional**.

The compiler may

```
Perform NRVO
```

or

```
Use Move Constructor
```

Both are legal.

---

# Why isn't NRVO mandatory?

Consider

```cpp
MyCtr fun(bool flag)
{
    MyCtr a(10);

    MyCtr b(20);

    if(flag)
        return a;

    return b;
}
```

Question

Which object should be constructed directly?

```
a ?

or

b ?
```

Compiler doesn't know until runtime.

Therefore,

the standard allows the compiler to decide.

Hence

```
NRVO

Optional
```

---

# RVO vs NRVO

| Feature | RVO | NRVO |
|----------|-----|------|
| Returns | Temporary object | Named local object |
| Example | `return MyCtr();` | `return temp;` |
| C++17 | Guaranteed | Not Guaranteed |
| Temporary Exists | No | Yes |
| Compiler Choice | No choice | May optimize |

---

# Copy Constructor

Example

```cpp
MyCtr a(10);

MyCtr b = a;
```

Output

```
Parameterized Constructor

Copy Constructor
```

Reason

```
Named object

↓

Another named object
```

---

# Move Constructor

Example

```cpp
MyCtr a(10);

MyCtr b = std::move(a);
```

Output

```
Parameterized Constructor

Move Constructor
```

Move transfers ownership instead of copying.

---

# When is Move Constructor Used?

Suppose

```cpp
MyCtr fun()
{
    MyCtr temp(10);

    return temp;
}
```

If NRVO is **not** performed,

compiler tries

```
Move Constructor
```

If move constructor doesn't exist,

compiler uses

```
Copy Constructor
```

---

# Complete Decision Flow

```
return MyCtr()

↓

RVO

↓

Direct Construction

(No Copy)

(No Move)

--------------------------------

return temp

↓

Can NRVO happen?

↓

YES

↓

Direct Construction

(No Copy)

(No Move)

--------------------------------

NO

↓

Move Constructor Available?

↓

YES

↓

Move Constructor

↓

NO

↓

Copy Constructor
```

---

# Constructor Calls in Different Cases

## Case 1

```cpp
MyCtr obj(10);
```

Calls

```
Parameterized Constructor
```

---

## Case 2

```cpp
MyCtr obj2 = obj1;
```

Calls

```
Copy Constructor
```

---

## Case 3

```cpp
MyCtr obj2 = std::move(obj1);
```

Calls

```
Move Constructor
```

---

## Case 4

```cpp
return MyCtr();
```

C++17

```
Parameterized Constructor

Only
```

---

## Case 5

```cpp
MyCtr temp;

return temp;
```

Compiler performs NRVO

```
Parameterized Constructor

Only
```

---

## Case 6

```cpp
MyCtr temp;

return temp;
```

Compiler does NOT perform NRVO

```
Parameterized Constructor

↓

Move Constructor
```

or

```
Parameterized Constructor

↓

Copy Constructor
```

---

# Why Return by Value is Efficient

Modern C++

```cpp
vector<int> createVector()
{
    vector<int> v;

    return v;
}
```

looks expensive,

but compiler performs

```
NRVO

or

Move
```

Therefore

returning by value is usually efficient.

---

# Interview Questions

## Q1. What is Copy Elision?

Compiler optimization that removes unnecessary copy/move constructor calls by constructing the object directly in its destination.

---

## Q2. What is RVO?

Optimization when returning an unnamed temporary object.

Example

```cpp
return MyCtr();
```

Guaranteed since C++17.

---

## Q3. What is NRVO?

Optimization when returning a named local variable.

Example

```cpp
return temp;
```

Optional.

---

## Q4. Why is RVO guaranteed but NRVO isn't?

Because

```
return MyCtr();
```

returns a **prvalue**, and C++17 requires direct construction.

Whereas

```
return temp;
```

returns a named local object.

The compiler **may** optimize it, but the language does not require it.

---

## Q5. If NRVO fails, what happens?

Compiler prefers

```
Move Constructor
```

If unavailable,

```
Copy Constructor
```

---

# Memory Visualization

## RVO

```
return MyCtr()

↓

Caller Object

Only ONE object exists.
```

---

## NRVO

Without optimization

```
temp

↓

Move

↓

Caller Object
```

With optimization

```
Caller Object

↑

temp
```

Same object.

---

# Quick Revision Table

| Situation | Constructor Called |
|-----------|-------------------|
| `A a(10);` | Parameterized |
| `A b = a;` | Copy |
| `A b = std::move(a);` | Move |
| `return A();` (C++17) | Parameterized only (Guaranteed RVO) |
| `return temp;` + NRVO | Parameterized only |
| `return temp;` without NRVO | Move (preferred) or Copy |
| `A a = fun();` (returns `A()`) | No Copy, No Move (C++17) |

---

# Interview Memory Trick

```
Copy Elision
│
├── RVO
│      │
│      ├── return MyCtr()
│      ├── Temporary (prvalue)
│      └── Guaranteed (C++17)
│
└── NRVO
       │
       ├── return temp
       ├── Named Local Variable
       └── Optional
```

---

# Golden Rule

```
return MyCtr(...)
        ↓
Guaranteed RVO
        ↓
No Copy
No Move

--------------------------------

return temp
        ↓
NRVO may happen
        ↓
If not
        ↓
Move
        ↓
Else Copy
```