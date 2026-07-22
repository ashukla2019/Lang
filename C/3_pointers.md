# C Interview Handbook
# Part 3A.1 - Pointer Fundamentals

---

# Table of Contents

1. What is a Pointer?
2. Why Do We Need Pointers?
3. Memory Addresses
4. Variables and Memory
5. Pointer Declaration
6. Pointer Initialization
7. Address-of Operator (&)
8. Dereference Operator (*)
9. Reading and Writing Through Pointers
10. Pointer Size
11. Pointer Types
12. Common Mistakes
13. Interview Questions
14. Quick Revision

---

# 1. What is a Pointer?

A **pointer** is a variable that stores the **memory address** of another variable.

Instead of storing a value directly, it stores **where that value is located in memory**.

Example

```c
int x = 10;
int *p = &x;
```

Memory

```text
Variable      Address      Value

x             1000         10
p             2000         1000
```

Explanation

- `x` stores **10**
- `x` is stored at address **1000**
- `p` stores **1000**
- Therefore `p` points to `x`

---

# Why are Pointers Important?

Pointers are used to

- Access memory directly
- Allocate dynamic memory
- Pass large objects efficiently
- Modify variables inside functions
- Build data structures
- Implement operating systems
- Write device drivers
- Develop networking software

Without pointers, C would not support efficient low-level programming.

---

# 2. Why Do We Need Pointers?

Suppose we have

```c
int x = 10;
```

Normally

```text
x

↓

10
```

But what if another function needs to modify `x`?

Instead of copying the value, we send its address.

```text
Function

↓

Address

↓

Original Variable
```

This avoids unnecessary copying.

---

# 3. Memory Addresses

Every variable occupies memory.

Example

```c
int age = 25;
char ch = 'A';
float pi = 3.14;
```

Possible memory

```text
Address     Variable     Value

1000        age          25

1004        ch           'A'

1008        pi           3.14
```

Actual addresses are assigned by the operating system and compiler.

---

# 4. Variables and Memory

Example

```c
int x = 50;
```

Memory

```text
Address

5000

↓

+------+
|  50  |
+------+
```

Variable name

```text
x

↓

5000
```

So

```text
Variable

↓

Memory Address

↓

Stored Value
```

---

# 5. Pointer Declaration

Syntax

```c
datatype *pointerName;
```

Examples

```c
int *p;

char *c;

float *f;

double *d;
```

The `*` indicates that the variable is a pointer.

---

# Example

```c
int x = 100;

int *p;
```

Currently

```text
p

↓

Unknown Address
```

Until initialized, it contains an unpredictable value.

---

# 6. Pointer Initialization

Always initialize pointers.

Correct

```c
int x = 10;

int *p = &x;
```

Memory

```text
x

Address : 1000

Value : 10


p

Address : 2000

Value : 1000
```

Diagram

```text
+-------+
| 1000  |   p
+-------+
     |
     |
     V
+-------+
|  10   |   x
+-------+
```

---

# 7. Address-of Operator (&)

The `&` operator returns the memory address of a variable.

Example

```c
int x = 20;

printf("%p", &x);
```

Possible output

```text
0x7ffd1234
```

Meaning

```text
&x

↓

Address of x
```

---

# Example

```c
int marks = 90;

printf("%d\n", marks);

printf("%p\n", &marks);
```

Output

```text
90

0x7ffd...
```

The exact address changes every execution.

---

# 8. Dereference Operator (*)

The `*` operator accesses the value stored at the address held by a pointer.

Example

```c
int x = 50;

int *p = &x;

printf("%d", *p);
```

Output

```text
50
```

Diagram

```text
p

↓

Address 1000

↓

+------+
|  50  |
+------+
```

Here

```text
p

↓

Address

↓

x

↓

50
```

`*p` means

> Go to the address stored inside `p` and read the value.

---

# 9. Reading Through a Pointer

Example

```c
int x = 25;

int *p = &x;

printf("%d\n", *p);
```

Output

```text
25
```

`*p` returns the value stored in `x`.

---

# Writing Through a Pointer

Example

```c
int x = 10;

int *p = &x;

*p = 99;

printf("%d", x);
```

Output

```text
99
```

Memory

Before

```text
x = 10
```

After

```text
*p = 99

↓

x = 99
```

A pointer can both read and modify the original variable.

---

# Another Example

