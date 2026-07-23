# C++ `constexpr` (Complete Notes)

> `constexpr` was introduced in **C++11** and enhanced in **C++14**, **C++17**, and **C++20**.
>
> It tells the compiler:
>
> **"If possible, evaluate this expression at compile time."**

---

# Table of Contents

1. Why `constexpr`?
2. Compile Time vs Runtime
3. `constexpr` Variable
4. `const` vs `constexpr`
5. `constexpr` Function
6. Compile-time vs Runtime Evaluation
7. `constexpr` with Objects
8. `if constexpr` (C++17)
9. Real-world Uses
10. Interview Questions
11. Summary

---

# 1. Why `constexpr`?

Before C++11, if we wanted compile-time constants, we usually used:

```cpp
#define SIZE 100
```

or

```cpp
const int SIZE = 100;
```

### Problems with `#define`

- No type checking
- No scope
- Difficult to debug
- Pure text replacement

Example

```cpp
#define PI 3.14
```

The compiler simply replaces `PI` with `3.14`.

---

### Problems with `const`

```cpp
int x;

cin >> x;

const int SIZE = x;
```

This is valid.

But

```text
SIZE

↓

Known only at Runtime
```

It is **read-only**, but **not necessarily a compile-time constant**.

---

## Solution

C++11 introduced

```cpp
constexpr
```

Meaning

```text
Compile-Time Constant

↓

Compiler computes it

↓

Program runs faster
```

---

# 2. Compile Time vs Runtime

## Compile Time

Work performed while compiling the program.

```text
Source Code

↓

Compiler

↓

Executable
```

Example

```cpp
constexpr int x = 100;
```

Compiler already knows

```
100
```

before the program starts.

---

## Runtime

Work performed after the program starts.

```cpp
int x;

cin >> x;
```

Compiler doesn't know the value until the user enters it.

---

## Diagram

```text
Compile Time

Source Code
      ↓
Compiler
      ↓
Executable

-------------------------

Runtime

Executable
      ↓
User Input
      ↓
Program Executes
```

---

# 3. `constexpr` Variable

Example

```cpp
#include <iostream>
using namespace std;

constexpr int SIZE = 10;

int main()
{
    int arr[SIZE];

    cout << SIZE << endl;
}
```

Explanation

```text
SIZE

↓

Known during compilation

↓

Compiler allocates

int arr[10]
```

Benefits

- Faster
- Safer
- No runtime calculation

---

# 4. `const` vs `constexpr`

Example

```cpp
const int a = 10;

constexpr int b = 10;
```

Both are valid.

Difference

| const | constexpr |
|--------|------------|
| Read-only | Compile-time constant |
| May be runtime | Must be compile-time evaluable |
| Prevents modification | Enables compile-time optimization |

---

Example

```cpp
int n;

cin >> n;

const int x = n;
```

Valid.

Because

```text
x

↓

Read Only

↓

Value known at Runtime
```

---

Now

```cpp
constexpr int y = n;
```

Compiler Error

Reason

```text
n

↓

Unknown

↓

Cannot evaluate during compilation
```

---

# 5. `constexpr` Function

Without `constexpr`

```cpp
int square(int x)
{
    return x * x;
}
```

Every call executes at runtime.

---

With `constexpr`

```cpp
constexpr int square(int x)
{
    return x * x;
}
```

Usage

```cpp
constexpr int ans = square(5);

cout << ans;
```

Compiler computes

```text
square(5)

↓

25

↓

Embedded into executable
```

No runtime calculation.

---

# 6. Compile-Time vs Runtime Evaluation

Example

```cpp
constexpr int square(int x)
{
    return x * x;
}

int main()
{
    constexpr int a = square(10);

    int x = 5;

    int b = square(x);
}
```

Explanation

Compile-time

```text
square(10)

↓

Known

↓

Compiler computes
```

Runtime

```text
square(x)

↓

x not known

↓

Normal function call
```

A `constexpr` function **can execute either at compile time or at runtime**, depending on whether its arguments are compile-time constants.

---

# 7. Using `constexpr` for Array Size

Example

```cpp
constexpr int getSize()
{
    return 20;
}

int arr[getSize()];
```

