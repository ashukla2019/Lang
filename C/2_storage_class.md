# Chapter 9 – Storage Classes
# Part 1 – Fundamentals of Storage Classes

---

# Contents

1. What are Storage Classes?
2. Why are Storage Classes Needed?
3. Scope, Lifetime and Linkage
4. Types of Storage Classes
5. auto Storage Class
6. register Storage Class
7. static Storage Class
8. extern Storage Class
9. Comparison Table
10. Interview Questions
11. Key Takeaways

---

# 1. What are Storage Classes?

Every variable in C has several properties besides its data type.

For example,

```c
int x;
```

The compiler needs to know:

- Where should `x` be stored?
- Who can access it?
- When is it created?
- When is it destroyed?
- Can another source file access it?

These properties are determined by the **Storage Class**.

A storage class specifies:

- Storage location
- Scope (Visibility)
- Lifetime (Existence)
- Linkage (Accessibility across source files)

---

# 2. Why are Storage Classes Needed?

Consider the following program.

```c
void fun()
{
    int count = 0;

    count++;

    printf("%d\n", count);
}
```

Calling

```c
fun();
fun();
fun();
```

Output

```
1
1
1
```

Why?

Because

```
count
```

is created every time the function is called.

Now change it to

```c
static int count = 0;
```

Output

```
1
2
3
```

The storage class changes the variable's lifetime.

---

# 3. Scope, Lifetime and Linkage

Before studying storage classes, understand these three terms.

Many interviewers ask them directly.

---

# Scope

Scope defines **where a variable can be accessed**.

Example

```c
void fun()
{
    int x = 10;

    printf("%d", x);
}
```

Valid

```c
printf("%d", x);
```

inside the function.

Invalid

```c
int main()
{
    printf("%d", x);
}
```

because `x` is outside its scope.

---

## Types of Scope

### Block Scope

Variables declared inside

```c
{}
```

are visible only inside that block.

Example

```c
int main()
{
    {
        int x = 10;
    }

    printf("%d", x);      // Error
}
```

---

### File Scope

Variables declared outside every function.

Example

```c
int x = 100;

int main()
{
    printf("%d", x);
}
```

Visible from the declaration to the end of the source file (subject to linkage).

---

# Lifetime

Lifetime defines **how long the variable exists in memory**.

Example

```c
void fun()
{
    int x = 5;
}
```

Memory is allocated

```
Function starts
```

Memory is released

```
Function ends
```

---

Static variable

```c
static int x = 5;
```

Memory

```
Program starts

↓

Program ends
```

---

# Linkage

Linkage determines whether an identifier can be referred to from another source file.

There are three types.

### No Linkage

Local variables.

Example

```c
void fun()
{
    int x;
}
```

Cannot be accessed outside the block.

---

### Internal Linkage

Visible only inside the current source file.

Created using

```c
static
```

for global variables.

---

### External Linkage

Accessible from multiple source files.

Created using

```c
extern
```

or by defining a global variable without `static`.

---

# Summary

| Property | Meaning |
|-----------|---------|
| Scope | Where can it be accessed? |
| Lifetime | How long does it exist? |
| Linkage | Can another source file access it? |

---

# 4. Types of Storage Classes

C provides four storage classes.

| Storage Class | Keyword |
|---------------|---------|
| Automatic | auto |
| Register | register |
| Static | static |
| External | extern |

---

# 5. auto Storage Class

This is the default storage class for local variables.

Example

```c
void fun()
{
    auto int x = 10;
}
```

is exactly the same as

```c
void fun()
{
    int x = 10;
}
```

The compiler automatically assumes

```
auto
```

---

## Properties

| Property | Value |
|----------|-------|
| Scope | Block |
| Lifetime | Function Call |
| Storage | Stack |
| Initial Value | Garbage (indeterminate if not initialized) |
| Linkage | None |

---

## Example

```c
#include <stdio.h>

void fun()
{
    auto int x = 1;

    printf("%d\n", x);
}

int main()
{
    fun();
    fun();
}
```

Output

```
1
1
```

Each function call creates a new variable.

---

## Memory Diagram

```
Function Call

↓

Stack

+---------+

x = 1

+---------+

↓

Function Ends

↓

Memory Removed
```

---

# 6. register Storage Class

`register` suggests that the compiler keep the variable in a CPU register for faster access.

Example

```c
register int i;
```

