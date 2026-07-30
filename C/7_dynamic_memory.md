# C Interview Handbook
# Chapter 5 – Dynamic Memory Management
# Part 1 – Memory Layout, Stack vs Heap & malloc()

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- Process memory layout
- Stack vs Heap
- Static/Data/BSS/Text segments
- Why dynamic memory is needed
- malloc()
- malloc() internals
- Heap allocation flow
- Common interview questions

---

# Why Do We Need Dynamic Memory?

Suppose we need an array.

```c
int arr[100];
```

Works fine.

But what if the size is only known at runtime?

```text
User enters

↓

50000
```

We cannot write

```c
int arr[n];
```

in portable C for every use case (and large arrays may overflow the stack).

Instead,

allocate memory while the program is running.

This is called

```
Dynamic Memory Allocation
```

---

# Process Memory Layout

Every C program is divided into several memory regions.

```
+----------------------+
| Command Line Args    |
+----------------------+
| Environment Variables|
+----------------------+
| Stack                |
|        ↓             |
|                      |
|                      |
|                      |
|        ↑             |
| Heap                 |
+----------------------+
| BSS                  |
+----------------------+
| Data                 |
+----------------------+
| Read Only Data       |
+----------------------+
| Text (Code)          |
+----------------------+
```

---

# Text Segment

Contains

- Machine instructions
- Program code

Example

```c
int add(int a,int b)
{
    return a+b;
}
```

The compiled instructions are stored in

```
Text Segment
```

Usually

```
Read Only

Executable
```

---

# Read Only Data (.rodata)

Contains

- String literals
- Constant data

Example

```c
printf("Hello");
```

```
"Hello"

↓

Stored in

↓

Read Only Data
```

Attempting to modify it

```c
char *p = "Hello";

p[0] = 'A';
```

Produces

```
Undefined Behavior

Often

Segmentation Fault
```

---

# Initialized Data Segment (.data)

Contains initialized global and static variables.

Example

```c
int x = 100;

static int y = 50;
```

Memory

```
Data Segment

↓

x

↓

100

y

↓

50
```

---

# BSS Segment

Contains uninitialized global/static variables.

Example

```c
int count;

static int value;
```

Both become

```
0
```

before `main()` begins.

```
BSS

↓

count

↓

0
```

---

# Stack

Stores

- Local variables
- Function parameters
- Return addresses
- Stack frames

Example

```c
void fun()
{
    int x = 10;
}
```

Memory

```
Stack

↓

x
```

When function returns

```
Stack Frame

↓

Destroyed
```

---

# Heap

Heap is used for

```
Dynamic Memory Allocation
```

Memory is requested using

```c
malloc()
```

and released using

```c
free()
```

Unlike the stack,

```
Heap Memory

↓

Exists

↓

Until free()
```

---

# Stack vs Heap

| Stack | Heap |
|--------|------|
| Automatic | Manual |
| Fast | Slower |
| Limited size | Usually much larger |
| Auto cleanup | Must call `free()` |
| Function scope | Programmer controlled |

---

# Stack Example

```c
void fun()
{
    int x = 10;
}
```

Memory

```
Call fun()

↓

Stack Frame Created

↓

x

↓

10

↓

Return

↓

Frame Destroyed
```

---

# Heap Example

```c
int *p = malloc(sizeof(int));

*p = 100;

free(p);
```

Memory

```
Stack

p

↓

Heap

100
```

Even if another function is called,

heap memory remains valid until `free()`.

---

# What is malloc()?

Prototype

```c
void *malloc(size_t size);
```

Header

```c
#include <stdlib.h>
```

Purpose

```
Allocate

↓

Requested Bytes

↓

From Heap
```

---

# Return Type

`malloc()` returns

```c
void *
```

A generic pointer.

Example

```c
int *p = malloc(sizeof(int));
```

In C,

`void *` is automatically converted to the required pointer type.

---

# Allocating One Integer

