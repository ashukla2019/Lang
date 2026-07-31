# C MASTER HANDBOOK

The goal is to understand:

```text
C
 ↓
Types
 ↓
Objects
 ↓
Pointers
 ↓
Memory
 ↓
Lifetime / Ownership
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

---

# TABLE OF CONTENTS

## Part 1 — C Fundamentals

1. C Program Structure
2. Compilation Pipeline
3. Translation Units
4. Data Types
5. Variables
6. Constants
7. Scope
8. Lifetime
9. Linkage
10. Storage Classes
11. Operators
12. Expressions
13. Control Flow
14. Functions
15. Parameter Passing

## Part 2 — Arrays and Strings

16. Arrays
17. Array vs Pointer
18. Multidimensional Arrays
19. Array Parameters
20. Character Arrays
21. C Strings
22. `sizeof` vs `strlen`
23. String Literals
24. String Copying
25. String Comparison
26. String Concatenation
27. String Searching
28. Safe String Handling
29. String Pitfalls
30. String Interview Problems

## Part 3 — Pointers

31. Pointer Fundamentals
32. Address and Dereference
33. Pointer Types
34. Pointer Arithmetic
35. Pointer and Arrays
36. Pointer to Pointer
37. `void *`
38. NULL Pointers
39. Wild Pointers
40. Dangling Pointers
41. Pointer to Structure
42. Pointer to Array
43. Array of Pointers
44. Function Pointers
45. Callback Functions
46. Function Pointer Tables
47. `const` and Pointers
48. `volatile` and Pointers
49. `restrict` and Pointers
50. Pointer Casting
51. Pointer and Integer Conversion
52. Pointer Alignment
53. Pointer Aliasing
54. Strict Aliasing
55. One-Past-the-End Pointer
56. Pointer Ownership
57. Pointer Lifetime
58. Dynamic 2D Arrays
59. Common Pointer Bugs
60. Pointer Interview Problems

## Part 4 — Structures, Unions and Enums

61. Structures
62. Structure Initialization
63. Structure Assignment
64. Structure Pointers
65. Nested Structures
66. Self-Referential Structures
67. Padding
68. Alignment
69. Structure Size
70. Packed Structures
71. Bit Fields
72. Unions
73. Tagged Unions
74. Enums
75. `typedef`

## Part 5 — Bit Manipulation

76. Binary and Hexadecimal
77. Bits and Bytes
78. Masks
79. Set a Bit
80. Clear a Bit
81. Toggle a Bit
82. Test a Bit
83. Extract a Field
84. Insert a Field
85. Shift Operations
86. Signed vs Unsigned Shifts
87. Logical vs Arithmetic Shift
88. Power of Two
89. Count Set Bits
90. Clear Lowest Set Bit
91. Find Lowest Set Bit
92. Odd / Even
93. Bit Reversal
94. Bit Rotation
95. XOR Tricks
96. Register Manipulation
97. Bit Manipulation and Endianness
98. Embedded Bit Problems
99. Bit Interview Problems

## Part 6 — Memory

100. Process Memory Layout
101. Stack
102. Heap
103. Static Storage
104. `.text`
105. `.rodata`
106. `.data`
107. `.bss`
108. `malloc`
109. `calloc`
110. `realloc`
111. `free`
112. Memory Ownership
113. Memory Leaks
114. Use-After-Free
115. Double Free
116. Buffer Overflow
117. Uninitialized Memory
118. Memory Alignment
119. Memory Corruption

## Part 7 — Type System

120. Type Conversions
121. Integer Promotions
122. Usual Arithmetic Conversions
123. Signed vs Unsigned
124. Integer Overflow
125. Narrowing
126. Explicit Casts
127. `sizeof`
128. `offsetof`
129. Fixed-Width Integer Types

## Part 8 — Qualifiers

130. `const`
131. `volatile`
132. `restrict`
133. `const volatile`
134. Qualifiers in Embedded C

## Part 9 — Preprocessor

135. `#include`
136. `#define`
137. Object-Like Macros
138. Function-Like Macros
139. Macro Parentheses
140. Macro Side Effects
141. Conditional Compilation
142. Include Guards
143. Macro vs Inline Function

## Part 10 — Compilation and Linking

144. Preprocessing
145. Compilation
146. Assembly
147. Object Files
148. Linking
149. Symbols
150. External Symbols
151. Internal Linkage
152. `static`
153. `extern`
154. Static Libraries
155. Shared Libraries
156. ABI Basics

## Part 11 — Undefined Behavior

157. What Is Undefined Behavior?
158. Signed Overflow
159. Out-of-Bounds Access
160. Invalid Pointer Dereference
161. Use-After-Free
162. Double Free
163. Invalid Shift
164. Strict Aliasing
165. Lifetime Violations
166. Unsequenced / Problematic Evaluation
167. Undefined Behavior and Optimization

## Part 12 — Embedded C

168. Memory-Mapped I/O
169. Hardware Registers
170. `volatile` Registers
171. Interrupts
172. ISR Design
173. Shared ISR Data
174. DMA
175. Alignment and DMA
176. Fixed-Width Types
177. Register Bit Manipulation
178. Ring Buffers
179. State Machines
180. Memory Pools

## Part 13 — Concurrency

181. Threads
182. Shared Memory
183. Race Conditions
184. Data Races
185. Atomic Operations
186. C11 Atomics
187. Memory Ordering
188. Mutex vs Atomic
189. Producer / Consumer
190. Lock-Free Basics

## Part 14 — Linux C

191. System Calls
192. File Descriptors
193. `open`
194. `read`
195. `write`
196. `close`
197. `mmap`
198. `ioctl`
199. `errno`
200. C and Linux Drivers

## Part 15 — Debugging

201. GDB
202. Breakpoints
203. Backtrace
204. Stack Inspection
205. Memory Inspection
206. Watchpoints
207. Core Dumps
208. ASan
209. UBSan
210. TSan
211. Static Analysis
212. Compiler Warnings

## Part 16 — Performance

213. Cache
214. Locality
215. False Sharing
216. Branch Prediction
217. Memory Allocation
218. Data Layout
219. Memory Pools
220. Performance Measurement

## Part 17 — Senior Interview Problems

221. Pointer Problems
222. String Problems
223. Bit Problems
224. Memory Problems
225. Structure Problems
226. Concurrency Problems
227. Embedded Problems
228. Debugging Problems

## Part 19 — Input Handling

229. Buffered stdio vs Raw Syscalls
230. `scanf` and `%s` Danger
231. `gets()` Removal
232. `fgets`
233. `getline`
234. `getchar` / `putchar` and EOF
235. `scanf` + `fgets` Buffering Gotcha
236. `fread` / `fwrite` for Binary Data
237. Buffering Modes
238. Partial Reads/Writes and `EINTR`

---

# PART 1 — C FUNDAMENTALS

# 1. C Program Structure

Typical C program:

```c
#include <stdio.h>

int main(void)
{
    printf("Hello\n");
    return 0;
}
```

Main components:

```text
Header
 ↓
Declarations
 ↓
Functions
 ↓
main()
```

---

# 2. Compilation Pipeline

The conceptual pipeline is:

```text
main.c
  |
  v
Preprocessor
  |
  v
Expanded C
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
main.o
  |
  v
Linker
  |
  v
Executable
```

Example:

```bash
gcc main.c -o main
```

---

# 3. Translation Unit

A translation unit is the source file after preprocessing, including the contents of included headers.

For:

```c
#include "foo.h"

int main(void)
{
}
```

the compiler sees approximately:

```text
foo.h contents
+
main.c contents
```

after preprocessing.

---

# 4. Data Types
# C Fundamental Data Types

# Integer Types

| Type | Typical Size (64-bit Linux) | Range (Signed) | Purpose |
|------|:---------------------------:|---------------:|---------|
| `char` | 1 byte | -128 to 127 | Character/small integer |
| `short` | 2 bytes | -32,768 to 32,767 | Small integer |
| `int` | 4 bytes | ±2.1 billion | General-purpose integer |
| `long` | 8 bytes (Linux), 4 bytes (Windows) | Platform-dependent | Large integer |
| `long long` | 8 bytes | ±9.22 × 10¹⁸ | Very large integer |

## char
Stores a single byte. It is an integer type.

```c
char ch = 'A';
char x = 65;
printf("%d\n", 'A'); // 65
printf("%c\n", 65);  // A
```

## short
Usually 2 bytes.

```c
short age = 25;
```

## int
General-purpose integer, usually 4 bytes.

```c
int count = 100;
```

## long
Platform-dependent (8 bytes on 64-bit Linux, 4 bytes on 64-bit Windows).

```c
long population = 8000000000L;
```

## long long
At least 64 bits.

```c
long long distance = 900000000000LL;
```

## Signed vs Unsigned

```c
unsigned int x = 4000000000U;
```

- Signed: negative and positive values.
- Unsigned: only non-negative values.

# Floating-Point Types

| Type | Typical Size | Precision | Purpose |
|------|:------------:|----------:|---------|
| `float` | 4 bytes | ~6–7 digits | Single precision |
| `double` | 8 bytes | ~15–16 digits | Double precision |
| `long double` | Usually 16 bytes | Platform-dependent | Extended precision |

## float

```c
float pi = 3.14f;
```

32-bit IEEE-754 floating-point.

## double

```c
double pi = 3.141592653589793;
```

64-bit floating-point with higher precision.

## long double

```c
long double value = 3.141592653589793238L;
```

