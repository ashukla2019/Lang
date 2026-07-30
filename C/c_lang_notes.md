# Senior C Programming Master Handbook

## C for Senior Linux / Embedded / Systems Interviews

### Target Roles

This handbook is designed for senior engineers working with:

* Embedded Linux
* Linux systems
* Device drivers
* Firmware
* Networking
* Storage
* Infrastructure
* SoC/platform software
* Performance-critical systems

Target companies include:

* Qualcomm
* NVIDIA
* AMD
* Intel
* Broadcom
* Cisco
* Arista
* ARM
* Apple
* Microsoft
* Google
* Amazon
* Other senior embedded/systems organizations

---

# Table of Contents

1. C Fundamentals
2. Compilation Model
3. Data Types
4. Variables and Constants
5. Storage Classes
6. Scope, Lifetime and Linkage
7. Operators
8. Control Flow
9. Functions
10. Arrays
11. Strings
12. Pointers
13. Pointer Arithmetic
14. Pointer to Pointer
15. Function Pointers
16. Callbacks
17. Structures
18. Unions
19. Enumerations
20. typedef
21. const
22. volatile
23. restrict
24. Bit Manipulation
25. Dynamic Memory
26. Stack vs Heap
27. Memory Layout
28. Alignment and Padding
29. Endianness
30. Type Conversions
31. Integer Promotions
32. Signed vs Unsigned
33. Preprocessor
34. Macros
35. Header Files
36. Compilation and Linking
37. Static and Shared Libraries
38. Linkage and Symbols
39. `static` in C
40. `extern`
41. Undefined Behavior
42. Common C Bugs
43. Buffer Overflow
44. Dangling Pointers
45. Memory Leaks
46. Use-After-Free
47. Double Free
48. Strict Aliasing
49. Sequence / Evaluation Issues
50. `memcpy`, `memmove`, `memcmp`
51. String Functions
52. Function Calling and ABI Basics
53. Memory-Mapped I/O
54. Embedded C
55. Interrupt-Safe C
56. Concurrency and Atomics
57. C and Linux
58. System Calls
59. File Descriptors
60. Debugging C
61. GDB
62. Sanitizers
63. Performance
64. Coding Patterns
65. Senior Interview Questions
66. Final C Mental Models
67. Final Interview Checklist

---

# 1. C Fundamentals

C is:

```text
Compiled
Statically typed
Procedural
Low-level systems-oriented
Portable
```

C gives direct control over:

```text
Memory
Pointers
Data representation
Hardware interfaces
Calling conventions
Binary layout
```

This is why C remains important for:

```text
Operating systems
Embedded systems
Firmware
Device drivers
Networking
Databases
Compilers
Performance-critical software
```

---

# 2. Compilation Model

A C program normally goes through:

```text
Source
  |
  v
Preprocessor
  |
  v
Expanded source
  |
  v
Compiler
  |
  v
Assembly
  |
  v
Assembler
  |
  v
Object file
  |
  v
Linker
  |
  v
Executable
```

Typical command:

```bash
gcc main.c -o main
```

Conceptually:

```text
main.c
 ↓
preprocess
 ↓
compile
 ↓
assemble
 ↓
link
 ↓
main
```

---

# 3. Preprocessing

The preprocessor handles directives such as:

```c
#include
#define
#if
#ifdef
#ifndef
#endif
```

Example:

```c
#define MAX 100
```

The preprocessor replaces:

```c
MAX
```

with:

```c
100
```

before compilation.

---

# 4. Data Types

Basic C types:

```text
char
short
int
long
long long
float
double
long double
```

Modifiers:

```text
signed
unsigned
short
long
```

Important:

> Do not assume exact sizes for all C types across all platforms.

Use:

```c
sizeof(type)
```

or fixed-width types:

```c
#include <stdint.h>

uint32_t
int32_t
uint64_t
int64_t
```

---

# 5. `sizeof`

`sizeof` returns the size in bytes.

```c
int x;

printf("%zu\n", sizeof(x));
```

For an array:

```c
int a[10];

sizeof(a)
```

returns the size of the entire array when `a` is actually an array in that expression.

---

# 6. Variables

Example:

```c
int count = 10;
```

A variable has:

```text
Type
Name
Storage
Value
Lifetime
Scope
Linkage
```

These concepts become extremely important in senior interviews.

---

# 7. Constants

Use:

```c
const int max = 100;
```

`const` means the object should not be modified through that particular access path.

Important:

```c
const int *p;
```

and:

```c
int *const p;
```

mean different things.

---

# 8. Scope

Scope determines where an identifier can be referenced.

Common scopes:

```text
Block scope
File scope
Function scope
Function prototype scope
```

Example:

```c
void f(void)
{
    int x = 10;

    {
        int y = 20;
    }
}
```

`y` cannot be accessed outside its block.

---

# 9. Lifetime

Lifetime determines how long an object exists.

Examples:

```text
Automatic
Static
Allocated
```

Conceptually:

```text
Automatic
    → usually exists during block execution

Static
    → exists for entire program execution

Dynamic
    → exists until explicitly released
```

---

# 10. Linkage

Linkage determines whether declarations refer to the same entity across scopes/files.

Types:

```text
External linkage
Internal linkage
No linkage
```

Example:

```c
static int counter;
```

at file scope gives internal linkage.

---

# 11. Storage Classes

Important C keywords:

```text
auto
static
extern
register
```

Modern C programming rarely uses `register` explicitly.

`static` is extremely important.

---

# 12. `static`

At file scope:

```c
static int value;
```

means:

> The symbol has internal linkage.

It is visible only within that translation unit.

Inside a function:

```c
void counter(void)
{
    static int count = 0;
    count++;
}
```

`count` retains its value between calls.

---

# 13. `extern`

Example:

```c
extern int global_counter;
```

This declares an object defined elsewhere.

Typical:

```text
file1.c
    |
    +-- definition

file2.c
    |
    +-- extern declaration
```

---

# 14. Operators

Important categories:

```text
Arithmetic
Relational
Logical
Bitwise
Assignment
Increment/decrement
Conditional
Pointer
sizeof
```

Bitwise operators are especially important in embedded C.

---

# 15. Bitwise Operators

```text
&
|
^
~
<<
>>
```

Example:

```c
uint32_t x = 0x0F;

x |= (1U << 3);
```

Sets bit 3.

Clear:

```c
x &= ~(1U << 3);
```

Toggle:

```c
x ^= (1U << 3);
```

Test:

```c
if (x & (1U << 3))
{
}
```

---

# 16. Control Flow

Common constructs:

```c
if
else
switch
for
while
do while
break
continue
return
```

Senior interviews often test:

```text
switch behavior
fall-through
loop boundaries
signed/unsigned comparisons
```

---

# 17. Functions

Function:

```c
int add(int a, int b)
{
    return a + b;
}
```

Declaration:

```c
int add(int, int);
```

Definition:

```c
int add(int a, int b)
{
    return a + b;
}
```

---

# 18. Pass by Value

C passes arguments by value.

```c
void f(int x)
{
    x = 100;
}
```

The caller's variable does not change.

To modify caller data, pass an address:

```c
void f(int *x)
{
    *x = 100;
}
```

---

# 19. Arrays

```c
int a[5];
```

Memory:

```text
a[0]
a[1]
a[2]
a[3]
a[4]
```

Elements are contiguous.

```text
a[i]
```

is conceptually:

```text
*(a + i)
```

---

# 20. Array Size

For an actual array:

```c
int a[10];

size_t n = sizeof(a) / sizeof(a[0]);
```

This works because:

```text
sizeof(a)
```

is the size of the entire array.

---

# 21. Array vs Pointer

These are not the same:

```c
int a[10];
int *p;
```

Array:

```text
Storage for 10 integers
```

Pointer:

```text
Storage for an address
```

Important:

> In many expressions, an array decays to a pointer to its first element, but an array is not itself a pointer.

---

# 22. Pointer Fundamentals

Pointer:

```c
int x = 10;
int *p = &x;
```

Memory:

```text
p
 |
 | points to
 v
+-------+
|  10   |
+-------+
   x
```

Dereference:

```c
*p
```

gives:

```text
10
```

---

# 23. Pointer Operators

Address:

```c
&x
```

Dereference:

```c
*p
```

Example:

```c
int x = 10;
int *p = &x;

*p = 20;
```

Now:

```text
x == 20
```

---

# 24. NULL Pointer

Use:

```c
int *p = NULL;
```

A NULL pointer represents:

> No valid object/function is being referenced through that pointer.

Never dereference it.

```c
*p = 10;   // invalid
```

---

# 25. Pointer Arithmetic

For:

```c
int *p;
```

then:

```c
p + 1
```

moves by:

```text
sizeof(int)
```

not one byte.

Example:

```text
p
 |
 v
int

p + 1
 |
 v
next int
```

---

# 26. Pointer Comparison

Pointer arithmetic and comparison are only well-defined under specific rules, primarily involving pointers into the same array object (or one-past-the-end).

Do not assume arbitrary pointer comparisons are meaningful.

---

# 27. Pointer to Pointer

```c
int x = 10;
int *p = &x;
int **pp = &p;
```

Relationship:

```text
pp
 |
 v
 p
 |
 v
 x
```

Useful for:

```text
Modifying a pointer
Dynamic data structures
Output parameters
2D pointer-based structures
```

---

# 28. Function Pointers

Example:

```c
int add(int a, int b)
{
    return a + b;
}

int (*fp)(int, int) = add;
```

Call:

```c
int result = fp(10, 20);
```

Function pointers are heavily used for:

```text
Callbacks
Drivers
Interrupt handlers
State machines
Dispatch tables
Plugin interfaces
```

---

# 29. Callback

Example:

```c
void process(int (*callback)(int))
{
    int value = callback(10);
}
```

The caller provides behavior through a function pointer.

---

# 30. Function Pointer Table

Example:

```c
typedef void (*handler_t)(void);

handler_t handlers[] =
{
    handler_a,
    handler_b,
    handler_c
};
```

Useful for:

```text
Command dispatch
Protocol handling
State machines
Driver operations
```

---

# 31. Structures

```c
struct Point
{
    int x;
    int y;
};
```

Usage:

```c
struct Point p = {10, 20};
```

Access:

```c
p.x
```

---

# 32. Structure Pointer

```c
struct Point *p;
```

Access:

```c
p->x
```

Equivalent to:

```c
(*p).x
```

---

# 33. Structure Memory

Example:

```c
struct S
{
    char c;
    int x;
};
```

Do not assume:

```text
sizeof(struct S) == sizeof(char) + sizeof(int)
```

because of alignment and padding.

---

# 34. Padding

Compiler may insert padding:

```text
struct S
{
    char c;
    int x;
};
```

Possible layout:

```text
+----+----+----+----+
| c  |pad |pad |pad |
+----+----+----+----+
|        x          |
+-------------------+
```

Padding allows efficient aligned access.

---

# 35. Alignment

Objects may require specific alignment.

Example:

```text
char  → potentially 1-byte alignment
int   → commonly 4-byte alignment
```

Exact requirements are implementation-dependent.

---

# 36. Structure Packing

Packing can reduce padding but may cause:

```text
Unaligned access
Performance penalties
Hardware faults on some architectures
```

Avoid packed structures unless there is a real binary-layout requirement.

Common use:

```text
Network protocol headers
Hardware register layouts
File formats
```

---

# 37. Structure Assignment

Structures can be assigned:

```c
struct A a;
struct A b;

b = a;
```

The value of each member is copied.

For members that are pointers:

```text
pointer value is copied
```

This does not automatically deep-copy pointed-to memory.

---

# 38. Union

Example:

```c
union Data
{
    uint32_t u32;
    float f;
};
```

Members share storage.

Conceptually:

```text
+----------------+
| shared storage |
+----------------+
    ↑       ↑
   u32      f
```

Only one member's representation should generally be treated as active at a time, subject to C's specific rules.

---

# 39. Union Use Cases

Common uses:

```text
Variant data
Protocol representations
Hardware registers
Memory-efficient structures
```

---

# 40. Enum

```c
enum State
{
    IDLE,
    RUNNING,
    ERROR
};
```

Useful for:

```text
States
Modes
Flags/categories
Readable constants
```

Do not blindly assume the exact underlying representation size across all implementations.

---

# 41. typedef

Example:

```c
typedef unsigned int uint;
```

Structure:

```c
typedef struct
{
    int x;
    int y;
} Point;
```

Then:

```c
Point p;
```

---

# 42. `const`

Important forms:

```c
const int *p;
int const *p;
int *const p;
const int *const p;
```

Meaning:

```text
const int *p
    → cannot modify int through p

int *const p
    → p itself cannot point elsewhere

const int *const p
    → neither
```