```c
int *p;

p = malloc(sizeof(int));
```

Memory

```
Heap

+------+
| ???? |
+------+
```

Notice

The value is

```
Garbage
```

because `malloc()` does **not** initialize memory.

---

# Using malloc()

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p;

    p = malloc(sizeof(int));

    if(p == NULL)
    {
        return 1;
    }

    *p = 500;

    printf("%d\n", *p);

    free(p);

    return 0;
}
```

Output

```
500
```

---

# Allocating an Array

```c
int *arr;

arr = malloc(5 * sizeof(int));
```

Memory

```
Heap

+----+----+----+----+----+
|    |    |    |    |    |
+----+----+----+----+----+
```

Use like a normal array

```c
arr[0] = 10;

arr[1] = 20;
```

---

# Why sizeof()?

Wrong

```c
malloc(5);
```

Correct

```c
malloc(5 * sizeof(int));
```

Reason

Different systems may have different integer sizes.

---

# Better Style

Instead of

```c
int *p =
malloc(sizeof(int));
```

Many experienced developers write

```c
int *p =
malloc(sizeof(*p));
```

Advantages

- No repeated type name
- Safer during refactoring

Similarly,

```c
Student *s =
malloc(sizeof(*s));
```

---

# What Happens Internally?

```
malloc()

↓

Request Memory

↓

Heap Manager

↓

Find Free Block

↓

Reserve Block

↓

Return Address
```

Visualization

```
Program

↓

malloc()

↓

Heap Manager

↓

Free Block

↓

Allocated Block

↓

Pointer Returned
```

---

# What if malloc() Fails?

Possible reasons

- Heap exhausted
- Out of memory
- Allocation limit reached

Return value

```
NULL
```

Always check

```c
if(p == NULL)
{
    printf("Allocation Failed\n");
}
```

---

# Why Heap is Slower?

Stack

```
Push

↓

Pop
```

Very simple.

Heap

```
Find Free Block

↓

Split Block

↓

Update Metadata

↓

Return Pointer
```

Much more work.

---

# Common Interview Questions

---

## Q1

Where does `malloc()` allocate memory?

```
Heap
```

---

## Q2

Does `malloc()` initialize memory?

No.

Memory contains indeterminate values.

---

## Q3

What does `malloc()` return?

```
void *
```

---

## Q4

Why check for `NULL`?

Allocation can fail.

---

## Q5

Can we access memory after `free()`?

No.

Doing so is **undefined behavior**.

---

## Q6

Who releases heap memory?

The programmer.

Using

```c
free()
```

---

## Q7

Why use `sizeof(*ptr)` instead of `sizeof(type)`?

It automatically matches the pointer type and avoids bugs if the type changes later.

---

# Common Interview Traps

### Trap 1

```c
int *p;

*p = 10;
```

Wrong.

No memory allocated.

---

### Trap 2

```c
malloc(sizeof(pointer));
```

Instead of

```c
malloc(sizeof(*pointer));
```

Be careful not to confuse the pointer size with the size of the object it points to.

---

### Trap 3

```c
malloc(100);
```

Without explaining what the 100 represents.

Prefer

```c
malloc(25 * sizeof(int));
```

---

### Trap 4

Ignoring `NULL`

```c
p = malloc(...);

*p = 10;
```

Could crash if allocation failed.

---

# Real Embedded Examples

## Buffer Allocation

```c
char *buffer =
malloc(1024);
```

---

## UART Receive Buffer

```c
uint8_t *rx =
malloc(256);
```

---

## Linked List Node

```c
struct Node *node =
malloc(sizeof(*node));
```

---

## Dynamic Packet

```c
Packet *pkt =
malloc(sizeof(*pkt));
```

---

# Quick Revision

```
Process Memory

↓

Text

↓

RO Data

↓

Data

↓

BSS

↓

Heap

↓

Stack

----------------------

malloc()

↓

Heap Allocation

----------------------