```c
int salary = 1000;

int *p = &salary;

*p = *p + 500;

printf("%d", salary);
```

Output

```text
1500
```

---

# 10. Pointer Size

Many beginners think pointer size depends on the data type.

It does **not**.

Example

```c
int *p;

char *c;

float *f;

double *d;
```

On a 64-bit system

```text
sizeof(p) = 8

sizeof(c) = 8

sizeof(f) = 8

sizeof(d) = 8
```

Why?

Because all pointers store **addresses**, and on a 64-bit machine an address is 8 bytes.

On a 32-bit system

```text
All pointers are usually 4 bytes.
```

---

# Pointer Types

```c
int *p;

char *c;

float *f;

double *d;

long *l;
```

Difference

They all store addresses, but the compiler uses the pointed-to type to determine:

- How many bytes to read/write when dereferencing.
- How pointer arithmetic behaves.

Example

```c
int *p;
```

`p + 1` advances by `sizeof(int)` bytes.

```c
char *c;
```

`c + 1` advances by `sizeof(char)` (1 byte).

---

# Common Mistakes

## Mistake 1

```c
int *p;

*p = 10;
```

Wrong.

`p` is uninitialized (wild pointer).

---

## Mistake 2

```c
int *p = NULL;

*p = 10;
```

Wrong.

Cannot dereference a NULL pointer.

---

## Mistake 3

```c
int x = 10;

int *p;

p = x;
```

Wrong.

Assigning an integer value to a pointer.

Correct

```c
p = &x;
```

---

## Mistake 4

```c
int x = 5;

printf("%d", &x);
```

Wrong format specifier.

Correct

```c
printf("%p", (void *)&x);
```

---

# Frequently Asked Interview Questions

### Q1. What is a pointer?

A variable that stores the memory address of another variable.

---

### Q2. What does `&` do?

Returns the address of a variable.

---

### Q3. What does `*` do?

Dereferences a pointer and accesses the value stored at the pointed-to address.

---

### Q4. Can a pointer change a variable?

Yes.

Example

```c
int x = 5;

int *p = &x;

*p = 100;
```

Now

```text
x = 100
```

---

### Q5. Why are pointers used?

- Dynamic memory allocation
- Efficient function calls
- Data structures
- System programming
- Memory access
- Device drivers

---

### Q6. Does pointer size depend on the data type?

No.

Pointer size depends on the system architecture (typically 4 bytes on 32-bit, 8 bytes on 64-bit systems).

---

# Quick Revision

✓ Pointer stores an address, not the actual value.

✓ `&` gives the address of a variable.

✓ `*` accesses the value stored at the pointed-to address.

✓ Initialize pointers before use.

✓ Pointer size depends on the machine architecture.

✓ Pointers allow reading and modifying variables indirectly.

✓ Uninitialized pointers are dangerous.

✓ Never dereference a NULL pointer.

---

# Next Part

**Part 3A.2 – Pointer Operations & Memory Diagrams**

Topics:

- Pointer Assignment
- Pointer Copying
- Multiple Pointers
- Swapping Using Pointers
- Function Parameters
- Memory Tracing
- Address Calculations
- 20+ Memory Diagrams
- 25+ Interview Questions

--------------------

# C Interview Handbook
# Part 3A.2 - Pointer Operations & Memory Diagrams

---

# Table of Contents

1. Pointer Assignment
2. Copying Pointers
3. Multiple Pointers to Same Variable
4. Changing Values Through Pointers
5. Swapping Using Pointers
6. Pointers as Function Parameters
7. Pass by Value vs Pass by Address
8. Pointer Memory Diagrams
9. Common Mistakes
10. Interview Questions
11. Quick Revision

---

# 1. Pointer Assignment

A pointer stores the address of a variable.

Example

```c
int x = 10;

int *p = &x;
```

Memory

```text
Address      Value

1000         10
2000         1000
```

Diagram

```text
       p
       |
       V
+------------+
| Address1000|
+------------+
       |
       V
+------------+
|    x=10    |
+------------+
```

---

# 2. Reading Through Pointer

```c
int x = 50;

int *p = &x;

printf("%d\n", *p);
```

Output

```text
50
```

Explanation

```
p

↓

Address of x

↓

Read value

↓

50
```

---

# 3. Writing Through Pointer

