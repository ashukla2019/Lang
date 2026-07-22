# C Interview Handbook
# Part 1 - C Fundamentals

---

# Table of Contents

1. Introduction to C
2. Structure of a C Program
3. Compilation Process
4. Variables
5. Data Types
6. Constants
7. Operators
8. Type Conversion
9. Storage Classes
10. Scope & Lifetime
11. Keywords
12. Input & Output
13. Important Interview Questions
14. Quick Revision

---

# 1. Introduction to C

## What is C?

C is a

- Procedural Programming Language
- Middle-Level Language
- Compiled Language
- Fast
- Portable
- Efficient

It is widely used for

- Operating Systems
- Device Drivers
- Embedded Systems
- Networking
- Databases
- Compilers

Example

```c
#include <stdio.h>

int main()
{
    printf("Hello World\n");
    return 0;
}
```

---

# 2. Structure of a C Program

```text
+----------------------+
| Header Files         |
+----------------------+
| Global Variables     |
+----------------------+
| Function Declaration |
+----------------------+
| main()               |
+----------------------+
| User Functions       |
+----------------------+
```

Example

```c
#include <stdio.h>

// Global Variable
int x = 10;

// Function Declaration
void display();

int main()
{
    display();
    return 0;
}

void display()
{
    printf("%d\n", x);
}
```

---

# 3. Compilation Process

## Flow

```text
Source Code (.c)

↓

Preprocessor

↓

Compiler

↓

Assembler

↓

Object File (.o)

↓

Linker

↓

Executable
```

### Step 1 - Preprocessor

Processes

- #include
- #define
- #ifdef
- Macros

Output

```text
Expanded Source Code
```

---

### Step 2 - Compiler

Converts C code into Assembly.

Checks

- Syntax
- Type Errors

Output

```text
Assembly Code (.s)
```

---

### Step 3 - Assembler

Converts

```text
Assembly

↓

Machine Code
```

Output

```text
Object File (.o)
```

---

### Step 4 - Linker

Links

- Object files
- Libraries

Produces

```text
Executable
```

---

# Interview Question

Difference between Compiler and Linker?

Compiler

- Converts C → Assembly
- Detects syntax errors

Linker

- Combines object files
- Resolves function references

---

# 4. Variables

Variable is a named memory location.

Example

```c
int age = 20;
```

Memory

```text
Address      Value

1000         20
```

Variable

```text
age

↓

1000
```

---

## Variable Naming Rules

Allowed

```text
age
student1
total_marks
```

Not Allowed

```text
1age
total-marks
float
```

---

# 5. Data Types

## Integer

```c
int
short
long
long long
```

---

## Floating Point

```c
float
double
long double
```

---

## Character

```c
char
```

Stores

```text
One Character
```

Example

```c
char ch='A';
```

---

## Void

Represents

```text
No Value
```

Example

```c
void display();
```

---

# sizeof()

Returns memory occupied.

Example

```c
printf("%zu", sizeof(int));
```

Typical output

```text
4
```

---

# 6. Constants

## Literal

```c
10
3.14
'A'
"Hello"
```

---

## const

```c
const int MAX = 100;
```

Cannot modify later.

---

## #define

```c
#define PI 3.14159
```

No memory allocated.

Replaced during preprocessing.

---

Interview

Difference between const and #define?

const

- Has type
- Memory allocated
- Checked by compiler

#define

- Text replacement
- No type
- No memory

---

# 7. Operators

## Arithmetic

```text
+
-
*
/
%
```

---

## Relational

```text
<
>
<=
>=
==
!=
```

Returns

```text
0 or 1
```

---

## Logical

```text
&&
||
!
```

---

## Assignment

```text
=
+=
-=
*=
/=
```

---

## Increment

```text
++
--
```

Example

```c
int x = 5;

printf("%d", x++);
```

Output

```text
5
```

Now

```text
x = 6
```

---

Example

```c
int x=5;

printf("%d", ++x);
```

Output

```text
6
```

---

## Bitwise

```text
&
|
^
~
<<
>>
```

---

## Conditional Operator

```c
(condition) ? value1 : value2;
```

Example

```c
int max=(a>b)?a:b;
```