Modern compilers decide automatically whether to use a register, so this keyword is only a hint and may be ignored.

---

## Properties

| Property | Value |
|----------|-------|
| Scope | Block |
| Lifetime | Function Call |
| Storage | CPU Register (if possible) |
| Linkage | None |

---

## Example

```c
void sum()
{
    register int i;

    for(i = 0; i < 1000; i++)
    {
    }
}
```

---

## Why Use register?

Frequently used variables.

Examples

- Loop counters
- Small calculations
- Temporary values

Today, compiler optimizations generally make explicit `register` unnecessary.

---

## Limitation

You cannot apply the address-of operator to a register variable.

```c
register int x = 10;

int *p = &x;      // Error
```

Reason

A register variable may not have a memory location that the program can take the address of.

---

# 7. static Storage Class

One of the most important interview topics.

`static` behaves differently depending on where it is used.

There are three common cases:

- Static local variable
- Static global variable
- Static function

We cover the first two in this part.

---

# Static Local Variable

Example

```c
void fun()
{
    static int count = 0;

    count++;

    printf("%d\n", count);
}
```

Calling

```c
fun();
fun();
fun();
```

Output

```
1
2
3
```

---

## Why?

Memory is allocated only once.

```
Program Starts

↓

Memory Allocated

↓

Function Called

↓

Value Updated

↓

Function Ends

↓

Memory Retained

↓

Next Call Uses Same Variable

↓

Program Ends

↓

Memory Released
```

---

## Properties

| Property | Value |
|----------|-------|
| Scope | Block |
| Lifetime | Entire Program |
| Storage | Data/BSS Segment |
| Linkage | None |

---

## Memory Diagram

```
Data Segment

+-----------+

count = 0

+-----------+

↓

Call 1

count = 1

↓

Call 2

count = 2

↓

Call 3

count = 3
```

---

# Static Global Variable

Example

```c
static int counter = 100;
```

This variable is visible only inside the current source file.

Other files cannot access it.

---

## Properties

| Property | Value |
|----------|-------|
| Scope | File |
| Lifetime | Entire Program |
| Linkage | Internal |

---

# Why Use Static Globals?

To hide implementation details.

Example

```
driver.c

↓

static int deviceState;
```

Only code inside

```
driver.c
```

can access `deviceState`.

This is a common pattern in embedded software and Linux kernel code.

---

# 8. extern Storage Class

`extern` is used to access a global variable defined in another source file.

---

## Example

### file1.c

```c
int counter = 100;
```

---

### file2.c

```c
extern int counter;

void printCounter()
{
    printf("%d\n", counter);
}
```

The variable is defined only once, but can be used in multiple files.

---

## Properties

| Property | Value |
|----------|-------|
| Scope | File |
| Lifetime | Entire Program |
| Linkage | External |

---

## Definition vs Declaration

Definition

```c
int x = 10;
```

Creates storage.

---

Declaration

```c
extern int x;
```

Does **not** create storage.

It tells the compiler that the variable exists elsewhere.

---

# Memory Summary

```
Stack

↓

auto

register

---------------------

Data Segment

↓

Initialized static

Initialized global

---------------------

BSS

↓

Uninitialized static

Uninitialized global

---------------------

Text

↓

Functions
```

---

# Comparison Table

| Feature | auto | register | static (local) | static (global) | extern |
|----------|------|----------|----------------|-----------------|--------|
| Scope | Block | Block | Block | File | File |
| Lifetime | Function call | Function call | Entire Program | Entire Program | Entire Program |
| Linkage | None | None | None | Internal | External |
| Default Value | Garbage | Garbage | 0 | 0 | Defined elsewhere |
| Storage | Stack | Register/Stack | Data/BSS | Data/BSS | Data/BSS |

---

# Frequently Asked Interview Questions

### Q1. What are storage classes?

Storage classes define a variable's **scope, lifetime, storage location, and linkage**.

---

### Q2. What is the default storage class of a local variable?

```
auto
```

---

### Q3. Why is `register` rarely used today?

Modern compilers perform register allocation automatically and usually make better decisions than manual hints.

---

### Q4. Difference between `static` and `extern`?

`static` (global)

- Internal linkage
- Visible only within the current source file

`extern`

- External linkage
- Refers to a variable defined in another source file

---

### Q5. Difference between a static local variable and a normal local variable?

Normal local variable

- Created on each function call
- Destroyed when the function returns