Higher precision than `double` (implementation-dependent).

# void

Represents **no value** or **no type**.

## Function returning nothing

```c
void printMessage(void)
{
    printf("Hello\n");
}
```

## Function with no parameters

```c
void func(void)
{
}
```

## Generic Pointer

```c
int x = 10;
void *ptr = &x;

printf("%d\n", *(int *)ptr);
```

`void *` can point to any data type but must be cast before dereferencing.

# Memory Comparison

```text
char          : 1 byte
short         : 2 bytes
int           : 4 bytes
long          : 8 bytes (Linux)
long long     : 8 bytes
float         : 4 bytes
double        : 8 bytes
long double   : 16 bytes (typical)
```

# Check Sizes

```c
#include <stdio.h>

int main(void)
{
    printf("char        : %zu\n", sizeof(char));
    printf("short       : %zu\n", sizeof(short));
    printf("int         : %zu\n", sizeof(int));
    printf("long        : %zu\n", sizeof(long));
    printf("long long   : %zu\n", sizeof(long long));
    printf("float       : %zu\n", sizeof(float));
    printf("double      : %zu\n", sizeof(double));
    printf("long double : %zu\n", sizeof(long double));
    printf("void *      : %zu\n", sizeof(void *));

    return 0;
}
```

# Interview Tips

- `char` is an integer type occupying 1 byte.
- `int` is the default integer type.
- `long` is platform-dependent.
- `long long` is at least 64 bits.
- `float`, `double`, and `long double` provide increasing precision.
- `void` represents no value and `void *` is a generic pointer.
- Use `sizeof()` instead of assuming type sizes.
```

---

# 5. Variables

Example:

```c
int count = 10;
```

A variable/object has important properties:

```text
Type
Value
Address
Storage duration
Scope
Linkage
Alignment
Lifetime
```

Senior C questions frequently combine these concepts.

---

# 6. Scope

Scope determines where an identifier is visible.

Important scopes:

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

`y` exists only in the inner block.

---

# 7. Lifetime

Lifetime answers:

> When does the object exist?

Common categories:

```text
Automatic
Static
Allocated
```

Example:

```c
void f(void)
{
    int x;
}
```

`x` has automatic storage duration.

---

# 8. Linkage

Linkage answers:

> Does this declaration refer to an entity that can be shared across scopes/translation units?

Important:

```text
External linkage
Internal linkage
No linkage
```

---

# 9. Storage Classes

Important keywords:

```c
auto
static
extern
register
```

`static` is particularly important.

At file scope:

```c
static int counter;
```

means internal linkage.

Inside a function:

```c
static int counter;
```

means the object has static storage duration and retains its value between calls.

---

# 10. Functions

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

C passes function arguments by value.

To modify caller-owned data:

```c
void set_value(int *p)
{
    *p = 100;
}
```

---

# PART 2 — ARRAYS AND STRINGS

# 11. Arrays

```c
int a[5];
```

Memory is contiguous:

```text
a[0] a[1] a[2] a[3] a[4]
```

Elements have identical type.

---

# 12. Array Indexing

```c
a[i]
```

is defined in terms of pointer arithmetic as:

```c
*(a + i)
```

Therefore:

```c
a[3]
```

and:

```c
3[a]
```

are equivalent according to the language syntax.

Do not use the second form in production code; it is mainly an interview curiosity.

---

# 13. Array vs Pointer

These are fundamentally different:

```c
int a[10];
int *p;
```

`a` is an array object.

`p` is a pointer object.

For example:

```c
sizeof(a)
```

returns the size of the complete array.

But:

```c
sizeof(p)
```

returns the size of the pointer.

---

# 14. Array Decay

In many expressions:

```c
int a[10];
```

`a` converts to:

```c
&a[0]
```

Exceptions include important contexts such as:

```c
sizeof(a)
& a
```

and string literal initialization.

This is one of the most important array/pointer concepts.

---

# 15. Multidimensional Arrays

Example:

```c
int matrix[3][4];
```

Memory is contiguous in row-major order:

```text
row 0
  0 1 2 3

row 1
  0 1 2 3

row 2
  0 1 2 3
```

`matrix[i][j]` accesses the appropriate element.

---

# 16. Array Parameters

This:

```c
void process(int a[10]);
```

is adjusted to essentially:

```c
void process(int *a);
```

The function does not receive the array size automatically.

Therefore:

```c
void process(int *a, size_t n);
```

is usually clearer.

---

# 17. Character Arrays

```c
char s[6] = "hello";
```

Memory:

```text
'h'
'e'
'l'
'l'
'o'
'\0'
```

A C string requires a terminating null byte.

---

# 18. String Literal

```c
char *p = "hello";
```

The literal is not modifiable.

Do not do:

```c
p[0] = 'H';
```

That is undefined behavior.

Prefer:

```c
char p[] = "hello";
```

when a modifiable character array is required.

---

# 19. `char s[]` vs `char *s`

### Array

```c
char s[] = "hello";
```

Creates an array containing the characters.

### Pointer

```c
const char *s = "hello";
```

Points to a string literal.

Important:

```text
Array owns storage.
Pointer stores an address.
```

---

# 20. `sizeof` vs `strlen`

Example:

```c
char s[] = "hello";
```

Then:

```c
sizeof(s)
```

is:

```text
6
```

because the terminating `'\0'` is included.

But:

```c
strlen(s)
```

is:

```text
5
```

because `strlen` counts characters before the null terminator.

---

# 21. `strlen`

```c
size_t n = strlen(s);
```

Requirements:

* `s` must point to a valid null-terminated string.
* It scans until `'\0'`.

Complexity:

```text
O(n)
```

Calling `strlen()` repeatedly inside a loop can accidentally produce O(n²) behavior.

---

# 22. `strcpy`

```c
strcpy(dst, src);
```

Copies the source string including its null terminator.

The destination must be large enough.

Otherwise:

```text
Buffer overflow
```

---

# 23. `strncpy`

```c
strncpy(dst, src, n);
```

Important:

> `strncpy()` is not automatically a safe replacement for `strcpy()`.

If the source is at least `n` characters long, the destination may not be null-terminated.

---

# 24. `strcmp`

```c
strcmp(a, b);
```

Returns:

```text
< 0
= 0
> 0
```

Do not assume the exact non-zero value.

Correct usage:

```c
if (strcmp(a, b) == 0)
{
}
```

---

# 25. `strncmp`

```c
strncmp(a, b, n);
```

Compares at most `n` characters.

Still be careful about whether the inputs are valid strings and what semantics you actually need.

---

# 26. `strcat`

```c
strcat(dst, src);
```

Appends `src` to `dst`.

The destination must have enough space for:

```text
existing string
+
new string
+
'\0'
```

---

# 27. `strchr`

Find character:

```c
char *p = strchr(s, 'x');
```

Returns:

```text
pointer to first occurrence
```

or:

```text
NULL
```

---

# 28. `strstr`

Find substring:

```c
char *p = strstr(s, "abc");
```

Returns:

```text
pointer to first occurrence
```

or:

```text
NULL
```

---

# 29. `snprintf`

Prefer bounded formatting:

```c
snprintf(buf, sizeof(buf), "%s:%d", name, port);
```

Always consider:

```text
Buffer size
Return value
Truncation
Format correctness
```

---

# 30. Strings and Embedded Systems

Embedded systems frequently use fixed buffers:

```c
char buffer[128];
```

Important questions:

```text
What is maximum length?
Who owns buffer?
Is it null terminated?
Can input exceed capacity?
Can interrupt/DMA modify it?
```

---

# 31. String Pitfalls

Common bugs:

```text
Missing '\0'
Buffer overflow
Writing to string literal
Using uninitialized char array
Using strlen on non-string memory
Incorrect buffer size
Off-by-one errors
Overlapping copies
```

---

# 32. String Interview Problem

Reverse a string in-place:

```c
void reverse(char *s)
{
    size_t i = 0;
    size_t j = strlen(s);

    if (j == 0)
        return;

    j--;

    while (i < j)
    {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;

        i++;
        j--;
    }
}
```

Key concepts tested:

```text
Pointers
Arrays
Null termination
Indexing
Boundary conditions
```

---

# 20a. `memcpy` vs `memmove`

Both copy raw bytes, but they differ on overlapping regions.

```c
void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
```

`memcpy` assumes the regions do **not** overlap — behavior is undefined if
they do. `memmove` explicitly handles overlap correctly (conceptually by
copying through a temporary or choosing a safe copy direction).

```c
char buf[10] = "abcdefghi";

memmove(buf + 2, buf, 5);   /* safe: overlapping, shifts right */
memcpy(buf + 2, buf, 5);    /* undefined behavior: overlapping regions */
```

Rule of thumb: if source and destination might overlap and you aren't
certain, use `memmove`.

---

# 20b. `memcmp` vs `strcmp`

```c
int memcmp(const void *a, const void *b, size_t n);
int strcmp(const char *a, const char *b);
```

`strcmp` compares characters until it hits a `'\0'` in either string.
`memcmp` compares exactly `n` bytes regardless of embedded null bytes —
important when comparing fixed-size binary buffers, structs, or strings that
may legitimately contain `'\0'` before their logical end.

Using `strcmp` on non-null-terminated binary data can read past the buffer;
using `memcmp` on two strings of different lengths without checking lengths
first can miss the actual point of difference. Pick the one that matches
what you're actually comparing.

---

# 20c. Worked Implementations

`strlen`, `strcpy`, `strcmp`, `strstr` implemented from scratch:

```c
size_t my_strlen(const char *s)
{
    const char *p = s;

    while (*p != '\0')
        p++;

    return (size_t)(p - s);
}