---

# 43. `volatile`

`volatile` tells the compiler that accesses to an object are observable and should not be optimized away or merged in ways inconsistent with the language rules.

Common embedded uses:

```text
Memory-mapped registers
Hardware status
Some signal-handler-related objects
```

Example:

```c
volatile uint32_t *status;
```

Important:

> `volatile` does NOT make operations atomic.

It does NOT provide:

```text
Thread synchronization
Memory ordering
Locking
Atomic read-modify-write
```

---

# 44. `restrict`

`restrict` communicates an aliasing promise to the compiler.

Example:

```c
void copy(int *restrict dst,
          const int *restrict src,
          size_t n);
```

It tells the compiler that the accessed objects are not being accessed through conflicting pointer aliases in the relevant way.

Potential benefit:

```text
Better optimization
```

But violating the restrict contract causes undefined behavior.

---

# 45. Bit Manipulation

Extremely important for embedded interviews.

Set bit:

```c
x |= (1U << n);
```

Clear:

```c
x &= ~(1U << n);
```

Toggle:

```c
x ^= (1U << n);
```

Test:

```c
if (x & (1U << n))
```

Extract field:

```c
field = (x >> shift) & mask;
```

Insert field:

```c
x = (x & ~(mask << shift))
    | ((value & mask) << shift);
```

---

# 46. Common Bit Tricks

Check power of two:

```c
x != 0 && (x & (x - 1)) == 0
```

Clear lowest set bit:

```c
x &= (x - 1);
```

Get lowest set bit:

```c
x & -x
```

For unsigned values, prefer reasoning carefully about the integer type and conversions.

---

# 47. Bit Masks

Example:

```c
#define ENABLE_BIT   (1U << 0)
#define ERROR_BIT    (1U << 1)
#define READY_BIT    (1U << 2)
```

Usage:

```c
status |= ENABLE_BIT;
status &= ~ERROR_BIT;
```

Parenthesize macros carefully.

---

# 48. Dynamic Memory

Functions:

```c
malloc()
calloc()
realloc()
free()
```

Example:

```c
int *p = malloc(10 * sizeof(*p));

if (p == NULL)
{
    /* allocation failed */
}
```

Release:

```c
free(p);
```

---

# 49. `malloc`

```c
void *malloc(size_t size);
```

Allocates uninitialized storage.

Example:

```c
int *p = malloc(sizeof(*p));
```

The returned storage is suitably aligned for types requiring fundamental alignment.

---

# 50. `calloc`

```c
int *p = calloc(10, sizeof(*p));
```

Allocates space for 10 objects and initializes all allocated bytes to zero.

Do not confuse byte-zero initialization with every possible C type having the same semantic representation as the integer value zero.

---

# 51. `realloc`

```c
p = realloc(p, new_size);
```

Danger:

```c
p = realloc(p, new_size);
```

If `realloc` fails, the original pointer is still valid, but the assignment loses it.

Safer:

```c
void *tmp = realloc(p, new_size);

if (tmp != NULL)
    p = tmp;
```

---

# 52. `free`

```c
free(p);
```

After freeing:

```text
p
```

must not be dereferenced.

Good practice:

```c
free(p);
p = NULL;
```

Setting to NULL is useful when the pointer remains in scope and may otherwise be reused, but it is not a substitute for correct ownership design.

---

# 53. Stack vs Heap

### Stack

Typically used for:

```text
Automatic variables
Function call state
Local arrays
```

### Heap

Used for dynamically allocated objects.

Conceptually:

```text
Process
 |
 +-- Code
 +-- Data
 +-- Heap
 |
 +-- Stack
```

Exact memory layout is platform/ABI dependent.

---

# 54. Memory Layout

Typical process layout:

```text
High Address
+----------------+
| Stack          |
+----------------+
|                |
| mmap / shared  |
| libraries      |
+----------------+
| Heap           |
+----------------+
| BSS            |
+----------------+
| Data           |
+----------------+
| Read-only data |
+----------------+
| Text / Code    |
+----------------+
Low Address
```

Linux virtual memory introduces additional regions and mappings.

---

# 55. `.text`

Contains executable program code.

Usually:

```text
Read + Execute
```

and not writable.

---

# 56. `.rodata`

Read-only data.

Examples:

```c
const char *msg = "hello";
```

String literals are not modifiable.

Attempting to modify a string literal results in undefined behavior.

---

# 57. `.data`

Initialized writable global/static objects.

Example:

```c
int global = 10;
```

---

# 58. `.bss`

Uninitialized or zero-initialized global/static objects.

Example:

```c
static int counter;
```

The loader/runtime provides the required zero initialization.

---

# 59. Endianness

Endianness determines byte ordering.

Example:

```text
0x12345678
```

Little endian memory:

```text
78 56 34 12
```

Big endian:

```text
12 34 56 78
```

---

# 60. Detecting Endianness

Conceptually:

```c
uint32_t x = 1;
unsigned char *p = (unsigned char *)&x;
```

If:

```text
*p == 1
```

the system is little endian.

But portable software should avoid depending on host byte order unnecessarily.

---

# 61. Network Byte Order

Networking commonly uses:

```text
Big endian
```

Conversions:

```c
htons()
ntohs()
htonl()
ntohl()
```

Meaning:

```text
host → network
network → host
```

---

# 62. Type Conversions

Example:

```c
int x = 10;
double y = x;
```

Implicit conversion occurs.

Explicit:

```c
double y = (double)x;
```

Senior interviews often focus on:

```text
Signed/unsigned conversion
Integer promotions
Narrowing
Pointer conversions
Aliasing
```

---

# 63. Integer Promotions

Smaller integer types such as:

```text
char
short
```

are commonly promoted to `int` or `unsigned int` in expressions according to C's integer-promotion rules.

Example:

```c
char a = 100;
char b = 30;

int x = a + b;
```

The arithmetic is not necessarily performed as `char` arithmetic.

---

# 64. Signed vs Unsigned

Example:

```c
int x = -1;
unsigned int y = 1;

if (x < y)
```

This can produce surprising results because of the usual arithmetic conversions.

Important:

> Be extremely careful when comparing signed and unsigned values.

---

# 65. Unsigned Overflow

Unsigned integer arithmetic wraps modulo 2^N for an N-bit unsigned type.

Example for an 8-bit unsigned type:

```text
255 + 1 → 0
```

Signed integer overflow is different:

> Signed overflow is undefined behavior.