Static local variable

- Created once
- Retains its value across function calls

---

### Q6. Where are static variables stored?

In the **Data Segment** (initialized) or **BSS Segment** (uninitialized), not on the stack.

---

### Q7. What is the difference between declaration and definition?

A **declaration** tells the compiler that a variable or function exists.

A **definition** allocates storage (for variables) or provides the implementation (for functions).

---

# Key Takeaways

- Storage classes determine **scope, lifetime, storage location, and linkage**.
- `auto` is the default for local variables.
- `register` is a compiler hint and is rarely needed with modern optimizers.
- `static` local variables preserve their values between function calls.
- `static` global variables provide **internal linkage**, making them visible only within the current source file.
- `extern` allows access to global variables defined in other source files and provides **external linkage**.
- Understanding **scope**, **lifetime**, and **linkage** is essential for C interviews and for writing modular, maintainable programs.
-----------------------------------------------------------------------------------
# Chapter 9 – Storage Classes
# Part 2 – Scope, Linkage & Multi-File Programming (Interview Deep Dive)

---

# Contents

1. Scope vs Lifetime vs Linkage
2. Block Scope
3. Function Scope
4. File Scope
5. Linkage
6. Internal Linkage
7. External Linkage
8. No Linkage
9. static Functions
10. Multiple Source Files
11. extern with Functions
12. Global Variables
13. Common Interview Questions
14. Best Practices
15. Key Takeaways

---

# 1. Scope vs Lifetime vs Linkage

These three terms are one of the most frequently asked interview topics.

Many candidates confuse them.

Think of them as answering three different questions.

| Property | Question |
|----------|----------|
| Scope | Where can I access it? |
| Lifetime | How long does it exist? |
| Linkage | Can another source file access it? |

Example

```c
void fun()
{
    int x = 10;
}
```

Here

```
Scope

↓

Inside fun()
```

```
Lifetime

↓

Only during function execution
```

```
Linkage

↓

None
```

---

# 2. Block Scope

Variables declared inside

```
{}
```

have block scope.

Example

```c
int main()
{
    int a = 10;

    {
        int b = 20;

        printf("%d\n", b);
    }

    printf("%d\n", a);
}
```

Output

```
20
10
```

Trying to access

```c
b
```

outside the block

```c
printf("%d", b);
```

Compiler Error

---

## Nested Blocks

```c
int main()
{
    int x = 5;

    {
        int y = 10;

        {
            int z = 15;
        }
    }
}
```

Visibility

```
Outer Block

↓

x

↓

Inner Block

↓

x
y

↓

Innermost Block

↓

x
y
z
```

Variables from outer blocks are visible in inner blocks.

Reverse is NOT true.

---

# Variable Shadowing

```c
int x = 10;

int main()
{
    int x = 20;

    printf("%d", x);
}
```

Output

```
20
```

The local variable hides the global variable.

---

Example

```c
int value = 100;

void fun()
{
    int value = 50;

    printf("%d\n", value);
}

int main()
{
    printf("%d\n", value);

    fun();
}
```

Output

```
100
50
```

---

# 3. Function Scope

Only labels have function scope.

Example

```c
void fun()
{
start:

    printf("Hello");

    goto start;
}
```

The label

```
start
```

is visible everywhere inside that function.

It cannot be accessed from another function.

---

# 4. File Scope

Variables declared outside every function have file scope.

Example

```c
int count = 100;

void fun()
{
}

int main()
{
}
```

The variable

```
count
```

can be used anywhere below its declaration in the same source file.

---

# 5. Linkage

Linkage determines whether an identifier can be shared across multiple source files.

There are three types.

```
No Linkage

Internal Linkage

External Linkage
```

---

# 6. No Linkage

Local variables have no linkage.

Example

```c
void fun()
{
    int x = 5;
}
```

Another function cannot access

```
x
```

---

# 7. Internal Linkage

Created using

```c
static
```

at file scope.

Example

```c
static int deviceState = 0;
```

Only

```
device.c
```

can access it.

Another source file

```
main.c
```

cannot use it.

---

Memory

```
device.c

↓

deviceState
```

Visible only inside

```
device.c
```

---

# Internal Linkage Example

## driver.c

```c
static int counter = 0;

void increment()
{
    counter++;
}
```

---

## main.c

```c
extern int counter;

int main()
{
    printf("%d", counter);
}
```

Compilation