```c
int x = 50;

int *p = &x;

*p = 200;

printf("%d", x);
```

Output

```text
200
```

Memory

Before

```text
x = 50
```

After

```text
*p = 200

↓

x = 200
```

The pointer directly modifies the original variable.

---

# 4. Copying Pointers

Example

```c
int x = 10;

int *p = &x;

int *q = p;
```

Memory

```text
      p
      |
      |

      q
      |
      V

+-----------+
|    x=10   |
+-----------+
```

Both pointers store the same address.

Verify

```c
printf("%p\n", (void *)p);
printf("%p\n", (void *)q);
```

Output (example)

```text
0x1000
0x1000
```

---

# Changing Through Either Pointer

```c
*q = 500;

printf("%d\n", x);
printf("%d\n", *p);
```

Output

```text
500
500
```

Reason

Both pointers refer to the same memory location.

---

# 5. Multiple Pointers

```c
int x = 25;

int *p = &x;

int *q = &x;

int *r = &x;
```

Diagram

```text
        p
        |

        q
        |

        r
        |

        V

+------------+
|   x = 25   |
+------------+
```

Any pointer can modify x.

---

Example

```c
*r = 100;
```

Now

```text
x = 100

*p = 100

*q = 100
```

---

# 6. Pointer Variable Can Change

Pointers themselves are variables.

Example

```c
int a = 10;

int b = 20;

int *p = &a;

printf("%d\n", *p);

p = &b;

printf("%d\n", *p);
```

Output

```text
10
20
```

Diagram

Initially

```text
p

↓

a
```

Later

```text
p

↓

b
```

---

# 7. Swapping Using Pointers

Without pointers

```c
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}
```

Original values remain unchanged because copies are modified.

---

Using pointers

```c
#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;

    *b = temp;
}

int main()
{
    int x = 10;
    int y = 20;

    swap(&x, &y);

    printf("%d %d\n", x, y);

    return 0;
}
```

Output

```text
20 10
```

---

Memory Diagram

Before

```text
x = 10

y = 20
```

Addresses passed

```text
&a

↓

x

&b

↓

y
```

Inside function

```text
*a = x

*b = y
```

Swap

```text
temp = x

x = y

y = temp
```

---

# 8. Pointers as Function Parameters

Example

```c
void increment(int *num)
{
    (*num)++;
}
```

Call

```c
int x = 5;

increment(&x);
```

Result

```text
x = 6
```

Explanation

Instead of copying x,

its address is passed.

The function updates the original variable.

---

# 9. Pass by Value

```c
void fun(int x)
{
    x = 100;
}
```

Call

```c
int a = 10;

fun(a);
```

Result

```text
a = 10
```

Reason

A copy is modified.

---

Memory

```text
main()

a = 10

↓

Copy

↓

fun()

x = 10
```

---

# 10. Pass by Address

```c
void fun(int *p)
{
    *p = 100;
}
```

Call

```c
int a = 10;

fun(&a);
```

Result

```text
a = 100
```

Memory

```text
a

↓

Address

↓

Function

↓

Modify Original
```

---

# 11. Pointer Comparison

Pointers can be compared if they point into the same object or array.

Example

```c
int a = 10;

int *p = &a;

int *q = &a;

if (p == q)
{
    printf("Same Address");
}
```

Output

```text
Same Address
```

---

# 12. Pointer and NULL

```c
int *p = NULL;

if (p == NULL)
{
    printf("Pointer is NULL");
}
```

Always check a pointer before dereferencing it when there is a possibility it is NULL.

---

# 13. Memory Tracing Example

```c
int x = 10;

int *p = &x;

*p = 20;

x = 30;

printf("%d\n", *p);
```

Step 1

```text
x = 10
```

Step 2

```text
*p = 20

↓

x = 20
```

Step 3

```text
x = 30
```

Step 4

```text
*p

↓

30
```

Output

```text
30
```

---

# 14. Common Mistakes

## Mistake 1

```c
int *p;

printf("%d", *p);
```

Wrong

Pointer is uninitialized.

---

## Mistake 2

```c
int *p = NULL;

printf("%d", *p);
```

Wrong

Dereferencing NULL leads to undefined behavior.

---

## Mistake 3

```c
int x = 10;

int *p = &x;

p = NULL;

printf("%d", *p);
```

Wrong

The pointer no longer points to x.

---

## Mistake 4

