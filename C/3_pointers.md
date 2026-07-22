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

# C Interview Handbook
# Part 3C.1 - Arrays vs Pointers

---

# Table of Contents

1. Introduction
2. Array Memory Layout
3. Array Name
4. Array Name Decays to Pointer
5. arr vs &arr
6. arr[i] vs *(arr+i)
7. Pointer Indexing
8. Pointer vs Array
9. sizeof(Array) vs sizeof(Pointer)
10. Common Mistakes
11. Interview Questions
12. Quick Revision

---

# 1. Introduction

Arrays and pointers are closely related in C, but **they are NOT the same thing**.

Many interview questions are designed to test whether you understand the difference.

Remember:

> **An array is a collection of elements.**
>
> **A pointer is a variable that stores an address.**

---

# 2. Array Memory Layout

Example

```c
int arr[5] = {10,20,30,40,50};
```

Suppose

```text
sizeof(int) = 4
```

Memory

```text
Address      Value

1000         10
1004         20
1008         30
1012         40
1016         50
```

Diagram

```text
          arr

           |

           V

+------+------+------+------+------+
|  10  | 20  | 30  | 40  | 50  |
+------+------+------+------+------+

1000   1004  1008  1012  1016
```

Each integer occupies 4 bytes.

---

# 3. Array Name

The array name represents the beginning of the array.

Example

```c
int arr[5];
```

Expression

```c
arr
```

means

```text
Address of first element
```

Therefore

```text
arr

↓

&arr[0]
```

Example

```c
printf("%p\n",(void *)arr);

printf("%p\n",(void *)&arr[0]);
```

Output

Both addresses are identical.

---

# 4. Array Name Decays to Pointer

In most expressions, the array name automatically converts (decays) to a pointer to its first element.

Example

```c
int arr[5];

int *p = arr;
```

Actually means

```c
int *p = &arr[0];
```

Memory

```text
p

↓

arr[0]

↓

10
```

---

# Important Rule

Array name decays into

```text
Pointer to First Element
```

except in a few situations:

- `sizeof(arr)`
- `&arr`
- string literal initialization

---

# 5. arr vs &arr

This is a favorite interview question.

Example

```c
int arr[5];
```

### arr

Type

```text
int *
```

Value

```text
Address of first element
```

Suppose

```text
1000
```

---

### &arr

Type

```text
int (*)[5]
```

(pointer to an array of 5 integers)

Value

```text
Address of entire array
```

Also

```text
1000
```

Both print the same address, but **their types are different**.

---

# Pointer Arithmetic Difference

```c
arr + 1
```

Moves by one integer.

Suppose

```
1000
```

After

```
1004
```

---

Now

```c
&arr + 1
```

Moves by the size of the whole array.

```
1000

+

20 bytes

=

1020
```

because

```
5 × sizeof(int)

=

20
```

---

Example

```c
#include <stdio.h>

int main()
{
    int arr[5];

    printf("%p\n", (void *)arr);

    printf("%p\n", (void *)(arr + 1));

    printf("%p\n", (void *)&arr);

    printf("%p\n", (void *)(&arr + 1));
}
```

Observe that:

- `arr + 1` advances to the next `int`.
- `&arr + 1` advances past the entire array.

---

# 6. arr[i] vs *(arr+i)

These are exactly equivalent.

Example

```c
int arr[] = {10,20,30};
```

Expression

```c
arr[1]
```

Compiler converts it into

```c
*(arr + 1)
```

Explanation

```
arr

↓

1000

+

1×4

↓

1004

↓

20
```

Therefore

```text
arr[1]

=

*(arr+1)

=

20
```

---

More Examples

```c
arr[0] == *(arr+0)

arr[1] == *(arr+1)

arr[2] == *(arr+2)
```

All are true.

---

# 7. Pointer Indexing

Example

```c
int arr[]={5,10,15};

int *p=arr;
```

Then

```c
p[0]
```

means

```c
*(p+0)
```

---

Similarly

```c
p[2]
```

means

```c
*(p+2)
```

Output

```text
15
```

This is why pointers can be used like arrays.

---

# 8. Pointer vs Array

Example

```c
int arr[5];

int *p = arr;
```

They look similar but are different.

| Array | Pointer |
|--------|----------|
| Fixed-size object | Variable that stores an address |
| Cannot be assigned | Can be reassigned |
| `sizeof(arr)` = total array size | `sizeof(p)` = pointer size |
| Storage reserved for all elements | Stores only one address |

---

Example

```c
p++;
```

Valid.

---

Example

```c
arr++;
```

Invalid.

Why?

Because an array name is **not a modifiable lvalue**.

It always refers to the same array.

---

# 9. sizeof(Array) vs sizeof(Pointer)

Example

```c
int arr[5];

int *p = arr;
```

Suppose

```
sizeof(int)=4
```

Then

```c
sizeof(arr)
```

returns

```
20
```

because

```
5 × 4
```

---

Now

```c
sizeof(p)
```

returns

```
8
```

(on a 64-bit system)

because it stores only an address.

---

# 10. Common Mistakes

## Mistake 1

```c
arr++;
```

Wrong.

Array names cannot be incremented.

---

## Mistake 2

```c
arr = p;
```

Wrong.

An array cannot be assigned to after declaration.

---

## Mistake 3

```c
int arr[5];

printf("%d", sizeof(arr));
```

Using `%d` for `sizeof` is not portable.

Correct

```c
printf("%zu", sizeof(arr));
```

---

## Mistake 4

Thinking

```text
Array == Pointer
```

Wrong.

Arrays often decay to pointers, but they are different types.

---

# Frequently Asked Interview Questions

### Q1. Is an array a pointer?

No.

An array is an object containing elements.

A pointer is a variable storing an address.

---

### Q2. Why does `arr` behave like a pointer?

Because in most expressions it **decays** to a pointer to its first element.

---

### Q3. Why is `arr++` invalid?

Because the array name is not a modifiable variable.

---

### Q4. Why is `p++` valid?

Because `p` is a pointer variable and can be changed to point elsewhere.

---

### Q5. What is the difference between `arr` and `&arr`?

- `arr` is (after decay) a pointer to the first element (`int *`).
- `&arr` is a pointer to the entire array (`int (*)[N]`).

They usually print the same address but have different types and different pointer arithmetic.

---

### Q6. Why are `arr[i]` and `*(arr+i)` equivalent?

Array indexing is defined in terms of pointer arithmetic and dereferencing.

---

# Quick Revision

✓ Array stores multiple elements.

✓ Pointer stores one address.

✓ `arr` usually decays to `&arr[0]`.

✓ `arr[i] == *(arr+i)`.

✓ `p[i] == *(p+i)`.

✓ `arr++` ❌ Invalid.

✓ `p++` ✅ Valid.

✓ `sizeof(arr)` = total array size.

✓ `sizeof(pointer)` = size of an address.

✓ `arr` and `&arr` have the same numeric address but different types.

---

# Next Part

**Part 3C.2 – Pointer to Array & Array of Pointers**

Topics

- Pointer to Entire Array
- Array of Pointers
- Pointer Arrays vs 2D Arrays
- String Arrays
- Memory Diagrams
- Interview Questions
-------------------------------
# C Interview Handbook
# Part 3C.2 - Pointer to Array & Array of Pointers

---

# Table of Contents

1. Pointer to an Array
2. Array of Pointers
3. Pointer to Array vs Array of Pointers
4. Strings Using Array of Pointers
5. Memory Diagrams
6. Common Mistakes
7. Interview Questions
8. Quick Revision

---

# 1. Pointer to an Array

A **pointer to an array** stores the address of an entire array.

Syntax

```c
int (*p)[5];
```

Read it as:

> p is a pointer to an array of 5 integers.

Notice the parentheses.

Without them, the meaning changes.

---

## Example

```c
#include <stdio.h>

int main()
{
    int arr[5] = {10,20,30,40,50};

    int (*p)[5] = &arr;

    printf("%d\n", (*p)[0]);
    printf("%d\n", (*p)[2]);
}
```

Output

```text
10
30
```

---

## Memory

```text
arr

+----+----+----+----+----+
|10  |20  |30  |40  |50  |
+----+----+----+----+----+

^

|

p
```

`p` points to the **whole array**, not just the first element.

---

# Why Parentheses?

Consider

```c
int *p[5];
```

This is **NOT** a pointer to an array.

It is

```text
Array of 5 pointers
```

Whereas

```c
int (*p)[5];
```

means

```text
Pointer to one array of 5 integers
```

Always remember

```
()

change the meaning.
```

---

# Pointer Arithmetic

Suppose