---

# 66. Preprocessor Macros

Example:

```c
#define SQUARE(x) ((x) * (x))
```

Parentheses are important.

Bad:

```c
#define SQUARE(x) x * x
```

Then:

```c
SQUARE(a + b)
```

can expand incorrectly.

---

# 67. Macro Side Effects

This macro:

```c
#define SQUARE(x) ((x) * (x))
```

with:

```c
SQUARE(i++)
```

evaluates `i++` more than once.

Avoid macros that evaluate arguments multiple times when side effects are possible.

---

# 68. Function-like Macro vs Function

Macro:

```text
Text substitution
```

Function:

```text
Type checking
Single evaluation of arguments
Normal function semantics
```

Prefer inline/static functions when appropriate.

---

# 69. Header Files

Header:

```c
#ifndef DEVICE_H
#define DEVICE_H

void device_init(void);

#endif
```

Provides declarations and shared interfaces.

Avoid putting unnecessary definitions in headers.

---

# 70. Include Guards

Purpose:

```text
Prevent multiple inclusion
```

Pattern:

```c
#ifndef FILE_H
#define FILE_H

...

#endif
```

Alternative:

```c
#pragma once
```

is widely supported but technically implementation-specific rather than part of the ISO C standard.

---

# 71. Translation Unit

A translation unit is approximately:

```text
source file
+
all included headers after preprocessing
```

The compiler compiles translation units independently.

---

# 72. Compilation and Linking

Example:

```text
main.c
foo.c
bar.c
```

Compile:

```text
main.o
foo.o
bar.o
```

Link:

```text
main
```

The linker resolves symbols between object files and libraries.

---

# 73. Static Library

Usually:

```text
libfoo.a
```

Contains object files archived together.

Linking can copy required object code into the executable.

---

# 74. Shared Library

Usually:

```text
libfoo.so
```

Shared libraries can be loaded/shared at runtime.

Benefits:

```text
Code sharing
Smaller executables
Independent library updates
```

Potential complexity:

```text
ABI compatibility
Loader behavior
Symbol resolution
Versioning
```

---

# 75. Symbols

The linker works with symbols such as:

```text
Functions
Global variables
```

Example:

```c
void foo(void);
```

If `foo()` is defined in another object file, the linker resolves the reference.

---

# 76. Static Function

```c
static void helper(void)
{
}
```

At file scope:

```text
helper has internal linkage
```

It is not visible as an external symbol to other translation units.

---

# 77. `extern` vs `static`

```text
extern
    → declaration referring to an entity with linkage

static at file scope
    → internal linkage
```

Example:

```c
/* file1.c */
int global;

/* file2.c */
extern int global;
```

---

# 78. `memcpy`

```c
memcpy(dst, src, n);
```

Copies `n` bytes.

Important:

> Source and destination must not overlap.

If they overlap, behavior is undefined.

---

# 79. `memmove`

```c
memmove(dst, src, n);
```

Correctly handles overlapping regions.

Rule:

```text
No overlap → memcpy
Possible overlap → memmove
```

---

# 80. `memcmp`

Compares raw bytes.

Do not use `memcmp` blindly to compare structures containing:

```text
Padding
Pointers
Floating-point values
Other representation-sensitive fields
```

Two logically equal structures can have different padding bytes.

---

# 81. String Fundamentals

C strings are:

```text
Array of char
terminated by '\0'
```

Example:

```c
char s[] = "hello";
```

Memory:

```text
h e l l o \0
```

---

# 82. Common String Functions

Important:

```text
strlen
strcpy
strncpy
strcat
strcmp
strchr
strstr
snprintf
```

Be careful with:

```text
Buffer size
Null termination
Destination capacity
Overlapping memory
```

---

# 83. Why `strncpy()` Is Dangerous to Misunderstand

`strncpy()` does not simply mean:

> "safe strcpy."

If the source is long enough, the destination may not be null-terminated.

Use carefully, or prefer explicit bounded designs such as `snprintf` where appropriate.

---

# 84. `snprintf`

Prefer:

```c
snprintf(buf, sizeof(buf), "%s", src);
```

over unbounded formatting functions when constructing strings.

Still check:

```text
Return value
Truncation
Encoding/format correctness
```

---

# 85. Undefined Behavior

Undefined behavior means:

> The C standard imposes no requirements on what happens.

Examples:

```text
Signed integer overflow
Out-of-bounds access
Use-after-free
Dereferencing invalid pointers
Double free
Modifying string literal
Invalid shift
Violating restrict assumptions
Some invalid aliasing
```

Compilers can exploit UB assumptions during optimization.

---

# 86. Buffer Overflow

Bad:

```c
char buf[10];

strcpy(buf, input);
```

If `input` is too large:

```text
Memory corruption
```

Potential consequences:

```text
Crash
Security vulnerability
Control-flow corruption
Silent data corruption
```

---

# 87. Out-of-Bounds Access

Bad:

```c
int a[10];

a[10] = 5;
```

Valid indices:

```text
0 ... 9
```

`a[10]` is out of bounds.

---

# 88. Dangling Pointer

```c
int *p = malloc(sizeof(*p));

free(p);

*p = 10;
```

`p` is dangling.

The memory is no longer owned by the allocation.

---

# 89. Use-After-Free

Pattern:

```text
allocate
   ↓
use
   ↓
free
   ↓
use again
```

This is a serious bug.

---

# 90. Double Free

```c
free(p);
free(p);
```

Invalid.

Can cause:

```text
Heap corruption
Crash
Security vulnerabilities
```

---

# 91. Memory Leak

```c
p = malloc(...);

/* p lost without free */
```

Repeated leaks can exhaust process memory.

---

# 92. Ownership

Senior C design should make ownership clear.

Ask:

```text
Who allocates?
Who owns?
Who modifies?
Who frees?
How long is it valid?
Can ownership transfer?
```

Example:

```text
create()
    → caller owns object

destroy()
    → caller releases object
```

Clear ownership is one of the most important C design practices.

---

# 93. Lifetime

A pointer can remain numerically non-NULL while pointing to an object whose lifetime has ended.

Therefore:

```text
Pointer validity
≠
Object lifetime
```

This distinction is fundamental for debugging C.

---

# 94. Strict Aliasing

C has rules governing which lvalue types may be used to access an object's stored value.

Violating those rules can create undefined behavior and unexpected optimization results.

Do not casually type-pun through incompatible pointer types.

---