char *my_strcpy(char *dst, const char *src)
{
    char *ret = dst;

    while ((*dst++ = *src++) != '\0')
        ;

    return ret;
}

int my_strcmp(const char *a, const char *b)
{
    while (*a != '\0' && *a == *b)
    {
        a++;
        b++;
    }

    return (unsigned char)*a - (unsigned char)*b;
}

char *my_strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0')
        return (char *)haystack;

    for (; *haystack != '\0'; haystack++)
    {
        const char *h = haystack;
        const char *n = needle;

        while (*h != '\0' && *n != '\0' && *h == *n)
        {
            h++;
            n++;
        }

        if (*n == '\0')
            return (char *)haystack;
    }

    return NULL;
}
```

---

# 20d. Safe Integer Parsing — `strtol` / `strtoul`

`atoi()` has no error reporting — it silently returns 0 on invalid input
with no way to distinguish that from an actual "0". Prefer `strtol`:

```c
#include <errno.h>
#include <stdlib.h>

char *endptr;
errno = 0;

long value = strtol(str, &endptr, 10);

if (endptr == str)
{
    /* no digits were parsed */
}
else if (errno == ERANGE)
{
    /* value out of range for long */
}
else if (*endptr != '\0')
{
    /* trailing non-numeric characters */
}
```

Three things to check: `endptr == str` (nothing parsed), `errno == ERANGE`
(overflow/underflow), and whatever `*endptr` points to (trailing garbage).
`strtoul` follows the same pattern for unsigned values.

---

# 20e. `strtok` and Why It's Dangerous

```c
char *token = strtok(str, ",");

while (token != NULL)
{
    token = strtok(NULL, ",");
}
```

Two problems senior interviewers expect you to know:

```text
1. It modifies the input string in place (writes '\0' at delimiters).
2. It keeps internal static state — not thread-safe, and calls cannot
   be interleaved/nested (e.g. tokenizing two strings at once breaks).
```

Prefer the reentrant `strtok_r` (POSIX) when thread-safety or nested
tokenizing is required — it takes an explicit `saveptr` argument instead of
hidden static state.

---

# 20f. `strdup`

```c
char *copy = strdup(original);

/* ... */

free(copy);
```

Allocates a new buffer and copies the string, including the terminator.
Not part of ISO C (it's POSIX), but extremely commonly used. Ownership is
clear: the caller receives allocated memory and is responsible for
`free()`-ing it — ties directly back to the ownership discipline in
Part 71/127.

---

# PART 3 — POINTERS

# 33. Pointer Fundamentals

```c
int x = 10;
int *p = &x;
```

Relationship:

```text
p
 |
 | address of
 v
 x
```

Dereference:

```c
*p
```

returns the object stored at that address.

---

# 34. Address Operator

```c
&x
```

returns the address of `x`.

Example:

```c
int x;
int *p = &x;
```

---

# 35. Dereference Operator

```c
*p
```

accesses the object pointed to by `p`.

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

# 36. Pointer Type Matters

```c
int *p;
char *q;
double *r;
```

Pointer arithmetic depends on the pointed-to type.

If:

```c
p + 1
```

then the address advances by:

```text
sizeof(*p)
```

---

# 37. Pointer Arithmetic

For:

```c
int a[5];
int *p = a;
```

then:

```c
p + 1
```

points to:

```c
a[1]
```

not one byte after `a[0]`.

---

# 38. Valid Pointer Arithmetic

Pointer arithmetic is defined within an array object and one-past-the-end.

Valid:

```c
int a[5];

int *p = a;
p++;
p += 3;
```

Valid one-past:

```c
int *end = a + 5;
```

But:

```c
*end
```

is invalid.

---

# 39. One-Past-the-End Pointer

For:

```c
int a[5];
```

valid pointer range for iteration:

```text
&a[0]
&a[1]
&a[2]
&a[3]
&a[4]
&a[5]  ← one-past
```

`&a[5]` can be used for comparison but not dereferenced.

Typical loop:

```c
for (int *p = a; p != a + 5; ++p)
{
}
```

---

# 40. Pointer Comparison

Pointers into the same array can be meaningfully ordered.

For unrelated objects, relational pointer comparisons are not generally meaningful/portable.

Do not write code based on assumptions such as:

```c
if (&a < &b)
```

for unrelated objects.

---

# 41. NULL Pointer

```c
int *p = NULL;
```

Means the pointer is not currently pointing to a valid object.

Check:

```c
if (p != NULL)
{
}
```

Never dereference:

```c
*p
```

when `p == NULL`.

---

# 42. NULL vs Wild Pointer

### NULL

Explicitly represents no valid target:

```c
int *p = NULL;
```

### Wild pointer

Uninitialized pointer:

```c
int *p;
```

Using `p` before assigning a valid value is dangerous.

---

# 43. Dangling Pointer

Example:

```c
int *p = malloc(sizeof(*p));

free(p);
```

Now `p` is dangling.

The pointer value may still exist, but the object lifetime has ended.

---

# 44. Use-After-Free

```c
free(p);

*p = 10;
```

Undefined behavior.

This can produce:

```text
Crash
Memory corruption
Security vulnerability
Random behavior
```

---

# 45. Pointer to Pointer

```c
int x = 10;
int *p = &x;
int **pp = &p;
```

Diagram:

```text
pp
 |
 v
 p
 |
 v
 x
```

Useful when a function must modify the caller's pointer.

---

# 46. Modifying a Pointer Through `T **`

Example:

```c
void allocate(int **p)
{
    *p = malloc(sizeof(**p));
}
```

Usage:

```c
int *p = NULL;

allocate(&p);
```

The function changes the caller's pointer.

---

# 47. `void *`

`void *` is a generic object pointer.

Example:

```c
int x = 10;

void *p = &x;
```

Before dereferencing, convert/access through an appropriate object pointer type.

Common use:

```text
malloc
Generic APIs
Callbacks
Containers
```

---

# 48. `void *` and Pointer Arithmetic

Standard C does not define arithmetic on `void *`.

Use:

```c
unsigned char *
char *
```

when byte-wise pointer arithmetic is required.

---

# 49. Pointer to Structure

```c
struct Device
{
    int id;
};

struct Device d;
struct Device *p = &d;
```

Access:

```c
p->id
```

Equivalent to:

```c
(*p).id
```

---

# 50. `.` vs `->`

Object:

```c
d.id
```

Pointer:

```c
p->id
```

`p->id` is equivalent to:

```c
(*p).id
```

---

# 51. Pointer to Array

Example:

```c
int a[4];

int (*p)[4] = &a;
```

`p` points to the entire array.

This is different from:

```c
int *p;
```

which points to an individual `int`.

---

# 52. Array of Pointers

```c
char *names[3];
```

This means:

```text
array
 |
 +-- pointer
 +-- pointer
 +-- pointer
```

Each pointer can point to a different string/object.

---

# 53. Pointer to Array vs Array of Pointers

Very common interview question.

```c
int (*p)[10];
```

means:

```text
pointer to array of 10 int
```

while:

```c
int *p[10];
```

means:

```text
array of 10 pointers to int
```

Parentheses matter.

---

# 54. Dynamic 2D Array — Single Allocation

For a matrix:

```c
int *matrix = malloc(rows * cols * sizeof(*matrix));
```

Access:

```c
matrix[i * cols + j]
```

Advantages:

```text
One allocation
Contiguous memory
Cache friendly
Simple ownership
```

---

# 55. Dynamic 2D Array — Pointer-to-VLA

For appropriate C versions/toolchains:

```c
int (*matrix)[cols] = malloc(rows * sizeof(*matrix));
```

Then:

```c
matrix[i][j]
```

This preserves natural 2D indexing.

---

# 56. Dynamic 2D Array — Array of Pointers

```c
int **matrix;
```

can be constructed as:

```text
matrix
 |
 +--> row 0
 +--> row 1
 +--> row 2
```

Each row can be separately allocated.

Advantages:

```text
Rows can have different sizes
```

Disadvantages:

```text
Multiple allocations
Fragmentation
Less locality
More complicated ownership
```

---

# 57. Function Pointer

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

---

# 58. Function Pointer Syntax

This:

```c
int (*fp)(int, int);
```

means:

```text
fp
 ↓
pointer
 ↓
function
 ↓
takes int, int
 ↓
returns int
```

Without parentheses:

```c
int *fp(int, int);
```

means a function returning `int *`.

---

# 59. Callback

```c
void process(int (*callback)(int))
{
    int result = callback(10);
}
```

Callbacks are common in:

```text
Drivers
Networking
State machines
Event systems
Libraries
Interrupt frameworks
```

---

# 60. Function Pointer Table

```c
typedef void (*handler_t)(void);

handler_t table[] =
{
    handler_a,
    handler_b,
    handler_c
};
```

Useful for dispatch:

```text
command
   ↓
index
   ↓
handler table
   ↓
function
```

---

# 61. `const` Pointer Cases

### Pointer to const

```c
const int *p;
```

Cannot modify the integer through `p`.

### Const pointer

```c
int *const p = &x;
```

Cannot change `p` to point somewhere else.

### Const pointer to const

```c
const int *const p = &x;
```

Neither can be modified through `p`.

---

# 62. All Important `const` Forms

```c
const int *p;
int const *p;
int *const p;
const int *const p;
```

Remember:

```text
const int *p
    → data const through p