```
Undefined Reference

Linker Error
```

Because

```
counter
```

has internal linkage.

---

# 8. External Linkage

Default for global variables.

Example

## file1.c

```c
int counter = 10;
```

---

## file2.c

```c
extern int counter;

void printCounter()
{
    printf("%d", counter);
}
```

Output

```
10
```

---

Memory

```
counter

↓

Shared by

file1.c

file2.c
```

---

# 9. static Functions

Many people know about static variables.

Fewer know about static functions.

Example

```c
static void helper()
{
    printf("Helper");
}
```

Only this source file can call

```
helper()
```

---

Why?

It hides implementation details.

Example

```
uart.c

↓

static parsePacket()

↓

static checksum()

↓

uart_send()
```

Only

```
uart_send()
```

is exposed.

Everything else remains private.

This is similar to **private helper functions** in other languages.

---

# 10. Multiple Source Files

Suppose

```
Project

↓

main.c

driver.c

driver.h
```

---

driver.h

```c
void driverInit(void);
```

---

driver.c

```c
#include "driver.h"

void driverInit()
{
}
```

---

main.c

```c
#include "driver.h"

int main()
{
    driverInit();
}
```

Header files contain declarations.

Source files contain definitions.

---

# 11. extern with Functions

Functions are

by default

```
extern
```

Example

```c
void fun()
{
}
```

is equivalent to

```c
extern void fun()
{
}
```

Therefore

```c
extern void fun();
```

is usually unnecessary in header files.

---

# 12. Global Variables

Global variables should be minimized.

Bad

```c
int temperature;

int pressure;

int speed;

int state;

int error;
```

Every file can modify them.

Difficult to debug.

---

Better

```c
static int state;
```

Provide access through functions.

```c
void setState(int s)
{
    state = s;
}

int getState()
{
    return state;
}
```

Encapsulation improves maintainability.

---

# Lifetime of Globals

Global variables

```
Program Starts

↓

Memory Allocated

↓

Remain Alive

↓

Program Ends

↓

Memory Released
```

Regardless of whether they are accessed.

---

# 13. Frequently Asked Interview Questions

## Q1. Difference between scope and linkage?

Scope

```
Visibility
```

Linkage

```
Can another source file access it?
```

---

## Q2. Difference between file scope and block scope?

Block Scope

```
Visible only inside {}
```

File Scope

```
Visible throughout the source file
```

---

## Q3. Difference between static local and static global?

Static Local

```
Block Scope

Program Lifetime

No Linkage
```

Static Global

```
File Scope

Program Lifetime

Internal Linkage
```

---

## Q4. Difference between global and extern?

Global Variable

```c
int count;
```

Creates storage.

---

Extern Variable

```c
extern int count;
```

Creates NO storage.

Only declares that storage exists elsewhere.

---

## Q5. Why make helper functions static?

To prevent accidental use from other source files and avoid namespace pollution.

---

## Q6. Can two files have static variables with the same name?

Yes.

Example

```
file1.c

↓

static int count;
```

```
file2.c

↓

static int count;
```

Both are completely independent because each has internal linkage.

---

## Q7. What happens if two source files define the same global variable?

Example

file1.c

```c
int counter;
```

file2.c

```c
int counter;
```

Result

```
Multiple Definition

Linker Error
```

Only one definition should exist.

Other files should use

```c
extern int counter;
```

---

# 14. Best Practices

✓ Prefer local variables over global variables.

✓ Use `static` for helper functions that should not be visible outside the file.

✓ Use `static` globals to hide module implementation details.

✓ Avoid exposing writable global variables.

✓ Share data across files using `extern` only when necessary.

✓ Place declarations in header files and definitions in source files.

✓ Keep global state minimal to improve modularity and testability.

---

# Key Takeaways

- **Scope** determines where an identifier is visible.
- **Lifetime** determines how long it exists in memory.
- **Linkage** determines whether it can be shared across source files.
- Local variables have **block scope** and **no linkage**.
- Global variables have **file scope** and, by default, **external linkage**.
- `static` at file scope gives **internal linkage**, restricting visibility to one source file.
- `static` functions are private to their source file and are commonly used for helper routines.
- `extern` declares identifiers defined in another translation unit without allocating storage.
- Understanding how declarations, definitions, scope, lifetime, and linkage interact is essential for writing modular C programs and for succeeding in systems programming interviews.
- -----------------------------------------------------------------
# Chapter 9 – Storage Classes
# Part 3 – Memory Layout, Initialization & Advanced Interview Concepts