Returns

↓

void *

----------------------

Memory

↓

Not Initialized

----------------------

Failure

↓

NULL

----------------------

Always

↓

Check NULL

↓

Call free()
```

---

# Key Interview Takeaways

✅ Every process has separate memory regions: Text, Read-only Data, Data, BSS, Heap, and Stack.

✅ `malloc()` allocates memory from the heap and returns a `void *`.

✅ Memory allocated by `malloc()` is **not initialized**.

✅ Always check for `NULL` before using the returned pointer.

✅ Heap memory persists until explicitly released with `free()`.

---

# Next Part

In **Part 2**, we'll cover:

- `calloc()`
- `realloc()`
- `free()`
- Difference between `malloc()` and `calloc()`
- Resizing memory safely
- Memory initialization
- Real interview questions

----------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 5 – Dynamic Memory Management
# Part 2 – calloc(), realloc() & free()

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- calloc()
- realloc()
- free()
- Difference between malloc() and calloc()
- How realloc() works internally
- Safe use of realloc()
- Memory deallocation
- Common interview questions

---

# calloc()

Prototype

```c
void *calloc(size_t num, size_t size);
```

Header

```c
#include <stdlib.h>
```

Purpose

```
Allocate Memory

↓

Initialize All Bytes To Zero
```

Unlike `malloc()`, `calloc()` clears the allocated memory.

---

# Syntax

```c
int *arr;

arr = calloc(5, sizeof(int));
```

Meaning

```
Allocate

↓

5 integers

↓

Initialize to 0
```

Memory

```
+----+----+----+----+----+
| 0  | 0  | 0  | 0  | 0  |
+----+----+----+----+----+
```

---

# Example

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr;

    arr = calloc(5, sizeof(int));

    if(arr == NULL)
        return 1;

    for(int i = 0; i < 5; i++)
        printf("%d ", arr[i]);

    free(arr);

    return 0;
}
```

Output

```
0 0 0 0 0
```

---

# malloc() vs calloc()

| malloc() | calloc() |
|-----------|----------|
| One argument | Two arguments |
| Doesn't initialize memory | Initializes memory to zero |
| Usually slightly faster | Slightly slower due to initialization |

Example

```c
malloc(5 * sizeof(int));
```

vs

```c
calloc(5, sizeof(int));
```

---

# When Should You Use calloc()?

Use it when you want memory to start with known values.

Example

```c
struct Node *node =
calloc(1, sizeof(*node));
```

All members become zero.

Pointers become

```
NULL
```

Integer members become

```
0
```

---

# realloc()

Prototype

```c
void *realloc(void *ptr,
              size_t new_size);
```

Purpose

```
Resize Existing Memory
```

---

# Why realloc()?

Suppose the user enters data.

Initially

```
Need

↓

10 integers
```

Later

```
Need

↓

100 integers
```

Instead of allocating a new array manually,

use

```c
realloc()
```

---

# Example

```c
int *arr;

arr = malloc(5 * sizeof(int));

arr = realloc(arr,
              10 * sizeof(int));
```

Now

```
Old Size

↓

5 integers

↓

New Size

↓

10 integers
```

---

# What Happens Internally?

### Case 1

Enough free space exists after the current block.

```
Old Block

↓

Expanded

↓

Same Address
```

Example

```
1000

↓

Still

1000
```

---

### Case 2

Not enough free space.

```
Allocate New Block

↓

Copy Old Data

↓

Free Old Block

↓

Return New Address
```

Example

```
Old

1000

↓

New

5000
```

The pointer may change.

---

# Important Rule

Never assume the returned pointer is the same.

Wrong

```c
realloc(ptr,
        size);
```

Correct

```c
ptr = realloc(ptr,
              size);
```

Even better

```c
int *temp;

temp = realloc(ptr,
               size);

if(temp != NULL)
{
    ptr = temp;
}
```

This avoids losing the original pointer if `realloc()` fails.