```text
Address of arr = 1000
```

Then

```c
p + 1
```

moves by

```
sizeof(arr)

=

5 × sizeof(int)

=

20 bytes
```

New address

```
1020
```

---

# 2. Array of Pointers

An **array of pointers** stores multiple pointer variables.

Syntax

```c
int *p[3];
```

Read it as

> p is an array containing 3 pointers to int.

---

## Example

```c
#include <stdio.h>

int main()
{
    int a = 10;
    int b = 20;
    int c = 30;

    int *p[3];

    p[0] = &a;
    p[1] = &b;
    p[2] = &c;

    printf("%d\n", *p[0]);
    printf("%d\n", *p[1]);
    printf("%d\n", *p[2]);
}
```

Output

```text
10
20
30
```

---

## Memory Diagram

```text
a = 10
b = 20
c = 30

p

+---------+
| &a      |
+---------+
| &b      |
+---------+
| &c      |
+---------+

Each element of p is a pointer.
```

---

# Accessing Data

```c
*p[0]
```

means

```text
Dereference pointer stored in p[0]
```

Result

```text
10
```

Similarly

```c
*p[1]
```

returns

```text
20
```

---

# 3. Pointer to Array vs Array of Pointers

| Pointer to Array | Array of Pointers |
|------------------|-------------------|
| `int (*p)[5]` | `int *p[5]` |
| One pointer | Five pointers |
| Points to an entire array | Each element points somewhere |
| Pointer arithmetic jumps by the whole array | Pointer arithmetic on each element behaves like a normal pointer |

---

## Visual Difference

### Pointer to Array

```text
        p
        |
        V

+----+----+----+----+----+
|10  |20  |30  |40  |50  |
+----+----+----+----+----+
```

---

### Array of Pointers

```text
p

+-----+
| &a  |
+-----+
| &b  |
+-----+
| &c  |
+-----+

 |      |      |
 V      V      V

10     20     30
```

---

# 4. Strings Using Array of Pointers

This is a very common use case.

```c
#include <stdio.h>

int main()
{
    char *names[] =
    {
        "Alice",
        "Bob",
        "Charlie"
    };

    printf("%s\n", names[0]);
    printf("%s\n", names[2]);
}
```

Output

```text
Alice
Charlie
```

---

## Memory

```text
names

+------------+
| ---------- |----> "Alice"
+------------+
| ---------- |----> "Bob"
+------------+
| ---------- |----> "Charlie"
+------------+
```

Each array element stores the address of the first character of a string.

---

# 5. Pointer to 2D Array (Preview)

Suppose

```c
int arr[3][4];
```

Pointer

```c
int (*p)[4] = arr;
```

Meaning

```
p

↓

One complete row

↓

4 integers
```

This is why the column size is required when passing a 2D array to a function.