```c
int x = 10;

int *p = &x;

int *q = p;

q = NULL;
```

Only q becomes NULL.

p still points to x.

---

# Frequently Asked Interview Questions

### Q1. What happens when one pointer is assigned to another?

Only the address is copied.

The pointed-to object is **not** copied.

---

### Q2. Can multiple pointers point to the same variable?

Yes.

All of them can read or modify that variable.

---

### Q3. Why use pointers in functions?

To modify the caller's variables and avoid copying large objects.

---

### Q4. Difference between

```c
p = &x;
```

and

```c
*p = x;
```

`p = &x;`

Stores the address of `x` in `p`.

`*p = x;`

Stores the value of `x` into the memory pointed to by `p`. `p` must already point to valid memory.

---

### Q5. Does changing one pointer change another copied pointer?

No.

Changing where one pointer points does not affect the other pointer.

Example

```c
int a = 10;
int b = 20;

int *p = &a;
int *q = p;

q = &b;
```

Now

```text
p → a

q → b
```

---

# Quick Revision

✓ A pointer stores an address.

✓ Multiple pointers can point to the same variable.

✓ Copying a pointer copies only the address.

✓ Dereferencing (`*`) accesses the value.

✓ Pass pointers to functions to modify original variables.

✓ Pass by value modifies a copy.

✓ Pass by address modifies the original object.

✓ Pointers themselves can point to different variables over time.

✓ Always initialize pointers before using them.

---

# Next Part

**Part 3A.3 - NULL, Wild & Dangling Pointers**

Topics

- NULL Pointer
- Wild Pointer
- Dangling Pointer
- Void Pointer
- Safe Pointer Practices
- Memory Safety
- Common Bugs
- Debugging Pointer Errors
- Interview Questions

----------------------------
# C Interview Handbook
# Part 3A.3 - NULL, Wild & Dangling Pointers

---

# Table of Contents

1. Why Pointer Safety Matters
2. NULL Pointer
3. Wild Pointer
4. Dangling Pointer
5. Void Pointer
6. Pointer Safety Rules
7. Common Pointer Bugs
8. Memory Diagrams
9. Interview Questions
10. Quick Revision

---

# 1. Why Pointer Safety Matters

Pointers give direct access to memory.

This makes C very powerful, but also dangerous.

Incorrect pointer usage can cause

- Program crashes
- Memory corruption
- Security vulnerabilities
- Undefined Behavior

Most difficult bugs in C programs are caused by incorrect pointer usage.

---

# 2. NULL Pointer

A NULL pointer points to **nothing**.

It does not refer to any valid memory location.

Example

```c
int *p = NULL;
```

Memory

```text
p

↓

NULL
```

NULL is commonly used to indicate

- No object
- Allocation failure
- End of a linked list
- Invalid pointer

---

# Checking NULL

Always check before dereferencing.

```c
if (p != NULL)
{
    printf("%d\n", *p);
}
```

Wrong

```c
int *p = NULL;

printf("%d", *p);
```

Dereferencing a NULL pointer causes **Undefined Behavior**.

---

# Why Initialize to NULL?

Suppose

```c
int *p;
```

What does p contain?

Unknown.

Instead

```c
int *p = NULL;
```

Now we know it points nowhere until assigned a valid address.

---

# 3. Wild Pointer

A **wild pointer** is an **uninitialized pointer**.

Example

```c
int *p;

*p = 10;
```

Wrong.

Memory

```text
p

↓

??????
```

The pointer contains a random address.

Writing through it may

- Crash the program
- Corrupt memory
- Overwrite important data

---

# Correct

```c
int *p = NULL;
```

or

```c
int x = 10;

int *p = &x;
```

---

# 4. Dangling Pointer

A dangling pointer points to memory that has already been released.

Example

```c
int *p = malloc(sizeof(int));

*p = 100;

free(p);

printf("%d", *p);
```

Wrong.

Memory

Before

```text
p

↓

Heap Memory

↓

100
```

After free()

```text
Heap Memory

Released

p

↓

Old Address
```

The pointer still contains the old address.

That address is no longer valid.

---

# Correct

```c
free(p);

p = NULL;
```

Now

```text
p

↓

NULL
```

No accidental access.

---

# Another Example

```c
int *p = malloc(sizeof(int));

free(p);

free(p);
```

Wrong.

Second free()