---

# Complete Example

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr;

    arr = malloc(5 * sizeof(int));

    if(arr == NULL)
        return 1;

    for(int i = 0; i < 5; i++)
        arr[i] = i + 1;

    int *temp;

    temp = realloc(arr,
                   10 * sizeof(int));

    if(temp == NULL)
    {
        free(arr);
        return 1;
    }

    arr = temp;

    for(int i = 5; i < 10; i++)
        arr[i] = i + 1;

    for(int i = 0; i < 10; i++)
        printf("%d ", arr[i]);

    free(arr);

    return 0;
}
```

Output

```
1 2 3 4 5 6 7 8 9 10
```

---

# What Happens to New Memory?

Suppose

```c
arr = realloc(arr,
              10 * sizeof(int));
```

Original

```
1 2 3 4 5
```

New memory

```
1 2 3 4 5 ? ? ? ? ?
```

The extra memory is

```
Uninitialized
```

unless you initialize it yourself.

---

# free()

Prototype

```c
void free(void *ptr);
```

Purpose

```
Return Memory

↓

Back To Heap
```

Example

```c
int *p =
malloc(sizeof(int));

free(p);
```

Memory becomes available for future allocations.

---

# After free()

After

```c
free(p);
```

The pointer still contains the old address.

```
p

↓

1000
```

But

```
Memory

↓

No Longer Owned
```

Using it is undefined behavior.

---

# Good Practice

```c
free(p);

p = NULL;
```

Now accidental reuse becomes easier to detect.

---

# Double Free

Wrong

```c
free(p);

free(p);
```

Result

```
Undefined Behavior
```

May crash the program or corrupt the heap.

---

# Freeing NULL

Safe

```c
int *p = NULL;

free(p);
```

Nothing happens.

The C standard guarantees this is safe.

---

# realloc() Special Cases

### Case 1

```c
realloc(NULL,
        size);
```

Equivalent to

```c
malloc(size);
```

---

### Case 2

```c
realloc(ptr,
        0);
```

Implementation-defined behavior.

On most systems,

```
Acts Like

↓

free(ptr)
```

Avoid relying on this behavior in portable code.

---

# Common Interview Questions

---

## Q1

Difference between malloc() and calloc()?

| malloc() | calloc() |
|-----------|----------|
| Doesn't initialize memory | Initializes memory to zero |
| One argument | Two arguments |

---

## Q2

Does realloc() always move memory?

No.

If sufficient adjacent space exists,

the block may simply be expanded.

---

## Q3

Can realloc() fail?

Yes.

It returns

```
NULL
```

while leaving the original allocation unchanged.

---

## Q4

Why use a temporary pointer with realloc()?

Wrong

```c
ptr = realloc(ptr,
              size);
```

If it fails,

the original pointer is lost.

Correct

```c
temp = realloc(ptr,
               size);

if(temp)
    ptr = temp;
```

---

## Q5

Can free(NULL) crash?

No.

It is safe.

---

## Q6

What happens after free()?

The pointer becomes

```
Dangling
```

unless set to `NULL`.

---

## Q7

Can we access memory after free()?

No.

This is

```
Use-After-Free

↓

Undefined Behavior
```

---

# Common Interview Traps

### Trap 1

```c
ptr = realloc(ptr,
              size);
```

Ignoring allocation failure.

---

### Trap 2

Using new memory without initialization.

```c
realloc()
```

does **not** zero the additional bytes.

---

### Trap 3

Forgetting

```c
free()
```

Memory leak.

---

### Trap 4

Calling

```c
free()

↓

Twice
```

Double free.

---

### Trap 5

Accessing

```c
*p
```

after

```c
free(p);
```

Undefined behavior.

---

# Real Embedded Examples

## Growing UART Buffer

```c
rx =
realloc(rx,
        new_size);
```

---

## Dynamic Packet Buffer

```c
packet =
realloc(packet,
        packet_size);