(We'll study this in Part 3C.3.)

---

# 6. Common Mistakes

## Mistake 1

Confusing

```c
int *p[5];
```

with

```c
int (*p)[5];
```

They are completely different declarations.

---

## Mistake 2

```c
int (*p)[5];

printf("%d", *p);
```

Wrong format specifier and wrong expression.

`*p` is an array, not an `int`.

To access an element

```c
printf("%d\n", (*p)[0]);
```

---

## Mistake 3

Forgetting parentheses

```c
int *p[5];
```

is **not** the same as

```c
int (*p)[5];
```

---

# 7. Frequently Asked Interview Questions

### Q1. What is a pointer to an array?

A pointer whose type is "pointer to an entire array."

Example

```c
int (*p)[5];
```

---

### Q2. What is an array of pointers?

An array where every element is a pointer.

Example

```c
int *p[5];
```

---

### Q3. Why are parentheses required?

Because `[]` has higher precedence than `*`.

Without parentheses

```c
int *p[5];
```

means

```text
Array of pointers
```

With parentheses

```c
int (*p)[5];
```

means

```text
Pointer to array
```

---

### Q4. Which is used for string lists?

Array of pointers.

Example

```c
char *days[] =
{
    "Mon",
    "Tue",
    "Wed"
};
```

---

### Q5. Why is `int (*p)[4]` used with 2D arrays?

Each row contains 4 integers.

The compiler must know the row size to perform pointer arithmetic correctly.

---

# 8. Quick Revision

✓ `int (*p)[5]` → Pointer to one array of 5 integers.

✓ `int *p[5]` → Array containing 5 pointers.

✓ Parentheses completely change the meaning.

✓ Array of pointers is commonly used for strings.

✓ Pointer to array is commonly used with multidimensional arrays.

✓ `[]` has higher precedence than `*`.

---

# Next Part

**Part 3C.3 – Multidimensional Arrays & Pointer Arithmetic**

Topics

- 2D Arrays
- Memory Layout
- Row-major Order
- Pointer Arithmetic in 2D Arrays
- Passing 2D Arrays to Functions
- `arr`, `arr[0]`, `&arr`, and `&arr[0][0]`
- Interview Questions
----------------------------
# C Interview Handbook
# Part 3C.3 - Multidimensional Arrays & Pointer Arithmetic

---

# Table of Contents

1. Introduction
2. Memory Layout of 2D Arrays
3. Row-Major Order
4. Array Name in 2D Arrays
5. Pointer Arithmetic
6. Accessing Elements
7. Passing 2D Arrays to Functions
8. arr vs arr[0] vs &arr vs &arr[0][0]
9. Common Mistakes
10. Interview Questions
11. Quick Revision

---

# 1. Introduction

A multidimensional array is an array whose elements are themselves arrays.

Example

```c
int arr[3][4];
```

Read as

```text
3 rows
4 columns
```

Memory

```text
Row 0

10 20 30 40

Row 1

50 60 70 80

Row 2

90 100 110 120
```

---

# 2. Memory Layout

Example

```c
int arr[3][4] =
{
    {10,20,30,40},
    {50,60,70,80},
    {90,100,110,120}
};
```

Assume

```
sizeof(int)=4
```

Memory

```text
Address     Value

1000        10
1004        20
1008        30
1012        40

1016        50
1020        60
1024        70
1028        80

1032        90
1036        100
1040        110
1044        120
```

Notice

There are **no gaps** between rows.

---

# 3. Row-Major Order

C stores multidimensional arrays in **row-major order**.

Meaning

```
Complete Row 0

↓

Complete Row 1

↓

Complete Row 2
```

Visualization

```text
+----+----+----+----+
|10  |20  |30  |40  |
+----+----+----+----+
|50  |60  |70  |80  |
+----+----+----+----+
|90  |100 |110 |120 |
+----+----+----+----+
```

Memory is continuous.

---

# Formula

```
Address

=

Base Address

+

((Row × Columns)+Column)

×

sizeof(DataType)
```

Example

Find

```
arr[2][1]
```

```
Base =1000

Row=2

Column=1

Columns=4
```

```
1000

+

((2×4)+1)

×

4

=

1000+36

=

1036
```

Address

```
1036
```

Value

```
100
```

---

# 4. Array Name in 2D Arrays

Suppose

```c
int arr[3][4];
```

Then

```c
arr
```

is **not** an `int *`.

It decays to

```text
Pointer to first row
```

Type

```c
int (*)[4]
```

Meaning

```
Pointer

↓

One row

↓

4 integers
```

---

# arr[0]

```
arr[0]
```

is the first row.

In expressions, it decays to

```text
Pointer to first element of row 0
```

Type

```c
int *
```

---

# arr[0][0]

First element.

Type

```text
int
```

---

# 5. Pointer Arithmetic

Example

```c
int arr[3][4];

int (*p)[4] = arr;
```

Initially

```
p

↓

Row0
```

After

```c
p++;
```

Pointer moves by

```
sizeof(one row)

=

4×4

=

16 bytes
```

Now

```
p

↓

Row1
```

---

Example

```c
printf("%d\n", p[1][2]);
```

Same as

```c
printf("%d\n", arr[1][2]);
```

---

# 6. Accessing Elements

Normal

```c
arr[2][3]
```

Pointer form

```c
*(*(arr+2)+3)
```

Explanation

```
arr

↓

Row0

↓

arr+2

↓

Row2

↓

*(arr+2)

↓

First element of Row2

↓

+3

↓

Fourth element

↓

120
```

---

Example

```c
printf("%d\n", *(*(arr+1)+2));
```

Output

```
70
```

---

# 7. Passing 2D Arrays to Functions

Wrong

```c
void display(int arr[][])
{
}
```

Compiler Error.

---

Correct

```c
void display(int arr[][4])
{
}
```

or

```c
void display(int (*arr)[4])
{
}
```

Why?

Compiler must know

```
Column Size
```

to calculate addresses correctly.

---

Example

```c
#include <stdio.h>

void print(int arr[][4], int rows)
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<4;j++)
        {
            printf("%d ",arr[i][j]);
        }

        printf("\n");
    }
}
```

---

# 8. arr vs arr[0] vs &arr vs &arr[0][0]

Suppose

```c
int arr[3][4];
```

| Expression | Meaning | Type |
|------------|---------|------|
| `arr` | Pointer to first row | `int (*)[4]` |
| `arr[0]` | First row (decays to first element) | `int *` |
| `&arr` | Pointer to whole 2D array | `int (*)[3][4]` |
| `&arr[0][0]` | Address of first integer | `int *` |

---

Pointer Arithmetic

```
arr+1

↓

Next Row
```

```
arr[0]+1

↓

Next Integer
```

Very important interview question.

---

# 9. Common Mistakes

## Mistake 1

```c
void fun(int arr[][])
```

Wrong.

Need column size.

---

## Mistake 2

Thinking

```
arr

↓

int*
```

Wrong.

For a 2D array,

```
arr

↓

Pointer to Row
```

---

## Mistake 3

Confusing

```
arr+1
```

with

```
arr[0]+1
```

`arr+1`

Moves to next row.

`arr[0]+1`

Moves to next column.

---

# 10. Frequently Asked Interview Questions

### Q1. How are 2D arrays stored?

Row-major order.

---

### Q2. Why is column size required?

Compiler needs it to compute addresses.

---

### Q3. What is the type of arr?

```
int (*)[Columns]
```

---

### Q4. What is arr[0]?

First row.

Type

```
int *
```

(after decay)

---

### Q5. Difference between

```
arr+1
```

and

```
arr[0]+1
```

`arr+1`

↓

Next row.

`arr[0]+1`

↓

Next column.

---

### Q6. Why is

```
*(*(arr+i)+j)
```

equivalent to

```
arr[i][j]
```

Because array indexing is implemented using pointer arithmetic and dereferencing.

---

# 11. Quick Revision

✓ 2D arrays are stored in row-major order.

✓ Memory is contiguous.

✓ `arr` → pointer to first row.

✓ `arr[0]` → first row (decays to first element).

✓ `arr+1` → next row.

✓ `arr[0]+1` → next column.

✓ `arr[i][j] == *(*(arr+i)+j)`.

✓ Pass the column size when passing a 2D array to a function.

---

# Next Part

**Part 3C.4 – Arrays & Pointers Interview Questions**

Topics

- 40+ Output Prediction Questions
- Memory Tracing
- Pointer Arithmetic Problems
- Array Decay Questions
- 2D Array Questions
- Frequently Asked Interview Programs
----------------------------
# C Interview Handbook
# Part 3C.4 - Arrays & Pointers Interview Questions (Part 1)

---

# Table of Contents

1. Array Basics
2. Pointer Basics
3. Array Decay
4. Pointer Arithmetic
5. Output Prediction
6. Memory Tracing

---

# Q1. What does the array name represent?

```c
#include <stdio.h>

int main()
{
    int arr[5] = {10,20,30,40,50};

    printf("%p\n", (void *)arr);
    printf("%p\n", (void *)&arr[0]);

    return 0;
}
```

Output

```text
Same Address
```

Explanation

```
arr

↓

Address of first element

↓

&arr[0]
```

Therefore

```text
arr == &arr[0]
```

(Value is the same, though their types are different.)

---

# Q2. arr[2] vs *(arr+2)

```c
#include <stdio.h>

int main()
{
    int arr[]={5,10,15,20};

    printf("%d\n", arr[2]);

    printf("%d\n", *(arr+2));

    return 0;
}
```

Output

```text
15
15
```

Explanation

```
arr[2]

↓

*(arr+2)
```

Always equivalent.

---

# Q3. Pointer Indexing

```c
#include <stdio.h>

int main()
{
    int arr[]={1,2,3};

    int *p=arr;

    printf("%d\n", p[2]);

    return 0;
}
```

Output

```text
3
```

Explanation

```
p[2]

↓

*(p+2)
```

---

# Q4. sizeof(Array)

```c
#include <stdio.h>

int main()
{
    int arr[10];

    printf("%zu\n", sizeof(arr));

    return 0;
}
```

Output (Typical)

```text
40
```

Reason

```
10 × sizeof(int)

=

40
```

---

# Q5. sizeof(Pointer)

```c
#include <stdio.h>

int main()
{
    int arr[10];

    int *p=arr;

    printf("%zu\n", sizeof(p));

    return 0;
}
```

Typical Output

```text
8
```

(64-bit system)

Reason

A pointer stores only an address.

---

# Q6. Pointer Increment

```c
#include <stdio.h>

int main()
{
    int arr[]={10,20,30};

    int *p=arr;

    p++;

    printf("%d\n", *p);

    return 0;
}
```

Output

```text
20
```

Explanation

```
p

↓

arr[1]
```

---

# Q7. Pointer Arithmetic

```c
#include <stdio.h>

int main()
{
    int arr[]={10,20,30,40};

    int *p=arr;

    printf("%d\n", *(p+3));

    return 0;
}
```

Output

```text
40
```

---

# Q8. Pointer Difference

```c
#include <stdio.h>

int main()
{
    int arr[10];

    int *p=&arr[8];

    int *q=&arr[3];

    printf("%ld\n", p-q);

    return 0;
}
```

Output

```text
5
```

Explanation

Difference is measured in **elements**, not bytes.

---

# Q9. arr vs &arr

```c
#include <stdio.h>

int main()
{
    int arr[5];

    printf("%p\n",(void *)arr);

    printf("%p\n",(void *)&arr);

    return 0;
}
```

Output

```text
Same numeric address
```

But

Types are different.

```
arr

↓

int *

&arr

↓

int (*)[5]
```

---

# Q10. arr+1 vs &arr+1

```c
#include <stdio.h>

int main()
{
    int arr[5];

    printf("%p\n",(void *)(arr+1));

    printf("%p\n",(void *)(&arr+1));

    return 0;
}
```

Explanation

```
arr+1

↓

Next Integer
```

```
&arr+1

↓

Next Entire Array
```

---

# Q11. Pointer to Pointer

```c
#include <stdio.h>

int main()
{
    int x=10;

    int *p=&x;

    int **pp=&p;

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

# Q12. 2D Array

```c
#include <stdio.h>

int main()
{
    int arr[2][2] =
    {
        {1,2},
        {3,4}
    };

    printf("%d\n", arr[1][0]);

    return 0;
}
```

Output

```text
3
```

---

# Q13. Pointer Form

```c
printf("%d\n", *(*(arr+1)+1));
```

Output

```text
4
```

Explanation

```
arr+1

↓

Second Row

↓

+1

↓

Second Column

↓

4
```

---

# Q14. Valid or Invalid?

```c
arr++;
```

Answer

```text
Invalid
```

Reason

Array names are not modifiable lvalues.

---

# Q15. Valid or Invalid?

```c
int *p=arr;

p++;
```

Answer

```text
Valid
```

Reason

Pointers are variables.

---

# Most Asked Interview Questions

1. Difference between array and pointer?
2. Why does array decay to pointer?
3. Difference between arr and &arr?
4. Difference between arr+1 and &arr+1?
5. Why is arr++ illegal?
6. Why is p++ legal?
7. Why does pointer arithmetic depend on data type?
8. Why is arr[i] equal to *(arr+i)?
9. Why does sizeof(arr) differ from sizeof(pointer)?
10. Why is pointer subtraction measured in elements?

---

# Quick Revision

✓ `arr` usually decays to a pointer to the first element.

✓ `arr[i] == *(arr+i)`.

✓ `p[i] == *(p+i)`.

✓ `arr+1` → next element.

✓ `&arr+1` → past the whole array.

✓ `sizeof(arr)` = total array size.

✓ `sizeof(pointer)` = pointer size.

✓ Pointer subtraction returns the number of elements.

✓ Arrays cannot be incremented.

✓ Pointers can be incremented.

---

# Next Chapter

**Part 3D - Advanced Pointers**

Topics

- Pointer to Pointer
- Triple Pointer
- Function Pointers
- Callback Functions
- const with Pointers
- Pointer to Structure
- Generic Programming using void*

----------------------------------
# C Interview Handbook
# Part 3D.1 - Double Pointers & Triple Pointers

---

# Table of Contents

1. What is a Double Pointer?
2. Why Do We Need Double Pointers?
3. Memory Layout
4. Triple Pointer
5. Passing Pointer to Functions
6. Dynamic Memory Allocation Example
7. Common Mistakes
8. Interview Questions
9. Quick Revision

---

# 1. What is a Double Pointer?

A double pointer is a pointer that stores the address of another pointer.

Syntax

```c
int **pp;
```

Read as

```text
pp is a pointer to a pointer to int.
```

---

# 2. Memory Layout

Example

```c
#include <stdio.h>

int main()
{
    int x = 10;

    int *p = &x;

    int **pp = &p;

    printf("%d\n", x);
    printf("%d\n", *p);
    printf("%d\n", **pp);

    return 0;
}
```

Output

```text
10
10
10
```

---

Memory Diagram

```text
        pp
        |
        V
+---------------+
| Address of p  |
+---------------+
        |
        V
+---------------+
| Address of x  |
+---------------+
        |
        V
+---------------+
|     x = 10    |
+---------------+
```

---

# Access Levels

```text
pp
```

Stores address of `p`

```text
*pp
```

Gives pointer `p`

```text
**pp
```

Gives value of `x`

---

# Example

```c
printf("%p\n", (void *)pp);
printf("%p\n", (void *)*pp);
printf("%d\n", **pp);
```

Meaning

```text
pp   → Address of p

*pp  → Address of x

**pp → Value stored in x
```

---

# 3. Why Do We Need Double Pointers?

They are used when a function needs to modify a pointer itself.

Example

Wrong

```c
void allocate(int *p)
{
    p = malloc(sizeof(int));

    *p = 100;
}
```

```c
int *ptr = NULL;

allocate(ptr);
```

Result

```text
ptr is still NULL
```

Reason

A copy of the pointer was modified.

---

Correct

```c
#include <stdlib.h>

void allocate(int **p)
{
    *p = malloc(sizeof(int));

    if (*p != NULL)
    {
        **p = 100;
    }
}
```

Usage

```c
int *ptr = NULL;

allocate(&ptr);

printf("%d\n", *ptr);

free(ptr);
```

Output

```text
100
```

---

Memory

Before

```text
ptr

↓

NULL
```

Function receives

```text
&ptr
```

Inside

```text
*p

↓

ptr
```

Allocation

```text
ptr

↓

Heap Memory

↓

100
```

---

# 4. Triple Pointer

A triple pointer stores the address of a double pointer.

Syntax

```c
int ***ppp;
```

Example

```c
#include <stdio.h>

int main()
{
    int x = 10;

    int *p = &x;

    int **pp = &p;

    int ***ppp = &pp;

    printf("%d\n", ***ppp);

    return 0;
}
```

Output

```text
10
```

---

Memory Diagram

```text
ppp
 |
 V
pp
 |
 V
p
 |
 V
x
 |
 V
10
```

---

# 5. Passing Pointer to Functions

Example

```c
#include <stdio.h>

void change(int *p)
{
    *p = 50;
}

int main()
{
    int x = 10;

    change(&x);

    printf("%d\n", x);

    return 0;
}
```

Output

```text
50
```

---

Now change the pointer itself.

```c
void update(int **pp)
{
    static int y = 99;

    *pp = &y;
}
```

Usage

```c
int x = 10;

int *p = &x;

update(&p);

printf("%d\n", *p);
```

Output

```text
99
```

Reason

The pointer `p` now points to `y`.

---

# 6. Dynamic Memory Allocation Example

```c
#include <stdio.h>
#include <stdlib.h>

void createArray(int **arr, int size)
{
    *arr = malloc(size * sizeof(int));

    if (*arr == NULL)
        return;

    for (int i = 0; i < size; i++)
    {
        (*arr)[i] = i + 1;
    }
}

int main()
{
    int *arr = NULL;

    createArray(&arr, 5);

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    free(arr);

    return 0;
}
```

Output

```text
1 2 3 4 5
```

---

# 7. Common Mistakes

## Mistake 1

```c
int **pp;

printf("%d", **pp);
```

Wrong

`pp` is uninitialized.

---

## Mistake 2

```c
int *p = NULL;

int **pp = &p;

printf("%d", **pp);
```

Wrong

`*pp` is `NULL`.

Dereferencing it causes Undefined Behavior.

---

## Mistake 3

Forgetting one level of dereference.

```c
*pp
```

returns

```text
Pointer
```

not the actual integer.

Need

```c
**pp
```

---

# 8. Frequently Asked Interview Questions

### Q1. What is a double pointer?

A pointer that stores the address of another pointer.

---

### Q2. Why are double pointers used?

To modify a pointer itself, such as allocating memory inside a function.

---

### Q3. Difference between `*pp` and `**pp`?

```text
*pp  → Pointer (int *)

**pp → Integer value (int)
```

---

### Q4. Where are double pointers commonly used?

- Dynamic memory allocation
- Linked lists
- Trees
- Graphs
- Callback APIs
- Command-line arguments (`char **argv`)
- Arrays of strings

---

### Q5. What is a triple pointer?

A pointer to a double pointer.

Used less frequently, but appears in complex APIs and data structures.

---

# 9. Quick Revision

✓ `int *p` → Pointer to int.

✓ `int **pp` → Pointer to pointer.

✓ `int ***ppp` → Pointer to pointer to pointer.

✓ `*pp` gives the pointer.

✓ `**pp` gives the value.

✓ Use `int **` when a function must modify a pointer.

✓ Always initialize pointers before dereferencing.

✓ Free dynamically allocated memory when it is no longer needed.

---

# Next Part

**Part 3D.2 – Function Pointers & Callback Functions**

Topics

- Function Pointer Syntax
- Calling Functions Through Pointers
- Arrays of Function Pointers
- Callback Functions
- `qsort()` Comparator
- Real-world Linux & Embedded Examples
- Interview Questions

---------------------------------
# C Interview Handbook
# Part 3D.1 - Double Pointers & Triple Pointers

---

# Table of Contents

1. What is a Double Pointer?
2. Why Do We Need Double Pointers?
3. Memory Layout
4. Triple Pointer
5. Passing Pointer to Functions
6. Dynamic Memory Allocation Example
7. Common Mistakes
8. Interview Questions
9. Quick Revision

---

# 1. What is a Double Pointer?

A double pointer is a pointer that stores the address of another pointer.

Syntax

```c
int **pp;
```

Read as

```text
pp is a pointer to a pointer to int.
```

---

# 2. Memory Layout

Example

```c
#include <stdio.h>

int main()
{
    int x = 10;

    int *p = &x;

    int **pp = &p;

    printf("%d\n", x);
    printf("%d\n", *p);
    printf("%d\n", **pp);

    return 0;
}
```

Output

```text
10
10
10
```

---

Memory Diagram

```text
        pp
        |
        V
+---------------+
| Address of p  |
+---------------+
        |
        V
+---------------+
| Address of x  |
+---------------+
        |
        V
+---------------+
|     x = 10    |
+---------------+
```

---

# Access Levels

```text
pp
```

Stores address of `p`

```text
*pp
```

Gives pointer `p`

```text
**pp
```

Gives value of `x`

---

# Example

```c
printf("%p\n", (void *)pp);
printf("%p\n", (void *)*pp);
printf("%d\n", **pp);
```

Meaning

```text
pp   → Address of p

*pp  → Address of x

**pp → Value stored in x
```

---

# 3. Why Do We Need Double Pointers?

They are used when a function needs to modify a pointer itself.

Example

Wrong

```c
void allocate(int *p)
{
    p = malloc(sizeof(int));

    *p = 100;
}
```

```c
int *ptr = NULL;

allocate(ptr);
```

Result

```text
ptr is still NULL
```

Reason

A copy of the pointer was modified.

---

Correct

```c
#include <stdlib.h>

void allocate(int **p)
{
    *p = malloc(sizeof(int));

    if (*p != NULL)
    {
        **p = 100;
    }
}
```

Usage

```c
int *ptr = NULL;

allocate(&ptr);

printf("%d\n", *ptr);

free(ptr);
```

Output

```text
100
```

---

Memory

Before

```text
ptr

↓

NULL
```

Function receives

```text
&ptr
```

Inside

```text
*p

↓

ptr
```

Allocation

```text
ptr

↓

Heap Memory

↓

100
```

---

# 4. Triple Pointer

A triple pointer stores the address of a double pointer.

Syntax

```c
int ***ppp;
```

Example

```c
#include <stdio.h>

int main()
{
    int x = 10;

    int *p = &x;

    int **pp = &p;

    int ***ppp = &pp;

    printf("%d\n", ***ppp);

    return 0;
}
```

Output

```text
10
```

---

Memory Diagram

```text
ppp
 |
 V
pp
 |
 V
p
 |
 V
x
 |
 V
10
```

---

# 5. Passing Pointer to Functions

Example

```c
#include <stdio.h>

void change(int *p)
{
    *p = 50;
}

int main()
{
    int x = 10;

    change(&x);

    printf("%d\n", x);

    return 0;
}
```

Output

```text
50
```

---

Now change the pointer itself.

```c
void update(int **pp)
{
    static int y = 99;

    *pp = &y;
}
```

Usage

```c
int x = 10;

int *p = &x;

update(&p);

printf("%d\n", *p);
```

Output

```text
99
```

Reason

The pointer `p` now points to `y`.

---

# 6. Dynamic Memory Allocation Example

```c
#include <stdio.h>
#include <stdlib.h>

void createArray(int **arr, int size)
{
    *arr = malloc(size * sizeof(int));

    if (*arr == NULL)
        return;

    for (int i = 0; i < size; i++)
    {
        (*arr)[i] = i + 1;
    }
}

int main()
{
    int *arr = NULL;

    createArray(&arr, 5);

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    free(arr);

    return 0;
}
```

Output

```text
1 2 3 4 5
```

---

# 7. Common Mistakes

## Mistake 1

```c
int **pp;

printf("%d", **pp);
```

Wrong

`pp` is uninitialized.

---

## Mistake 2

```c
int *p = NULL;

int **pp = &p;

printf("%d", **pp);
```

Wrong

`*pp` is `NULL`.

Dereferencing it causes Undefined Behavior.

---

## Mistake 3

Forgetting one level of dereference.

```c
*pp
```

returns

```text
Pointer
```

not the actual integer.

Need

```c
**pp
```

---

# 8. Frequently Asked Interview Questions

### Q1. What is a double pointer?

A pointer that stores the address of another pointer.

---

### Q2. Why are double pointers used?

To modify a pointer itself, such as allocating memory inside a function.

---

### Q3. Difference between `*pp` and `**pp`?

```text
*pp  → Pointer (int *)

**pp → Integer value (int)
```

---

### Q4. Where are double pointers commonly used?

- Dynamic memory allocation
- Linked lists
- Trees
- Graphs
- Callback APIs
- Command-line arguments (`char **argv`)
- Arrays of strings

---

### Q5. What is a triple pointer?

A pointer to a double pointer.

Used less frequently, but appears in complex APIs and data structures.

---

# 9. Quick Revision

✓ `int *p` → Pointer to int.

✓ `int **pp` → Pointer to pointer.

✓ `int ***ppp` → Pointer to pointer to pointer.

✓ `*pp` gives the pointer.

✓ `**pp` gives the value.

✓ Use `int **` when a function must modify a pointer.

✓ Always initialize pointers before dereferencing.

✓ Free dynamically allocated memory when it is no longer needed.

---

# Next Part

**Part 3D.2 – Function Pointers & Callback Functions**

Topics

- Function Pointer Syntax
- Calling Functions Through Pointers
- Arrays of Function Pointers
- Callback Functions
- `qsort()` Comparator
- Real-world Linux & Embedded Examples
- Interview Questions
-------------------------
# C Interview Handbook
# Part 3D.2 - Function Pointers & Callback Functions

---

# Table of Contents

1. Why Function Pointers?
2. Function Pointer Syntax
3. Calling Functions Using Function Pointers
4. Passing Function Pointers
5. Callback Functions
6. Array of Function Pointers
7. qsort() Example
8. Real-world Uses
9. Common Mistakes
10. Interview Questions
11. Quick Revision

---

# 1. Why Function Pointers?

Normally we call functions directly.

```c
add(10,20);
```

Sometimes we don't know **which function** should be called until runtime.

Instead of storing data,

we store

```
Address of a Function
```

Function pointers make this possible.

---

# 2. Function Pointer Syntax

Suppose

```c
int add(int a,int b)
{
    return a+b;
}
```

Pointer

```c
int (*fp)(int,int);
```

Read as

```
fp

↓

Pointer

↓

Function

↓

Returns int

↓

Accepts (int,int)
```

Notice the parentheses.

Without them

```c
int *fp(int,int);
```

means

```
Function returning int*
```

NOT

```
Pointer to function
```

---

# 3. Assigning a Function

```c
fp = add;
```

or

```c
fp = &add;
```

Both are valid.

The function name automatically converts to its address.

---

# Calling Through Pointer

Method 1

```c
fp(10,20);
```

Method 2

```c
(*fp)(10,20);
```

Both produce the same result.

---

## Example

```c
#include <stdio.h>

int add(int a,int b)
{
    return a+b;
}

int main()
{
    int (*fp)(int,int)=add;

    printf("%d\n", fp(10,20));

    return 0;
}
```

Output

```text
30
```

---

# Memory Diagram

```text
           fp
           |
           V
+-------------------+
| Address of add()  |
+-------------------+
           |
           V

add()

↓

Machine Instructions
```

---

# 4. Passing Function Pointer

Functions can receive function pointers.

Example

```c
#include <stdio.h>

int add(int a,int b)
{
    return a+b;
}

int sub(int a,int b)
{
    return a-b;
}

int calculate(int x,int y,
              int (*operation)(int,int))
{
    return operation(x,y);
}

int main()
{
    printf("%d\n", calculate(10,5,add));

    printf("%d\n", calculate(10,5,sub));

    return 0;
}
```

Output

```text
15
5
```

Explanation

```
calculate()

↓

Calls whichever function
was passed
```

---

# 5. Callback Functions

A callback is a function that is passed to another function and called later.

Example

```c
#include <stdio.h>

void greet()
{
    printf("Hello\n");
}

void execute(void (*callback)())
{
    callback();
}

int main()
{
    execute(greet);

    return 0;
}
```

Output

```text
Hello
```

Flow

```text
main()

↓

execute()

↓

callback()

↓

greet()
```

---

# Why Callbacks?

They make programs flexible.

Instead of hardcoding behavior,

the caller chooses what should happen.

Examples

- GUI button click
- Timer expiry
- Interrupt handlers
- Network events
- File system notifications

---

# 6. Array of Function Pointers

Example

```c
#include <stdio.h>

int add(int a,int b)
{
    return a+b;
}

int sub(int a,int b)
{
    return a-b;
}

int main()
{
    int (*ops[2])(int,int);

    ops[0]=add;
    ops[1]=sub;

    printf("%d\n", ops[0](10,5));

    printf("%d\n", ops[1](10,5));

    return 0;
}
```

Output

```text
15
5
```

Memory

```text
ops

+----------------+
| Address add()  |
+----------------+
| Address sub()  |
+----------------+
```

---

# 7. qsort() Example

The C standard library uses callbacks.

```c
qsort(array,
      n,
      sizeof(int),
      compare);
```

Comparator

```c
int compare(const void *a,
            const void *b)
{
    return (*(int*)a - *(int*)b);
}
```

Flow

```text
qsort()

↓

Calls compare()

↓

Many Times

↓

Sort Complete
```

This is one of the most famous examples of callback functions in C.

---

# 8. Real-world Uses

Function pointers are used in

### Linux Kernel

```text
File Operations

↓

read()

write()

open()

close()
```

Each driver provides function pointers to implement these operations.

---

### Device Drivers

Different hardware drivers register their own functions.

---

### Networking

Packet receive handlers

Protocol handlers

Socket operations

---

### Embedded Systems

Interrupt Service Routines (ISRs)

Timer callbacks

Peripheral drivers

---

### GUI Libraries

Button click

Mouse event

Keyboard event

Window resize

All use callbacks.

---

# 9. Common Mistakes

## Mistake 1

Wrong declaration

```c
int *fp(int,int);
```

This declares

```
Function returning int*
```

Correct

```c
int (*fp)(int,int);
```

---

## Mistake 2

Calling NULL function pointer

```c
int (*fp)(int,int)=NULL;

fp(1,2);
```

Undefined Behavior.

Always check

```c
if(fp!=NULL)
{
    fp(1,2);
}
```

---

## Mistake 3

Assigning incompatible function

```c
float fun(float,float);

fp=fun;
```

Wrong.

Function signatures must match.

---

# 10. Frequently Asked Interview Questions

### Q1. What is a function pointer?

A pointer that stores the address of a function.

---

### Q2. Why use function pointers?

To choose behavior at runtime.

---

### Q3. What is a callback?

A function passed to another function and invoked later.

---

### Q4. Difference between

```c
fp()
```

and

```c
(*fp)()
```

None.

Both call the function.

---

### Q5. Where are function pointers used?

- Linux kernel
- Device drivers
- GUI frameworks
- Network stacks
- Embedded systems
- Standard library (`qsort`, `bsearch`)

---

### Q6. Why are parentheses required?

Because `()` has higher precedence than `*`.

```c
int (*fp)(int,int);
```

means

```
Pointer to function
```

---

# 11. Quick Revision

✓ Function names decay to function pointers.

✓ `fp = add;` and `fp = &add;` are equivalent.

✓ `fp()` and `(*fp)()` both call the function.

✓ Callbacks are functions passed as arguments.

✓ Arrays of function pointers implement dispatch tables.

✓ Function pointers are heavily used in operating systems, drivers, and event-driven programming.

---

# Next Part

**Part 3D.3 – const with Pointers (Most Confusing Interview Topic)**

Topics

- `const int *p`
- `int *const p`
- `const int *const p`
- Constant Pointer vs Pointer to Constant
- Memory Diagrams
- Interview Questions
-----------------------------------
# C Interview Handbook
# Part 3D.3 - const with Pointers

---

# Table of Contents

1. Why const with Pointers?
2. Pointer to Constant
3. Constant Pointer
4. Constant Pointer to Constant
5. Reading const Declarations
6. Memory Diagrams
7. Common Mistakes
8. Interview Questions
9. Quick Revision

---

# 1. Why const with Pointers?

When using pointers, there are two things that can change:

1. The **data** being pointed to.
2. The **pointer** itself.

`const` lets us prevent changes to either one (or both).

---

# 2. Pointer to Constant

Declaration

```c
const int *p;
```

or

```c
int const *p;
```

Both declarations are identical.

Meaning

```text
Data is constant.

Pointer can change.
```

---

Example

```c
int a = 10;
int b = 20;

const int *p = &a;

p = &b;      // ✓ Allowed

*p = 50;     // ✗ Error
```

Memory

```text
Initially

p
 |
 V
a = 10

Later

p
 |
 V
b = 20
```

The pointer moved, but the data cannot be modified through `p`.

---

# 3. Constant Pointer

Declaration

```c
int *const p = &a;
```

Meaning

```text
Pointer is constant.

Data can change.
```

Example

```c
int a = 10;
int b = 20;

int *const p = &a;

*p = 100;    // ✓ Allowed

p = &b;      // ✗ Error
```

Memory

```text
p
 |
 V
a = 10

Pointer cannot move.
```

---

# 4. Constant Pointer to Constant

Declaration

```c
const int *const p = &a;
```

Meaning

```text
Pointer cannot change.

Data cannot change.
```

Example

```c
int a = 10;

const int *const p = &a;

*p = 20;     // ✗ Error

p = NULL;    // ✗ Error
```

Nothing can change.

---

# 5. Reading const Declarations

A simple rule:

Read from the variable name outward.

---

Example

```c
const int *p;
```

Start at `p`

```
p

↓

Pointer

↓

to const int
```

Meaning

```
Pointer can move.

Data cannot change.
```

---

Example

```c
int *const p;
```

Read

```
p

↓

const pointer

↓

to int
```

Meaning

```
Pointer fixed.

Data writable.
```

---

Example

```c
const int *const p;
```

Read

```
p

↓

const pointer

↓

to const int
```

Meaning

```
Nothing changes.
```

---

# 6. Summary Table

| Declaration | Can modify data? | Can change pointer? |
|-------------|------------------|---------------------|
| `int *p` | ✓ Yes | ✓ Yes |
| `const int *p` | ✗ No | ✓ Yes |
| `int *const p` | ✓ Yes | ✗ No |
| `const int *const p` | ✗ No | ✗ No |

This table is one of the most frequently asked interview questions.

---

# 7. Memory Diagrams

## Normal Pointer

```text
p
 |
 V
10

Data ✓

Pointer ✓
```

---

## Pointer to Constant

```text
p
 |
 V
10

Data ✗

Pointer ✓
```

---

## Constant Pointer

```text
p
 |
 V
10

Data ✓

Pointer ✗
```

---

## Constant Pointer to Constant

```text
p
 |
 V
10

Data ✗

Pointer ✗
```

---

# 8. Function Parameters

Read-only parameter

```c
void print(const int *arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);

        // arr[i] = 0;   // Error
    }
}
```

Why?

The function promises not to modify the array.

---

# Returning const Pointer

Example

```c
const char *getMessage()
{
    return "Hello";
}
```

The caller should treat the returned string as read-only.

---

# 9. Common Mistakes

## Mistake 1

```c
const int *p = &a;