Compiler changes it to

```cpp
int arr[20];
```

---

# 8. `constexpr` Objects

Example

```cpp
class Point
{
public:

    int x;

    constexpr Point(int value)
        : x(value)
    {
    }
};

constexpr Point p(100);
```

Explanation

```text
Object

↓

Created During Compilation

↓

No Runtime Cost
```

---

# 9. `if constexpr` (C++17)

Before C++17

```cpp
template<typename T>
void print(T value)
{
    if(is_integral_v<T>)
        cout << "Integer";
    else
        cout << "Other";
}
```

Problem

Both branches must compile.

---

C++17

```cpp
template<typename T>
void print(T value)
{
    if constexpr(is_integral_v<T>)
        cout << "Integer";
    else
        cout << "Other";
}
```

Explanation

Compiler removes the unused branch.

Diagram

```text
if constexpr

↓

Condition Known

↓

Unused Branch Removed

↓

Smaller Faster Code
```

---

# 10. Real-World Uses

## Fixed Buffer Size

```cpp
constexpr int BUFFER_SIZE = 1024;
```

---

## Mathematical Constants

```cpp
constexpr double PI = 3.141592653589;
```

---

## Compile-Time Calculations

```cpp
constexpr int cube(int x)
{
    return x * x * x;
}
```

---

## Template Parameters

```cpp
template<int Size>
class Buffer
{
};

Buffer<20> b;
```

---

## Switch Statements

```cpp
constexpr int START = 1;

switch(choice)
{
case START:
    break;
}
```

---

## Compile-Time Objects

```cpp
constexpr Point origin(0);
```

---

# 11. C++14 Improvements

C++11 `constexpr` functions were very limited.

Example

```cpp
constexpr int factorial(int n)
{
    int result = 1;

    for(int i = 1; i <= n; i++)
        result *= i;

    return result;
}
```

This became possible starting with **C++14**, which allows loops, local variables, and more complex logic inside `constexpr` functions.

---

# 12. Interview Questions

## Q1. Is every `const` variable `constexpr`?

No.

```cpp
int n;

cin >> n;

const int x = n;
```

Valid.

```cpp
constexpr int y = n;
```

Compilation Error.

---

## Q2. Can a `constexpr` function execute at runtime?

Yes.

```cpp
constexpr int add(int a, int b)
{
    return a + b;
}

int x;

cin >> x;

cout << add(x, 5);
```

Since `x` is only known at runtime, the function executes like a normal function.

---

## Q3. Can `constexpr` functions contain loops?

- **C++11:** Very limited support.
- **C++14 and later:** Yes.

Example

```cpp
constexpr int sum(int n)
{
    int total = 0;

    for(int i = 1; i <= n; i++)
        total += i;

    return total;
}
```

---

## Q4. Is `constexpr` always evaluated at compile time?

No.

Example

```cpp
constexpr int square(int x)
{
    return x * x;
}

int value;

cin >> value;

cout << square(value);
```

Since `value` is known only at runtime, the function executes at runtime.

---

## Q5. Difference between `const` and `constexpr`?

```text
const

↓

Cannot Modify

-------------------------

constexpr

↓

Compile-Time Constant

(if possible)
```

---

# Summary Table

| Feature | Purpose |
|---------|---------|
| `constexpr` variable | Compile-time constant |
| `constexpr` function | Compile-time computation when possible |
| `constexpr` object | Compile-time object creation |
| `if constexpr` | Compile-time branching (C++17) |

---

# Memory Trick

```text
constexpr
      │
      ▼
Known at Compile Time
      │
      ├── Variables
      ├── Functions
      ├── Objects
      └── if constexpr

Benefits
      │
      ▼
✓ Faster execution
✓ Compile-time validation
✓ Better optimization
✓ Type-safe constants
```

---

# Key Takeaways

- `const` means **the value cannot be modified**.
- `constexpr` means **the compiler can evaluate it during compilation** (if possible).
- A `constexpr` function is **not forced** to execute at compile time. It runs at compile time only when all its inputs are compile-time constants; otherwise, it behaves like a normal function.
- `if constexpr` (introduced in C++17) enables compile-time branching by removing the unused branch during compilation.