---

# 8. Type Conversion

## Implicit

Done automatically.

Example

```c
int x=10;

float y=x;
```

---

## Explicit

Done by programmer.

```c
float x=10.5;

int y=(int)x;
```

Output

```text
10
```

---

# 9. Storage Classes

## auto

Default local variable.

```c
void fun()
{
    auto int x=10;
}
```

---

## static

Value persists across function calls.

```c
void fun()
{
    static int count=0;

    count++;

    printf("%d",count);
}
```

Output

```text
1
2
3
```

---

## extern

Used to access global variables from another file.

```c
extern int total;
```

---

## register

Suggests storing variable in CPU register.

```c
register int i;
```

Compiler may ignore it.

---

# Interview Table

| Storage Class | Scope | Lifetime |
|---------------|-------|----------|
| auto | Local | Function |
| static(local) | Local | Entire Program |
| static(global) | File | Entire Program |
| extern | Global | Entire Program |
| register | Local | Function |

---

# 10. Scope and Lifetime

## Local Variable

Accessible only inside function.

```c
void fun()
{
    int x=10;
}
```

---

## Global Variable

Accessible everywhere after declaration.

```c
int x=100;
```

---

## Lifetime

Local

```text
Function starts

↓

Variable Created

↓

Function Ends

↓

Destroyed
```

Static

```text
Program Starts

↓

Variable Created

↓

Program Ends

↓

Destroyed
```

---

# 11. Important Keywords

```text
auto
break
case
char
const
continue
default
do
double
else
enum
extern
float
for
goto
if
inline
int
long
register
return
short
signed
sizeof
static
struct
switch
typedef
union
unsigned
void
volatile
while
```

---

# 12. Input & Output

## printf()

```c
printf("Age=%d", age);
```

---

## scanf()

```c
scanf("%d",&age);
```

Remember

```text
&
```

passes the variable's address so `scanf()` can modify it.

---

# Common Format Specifiers

| Type | Specifier |
|------|-----------|
| int | %d |
| char | %c |
| float | %f |
| double | %lf |
| string | %s |
| pointer | %p |

---

# 13. Frequently Asked Interview Questions

### Q1. Why is C called a middle-level language?

Because it supports

- High-level programming features
- Low-level memory access using pointers

---

### Q2. Difference between Compiler and Interpreter?

Compiler

- Converts entire program before execution.
- Faster execution.
- Generates executable.

Interpreter

- Executes line by line.
- Slower execution.
- No separate executable.

---

### Q3. Difference between const and #define?

See Section 6.

---

### Q4. Difference between ++i and i++?

`++i` (Pre-increment)
- Increment first.
- Then use the value.

`i++` (Post-increment)
- Use the current value.
- Increment afterward.

---

### Q5. Difference between local and global variables?

Local
- Declared inside a function.
- Limited scope.
- Exists only during the function call.

Global
- Declared outside functions.
- Visible according to scope rules.
- Exists for the entire program.

---

### Q6. What is sizeof()?

Returns the size (in bytes) of a type or object.

Example

```c
int a;
printf("%zu\n", sizeof(a));
```

---

### Q7. What is the default storage class?

`auto` for local variables.

---

# 14. Quick Revision

✓ C is procedural and compiled.

✓ Compilation flow

```text
.c
↓

Preprocessor

↓

Compiler

↓

Assembler

↓

Object

↓

Linker

↓

Executable
```

✓ Variable stores data in memory.

✓ `const` is typed and occupies storage; `#define` is a preprocessor text replacement.

✓ Learn all operators, especially increment/decrement and bitwise operators.

✓ Understand implicit vs explicit type conversion.

✓ Master storage classes: `auto`, `static`, `extern`, and `register`.

✓ Understand scope (where a name is visible) and lifetime (how long an object exists).

✓ Remember common `printf()` and `scanf()` format specifiers.

---

# Next Part

Part 2 - Memory Management

- Memory Layout
- Stack
- Heap
- malloc()
- calloc()
- realloc()
- free()
- Memory Leak
- Dangling Pointer
- Wild Pointer
- NULL Pointer
- Memory Corruption
- Best Practices