attempts to free memory that has already been released.

This is called **Double Free**.

---

# Correct

```c
free(p);

p = NULL;

free(p);
```

Calling `free(NULL)` is safe.

---

# 5. Void Pointer

A void pointer is a **generic pointer**.

It can store the address of any data type.

Example

```c
int x = 10;

void *p = &x;
```

Memory

```text
p

↓

x
```

But

```c
printf("%d", *p);
```

Wrong.

Compiler doesn't know the type.

---

# Correct

```c
printf("%d", *(int *)p);
```

Type cast first.

---

# Another Example

```c
float f = 3.5;

void *p = &f;

printf("%.1f", *(float *)p);
```

Output

```text
3.5
```

---

# Why Use void* ?

Generic libraries.

Examples

```text
malloc()

qsort()

bsearch()

memcpy()
```

All use `void *` because they work with any data type.

---

# 6. Pointer Safety Rules

Always

✔ Initialize pointers.

✔ Check malloc() return value.

✔ Free allocated memory.

✔ Set pointer to NULL after free().

✔ Check for NULL before dereferencing when appropriate.

Never

✘ Dereference NULL.

✘ Dereference wild pointers.

✘ Access freed memory.

✘ Free stack variables.

✘ Free the same memory twice.

---

# 7. Common Pointer Bugs

## Bug 1

Uninitialized Pointer

```c
int *p;

*p = 10;
```

Reason

Wild pointer.

---

## Bug 2

NULL Dereference

```c
int *p = NULL;

printf("%d", *p);
```

---

## Bug 3

Use After Free

```c
free(p);

*p = 100;
```

Memory already released.

---

## Bug 4

Double Free

```c
free(p);

free(p);
```

---

## Bug 5

Freeing Stack Memory

```c
int x = 10;

free(&x);
```

Wrong.

Only heap memory can be freed.

---

## Bug 6

Returning Address of Local Variable

```c
int* fun()
{
    int x = 10;

    return &x;
}
```

Wrong.

When the function returns

```text
Stack Frame

Destroyed
```

Returned pointer becomes dangling.

Correct

Use

- dynamic allocation
- static variable
- or let the caller provide storage

---

# 8. Memory Diagrams

Example

```c
int x = 50;

int *p = &x;
```

Memory

```text
+---------+
| p=1000  |
+---------+
     |
     |
     V
+---------+
| x = 50  |
+---------+
```

---

After

```c
p = NULL;
```

Memory

```text
+---------+
| p=NULL  |
+---------+
```

---

After

```c
free(p);
```

Correct sequence

```c
free(p);

p = NULL;
```

Memory

```text
Heap

Released


p

↓

NULL
```

---

# 9. Frequently Asked Interview Questions

### Q1. Difference between NULL pointer and Wild pointer?

NULL Pointer

- Intentionally points to nothing.
- Safe to compare against NULL.

Wild Pointer

- Uninitialized.
- Contains an unpredictable address.

---

### Q2. Difference between Wild pointer and Dangling pointer?

Wild Pointer

Never initialized.

Dangling Pointer

Was valid earlier, but now points to released memory.

---

### Q3. Why set pointer to NULL after free()?

Prevents accidental use of freed memory and helps avoid double-free bugs.

---

### Q4. What is a void pointer?

A generic pointer that can point to any data type.

It must be type-cast before dereferencing.

---

### Q5. Can we dereference a void pointer?

No.

Example

Wrong

```c
void *p;

*p;
```

Correct

```c
*(int *)p;
```

---

### Q6. Why is returning the address of a local variable wrong?

Local variables are stored on the stack.

After the function returns

```text
Stack Frame

Destroyed
```

The returned pointer refers to invalid memory.

---

### Q7. Is free(NULL) valid?

Yes.

The C standard specifies that calling `free(NULL)` has no effect.

---

# 10. Quick Revision

✓ NULL pointer → points to nothing.

✓ Wild pointer → uninitialized pointer.

✓ Dangling pointer → points to freed memory.

✓ Void pointer → generic pointer.

✓ Always initialize pointers.

✓ Free every allocated block exactly once.

✓ Set pointers to NULL after free() when they may be reused.

✓ Never return the address of a local variable.

✓ Never free stack memory.

✓ Never dereference NULL, wild, or dangling pointers.

---

# Next Part

