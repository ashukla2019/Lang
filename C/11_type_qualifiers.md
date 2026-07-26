# Chapter 11 – Type Qualifiers
# Part 1 – const Fundamentals

---

# Contents

1. What are Type Qualifiers?
2. What is const?
3. Why Do We Need const?
4. const Variables
5. Memory Layout of const
6. const vs #define
7. const and Functions
8. Compiler Optimizations
9. Common Misconceptions
10. Interview Questions
11. Best Practices
12. Key Takeaways

---

# 1. What are Type Qualifiers?

A **type qualifier** provides additional information about how an object can be used.

C provides four major type qualifiers.

| Qualifier | Purpose |
|-----------|----------|
| const | Read-only object |
| volatile | Object may change unexpectedly |
| restrict | Pointer aliasing optimization |
| _Atomic | Atomic operations |

This chapter begins with **const**, one of the most frequently asked C interview topics.

---

# 2. What is const?

`const` tells the compiler that an object **should not be modified through that declaration**.

Example

```c
const int x = 10;
```

Attempting

```c
x = 20;
```

Compiler Error

```
error: assignment of read-only variable 'x'
```

---

Think of it as

```
Normal Variable

Read

✓

Write

✓
```

```
Const Variable

Read

✓

Write

✗
```

---

# 3. Why Do We Need const?

Without const

```c
void print(int *value)
{
    *value = 100;
}
```

Nothing prevents accidental modification.

---

Using const

```c
void print(const int *value)
{
    printf("%d\n", *value);
}
```

Now

```c
*value = 100;
```

Compiler Error

The function promises not to modify the caller's data.

---

Benefits

- Prevents accidental modification
- Documents programmer intent
- Enables compiler diagnostics
- Improves API design
- Helps optimization in some cases

---

# 4. const Variables

Example

```c
const int age = 25;

printf("%d\n", age);
```

Valid

---

Attempt

```c
age = 30;
```

Compiler Error

---

Example

```c
const float PI = 3.14159f;

float area = PI * r * r;
```

Perfectly valid.

---

# Initialization

Const variables should be initialized when declared.

Correct

```c
const int x = 5;
```

Wrong

```c
const int x;

x = 5;
```

Compiler Error

A const-qualified object cannot be assigned after its initialization.

---

# 5. Memory Layout of const

Interview Question

> Where is a const variable stored?

Answer

**It depends.**

---

## Local const

```c
void fun()
{
    const int x = 10;
}
```

Typically stored on the

```
Stack
```

---

## Global const

```c
const int value = 100;
```

Typically stored in a

```
Read-Only Data Section (.rodata)
```

or another implementation-defined read-only segment.

Attempting to modify it through undefined means can cause a runtime fault on many systems.

---

Memory Diagram

```
+----------------------+
| Text                 |
+----------------------+

+----------------------+
| Read-Only Data       |
|----------------------|
| Global const         |
+----------------------+

+----------------------+
| Data                 |
+----------------------+

+----------------------+
| BSS                  |
+----------------------+

+----------------------+
| Heap                 |
+----------------------+

+----------------------+
| Stack                |
|----------------------|
| Local const          |
+----------------------+
```

---

# 6. const vs #define

Many beginners confuse these.

---

Using macro

```c
#define SIZE 100
```

Preprocessor replaces

```
SIZE

↓

100
```

No variable exists.

---

Using const

```c
const int SIZE = 100;
```

Creates a typed object.

---

Comparison

| Feature | const | #define |
|----------|-------|----------|
| Type | Yes | No |
| Scope | Yes | No |
| Debugger Visibility | Yes | Usually No |
| Compiler Checks | Yes | No |
| Text Replacement | No | Yes |
| Memory | Depends | None |

---

Example

```c
const int x = 10;
```

Compiler knows

```
Type

↓

int
```

---

Macro

```c
#define X 10
```

Compiler only receives

```
10
```

No type information is associated with the macro itself.

---

# 7. const and Functions

Very common interview topic.

---

Passing by Value

```c
void print(const int x)
{
    printf("%d", x);
}
```

The caller's variable is copied.

Using `const` here mainly prevents accidental modification inside the function.

---

Passing by Pointer

```c
void print(const int *x)
{
    printf("%d", *x);
}
```

The function promises not to modify the object pointed to.

---

Example

```c
int value = 100;

print(&value);
```

Inside

```c
*x = 20;
```

Compiler Error

---

Returning const

Example

```c
const char *getName(void)
{
    return "OpenAI";
}
```

The caller should treat the returned string as read-only.

Attempting to modify a string literal is undefined behavior.

---

# 8. Compiler Optimizations

Since a const-qualified object is not intended to change through that declaration,

the compiler may

- Keep values in registers
- Eliminate redundant loads
- Propagate constants

Example

```c
const int size = 8;

for(int i = 0; i < size; i++)
{
}
```

The compiler knows

```
size = 8
```

at compile time and can optimize accordingly.

(Actual optimizations depend on the compiler and optimization level.)

---

# 9. Common Misconceptions

---

## Misconception 1

"const means compile-time constant."

Not always.

Example

```c
int value = 10;

const int x = value;
```

`x` is read-only after initialization, but its value was obtained at runtime.

---

## Misconception 2

"const objects are always stored in ROM."

False.

Local const objects are typically on the stack.

Global const objects are commonly placed in read-only sections by the toolchain.

---

## Misconception 3

"const makes data immutable."

Not exactly.

It prevents modification **through that particular declaration**.

Whether the underlying object can be modified depends on how it was originally defined.

(We'll explore this in detail with const pointers in Part 2.)

---

# 10. Frequently Asked Interview Questions

---

## Q1. What is const?

A type qualifier indicating that an object should not be modified through that declaration.

---

## Q2. Does const always allocate memory?

No.

Storage depends on the object and optimization.

Some const objects may even be optimized away if they are never used.

---

## Q3. Difference between

```c
const int x = 10;
```

and

```c
#define X 10
```

`const`

- Typed object
- Compiler-checked
- Respects scope

`#define`

- Preprocessor substitution
- Untyped
- No scope rules

---

## Q4. Can const variables be initialized later?

No.

They should be initialized when declared.

---

## Q5. Can we read a const variable?

Yes.

Only modification is restricted.

---

## Q6. Does const improve performance?

Sometimes.

It gives the compiler additional information that may enable optimizations, but it does not guarantee faster code.

---

## Q7. Why should function parameters use const?

To prevent accidental modification of caller-owned data and to clearly express intent.

---

# Best Practices

✓ Use `const` whenever data should not be modified.

✓ Mark pointer parameters as `const` if the function only reads the data.

✓ Prefer `const` over `#define` for typed constants.

✓ Initialize const-qualified objects at declaration.

✓ Treat string literals as read-only.

---

# Key Takeaways

- `const` is a **type qualifier**, not a storage class.
- It prevents modification **through the qualified declaration**.
- `const` improves code safety, readability, and API design.
- Local const objects are typically stored on the stack, while global const objects are commonly placed in read-only memory sections.
- `const` is different from `#define` because it has a type and participates in the language.
- Using `const` in function parameters documents intent and helps prevent bugs.
- `const` does not necessarily mean "compile-time constant" or "stored in ROM."

---

# Next Part

**Part 2 – const Pointers (The Most Important Interview Topic)**

We'll cover:

- `const int *`
- `int * const`
- `const int * const`
- Reading declarations
- Pointer modification vs data modification
- Memory diagrams
- 30+ pointer interview questions

- -----------------------------------------------------------