*p = 5;
```

Wrong.

The pointed-to data is treated as read-only through `p`.

---

## Mistake 2

```c
int *const p = &a;

p = &b;
```

Wrong.

The pointer itself is constant.

---

## Mistake 3

Thinking

```c
const int *p;
```

means

```
a itself is const
```

Not necessarily.

It only means you cannot modify `a` **through this pointer**.

If another non-const pointer or direct access exists, `a` may still be modified.

---

# 10. Frequently Asked Interview Questions

### Q1. Difference between

```c
const int *p;
```

and

```c
int *const p;
```

`const int *p`

```
Pointer movable

Data read-only
```

`int *const p`

```
Pointer fixed

Data writable
```

---

### Q2. Why use const?

- Prevent accidental modification.
- Improve code readability.
- Express intent.
- Enable APIs to accept read-only data safely.

---

### Q3. Why use const in function parameters?

To tell callers that the function will not modify the provided data.

---

### Q4. Which declaration prevents both pointer and data changes?

```c
const int *const p;
```

---

### Q5. Are these equivalent?

```c
const int *p;
```

and

```c
int const *p;
```

Yes.

Only the placement of `const` differs.

---

# 11. Quick Revision

✓ `int *p` → Data ✓, Pointer ✓

✓ `const int *p` → Data ✗, Pointer ✓

✓ `int *const p` → Data ✓, Pointer ✗

✓ `const int *const p` → Data ✗, Pointer ✗

✓ Read declarations from the variable name outward.

✓ Use `const` whenever data should not be modified.

---

# Interview Memory Trick

```text
const BEFORE *

