# C Interview Handbook
# Part 2 - Memory Management

---

# Table of Contents

1. Why Memory Management?
2. Process Memory Layout
3. Text Segment
4. Initialized Data Segment
5. BSS Segment
6. Heap
7. Stack
8. Stack vs Heap
9. Dynamic Memory Allocation
10. malloc()
11. calloc()
12. realloc()
13. free()
14. Memory Leaks
15. Dangling Pointer
16. Wild Pointer
17. NULL Pointer
18. Memory Corruption
19. Common Memory Bugs
20. Best Practices
21. Interview Questions
22. Quick Revision

---

# 1. Why Memory Management?

Every running program requires memory to store:

- Instructions
- Variables
- Function calls
- Dynamically allocated objects

Understanding memory management is essential because many C interview questions focus on pointers, allocation, and debugging memory-related issues.

---

# 2. Process Memory Layout

When a C program starts, the operating system creates a process with the following memory layout:

```text
 Higher Address
+------------------------+
| Command Line / Env     |
+------------------------+
| Stack                  |
| (Function Calls)       |
| grows downward         |
+------------------------+
|                        |
|   Free Memory          |
|                        |
+------------------------+
| Heap                   |
| Dynamic Allocation     |
| grows upward           |
+------------------------+
| BSS                    |
| Uninitialized Globals  |
+------------------------+
| Data                   |
| Initialized Globals    |
+------------------------+
| Text (Code)            |
+------------------------+
 Lower Address
```

---

# 3. Text Segment (Code Segment)

Stores:

- Machine instructions
- Read-only executable code

Example

```c
#include <stdio.h>

int main()
{
    printf("Hello");
}
```

The compiled instructions for `main()` are stored in the Text segment.

Characteristics

- Read Only
- Shared between processes (when possible)
- Created when program starts

---

# 4. Initialized Data Segment

Stores

- Global variables
- Static variables

that have an initial value.

Example

```c
int count = 10;
static int total = 20;
```

Memory

```text
Data Segment

count = 10

total = 20
```

---

# 5. BSS Segment

BSS = Block Started by Symbol

Stores

- Global variables
- Static variables

without explicit initialization.

Example

```c
int x;

static int y;
```

Both become zero before `main()` starts.

Memory

```text
BSS

x = 0

y = 0
```

---

# 6. Heap

Heap stores memory allocated during program execution.

Allocated using

```c
malloc()
calloc()
realloc()
```

Example

```c
int *p = malloc(sizeof(int));
```

Memory

```text
Heap

+-------+
| 100   |
+-------+

p

↓

Heap Memory
```

Characteristics

- Dynamic size
- Slower than stack
- Must free manually
- Shared across functions via pointers

---

# 7. Stack

Stores

- Local variables
- Function parameters
- Return addresses
- Saved registers

Example

```c
void fun()
{
    int x = 10;
}
```

Memory

```text
Stack

+------+
| x=10 |
+------+
```

Automatically removed when the function returns.

---

# Stack Growth

```text
main()

↓

fun()

↓

display()
```

Stack

```text
+------------+
| display()  |
+------------+
| fun()      |
+------------+
| main()     |
+------------+
```

Each function call creates a new **stack frame**.

---

# 8. Stack vs Heap

| Feature | Stack | Heap |
|----------|-------|------|
| Allocation | Automatic | Manual |
| Speed | Fast | Slower |
| Size | Limited | Larger |
| Lifetime | Function scope | Until free() |
| Managed By | Compiler | Programmer |

---

# 9. Dynamic Memory Allocation

Why use it?

Sometimes the required memory size is unknown until runtime.

Example

```c
int n;

scanf("%d",&n);

int *arr = malloc(n * sizeof(int));
```

Now the array size depends on user input.

---

# 10. malloc()

Syntax

```c
void *malloc(size_t size);
```

Allocates memory but **does not initialize it**.

Example

```c
int *p = malloc(sizeof(int));

if(p == NULL)
{
    printf("Allocation Failed");
    return 1;
}

*p = 100;

printf("%d", *p);

free(p);
```

Memory

```text
Heap

+------+
| 100  |
+------+

p

↓

Heap
```

---

# malloc() Important Points

- Returns pointer to allocated memory
- Returns NULL if allocation fails
- Memory contains garbage values initially
- Must call free()

---

# 11. calloc()

Syntax

```c
void *calloc(size_t n, size_t size);
```

Allocates memory and initializes every byte to zero.

Example

```c
int *p = calloc(5, sizeof(int));

for(int i=0;i<5;i++)
    printf("%d ", p[i]);

free(p);
```

Output

```text
0 0 0 0 0
```

---

# malloc() vs calloc()

| malloc() | calloc() |
|-----------|----------|
| One argument | Two arguments |
| Garbage values | Zero initialized |
| Slightly faster | Slightly slower |

---

# 12. realloc()

Used to resize previously allocated memory.

Syntax

```c
realloc(ptr,newSize);
```

Example

```c
int *p = malloc(5 * sizeof(int));

p = realloc(p,10 * sizeof(int));

free(p);
```