---

# Contents

1. Variable Initialization
2. Where Variables are Stored
3. Stack vs Data vs BSS
4. Static Initialization Rules
5. extern and Initialization
6. Tentative Definitions
7. Declaration vs Definition
8. Common Linker Errors
9. Storage Classes and Recursion
10. Storage Classes and Threads
11. Storage Classes Summary
12. Interview Questions
13. Key Takeaways

---

# 1. Variable Initialization

One of the most common interview questions is:

> Which variables are initialized automatically?

The answer depends on the storage class.

| Variable Type | Default Value |
|--------------|---------------|
| Local (auto) | Garbage (Indeterminate) |
| register | Garbage (Indeterminate) |
| static | 0 |
| Global | 0 |

Example

```c
void fun()
{
    int x;

    printf("%d\n", x);
}
```

Output

```
Garbage value (Undefined Behavior if read)
```

---

Example

```c
static int x;

printf("%d", x);
```

Output

```
0
```

because static variables are automatically initialized.

---

# 2. Where Variables are Stored

Consider

```c
int global = 100;

static int staticGlobal = 50;

int main()
{
    int local = 10;

    static int counter = 0;

    char *p = malloc(100);
}
```

Memory Layout

```
+----------------------+
|      Stack           |
|----------------------|
| local                |
+----------------------+

+----------------------+
|      Heap            |
|----------------------|
| malloc(100)          |
+----------------------+

+----------------------+
| Data Segment         |
|----------------------|
| global               |
| staticGlobal         |
| counter              |
+----------------------+

+----------------------+
| Text Segment         |
|----------------------|
| main()               |
+----------------------+
```

---

# 3. Data Segment vs BSS

The compiler divides global/static variables into two sections.

---

## Data Segment

Initialized globals/statics.

Example

```c
int x = 10;

static int y = 20;
```

Stored in

```
Data Segment
```

---

## BSS Segment

Uninitialized globals/statics.

Example

```c
int count;

static int total;
```

Stored in

```
BSS
```

Both become

```
0
```

before

```
main()
```

starts.

---

Memory Layout

```
Text

↓

Initialized Data

↓

BSS

↓

Heap

↓

Stack
```

---

# 4. Static Initialization Rules

Only **constant expressions** can initialize static/global variables.

Correct

```c
static int x = 100;
```

Correct

```c
static int y = 10 + 20;
```

Wrong

```c
int fun();

static int z = fun();
```

Compiler Error

Reason

Static initialization happens **before program execution**, so function calls are not allowed.

---

# 5. extern and Initialization

Correct

```c
/* file1.c */

int counter = 100;
```

```c
/* file2.c */

extern int counter;
```

---

Wrong

```c
extern int counter = 100;
```

This is **actually a definition**, not just a declaration.

If another file also defines

```c
int counter = 100;
```

the linker reports

```
Multiple Definition Error
```

---

# 6. Tentative Definitions

One of the most misunderstood C topics.

Example

```c
int x;
```

Is this a declaration or a definition?

Answer

It is a **tentative definition**.

If no other definition exists,

```c
int x;
```

becomes

```c
int x = 0;
```

---

Example

```c
int x;

int main()
{
}
```

Compiler behaves as if

```c
int x = 0;
```

exists.

---

Example

```c
int x;

int x = 20;
```

Valid.

The second line is the actual definition.

---

# 7. Declaration vs Definition

Very common interview question.

---

Declaration

Introduces a name.

No storage allocated.

Example

```c
extern int count;
```

---

Definition

Creates storage.

Example

```c
int count = 0;
```

---

Functions

Declaration

```c
void fun();
```

Definition

```c
void fun()
{
}
```

---

Summary

| Statement | Declaration | Definition |
|-----------|-------------|------------|
| `extern int x;` | Yes | No |
| `int x;` | Yes | Tentative Definition |
| `int x = 10;` | Yes | Yes |
| `void fun();` | Yes | No |
| `void fun(){}` | Yes | Yes |

---

# 8. Common Linker Errors

---

## Multiple Definition

file1.c

```c
int count = 10;
```

file2.c

```c
int count = 20;
```

Result

```
Multiple definition of count
```

---

## Undefined Reference

file1.c

```c
extern int count;
```

No source file defines

```c
count
```

Result