int *const p
    → pointer const

const int *const p
    → both
```

---

# 63. `volatile` Pointer

```c
volatile uint32_t *reg;
```

Means accesses through `reg` are volatile accesses.

Common for:

```text
Hardware registers
MMIO
```

---

# 64. Pointer to Volatile vs Volatile Pointer

```c
volatile int *p;
```

The pointed-to object is volatile.

```c
int *volatile p;
```

The pointer object itself is volatile.

```c
volatile int *volatile p;
```

Both are volatile.

---

# 65. `restrict`

```c
void copy(int *restrict dst,
          const int *restrict src,
          size_t n);
```

`restrict` is a promise about aliasing used to enable optimization.

Violating the restrict contract can result in undefined behavior.

---

# 66. Pointer Casting

Example:

```c
void *p = ...;

int *ip = p;
```

For object pointers, C permits conversion between `void *` and object pointer types.

But arbitrary pointer casts can create:

```text
Alignment problems
Aliasing violations
Invalid access
Undefined behavior
```

A cast does not magically make an address valid for every type.

---

# 67. Pointer to Integer

Converting pointers to integers is implementation-defined or otherwise constrained by the implementation.

Use appropriate implementation-provided integer types when required, such as:

```c
uintptr_t
intptr_t
```

from `<stdint.h>`.

Do not casually assume:

```c
(int)p
```

is safe.

---

# 68. Alignment

Every object type may have alignment requirements.

Example:

```text
Address 0x1000
```

may be suitable for a 4-byte-aligned object.

An address such as:

```text
0x1001
```

may not be.

Misalignment can cause:

```text
Performance problems
Hardware faults
Undefined behavior
```

depending on the operation/platform.

---

# 69. Pointer Aliasing

Two pointers may refer to the same object:

```c
int x;

int *p = &x;
int *q = &x;
```

Now:

```text
p
 \
  → x
 /
q
```

The compiler must account for valid aliasing relationships.

---

# 70. Strict Aliasing

Do not assume this is valid:

```c
float f;

int *p = (int *)&f;

printf("%d", *p);
```

Accessing an object through an incompatible lvalue type can violate C's aliasing rules.

Potential result:

```text
Undefined behavior
```

Use `memcpy` for representation copying when appropriate.

---

# 71. Pointer Ownership

For every pointer in serious C code, ask:

```text
Who allocated?
Who owns?
Who can modify?
Who frees?
How long is it valid?
Can ownership transfer?
```

This is one of the most important senior-level C concepts.

---

# 72. Pointer Lifetime

A pointer's lifetime and the pointed object's lifetime are separate concepts.

Example:

```c
int *p = malloc(sizeof(*p));
```

After:

```c
free(p);
```

the pointer variable may still exist, but the allocated object does not.

Therefore:

```text
Pointer exists
≠
Pointed object exists
```

---

# 73. Common Pointer Bugs

Know these:

```text
NULL dereference
Uninitialized pointer
Dangling pointer
Use-after-free
Double free
Buffer overflow
Out-of-bounds pointer arithmetic
Invalid pointer cast
Wrong pointer type
Alignment violation
Strict-aliasing violation
Returning pointer to dead local object
```

---

# 74. Returning Address of Local Variable

Bad:

```c
int *get_value(void)
{
    int x = 10;
    return &x;
}
```

`x` ceases to exist when the function returns.

Returned pointer is invalid.

---

# 75. Pointer Interview Problem

Implement swap:

```c
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
```

Concepts:

```text
Address passing
Dereference
Caller modification
```

---

# 76. Pointer Interview Problem — Reverse Array

```c
void reverse(int *a, size_t n)
{
    if (n == 0)
        return;

    int *left = a;
    int *right = a + n - 1;

    while (left < right)
    {
        int tmp = *left;
        *left = *right;
        *right = tmp;

        ++left;
        --right;
    }
}
```

Tests:

```text
Pointer arithmetic
Boundary conditions
Array traversal
```

---

# 76a. `container_of`

One of the most common Linux kernel / driver interview questions.

Given a pointer to a member, recover a pointer to the containing structure.

```c
struct device
{
    int id;
    struct list_node node;
};

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))
```

Usage:

```c
struct list_node *n = get_node_from_list();

struct device *d = container_of(n, struct device, node);
```

Conceptually:

```text
struct device
 +-- id
 +-- node  <-- ptr points here
      |
      | subtract offsetof(device, node)
      v
struct device *  <-- recovered
```

This is how Linux implements intrusive linked lists (`list_head`), and why
`offsetof` (Part 7) matters beyond struct layout trivia.

---

# 76b. Reading Complex Pointer Declarations

Senior interviewers sometimes hand you a declaration and ask "what is this?"

Use the **right-left rule**: start at the identifier, alternate reading right
then left around parentheses/brackets.

```c
int *p;
```
→ `p` is a pointer to `int`

```c
int *p[10];
```
→ `p` is an array of 10 pointers to `int`

```c
int (*p)[10];
```
→ `p` is a pointer to an array of 10 `int`

```c
int (*f)(int);
```
→ `f` is a pointer to a function taking `int` returning `int`

```c
int (*(*f)(int))[10];
```
→ `f` is a pointer to a function taking `int`, returning a pointer to an
array of 10 `int`

Parentheses bind the `*` to the identifier first; without them, `[]` and `()`
bind tighter than `*`.

---

# 76c. Pointer Subtraction

Pointer arithmetic also works in reverse — subtracting two pointers into the
same array gives the number of elements between them, typed as `ptrdiff_t`.

```c
int a[10];

int *p = &a[7];
int *q = &a[2];

ptrdiff_t n = p - q;   /* 5 */
```

Valid only when both pointers point into the same array object (or one past
its end). Subtracting pointers into unrelated objects is undefined behavior,
just like relational comparison (Part 40).

---

# 76d. Opaque Pointers / Incomplete Types

A common C encapsulation pattern (used heavily in library and driver APIs):
expose only a pointer to an incomplete type in the header, and define the
real structure privately in the `.c` file.

Header:

```c
typedef struct device device_t;

device_t *device_create(void);
void device_destroy(device_t *d);
int device_get_id(device_t *d);
```

Source file:

```c
struct device
{
    int id;
    /* internal fields hidden from callers */
};
```

Callers can hold and pass `device_t *` freely but cannot see or depend on
its layout — the C equivalent of pImpl. This is how many kernel and
userspace libraries (e.g. `FILE *`) hide implementation details.

---

# 76e. Pointer Arithmetic Out-of-Bounds Without Dereference

A subtle point: forming an out-of-bounds pointer is undefined behavior even
if you never dereference it.

```c
int a[5];

int *p = a + 6;   /* already UB — more than one-past-the-end */
```

Only `a + 0` through `a + 5` (one-past-the-end) are valid pointer values for
a 5-element array. `a + 6` is invalid the moment it is *computed*, not just
when read.

---

# 76f. Function Pointers and `void *`

Standard C does not guarantee that a function pointer can be converted
to/from `void *` — object pointers and function pointers are not
interchangeable in strict ISO C.

```c
void *p = (void *)some_function;   /* not guaranteed portable in strict C */
```

POSIX explicitly relaxes this for APIs like `dlsym()`, which is why it works
in practice on Linux. Know the distinction: portable ISO C code should not
rely on it outside a POSIX context.

---

# 76g. Linked List Interview Problems — Worked

These are named in the problem list (Part 17); here they're implemented.

**Reverse a singly linked list:**

```c
struct Node
{
    int value;
    struct Node *next;
};

struct Node *reverse(struct Node *head)
{
    struct Node *prev = NULL;

    while (head != NULL)
    {
        struct Node *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;
}
```

**Detect a cycle (Floyd's tortoise and hare):**

```c
int has_cycle(struct Node *head)
{
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return 1;
    }

    return 0;
}
```

**Find the middle node (same slow/fast idea):**

```c
struct Node *find_middle(struct Node *head)
{
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
```

Concepts tested: pointer traversal, `NULL` checks, aliasing, two-pointer
technique.

---

# PART 4 — STRUCTURES, UNIONS AND ENUMS

# 77. Structure

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

---

# 78. Self-Referential Structure

```c
struct Node
{
    int value;
    struct Node *next;
};
```

Used for:

```text
Linked lists
Trees
Graphs
Queues
```

A structure cannot contain itself directly by value because that would require infinite size.

It can contain a pointer to itself.

---

# 79. Padding

Example:

```c
struct S
{
    char c;
    int x;
};
```

Possible memory:

```text
c
padding
padding
padding
x x x x
```

The exact layout is implementation-dependent.

---

# 80. Structure Alignment

Structure size often includes trailing padding so arrays of structures keep members aligned.

```c
struct S a[10];
```

Each element must begin at an appropriate alignment boundary.

---

# 81. Reordering Members

Compare conceptually:

```c
struct A
{
    char c;
    int x;
    char d;
};
```

versus:

```c
struct B
{
    int x;
    char c;
    char d;
};
```

The second may require less padding.

For memory-constrained systems, member ordering can matter.

---

# 82. Packed Structures

Packing may remove padding:

```text
Memory saving
```

but can introduce:

```text
Unaligned accesses
Performance cost
Hardware faults
```

Use packed layouts only when required by an external binary format/hardware specification.

---

# 83. Bit Fields

Example:

```c
struct Flags
{
    unsigned ready : 1;
    unsigned error : 1;
    unsigned mode  : 2;
};
```

Useful for compact representations.

But layout is implementation-dependent.

Do not blindly use C bit fields for portable network protocols or hardware registers without understanding the compiler/ABI rules.

---

# 84. Union

```c
union Data
{
    uint32_t u32;
    float f;
};
```

Members overlap in storage.

Size is sufficient for the largest member, subject to alignment.

---

# 85. Tagged Union

Common pattern:

```c
enum Type
{
    TYPE_INT,
    TYPE_FLOAT
};

struct Value
{
    enum Type type;