**Part 3A.4 – Pointer Interview Programs & Output Questions**

Topics

- 30+ Pointer Programs
- Memory Tracing
- Output Prediction
- Common Interview Questions
- Line-by-Line Explanation
- Best Practices

------------------------
# C Interview Handbook
# Part 3A.4 - Pointer Interview Programs & Output Questions

---

# Table of Contents

1. Basic Pointer Questions
2. Pointer Modification
3. Pointer Assignment
4. Function Arguments
5. Common Mistakes
6. Output Prediction
7. Quick Revision

---

# Q1. Basic Pointer

```c
#include <stdio.h>

int main()
{
    int x = 10;

    int *p = &x;

    printf("%d\n", *p);

    return 0;
}
```

Output

```text
10
```

Explanation

```
x = 10

p

↓

Address of x

↓

*p

↓

10
```

---

# Q2. Modify Variable Using Pointer

```c
#include <stdio.h>

int main()
{
    int x = 10;

    int *p = &x;

    *p = 50;

    printf("%d\n", x);

    return 0;
}
```

Output

```text
50
```

Explanation

```
*p

↓

Changes x directly
```

---

# Q3. Address Operator

```c
#include <stdio.h>

int main()
{
    int x = 20;

    printf("%p\n", (void *)&x);

    return 0;
}
```

Output

```text
Address of x
```

Example

```text
0x7ffd1234
```

Address changes every execution.

---

# Q4. Pointer Stores Address

```c
#include <stdio.h>

int main()
{
    int x = 25;

    int *p = &x;

    printf("%p\n", (void *)p);

    printf("%p\n", (void *)&x);

    return 0;
}
```

Output

Both addresses are identical.

Reason

```
p stores address of x
```

---

# Q5. Pointer Copy

```c
#include <stdio.h>

int main()
{
    int x = 10;

    int *p = &x;

    int *q = p;

    *q = 100;

    printf("%d\n", x);

    return 0;
}
```

Output

```text
100
```

Explanation

Both pointers point to the same variable.

---

# Q6. Pointer Reassignment

```c
#include <stdio.h>

int main()
{
    int a = 10;

    int b = 20;

    int *p = &a;

    printf("%d\n", *p);

    p = &b;

    printf("%d\n", *p);

    return 0;
}
```

Output

```text
10
20
```

Explanation

Pointer now points to b instead of a.

---

# Q7. Pass by Value

```c
#include <stdio.h>

void change(int x)
{
    x = 100;
}

int main()
{
    int a = 10;

    change(a);

    printf("%d\n", a);

    return 0;
}
```

Output

```text
10
```

Explanation

A copy of `a` is modified.

---

# Q8. Pass by Address

```c
#include <stdio.h>

void change(int *p)
{
    *p = 100;
}

int main()
{
    int a = 10;

    change(&a);

    printf("%d\n", a);

    return 0;
}
```

Output

```text
100
```

Explanation

The original variable is modified through its address.

---

# Q9. NULL Pointer

```c
#include <stdio.h>

int main()
{
    int *p = NULL;

    if (p == NULL)
    {
        printf("NULL Pointer\n");
    }

    return 0;
}
```

Output

```text
NULL Pointer
```

---

# Q10. Wild Pointer

```c
int *p;

*p = 10;
```

Output

```text
Undefined Behavior
```

Reason

`p` contains an unknown address.

---

# Q11. Dangling Pointer

```c
#include <stdlib.h>

int main()
{
    int *p = malloc(sizeof(int));

    free(p);

    *p = 10;
}
```

Output

```text
Undefined Behavior
```

Reason

Memory has already been released.

---

# Q12. Double Free

```c
#include <stdlib.h>

int main()
{
    int *p = malloc(sizeof(int));

    free(p);

    free(p);
}
```

Output

```text
Undefined Behavior
```

Reason

The same memory block is freed twice.

---

# Q13. Returning Local Variable Address

```c
int* fun()
{
    int x = 10;

    return &x;
}
```

Output

```text
Undefined Behavior
```

Reason

`x` is destroyed when the function returns.

---

# Q14. Pointer Comparison

```c
#include <stdio.h>

int main()
{
    int x = 10;

    int *p = &x;

    int *q = &x;

    if (p == q)
    {
        printf("Equal\n");
    }

    return 0;
}
```

Output

```text
Equal
```

Reason

Both pointers store the same address.

