# C Storage Classes
# auto, static, extern, register - Complete Interview Notes

---

# Table of Contents

1. Why Storage Classes?
2. What is a Storage Class?
3. Types of Storage Classes
4. auto
5. static
6. extern
7. register
8. Lifetime vs Scope vs Linkage
9. Comparison Table
10. Interview Questions

---

# 1. Why Storage Classes?

When we declare a variable

```c
int x = 10;
```

The compiler needs answers to questions like:

- Where should it be stored?
- Who can access it?
- How long should it live?
- Should other files be able to access it?

These are controlled by **Storage Classes**.

---

# 2. What is a Storage Class?

A storage class tells the compiler

- Storage location
- Scope
- Lifetime
- Linkage

There are four storage classes in C

```
auto

static

extern

register
```

---

# Understanding Scope

Scope = Where a variable can be accessed.

Example

```c
void fun()
{
    int x = 10;
}
```

```
x exists only inside fun()
```

---

# Understanding Lifetime

Lifetime = How long variable remains in memory.

Example

```c
void fun()
{
    int x = 10;
}
```

```
Memory created

↓

Function executes

↓

Memory destroyed
```

---

# Understanding Linkage

Linkage tells whether another file can access the variable.

```
File1.c

↓

Can File2.c access it?

Yes → External Linkage

No → Internal Linkage
```

---

# 3. auto

Default storage class.

Example

```c
auto int x = 10;
```

Exactly same as

```c
int x = 10;
```

Compiler automatically assumes

```
auto
```

Example

```c
void fun()
{
    auto int x = 10;

    printf("%d", x);
}
```

Memory

```
Stack

+------+
|  x   |
+------+
```

Function returns

↓

Memory removed.

Properties

| Property | Value |
|-----------|-------|
| Storage | Stack |
| Scope | Local |
| Lifetime | Function call |
| Default Value | Garbage |

---

Example

```c
void fun()
{
    int x;

    printf("%d", x);
}
```

Output

```
Garbage Value
```

because auto variables are **not initialized automatically**.

---

# 4. static

Static variables keep their value even after function returns.

Example

```c
void fun()
{
    static int count = 0;

    count++;

    printf("%d\n", count);
}
```

Call

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

Why?

Memory

```
Program Starts

↓

count created

↓

Function returns

↓

count NOT destroyed

↓

Function called again

↓

Same count reused
```

---

Normal Variable

```c
void fun()
{
    int count = 0;

    count++;

    printf("%d", count);
}
```

Output

```
1

1

1
```

because memory is recreated every call.

---

Static Local Variable

Storage

```
Data Segment
```

Not stack.

Properties

| Property | Value |
|-----------|-------|
| Storage | Data Segment |
| Scope | Local |
| Lifetime | Entire Program |
| Default Value | 0 |

---

# Static Global Variable

Example

File1.c

```c
static int x = 10;
```

File2.c

```c
extern int x;
```

Compilation

```
Error
```

Why?

Because

```
static

↓

Internal Linkage

↓

Visible only inside File1.c
```

---

# 5. extern

Suppose

File1.c

```c
int x = 100;
```

File2.c

```c
extern int x;

printf("%d", x);
```

Output

```
100
```

extern means

```
Variable exists elsewhere.

Don't allocate memory.

Just use it.
```

Memory

```
File1

x

↓

File2

extern x

↓

Uses same variable
```

---

Without extern

File2.c

```c
int x;
```

This creates another variable.

Different memory.

---

Properties

| Property | Value |
|-----------|-------|
| Storage | Data Segment |
| Scope | Global |
| Lifetime | Entire Program |
| Linkage | External |

---

# extern Function

Every function has external linkage by default.

```c
extern void fun();
```

Usually unnecessary.

---

# 6. register

register tells compiler

```
Try storing variable inside CPU register.
```

Example

```c
register int i;

for(i=0;i<100;i++)
{
}
```

Why?

Registers are much faster than RAM.

Memory

```
CPU Register

↓

Fast

----------------

RAM

↓

Slower
```

Important

Compiler may ignore it.

Modern compilers perform their own optimization.

---

Cannot Take Address

```c
register int x = 10;

printf("%p", &x);
```

May produce compilation error.

Reason

Registers don't have memory addresses like RAM variables.

---

Properties

| Property | Value |
|-----------|-------|
| Storage | CPU Register (if possible) |
| Scope | Local |
| Lifetime | Function call |
| Default Value | Garbage |

---

# 7. Lifetime Comparison

auto

```
Function Starts

↓

Created

↓

Destroyed

↓

Function Ends
```

---

static

```
Program Starts

↓

Created

↓

Never Destroyed

↓

Program Ends
```

---

extern

```
Program Starts

↓

Exists

↓

Program Ends
```

---

register

```
Function Starts

↓

Created

↓

Destroyed

↓

Function Ends
```

---

# 8. Scope Comparison

```
auto

↓

Local
```

```
register

↓

Local
```

```
static local

↓

Local
```

```
static global

↓

Current File
```

```
extern

↓

Entire Program
```

---

# 9. Complete Comparison

| Feature | auto | static | extern | register |
|----------|------|---------|----------|-----------|
| Storage | Stack | Data Segment | Data Segment | Register/Stack |
| Scope | Local | Local or File | Global | Local |
| Lifetime | Function Call | Entire Program | Entire Program | Function Call |
| Default Value | Garbage | 0 | 0 | Garbage |
| Linkage | None | Internal (global) | External | None |

---

# Memory Layout

```
+---------------------------+
| Code Segment              |
+---------------------------+

| Initialized Data          |
| static = 10               |
| global = 20               |
+---------------------------+

| BSS                       |
| static int x;             |
| global int y;             |
+---------------------------+

| Heap                      |
| malloc()                  |
+---------------------------+

| Stack                     |
| auto variables            |
| register (if spilled)     |
+---------------------------+
```

---

# Interview Questions

## Why is auto rarely written?

Because every local variable is `auto` by default.

---

## Why use static inside a function?

To preserve a variable's value across function calls.

---

## Difference between global and static global?

Global

```
Visible to all files.
```

Static Global

```
Visible only inside current source file.
```

---

## Why use extern?

To access a global variable or function defined in another source file.

---

## Does extern allocate memory?

No.

It only declares that the variable exists elsewhere.

---

## Why is register obsolete?

Modern compilers automatically decide whether a variable should be placed in a CPU register, making the `register` keyword mostly ignored.

---

## Can we take address of register variable?

No (by the C language rules).

```c
register int x;

printf("%p",&x);    // Invalid
```

---

## Where are static variables stored?

```
Data Segment
```

---

## Where are auto variables stored?

```
Stack
```

---

## Which variables are initialized to zero automatically?

- Global variables
- Static variables

Not

- auto
- register

---

# Key Takeaways

- `auto` is the default storage class for local variables.
- `static` extends a variable's lifetime to the entire program.
- `static` at file scope gives **internal linkage** (visible only within that file).
- `extern` declares a variable or function defined in another file and does not allocate memory.
- `register` is only a request to the compiler to use a CPU register and is generally ignored by modern compilers.
- Storage classes define **where a variable is stored, its scope, its lifetime, and its linkage**—all common interview topics.