```

---

## Dynamic Log Buffer

```c
log =
calloc(100,
       sizeof(char));
```

---

## Linked List Node

```c
Node *node =
calloc(1,
       sizeof(*node));
```

---

# Quick Revision

```
calloc()

↓

Allocate

+

Zero Initialize

------------------------

malloc()

↓

Allocate

↓

Garbage Values

------------------------

realloc()

↓

Resize Memory

↓

May Move Block

------------------------

free()

↓

Return Memory

↓

Heap

------------------------

Good Practice

↓

free(ptr);

ptr = NULL;

------------------------

Safe realloc

↓

temp = realloc()

↓

Success?

↓

ptr = temp
```

---

# Key Interview Takeaways

✅ `calloc()` allocates and zero-initializes memory.

✅ `malloc()` allocates memory but leaves it uninitialized.

✅ `realloc()` may either expand the existing block or allocate a new one and copy the data.

✅ Always use a temporary pointer when calling `realloc()`.

✅ Every successful `malloc()`, `calloc()`, or `realloc()` allocation must eventually be released using `free()`.

---

# Next Part

In **Part 3**, we'll cover the memory bugs that interviewers love to ask:

- Dangling pointers
- Wild pointers
- Null pointers
- Memory leaks
- Double free
- Use-after-free
- Buffer overflow
- Heap corruption
- Defensive programming techniques
- 40+ interview questions from Qualcomm, NVIDIA, Broadcom, AMD, Intel, and Linux kernel teams.
-----------------------------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 5 – Dynamic Memory Management
# Part 3 – Memory Bugs (Dangling Pointer, Wild Pointer, Memory Leak & More)

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

This chapter covers the most common memory-related bugs asked in C interviews.

After completing this chapter, you should understand:

- Null pointer
- Wild pointer
- Dangling pointer
- Memory leak
- Double free
- Use-after-free
- Buffer overflow
- Heap corruption
- Defensive programming
- Common interview questions

---

# Why Are Memory Bugs Important?

Most crashes in C/C++ programs happen because of incorrect memory handling.

Common symptoms include:

- Segmentation fault
- Random crashes
- Data corruption
- Security vulnerabilities
- Heap corruption

Large companies such as Qualcomm, NVIDIA, and Broadcom expect engineers to recognize these bugs quickly.

---

# 1. Null Pointer

A null pointer points to **no valid memory**.

```c
int *ptr = NULL;
```

Memory

```
ptr

↓

NULL
```

---

## Why Use NULL?

Instead of leaving a pointer uninitialized,

```c
int *ptr = NULL;
```

clearly indicates that it does not currently point to an object.

---

## Checking for NULL

```c
if(ptr != NULL)
{
    *ptr = 10;
}
```

Always validate pointers before dereferencing them when appropriate.

---

## Dereferencing NULL

```c
int *ptr = NULL;

*ptr = 100;
```

Result

```
Undefined Behavior

Usually

Segmentation Fault
```

---

# 2. Wild Pointer

A wild pointer is an **uninitialized pointer**.

Example

```c
int *ptr;
```

Memory

```
ptr

↓

???????
```

The pointer contains an indeterminate address.

---

## Problem

```c
int *ptr;

*ptr = 10;
```

Result

```
Undefined Behavior
```

The program may:

- Crash
- Corrupt memory
- Appear to work accidentally

---

## Correct Way

```c
int *ptr = NULL;
```

or

```c
int value = 10;

int *ptr = &value;
```

---

# 3. Dangling Pointer

A dangling pointer points to memory that is **no longer valid**.

Example

```c
int *ptr =
malloc(sizeof(int));

free(ptr);
```

Memory

```
Before free()

ptr

↓

Heap

↓

100
```

After

```c
free(ptr);
```

```
ptr

↓

Old Address

Memory

↓

Released
```

The pointer still stores the old address, but that memory is no longer owned by the program.

---

## Problem

```c
int *ptr =
malloc(sizeof(int));