# 95. Safe Type Punning

When representation-level copying is required, use mechanisms consistent with C's rules, such as:

```c
memcpy()
```

Example:

```c
uint32_t u;
float f;

memcpy(&u, &f, sizeof(u));
```

This copies representation bytes without violating aliasing rules in the same way as an invalid pointer cast would.

---

# 96. Alignment Bugs

Example concept:

```text
Unaligned address
       |
       v
   +---+
   |int|
   +---+
```

Some CPUs support unaligned access with a performance cost.

Others may fault or require special handling.

This is particularly important in:

```text
ARM
Embedded CPUs
DMA
Packed protocol structures
```

---

# 97. Memory-Mapped I/O

Embedded systems often map hardware registers into an address space.

Conceptually:

```text
CPU
 |
 v
0x40000000
 |
 v
Hardware Register
```

Example:

```c
volatile uint32_t *reg =
    (volatile uint32_t *)0x40000000;

*reg = 1;
```

The exact address and access mechanism are platform-specific.

---

# 98. Why `volatile` for MMIO?

Hardware can change register values independently of normal program flow.

Therefore the compiler must not assume:

```text
"nothing changes unless this C code changes it."
```

`volatile` makes accesses observable to the compiler.

But remember:

> `volatile` does not provide atomicity or inter-thread synchronization.

---

# 99. Embedded C

Important embedded concepts:

```text
Registers
MMIO
Interrupts
DMA
volatile
Bit manipulation
Fixed-width integers
Alignment
Packing
Memory constraints
Real-time behavior
Boot sequence
```

---

# 100. Interrupt Handler

A simplified model:

```text
Hardware
   |
   v
Interrupt
   |
   v
CPU
   |
   v
ISR
```

ISR should generally be:

```text
Short
Fast
Deterministic
Careful about blocking
```

Avoid doing long operations unnecessarily inside interrupt context.

---

# 101. ISR and Shared Data

Suppose:

```text
Main code
    |
    +-- shared variable
            ^
            |
        ISR modifies
```

The shared state needs an appropriate synchronization/atomicity strategy.

`volatile` alone is not a complete synchronization mechanism.

---

# 102. Atomic Operations

C11 provides:

```c
#include <stdatomic.h>
```

Example:

```c
atomic_int counter;
atomic_fetch_add(&counter, 1);
```

Atomics provide defined operations and memory-ordering semantics.

---

# 103. Atomic vs Volatile

```text
volatile
    → compiler visibility/observable accesses

atomic
    → atomicity + synchronization/memory ordering
```

Therefore:

```text
volatile ≠ atomic
```

This is one of the most important senior C interview questions.

---

# 104. Memory Ordering

C11 atomics support memory orders such as:

```text
memory_order_relaxed
memory_order_acquire
memory_order_release
memory_order_acq_rel
memory_order_seq_cst
```

Conceptually:

```text
Relaxed
    → atomicity without synchronization ordering

Acquire
    → prevents later operations from moving before acquire in the relevant model

Release
    → publishes prior operations

Sequentially consistent
    → strongest/simple global ordering model
```

---

# 105. Data Race

If two threads access the same memory concurrently and at least one access is a conflicting write, without appropriate synchronization, the program has a data race.

In C:

> A data race results in undefined behavior.

Solutions can include:

```text
Mutex
Atomic
Condition variable
Other synchronization mechanisms
```

---

# 106. Race Condition

Race condition:

```text
Outcome depends on timing/interleaving
```

Example:

```text
Thread A
    read x
    add 1
    write x

Thread B
    read x
    add 1
    write x
```

Updates can be lost.

---

# 107. Linux and C

Linux system interfaces are heavily C-oriented.

Examples:

```c
open()
read()
write()
close()
mmap()
ioctl()
socket()
fork()
exec()
```

Understanding C pointers and memory is essential for using these APIs correctly.

---

# 108. File Descriptors

Linux represents many resources with file descriptors:

```text
File
Socket
Pipe
Device
Event interface
```

Example:

```c
int fd = open("file", O_RDONLY);
```

Then:

```c
read(fd, ...);
close(fd);
```

---

# 109. `mmap`

`mmap()` maps memory into a process address space.

Possible uses:

```text
File mapping
Shared memory
Device memory
Anonymous memory
```

Conceptually:

```text
Process Virtual Address
        |
        v
      Mapping
        |
        v
Physical pages / file / device
```

---

# 110. `ioctl`

`ioctl()` provides device-specific control operations.

Typical:

```text
Application
    |
    v
ioctl()
    |
    v
Driver
    |
    v
Hardware
```

It is common in Linux device-driver interfaces.

---

# 111. ABI Basics

ABI means:

> Application Binary Interface.

It defines binary-level conventions such as:

```text
Calling convention
Register usage
Stack layout
Argument passing
Return values
Data layout
Alignment
Symbol conventions
```

ABI knowledge matters for:

```text
C/C++ interoperability
Assembly interaction
Debugging
Compiler behavior
Kernel/userspace interfaces
```

---

# 112. Function Calling

Conceptually:

```text
Caller
  |
  +-- arguments
  |
  v
Function
  |
  +-- return value
  |
  v
Caller
```

Actual argument passing may use:

```text
Registers
Stack
```

depending on the ABI and target architecture.

---

# 113. Calling Convention

Different architectures use different ABIs.

Examples:

```text
x86-64 System V ABI
AArch64 ABI
```

You should know the concept rather than memorize every register unless the role specifically requires it.

---

# 114. Debugging C

Typical workflow:

```text
Reproduce
   ↓
Collect evidence
   ↓
Find failing thread/function
   ↓
Inspect stack
   ↓
Inspect variables
   ↓
Check memory
   ↓
Identify root cause
   ↓
Fix
   ↓
Add regression test
```

---

# 115. GDB

Important commands:

```bash
gdb ./program
```

Inside GDB:

```text
break
run
continue
next
step
finish
print
display
backtrace
frame
info locals
info registers
watch
x
```

---

# 116. Breakpoint

```text
break function_name
```

or:

```text
break file.c:100
```

Then:

```text
run
```

Execution stops there.

---

# 117. Backtrace

When a crash occurs:

```text
bt
```

shows the call stack.

Example:

```text
main
 ↓
process
 ↓
parse
 ↓
memcpy
```

This helps identify where the crash occurred.

---

# 118. Core Dump

A core dump captures process state after a crash.

Typical workflow:

```text
Crash
 ↓
core file
 ↓
gdb executable core
 ↓
bt
 ↓
inspect frames
```

---

# 119. Sanitizers

Important tools:

```text
AddressSanitizer
UndefinedBehaviorSanitizer
ThreadSanitizer
LeakSanitizer
```

Typical compilation:

```bash
gcc -fsanitize=address -g program.c
```

Sanitizers can detect many classes of bugs much earlier than traditional debugging.

---

# 120. AddressSanitizer

ASan can detect issues such as:

```text
Heap buffer overflow
Stack buffer overflow
Use-after-free
Use-after-scope
Some memory leaks depending on configuration
```

---

# 121. UndefinedBehaviorSanitizer

UBSan detects various forms of undefined or invalid behavior, such as:

```text
Invalid shifts
Certain signed overflow cases
Invalid casts
Out-of-range operations
```

Exact checks depend on compiler/runtime options.

---

# 122. ThreadSanitizer

TSan detects many data-race problems in multithreaded programs.

Conceptually:

```text
Thread A
   |
   +-- shared x

Thread B
   |
   +-- shared x

       ↓

ThreadSanitizer
       ↓
Possible data race
```

---

# 123. Performance

Performance depends on:

```text
Algorithm
Memory access
Cache behavior
Branching
CPU utilization
Lock contention
I/O
System calls
Allocation
Data layout
```

Do not optimize blindly.

First:

```text
Measure
   ↓
Identify bottleneck
   ↓
Optimize
   ↓
Measure again
```

---

# 124. Cache Awareness

Modern CPUs have caches:

```text
CPU
 |
 +-- L1
 |
 +-- L2
 |
 +-- L3
 |
 +-- RAM
```

Accessing memory with good locality can improve performance.

---

# 125. Spatial Locality

If you access:

```text
a[0]
a[1]
a[2]
a[3]
```

the CPU may benefit because nearby data can be fetched together.

---

# 126. False Sharing

Two threads modify different variables that happen to occupy the same cache line.

```text
Cache Line
+--------------------------+
| Thread A data | Thread B |
+--------------------------+
```

This can cause cache-line bouncing and performance degradation.

---

# 127. Branch Prediction

Modern CPUs predict branches.

Code with predictable branches can be faster than code with highly unpredictable branches.

But:

> Do not manually optimize branches without measuring.

---

# 128. Data-Oriented Design

Performance can improve by organizing data for efficient access.

Array of structures:

```c
struct Point
{
    float x;
    float y;
};

struct Point points[N];
```

Structure of arrays:

```text
x[N]
y[N]
```

Which is better depends on the access pattern.

---

# 129. Allocation Performance

Frequent:

```text
malloc()
free()
```

can become expensive or cause fragmentation.

Alternatives can include:

```text
Object pools
Slabs
Arena allocators
Static allocation
Per-thread caches
```

depending on the application.

---

# 130. Embedded Memory Strategy

Embedded systems may prefer:

```text
Static allocation
Fixed-size buffers
Memory pools
Deterministic allocation
```

especially when:

```text
Memory is limited
Real-time behavior matters
Fragmentation is unacceptable
```

---

# 131. Defensive C

Good practices:

```text
Check pointers
Check allocation failures
Validate lengths
Validate input
Avoid unchecked arithmetic
Avoid unsafe string handling
Define ownership
Minimize global state
Use const correctly
Use fixed-width integers where appropriate
```

---

# 132. Error Handling

Prefer explicit error handling.

Example:

```c
int fd = open(...);

if (fd < 0)
{
    return -1;
}
```

Linux APIs often communicate errors through:

```text
Return values
errno
```

Know which convention each API uses.

---

# 133. Resource Cleanup

Typical pattern:

```text
Acquire
   ↓
Use
   ↓
Cleanup
```

For multiple resources:

```text
resource A
resource B
resource C
```

Failure paths must release already-acquired resources.

In C, `goto cleanup` is often a clean and accepted kernel/embedded pattern.

---

# 134. Cleanup Pattern

Example:

```c
int ret = -1;

a = acquire_a();
if (!a)
    goto out;

b = acquire_b();
if (!b)
    goto free_a;

ret = 0;

free_b:
    release_b(b);

free_a:
    release_a(a);

out:
    return ret;
```

The exact labels depend on resource ownership.

---

# 135. State Machine Pattern

Embedded software often uses:

```c
switch (state)
{
case STATE_IDLE:
    ...
    break;

case STATE_RUNNING:
    ...
    break;

case STATE_ERROR:
    ...
    break;
}
```

Useful for:

```text
Protocols
Drivers
Firmware
Connection management
Device states
```

---

# 136. Ring Buffer

A ring buffer is common in:

```text
Drivers
UART
Networking
Audio
Logging
Producer/consumer systems
```

Conceptually:

```text
        head
         ↓
+---+---+---+---+---+
|   |   |   |   |   |
+---+---+---+---+---+
             ↑
            tail
```

Important considerations:

```text
Wrap-around
Full/empty distinction
Concurrency
Memory ordering
Ownership
```

---

# 137. Producer / Consumer

```text
Producer
   |
   v
+---------+
| Buffer  |
+---------+
   |
   v
Consumer
```

Synchronization can involve:

```text
Mutex
Atomic
Semaphore
Condition variable
Lock-free algorithm
```

depending on requirements.

---

# 138. Common Senior C Interview Traps

Know these extremely well:

```text
Array vs pointer
const pointer variations
volatile vs atomic
static meaning
extern
sizeof array vs pointer
struct padding
alignment
endianness
signed/unsigned conversion
integer promotion
pointer arithmetic
function pointers
malloc/realloc
memcpy vs memmove
undefined behavior
strict aliasing
use-after-free
double free
memory leaks
buffer overflow
```

---

# 139. Interview Question: Array vs Pointer

Question:

```c
int a[10];
int *p = a;
```

Difference:

```text
a
→ array object

p
→ pointer object
```

In many expressions:

```text
a → &a[0]
```

but:

```c
sizeof(a)
```

does not equal:

```c
sizeof(p)
```

---

# 140. Interview Question: `const`

Explain:

```c
const int *p;
```

Answer:

```text
Cannot modify int through p.
```

Explain:

```c
int *const p;
```

Answer:

```text
p cannot point to another object.
```

---

# 141. Interview Question: `volatile`

Answer:

```text
volatile tells the compiler that accesses to the object are observable
and must not be optimized away or merged inappropriately.
```

Common uses:

```text
MMIO
Hardware registers
Certain asynchronous signal-related cases
```

But:

```text
volatile != atomic
volatile != mutex
volatile != memory barrier
```

---

# 142. Interview Question: `static`

At file scope:

```text
Internal linkage
```

Inside function:

```text
Static storage duration
```

This distinction is frequently tested.

---

# 143. Interview Question: `malloc` vs `calloc`

```text
malloc
    → allocates bytes
    → contents indeterminate

calloc
    → allocates an array-like region
    → initializes allocated bytes to zero
```

---

# 144. Interview Question: `malloc` vs `realloc`

`malloc`:

```text
Creates a new allocation.
```

`realloc`:

```text
Attempts to resize an existing allocation.
```

The allocation may move.

Therefore old pointers into the allocation can become invalid after a successful move.

---

# 145. Interview Question: `memcpy` vs `memmove`

```text
memcpy
    → source/destination must not overlap

memmove
    → overlap supported
```

---

# 146. Interview Question: Why Structure Padding?

Because CPUs/ABIs often require or benefit from aligned accesses.

Padding:

```text
Improves alignment
```

but increases:

```text
Memory footprint
```

---

# 147. Interview Question: Why Does `sizeof(struct)` Include Padding?

Because structure size is typically rounded so that elements of an array of that structure keep each member correctly aligned.

Example:

```c
struct S
{
    char c;
    int x;
};
```

If `sizeof(struct S)` were not suitably aligned, `array[1].x` could be misaligned.

---

# 148. Interview Question: Endianness

Given:

```text
0x12345678
```

Little endian:

```text
78 56 34 12
```

Big endian:

```text
12 34 56 78
```

Important for:

```text
Networking
File formats
Hardware registers
Binary protocols
Cross-platform data
```

---

# 149. Interview Question: Why Is Signed Overflow Dangerous?

Because signed integer overflow is undefined behavior.

The compiler can assume it does not happen and optimize accordingly.

Do not rely on wraparound for signed integers.

---

# 150. Interview Question: Why Is This Dangerous?

```c
int x = 10;

printf("%d\n", x++ + ++x);
```

The expression involves problematic multiple modifications/evaluation rules and should not be written.

General rule:

> Avoid complicated expressions with multiple side effects on the same scalar object.

---

# 151. Interview Question: What Is a Dangling Pointer?

A pointer whose referenced object's lifetime has ended.

Example:

```c
int *p = malloc(sizeof(*p));

free(p);
```

Now:

```text
p → dangling pointer
```

---

# 152. Interview Question: What Is a Memory Leak?

Allocated memory becomes unreachable without being released.

```text
malloc
  ↓
pointer lost
  ↓
cannot free
```

---

# 153. Interview Question: What Is Use-After-Free?

```text
allocate
 ↓
free
 ↓
access freed object
```

It is undefined behavior.

---

# 154. Interview Question: Why Is `volatile` Not Enough for Threads?

Consider:

```c
volatile int counter;
```

Two threads can still perform:

```text
read
modify
write
```

concurrently.

`volatile` does not make this sequence atomic.

Use:

```text
atomic
mutex
other synchronization
```

as appropriate.

---

# 155. Interview Question: What Happens During a Function Call?

Conceptually:

```text
Caller
   |
   +-- arguments
   |
   v
Calling convention
   |
   v
Callee
   |
   +-- local state
   |
   +-- return value
   |
   v
Caller
```

Actual implementation depends on:

```text
Architecture
ABI
Compiler
Optimization
```

---

# 156. Interview Question: Why Use Function Pointers?

Because they allow runtime selection of behavior.

Examples:

```text
Callbacks
Drivers
Interrupt dispatch
State machines
Protocol handlers
Operations tables
```

---

# 157. Interview Question: Why Use `uint32_t`?

When exact-width representation matters.

Example:

```c
uint32_t register_value;
```

This is preferable to assuming:

```text
unsigned int == 32 bits
```

on every platform.

---

# 158. Interview Question: How Would You Design a Driver Interface?

Think:

```text
Application
    |
    v
Stable API
    |
    v
Kernel Driver
    |
    v
Hardware
```

Questions:

```text
Who owns buffers?
Who allocates?
Blocking or non-blocking?
What happens on timeout?
How are errors returned?
How is concurrency handled?
How are interrupts handled?
How is DMA synchronized?
```

---

# 159. Interview Question: How Would You Debug Random Memory Corruption?

Start with:

```text
1. Reproduce
2. Enable ASan if possible
3. Enable UBSan
4. Check buffer boundaries
5. Check lifetime
6. Check use-after-free
7. Check double free
8. Check data races
9. Inspect core dumps
10. Use watchpoints
11. Check DMA/hardware interaction
12. Check stack corruption
```

---

# 160. Interview Question: How Would You Debug a Crash That Happens Only in Release?

Suspect:

```text
Optimization-sensitive UB
Uninitialized data
Race condition
Memory corruption
Strict-aliasing violation
Lifetime bug
Timing dependency
Compiler/ABI issue
```

Useful tools:

```text
GDB
ASan
UBSan
TSan
Core dump
Compiler warnings
Disassembly
```

---

# 161. Compiler Warnings

Use aggressive warnings where practical:

```bash
gcc -Wall -Wextra -Wpedantic
```

Depending on project/toolchain, additional warnings can be valuable.

Warnings are one of the cheapest ways to catch bugs early.

---

# 162. Static Analysis

Useful categories:

```text
Null dereference
Resource leaks
Uninitialized variables
Dead code
Buffer errors
Concurrency issues
API misuse
```

Tools vary by environment.

---

# 163. C Coding Principles

Senior-level C should emphasize:

```text
Clear ownership
Explicit lifetime
Simple control flow
Small functions
Defensive validation
Correct error handling
Minimal global state
Well-defined interfaces
Predictable memory usage
Measured performance
```

---

# 164. C + Linux + Embedded Relationship

Remember this chain:

```text
C
 |
 v
Memory
 |
 v
Pointers
 |
 v
Virtual Address
 |
 v
Linux Kernel
 |
 v
Driver
 |
 v
MMIO / DMA
 |
 v
Hardware
```

This is why C knowledge matters so much in embedded Linux.

---

# 165. C + Networking Relationship

```text
C Application
      |
      v
socket()
      |
      v
TCP / UDP
      |
      v
Linux Network Stack
      |
      v
Driver
      |
      v
DMA
      |
      v
NIC
```