↓

Protects DATA


const AFTER *

↓

Protects POINTER
```

Examples

```text
const int *p

↓

Protect DATA


int *const p

↓

Protect POINTER


const int *const p

↓

Protect BOTH
```

---

# Next Part

**Part 3D.4 – Structures, Unions & Pointers**

Topics

- Pointer to Structure
- `.` vs `->`
- Self-Referential Structures
- Linked List Nodes
- Pointer to Union
- Memory Layout
- Interview Questions
-------------------------------

# C Interview Handbook
# Part 3D.4 - Structures, Unions & Pointers

---

# Table of Contents

1. What is a Structure?
2. Pointer to Structure
3. Dot (.) vs Arrow (->) Operator
4. Self-Referential Structures
5. Linked List Node Example
6. Unions
7. Pointer to Union
8. Memory Layout
9. Common Mistakes
10. Interview Questions
11. Quick Revision

---

# 1. What is a Structure?

A structure groups different data types into one object.

Example

```c
struct Student
{
    int id;
    char grade;
    float marks;
};
```

Memory

```text
+-------------------+
| id                |
+-------------------+
| grade             |
+-------------------+
| padding (if any)  |
+-------------------+
| marks             |
+-------------------+
```

The compiler may insert **padding** for alignment.

---

# 2. Pointer to Structure

Example

```c
#include <stdio.h>