    union
    {
        int i;
        float f;
    } data;
};
```

The tag tells the program which union member is intended.

---

# PART 5 — BIT MANIPULATION

# 86. Binary Basics

Example:

```text
8-bit:
00000001
```

Bit positions:

```text
7 6 5 4 3 2 1 0
```

For:

```text
00001010
```

bits 3 and 1 are set.

---

# 87. Hexadecimal

Each hex digit represents 4 bits.

```text
0xF = 1111
0xA = 1010
0x5 = 0101
```

Therefore:

```text
0x12345678
```

contains 8 hex digits = 32 bits.

---

# 88. Set a Bit

```c
x |= (1U << n);
```

Example:

```c
x |= (1U << 3);
```

sets bit 3.

---

# 89. Clear a Bit

```c
x &= ~(1U << n);
```

Clears bit `n`.

---

# 90. Toggle a Bit

```c
x ^= (1U << n);
```

If bit was:

```text
0 → 1
1 → 0
```

---

# 91. Test a Bit

```c
if (x & (1U << n))
{
    /* bit set */
}
```

---

# 92. Create a Mask

For `n` bits:

```c
#define MASK(n) ((1U << (n)) - 1U)
```

But be careful when `n` reaches or exceeds the width of the type.

For a 32-bit value, blindly doing:

```c
1U << 32
```

is invalid.

---

# 93. Extract a Field

Suppose:

```text
field width = 4
shift = 8
```

Then:

```c
value = (x >> 8) & 0xF;
```

---

# 94. Insert a Field

```c
x = (x & ~(0xF << 8))
    | ((value & 0xF) << 8);
```

This:

```text
clears old field
+
inserts new field
```

---

# 95. Generic Field Macros

Conceptually:

```c
#define FIELD_MASK(width) \
    ((1U << (width)) - 1U)

#define FIELD_GET(x, shift, mask) \
    (((x) >> (shift)) & (mask))

#define FIELD_PREP(x, shift, mask) \
    (((x) & (mask)) << (shift))
```

In production, design these carefully for type width and shift edge cases.

---

# 96. Left Shift

```c
x << n
```

moves bits toward more significant positions.

Example:

```text
00000101
<< 1
00001010
```

For unsigned integers, shifts are well-defined when the shift count is within range, with discarded high bits.

---

# 97. Right Shift

```c
x >> n
```

moves bits toward less significant positions.

For unsigned types:

```text
logical right shift
```

zeros enter from the left.

---

# 98. Signed Right Shift

For negative signed values, right-shift behavior is implementation-defined.

Therefore for bit-level work prefer unsigned types when the desired semantics are bitwise.

---

# 99. Shift Count Rules

For an N-bit value, the shift count must satisfy:

```text
0 <= shift < N
```

Bad:

```c
uint32_t x = 1U << 32;
```

The shift count is invalid.

---

# 100. Always Prefer Unsigned for Bit Operations

Prefer:

```c
uint32_t x;
```

rather than:

```c
int x;
```

for register/mask manipulation.

Use:

```c
1U
```

or an appropriately typed constant.

---

# 101. Power of Two

For unsigned integer `x`:

```c
x != 0 && (x & (x - 1)) == 0
```

is true for powers of two.

Examples:

```text
1
2
4
8
16
32
```

---

# 102. Clear Lowest Set Bit

```c
x &= (x - 1);
```

Example:

```text
10110000
10101111
--------
10100000
```

It removes the lowest set bit.

---

# 103. Count Set Bits

Simple method:

```c
int count_bits(uint32_t x)
{
    int count = 0;

    while (x)
    {
        x &= x - 1;
        count++;
    }

    return count;
}
```

Complexity:

```text
O(number of set bits)
```

---

# 104. Lowest Set Bit

For unsigned `x`:

```c
x & (~x + 1U)
```

or commonly:

```c
x & -x
```

The latter requires careful consideration of integer types/conversions; for clean embedded code, use an explicitly unsigned expression.

---

# 105. Odd or Even

```c
if (x & 1U)
{
    /* odd */
}
else
{
    /* even */
}
```

---

# 106. Swap Using XOR

Classic interview trick:

```c
a ^= b;
b ^= a;
a ^= b;
```

But:

> Do not use this in normal production code.

A temporary variable is clearer and avoids aliasing problems when `a` and `b` refer to the same storage.

---

# 107. Reverse Bits

Conceptually:

```text
Input:
10110000

Output:
00001101
```

Can be implemented using:

```text
Loop
Masking
Shifting
Lookup tables
Architecture-specific instructions
```

For senior interviews, be able to implement the loop-based version.

---

# 108. Rotate Left

For an unsigned N-bit value:

```c
(x << n) | (x >> (N - n))
```

but only when the shift counts are valid.

For generic code, explicitly handle:

```text
n == 0
n >= N
```

or normalize the count.

---

# 109. Register Manipulation

Typical embedded register:

```text
31              16 15       8 7       4 3       0
+----------------+-----------+---------+---------+
|      field     |   mode    | status  | enable  |
+----------------+-----------+---------+---------+
```

Operations:

```text
Read register
 ↓
Mask
 ↓
Modify field
 ↓
Write register
```

---

# 110. Read-Modify-Write

Example:

```c
reg = (reg & ~MASK) | VALUE;
```

But hardware registers may have special semantics such as:

```text
Write-one-to-clear
Read-to-clear
Reserved bits
Side effects
```

Never assume every register is an ordinary RAM variable.

---

# 111. Atomic Register Modification

If a hardware register can be modified concurrently by hardware/other contexts, a simple:

```c
reg = reg | mask;
```

may not be sufficient.

Possible solutions depend on the hardware:

```text
Atomic CPU instruction
Interrupt masking
Lock
Dedicated SET/CLR register
Hardware atomic operation
```

---

# 112. Bit Manipulation Interview Problem

Set bits `[start, end]`.

Conceptually:

```c
mask = ((1U << width) - 1U) << start;
x |= mask;
```

Again, handle full-width fields carefully to avoid invalid shifts.

---

# 113. Bit Manipulation Interview Problem

Clear bits `[start, end]`:

```c
x &= ~mask;
```

---

# 114. Bit Manipulation Interview Problem

Extract bits `[start, end]`:

```c
field = (x >> start) & mask;
```

---

# 115. Bit Manipulation Interview Problem

Check whether exactly one bit is set:

```c
x != 0 && (x & (x - 1)) == 0
```

---

# 116. Bit Manipulation Interview Problem

Find position of lowest set bit.

Conceptually:

```text
x & -x
```

isolates it.

To find the index, use:

```text
ctz
```

when available, while ensuring the input is non-zero.

---

# 117. Endianness vs Bit Order

Important distinction:

```text
Endianness
    → byte ordering

Bit numbering
    → how bit positions are named/interpreted
```

Do not confuse:

```text
byte order
```

with:

```text
bit numbering
```

---

# 95a. Two's Complement

Signed integers on essentially all modern platforms use two's complement
representation.

To negate a value: invert all bits, then add 1.

```text
   00000101   (5)
   11111010   (invert)
 + 00000001
 ----------
   11111011   (-5)
```

This is why a single `0` bit pattern represents zero (no separate +0/−0),
and why the range is asymmetric: an 8-bit signed type covers `-128..127`,
not `-127..127`.

---

# 95b. Find the Single Unique Number (XOR)

Classic interview problem: every element in an array appears twice except
one — find it in O(n) time, O(1) space.

```c
int find_unique(int *a, size_t n)
{
    int result = 0;

    for (size_t i = 0; i < n; i++)
        result ^= a[i];

    return result;
}
```

Works because `x ^ x == 0` and `x ^ 0 == x` — every paired value cancels
out, leaving only the unpaired one. Directly builds on the XOR-swap trick
already in the handbook (Part 106).

---

# 95c. Detecting Opposite Signs with XOR

```c
int opposite_signs(int a, int b)
{
    return (a ^ b) < 0;
}
```

XOR of the sign bits leaves the result's sign bit set only when exactly one
of `a`/`b` is negative — avoids overflow-prone approaches like checking
`a * b < 0`.

---

# 95d. Runtime Endianness Check

Endianness is discussed conceptually earlier (Part 117) but never
demonstrated. The classic runtime check:

```c
int is_little_endian(void)
{
    uint32_t x = 1;
    unsigned char *p = (unsigned char *)&x;

    return p[0] == 1;
}
```

If the least-significant byte of `x` is stored first in memory, the machine
is little-endian.

---

# 95e. `htons` / `htonl` / `ntohs` / `ntohl`

Network protocols conventionally use big-endian ("network byte order").
POSIX provides conversion functions so code is portable across host
endianness:

```c
#include <arpa/inet.h>

uint16_t port_be  = htons(port_host);   /* host  -> network, 16-bit */
uint32_t addr_be  = htonl(addr_host);   /* host  -> network, 32-bit */

uint16_t port_host = ntohs(port_be);    /* network -> host, 16-bit */
uint32_t addr_host = ntohl(addr_be);    /* network -> host, 32-bit */
```

On a big-endian host these are no-ops; on little-endian hosts they byte-swap.
Always use them at protocol/wire boundaries rather than hand-rolled swaps.

---

# 95f. Compiler Bit-Counting Builtins

Set-bit counting is implemented by hand in Part 103. In practice, GCC/Clang
provide intrinsics that map to dedicated CPU instructions where available:

```c
__builtin_popcount(x);   /* number of set bits */
__builtin_clz(x);        /* count leading zeros (x must be non-zero) */
__builtin_ctz(x);        /* count trailing zeros (x must be non-zero) */
```

These are typically faster than a hand-written loop and are worth mentioning
in an interview even if you also show the manual version — it demonstrates
awareness of what the toolchain offers versus portable-C fallbacks.

---

# PART 6 — MEMORY

# 118. Typical Process Memory

Conceptually:

```text
High Address
+----------------+
| Stack          |
+----------------+
| mmap / libs    |
+----------------+
| Heap           |
+----------------+
| BSS            |
+----------------+
| Data           |
+----------------+
| Read-only data |
+----------------+
| Text           |
+----------------+
Low Address
```

Linux adds many mappings beyond this simplified model.

---

# 119. Stack

Typically contains:

```text
Local variables
Function call state
Saved registers
Arguments/return state depending on ABI
```

Stack size is limited.

---

# 120. Heap

Dynamic memory:

```c
malloc()
calloc()
realloc()
free()
```

Heap allocation has:

```text
Allocation overhead
Fragmentation concerns
Failure cases
Lifetime management
```

---

# 121. `malloc`

```c
int *p = malloc(10 * sizeof(*p));
```

Good pattern:

```c
T *p = malloc(n * sizeof(*p));
```

This avoids repeating the type name.

Always check failure when required.

---

# 122. `calloc`

```c
int *p = calloc(n, sizeof(*p));
```

Allocates space and initializes the allocated bytes to zero.

---

# 123. `realloc`

Dangerous:

```c
p = realloc(p, new_size);
```

because failure can lose the original pointer.

Better:

```c
void *tmp = realloc(p, new_size);

if (tmp != NULL)
    p = tmp;
```

---

# 124. `free`

```c
free(p);
```

After free:

```text
object lifetime ended
```

Do not access the object.

---

# 125. Memory Leak

```text
malloc
 ↓
pointer lost
 ↓
memory unreachable
```

Repeated leaks can eventually exhaust available memory.

---

# 126. Buffer Overflow

```c
char buf[8];

buf[8] = 'x';
```

Valid:

```text
buf[0] ... buf[7]
```

`buf[8]` is outside the array.

---

# 127. Memory Ownership

Senior design question:

> Who frees this object?

Every dynamically allocated object should have an understandable ownership model.

Examples:

```text
Caller owns
Callee owns
Shared ownership
Transferred ownership
Borrowed pointer
```

---

# 128. Ownership Transfer

Example:

```text
create()
 ↓
caller owns
 ↓
pass_to_queue()
 ↓
queue owns
 ↓
consumer
 ↓
free()
```

Explicit ownership prevents many memory bugs.

---

# PART 7 — TYPE SYSTEM

# 129. Integer Promotions

Types such as:

```text
char
short
```

are commonly promoted to `int` or `unsigned int` in expressions according to the integer-promotion rules.

This affects:

```text
Arithmetic
Comparisons
Bitwise operations
Function arguments
```

---

# 130. Signed vs Unsigned

Danger:

```c
int x = -1;
unsigned int y = 1;

if (x < y)
{
}
```

Conversions may convert `x` to unsigned.

This can produce surprising results.

---

# 131. Signed Overflow

This is undefined:

```c
int x = INT_MAX;
x++;
```

Do not depend on wraparound for signed integers.

---

# 132. Unsigned Overflow

Unsigned arithmetic wraps modulo 2^N.

For an 8-bit unsigned value:

```text
255 + 1 → 0
```

---

# 133. `sizeof`

`sizeof` returns a `size_t`.

Use:

```c
printf("%zu\n", sizeof(x));
```

Common mistake:

```c
sizeof(pointer)
```

does not give the size of the pointed object.

---

# 134. `offsetof`

From `<stddef.h>`:

```c
offsetof(struct_name, member)
```

gives the byte offset of a member within a structure, subject to the standard's constraints.

Important in:

```text
Data structures
Container patterns
Binary layouts
Kernel-style programming
```

---

# 135. Fixed-Width Types

Use:

```c
uint8_t
uint16_t
uint32_t
uint64_t
```

when exact width matters.

Also know:

```c
size_t
ptrdiff_t
uintptr_t
intptr_t
```

---

# PART 8 — QUALIFIERS

# 136. `const`

```c
const int x = 10;
```

Means the object is not modifiable through that identifier/access path.

---

# 137. `volatile`

Use when the value can change in ways relevant to the program outside ordinary C execution assumptions.

Common embedded example:

```c
volatile uint32_t *reg;
```

Remember:

```text
volatile != atomic
volatile != lock
volatile != memory barrier
```

---

# 138. `restrict`

Promises a particular non-aliasing relationship to help optimization.

Use only when the promise is true.

---

# 139. `const volatile`

Possible for hardware registers:

```c
const volatile uint32_t *status;
```

Meaning:

```text
volatile
    → hardware/other agent may change it

const
    → software should not write through this pointer
```

This is common for read-only hardware status registers.

---

# PART 9 — PREPROCESSOR

# 140. Macro

```c
#define MAX(a, b) ((a) > (b) ? (a) : (b))
```

But note:

```c
MAX(i++, j++)
```

can evaluate arguments multiple times.

Prefer functions/inline functions when possible.

---

# 141. Include Guards

```c
#ifndef DEVICE_H
#define DEVICE_H

void device_init(void);

#endif
```

Prevents duplicate declarations from repeated inclusion.

---

# 142. Conditional Compilation

```c
#ifdef DEBUG
    log_debug();
#endif
```

Common for:

```text
Platform code
Debug builds
Feature flags
Architecture-specific code
```

---

# PART 10 — COMPILATION AND LINKING

# 143. Object Files

Source:

```text
main.c
device.c
```

Compile:

```text
main.o
device.o
```

Link:

```text
application
```

---

# 144. Static Library

```text
libdevice.a
```

Archive of object files.

---

# 145. Shared Library

```text
libdevice.so
```

Loaded/shared at runtime.

Important concepts:

```text
Dynamic linker
Symbol resolution
ABI compatibility
Library versioning
```

---

# 146. `static` at File Scope

```c
static void helper(void)
{
}
```

The function has internal linkage.

Other translation units cannot directly reference it by external linkage.

---

# 147. `extern`

```c
extern int global;
```

Declares an object defined elsewhere.

---

# PART 11 — UNDEFINED BEHAVIOR

# 148. Undefined Behavior

Examples:

```text
Signed overflow
Out-of-bounds access
Invalid pointer dereference
Use-after-free
Double free
Invalid shift
Modifying string literal
Invalid lifetime access
Violating aliasing rules
```

Compiler is not required to preserve intuitive behavior after UB occurs.

---

# 149. Why UB Matters

Suppose:

```c
int x = INT_MAX;
x++;
```

A compiler may make optimization decisions based on the assumption that signed overflow does not happen.

Therefore:

```text
UB
 ↓
Compiler assumptions
 ↓
Unexpected optimized code
```

---

# PART 12 — EMBEDDED C

# 150. Memory-Mapped I/O

Hardware register:

```c
volatile uint32_t *reg =
    (volatile uint32_t *)ADDRESS;
```

Then:

```c
*reg = value;
```

Conceptually:

```text
CPU
 ↓
Virtual/physical mapping
 ↓
Hardware register
```

---

# 151. Hardware Register

Do not treat every register as ordinary RAM.

A register may have:

```text
Read side effects
Write side effects
Reserved bits
Write-one-to-clear
Read-only bits
Write-only bits
```

Always follow the hardware specification.

---

# 152. Interrupts

Conceptually:

```text
Hardware event
 ↓
Interrupt
 ↓
CPU
 ↓
ISR
```

ISR should usually be:

```text
Short
Fast
Predictable
Minimal
```

---

# 153. ISR and Shared Data

If:

```text
main code
     |
     v
shared variable
     ^
     |
    ISR
```

you need appropriate synchronization/atomicity.

`volatile` alone is not sufficient for general concurrency.

---

# 154. DMA

DMA:

```text
Device
  |
  | DMA
  v
Memory
```

CPU may not copy every byte.

Important concepts:

```text
Cache coherency
Memory barriers
Buffer ownership
Alignment
Mapping/unmapping
Synchronization
```

---

# 155. Ring Buffer

Typical:

```text
        head
          ↓
+---+---+---+---+---+
|   |   |   |   |   |
+---+---+---+---+---+
                  ↑
                 tail
```

Used in:

```text
UART
Networking
Drivers
Logging
Producer/consumer
```

---

# 156. State Machine

```c
switch (state)
{
case IDLE:
    ...
    break;

case RUNNING:
    ...
    break;

case ERROR:
    ...
    break;
}
```

Very common in embedded systems.

---

# PART 13 — CONCURRENCY

# 157. Race Condition

Outcome depends on timing/interleaving.

Example:

```text
Thread A       Thread B

read x
               read x
add 1
               add 1
write x
               write x
```

One update can be lost.

---

# 158. Data Race

Conflicting concurrent accesses to the same memory, at least one a write, without appropriate synchronization constitute a data race.

In C:

```text
Data race
   ↓
Undefined behavior
```

---

# 159. Atomic

C11:

```c
#include <stdatomic.h>

atomic_int counter;
```

Operation:

```c
atomic_fetch_add(&counter, 1);
```

Provides atomicity according to the selected memory-order semantics.

---

# 160. Atomic vs Volatile

```text
volatile
    → observable accesses / compiler behavior

atomic
    → atomic operations + synchronization semantics
```

Do not substitute one for the other.

---

# 161. Memory Ordering

Know:

```text
relaxed
acquire
release
acq_rel
seq_cst
```

At senior level, understand the concept:

```text
Atomicity
+
Visibility
+
Ordering
```

are separate concerns.

---

# PART 14 — LINUX C

# 162. File Descriptor

Linux APIs often represent resources using integer file descriptors:

```c
int fd = open(...);
```

Then:

```c
read(fd, ...);
write(fd, ...);
close(fd);
```

Resources can include:

```text
Files
Sockets
Pipes
Devices
```

---

# 163. `mmap`

Maps memory into a process address space.

Used for:

```text
Files
Shared memory
Device mappings
Anonymous memory
```

---

# 164. `ioctl`

Device-specific control interface:

```text
Application
 ↓
ioctl()
 ↓
Driver
 ↓
Hardware
```

Common in Linux device drivers.

---

# PART 15 — DEBUGGING

# 165. GDB

Important commands:

```text
break
run
continue
next
step
finish
print
backtrace
frame
info locals
info registers
watch
x
```

---

# 166. Backtrace

```text
bt
```

Example:

```text
main
 ↓
process
 ↓
parse
 ↓
driver
 ↓
crash
```

---

# 167. Core Dump

```text
Crash
 ↓
core
 ↓
gdb executable core
 ↓
bt
 ↓
inspect frame
 ↓
inspect memory
```

---

# 168. ASan

AddressSanitizer can detect many:

```text
Heap overflow
Stack overflow
Use-after-free
Use-after-scope
```

---

# 169. UBSan

Useful for detecting various undefined-behavior classes such as:

```text
Invalid shifts
Certain arithmetic issues
Invalid conversions
Other runtime UB checks
```

---

# 170. TSan

ThreadSanitizer detects many data-race problems.

---

# PART 16 — PERFORMANCE

# 171. Cache

Conceptual hierarchy:

```text
CPU
 ↓
L1
 ↓
L2
 ↓
L3
 ↓
RAM
```

Cache locality matters.

---

# 172. Spatial Locality

Accessing nearby memory:

```c
a[0]
a[1]
a[2]
a[3]
```

can benefit from cache lines.

---

# 173. False Sharing

Two threads modify separate variables located on the same cache line.

Result:

```text
Cache-line bouncing
Performance degradation
```

---

# 174. Memory Pools

Instead of:

```text
malloc
free
malloc
free
```

frequently, use a pool when appropriate:

```text
Pool
 |
 +-- object
 +-- object
 +-- object
```

Benefits:

```text
Predictable allocation
Reduced fragmentation
Lower allocation overhead
```

---

# PART 17 — SENIOR INTERVIEW PROBLEMS

## Pointer Problems

Be able to implement:

```text
Swap two values
Reverse array
Reverse linked list
Detect cycle
Find middle node
Implement memcpy
Implement memmove
Implement strlen
Implement strcpy
Implement strcmp
Dynamic 2D array
Callback-based dispatcher
```

---

## String Problems

Be able to solve:

```text
Reverse string
Check palindrome
Count characters
Remove duplicate characters
Find first non-repeating character
Implement strlen
Implement strcpy
Implement strcmp
Implement strstr
Tokenize a string
Parse integer safely
```

---

## Bit Problems

Be able to implement:

```text
Set bit
Clear bit
Toggle bit
Test bit
Extract field
Insert field
Count set bits
Check power of two
Find lowest set bit
Reverse bits
Rotate bits
Swap bits
Count transitions
Find missing number using XOR
Manipulate hardware register fields
```

---

## Memory Problems

Be able to explain:

```text
Memory leak
Use-after-free
Double free
Buffer overflow
Dangling pointer
Stack overflow
Heap fragmentation
Alignment fault
Invalid lifetime
```

---

## Embedded Problems

Be able to design:

```text
Ring buffer
State machine
Register interface
Interrupt-safe data structure
Producer/consumer queue
Memory pool
DMA buffer management
Callback framework
```

---

# PART 18 — MOST IMPORTANT INTERVIEW QUESTIONS

You should be able to answer these without notes.

## Pointers

```text
1. What is a pointer?
2. What is pointer arithmetic?
3. Array vs pointer?
4. Pointer to array vs array of pointers?
5. What is a double pointer?
6. Why use int **?
7. What is void *?
8. What is a dangling pointer?
9. What is a wild pointer?
10. What is a NULL pointer?
11. What is a function pointer?
12. What is a callback?
13. Explain all const-pointer combinations.
14. What is pointer aliasing?
15. What is strict aliasing?
16. What is one-past-the-end?
17. What happens when a pointer is freed?
18. Can a pointer be valid but the object invalid?
19. How do you allocate a 2D array?
20. Why is returning address of a local variable wrong?
```

---

# Strings

```text
21. char s[] vs char *s?
22. sizeof vs strlen?
23. Why is '\0' important?
24. Why is strcpy dangerous?
25. Why isn't strncpy automatically safe?
26. memcpy vs strcpy?
27. strcmp vs memcmp?
28. How do you safely format strings?
29. How do you reverse a string?
30. How do you detect buffer overflow?
```

---

# Bit Manipulation

```text
31. Set a bit.
32. Clear a bit.
33. Toggle a bit.
34. Test a bit.
35. Extract a field.
36. Insert a field.
37. Check power of two.
38. Count set bits.
39. Clear lowest set bit.
40. Find lowest set bit.
41. Reverse bits.
42. Rotate bits.
43. What is logical shift?
44. What is arithmetic shift?
45. Why prefer unsigned for bit operations?
46. What happens if shift count equals type width?
47. How do you modify a hardware register safely?
```

---

# Memory

```text
48. Stack vs heap?
49. malloc vs calloc?
50. realloc behavior?
51. What is a memory leak?
52. What is use-after-free?
53. What is double free?
54. What is buffer overflow?
55. What is alignment?
56. What is padding?
57. How do you debug memory corruption?
```

---

# Embedded

```text
58. Why volatile?
59. volatile vs atomic?
60. How does MMIO work?
61. How should an ISR be designed?
62. What is DMA?
63. What problems can DMA create?
64. How do you design a ring buffer?
65. How do you safely manipulate hardware registers?
```

---

# Concurrency

```text
66. Race condition?
67. Data race?
68. Atomic vs mutex?
69. What is memory ordering?
70. What is acquire/release?
71. What is false sharing?
```

---

# Compilation

```text
72. Preprocessor vs compiler?
73. What is a translation unit?
74. What is an object file?
75. What does linker do?
76. static vs extern?
77. Static library vs shared library?
78. What is ABI?
```

---

# PART 19 — INPUT HANDLING

# 200a. Buffered stdio vs Raw Syscalls

Part 14 covers `open`/`read`/`write`/`close` — raw, unbuffered Linux
syscalls. Most C programs instead go through the C library's buffered stdio
layer:

```text
Application
    ↓
stdio (FILE *, buffered)
    ↓
read() / write() syscalls
    ↓
Kernel
```

`FILE *` functions (`fgets`, `fread`, `fprintf`, ...) batch small reads/writes
into fewer syscalls for efficiency. Raw syscalls give you direct control but
no buffering — you manage that yourself.

---

# 200b. `scanf` and Why `%s` Is Dangerous

```c
char buf[16];

scanf("%s", buf);   /* no bound — classic buffer overflow */
```

`%s` with no width specifier reads until whitespace with **no bound
checking**, and will happily overflow `buf` given long enough input.

Safer:

```c
scanf("%15s", buf);   /* bounded to 15 chars + '\0' */
```

Still awkward for general line input — see `fgets`/`getline` below.
`scanf` is also error-prone for numeric input: on a match failure it leaves
the offending characters in the stream, which can desync subsequent calls.
Always check its return value (number of successful conversions).

---

# 200c. `gets()` — Removed From the Standard

```c
char buf[16];

gets(buf);   /* DO NOT USE — removed from C11 */
```

`gets()` has no way to bound how much it reads — it was formally removed
from the C standard in C11 specifically because it cannot be used safely.
If you see it in legacy code, replace it with `fgets`.

---

# 200d. `fgets` — the Safe Line-Reading Function

```c
char buf[128];

if (fgets(buf, sizeof(buf), stdin) != NULL)
{
    /* success */
}
```

Bounded by the buffer size, and null-terminates the result. Important
quirk: if a full line fits, `fgets` keeps the trailing `'\n'` in the buffer
— callers typically strip it:

```c
size_t len = strlen(buf);

if (len > 0 && buf[len - 1] == '\n')
    buf[len - 1] = '\0';
```

Also returns `NULL` on EOF or error before reading anything — always check
before using the buffer.

---

# 200e. `getline` — Dynamically Growing Input

POSIX `getline` reads an entire line of arbitrary length, growing the
buffer as needed:

```c
char *line = NULL;
size_t cap = 0;

ssize_t n = getline(&line, &cap, stdin);

if (n != -1)
{
    /* line contains n bytes, including '\n' if present */
}

free(line);
```

`line` may be reallocated internally — always pass its address and free it
yourself when done. Useful when input length isn't known ahead of time,
avoiding the fixed-buffer limitation of `fgets`.

---

# 200f. `getchar` / `putchar` and EOF

```c
int c;

while ((c = getchar()) != EOF)
{
    putchar(c);
}
```

`getchar()` returns `int`, not `char` — this matters because `EOF` is
typically `-1`, and on platforms where `char` is unsigned, comparing a
`char`-truncated value against `EOF` can never be true, causing an infinite
loop. Always store the return value in an `int` before comparing to `EOF`.

---

# 200g. The `scanf` + `fgets` Buffering Gotcha

A very common real bug:

```c
int n;
char name[64];

scanf("%d", &n);       /* leaves trailing '\n' in stdin */
fgets(name, sizeof(name), stdin);   /* reads the leftover '\n', not input */
```

`scanf("%d", ...)` consumes only the digits, leaving the newline in the
input buffer. The following `fgets` immediately reads that leftover `'\n'`
and returns an empty line instead of waiting for the user.

Fix: consume the rest of the line after `scanf`, or avoid mixing `scanf`
and `fgets` — prefer `fgets` + `sscanf`/`strtol` for all input instead:

```c
char line[64];

fgets(line, sizeof(line), stdin);
int n = (int)strtol(line, NULL, 10);
```

A related trap: calling `fflush(stdin)` to clear the leftover input is
undefined behavior per the C standard — `fflush` is only defined for output
streams. Some libraries (glibc) extend it to work on input, but portable
code should not rely on it.

---

# 200h. `fread` / `fwrite` for Binary Data

Text-oriented functions (`scanf`, `fgets`) are unsuitable for binary data.
Use `fread`/`fwrite` for fixed-size binary records:

```c
struct Record r;

size_t got = fread(&r, sizeof(r), 1, fp);

if (got != 1)
{
    /* short read / EOF / error */
}
```

Always check the returned element count, not just that the call "ran" —
a short read (fewer elements than requested) can mean EOF or a partial
record, and the struct's contents should not be trusted if the count is
short. Also be mindful of struct padding (Part 79) when reading/writing
binary records across different compilers/platforms.

---

# 200i. Buffering Modes

stdout's buffering mode depends on the destination: line-buffered when
connected to a terminal (flushes on `'\n'`), but fully buffered when
redirected to a file or pipe (flushes only when the buffer fills or the
program exits/flushes explicitly). This is the usual explanation for
"why didn't my printf show up" when output is piped.

```c
setvbuf(stdout, NULL, _IONBF, 0);   /* force unbuffered */
fflush(stdout);                      /* force a flush now (output only) */
```

---

# 200j. Partial Reads, Partial Writes, and `EINTR`

Raw `read()`/`write()` syscalls (Part 14) are not guaranteed to transfer the
full requested amount in one call, and can be interrupted by a signal
(`errno == EINTR`). Production code needs a retry loop:

```c
size_t total = 0;

while (total < len)
{
    ssize_t n = read(fd, buf + total, len - total);

    if (n < 0)
    {
        if (errno == EINTR)
            continue;

        /* real error */
        break;
    }

    if (n == 0)
        break;   /* EOF */

    total += (size_t)n;
}
```

Treating a single `read()`/`write()` call as "all or nothing" is a common
source of subtle bugs, especially with pipes, sockets, and large buffers.

---

# 200k. Input Handling Interview Questions

```text
1. Why is gets() unsafe, and what replaced it?
2. Why is scanf("%s", buf) dangerous?
3. What does fgets do with the trailing newline?
4. Why does getchar() return int, not char?
5. Why can mixing scanf and fgets cause a skipped read?
6. Why is fflush(stdin) undefined behavior?
7. When would you use getline over fgets?
8. Why check fread's return value instead of just calling it?
9. Buffered stdio vs raw read()/write() — what's the tradeoff?
10. Why is stdout sometimes delayed when piped to a file?
11. Why must read()/write() be called in a retry loop?
12. Why is strtok unsafe in multithreaded code, and what replaces it?
```

---

# DEBUGGING MENTAL MODEL

When a senior interviewer gives you a C crash, think:

```text
Crash
 |
 +-- Pointer?
 |     |
 |     +-- NULL?
 |     +-- Wild?
 |     +-- Dangling?
 |     +-- Wrong type?
 |
 +-- Memory?
 |     |
 |     +-- Overflow?
 |     +-- Underflow?
 |     +-- Use-after-free?
 |     +-- Double-free?
 |     +-- Alignment?
 |
 +-- Lifetime?
 |
 +-- Concurrency?
 |     |
 |     +-- Race?
 |     +-- Data race?
 |     +-- Atomicity?
 |
 +-- Compiler?
 |     |
 |     +-- UB?
 |     +-- Aliasing?
 |     +-- Optimization?
 |
 +-- Hardware?
       |
       +-- DMA?
       +-- MMIO?
       +-- Interrupt?
       +-- Cache?
```

---

# FINAL C MENTAL MODEL

For any C code, ask:

```text
1. What is the type?
2. Where does the object live?
3. What is its address?
4. Who owns it?
5. How long does it live?
6. Is the pointer valid?
7. Is the access aligned?
8. Can objects alias?
9. Can another thread/ISR modify it?
10. Is the operation atomic?
11. Is there undefined behavior?
12. What will the compiler generate?
13. What does the ABI require?
14. Does hardware interact with this memory?
```

---

# FINAL DEPENDENCY CHAIN

```text
C Syntax
   ↓
Types
   ↓
Objects
   ↓
Arrays
   ↓
Strings
   ↓
Pointers
   ↓
Pointer Arithmetic
   ↓
Memory
   ↓
Lifetime
   ↓
Ownership
   ↓
Alignment
   ↓
Structures
   ↓
Bit Manipulation
   ↓
Compiler
   ↓
ABI
   ↓
Linux
   ↓
Drivers
   ↓
MMIO / DMA
   ↓
Hardware
```

For concurrency:

```text
Shared Memory
   ↓
Multiple Execution Contexts
   ↓
Race
   ↓
Atomic / Lock
   ↓
Memory Ordering
   ↓
Correctness
```

For debugging:

```text
Failure
   ↓
Reproduce
   ↓
Evidence
   ↓
Stack
   ↓
Pointers
   ↓
Memory
   ↓
Lifetime
   ↓
Concurrency
   ↓
Hardware
   ↓
Root Cause
```

---

# FINAL CHECKLIST

Before considering C preparation complete:

```text
[ ] C fundamentals
[ ] Arrays
[ ] Strings
[ ] ALL major pointer cases
[ ] Pointer arithmetic
[ ] Double pointers
[ ] void *
[ ] Function pointers
[ ] Callbacks
[ ] Pointer-to-array
[ ] Array-of-pointers
[ ] const pointers
[ ] volatile pointers
[ ] restrict
[ ] Aliasing
[ ] Strict aliasing
[ ] Lifetime
[ ] Ownership
[ ] Structures
[ ] Unions
[ ] Padding
[ ] Alignment
[ ] Bit fields
[ ] Binary/hex
[ ] Set/clear/toggle/test bits
[ ] Field extraction/insertion
[ ] Shifts
[ ] Rotations
[ ] Bit counting
[ ] Register manipulation
[ ] Endianness
[ ] malloc/calloc/realloc/free
[ ] Memory leaks
[ ] UAF
[ ] Double free
[ ] Buffer overflow
[ ] UB
[ ] Type conversions
[ ] Integer promotions
[ ] Signed/unsigned
[ ] Preprocessor
[ ] Compilation
[ ] Linking
[ ] Static/shared libraries
[ ] ABI
[ ] MMIO
[ ] Interrupts
[ ] DMA
[ ] Atomics
[ ] Memory ordering
[ ] Linux system calls
[ ] GDB
[ ] Core dumps
[ ] ASan
[ ] UBSan
[ ] TSan
[ ] Cache
[ ] False sharing
[ ] Senior C coding problems
[ ] container_of
[ ] Reading complex pointer declarations (right-left rule)
[ ] Pointer subtraction / ptrdiff_t
[ ] Opaque pointers / incomplete types
[ ] Pointer arithmetic UB without dereference
[ ] Function pointer <-> void* portability
[ ] Reverse / cycle-detect / find-middle on a linked list (implemented)
[ ] Two's complement
[ ] XOR: find unique element, opposite-sign check
[ ] Runtime endianness check
[ ] htons/htonl/ntohs/ntohl
[ ] __builtin_popcount/clz/ctz
[ ] memcpy vs memmove
[ ] memcmp vs strcmp
[ ] strlen/strcpy/strcmp/strstr implemented from scratch
[ ] strtol/strtoul safe parsing (errno, endptr)
[ ] strtok danger + strtok_r
[ ] strdup and ownership
[ ] scanf("%s") overflow risk
[ ] gets() removal from C11
[ ] fgets newline handling
[ ] getline dynamic input
[ ] getchar/EOF int-vs-char pitfall
[ ] scanf + fgets leftover-newline bug
[ ] fflush(stdin) undefined behavior
[ ] fread/fwrite for binary data
[ ] stdout buffering modes (terminal vs pipe/file)
[ ] Partial read()/write() and EINTR retry loop
```

# END — C MASTER HANDBOOK