free(ptr);

*ptr = 10;
```

Result

```
Use-After-Free

↓

Undefined Behavior
```

---

## Best Practice

```c
free(ptr);

ptr = NULL;
```

Now

```
ptr

↓

NULL
```

Accidental reuse becomes easier to detect.

---

# 4. Memory Leak

Memory leak occurs when allocated memory is never released.

Example

```c
void fun()
{
    int *p =
    malloc(sizeof(int));

    *p = 10;

    return;
}
```

Memory

```
malloc()

↓

Heap

↓

No Pointer Exists

↓

Cannot Free

↓

Memory Leak
```

---

## Correct Version

```c
void fun()
{
    int *p =
    malloc(sizeof(int));

    if(p == NULL)
        return;

    *p = 10;

    free(p);
}
```

---

# Why Memory Leaks Matter

Suppose a server leaks

```
64 Bytes
```

per request.

After

```
1,000,000

requests
```

Memory leaked

```
≈ 64 MB
```

Long-running programs eventually exhaust available memory.

---

# 5. Double Free

Example

```c
int *p =
malloc(sizeof(int));

free(p);

free(p);
```

Result

```
Undefined Behavior
```

Possible outcomes

- Crash
- Heap corruption
- Security vulnerability

---

## Correct Way

```c
free(p);

p = NULL;
```

Second call

```c
free(p);
```

is safe because `free(NULL)` does nothing.

---

# 6. Use-After-Free

Example

```c
int *p =
malloc(sizeof(int));

*p = 100;

free(p);

printf("%d", *p);
```

The pointer refers to memory that has already been released.

Result

```
Undefined Behavior
```

Sometimes it prints

```
100
```

Sometimes

```
Crash
```

Sometimes

```
Random Value
```

Never rely on any observed behavior.

---

# 7. Buffer Overflow

One of the most frequently asked interview topics.

Example

```c
int arr[5];

arr[5] = 100;
```

Memory

```
+----+----+----+----+----+
|0   |1   |2   |3   |4   |
+----+----+----+----+----+

arr[5]

↓

Outside Array
```

Result

```
Undefined Behavior
```

---

## Character Array Overflow

```c
char name[5];

strcpy(name,
       "Qualcomm");
```

The string is larger than the destination array.

Memory outside the array is overwritten.

---

# Why Buffer Overflow Is Dangerous

It may overwrite

- Other variables
- Heap metadata
- Function return addresses
- Security-sensitive data

This is one of the oldest and most dangerous classes of software bugs.

---

# 8. Heap Corruption

Example

```c
char *p =
malloc(10);

strcpy(p,
       "This string is much longer");
```

Memory

```
Allocated

↓

10 Bytes

↓

Write

↓

25 Bytes
```

Result

```
Heap Metadata

↓

Corrupted
```

The crash may happen much later during another `malloc()` or `free()` call.

---

# 9. Returning Address of Local Variable

Classic interview question.

Wrong

```c
int* fun()
{
    int x = 10;

    return &x;
}
```

Memory

```
Stack

↓

x

↓

Function Returns

↓

Stack Frame Destroyed
```

Returned pointer becomes dangling.

---

## Correct Ways

Return by value

```c
int fun()
{
    int x = 10;

    return x;
}
```

or allocate dynamically

```c
int* fun()
{
    int *p =
    malloc(sizeof(int));

    if(p)
        *p = 10;

    return p;
}
```

Caller must call

```c
free()
```

---

# 10. Returning Pointer to String Literal

Correct

```c
const char *fun()
{
    return "Hello";
}
```

The string literal exists for the lifetime of the program.

Do **not** modify it.

---

# Defensive Programming Tips

## Initialize Pointers

Good

```c
int *ptr = NULL;
```

---

## Check malloc()

```c
ptr = malloc(sizeof(*ptr));

