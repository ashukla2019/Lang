# C Interview Handbook
# Part 3F - Storage Classes & Memory Layout

---

# Table of Contents

1. What are Storage Classes?
2. Scope, Lifetime & Linkage
3. auto
4. register
5. static
6. extern
7. Memory Layout of a C Program
8. Text, Data, BSS, Heap & Stack
9. Memory Allocation Flow
10. Common Interview Questions
11. Quick Revision

---

# 1. What are Storage Classes?

A storage class defines

- Scope
- Lifetime
- Linkage
- Storage location

There are four storage classes in C.

```
auto
register
static
extern
```

---

# 2. Scope, Lifetime & Linkage

Before learning storage classes, understand these terms.

## Scope

Where a variable is visible.

Example

```c
void fun()
{
    int x = 10;
}
```

`x` is visible only inside `fun()`.

---

## Lifetime

How long a variable exists.

Example

```c
void fun()
{
    int x = 10;
}
```

`x` is created when `fun()` starts.

Destroyed when `fun()` returns.

---

## Linkage

Can another source file access this variable?

```
Internal Linkage

↓

Only current source file

External Linkage

↓

Accessible from other files
```

---

# 3. auto Storage Class

Default storage class for local variables.

Example

```c
void fun()
{
    auto int x = 10;

    printf("%d\n", x);
}
```

Usually written simply as

```c
int x = 10;
```

Properties

| Property | Value |
|----------|-------|
| Scope | Local |
| Lifetime | Function call |
| Default Value | Garbage (indeterminate) |
| Storage | Stack |

---

# 4. register Storage Class

Requests the compiler to keep a variable in a CPU register.

Example

```c
register int i;

for(i = 0; i < 10; i++)
{
    printf("%d\n", i);
}
```

Important

The compiler may ignore this request.

Modern compilers perform their own optimizations.

---

Cannot take its address

```c
register int x = 10;

printf("%p", (void *)&x);
```

This is not allowed by the C language.

---

Properties

| Property | Value |
|----------|-------|
| Scope | Local |
| Lifetime | Function call |
| Storage | Register (if possible) |

---

# 5. static Storage Class

`static` changes lifetime and/or linkage depending on where it is used.

---

## Static Local Variable

Example

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

    return 0;
}
```

Output

```text
1
2
3
```

Why?

The variable is initialized only once.

It exists until the program exits.

---

Memory

```text
Program Starts

↓

count = 0

↓

Function Call

↓

count++

↓

Function Returns

↓

count remains in memory

↓

Next Call

↓

Reuse previous value
```

---

## Static Global Variable

```c
static int value = 100;
```

Meaning

```
Internal Linkage

↓

Visible only inside
this source file
```

Useful for hiding implementation details.

---

Properties

| Property | Value |
|----------|-------|
| Scope | Local or File |
| Lifetime | Entire Program |
| Linkage | Internal (file-scope static) |

---

# 6. extern Storage Class

Used to access a global variable defined in another source file.

---

File1.c

```c
int count = 10;
```

---

File2.c

```c
extern int count;

printf("%d\n", count);
```

`extern` tells the compiler

```
The definition exists
in another file.
```

---

Properties

| Property | Value |
|----------|-------|
| Scope | Global |
| Lifetime | Entire Program |
| Linkage | External |

---

# 7. Memory Layout of a C Program

Typical memory layout

```text
+----------------------+
| Command-line Args    |
+----------------------+
| Environment          |
+----------------------+
| Stack                |
| grows downward       |
+----------------------+
|                      |
|      Free Space      |
|                      |
+----------------------+
| Heap                 |
| grows upward         |
+----------------------+
| BSS                  |
+----------------------+
| Data                 |
+----------------------+
| Text (Code)          |
+----------------------+
```

---

# 8. Memory Segments

## Text Segment

Contains

```
Machine Instructions

Compiled Functions

Read-only Code
```

Example

```c
void fun()
{
}
```

Stored in Text Segment.

---

## Data Segment

Stores

```
Initialized Global Variables

Initialized Static Variables
```

Example

```c
int g = 100;

static int x = 5;
```

---

## BSS Segment

Stores

```
Uninitialized Globals

Uninitialized Static Variables
```

Example

```c
int g;

static int s;
```

Both are automatically initialized to zero before `main()` starts.

---

## Heap

Dynamic memory.

Allocated using

```text
malloc()

calloc()

realloc()
```

Released using

```text
free()
```

---

## Stack

Stores

```
Function Calls

Parameters

Return Address

Local Variables
```

Example

```c
void fun()
{
    int x = 10;
}
```

`x` lives on the stack.

---

# 9. Memory Allocation Flow

Example

```c
int global = 10;

static int counter = 0;

int main()
{
    int local = 5;

    int *p = malloc(sizeof(int));

    *p = 20;

    free(p);

    return 0;
}
```

Memory

```text
Text

↓

main()

↓

Data

↓

global
counter

↓

Heap

↓

*p = 20

↓

Stack

↓

local
p
```

---

# Storage Class Summary

| Storage Class | Scope | Lifetime | Linkage | Storage |
|--------------|-------|----------|----------|----------|
| auto | Local | Function Call | None | Stack |
| register | Local | Function Call | None | Register (if possible) |
| static (local) | Local | Entire Program | None | Data/BSS |
| static (global) | File | Entire Program | Internal | Data/BSS |
| extern | Global | Entire Program | External | Data/BSS |

---

# Common Interview Questions

## Q1. Difference between scope and lifetime?

Scope

```
Where variable is accessible.
```

Lifetime

```
How long variable exists.
```

---

## Q2. Difference between static local and normal local?

Normal local

```
Created every call.

Destroyed every return.
```

Static local

```
Created once.

Destroyed when program exits.
```

---

## Q3. Difference between static and extern?

`static`

```
Internal linkage.

Only current source file.
```

`extern`

```
External linkage.

Defined elsewhere.
```

---

## Q4. Where are global variables stored?

```
Data Segment

or

BSS Segment
```

depending on whether they are initialized.

---

## Q5. Where is malloc memory stored?

```
Heap
```

---

## Q6. Where are local variables stored?

```
Stack
```

---

## Q7. What is BSS?

Stores

```
Uninitialized Globals

Uninitialized Static Variables
```

Automatically initialized to zero before program execution begins.

---

# Quick Revision

✓ `auto` → Default local variable.

✓ `register` → Hint to store in CPU register.

✓ `static` local → Retains value across function calls.

✓ `static` global → Internal linkage.

✓ `extern` → Variable defined in another source file.

✓ Text → Program instructions.

✓ Data → Initialized global/static variables.

✓ BSS → Uninitialized global/static variables.

✓ Heap → Dynamic memory.

✓ Stack → Function calls and local variables.

---

# Memory Trick

```text
Program

↓

Text

↓

Data

↓

BSS

↓

Heap ↑



Stack ↓
```

Remember

- Heap grows upward.
- Stack grows downward.
- They grow toward each other.

---

# Next Part

**Part 3G – Advanced C Concepts**

Topics

- volatile
- restrict (C99)
- typedef
- enum
- bit-fields
- Flexible Array Members
- _Bool
- Designated Initializers
- Interview Questions