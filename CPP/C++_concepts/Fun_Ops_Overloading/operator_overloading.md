# C++ Operator Overloading Cheat Sheet (Interview Notes)

---

# What is Operator Overloading?

Operator overloading allows **user-defined classes** to behave like built-in types.

Example:

```cpp
A a(10), b(20);

A c = a + b;
```

Internally,

```cpp
a + b;
```

becomes

```cpp
a.operator+(b);
```

or (friend function)

```cpp
operator+(a, b);
```

---

# How to Decide the Return Type?

Ask yourself:

```
Does this operator create a NEW object?
        │
       YES
        │
Return by Value

-----------------------

Does this operator MODIFY the current object?
        │
       YES
        │
Return *this (A&)

-----------------------

Does it COMPARE?
        │
       YES
        │
Return bool

-----------------------

Does it ACCESS an element?
        │
       YES
        │
Return Reference (T&)

-----------------------

Is it STREAM operator?
        │
       YES
        │
Return ostream& / istream&
```

---

# Rule 1 : Operators Creating New Objects

Return **by value**.

Examples:

-  '+'
-  '-'
-  '*'
-  '/'
-  %
-  unary -

```cpp
class A
{
    int x;

public:

    A(int val = 0) : x(val) {}

    A operator+(const A& rhs) const
    {
        return A(x + rhs.x);
    }
};
```

Usage

```cpp
A a(10), b(20);

A c = a + b;
```

Internally

```cpp
A c = a.operator+(b);
```

---

# Rule 2 : Operators Modifying Current Object

Return

```cpp
A&
```

because we return the current object.

Examples

- =
- +=
- -=
- *=
- /=
- %=

Example

```cpp
A& operator+=(const A& rhs)
{
    x += rhs.x;

    return *this;
}
```

Allows

```cpp
a += b += c;
```

---

# Rule 3 : Comparison Operators

Return

```cpp
bool
```

Examples

```cpp
==

!=

<

>

<=

>=
```

Example

```cpp
bool operator==(const A& rhs) const
{
    return x == rhs.x;
}
```

Usage

```cpp
if(a == b)
{
}
```

---

# Rule 4 : Index Operator []

Should return a reference.

```cpp
int& operator[](int index)
{
    return arr[index];
}
```

Usage

```cpp
obj[2] = 100;
```

If it returned

```cpp
int
```

then

```cpp
obj[2] = 100;
```

would modify only a temporary.

For read-only objects

```cpp
const int& operator[](int index) const;
```

---

# Rule 5 : Assignment Operator (=)

Always return

```cpp
A&
```

Example

```cpp
A& operator=(const A& rhs)
{
    if(this != &rhs)
    {
        x = rhs.x;
    }

    return *this;
}
```

Allows

```cpp
a = b = c;
```

Internally

```
b = c

returns b

↓

a = b
```

---

# Rule 6 : Prefix Increment

Return

```cpp
A&
```

because object is modified first.

```cpp
A& operator++()
{
    ++x;

    return *this;
}
```

Usage

```cpp
++a;
```

---

# Rule 7 : Postfix Increment

Return

```cpp
A
```

(old value)

Dummy int differentiates postfix.

```cpp
A operator++(int)
{
    A temp = *this;

    x++;

    return temp;
}
```

Usage

```cpp
a++;
```

Flow

```
Copy old object

↓

Increment current object

↓

Return old copy
```

---

# Rule 8 : Stream Insertion (<<)

Returns

```cpp
ostream&
```

Why?

Because we want chaining.

```cpp
cout << a << b << c;
```

Example

```cpp
#include <iostream>
using namespace std;

class A
{
    int x;

public:

    A(int val = 0) : x(val) {}

    friend ostream& operator<<(ostream& out, const A& obj);
};

ostream& operator<<(ostream& out, const A& obj)
{
    out << obj.x;

    return out;
}
```

Usage

```cpp
A a(100);

cout << a;
```

Internally

```cpp
operator<<(cout, a);
```

For chaining

```cpp
cout << a << b;
```

becomes

```cpp
operator<<(operator<<(cout, a), b);
```

This is why we must return

```cpp
ostream&
```

---

# Rule 9 : Stream Extraction (>>)

Returns

```cpp
istream&
```

Again,

for chaining.

```cpp
cin >> a >> b;
```

Example

```cpp
#include <iostream>
using namespace std;

class A
{
    int x;

public:

    friend istream& operator>>(istream& in, A& obj);
};

istream& operator>>(istream& in, A& obj)
{
    in >> obj.x;

    return in;
}
```

Usage

```cpp
A a;

cin >> a;
```

Internally

```cpp
operator>>(cin, a);
```

Chaining

```cpp
cin >> a >> b;
```

becomes

```cpp
operator>>(operator>>(cin, a), b);
```

Hence,

return

```cpp
istream&
```

---

# Complete Return Type Table

| Operator | Return Type | Reason |
|----------|-------------|--------|
| + | A | Creates new object |
| - | A | Creates new object |
| * | A | Creates new object |
| / | A | Creates new object |
| % | A | Creates new object |
| = | A& | Return current object |
| += | A& | Modify current object |
| -= | A& | Modify current object |
| *= | A& | Modify current object |
| /= | A& | Modify current object |
| == | bool | Comparison |
| != | bool | Comparison |
| < | bool | Comparison |
| > | bool | Comparison |
| <= | bool | Comparison |
| >= | bool | Comparison |
| [] | T& | Access element |
| Prefix ++ | A& | Return modified object |
| Postfix ++ | A | Return old object |
| Prefix -- | A& | Return modified object |
| Postfix -- | A | Return old object |
| << | ostream& | Stream chaining |
| >> | istream& | Stream chaining |

---

# Most Common Operator Signatures

```cpp
// Arithmetic
A operator+(const A&) const;
A operator-(const A&) const;
A operator*(const A&) const;
A operator/(const A&) const;

// Assignment
A& operator=(const A&);

// Compound Assignment
A& operator+=(const A&);
A& operator-=(const A&);
A& operator*=(const A&);
A& operator/=(const A&);

// Comparison
bool operator==(const A&) const;
bool operator!=(const A&) const;
bool operator<(const A&) const;
bool operator>(const A&) const;

// Indexing
T& operator[](size_t);
const T& operator[](size_t) const;

// Increment / Decrement
A& operator++();      // Prefix
A operator++(int);    // Postfix

A& operator--();      // Prefix
A operator--(int);    // Postfix

// Stream Operators
friend ostream& operator<<(ostream&, const A&);
friend istream& operator>>(istream&, A&);
```

---

# Interview Memory Trick

```
Creates New Object
        ↓
Return by Value

Modifies Current Object
        ↓
Return *this (A&)

Compares
        ↓
Return bool

Accesses Data
        ↓
Return Reference

Streams
        ↓
Return ostream& / istream&
```

---

# One-Line Summary

| Operator Type | Return |
|--------------|--------|
| Arithmetic (`+`, `-`, `*`, `/`) | `A` |
| Assignment (`=`, `+=`, `-=`) | `A&` |
| Comparison (`==`, `<`, `>`) | `bool` |
| Index (`[]`) | `T&` |
| Prefix (`++a`, `--a`) | `A&` |
| Postfix (`a++`, `a--`) | `A` |
| Output (`<<`) | `ostream&` |
| Input (`>>`) | `istream&` |

> **Golden Rule:** Return the type that best matches the operator's behavior. If it creates a new value, return a new object. If it modifies the current object, return `*this`. If it compares, return `bool`. If it supports chaining (like streams or assignment), return a reference.