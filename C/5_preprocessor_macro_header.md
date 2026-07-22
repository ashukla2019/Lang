# C Interview Handbook
# Part 3E - Preprocessor, Macros & Header Files

---

# Table of Contents

1. What is the Preprocessor?
2. #include
3. #define
4. Object-like Macros
5. Function-like Macros
6. Macro Pitfalls
7. Conditional Compilation
8. Header Files
9. Include Guards
10. #pragma once
11. Common Predefined Macros
12. Interview Questions
13. Quick Revision

---

# 1. What is the Preprocessor?

The C preprocessor runs **before compilation**.

Build Flow

```text
Source Code (.c)

↓

Preprocessor

↓

Expanded Source

↓

Compiler

↓

Assembly

↓

Assembler

↓

Object File (.o)

↓

Linker

↓

Executable
```

Preprocessor directives begin with `#`.

Examples

```c
#include
#define
#ifdef
#ifndef
#if
#elif
#else
#endif
```

---

# 2. #include

Includes the contents of another file.

Example

```c
#include <stdio.h>
```

Searches system include directories.

---

Example

```c
#include "myheader.h"
```

Searches the current project first, then system include paths (implementation-dependent).

---

# 3. #define

Creates a macro.

Example

```c
#define PI 3.14159

printf("%f\n", PI);
```

After preprocessing

```c
printf("%f\n", 3.14159);
```

---

# 4. Object-like Macros

Example

```c
#define MAX_SIZE 100
#define NAME "OpenAI"
```

Used for constants or simple text substitution.

---

# 5. Function-like Macros

Example

```c
#define SQUARE(x) ((x) * (x))
```

Usage

```c
int a = SQUARE(5);
```

Expands to

```c
int a = ((5) * (5));
```

---

# 6. Macro Pitfalls

## Missing Parentheses

Wrong

```c
#define SQUARE(x) x * x

int a = SQUARE(1 + 2);
```

Expands to

```c
1 + 2 * 1 + 2
```

Result

```text
5
```

Expected

```text
9
```

Correct

```c
#define SQUARE(x) ((x) * (x))
```

---

## Side Effects

```c
#define MAX(a,b) ((a) > (b) ? (a) : (b))

int x = 5;

int y = MAX(x++, 10);
```

`x++` may be evaluated more than once depending on the expression.

Avoid passing expressions with side effects to macros.

---

# 7. Conditional Compilation

Compile code only when a condition is true.

Example

```c
#ifdef DEBUG
printf("Debug Mode\n");
#endif
```

If `DEBUG` is defined, the statement is compiled.

---

Using `#ifndef`

```c
#ifndef DEBUG
printf("Release Mode\n");
#endif
```

---

Using `#if`

```c
#define VERSION 2

#if VERSION >= 2
printf("New Version\n");
#endif
```

---

# 8. Header Files

Header files contain declarations shared across multiple source files.

Example

```c
/* math_utils.h */

int add(int a, int b);
int sub(int a, int b);
```

Source file

```c
/* math_utils.c */

#include "math_utils.h"

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}
```

Main file

```c
#include "math_utils.h"

int main(void)
{
    return add(2, 3);
}
```

---

# 9. Include Guards

Prevent multiple inclusion of the same header.

```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int add(int, int);
int sub(int, int);

#endif
```

Flow

```text
First Include

↓

Macro Not Defined

↓

Process Header

↓

Define Macro

↓

Second Include

↓

Macro Already Defined

↓

Skip Header
```

---

# 10. #pragma once

Alternative to include guards.

```c
#pragma once

int add(int, int);
```

Simpler to write.

Note: Widely supported by modern compilers, but not part of the original C standard.

---

# 11. Common Predefined Macros

```c
__FILE__
```

Current file name.

---

```c
__LINE__
```

Current line number.

---

```c
__DATE__
```

Compilation date.

---

```c
__TIME__
```

Compilation time.

---

Example

```c
printf("%s\n", __FILE__);
printf("%d\n", __LINE__);
```

Useful for debugging and logging.

---

# 12. Common Mistakes

## Mistake 1

```c
#define PI = 3.14
```

Wrong.

Correct

```c
#define PI 3.14
```

---

## Mistake 2

```c
#define ADD(a,b) a+b
```

Use parentheses.

Correct

```c
#define ADD(a,b) ((a) + (b))
```

---

## Mistake 3

Forgetting include guards.

This may lead to multiple definition or redefinition errors.

---

## Mistake 4

Using macros where a function is more appropriate.

Prefer `inline` functions when:
- Type safety is important.
- Arguments may have side effects.
- Debugging readability matters.

---

# 13. Frequently Asked Interview Questions

### Q1. What is the preprocessor?

A tool that processes directives and performs text substitution before compilation.

---

### Q2. Difference between

```c
#include <stdio.h>
```

and

```c
#include "myheader.h"
```

`<>`

- Typically searches system include directories.

`""`

- Typically searches the current project first, then system include paths.

---

### Q3. Why use macros?

- Constants
- Conditional compilation
- Simple code generation
- Platform-specific code

---

### Q4. Why use include guards?

To prevent multiple inclusion of the same header file.

---

### Q5. Difference between macro and function?

Macro

- Text substitution
- No type checking
- May evaluate arguments multiple times

Function

- Type checked
- Arguments evaluated once before the call
- Easier to debug

---

### Q6. Why use `#ifdef DEBUG`?

To include debugging code only in debug builds.

---

# 14. Quick Revision

✓ Preprocessor runs before compilation.

✓ `#include` includes headers.

✓ `#define` creates macros.

✓ Always parenthesize macro parameters.

✓ Avoid side effects in macro arguments.

✓ Use include guards.

✓ `#pragma once` is a common alternative.

✓ `__FILE__` and `__LINE__` are useful for debugging.

---

# Interview Memory Trick

```text
#include

↓

Reuse Code

#define

↓

Text Replacement

#ifdef

↓

Conditional Compilation

#ifndef

↓

Include Guards
```

---

# Next Part

**Part 3F – Storage Classes & Memory Layout**

Topics

- auto
- static
- extern
- register
- Scope
- Lifetime
- Linkage
- Memory Layout (Text, Data, BSS, Heap, Stack)
- Interview Questions