---

# Q15. Pointer to Pointer (Preview)

```c
#include <stdio.h>

int main()
{
    int x = 10;

    int *p = &x;

    int **pp = &p;

    printf("%d\n", **pp);

    return 0;
}
```

Output

```text
10
```

Memory

```
pp

↓

p

↓

x

↓

10
```

---

# Most Frequently Asked Interview Questions

1. What is a pointer?
2. Why do we use pointers?
3. Difference between `&` and `*`?
4. What is a NULL pointer?
5. What is a wild pointer?
6. What is a dangling pointer?
7. What is a void pointer?
8. Why should `malloc()` be checked?
9. Why set a pointer to `NULL` after `free()`?
10. Why can't we return the address of a local variable?
11. Difference between pass by value and pass by address?
12. Can two pointers point to the same variable?
13. What is pointer dereferencing?
14. Does pointer size depend on data type?
15. What is Undefined Behavior?

---

# Quick Revision

✓ Pointer stores an address.

✓ `&` returns an address.

✓ `*` accesses the value at an address.

✓ Passing a pointer allows a function to modify the original variable.

✓ Multiple pointers can refer to the same object.

✓ Never dereference NULL, wild, or dangling pointers.

✓ Never return the address of a local variable.

✓ Always free dynamically allocated memory exactly once.

---

# Pointer Fundamentals Completed ✅

You now understand:
- Pointer basics
- Address and dereference operators
- Pointer assignment
- Function arguments
- NULL, wild, dangling pointers
- Void pointers
- Common interview questions

---

# Next Chapter

**Part 3B - Pointer Arithmetic (Very Important)**

Topics:
- `p++`, `p--`
- `p + n`
- `p - n`
- Pointer subtraction
- Why `p + 1` doesn't always add 1 byte
- Arrays and pointer arithmetic
- Memory diagrams
- 40+ interview questions
--------------------------------
# C Interview Handbook
# Part 3B - Pointer Arithmetic

---

# Table of Contents

1. What is Pointer Arithmetic?
2. Why Pointer Arithmetic Exists
3. Pointer Increment (p++)
4. Pointer Decrement (p--)
5. Pointer Addition
6. Pointer Subtraction
7. Difference Between Two Pointers
8. Pointer Comparison
9. Why p+1 Doesn't Mean Next Byte
10. Memory Diagrams
11. Common Mistakes
12. Interview Questions
13. Quick Revision

---

# 1. What is Pointer Arithmetic?

Pointer arithmetic means performing arithmetic operations on pointers.

Allowed operations

```text
++
--
+
-
Comparison
Difference
```

Not Allowed

```text
*
/
%
```

Example

```c
int arr[5] = {10,20,30,40,50};

int *p = arr;

p++;
```

---

# 2. Why Pointer Arithmetic Exists?

Pointers are mainly used to traverse arrays.

Example

```c
int arr[5]={10,20,30,40,50};

int *p=arr;
```

Memory

```text
Address     Value

1000        10
1004        20
1008        30
1012        40
1016        50
```

Pointer

```text
p

↓

1000
```

---

# 3. Pointer Increment

Example

```c
int arr[]={10,20,30};

int *p=arr;

printf("%d\n",*p);

p++;

printf("%d\n",*p);
```

Output

```text
10
20
```

Memory

Before

```text
p

↓

1000
```

After

```text
p++

↓

1004
```

Notice

It moved **4 bytes** because

```text
sizeof(int)=4
```

---

# Important Rule

```
p + 1

=

Current Address

+

sizeof(DataType)
```

For

```c
int *p;
```

```
p+1

↓

4 bytes
```

---

For

```c
char *p;
```

```
p+1

↓

1 byte
```

---

For

```c
double *p;
```

```
p+1

↓

8 bytes
```

---

# Why?

The compiler knows the pointer type.

It automatically moves to the **next object**, not simply the next byte.

---

# 4. Pointer Decrement

Example

```c
int arr[]={10,20,30};

int *p=&arr[2];

printf("%d\n",*p);

p--;

printf("%d\n",*p);
```

Output

```text
30
20
```

Memory

```text
1000 10

1004 20

1008 30

^

p
```

After

```text
1004

20
```

---

# 5. Pointer Addition

Example

```c
int arr[]={10,20,30,40,50};

int *p=arr;

p=p+3;

printf("%d",*p);
```