Understanding both C and Networking lets you debug across the entire stack.

---

# 166. C + Linux Interview Mental Model

When you see:

```c
char *p;
```

ask:

```text
Where does p live?
What does p point to?
Who owns the memory?
How long is it valid?
Is it aligned?
Can it be NULL?
Can another thread modify it?
Is the pointed memory writable?
```

This is senior-level C thinking.

---

# 167. C + Embedded Interview Mental Model

When you see:

```c
volatile uint32_t *reg;
```

ask:

```text
What address?
What hardware block?
Read or write?
Alignment?
Access width?
Side effects?
Ordering?
Interrupt interaction?
Concurrency?
Cache/DMA interaction?
```

---

# 168. Final C Mental Model

Remember:

```text
                    C PROGRAM
                        |
        +---------------+---------------+
        |               |               |
      CODE            DATA           MEMORY
        |               |               |
      Functions      Globals        Pointers
        |               |               |
        +---------------+---------------+
                        |
                        v
                    COMPILER
                        |
                        v
                      ABI
                        |
                        v
                       CPU
                        |
                        v
                    MEMORY / I/O
                        |
                        v
                     HARDWARE
```

---

# 169. Senior C Master Flow

For any C bug, reason through:

```text
Type
 ↓
Object
 ↓
Address
 ↓
Lifetime
 ↓
Ownership
 ↓
Alignment
 ↓
Access
 ↓
Concurrency
 ↓
Compiler
 ↓
ABI
 ↓
Hardware
```

This mental model is more valuable than memorizing hundreds of C functions.

---

# 170. Final Interview Checklist

## C Fundamentals

```text
[ ] Data types
[ ] sizeof
[ ] Scope
[ ] Lifetime
[ ] Linkage
[ ] static
[ ] extern
[ ] const
[ ] volatile
[ ] restrict
```

## Pointers

```text
[ ] Pointer basics
[ ] NULL
[ ] Pointer arithmetic
[ ] Pointer to pointer
[ ] Function pointers
[ ] Callbacks
[ ] Array vs pointer
[ ] const pointer combinations
```

## Memory

```text
[ ] Stack
[ ] Heap
[ ] malloc
[ ] calloc
[ ] realloc
[ ] free
[ ] Memory leaks
[ ] Dangling pointers
[ ] Use-after-free
[ ] Double free
[ ] Buffer overflow
```

## Data Representation

```text
[ ] Structures
[ ] Unions
[ ] Enums
[ ] typedef
[ ] Padding
[ ] Alignment
[ ] Endianness
[ ] Integer promotions
[ ] Signed/unsigned conversion
```

## Bit Manipulation

```text
[ ] Set bit
[ ] Clear bit
[ ] Toggle bit
[ ] Test bit
[ ] Extract field
[ ] Insert field
[ ] Power of two
[ ] Lowest set bit
[ ] Register manipulation
```

## Compilation

```text
[ ] Preprocessor
[ ] Translation unit
[ ] Compilation
[ ] Assembly
[ ] Object files
[ ] Linking
[ ] Static library
[ ] Shared library
[ ] Symbols
[ ] ABI
```

## Undefined Behavior

```text
[ ] Signed overflow
[ ] Out-of-bounds access
[ ] Use-after-free
[ ] Double free
[ ] Invalid pointer access
[ ] Strict aliasing
[ ] Invalid shifts
[ ] Lifetime violations
```

## Linux / Embedded

```text
[ ] System calls
[ ] File descriptors
[ ] mmap
[ ] ioctl
[ ] MMIO
[ ] Interrupts
[ ] DMA
[ ] volatile
[ ] Atomics
[ ] Memory ordering
[ ] Driver interfaces
```

## Debugging

```text
[ ] GDB
[ ] Core dumps
[ ] Backtrace
[ ] Watchpoints
[ ] ASan
[ ] UBSan
[ ] TSan
[ ] Compiler warnings
[ ] Static analysis
```

## Performance

```text
[ ] Cache
[ ] Locality
[ ] False sharing
[ ] Branch prediction
[ ] Allocation overhead
[ ] Memory pools
[ ] Data layout
[ ] Measure before optimizing
```

---

# 171. Final 20 Things You Must Be Able to Explain

For a senior C interview, you should be able to explain these without notes:

```text
1.  Array vs pointer
2.  Pointer arithmetic
3.  Pointer to pointer
4.  Function pointer/callback
5.  const variations
6.  volatile
7.  volatile vs atomic
8.  static
9.  extern
10. Structure padding/alignment
11. Endianness
12. malloc/calloc/realloc/free
13. memcpy vs memmove
14. Undefined behavior
15. Strict aliasing
16. Memory leak/use-after-free
17. Signed vs unsigned
18. Compilation/linking
19. MMIO/DMA/interrupt interaction
20. How to debug a difficult C crash
```

---

# 172. Final Dependency Chain

The most important C dependency chain is:

```text
C Syntax
   ↓
Types
   ↓
Objects
   ↓
Pointers
   ↓
Memory
   ↓
Lifetime
   ↓
Ownership
   ↓
Alignment
   ↓
Data Representation
   ↓
Compiler
   ↓
ABI
   ↓
Linux
   ↓
Driver
   ↓
Hardware
```

For embedded Linux:

```text
C
 ↓
Pointer
 ↓
Virtual Address
 ↓
MMU
 ↓
Kernel
 ↓
Driver
 ↓
MMIO / DMA
 ↓
Interrupt
 ↓
Hardware
```

For concurrency:

```text
C
 ↓
Shared Memory
 ↓
Multiple Threads
 ↓
Race
 ↓
Atomic / Mutex
 ↓
Memory Ordering
 ↓
Correct Program
```

For debugging:

```text
Crash
 ↓
Core
 ↓
GDB
 ↓
Stack
 ↓
Memory
 ↓
Lifetime
 ↓
Ownership
 ↓
Concurrency
 ↓
Root Cause
```

---

# Conclusion

For senior C/Linux/embedded interviews, the objective is not to memorize the C standard.

The objective is to understand:

```text
How C represents data
        ↓
How C accesses memory
        ↓
How pointers represent addresses
        ↓
How objects live and die
        ↓
How the compiler transforms code
        ↓
How the ABI executes functions
        ↓
How C interacts with Linux
        ↓
How Linux interacts with hardware
```

If you can reason confidently through those layers, you have the C foundation expected for senior systems and embedded engineering interviews.