if(ptr == NULL)
{
    return;
}
```

---

## Free Every Allocation

Every successful

```c
malloc()

calloc()

realloc()
```

must eventually have a matching

```c
free()
```

---

## Set Pointer to NULL

```c
free(ptr);

ptr = NULL;
```

---

## Check Array Bounds

Wrong

```c
arr[10];
```

Correct

```c
if(index < SIZE)
{
    arr[index] = value;
}
```

---

# Common Interview Questions

---

## Q1

Difference between a null pointer and a wild pointer?

| Null Pointer | Wild Pointer |
|--------------|--------------|
| Initialized to `NULL` | Uninitialized |
| Safe to compare | Contains garbage address |
| Doesn't point anywhere | May point anywhere |

---

## Q2

What is a dangling pointer?

A pointer referring to memory that is no longer valid.

---

## Q3

What causes memory leaks?

Allocated memory is never released using `free()`.

---

## Q4

Why is double free dangerous?

The heap manager may attempt to release an already released block, causing undefined behavior.

---

## Q5

What is use-after-free?

Accessing memory after it has been released.

---

## Q6

What is heap corruption?

Writing outside allocated heap memory or otherwise damaging allocator metadata.

---

## Q7

Why should pointers be set to NULL after free()?

To reduce the chance of accidentally using a dangling pointer.

---

## Q8

Can `free(NULL)` crash?

No.

It is guaranteed to be safe.

---

## Q9

Why is returning the address of a local variable wrong?

Because local variables are destroyed when the function returns.

---

## Q10

Which memory bugs are security risks?

- Buffer overflow
- Heap corruption
- Use-after-free
- Double free

---

# Common Interview Traps

### Trap 1

```c
int *p;

*p = 10;
```

Wild pointer.

---

### Trap 2

```c
free(p);

*p = 100;
```

Use-after-free.

---

### Trap 3

```c
free(p);

free(p);
```

Double free.

---

### Trap 4

```c
char buf[5];

strcpy(buf, "Broadcom");
```

Buffer overflow.

---

### Trap 5

```c
return &localVariable;
```

Returning a dangling pointer.

---

# Real Embedded Examples

## DMA Buffer

```c
uint8_t *dma =
malloc(4096);

/* ... */

free(dma);
dma = NULL;
```

---

## Network Packet

Always validate packet length before copying.

```c
if(packet_len <= sizeof(buffer))
{
    memcpy(buffer,
           packet,
           packet_len);
}
```

---

## Driver Development

Always pair

```c
malloc()

↓

free()
```

on every execution path, including error handling.

---

# Quick Revision

```
NULL Pointer

↓

Points To Nothing

------------------------

Wild Pointer

↓

Uninitialized

------------------------

Dangling Pointer

↓

Points To Freed Memory

------------------------

Memory Leak

↓

Forgot free()

------------------------

Double Free

↓

free()

↓

free()

------------------------

Use-After-Free

↓

Access After free()

------------------------

Buffer Overflow

↓

Write Beyond Memory

------------------------

Best Practices

↓

Initialize

↓

Check NULL

↓

Free Memory

↓

Set To NULL
```

---

# Key Interview Takeaways

✅ Always initialize pointers.

✅ Never dereference uninitialized or `NULL` pointers.

✅ Every successful dynamic allocation must be released.

✅ Never access memory after `free()`.

✅ Avoid writing outside array or heap boundaries.

✅ Many interview debugging questions revolve around these memory bugs.

---

# Next Part

In **Part 4**, we'll cover **Advanced Dynamic Memory Topics**:

- How `malloc()` works internally
- Heap allocator concepts
- Fragmentation (internal & external)
- Alignment in heap allocation
- Custom memory allocators
- Memory pools
- Embedded memory management
- `alloca()`
- 40+ advanced interview questions from Qualcomm, NVIDIA, Broadcom, AMD, Intel, and Linux kernel teams.
--------------------------------------------------------------------------------------------------------------------------------