struct Student
{
    int id;
    float marks;
};

int main()
{
    struct Student s = {101, 95.5};

    struct Student *p = &s;

    printf("%d\n", p->id);
    printf("%.1f\n", p->marks);

    return 0;
}
```

Output

```text
101
95.5
```

---

Memory

```text
        p
        |
        V

+------------------+
| id = 101         |
| marks = 95.5     |
+------------------+
```

---

# 3. Dot (.) vs Arrow (->)

If you have an object

```c
struct Student s;
```

Use

```c
s.id
```

---

If you have a pointer

```c
struct Student *p;
```

Use

```c
p->id
```

because

```text
p->id

↓

(*p).id
```

These two expressions are identical.

---

Example

```c
printf("%d\n", (*p).id);

printf("%d\n", p->id);
```

Both print the same value.

---

# 4. Self-Referential Structure

A structure can contain a pointer to another structure of the same type.

Example

```c
struct Node
{
    int data;
    struct Node *next;
};
```

Why a pointer?

This would be illegal:

```c
struct Node
{
    int data;
    struct Node next;
};
```

Reason

The compiler would need an infinitely large structure because each `Node` would contain another complete `Node`.

A pointer has a fixed size, so the structure size remains finite.

---

# 5. Linked List Node Example

```c
#include <stdio.h>