Can

- Increase memory
- Decrease memory

---

# realloc() Important Points

If enough space exists, the same block may be expanded.

Otherwise

- New block allocated
- Data copied
- Old block freed automatically

If allocation fails, `realloc()` returns `NULL` and the original pointer remains valid. A safer pattern is:

```c
int *temp = realloc(p, 10 * sizeof(int));

if (temp != NULL)
{
    p = temp;
}
```

---

# 13. free()

Releases allocated heap memory.

Example

```c
int *p = malloc(sizeof(int));

free(p);

p = NULL;
```

Always set pointer to NULL after freeing when it will continue to exist.

---

# Why free()?

Without free()

```text
Memory

Allocated

↓

Never Released

↓

Memory Leak
```

---

# 14. Memory Leak

Memory allocated

but

Never freed.

Example

```c
void fun()
{
    int *p = malloc(100);

    /* Forgot free() */
}
```

Every call leaks memory.

Large applications may eventually run out of available memory.

---

# 15. Dangling Pointer

A pointer referring to memory that has already been freed.

Example

```c
int *p = malloc(sizeof(int));

free(p);

/* Dangling Pointer */
*p = 10;
```

Undefined Behavior.

Correct

```c
free(p);

p = NULL;
```

---

# 16. Wild Pointer

Pointer declared

but never initialized.

Example

```c
int *p;

*p = 10;
```

Dangerous.

Always initialize.

```c
int *p = NULL;
```

---

# 17. NULL Pointer

A pointer that points to no valid object.

Example

```c
int *p = NULL;
```

Before dereferencing

```c
if(p != NULL)
{
    printf("%d", *p);
}
```

---

# 18. Memory Corruption

Occurs when memory outside allocated bounds is accessed or overwritten.

Example

```c
int *arr = malloc(5 * sizeof(int));

arr[10] = 100;
```

Possible results

- Crash
- Data corruption
- Random behavior
- Security vulnerabilities

---

# 19. Common Memory Bugs

## Buffer Overflow

```c
char name[5];

strcpy(name,"OpenAI");
```

Writes beyond the array.

---

## Double Free

```c
free(p);

free(p);
```

Undefined Behavior.

---

## Use After Free

```c
free(p);

printf("%d", *p);
```

Accessing released memory.

---

## Invalid Free

```c
int x = 10;

free(&x);
```

Only memory allocated by `malloc()`, `calloc()`, or `realloc()` may be freed.

---

# 20. Best Practices

✔ Always check `malloc()` return value.

✔ Free every allocated block exactly once.

✔ Set pointers to `NULL` after `free()` if they may be reused.

✔ Never dereference `NULL`.

✔ Never access freed memory.

✔ Never free stack memory.

✔ Never write outside array bounds.

✔ Match every allocation with a corresponding `free()`.

---

# 21. Frequently Asked Interview Questions

## Q1. Difference between Stack and Heap?

Stack

- Automatic allocation
- Fast
- Stores local variables
- Freed automatically

Heap

- Manual allocation
- Larger
- Stores dynamic memory
- Must call `free()`

---

## Q2. Difference between malloc() and calloc()?

`malloc()`

- One parameter
- Uninitialized memory

`calloc()`

- Two parameters
- Zero-initialized memory

---

## Q3. What is realloc()?

Changes the size of an existing heap allocation while preserving existing data (as much as possible).

---

## Q4. What is a Memory Leak?

Allocated memory that is never released using `free()`.

---

## Q5. What is a Dangling Pointer?

A pointer that still points to memory that has already been freed.

---

## Q6. What is a Wild Pointer?

An uninitialized pointer containing an unpredictable address.

---

## Q7. What is a NULL Pointer?

A pointer that intentionally points to no valid memory location.

---

## Q8. Why should malloc() be checked for NULL?

Allocation may fail due to insufficient memory. Dereferencing a `NULL` pointer causes undefined behavior.

---

# 22. Quick Revision

```
Process Memory

Text
↓

Data
↓

BSS
↓

Heap (grows upward)

↓

Free Space

↓

Stack (grows downward)
```

✔ Stack stores local variables and function call information.

✔ Heap stores dynamically allocated memory.

✔ `malloc()` allocates uninitialized memory.

✔ `calloc()` allocates zero-initialized memory.

✔ `realloc()` resizes existing allocations.

✔ `free()` releases heap memory.

✔ Memory Leak = allocated but never freed.

✔ Dangling Pointer = pointer to freed memory.

✔ Wild Pointer = uninitialized pointer.

✔ NULL Pointer = points to nothing.

✔ Avoid buffer overflows, double frees, and use-after-free bugs.

---

# Next Part

**Part 3 - Pointers (Complete Deep Dive)**

- Pointer Basics
- Pointer Arithmetic
- Pointer to Pointer
- Void Pointer
- Function Pointer
- Pointer to Array
- Array of Pointers
- Double Pointer
- const with Pointers
- Memory Diagrams
- 40+ Interview Questions
- Fully Commented Programs