```
Undefined reference to count
```

---

## Static Visibility

file1.c

```c
static int count = 10;
```

file2.c

```c
extern int count;
```

Result

```
Undefined reference
```

because

```
count
```

is hidden inside

```
file1.c
```

---

# 9. Storage Classes and Recursion

Normal Local Variable

```c
void fun()
{
    int x = 0;

    x++;

    printf("%d\n", x);

    fun();
}
```

Every recursive call gets a **new copy** of `x`.

---

Static Local Variable

```c
void fun()
{
    static int x = 0;

    x++;

    printf("%d\n", x);

    fun();
}
```

Output

```
1
2
3
4
5
...
```

All recursive calls share the same variable.

---

Memory

```
Recursive Calls

↓

Same static variable
```

---

# 10. Storage Classes and Threads

Suppose

```c
static int counter = 0;
```

Two threads execute

```c
counter++;
```

Problem

Both threads access the same variable.

Possible Result

```
Race Condition
```

Static **does not** provide thread safety.

Synchronization such as a mutex or atomic operations is still required.

---

# 11. Storage Classes Summary

| Feature | auto | register | static Local | static Global | extern |
|---------|------|----------|--------------|---------------|--------|
| Scope | Block | Block | Block | File | File |
| Lifetime | Function | Function | Entire Program | Entire Program | Entire Program |
| Linkage | None | None | None | Internal | External |
| Default Value | Garbage | Garbage | 0 | 0 | Defined Elsewhere |
| Storage | Stack | Register/Stack | Data/BSS | Data/BSS | Data/BSS |

---

# Memory Summary

```
                Program Memory

+------------------------------+
| Text Segment                 |
|------------------------------|
| Functions                    |
+------------------------------+

+------------------------------+
| Initialized Data             |
|------------------------------|
| Global = 10                  |
| static = 20                  |
+------------------------------+

+------------------------------+
| BSS                          |
|------------------------------|
| Global                       |
| static                       |
+------------------------------+

+------------------------------+
| Heap                         |
|------------------------------|
| malloc(), calloc()           |
+------------------------------+

+------------------------------+
| Stack                        |
|------------------------------|
| auto                         |
| register                     |
| Function Frames              |
+------------------------------+
```

---

# Frequently Asked Interview Questions

### Q1. Why are static variables initialized only once?

Memory is allocated before `main()` starts and remains allocated until the program exits.

---

### Q2. Can a static variable be initialized using a function call?

No.

Only constant expressions are allowed for static and global initialization.

---

### Q3. What is a tentative definition?

A declaration like

```c
int x;
```

that becomes a definition if no other definition exists in the translation unit.

---

### Q4. Why does `extern` not allocate memory?

`extern` only informs the compiler that the object is defined elsewhere.

---

### Q5. Can static variables cause race conditions?

Yes.

`static` controls **lifetime and linkage**, not synchronization.

---

### Q6. Where are global variables stored?

- Initialized globals → Data Segment
- Uninitialized globals → BSS Segment

---

### Q7. Why are automatic variables not initialized?

Automatically initializing every local variable would incur runtime overhead. The language leaves them indeterminate unless explicitly initialized.

---

### Q8. Is `register` guaranteed to place a variable in a CPU register?

No.

It is only a compiler hint. Modern optimizing compilers decide the best storage location.

---

# Best Practices

✓ Initialize local variables before use.

✓ Minimize global variables.

✓ Use `static` to hide implementation details.

✓ Use `extern` only for shared interfaces.

✓ Prefer passing data through function parameters rather than global state.

✓ Keep one definition of every global variable.

✓ Declare shared globals in a header using `extern` and define them in exactly one source file.

---

# Key Takeaways

- Automatic (`auto`) and `register` variables have automatic storage duration and are not automatically initialized.
- Global and `static` variables have static storage duration and are zero-initialized if no explicit initializer is provided.
- Initialized globals/statics are stored in the **Data Segment**; uninitialized ones are stored in the **BSS**.
- `extern` declares an object or function defined elsewhere and does not allocate storage.
- A tentative definition (`int x;`) becomes the definition if no other definition exists.
- `static` affects visibility and lifetime, but **does not provide thread safety**.
- Understanding declarations, definitions, memory layout, and linker behavior is essential for debugging multi-file C projects and for systems programming interviews.

---

# Next Part