Output

```text
40
```

Explanation

```
1000

+

3×4

=

1012
```

---

# Memory Diagram

```
Address

1000

↓

10

1004

↓

20

1008

↓

30

1012

↓

40

1016

↓

50
```

After

```text
p+3

↓

1012

↓

40
```

---

# 6. Pointer Subtraction

Example

```c
int arr[]={10,20,30,40};

int *p=&arr[3];

p=p-2;

printf("%d",*p);
```

Output

```text
20
```

---

# 7. Difference Between Two Pointers

Pointers pointing into the same array can be subtracted.

Example

```c
int arr[10];

int *p=&arr[8];

int *q=&arr[3];

printf("%ld",p-q);
```

Output

```text
5
```

Important

Result is **number of elements**, **not bytes**.

---

Memory

```text
0

1

2

3 ← q

4

5

6

7

8 ← p
```

Difference

```
8-3

=

5
```

---

# 8. Pointer Comparison

Pointers can be compared.

Example

```c
int arr[5];

int *p=&arr[1];

int *q=&arr[3];

if(p<q)
    printf("True");
```

Output

```text
True
```

Comparison is meaningful only when both pointers point into the **same array (or one past the end)**.

---

# 9. Why Doesn't p+1 Mean One Byte?

Example

```c
int *p;
```

Suppose

```
p=1000
```

Many beginners think

```
p+1

↓

1001
```

Wrong.

Compiler calculates

```
1000

+

sizeof(int)

=

1004
```

---

Example

```c
char *c;
```

```
c=500
```

After

```
c+1

↓

501
```

Because

```
sizeof(char)=1
```

---

Example

```c
double *d;
```

Suppose

```
d=8000
```

After

```
d+1

↓

8008
```

---

# 10. Memory Walk

Example

```c
int arr[]={5,10,15,20};

int *p=arr;
```

Step 1

```
p

↓

5
```

Step 2

```c
p++;
```

```
p

↓

10
```

Step 3

```c
p++;
```

```
p

↓

15
```

Step 4

```c
p--;
```

```
p

↓

10
```

---

# 11. Common Mistakes

## Mistake 1

```c
int x=10;

int *p=&x;

p++;
```

Allowed, but now `p` no longer points to `x`. Dereferencing it is generally invalid because it doesn't point to another valid `int` object.

---

## Mistake 2

```c
int *p=NULL;

p++;
```

Pointer arithmetic on a NULL pointer results in a pointer that is still not valid to dereference. Avoid doing this.

---

## Mistake 3

```c
int a;

int b;

int *p=&a;

int *q=&b;

printf("%ld",p-q);
```

Subtracting pointers that do not point into the same array is **Undefined Behavior**.

---

# 12. Frequently Asked Interview Questions

### Q1. Why does p++ move 4 bytes?

Because

```
sizeof(int)=4
```

---

### Q2. Why does char pointer move only one byte?

Because

```
sizeof(char)=1
```

---

### Q3. Can we add two pointers?

No.

```c
p+q
```

Invalid.

---

### Q4. Can we subtract two pointers?

Yes, but only if both point into the same array (or one past the end).

---

### Q5. What does p-q return?

Number of elements between the two pointers.

---

### Q6. Why is pointer arithmetic useful?

It allows efficient traversal of arrays and contiguous memory blocks.

---

### Q7. Is pointer arithmetic allowed on void*?

In standard C, **no**. Since `void` has no size, the compiler cannot determine how far to move. Some compilers (like GCC) support it as a non-standard extension.

---

# Quick Revision

✓ `p++` moves to the next element.

✓ Movement depends on the pointed-to type.

✓ `int*` → typically +4 bytes.

✓ `char*` → +1 byte.

✓ `double*` → typically +8 bytes.

✓ Pointer subtraction returns the number of elements.

✓ Do not add two pointers.

✓ Compare or subtract pointers only when they refer to the same array.

---

# Next Chapter

**Part 3C - Arrays and Pointers**

Topics

- Array Name as Pointer
- `arr` vs `&arr`
- `arr[i]` vs `*(arr+i)`
- Pointer Indexing
- Pointer vs Array
- Pointer to Array
- Array of Pointers
- Multidimensional Arrays
- Passing Arrays to Functions
- Memory Diagrams
- 50+ Interview Questions

-------------------------