struct Node
{
    int data;
    struct Node *next;
};

int main()
{
    struct Node n1 = {10, NULL};
    struct Node n2 = {20, NULL};

    n1.next = &n2;

    printf("%d\n", n1.data);
    printf("%d\n", n1.next->data);

    return 0;
}
```

Output

```text
10
20
```

---

Memory

```text
+------------------+
| data = 10        |
| next ----------+ |
+----------------|-+
                 |
                 V
       +------------------+
       | data = 20        |
       | next = NULL      |
       +------------------+
```

---

# 6. Unions

A union allows multiple members to share the same memory.

Example

```c
union Data
{
    int i;
    float f;
    char c;
};
```

Memory

```text
+------------------+
| Shared Memory    |
+------------------+
```

Only one member should be considered active at a time.

---

Example

```c
#include <stdio.h>

union Data
{
    int i;
    float f;
};

int main()
{
    union Data d;

    d.i = 100;

    printf("%d\n", d.i);

    d.f = 5.5;

    printf("%.1f\n", d.f);

    return 0;
}
```

After assigning `d.f`, the previous value stored in `d.i` is no longer meaningful because both members share the same storage.

---

# Structure vs Union

| Structure | Union |
|-----------|-------|
| Separate memory for each member | Shared memory |
| Members can all hold values simultaneously | One shared storage area |
| Size is typically at least the sum of member sizes (plus padding) | Size equals the largest member (plus any required alignment) |

---

# 7. Pointer to Union

Example

```c
union Data
{
    int i;
    float f;
};

union Data d;

union Data *p = &d;

p->i = 25;

printf("%d\n", p->i);
```

The `->` operator works with unions just as it does with structures.

---

# 8. Memory Layout

Structure

```text
+------+------+
| int  | char |
+------+------+
```

Members occupy different regions of memory.

---

Union

```text
+----------------+
| int / float /  |
| char (shared)  |
+----------------+
```

All members begin at the same address.

---

# 9. Common Mistakes

## Mistake 1

```c
struct Student *p;

p->id = 10;
```

Wrong.

`p` is uninitialized.

---

## Mistake 2

```c
struct Student *p = NULL;

printf("%d\n", p->id);
```

Wrong.

Dereferencing a NULL pointer causes Undefined Behavior.

---

## Mistake 3

```c
struct Node
{
    struct Node next;
};
```

Wrong.

Use a pointer instead:

```c
struct Node *next;
```

---

## Mistake 4

Assuming all union members hold independent values simultaneously.

Incorrect.

They share the same storage.

---

# 10. Frequently Asked Interview Questions

### Q1. Why use structures?

To group related data into one object.

---

### Q2. Why use pointers with structures?

To avoid copying large structures and to build dynamic data structures such as linked lists and trees.

---

### Q3. Difference between `.` and `->`?

`.` accesses a member through an object.

`->` accesses a member through a pointer.

---

### Q4. Why does a linked list use

```c
struct Node *next;
```

instead of

```c
struct Node next;
```

Because a pointer has a fixed size, while embedding another complete `Node` would make the structure impossible to size.

---

### Q5. Difference between structure and union?

Structures allocate storage for each member.

Unions let all members share the same storage.

---

### Q6. When are unions useful?

- Memory-efficient data representations
- Hardware register mappings
- Tagged data (used carefully with an indicator of the active member)
- Embedded systems

---

# 11. Quick Revision

✓ Structures group different data types.

✓ Use `.` with objects.

✓ Use `->` with pointers.

✓ `p->x` is the same as `(*p).x`.

✓ Self-referential structures use pointers.

✓ Linked lists are built using self-referential structures.

✓ Union members share the same memory.

✓ Structures allocate separate storage for members.

---

# Next Part

**Part 3D.5 – Dynamic Memory Allocation (malloc, calloc, realloc, free)**

Topics

- Stack vs Heap
- malloc()
- calloc()
- realloc()
- free()
- Memory Leaks
- Double Free
- Use After Free
- Best Practices
- Interview Questions
----------------------------
# C Interview Handbook
# Part 3D.5 - Dynamic Memory Allocation

---

# Table of Contents

1. Why Dynamic Memory Allocation?
2. Stack vs Heap
3. malloc()
4. calloc()
5. realloc()
6. free()
7. Memory Leaks
8. Common Memory Bugs
9. Best Practices
10. Interview Questions
11. Quick Revision

---

# 1. Why Dynamic Memory Allocation?

Sometimes the required memory size is not known at compile time.

Examples

- Read N numbers from a file
- User enters array size
- Linked Lists
- Trees
- Graphs
- Dynamic buffers

Dynamic memory is allocated at **runtime** from the **heap**.

---

# 2. Stack vs Heap

## Stack

- Automatically managed.
- Stores local variables.
- Fast allocation and deallocation.
- Memory is released when the function returns.

Example

```c
void fun()
{
    int x = 10;
}
```

When `fun()` returns, `x` is automatically destroyed.

---

## Heap

- Managed by the programmer.
- Used for dynamic memory.
- Memory remains allocated until `free()` is called.

Example

```c
int *p = malloc(sizeof(int));
```

---

Comparison

| Stack | Heap |
|-------|------|
| Automatic | Manual |
| Fast | Slower |
| Limited size | Usually larger |
| Released automatically | Must call `free()` |

---

# 3. malloc()

`malloc()` allocates a block of memory.

Syntax

```c
void *malloc(size_t size);
```

Example

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p = malloc(sizeof(int));

    if (p == NULL)
    {
        return 1;
    }

    *p = 100;

    printf("%d\n", *p);

    free(p);

    return 0;
}
```

Output

```text
100
```

---

Memory

Before

```text
p

↓

NULL
```

After `malloc`

```text
p

↓

Heap

↓

Uninitialized Memory
```

---

Important

The contents returned by `malloc()` are **indeterminate** (uninitialized).

Always initialize the memory before reading it.

---

# 4. calloc()

`calloc()` allocates memory and initializes every byte to zero.

Syntax

```c
void *calloc(size_t count, size_t size);
```

Example

```c
int *arr = calloc(5, sizeof(int));
```

Memory

```text
0 0 0 0 0
```

---

Comparison

| malloc() | calloc() |
|----------|-----------|
| One size argument | Count and size |
| Memory uninitialized | Memory zero-initialized |

---

# 5. realloc()

Changes the size of an existing allocation.

Syntax

```c
void *realloc(void *ptr, size_t new_size);
```

Example

```c
int *arr = malloc(3 * sizeof(int));

int *tmp = realloc(arr, 6 * sizeof(int));

if (tmp != NULL)
{
    arr = tmp;
}
else
{
    /* arr is still valid here */
}
```

Why use a temporary pointer?

If `realloc()` fails, it returns `NULL` and the original block remains allocated.

Assigning directly to `arr` would lose the original pointer and leak memory.

---

Possible behavior

```text
Old Block

↓

Reused

or

Moved

↓

New Block
```

The returned pointer may be the same or different.

---

# 6. free()

Releases dynamically allocated memory.

Example

```c
free(p);

p = NULL;
```

Why set to `NULL`?

It helps avoid accidentally using the old pointer later.

---

Memory

Before

```text
p

↓

Heap Memory
```

After

```text
Heap Memory

Released

p

↓

NULL
```

---

# 7. Memory Leaks

A memory leak occurs when allocated memory is no longer reachable and therefore cannot be freed.

Example

```c
int *p = malloc(sizeof(int));

p = NULL;
```

Wrong.

The original allocated block can no longer be accessed.

Correct

```c
free(p);

p = NULL;
```

---

# 8. Common Memory Bugs

## Bug 1 - Use After Free

```c
free(p);

*p = 10;
```

Wrong.

The memory has already been released.

---

## Bug 2 - Double Free

```c
free(p);

free(p);
```

Wrong.

Free the block only once.

---

## Bug 3 - Memory Leak

```c
p = malloc(sizeof(int));

p = malloc(sizeof(int));
```

Wrong.

The first allocation is lost.

---

## Bug 4 - Forgetting NULL Check

```c
int *p = malloc(1000000000000ULL);

*p = 10;
```

Wrong.

If allocation fails, `p` is `NULL`.

Always check

```c
if (p == NULL)
{
    /* Handle allocation failure */
}
```

---

## Bug 5 - Freeing Stack Memory

```c
int x = 10;

free(&x);
```

Wrong.

Only memory obtained from allocation functions such as `malloc`, `calloc`, or `realloc` should be passed to `free()`.

---

# 9. Best Practices

✔ Check every allocation for `NULL`.

✔ Free every allocated block exactly once.