**Part 4 – 70+ Storage Class Interview Questions & Coding Problems**
---------------------------------------------------------------
# Chapter 9 – Storage Classes
# Part 4 – 70+ Storage Class Interview Questions & Coding Problems

---

# Contents

1. Conceptual Interview Questions
2. Predict the Output Questions
3. Multi-file Programming Questions
4. Memory Layout Questions
5. Coding Problems
6. Common Mistakes
7. Company-Specific Questions
8. Key Takeaways

---

# 1. Conceptual Interview Questions

## Q1. What is a storage class?

**Answer**

A storage class specifies:

- Storage duration (lifetime)
- Scope
- Linkage
- Storage location (conceptually)

---

## Q2. How many storage classes are there?

There are four storage class specifiers commonly used in C:

- auto
- register
- static
- extern

(C11 also introduces `_Thread_local`, which we'll cover later.)

---

## Q3. What is the default storage class of a local variable?

```c
auto
```

---

## Q4. What is the default storage class of a global variable?

Global variables have:

- Static storage duration
- External linkage (unless declared `static`)

---

## Q5. What is the lifetime of

```c
auto
```

variables?

Only during function execution.

---

## Q6. What is the lifetime of

```c
static
```

variables?

Entire program execution.

---

## Q7. What is the difference between scope and lifetime?

Scope

```
Where variable is visible.
```

Lifetime

```
How long memory exists.
```

---

## Q8. What is linkage?

Whether the identifier can be referred to from another translation unit (source file).

---

## Q9. Difference between

```c
static
```

and

```c
extern
```

| static | extern |
|---------|---------|
| Internal linkage | External linkage |
| Hidden from other files | Shared across files |

---

## Q10. What is the difference between declaration and definition?

Declaration

```c
extern int x;
```

Definition

```c
int x = 10;
```

---

# 2. Predict the Output Questions

---

## Question 1

```c
#include <stdio.h>

void fun()
{
    int x = 0;

    x++;

    printf("%d ", x);
}

int main()
{
    fun();
    fun();
    fun();
}
```

Output

```
1 1 1
```

Reason

Each function call creates a new local variable.

---

## Question 2

```c
#include <stdio.h>

void fun()
{
    static int x = 0;

    x++;

    printf("%d ", x);
}

int main()
{
    fun();
    fun();
    fun();
}
```

Output

```
1 2 3
```

---

## Question 3

```c
#include <stdio.h>

int x = 10;

int main()
{
    int x = 20;

    printf("%d", x);
}
```

Output

```
20
```

Local variable shadows the global variable.

---

## Question 4

```c
#include <stdio.h>

int x = 10;

void fun()
{
    printf("%d", x);
}

int main()
{
    fun();
}
```

Output

```
10
```

---

## Question 5

```c
#include <stdio.h>

static int x = 100;

int main()
{
    printf("%d", x);
}
```

Output

```
100
```

---

## Question 6

```c
#include <stdio.h>

void fun()
{
    static int x;

    printf("%d ", x);

    x++;
}

int main()
{
    fun();
    fun();
    fun();
}
```

Output

```
0 1 2
```

---

## Question 7

```c
#include <stdio.h>

int fun()
{
    static int x = 5;

    return x++;
}

int main()
{
    printf("%d ", fun());
    printf("%d ", fun());
    printf("%d ", fun());
}
```

Output

```
5 6 7
```

---

## Question 8

```c
#include <stdio.h>

void fun()
{
    register int x = 5;

    printf("%d", x);
}

int main()
{
    fun();
}
```

Output

```
5
```

---

## Question 9

```c
register int x = 5;
```

Is it valid?

Answer

❌ No.

`register` can only be applied to objects with automatic storage duration (typically local variables or function parameters).

---

## Question 10

```c
register int x = 5;

int *p = &x;
```

Answer

Compiler Error.

The address of a register variable cannot be taken.

---

# 3. Multi-file Programming Questions

---

## Question 11

file1.c

```c
int count = 100;
```

file2.c

```c
extern int count;
```

Valid?

✅ Yes.

---

## Question 12

file1.c

```c
static int count = 100;
```

file2.c

```c
extern int count;
```

Result

```
Linker Error
```

---

## Question 13

file1.c

```c
int count;
```

file2.c

```c
int count;
```

Result

```
Multiple definition
```

(On many modern toolchains using `-fno-common`; historically some linkers accepted tentative definitions. Know the compiler/toolchain behavior.)

---

## Question 14

Which file should contain

```c
extern int count;
```

Answer

Usually

```
header file
```

---

## Question 15

Where should

```c
int count = 0;
```

be written?

Exactly one

```
source file
```

---

# 4. Memory Layout Questions

---

## Question 16

Where is

```c
int x;
```

declared globally stored?

Answer

```
BSS
```

---

## Question 17

Where is

```c
int x = 10;
```

stored?

Answer

```
Data Segment
```

---

## Question 18

Where is

```c
int x;
```

inside a function stored?

```
Stack
```

---

## Question 19

Where is

```c
static int x;
```

inside a function stored?

```
BSS
```

(or Data segment if initialized with a non-zero constant.)

---

## Question 20

Where is

```c
malloc()
```

memory stored?

```
Heap
```

---

# 5. Coding Problems

---

## Problem 1

Write a function that counts how many times it has been called.

Solution

```c
#include <stdio.h>

void counter()
{
    static int count = 0;

    count++;

    printf("%d\n", count);
}

int main()
{
    counter();
    counter();
    counter();
}
```

Output

```
1
2
3
```

---

## Problem 2

Generate unique IDs.

```c
int getNextID()
{
    static int id = 1000;

    return id++;
}
```

Output

```
1000

1001

1002
```

---

## Problem 3

Count recursive calls.

```c
#include <stdio.h>

void recur(int n)
{
    static int calls = 0;

    calls++;

    printf("Call %d\n", calls);

    if(n)
        recur(n - 1);
}

int main()
{
    recur(4);
}
```

Output

```
Call 1
Call 2
Call 3
Call 4
Call 5
```

---

## Problem 4

Hide a module variable.

```c
/* driver.c */

static int state = 0;

void setState(int s)
{
    state = s;
}

int getState(void)
{
    return state;
}
```

Only `driver.c` can directly access `state`.

---

## Problem 5

Implement a singleton-like configuration.

```c
typedef struct
{
    int timeout;
    int retries;
} Config;

Config *getConfig(void)
{
    static Config cfg = {10, 3};

    return &cfg;
}
```

---

# 6. Common Mistakes

---

## Mistake 1

Confusing

```
Scope
```

with

```
Lifetime
```

They are independent concepts.

---

## Mistake 2

Thinking

```c
static
```

means

```
Global
```

It does **not**.

It changes meaning depending on where it is used.

---

## Mistake 3

Using

```c
extern
```

without an actual definition.

Result

```
Undefined Reference
```

---

## Mistake 4

Defining globals inside header files.

Wrong

```c
/* config.h */

int count = 0;
```

Every source file including the header creates another definition.

Correct

```c
/* config.h */

extern int count;
```

```c
/* config.c */

int count = 0;
```

---

## Mistake 5

Using too many global variables.

Large embedded projects avoid this because it increases coupling and makes testing harder.

---

# 7. Company-Specific Questions

These questions are frequently asked in Qualcomm, NVIDIA, AMD, Broadcom, Intel, Samsung, and Linux kernel interviews.

### Easy

- What is the default storage class of a local variable?
- Difference between auto and static?
- What is extern?
- Where are global variables stored?
- Difference between stack and heap?

---

### Medium

- Explain scope, lifetime, and linkage.
- Difference between static local and static global.
- Difference between declaration and definition.
- Why use static helper functions?
- What happens if two source files define the same global?

---

### Advanced

- Explain tentative definitions.
- Explain BSS vs Data segment.
- Can `static` cause race conditions?
- Can `register` variables be optimized away?
- How does the linker resolve `extern` variables?
- What is a translation unit?
- Why should global variables be minimized in embedded software?

---

# Quick Revision Sheet

| Keyword | Scope | Lifetime | Linkage |
|----------|--------|----------|----------|
| auto | Block | Function | None |
| register | Block | Function | None |
| static local | Block | Program | None |
| static global | File | Program | Internal |
| extern | File | Program | External |

---

# Key Takeaways

- Master **scope**, **lifetime**, and **linkage**—they are foundational interview topics.
- Understand how `static` behaves differently for local variables, global variables, and functions.
- Use `extern` for declarations shared across translation units, with exactly one definition.
- Avoid defining global variables in header files.
- Know where different kinds of variables reside in memory (Stack, Heap, Data, BSS).
- Be familiar with linker errors such as **multiple definition** and **undefined reference** and how to fix them.

---