✔ Set pointers to `NULL` after `free()` when appropriate.

✔ Use `calloc()` when zero-initialized memory is required.

✔ Use a temporary pointer with `realloc()`.

✔ Match every successful allocation with a corresponding `free()`.

---

# 10. Frequently Asked Interview Questions

### Q1. Difference between stack and heap?

Stack is automatically managed.

Heap is manually managed.

---

### Q2. Difference between `malloc()` and `calloc()`?

`malloc()`

- Allocates memory.
- Leaves contents uninitialized.

`calloc()`

- Allocates memory.
- Initializes all bytes to zero.

---

### Q3. Why check `malloc()` for `NULL`?

Allocation can fail due to insufficient memory.

---

### Q4. Why use a temporary variable with `realloc()`?

To avoid losing the original allocation if resizing fails.

---

### Q5. What is a memory leak?

Allocated memory that is never freed and is no longer reachable.

---

### Q6. What is use-after-free?

Accessing memory after it has been released.

---

### Q7. Is `free(NULL)` valid?

Yes.

It has no effect.

---

# 11. Quick Revision

✓ Stack memory is automatic.

✓ Heap memory is dynamic.

✓ `malloc()` allocates uninitialized memory.

✓ `calloc()` allocates zero-initialized memory.

✓ `realloc()` resizes an allocation and may move it.

✓ `free()` releases heap memory.

✓ Always check allocation results.

✓ Never use memory after `free()`.

✓ Never free the same allocation twice.

✓ Prevent memory leaks by freeing every successful allocation.

---

# Interview Memory Trick

```text
malloc

↓

Allocate


calloc

↓

Allocate + Clear


realloc

↓

Resize


free

↓

Release
```

---

# Next Part

**Part 3D.6 – Command-Line Arguments & File Handling**

Topics

- `argc`
- `argv`
- `char **argv`
- Reading Command-Line Arguments
- `FILE *`
- `fopen()`
- `fclose()`
- `fscanf()`
- `fprintf()`
- `fgets()`
- Interview Questions
----------------------------
# C Interview Handbook
# Part 3D.6 - Command-Line Arguments & File Handling

---

# Table of Contents

1. Command-Line Arguments
2. argc and argv
3. Memory Layout of argv
4. File Handling Basics
5. File Modes
6. Reading from Files
7. Writing to Files
8. Binary File Operations
9. Common Mistakes
10. Interview Questions
11. Quick Revision

---

# 1. Command-Line Arguments

Programs can receive input directly from the command line.

Example

```bash
./app input.txt output.txt
```

Here

```
argv[0] -> "./app"

argv[1] -> "input.txt"

argv[2] -> "output.txt"
```

---

# 2. argc and argv

Main function

```c
int main(int argc, char *argv[])
{
}
```

Equivalent

```c
int main(int argc, char **argv)
{
}
```

Meaning

```
argc

↓

Number of command-line arguments

argv

↓

Array of pointers to strings
```

---

Example

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);

    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}
```

Run

```bash
./app one two three
```

Output

```text
argc = 4

./app
one
two
three
```

---

# 3. Memory Layout of argv

Suppose

```bash
./app hello world
```

Memory

```text
argv
 |
 +-------> "./app"
 |
 +-------> "hello"
 |
 +-------> "world"
 |
 +-------> NULL
```

Each element of `argv` is a `char *`.

---

# Accessing Characters

```c
argv[1][0]
```

Meaning

```
argv[1]

↓

"hello"

↓

First Character

↓

'h'
```

---

# 4. File Handling Basics

Files are accessed using `FILE *`.

Example

```c
FILE *fp;
```

A file must be opened before reading or writing.

---

# fopen()

Syntax

```c
FILE *fopen(const char *filename,
            const char *mode);
```

Example

```c
FILE *fp = fopen("data.txt", "r");

if(fp == NULL)
{
    printf("Open failed\n");
    return 1;
}
```

---

# fclose()

Always close files.

```c
fclose(fp);
```

This flushes buffered output and releases resources.

---

# 5. File Modes

| Mode | Meaning |
|------|---------|
| `"r"` | Read |
| `"w"` | Write (create or truncate) |
| `"a"` | Append |
| `"r+"` | Read & Write |
| `"w+"` | Read & Write (truncate/create) |
| `"a+"` | Read & Append |
| `"rb"` | Read binary |
| `"wb"` | Write binary |
| `"ab"` | Append binary |

---

# 6. Reading from Files

## fscanf()

```c
FILE *fp = fopen("data.txt","r");

int x;

fscanf(fp,"%d",&x);

printf("%d\n",x);

fclose(fp);
```

---

## fgets()

Reads one line.

```c
char buffer[100];

fgets(buffer,sizeof(buffer),fp);
```

Useful for reading text safely.

---

## fgetc()

Reads one character.

```c
int ch;

while((ch=fgetc(fp))!=EOF)
{
    putchar(ch);
}
```

---

# 7. Writing to Files

## fprintf()

```c
FILE *fp = fopen("out.txt","w");

fprintf(fp,"Age=%d\n",25);

fclose(fp);
```

---

## fputs()

Writes a string.

```c
fputs("Hello\n",fp);
```

---

## fputc()

Writes one character.

```c
fputc('A',fp);
```

---

# 8. Binary File Operations

## fwrite()

```c
int arr[5]={1,2,3,4,5};

FILE *fp=fopen("data.bin","wb");

fwrite(arr,
       sizeof(int),
       5,
       fp);

fclose(fp);
```

---

## fread()

```c
int arr[5];

FILE *fp=fopen("data.bin","rb");

fread(arr,
      sizeof(int),
      5,
      fp);

fclose(fp);
```

Binary I/O is commonly used for structured data.

---

# File Position Functions

## ftell()

Returns the current file position.

```c
long pos = ftell(fp);
```

---

## fseek()

Moves the file pointer.

```c
fseek(fp,0,SEEK_SET);   // Beginning

fseek(fp,0,SEEK_END);   // End

fseek(fp,10,SEEK_CUR);  // Forward 10 bytes
```

---

## rewind()

Moves to the beginning.

```c
rewind(fp);
```

Equivalent to

```c
fseek(fp,0,SEEK_SET);
```

followed by clearing the error and EOF indicators.

---

# 9. Common Mistakes

## Mistake 1

```c
FILE *fp=fopen("abc.txt","r");

fscanf(fp,"%d",&x);
```

Wrong.

Always check

```c
if(fp==NULL)
```

---

## Mistake 2

Forgetting

```c
fclose(fp);
```

May leave buffered data unwritten and leak resources.

---

## Mistake 3

Reading binary data using text functions.

Use

```text
fread()

fwrite()
```

for binary files.

---

## Mistake 4

Ignoring the return values of `fscanf()`, `fread()`, or `fwrite()`.

Always verify that the expected number of items was processed.

---

# 10. Frequently Asked Interview Questions

### Q1. Difference between

```c
char *argv[]
```

and

```c
char **argv
```

None.

They are equivalent in function parameters.

---

### Q2. What is `argc`?

Number of command-line arguments, including the program name.

---

### Q3. Why use `FILE *`?

It represents an open file stream managed by the C standard library.

---

### Q4. Difference between

```text
fprintf()
```

and

```text
fwrite()
```

`fprintf()`

- Formatted text output.

`fwrite()`

- Raw binary output.

---

### Q5. Difference between

```text
fgets()
```

and

```text
fscanf()
```

`fgets()`

- Reads an entire line (up to the buffer limit).

`fscanf()`

- Reads formatted input according to a format string.

---

### Q6. Why close a file?

To flush buffers and release system resources.

---

# 11. Quick Revision

✓ `argc` = Number of arguments.

✓ `argv` = Array of strings.

✓ `argv[0]` = Program name.

✓ `FILE *` represents an open file.

✓ `fopen()` opens a file.

✓ `fclose()` closes a file.

✓ `fprintf()` writes formatted text.

✓ `fscanf()` reads formatted text.

✓ `fread()` and `fwrite()` are for binary I/O.

✓ Always check the result of `fopen()` and other I/O functions.

---

# Interview Memory Trick

```text
Open

↓

Read / Write

↓

Close
```

```
fopen()

↓

fscanf()
fprintf()
fread()
fwrite()

↓

fclose()
```

---

# Next Part

**Part 3E – Preprocessor, Macros & Header Files**

Topics

- `#include`
- `#define`
- Object-like Macros
- Function-like Macros
- Conditional Compilation
- Include Guards
- `#ifdef`, `#ifndef`, `#endif`
- `#pragma once`
- Interview Questions
------------------------------
