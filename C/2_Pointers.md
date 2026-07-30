# Chapter 2 – Pointers
# Part 1 – Pointer Fundamentals

---

# Objectives

After completing this chapter, you should be able to answer questions like:

- What exactly is a pointer?
- Why do we need pointers?
- What is an address?
- How does a pointer store an address?
- What is the difference between `&` and `*`?
- What happens when we dereference a pointer?
- What is a NULL pointer?
- What is a wild pointer?
- What is a dangling pointer?
- Why is `void *` special?
- Why is every pointer 8 bytes on a 64-bit machine?
- How does the CPU access memory through a pointer?

---

# Why Do We Need Pointers?

Every variable occupies memory.

Example:

```c
int age = 25;
```

Suppose the compiler places `age` at memory location **1000**.

```
Memory

Address        Value

1000           25
```

Normally we access it using its name.

```c
printf("%d", age);
```

But sometimes we need to access memory **indirectly**.

Examples:

- Dynamic memory (`malloc`)
- Linked lists
- Trees
- Operating Systems
- Device Drivers
- Function callbacks
- Buffers
- Hardware registers

For this purpose, C provides **pointers**.

---

# What is a Pointer?

A pointer is simply a variable whose value is a memory address.

Example:

```c
int age = 25;

int *ptr = &age;
```

Memory:

```
Address        Value

1000           25      age

2000           1000    ptr
```

Notice carefully:

```
age stores data.

ptr stores an address.
```

This is the most important concept in C.

---

# Visualizing a Pointer

```
          +---------+
age ----> |   25    |
          +---------+
 Address = 1000


          +---------+
ptr ----> | 1000    |
          +---------+
 Address = 2000
```

`ptr` does **not** contain `25`.

It contains the address where `25` is stored.

---

# Address Operator (&)

The address operator returns the address of a variable.

Example:

```c
int x = 50;

printf("%p", &x);
```

Possible output:

```
0x7ffd6c9a8124
```

Here,

```
&x

↓

Address of x
```

---

## Example

```c
#include <stdio.h>

int main(void)
{
    int number = 100;

    printf("Value   : %d\n", number);

    printf("Address : %p\n", (void *)&number);

    return 0;
}
```

Possible output:

```
Value   : 100

Address : 0x7ffc32ab4014
```

The actual address changes every execution.

---

# Why Does the Address Change?

Modern operating systems use **Address Space Layout Randomization (ASLR)**.

Each program execution receives a different virtual address layout.

Benefits:

- Better security
- Makes attacks harder
- Prevents predictable addresses

> **Interview Insight:** If an interviewer asks why pointer values change between runs, ASLR is a good answer.

---

# Declaring a Pointer

General syntax:

```c
data_type *pointer_name;
```

Examples:

```c
int *p;

char *c;

float *f;

double *d;
```

The pointer type indicates the type of object it points to.

---

# Initializing a Pointer

Correct:

```c
int value = 20;

int *p = &value;
```

Memory:

```
Address      Value

1000         20

2000         1000
```

---

Incorrect:

```c
int *p;
```

This pointer contains an unknown value.

Using it causes undefined behavior.

---

# Dereference Operator (*)

The dereference operator accesses the object stored at the address contained in a pointer.

Example:

```c
int value = 40;

int *p = &value;

printf("%d", *p);
```

Memory:

```
Address       Value

1000          40

2000          1000
```

Execution:

```
*p

↓

Look inside p

↓

1000

↓

Read memory at 1000

↓

40
```

Output:

```
40
```

---

# Reading Pointer Declarations

Many beginners get confused by `*`.

Remember:

```
Declaration

*

means

"pointer to"
```

Example:

```c
int *p;
```

Read as:

```
p is a pointer to int
```

---

But inside expressions,

```c
*p
```

means

```
Value stored at the address
```

The symbol has two different meanings depending on context.

---

# Complete Example

```c
#include <stdio.h>

int main(void)
{
    int marks = 95;

    int *ptr = &marks;

    printf("marks = %d\n", marks);

    printf("&marks = %p\n", (void *)&marks);

    printf("ptr = %p\n", (void *)ptr);

    printf("*ptr = %d\n", *ptr);

    return 0;
}
```

Possible output:

```
marks = 95

&marks = 0x7ffd90...

ptr = 0x7ffd90...

*ptr = 95
```

Notice:

```
ptr == &marks
```

and

```
*ptr == marks
```

---

# Modifying Data Through a Pointer

Pointers allow indirect modification.

```c
#include <stdio.h>

int main(void)
{
    int value = 10;

    int *p = &value;

    *p = 99;

    printf("%d\n", value);

    return 0;
}
```

Output:

```
99
```

Memory:

Before:

```
value

10
```

After:

```
*p = 99

↓

value

99
```

---

# Why Is This Useful?

Suppose a function receives a pointer.

```c
void update(int *p)
{
    *p = 500;
}
```

Call:

```c
int x = 10;

update(&x);
```

Memory:

```
Before

x = 10


↓

update()

↓

*p = 500


↓

x = 500
```

This is how C simulates pass-by-reference.

---

# Pointer Size

Many people think pointer size depends on the data type.

It does not.

Example:

```c
int *a;

char *b;

double *c;
```

On a 64-bit machine:

```
sizeof(a) = 8

sizeof(b) = 8

sizeof(c) = 8
```

All pointers have the same size because they all store **addresses**.

---

On a 32-bit machine:

```
sizeof(pointer)

↓

4 bytes
```

On a 64-bit machine:

```
sizeof(pointer)

↓

8 bytes
```

---

# Why Doesn't Pointer Size Depend on the Data Type?

Because a pointer stores an **address**, not the object itself.

```
Pointer

↓

Memory Address

↓

Same size regardless of type
```

The data type only tells the compiler:

- how many bytes to read or write when dereferencing,
- how pointer arithmetic should behave,
- what type checking to enforce.

---

# NULL Pointer

A NULL pointer points to nothing.

```c
int *p = NULL;
```

Memory:

```
p

↓

NULL
```

It does not refer to any valid object.

---

Why use NULL?

Suppose memory allocation fails.

```c
int *p = malloc(sizeof(int));

if(p == NULL)
{
    printf("Allocation Failed\n");
}
```

NULL indicates:

```
No valid memory
```

---

# What Happens If We Dereference NULL?

```c
int *p = NULL;

printf("%d", *p);
```

The program usually crashes.

Reason:

```
NULL

↓

Invalid Address

↓

Segmentation Fault
```

Never dereference a NULL pointer.

---

# Wild Pointer

A wild pointer is an **uninitialized pointer**.

```c
int *p;
```

Memory:

```
p

↓

Unknown Address
```

The value inside `p` is garbage.

Using it:

```c
*p = 10;
```

causes undefined behavior.

Always initialize pointers.

Good:

```c
int *p = NULL;
```

or

```c
int value = 5;

int *p = &value;
```

---

# Dangling Pointer

A dangling pointer points to memory that is no longer valid.

Example:

```c
int *fun(void)
{
    int x = 10;

    return &x;
}
```

Memory:

```
Stack

+------+
|  x   |
+------+

Return

↓

Stack Frame Destroyed
```

Returned pointer:

```
Points Here

↓

Invalid Memory
```

Another example:

```c
int *p = malloc(sizeof(int));

free(p);
```

Now:

```
p

↓

Freed Memory
```

Using

```c
*p = 10;
```

is undefined behavior.

Good practice:

```c
free(p);

p = NULL;
```

---

# void Pointer

A `void *` is a generic pointer.

It can hold the address of any data type.

```c
int x = 10;

void *p = &x;
```

Later:

```c
printf("%d", *(int *)p);
```

Notice the cast.

A `void *` cannot be dereferenced directly because the compiler does not know the size or type of the object.

---

# How the CPU Uses a Pointer

Suppose:

```c
int value = 25;

int *p = &value;
```

Memory:

```
Address       Value

1000          25

2000          1000
```

Execution:

```c
printf("%d", *p);
```

Internally:

```
Read p

↓

1000

↓

Go to address 1000

↓

Read 4 bytes (int)

↓

25

↓

Print
```

The pointer itself is never "followed" magically.

The CPU simply uses its value as a memory address.

---

# Common Interview Questions

## Q1. What is a pointer?

A pointer is a variable that stores the memory address of another object.

---

## Q2. Does a pointer store data?

No.

It stores the address where the data is located.

---

## Q3. Why are pointers needed?

To:

- Access memory indirectly
- Build dynamic data structures
- Pass large objects efficiently
- Share data between functions
- Perform dynamic memory allocation
- Interface with hardware

---

## Q4. What is the difference between `&` and `*`?

```
&

↓

Address of a variable
```

```
*

↓

Value stored at an address
```

---

## Q5. What is a NULL pointer?

A pointer that intentionally points to no valid object.

---

## Q6. What is a wild pointer?

An uninitialized pointer containing an unknown address.

---

## Q7. What is a dangling pointer?

A pointer that refers to memory that has already been released or is no longer valid.

---

## Q8. Why can't we dereference a `void *`?

Because `void` has no size, so the compiler does not know how many bytes to access.

---

# Common Interview Traps

### Trap 1

```c
int *p;

*p = 10;
```

❌ Undefined behavior.

Reason:

`p` is a wild pointer.

---

### Trap 2

```c
int *p = NULL;

*p = 10;
```

❌ Usually causes a segmentation fault.

---

### Trap 3

```c
int x = 5;

int *p = &x;

printf("%p\n", (void *)p);
printf("%d\n", *p);
```

Output:

```
Address of x
5
```

Remember:

- `p` stores the address.
- `*p` accesses the value.

---

# Quick Revision

```
Variable

↓

Stored in Memory

↓

Has an Address

↓

Pointer Stores Address

↓

Dereference Reads/Writes Data

↓

NULL → No Object

↓

Wild Pointer → Uninitialized

↓

Dangling Pointer → Invalid Object

↓

void * → Generic Pointer
```

---

# Key Interview Takeaways

✅ A pointer stores an **address**, not the data.

✅ `&` gives the address of a variable.

✅ `*` accesses the value stored at that address.

✅ Pointer size depends on the **architecture**, not the pointed-to type.

✅ Always initialize pointers.

✅ Never dereference a NULL, wild, or dangling pointer.

✅ Understand what the CPU does when evaluating `*p`—this is a favorite systems interview topic.
------------------------------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 2 – Pointers
# Part 2 – Pointer Arithmetic

---

# Objectives

After completing this chapter, you should be able to answer:

- What is pointer arithmetic?
- Why does `p + 1` not always add 1 byte?
- Why does pointer arithmetic depend on data type?
- What happens internally when we increment a pointer?
- Can we add two pointers?
- Can we subtract two pointers?
- Why is pointer arithmetic only valid within the same array?
- What is the difference between `p++` and `++p`?

---

# Why Pointer Arithmetic Exists

Suppose we have an array.

```c
int arr[5] = {10,20,30,40,50};
```

Memory:

```
Address        Value

1000           10
1004           20
1008           30
1012           40
1016           50
```

Now suppose

```c
int *p = arr;
```

Memory

```
p

↓

1000
```

How can we move to the next integer?

One possibility:

```
1004
```

But we don't want programmers to manually calculate addresses.

Instead C provides

```c
p + 1
```

The compiler automatically computes the correct address.

---

# What Does p + 1 Mean?

Many beginners think

```
p + 1

↓

Address + 1 byte
```

This is **wrong**.

Pointer arithmetic always moves by the size of the pointed-to type.

Example

```c
int *p;
```

```
p + 1

↓

sizeof(int)

↓

Usually 4 bytes
```

---

# Example

```c
#include <stdio.h>

int main(void)
{
    int arr[] = {10,20,30};

    int *p = arr;

    printf("%p\n", (void *)p);

    printf("%p\n", (void *)(p+1));

    printf("%p\n", (void *)(p+2));

    return 0;
}
```

Possible Output

```
0x1000

0x1004

0x1008
```

Notice

```
Address

↓

1000

↓

1004

↓

1008
```

The address increases by 4 bytes because an `int` occupies 4 bytes on most systems.

---

# Internal Working

Compiler sees

```c
p + 1
```

Internally it becomes

```
Address stored in p

+

sizeof(int)

↓

New Address
```

If

```
p = 1000
```

then

```
p + 1

↓

1000 + 4

↓

1004
```

---

# Pointer Arithmetic Depends on Data Type

Example

```c
char *c;

short *s;

int *i;

double *d;
```

Suppose all contain address 1000.

```
char *

1000

↓

1001
```

```
short *

1000

↓

1002
```

```
int *

1000

↓

1004
```

```
double *

1000

↓

1008
```

because

```
char

↓

1 byte
```

```
short

↓

2 bytes
```

```
int

↓

4 bytes
```

```
double

↓

8 bytes
```

---

# Why?

Suppose

```c
int arr[3];
```

Memory

```
Address      Value

1000         arr[0]

1004         arr[1]

1008         arr[2]
```

If `p + 1` increased by only one byte,

```
1001
```

it would point into the middle of an integer.

That would be useless.

Therefore C advances by one **element**, not one byte.

---

# Increment Operator

Example

```c
int arr[] = {5,10,15};

int *p = arr;
```

Initially

```
p

↓

arr[0]
```

After

```c
p++;
```

```
p

↓

arr[1]
```

After

```c
p++;
```

```
p

↓

arr[2]
```

---

# Demonstration

```c
#include <stdio.h>

int main(void)
{
    int arr[] = {5,10,15};

    int *p = arr;

    printf("%d\n", *p);

    p++;

    printf("%d\n", *p);

    p++;

    printf("%d\n", *p);
}
```

Output

```
5

10

15
```

---

# Difference Between p++ and ++p

Both move the pointer to the next element.

Difference is the value returned by the expression.

Example

```c
int *p = arr;
```

```
*p++

↓

Read current element

↓

Move pointer
```

Equivalent to

```c
*(p++)
```

Whereas

```c
*++p
```

means

```
Move pointer

↓

Read next element
```

Example

```c
int arr[] = {10,20,30};

int *p = arr;

printf("%d\n", *p++);

printf("%d\n", *p);
```

Output

```
10

20
```

Explanation

```
Read 10

↓

Pointer moves

↓

Now points to 20
```

---

# Pointer Decrement

```c
p--;
```

Moves to previous element.

Example

```
Before

↓

arr[2]
```

```
After

↓

arr[1]
```

---

# Pointer Addition

Valid

```c
p + 1

p + 5

p + n
```

Invalid

```c
p + q
```

Two memory addresses cannot be added meaningfully.

---

# Pointer Subtraction

Pointer subtraction is valid only when both pointers point into the **same array**.

Example

```c
int arr[10];

int *p = &arr[8];

int *q = &arr[3];

printf("%td\n", p-q);
```

Output

```
5
```

Notice

```
Difference

↓

Elements

↓

Not Bytes
```

Internally

```
Address Difference

↓

Divide by sizeof(type)

↓

Answer
```

Example

```
1032 - 1012

↓

20 bytes

↓

20 / 4

↓

5 elements
```

---

# Why Pointer Subtraction Returns Elements

Suppose

```c
int arr[100];
```

You want to know

```
How many integers apart?
```

not

```
How many bytes apart?
```

That is why C returns the number of elements.

---

# Comparison Between Pointers

Pointers can be compared.

Example

```c
if(p == q)
```

Checks whether both point to the same object.

Example

```c
if(p < q)
```

Only meaningful when both pointers refer to the same array.

---

# Pointer Arithmetic Outside an Array

Suppose

```c
int x;

int *p = &x;

p++;
```

Although incrementing itself may produce a pointer value, dereferencing it is **undefined behavior** because it no longer points to a valid object.

Similarly,

```c
int *p = malloc(sizeof(int));

p++;

printf("%d", *p);
```

Undefined behavior.

Pointer arithmetic should stay within the allocated object (or one past its end).

---

# One Past the End Rule

C allows a pointer to point **one element past the end** of an array.

Example

```c
int arr[5];

int *p = arr + 5;
```

Valid

```
arr

↓

0

1

2

3

4

5
     ↑

One Past End
```

But

```c
*p
```

is **not** valid.

The pointer may exist.

Dereferencing it is undefined behavior.

---

# Using Pointer Arithmetic to Traverse an Array

```c
#include <stdio.h>

int main(void)
{
    int arr[] = {10,20,30,40,50};

    int *p = arr;

    for(int i = 0; i < 5; i++)
    {
        printf("%d ", *p);

        p++;
    }
}
```

Output

```
10 20 30 40 50
```

---

# How the CPU Executes *p++

Suppose

```c
int arr[] = {10,20,30};

int *p = arr;
```

Statement

```c
*p++;
```

Internally

```
Read pointer

↓

Read value

↓

Increase pointer by sizeof(int)

↓

Store updated pointer
```

Notice

```
Data

↓

Read First
```

```
Pointer

↓

Increment Later
```

---

# Common Interview Questions

## Q1. Why does `p + 1` increase by 4 bytes for an `int *`?

Because pointer arithmetic moves by **one element**, not one byte.

---

## Q2. Does pointer arithmetic depend on pointer size?

No.

It depends on the size of the pointed-to type (`sizeof(*p)`).

---

## Q3. Can we add two pointers?

No.

Adding two addresses has no meaningful interpretation in C.

---

## Q4. Can we subtract two pointers?

Yes, but only when they point into the same array (or one past the end).

The result is the number of elements between them.

---

## Q5. Why is pointer subtraction useful?

It tells you how many array elements separate two positions.

---

## Q6. Is this valid?

```c
int arr[5];

int *p = arr + 5;
```

Yes.

It points **one past the last element**.

Dereferencing it is invalid.

---

# Common Interview Traps

### Trap 1

```c
char *p = (char *)1000;

p++;
```

Address becomes

```
1001
```

---

### Trap 2

```c
int *p = (int *)1000;

p++;
```

Address becomes

```
1004
```

(on systems where `sizeof(int) == 4`).

---

### Trap 3

```c
int *p;
int *q;

p + q;
```

Compilation error.

Pointer addition is not allowed.

---

### Trap 4

```c
int arr[5];

int *p = arr + 5;

printf("%d", *p);
```

Undefined behavior.

The pointer is valid.

Dereferencing it is not.

---

### Trap 5

```c
int arr[] = {10,20,30};

int *p = arr;

printf("%d\n", *p++);
```

Output

```
10
```

Pointer now points to

```
20
```

---

# Quick Revision

```
Pointer Arithmetic

↓

Moves by Elements

↓

p + 1

↓

Address + sizeof(type)

↓

p++

↓

Next Element

↓

p--

↓

Previous Element

↓

Pointer Difference

↓

Number of Elements

↓

One Past End

↓

Valid Pointer

↓

Cannot Dereference
```

---

# Key Interview Takeaways

✅ Pointer arithmetic moves in **elements**, not bytes.

✅ The compiler automatically multiplies by `sizeof(type)`.

✅ `p++` and `++p` move the pointer the same way; the difference is **when** the increment occurs in the expression.

✅ Pointer subtraction returns the number of elements between two pointers.

✅ Never perform pointer arithmetic outside the bounds of the same array, except for the permitted **one-past-the-end** pointer.

✅ One-past-the-end pointers are valid to compare or subtract, but **never to dereference**.
-----------------------------------------------------------------------
# C Interview Handbook
# Chapter 2 – Pointers
# Part 3 – Arrays vs Pointers



---

# Objectives

After completing this chapter, you should be able to answer:

- Are arrays and pointers the same?
- Why do people say "arrays decay into pointers"?
- What is array decay?
- Why does `sizeof(array)` differ from `sizeof(pointer)`?
- Why can't an array be assigned?
- What happens when an array is passed to a function?
- How does array indexing work internally?
- Why is `arr[i]` equivalent to `*(arr+i)`?

---

# The Biggest Myth

One of the most common interview statements is:

```
Arrays are pointers.
```

This is **false**.

The correct statement is:

```
An array is NOT a pointer.

However,

in most expressions,

an array name automatically converts
(decays)

to a pointer to its first element.
```

This distinction is asked frequently in Qualcomm, NVIDIA, and Broadcom interviews.

---

# Array Example

```c
int arr[5] = {10,20,30,40,50};
```

Memory

```
Address      Value

1000         10
1004         20
1008         30
1012         40
1016         50
```

The array name

```
arr
```

represents the entire array.

---

# What is arr?

Many beginners think

```
arr

↓

Pointer Variable
```

Wrong.

`arr` is **not** a variable.

It is the name of the array.

The compiler knows:

- Starting address
- Number of elements
- Total size

---

# Array Name

```
arr

↓

Base Address

↓

1000
```

Whenever required,

```
arr

↓

becomes

↓

&arr[0]
```

This automatic conversion is called

```
Array Decay
```

---

# Array Decay

Example

```c
int arr[5];
```

Expression

```c
int *p = arr;
```

Compiler internally converts

```c
int *p = &arr[0];
```

Memory

```
arr

↓

1000
```

```
p

↓

1000
```

Both point to the first element.

---

# Arrays Are NOT Pointers

Consider

```c
int arr[5];

int *p = arr;
```

Memory

```
arr

↓

Entire Array
```

```
p

↓

Pointer Variable
```

Difference

| Array | Pointer |
|--------|----------|
| Fixed object | Variable |
| Cannot change address | Can point elsewhere |
| Compiler knows size | Compiler knows only pointer size |
| Occupies storage for all elements | Occupies storage only for address |

---

# sizeof(Array)

Example

```c
int arr[10];
```

Suppose

```
sizeof(int)

↓

4
```

Then

```c
sizeof(arr)
```

becomes

```
10 × 4

↓

40 bytes
```

Because the compiler knows the entire array.

---

# sizeof(Pointer)

```c
int *p;
```

On a 64-bit system

```c
sizeof(p)
```

returns

```
8 bytes
```

because only the address is stored.

---

# Example

```c
#include <stdio.h>

int main(void)
{
    int arr[10];

    int *p = arr;

    printf("%zu\n", sizeof(arr));

    printf("%zu\n", sizeof(p));
}
```

Output (64-bit)

```
40

8
```

Interview Question:

Why?

Answer:

```
Array

↓

Entire Object
```

```
Pointer

↓

Only Address
```

---

# Can We Assign an Array?

Suppose

```c
int arr[5];
```

Can we do

```c
arr = arr + 1;
```

No.

Compilation error.

Reason

The address of an array is fixed.

The array itself cannot move.

---

# Pointer Assignment

Pointer variables can change.

```c
int a = 10;

int b = 20;

int *p = &a;

p = &b;
```

Memory

Initially

```
p

↓

a
```

Later

```
p

↓

b
```

Pointers are variables.

Arrays are not.

---

# Array Name Is Like a Constant Address

Think of

```c
int arr[5];
```

as

```
const Address

↓

1000
```

The address never changes.

But

```c
int *p;
```

is

```
Variable Address

↓

Can Change
```

---

# Array Decay in Function Calls

Example

```c
void print(int arr[])
{
    printf("%zu\n", sizeof(arr));
}
```

Call

```c
int numbers[10];

print(numbers);
```

Many expect

```
40
```

Actual Output

```
8
```

Why?

Because

```
numbers

↓

Automatically converted

↓

Pointer
```

The function receives

```c
int *arr;
```

not the entire array.

---

# Proof

These two declarations are identical.

```c
void fun(int arr[])
```

and

```c
void fun(int *arr)
```

Compiler treats them the same.

---

# Passing Array Size

Since only a pointer is received,

the function cannot determine the number of elements.

Therefore

Always pass the size.

```c
void print(int arr[], int size)
{
    for(int i=0;i<size;i++)
        printf("%d ", arr[i]);
}
```

---

# Why Doesn't the Whole Array Get Copied?

Suppose

```c
int arr[100000];
```

Copying the entire array every function call would be extremely expensive.

Instead

Only one pointer (8 bytes on most 64-bit systems) is passed.

This makes function calls efficient.

---

# Array Indexing

Consider

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

This is defined by the C language.

---

# Example

Memory

```
Address      Value

1000         10

1004         20

1008         30
```

Expression

```c
arr + 1
```

becomes

```
1004
```

Then

```c
*(1004)
```

becomes

```
20
```

---

# Internal Working

Compiler sees

```c
arr[i]
```

Internally

```
Base Address

+

i × sizeof(type)

↓

Read Memory

↓

Return Value
```

So

```c
arr[3]
```

becomes

```
*(arr + 3)
```

---

# Strange but True

Since

```c
arr[i]

=

*(arr+i)
```

and addition is commutative,

the following is also valid.

```c
i[arr]
```

Example

```c
printf("%d", 2[arr]);
```

Output

```
30
```

Although valid,

never write code this way.

Interviewers sometimes ask this as a trick question.

---

# Pointer Indexing

Suppose

```c
int *p = arr;
```

Then

```c
p[2]
```

is also valid.

Compiler converts

```c
*(p+2)
```

Exactly the same way.

---

# Array of Characters

```c
char name[] = "John";
```

Memory

```
J

o

h

n

'\0'
```

Compiler automatically adds

```
Null Character

↓

'\0'
```

at the end.

---

# Character Pointer

```c
char *name = "John";
```

Here

```
Pointer

↓

Read-only String Literal
```

This is different from

```c
char name[] = "John";
```

which creates an array.

---

# Arrays in Memory

```
int arr[5]

+----+----+----+----+----+
|10  |20  |30  |40  |50  |
+----+----+----+----+----+

^

|

arr
```

Pointer

```
int *p = arr;

+---------+

| Address |

+---------+

|

↓

+----+----+----+----+----+
|10  |20  |30  |40  |50  |
+----+----+----+----+----+
```

Notice

The pointer is stored separately.

The array is the data itself.

---

# Common Interview Questions

## Q1. Are arrays and pointers the same?

No.

An array is a complete object.

A pointer is a variable storing an address.

---

## Q2. What is array decay?

Automatic conversion of an array name into a pointer to its first element in most expressions.

---

## Q3. Does an array always decay?

No.

There are important exceptions.

An array **does not decay** when used with:

- `sizeof`
- `&` (address-of operator)
- `_Alignof` (C11)
- As a string literal initializing a character array

Example

```c
sizeof(arr)
```

returns the size of the entire array, not the size of a pointer.

---

## Q4. Why is `sizeof(arr)` different from `sizeof(p)`?

Because

```
Array

↓

Entire Object
```

Pointer

```
↓

Only Address
```

---

## Q5. Why can't arrays be assigned?

Because the array's base address is fixed after creation.

---

## Q6. Why is `arr[i]` equivalent to `*(arr+i)`?

Because this is how the C language defines array indexing.

---

## Q7. Why is `i[arr]` valid?

Because

```
arr[i]

↓

*(arr+i)

↓

*(i+arr)

↓

i[arr]
```

---

# Common Interview Traps

### Trap 1

```c
int arr[10];

printf("%zu", sizeof(arr));
```

Output

```
40
```

Not

```
8
```

---

### Trap 2

```c
void fun(int arr[])
{
    printf("%zu", sizeof(arr));
}
```

Output (64-bit)

```
8
```

Because `arr` is actually a pointer parameter.

---

### Trap 3

```c
int arr[5];

arr++;
```

Compilation Error.

Arrays cannot be incremented.

---

### Trap 4

```c
int *p;

p++;
```

Valid.

Pointers can move.

---

### Trap 5

```c
printf("%d", 2["ABCDE"]);
```

Output

```
C
```

because

```
2["ABCDE"]

↓

"ABCDE"[2]

↓

'C'
```

---

# Quick Revision

```
Array

↓

Complete Object

↓

Fixed Address

↓

Decays to Pointer

↓

Except

sizeof

&

_Alignof

String Initialization

↓

Pointer

↓

Variable

↓

Stores Address

↓

Can Move

↓

Array Indexing

↓

arr[i]

↓

*(arr+i)
```

---

# Key Interview Takeaways

✅ Arrays and pointers are **related but not identical**.

✅ An array name usually **decays to a pointer to its first element**, but not in every context.

✅ `sizeof(array)` gives the size of the whole array, while `sizeof(pointer)` gives the size of the pointer itself.

✅ Function parameters declared as `int arr[]` are actually treated as `int *arr`.

✅ Array indexing is defined as pointer arithmetic: `arr[i] == *(arr + i)`.

✅ Arrays have a fixed base address and cannot be assigned or incremented; pointers can.
-------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 2 – Pointers
# Part 4 – Pointer to Pointer (`int **`)

---

# Objectives

After completing this chapter, you should be able to answer:

- What is a pointer to a pointer?
- Why do we need double pointers?
- How does `**` work?
- How are multiple levels of indirection resolved?
- Where are double pointers used?
- Why do functions sometimes take `int **` instead of `int *`?
- How are dynamic 2D arrays created?

---

# What is a Pointer to a Pointer?

We already know:

```c
int x = 10;
```

```
x

↓

Stores Data
```

A pointer stores the address of `x`.

```c
int *p = &x;
```

```
p

↓

Stores Address of x
```

Now suppose we want to store the address of `p`.

For that, we need another pointer.

```c
int **pp = &p;
```

This is called a **pointer to a pointer**.

---

# Memory Diagram

```c
int x = 10;

int *p = &x;

int **pp = &p;
```

Suppose

```
Variable     Address     Value

x            1000        10

p            2000        1000

pp           3000        2000
```

Visual diagram

```
pp
 │
 ▼
 p
 │
 ▼
 x
 │
 ▼
10
```

Or

```
+---------+
| 2000    |   pp
+---------+
     |
     ▼
+---------+
| 1000    |   p
+---------+
     |
     ▼
+---------+
| 10      |   x
+---------+
```

---

# Reading the Declaration

```c
int **pp;
```

Read it from the variable outward.

```
pp

↓

Pointer

↓

to Pointer

↓

to int
```

Similarly

```c
char **argv;
```

means

```
Pointer

↓

to Pointer

↓

to char
```

---

# Accessing the Value

Example

```c
int x = 50;

int *p = &x;

int **pp = &p;
```

```
*pp

↓

Pointer p
```

```
**pp

↓

Actual Value
```

Code

```c
printf("%d\n", **pp);
```

Output

```
50
```

---

# Step-by-Step Evaluation

Suppose

```c
int x = 25;

int *p = &x;

int **pp = &p;
```

Memory

```
Address      Value

1000         25

2000         1000

3000         2000
```

Expression

```c
**pp
```

Execution

```
Read pp

↓

2000

↓

Read memory at 2000

↓

1000

↓

Read memory at 1000

↓

25
```

---

# Difference Between *pp and **pp

Suppose

```c
int **pp;
```

Then

```
*pp

↓

Pointer
```

```
**pp

↓

Actual Integer
```

Example

```c
printf("%p\n", (void *)*pp);

printf("%d\n", **pp);
```

Output

```
Address

Value
```

---

# Modifying Data

```c
int x = 10;

int *p = &x;

int **pp = &p;

**pp = 500;
```

Now

```
x

↓

500
```

Even though we used two pointers.

---

# Why Do We Need Pointer to Pointer?

Consider this function.

```c
void fun(int *p)
{
    p = NULL;
}
```

Call

```c
int x = 5;

int *ptr = &x;

fun(ptr);
```

Question:

Does `ptr` become NULL?

Answer

No.

Because the pointer itself was passed by value.

Memory

```
Caller

ptr

↓

x
```

Inside function

```
Copy of ptr

↓

x
```

Changing the copy does not affect the original.

---

# Correct Way

Pass the address of the pointer.

```c
void fun(int **p)
{
    *p = NULL;
}
```

Call

```c
fun(&ptr);
```

Now

```
Caller

ptr

↓

NULL
```

The original pointer is modified.

---

# Real Example

```c
#include <stdio.h>

void reset(int **p)
{
    *p = NULL;
}

int main(void)
{
    int value = 100;

    int *ptr = &value;

    reset(&ptr);

    if(ptr == NULL)
        printf("Pointer Reset\n");
}
```

Output

```
Pointer Reset
```

---

# Why malloc() Often Uses Double Pointers

Suppose we write

```c
void allocate(int *p)
{
    p = malloc(sizeof(int));
}
```

Will this work?

No.

Because

```
p

↓

Copy
```

The caller's pointer never changes.

Correct

```c
void allocate(int **p)
{
    *p = malloc(sizeof(int));
}
```

Call

```c
int *ptr = NULL;

allocate(&ptr);
```

Now

```
ptr

↓

Allocated Memory
```

---

# Memory Diagram

Before

```
ptr

↓

NULL
```

After

```
ptr

↓

Heap

+------+
| Data |
+------+
```

---

# Dynamic 2D Array

Suppose

```
3 Rows

4 Columns
```

We first allocate memory for row pointers.

```c
int **matrix;

matrix = malloc(3 * sizeof(int *));
```

Memory

```
matrix

↓

+-----+
|     |
+-----+
|     |
+-----+
|     |
+-----+
```

Each entry is a pointer.

---

Now allocate each row.

```c
for(int i=0;i<3;i++)
{
    matrix[i] = malloc(4 * sizeof(int));
}
```

Memory

```
matrix

↓

+------+
| ---- |------+
+------+      |
| ---- |---+  |
+------+   |  |
| ---- |-- |--+
+------+   |


Row0

+----+----+----+----+

Row1

+----+----+----+----+

Row2

+----+----+----+----+
```

Each row is allocated independently.

---

# Accessing Elements

```c
matrix[2][3]
```

Internally

```
matrix

↓

Pointer

↓

Row 2 Pointer

↓

Column 3
```

Equivalent to

```c
*(*(matrix + 2) + 3)
```

Interviewers love asking this.

---

# Triple Pointer

Yes, C allows

```c
int ***p;
```

Meaning

```
Pointer

↓

Pointer

↓

Pointer

↓

Integer
```

Although valid,

triple pointers are much less common.

Mostly seen in

- Compilers
- Operating Systems
- Advanced libraries

---

# Real-Life Uses

Double pointers appear in

- `argv`
- Dynamic 2D arrays
- Linked list insertion
- Tree insertion
- Memory allocation helpers
- Parsing APIs

---

# argc and argv

Every C programmer has written

```c
int main(int argc, char *argv[])
```

Did you know

```c
char *argv[]
```

is exactly the same as

```c
char **argv
```

Why?

Because an array parameter decays into a pointer.

Memory

```
argv

↓

+-------+
| ----  | ---> "program"
+-------+
| ----  | ---> "file.txt"
+-------+
| ----  | ---> "-v"
+-------+
```

Each element is itself a pointer to a string.

---

# Common Interview Questions

## Q1. What is a pointer to a pointer?

A variable that stores the address of another pointer.

---

## Q2. Why do we need `int **`?

To modify a pointer itself, not just the data it points to.

---

## Q3. What is the difference between `*pp` and `**pp`?

```
*pp

↓

Pointer
```

```
**pp

↓

Actual Data
```

---

## Q4. Why doesn't this work?

```c
void fun(int *p)
{
    p = NULL;
}
```

Because `p` is a copy of the caller's pointer.

---

## Q5. Why is `char **argv` used?

Because `argv` is a pointer to an array of character pointers (after array decay).

---

## Q6. What does

```c
matrix[i][j]
```

become internally?

```
*(*(matrix+i)+j)
```

---

# Common Interview Traps

### Trap 1

```c
int *p = NULL;

int **pp = &p;

printf("%d", **pp);
```

❌ Undefined behavior.

`*pp` is `NULL`, so dereferencing it is invalid.

---

### Trap 2

```c
void allocate(int *p)
{
    p = malloc(sizeof(int));
}
```

Does not update the caller's pointer.

Use

```c
int **p
```

instead.

---

### Trap 3

```c
int x = 5;

int *p = &x;

int **pp = &p;

*pp = NULL;
```

This does **not** change `x`.

It changes `p` to `NULL`.

---

### Trap 4

```c
**pp = 50;
```

This changes the integer value, **not** the pointer.

---

# Quick Revision

```
x

↓

Data

↓

p

↓

Address of x

↓

pp

↓

Address of p

↓

*pp

↓

Pointer

↓

**pp

↓

Actual Data
```

---

# Key Interview Takeaways

✅ `int **` means **pointer to pointer to int**.

✅ `*pp` gives the pointer, while `**pp` gives the value.

✅ Use a double pointer when a function needs to modify the caller's pointer.

✅ Dynamic 2D arrays are commonly implemented using `int **`.

✅ `char **argv` is one of the most common real-world examples of a pointer to a pointer.

✅ Understand how `matrix[i][j]` expands to `*(*(matrix + i) + j)`—it's a favorite systems interview question.
----------------------------------------------------------------------------
# C Interview Handbook
# Chapter 2 – Pointers
# Part 5 – Function Pointers

---

# Objectives

After completing this chapter, you should be able to answer:

- What is a function pointer?
- Why do we need function pointers?
- How do we declare them?
- How do we call a function through a pointer?
- Where are function pointers used?
- What are callbacks?
- How are jump tables implemented?
- How do operating systems and device drivers use function pointers?

---

# Why Do We Need Function Pointers?

So far we've stored the address of **variables**.

Example

```c
int x = 10;

int *p = &x;
```

But functions also have addresses.

Example

```c
void hello(void)
{
    printf("Hello\n");
}
```

Memory (simplified)

```
Text Segment

Address

1000

↓

hello()

2000

↓

main()
```

Since functions have addresses, we can store those addresses.

---

# What is a Function Pointer?

A function pointer stores the address of a function.

Example

```c
void hello(void)
{
    printf("Hello\n");
}

void (*fp)(void) = hello;
```

Memory

```
fp

↓

Address of hello()
```

---

# Function Name

Like arrays,

a function name usually converts to a pointer to that function.

These are equivalent.

```c
fp = hello;
```

```c
fp = &hello;
```

Both store the function's address.

---

# Declaring a Function Pointer

General syntax

```c
return_type (*pointer_name)(parameter_list);
```

Example

```c
int (*fp)(int, int);
```

Read from the variable outward.

```
fp

↓

Pointer

↓

to Function

↓

taking two int

↓

returning int
```

---

# Why Parentheses Are Needed

Consider

```c
int *fp(int, int);
```

This does **not** mean a function pointer.

It means

```
Function

↓

takes two integers

↓

returns pointer to int
```

Correct function pointer

```c
int (*fp)(int, int);
```

Always remember:

```
Parentheses make the difference.
```

---

# Example

```c
#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int main(void)
{
    int (*fp)(int,int);

    fp = add;

    printf("%d\n", fp(5,3));

    return 0;
}
```

Output

```
8
```

---

# Calling Through a Function Pointer

Two forms are valid.

```c
fp(5,3);
```

or

```c
(*fp)(5,3);
```

Both are equivalent.

The compiler automatically dereferences the function pointer.

---

# Memory Diagram

Suppose

```
Address

1000

↓

add()

3000

↓

fp
```

Execution

```
fp()

↓

Read Address

↓

Jump to Function

↓

Execute
```

---

# Multiple Functions

```c
int add(int a,int b)
{
    return a+b;
}

int sub(int a,int b)
{
    return a-b;
}
```

Function pointer

```c
int (*operation)(int,int);
```

Now

```c
operation = add;

printf("%d\n", operation(10,5));
```

Output

```
15
```

Later

```c
operation = sub;

printf("%d\n", operation(10,5));
```

Output

```
5
```

Notice

Same pointer

Different function

---

# Why Is This Useful?

Instead of writing

```c
if(choice==1)
    add();

else
    sub();

else
    multiply();
```

we can select the function once.

```
Pointer

↓

Desired Function

↓

Call
```

Cleaner and faster for many applications.

---

# Callback Functions

A callback is a function passed as an argument to another function.

Example

```c
void execute(void (*task)(void))
{
    task();
}
```

Functions

```c
void hello(void)
{
    printf("Hello\n");
}

void bye(void)
{
    printf("Bye\n");
}
```

Usage

```c
execute(hello);

execute(bye);
```

Output

```
Hello

Bye
```

Notice

The function

```
execute()

```

doesn't know what it will execute.

It simply calls whatever function it receives.

---

# Why Callbacks?

Suppose you're writing a sorting library.

The library doesn't know

```
Ascending?

or

Descending?
```

Instead

User supplies a comparison function.

This is exactly how

```
qsort()
```

works.

---

# qsort() Example

```c
int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
```

Library

```
qsort()

↓

Calls compare()

↓

Many Times
```

The comparison function is a callback.

---

# Real-World Example

Suppose a button is clicked.

GUI Library

```
Button Clicked

↓

Call User Function
```

Programmer

```c
void buttonPressed(void)
{
    printf("Clicked!\n");
}
```

Library stores

```
Function Pointer

↓

buttonPressed()
```

When the button is clicked

```
Pointer

↓

Function

↓

Executed
```

---

# Function Pointer Array

We can create arrays of function pointers.

Example

```c
int add(int,int);
int sub(int,int);
int mul(int,int);

int (*operations[])(int,int)
=
{
    add,
    sub,
    mul
};
```

Memory

```
operations

↓

+--------+
| add    |
+--------+
| sub    |
+--------+
| mul    |
+--------+
```

Call

```c
operations[1](10,5);
```

Output

```
5
```

---

# Jump Tables

Jump tables are arrays of function pointers.

Instead of

```c
switch(choice)
{
case 1:
    add();
    break;

case 2:
    sub();
    break;

case 3:
    mul();
}
```

We can write

```c
operations[choice-1](10,5);
```

Advantages

- Cleaner code
- Faster dispatch
- Easy to extend

Operating systems and compilers often use jump tables.

---

# Device Driver Example

Linux drivers commonly define structures containing function pointers.

Example (simplified)

```c
struct device_ops
{
    int (*open)(void);

    int (*read)(void);

    int (*write)(void);

    int (*close)(void);
};
```

Different hardware fills these pointers with different implementations.

Application

```
Read File

↓

Driver

↓

read()

↓

Correct Hardware Function
```

This is polymorphism in C.

---

# Function Pointer Returning Function?

This is illegal.

Functions cannot return functions.

But they can return

```
Pointer to Function
```

Example

```c
int (*getOperation(void))(int,int);
```

Meaning

```
getOperation

↓

Function

↓

Returns

↓

Pointer to Function
```

These declarations become easier when read from the variable name outward.

---

# Typedef Makes Life Easier

Without typedef

```c
int (*fp)(int,int);
```

With typedef

```c
typedef int (*Operation)(int,int);

Operation fp;
```

Much easier to read.

Large projects almost always use `typedef` for function pointers.

---

# Common Interview Questions

## Q1. What is a function pointer?

A variable that stores the address of a function.

---

## Q2. Why use function pointers?

To select functions dynamically at runtime.

Common uses include:

- Callbacks
- Drivers
- Interrupt handlers
- State machines
- Jump tables
- Libraries

---

## Q3. Are these equivalent?

```c
fp();
```

```c
(*fp)();
```

Yes.

Both call the same function.

---

## Q4. Why are parentheses required?

Without parentheses,

```c
int *fp();
```

declares a function,

not a function pointer.

---

## Q5. What is a callback?

A function passed to another function and invoked later.

---

## Q6. Where are function pointers used?

- Linux kernel
- Device drivers
- Embedded firmware
- GUI frameworks
- Networking stacks
- Standard library (`qsort`, signal handlers)

---

# Common Interview Traps

### Trap 1

```c
int *fp(int,int);
```

This is **not** a function pointer.

It is

```
Function

↓

Returns int *
```

---

### Trap 2

```c
int (*fp)(int,int);
```

Correct.

Function pointer.

---

### Trap 3

```c
fp = add;

printf("%d", (*fp)(2,3));
```

Correct.

---

### Trap 4

```c
fp = add;

printf("%d", fp(2,3));
```

Also correct.

---

### Trap 5

```c
void (*fp)(void);

fp();
```

Undefined behavior if `fp` was never initialized.

Always assign a valid function before calling it.

---

# Quick Revision

```
Function

↓

Has Address

↓

Function Pointer

↓

Stores Address

↓

Call

↓

fp()

↓

Callback

↓

Pass Function as Argument

↓

Jump Table

↓

Array of Function Pointers

↓

Used in

Drivers

Kernel

Embedded Systems

Libraries
```

---

# Key Interview Takeaways

✅ Functions have memory addresses just like variables.

✅ A function pointer stores the address of a function.

✅ `fp()` and `(*fp)()` are equivalent.

✅ Parentheses are essential in function pointer declarations.

✅ Callbacks are functions passed to other functions for later execution.

✅ Arrays of function pointers implement efficient jump tables.

✅ Function pointers are heavily used in operating systems, embedded software, device drivers, and the Linux kernel.
-------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 2 – Pointers
# Part 6 – Advanced Pointer Types

---

# Objectives

After completing this chapter, you should be able to answer:

- What is a pointer to an array?
- What is an array of pointers?
- What is the difference between them?
- How do we read complex pointer declarations?
- What is a function returning a pointer?
- What is a pointer to a function returning a pointer?
- How do interviewers expect you to read declarations?

---

# Why This Chapter?

Many interviews contain declarations like:

```c
int (*p)[5];
```

or

```c
char *argv[];
```

or

```c
int (*fp)(int, int);
```

Candidates often memorize these.

Interviewers expect you to **read** them logically.

The trick is simple:

> **Always start from the variable name and move outward while respecting parentheses.**

---

# Reading Complex Declarations

Consider

```c
int *p;
```

Start from `p`

```
p

↓

Pointer

↓

to int
```

---

Now

```c
int **p;
```

Read

```
p

↓

Pointer

↓

to Pointer

↓

to int
```

---

Now

```c
int ***p;
```

Read

```
p

↓

Pointer

↓

Pointer

↓

Pointer

↓

to int
```

---

# Pointer to an Array

Declaration

```c
int (*p)[5];
```

Read step by step.

Start from `p`

```
p

↓

Pointer

↓

to

↓

Array of 5 integers
```

Notice the parentheses.

Without parentheses

```c
int *p[5];
```

means something completely different.

---

# Why Do We Need a Pointer to an Array?

Suppose

```c
int arr[5] = {10,20,30,40,50};
```

Normally

```c
int *p = arr;
```

points to the **first element**.

```
p

↓

arr[0]
```

But suppose we want a pointer to the **entire array**.

We write

```c
int (*p)[5] = &arr;
```

Memory

```
          arr
+----+----+----+----+----+
|10  |20  |30  |40  |50  |
+----+----+----+----+----+

          ▲
          │
          p
```

---

# Difference

```c
int *p = arr;
```

```
Points to

↓

First Element
```

Whereas

```c
int (*p)[5] = &arr;
```

```
Points to

↓

Entire Array
```

---

# Example

```c
#include <stdio.h>

int main(void)
{
    int arr[5] = {1,2,3,4,5};

    int (*p)[5] = &arr;

    printf("%d\n", (*p)[2]);

    return 0;
}
```

Output

```
3
```

Explanation

```
*p

↓

Entire Array

↓

(*p)[2]

↓

Third Element
```

---

# Pointer Arithmetic with Pointer to Array

Suppose

```c
int arr1[5];

int arr2[5];

int (*p)[5] = &arr1;
```

After

```c
p++;
```

Pointer moves by

```
sizeof(int[5])

↓

20 bytes
```

instead of

```
sizeof(int)

↓

4 bytes
```

This surprises many candidates.

---

# Array of Pointers

Declaration

```c
int *p[5];
```

Read

```
p

↓

Array of 5

↓

Pointers

↓

to int
```

Notice

No parentheses around `p`.

---

# Memory Layout

```c
int a=10,b=20,c=30,d=40,e=50;

int *p[5]={&a,&b,&c,&d,&e};
```

Memory

```
p

+--------+
| &a     |
+--------+
| &b     |
+--------+
| &c     |
+--------+
| &d     |
+--------+
| &e     |
+--------+
```

Each element stores an address.

---

# Accessing Elements

```c
printf("%d\n", *p[2]);
```

Execution

```
p[2]

↓

Pointer to c

↓

Dereference

↓

30
```

Output

```
30
```

---

# Pointer to Array vs Array of Pointers

| Pointer to Array | Array of Pointers |
|------------------|-------------------|
| `int (*p)[5]` | `int *p[5]` |
| One pointer | Five pointers |
| Points to entire array | Stores multiple addresses |
| Common in multidimensional arrays | Common for strings |

This is one of the most common interview questions.

---

# Character Pointer Array

Example

```c
char *names[] =
{
    "Alice",
    "Bob",
    "Charlie"
};
```

Memory

```
names

+---------+
| ---- |-------> "Alice"
+---------+
| ---- |-------> "Bob"
+---------+
| ---- |-------> "Charlie"
+---------+
```

This is exactly how

```c
char *argv[]
```

works.

---

# Pointer to Multidimensional Array

Example

```c
int matrix[3][4];
```

Declaration

```c
int (*p)[4] = matrix;
```

Read

```
p

↓

Pointer

↓

to Array of 4 integers
```

Memory

```
matrix

+----+----+----+----+
|Row0                |
+----+----+----+----+
|Row1                |
+----+----+----+----+
|Row2                |
+----+----+----+----+

^

p
```

Increment

```c
p++;
```

moves to the next row.

---

# Function Returning a Pointer

Functions cannot return arrays.

But they can return pointers.

Example

```c
int *getValue(void)
{
    static int x = 100;

    return &x;
}
```

Call

```c
int *p = getValue();
```

Memory

```
Static Variable

↓

x

↓

Return Address
```

Notice

Returning a pointer to a **static** variable is safe.

---

# Incorrect Example

```c
int *getValue(void)
{
    int x = 100;

    return &x;
}
```

Wrong.

Reason

```
Stack Frame Destroyed

↓

Dangling Pointer
```

---

# Pointer to Function Returning Pointer

Declaration

```c
int *(*fp)(void);
```

Read from `fp`.

```
fp

↓

Pointer

↓

to Function

↓

taking no arguments

↓

returning pointer to int
```

This declaration looks difficult but becomes easy when read from the variable outward.

---

# Typedef Simplifies Complex Types

Without `typedef`

```c
int *(*fp)(void);
```

With `typedef`

```c
typedef int *(*Operation)(void);

Operation fp;
```

Large codebases use `typedef` extensively to improve readability.

---

# Reading Practice

### Example 1

```c
int *p[10];
```

Read

```
Array of 10 pointers to int
```

---

### Example 2

```c
int (*p)[10];
```

Read

```
Pointer to array of 10 integers
```

---

### Example 3

```c
int (*fp)(int,int);
```

Read

```
Pointer to function taking two integers and returning int
```

---

### Example 4

```c
char **argv;
```

Read

```
Pointer to pointer to char
```

---

### Example 5

```c
int *(*fp)(void);
```

Read

```
Pointer to function returning pointer to int
```

---

# Common Interview Questions

## Q1. What is the difference between

```c
int (*p)[5];
```

and

```c
int *p[5];
```

Answer

First

```
Pointer to Array
```

Second

```
Array of Pointers
```

---

## Q2. Why are parentheses important?

Because

```c
int *p[5];
```

and

```c
int (*p)[5];
```

represent completely different types.

---

## Q3. Why can't functions return arrays?

Arrays cannot be copied or returned by value in C.

Instead,

functions return pointers.

---

## Q4. Why is returning a pointer to a static variable safe?

Because static variables live for the entire lifetime of the program.

---

## Q5. Why do interviewers ask complex declarations?

To check whether you understand C's declaration syntax rather than memorizing it.

---

# Common Interview Traps

### Trap 1

```c
int *p[5];
```

Many candidates answer

```
Pointer to Array
```

Wrong.

It is

```
Array of Pointers
```

---

### Trap 2

```c
int (*p)[5];
```

Many answer

```
Array of Pointers
```

Wrong.

It is

```
Pointer to Array
```

---

### Trap 3

```c
int *get(void)
{
    int x = 5;
    return &x;
}
```

Undefined behavior.

`x` is destroyed when the function returns.

---

### Trap 4

```c
int *get(void)
{
    static int x = 5;
    return &x;
}
```

Correct.

The static variable remains valid.

---

# Quick Revision

```
Pointer to Array

↓

int (*p)[5]

↓

One Pointer

↓

Whole Array

---------------------

Array of Pointers

↓

int *p[5]

↓

Five Pointers

↓

Different Objects

---------------------

Function Returning Pointer

↓

int *fun()

---------------------

Pointer to Function Returning Pointer

↓

int *(*fp)()
```

---

# Key Interview Takeaways

✅ Always read declarations from the **variable name outward**.

✅ `int (*p)[5]` is a **pointer to an array**, while `int *p[5]` is an **array of pointers**.

✅ A pointer to an array advances by the size of the entire array during pointer arithmetic.

✅ Functions cannot return arrays, but they can return pointers.

✅ Returning a pointer to a local variable is unsafe; returning a pointer to a static or dynamically allocated object is safe.

✅ Use `typedef` to simplify complex pointer declarations in production code.
--------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 2 – Pointers
# Part 7 – `void *`, `NULL`, Dangling, Wild and `const` Pointers

---

# Objectives

After completing this chapter, you should be able to answer:

- What is a `void *` pointer?
- Why is `void *` called a generic pointer?
- Why can't we dereference a `void *`?
- What is `NULL`?
- What is a dangling pointer?
- What is a wild pointer?
- What is a `const` pointer?
- What is the difference between
  - `const int *`
  - `int * const`
  - `const int * const`

These are among the **most frequently asked pointer questions** in Qualcomm, NVIDIA, Broadcom, AMD, Intel, and embedded software interviews.

---

# Generic Pointer (`void *`)

Normally, every pointer has a type.

Example

```c
int x = 10;
int *p = &x;
```

```
p

↓

Pointer to int
```

Similarly,

```c
char *p;
```

```
Pointer to char
```

But sometimes we want a pointer that can point to **any data type**.

That's where

```c
void *
```

comes in.

---

# Why Do We Need `void *`?

Suppose we have

```c
int x = 10;
float y = 5.5;
char c = 'A';
```

Instead of creating three functions

```c
printInt()

printFloat()

printChar()
```

we can write one generic function

```c
void print(void *ptr);
```

This is why `void *` is called a **generic pointer**.

---

# Example

```c
int x = 10;

void *ptr = &x;
```

Memory

```
ptr

↓

1000

↓

x
```

Notice

The pointer stores the address,

but **not the data type**.

---

# Why Can't We Dereference `void *`?

Consider

```c
void *ptr = &x;
```

Can we write

```c
printf("%d", *ptr);
```

No.

Compilation Error.

Why?

The compiler asks

```
How many bytes should I read?

1?

2?

4?

8?
```

Since `void` has **no size**, the compiler doesn't know.

---

# Correct Way

Convert the generic pointer back to the correct type.

```c
int x = 100;

void *ptr = &x;

printf("%d", *(int *)ptr);
```

Execution

```
void *

↓

Cast to int *

↓

Dereference

↓

100
```

---

# Another Example

```c
float f = 3.14;

void *ptr = &f;

printf("%.2f", *(float *)ptr);
```

Output

```
3.14
```

---

# Where is `void *` Used?

Almost every generic C library uses it.

Examples

```c
malloc()

calloc()

realloc()

qsort()

bsearch()

pthread_create()
```

These functions don't know what type of data you will use.

---

# Example - malloc()

Prototype

```c
void *malloc(size_t size);
```

Memory

```
malloc()

↓

Returns Address

↓

Unknown Type
```

You convert it

```c
int *p = malloc(sizeof(int));
```

or

```c
char *name = malloc(20);
```

---

# Pointer Arithmetic on `void *`

Consider

```c
void *ptr;
```

Can we write

```c
ptr++;
```

According to the C standard,

No.

Because

```
Compiler

↓

Doesn't Know Object Size
```

Some compilers (like GCC) allow it as an extension, but **don't rely on it in portable code**.

---

# NULL Pointer

A NULL pointer points to **nothing**.

Example

```c
int *p = NULL;
```

Memory

```
p

↓

NULL
```

Meaning

```
No Valid Address
```

---

# Why Use NULL?

Suppose

```c
int *p;
```

What does it contain?

```
Unknown Value
```

Using it is dangerous.

Instead

```c
int *p = NULL;
```

Now we know

```
Pointer

↓

Invalid

↓

Safe to Check
```

---

# Checking NULL

```c
if(p != NULL)
{
    printf("%d", *p);
}
```

Always verify a pointer before dereferencing it when it might be `NULL`.

---

# Dangling Pointer

A dangling pointer points to memory that **was valid earlier but is no longer valid**.

Example

```c
int *p;

{
    int x = 10;

    p = &x;
}
```

After the block ends

```
x

↓

Destroyed
```

But

```
p

↓

Still Points There
```

Memory

```
p

↓

Old Stack Address

↓

Invalid Memory
```

This is a dangling pointer.

---

# Another Dangling Pointer

```c
int *p = malloc(sizeof(int));

free(p);
```

After `free()`

```
Heap Memory

↓

Released
```

But

```
p

↓

Still Contains Old Address
```

Accessing

```c
*p
```

is undefined behavior.

---

# Best Practice

After freeing memory

```c
free(p);

p = NULL;
```

Now

```
p

↓

NULL
```

Accidental reuse becomes easier to detect.

---

# Wild Pointer

A wild pointer has **never been initialized**.

Example

```c
int *p;
```

Memory

```
p

↓

Garbage Address
```

Using

```c
*p = 5;
```

is undefined behavior.

---

# Difference

Wild Pointer

```
Never Initialized
```

Dangling Pointer

```
Was Valid

↓

Later Became Invalid
```

---

# Memory Comparison

Wild Pointer

```
int *p;

↓

Random Address
```

Dangling Pointer

```
malloc()

↓

free()

↓

Old Address
```

NULL Pointer

```
NULL

↓

No Address
```

---

# Constant Pointer Basics

There are three common forms.

Many interviewers ask all three together.

---

# 1. Pointer to Constant

Declaration

```c
const int *p;
```

or

```c
int const *p;
```

Both are identical.

Read

```
Pointer

↓

to Constant Integer
```

---

Example

```c
int x = 10;

const int *p = &x;
```

Allowed

```c
p = &anotherVariable;
```

Not Allowed

```c
*p = 20;
```

Memory

```
Pointer

↓

Can Move

Data

↓

Cannot Modify Through Pointer
```

---

# 2. Constant Pointer

Declaration

```c
int * const p = &x;
```

Read

```
Constant Pointer

↓

to Integer
```

Allowed

```c
*p = 100;
```

Not Allowed

```c
p = &y;
```

Memory

```
Pointer

↓

Fixed

Data

↓

Can Change
```

---

# 3. Constant Pointer to Constant Data

Declaration

```c
const int * const p = &x;
```

Read

```
Constant Pointer

↓

to Constant Integer
```

Neither is allowed.

```c
*p = 10;
```

❌

```c
p = &y;
```

❌

---

# Visual Summary

## `const int *p`

```
Pointer

↓

Can Move

↓

Data

Cannot Modify
```

---

## `int * const p`

```
Pointer

Cannot Move

↓

Data

Can Modify
```

---

## `const int * const p`

```
Pointer

Cannot Move

↓

Data

Cannot Modify
```

---

# Easy Memory Trick

Read **right to left**.

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

to

↓

const int
```

---

```c
int * const p;
```

Start at `p`

```
p

↓

const Pointer

↓

to int
```

---

# Common Interview Questions

## Q1. Why can't we dereference a `void *`?

Because the compiler doesn't know the size of the object.

---

## Q2. Why is `malloc()` declared as returning `void *`?

Because it can allocate memory for any data type.

---

## Q3. What is the difference between a wild pointer and a dangling pointer?

Wild pointer

```
Never Initialized
```

Dangling pointer

```
Memory Was Valid

↓

Later Freed or Destroyed
```

---

## Q4. Why should we assign `NULL` after `free()`?

To avoid accidentally using a dangling pointer.

---

## Q5. Which is safer?

```c
if(p)
```

or

```c
if(p != NULL)
```

Both are correct.

The first is shorter and commonly used in production C code.

---

## Q6. Difference between

```c
const int *p;
```

and

```c
int * const p;
```

First

```
Data Constant
```

Second

```
Pointer Constant
```

---

# Common Interview Traps

### Trap 1

```c
void *ptr;

printf("%d", *ptr);
```

❌ Illegal.

Cast before dereferencing.

---

### Trap 2

```c
free(p);

*p = 5;
```

Undefined behavior.

`p` is now a dangling pointer.

---

### Trap 3

```c
int *p;

*p = 10;
```

Undefined behavior.

`p` is a wild pointer.

---

### Trap 4

```c
const int *p = &x;

*p = 100;
```

Compilation Error.

---

### Trap 5

```c
int * const p = &x;

p = &y;
```

Compilation Error.

---

# Quick Revision

```
void *

↓

Generic Pointer

↓

Cast Before Dereference

-----------------------

NULL

↓

Points to Nothing

-----------------------

Wild Pointer

↓

Never Initialized

-----------------------

Dangling Pointer

↓

Points to Released Memory

-----------------------

const int *p

↓

Pointer Can Move

↓

Data Constant

-----------------------

int * const p

↓

Pointer Constant

↓

Data Can Change

-----------------------

const int * const p

↓

Neither Can Change
```

---

# Key Interview Takeaways

✅ `void *` is a generic pointer that can store the address of any data type.

✅ `void *` cannot be dereferenced until it is cast to the correct pointer type.

✅ `NULL` represents a pointer that intentionally points to no valid object.

✅ A **wild pointer** is uninitialized; a **dangling pointer** points to memory that is no longer valid.

✅ After `free()`, set the pointer to `NULL` to reduce the risk of using freed memory.

✅ Remember the three `const` pointer forms:
- `const int *p` → data is constant.
- `int * const p` → pointer is constant.
- `const int * const p` → both are constant.
- ------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 2 – Pointers
# Part 8 – Dynamic Memory Allocation (`malloc`, `calloc`, `realloc`, `free`)

---

# Objectives

After completing this chapter, you should be able to answer:

- What is dynamic memory allocation?
- Why do we need heap memory?
- Difference between stack and heap.
- How do `malloc()`, `calloc()`, `realloc()`, and `free()` work?
- What are memory leaks?
- What are double free and use-after-free?
- What interview questions are commonly asked?

This is **one of the highest-weight topics** in C interviews.

---

# Why Dynamic Memory?

Suppose we write

```c
int arr[100];
```

The compiler allocates memory at compile time.

```
Size

↓

Fixed
```

What if the user enters

```
1000

or

100000
```

elements?

We don't know the size beforehand.

We need memory **at runtime**.

This is called

```
Dynamic Memory Allocation
```

---

# Stack vs Heap

## Stack Memory

Allocated automatically.

```c
void fun()
{
    int x = 10;
}
```

Memory

```
Function Called

↓

Stack Allocated

↓

Function Returns

↓

Stack Released
```

Advantages

- Fast
- Automatic
- No cleanup required

Disadvantages

- Size fixed
- Lifetime limited to function

---

## Heap Memory

Allocated manually.

```c
int *p = malloc(sizeof(int));
```

Memory

```
Program Requests Memory

↓

Heap Manager

↓

Returns Address
```

Advantages

- Runtime allocation
- Large objects
- Flexible lifetime

Disadvantages

- Programmer must free memory
- Slower than stack
- Can leak memory

---

# Stack vs Heap Comparison

| Stack | Heap |
|--------|------|
| Automatic allocation | Manual allocation |
| Fast | Slower |
| Limited size | Much larger |
| Released automatically | Must call `free()` |
| Function lifetime | Programmer-controlled lifetime |

---

# Heap Memory Diagram

```c
int *p = malloc(sizeof(int));
```

Memory

```
Stack

+------+
|  p   |
+------+
   |
   ▼

Heap

+------+
| ???? |
+------+
```

Notice

The pointer is on the stack.

The actual data is on the heap.

---

# malloc()

Prototype

```c
void *malloc(size_t size);
```

Meaning

```
Allocate

↓

Specified Number of Bytes

↓

Return Starting Address
```

---

# Example

```c
int *p = malloc(sizeof(int));
```

Memory

```
Heap

+------+
| ???? |
+------+
```

Contents are

```
Uninitialized
```

They may contain garbage values.

---

# Example

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p = malloc(sizeof(int));

    *p = 100;

    printf("%d\n", *p);

    free(p);
}
```

Output

```
100
```

---

# Always Check malloc()

Memory allocation can fail.

Correct

```c
int *p = malloc(sizeof(int));

if(p == NULL)
{
    printf("Allocation Failed\n");
    return 1;
}
```

This is especially important in embedded and systems programming.

---

# Allocating an Array

```c
int n = 100;

int *arr = malloc(n * sizeof(int));
```

Memory

```
Heap

+----+----+----+----+...
```

Now

```c
arr[0]

arr[50]

arr[99]
```

all work normally.

---

# calloc()

Prototype

```c
void *calloc(size_t count,
             size_t size);
```

Example

```c
int *p = calloc(5, sizeof(int));
```

Memory

```
Heap

0

0

0

0

0
```

Unlike `malloc()`

```
calloc()

↓

Initializes Memory

↓

Zero
```

---

# malloc vs calloc

| malloc | calloc |
|----------|---------|
| One argument | Two arguments |
| Uninitialized memory | Zero-initialized memory |
| Usually slightly faster | Slightly slower due to initialization |

---

# realloc()

Suppose

```c
int *arr = malloc(5*sizeof(int));
```

Later

Need

```
10 Elements
```

Instead of allocating again,

use

```c
arr = realloc(arr,
              10*sizeof(int));
```

Memory

Before

```
5 Elements
```

After

```
10 Elements
```

The existing contents are preserved (up to the smaller of the old and new sizes).

---

# realloc() Internally

Possible cases

### Case 1

Enough space exists.

```
Current Block

↓

Expanded
```

Pointer remains unchanged.

---

### Case 2

No space available.

```
Allocate New Block

↓

Copy Data

↓

Free Old Block

↓

Return New Address
```

Pointer may change.

---

# Correct Usage

Instead of

```c
arr = realloc(arr,newSize);
```

prefer

```c
int *temp = realloc(arr, newSize);

if(temp != NULL)
{
    arr = temp;
}
```

Reason

If `realloc()` fails,

the original block is still valid.

Assigning directly may lose the only pointer to it, causing a memory leak.

---

# free()

Prototype

```c
void free(void *ptr);
```

Purpose

```
Return Heap Memory

↓

Back to System
```

Example

```c
free(arr);
```

After

```
Heap Released
```

Pointer still contains the old address.

---

# Memory Leak

Memory leak means

```
Memory Allocated

↓

Never Freed
```

Example

```c
void fun(void)
{
    int *p = malloc(sizeof(int));

    *p = 10;
}
```

When the function returns

```
Pointer Lost

↓

Heap Memory Still Exists
```

Memory cannot be accessed anymore.

This is a memory leak.

---

# Memory Leak Diagram

```
Stack

+------+
| p    |
+------+

↓

Function Returns

↓

Pointer Gone

↓

Heap Block Still Allocated
```

The program has no way to free that memory.

---

# Correct Version

```c
void fun(void)
{
    int *p = malloc(sizeof(int));

    *p = 10;

    free(p);
}
```

No memory leak.

---

# Double Free

Example

```c
free(p);

free(p);
```

Wrong.

The same memory is released twice.

Possible results

- Crash
- Heap corruption
- Undefined behavior

---

# Best Practice

```c
free(p);

p = NULL;
```

Second call

```c
free(p);
```

is safe because

```c
free(NULL);
```

does nothing.

---

# Use After Free

Example

```c
int *p = malloc(sizeof(int));

free(p);

*p = 20;
```

Wrong.

Memory has already been released.

This bug is called

```
Use-After-Free
```

It is one of the most dangerous memory bugs in C/C++.

---

# Dangling Pointer

After

```c
free(p);
```

The pointer still stores the old address.

```
p

↓

Released Memory
```

It becomes a dangling pointer.

---

# Allocating a 2D Array

```c
int rows = 3;

int cols = 4;

int **matrix = malloc(rows * sizeof(int *));

for(int i = 0; i < rows; i++)
{
    matrix[i] = malloc(cols * sizeof(int));
}
```

Memory

```
matrix

↓

+------+
| ---- |------+
+------+      |
| ---- |---+  |
+------+   |  |
| ---- |-- |--+
+------+   |

↓

Each Pointer

↓

One Row
```

Remember to free each row first, then the array of row pointers.

---

# Freeing a 2D Array

```c
for(int i = 0; i < rows; i++)
{
    free(matrix[i]);
}

free(matrix);
```

Free in the reverse order of allocation.

---

# Common Interview Questions

## Q1. Difference between stack and heap?

Stack

```
Automatic
```

Heap

```
Manual
```

---

## Q2. Difference between malloc() and calloc()?

`malloc()`

```
Uninitialized Memory
```

`calloc()`

```
Zero Initialized Memory
```

---

## Q3. Why check malloc() for NULL?

Allocation may fail if insufficient memory is available.

---

## Q4. What is a memory leak?

Allocated memory that is never released with `free()`.

---

## Q5. Why is direct assignment with realloc() risky?

If `realloc()` fails,

it returns `NULL`.

The original pointer is lost if overwritten.

---

## Q6. Is `free(NULL)` safe?

Yes.

It has no effect.

---

## Q7. What happens after free()?

The pointer still contains the old address.

It becomes a dangling pointer unless set to `NULL`.

---

# Common Interview Traps

### Trap 1

```c
int *p = malloc(sizeof(int));

printf("%d", *p);
```

Undefined behavior.

Memory is uninitialized.

---

### Trap 2

```c
free(p);

*p = 10;
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
int *p = malloc(100);

/* No free() */
```

Memory leak.

---

### Trap 5

```c
p = realloc(p,newSize);
```

Risky.

Prefer using a temporary pointer.

---

# Quick Revision

```
Dynamic Memory

↓

Heap

↓

malloc()

↓

Uninitialized

-------------------

calloc()

↓

Zero Initialized

-------------------

realloc()

↓

Resize Memory

↓

May Move Block

-------------------

free()

↓

Release Memory

-------------------

Memory Leak

↓

Forgot free()

-------------------

Double Free

↓

free()

↓

free()

-------------------

Use After Free

↓

Access Released Memory
```

---

# Key Interview Takeaways

✅ Stack memory is automatic; heap memory is manually managed.

✅ `malloc()` allocates uninitialized memory.

✅ `calloc()` allocates zero-initialized memory.

✅ `realloc()` resizes an existing allocation and may return a different address.

✅ Always check the return value of `malloc()` and `realloc()`.

✅ Every successful allocation should have a matching `free()`.

✅ Understand memory leaks, dangling pointers, double free, and use-after-free—these are frequently tested in systems interviews.
---------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 2 – Pointers
# Part 9 – Pointer Arithmetic (Most Asked Interview Topic)

---

# Objectives

After completing this chapter, you should be able to answer:

- What is pointer arithmetic?
- Why does `p + 1` not add 1 byte?
- How do increment and decrement work?
- How are arrays traversed using pointers?
- What is pointer subtraction?
- Which pointer operations are valid?
- Why can't we add two pointers?
- How does pointer arithmetic work for different data types?

This is one of the **top 5 most frequently asked pointer topics** in C interviews.

---

# Why Pointer Arithmetic?

Suppose we have

```c
int arr[] = {10,20,30,40,50};
```

Memory

```
Address      Value

1000         10
1004         20
1008         30
1012         40
1016         50
```

Pointer

```c
int *p = arr;
```

Memory

```
p

↓

1000
```

Question

How do we move to

```
20

↓

30

↓

40
```

Answer

```
Pointer Arithmetic
```

---

# First Rule

A pointer always moves in units of the **size of the object it points to**.

Not by one byte.

---

# p + 1

Example

```c
int *p = arr;
```

Suppose

```
p = 1000
```

Then

```c
p + 1
```

becomes

```
1000

+

sizeof(int)

↓

1004
```

NOT

```
1001
```

---

# Memory Diagram

```
Address

1000    1004    1008    1012    1016

+----+----+----+----+----+
|10  |20  |30  |40  |50  |
+----+----+----+----+----+

 ^

 p
```

After

```c
p++;
```

```
Address

1000    1004    1008    1012    1016

+----+----+----+----+----+
|10  |20  |30  |40  |50  |
+----+----+----+----+----+

      ^

      p
```

---

# Example

```c
#include <stdio.h>

int main(void)
{
    int arr[] = {10,20,30};

    int *p = arr;

    printf("%d\n", *p);

    p++;

    printf("%d\n", *p);

    return 0;
}
```

Output

```
10

20
```

---

# p + n

General Rule

```text
p + n
```

becomes

```text
Address

+

n × sizeof(type)
```

Example

```c
int *p = arr;
```

```
p + 3

↓

1000 + 3 × 4

↓

1012
```

Points to

```
40
```

---

# Different Data Types

## int Pointer

```c
int *p;
```

```
p++

↓

+4 bytes
```

(on most systems)

---

## char Pointer

```c
char *p;
```

```
p++

↓

+1 byte
```

---

## double Pointer

```c
double *p;
```

Usually

```
p++

↓

+8 bytes
```

---

## Structure Pointer

```c
struct Student
{
    int id;
    char grade;
};

struct Student *p;
```

```
p++

↓

sizeof(struct Student)
```

which depends on structure padding.

---

# Pointer Decrement

```c
p--;
```

Moves to the previous element.

Example

```
1012

↓

1008
```

---

# Array Traversal

Instead of

```c
for(int i=0;i<5;i++)
{
    printf("%d ", arr[i]);
}
```

we can write

```c
int *p = arr;

for(int i=0;i<5;i++)
{
    printf("%d ", *p);

    p++;
}
```

Output

```
10 20 30 40 50
```

---

# Pointer Indexing

Suppose

```c
int *p = arr;
```

Then

```c
p[3]
```

means

```c
*(p+3)
```

Exactly the same as

```c
arr[3]
```

---

# Pointer Comparison

Suppose

```c
int arr[5];

int *p = &arr[1];

int *q = &arr[4];
```

We can compare

```c
if(p < q)
```

because both pointers refer to elements of the **same array**.

---

# Pointer Subtraction

Example

```c
int arr[10];

int *p = &arr[8];

int *q = &arr[3];
```

Expression

```c
p - q
```

Result

```
5
```

NOT

```
20
```

Why?

Pointer subtraction returns the **number of elements** between two pointers.

---

# Memory Diagram

```
Index

0 1 2 3 4 5 6 7 8 9

        q         p
        |         |
        ▼         ▼

+--+--+--+--+--+--+--+--+--+--+

Difference

↓

5 Elements
```

---

# Why Doesn't It Return Bytes?

Suppose

```
Address Difference

20 Bytes
```

Compiler divides by

```
sizeof(int)

↓

4
```

Result

```
5
```

This makes pointer arithmetic independent of data type.

---

# Valid Operations

Allowed

```c
p++
```

```c
p--
```

```c
p + n
```

```c
p - n
```

```c
p - q
```

(if both point into the same array)

```c
p == q
```

```c
p < q
```

(same array)

---

# Invalid Operations

```c
p + q;
```

Illegal.

Adding two addresses has no meaningful interpretation.

---

```c
p * 2;
```

Illegal.

Pointers cannot be multiplied.

---

```c
p / 2;
```

Illegal.

Pointers cannot be divided.

---

# Why Can't We Add Two Pointers?

Suppose

```
Address A

1000

Address B

2000
```

What would

```
1000 + 2000
```

mean?

Nothing useful.

Therefore

```
Pointer + Pointer

↓

Not Allowed
```

---

# Pointer Arithmetic and Arrays

Remember

```c
arr[i]
```

is

```c
*(arr+i)
```

Example

```c
arr[4]
```

becomes

```
Base Address

+

4 × sizeof(int)

↓

Dereference
```

---

# One-Past-the-End Pointer

Suppose

```c
int arr[5];
```

Valid

```c
int *p = arr + 5;
```

This points **one past the last element**.

Memory

```
+----+----+----+----+----+
|0   |1   |2   |3   |4   |
+----+----+----+----+----+
                          ^
                          |
                       arr+5
```

This pointer is valid **for comparison and iteration**.

But

```c
*p
```

is **undefined behavior**.

---

# Pointer Arithmetic with void *

```c
void *p;
```

Can we write

```c
p++;
```

According to the C standard,

No.

Reason

```
sizeof(void)

↓

Unknown
```

Some compilers allow it as an extension.

Portable C code should avoid it.

---

# Pointer Arithmetic with Structures

```c
struct Student
{
    int id;
    char grade;
};

struct Student s[3];

struct Student *p = s;
```

```
p++

↓

sizeof(struct Student)
```

Not

```
sizeof(int)
```

---

# Common Interview Questions

## Q1. Why does

```c
p++
```

not add one byte?

Because it moves by

```
sizeof(*p)
```

---

## Q2. What does

```c
p - q
```

return?

The number of elements between the two pointers.

---

## Q3. Can we subtract two pointers?

Yes,

if both point into the same array (or one past its end).

---

## Q4. Can we compare pointers?

Yes,

when they point into the same array.

---

## Q5. Can we add two pointers?

No.

The operation has no defined meaning in C.

---

## Q6. Is

```c
arr + 5
```

valid?

Yes.

It points one element past the end.

Dereferencing it is invalid.

---

# Common Interview Traps

### Trap 1

```c
char *p;

p++;
```

Moves

```
1 Byte
```

---

### Trap 2

```c
int *p;

p++;
```

Moves

```
sizeof(int)
```

---

### Trap 3

```c
double *p;

p++;
```

Moves

```
sizeof(double)
```

---

### Trap 4

```c
int *p = arr + 5;

printf("%d", *p);
```

Undefined behavior.

---

### Trap 5

```c
int *p, *q;

p + q;
```

Compilation error.

---

### Trap 6

```c
int arr[10];

printf("%td\n", &arr[9] - &arr[2]);
```

Output

```
7
```

Not

```
28
```

---

# Quick Revision

```
Pointer Arithmetic

↓

Moves by

↓

sizeof(type)

----------------------

p++

↓

Next Element

----------------------

p--

↓

Previous Element

----------------------

p + n

↓

Advance n Elements

----------------------

p - n

↓

Go Back n Elements

----------------------

p - q

↓

Number of Elements

----------------------

Pointer + Pointer

↓

Illegal

----------------------

arr[i]

↓

*(arr+i)

----------------------

arr+size

↓

Valid

↓

Do Not Dereference
```

---

# Key Interview Takeaways

✅ Pointer arithmetic moves in **elements**, not bytes.

✅ `p + n` advances by `n × sizeof(*p)` bytes internally.

✅ Pointer subtraction returns the **number of elements** between pointers.

✅ Adding or multiplying pointers is illegal.

✅ `arr[i]` is exactly equivalent to `*(arr + i)`.

✅ A pointer may legally point **one past the last element**, but dereferencing it is undefined behavior.

> **Interview Tip:** If you thoroughly understand pointer arithmetic, arrays become much easier because array indexing is simply pointer arithmetic under the hood.
> -------------------------------------------------------------------------------------------------
> # C Interview Handbook
# Chapter 2 – Pointers
# Part 10 – Pointer Interview Questions & Tricky Programs

---

# Objectives

This chapter contains the **most commonly asked pointer interview questions**.

After completing it, you should be able to solve almost every pointer-based interview question asked in:

- Qualcomm
- NVIDIA
- Broadcom
- AMD
- Intel
- Samsung
- Linux Kernel Interviews

---

# Question 1

```c
int x = 10;

int *p = &x;

printf("%d\n", *p);
```

Output

```
10
```

Explanation

```
p

↓

Address of x

↓

*p

↓

Value at that Address

↓

10
```

---

# Question 2

```c
int x = 10;

int *p = &x;

*p = 20;

printf("%d\n", x);
```

Output

```
20
```

Because

```
*p

↓

Changes x
```

---

# Question 3

```c
int x = 10;

int *p = &x;

printf("%p\n", (void *)p);

printf("%p\n", (void *)&x);
```

Output

```
Same Address
```

Reason

```
p

=

&x
```

---

# Question 4

```c
int arr[] = {10,20,30};

int *p = arr;

printf("%d\n", *p);
```

Output

```
10
```

Because

```
arr

↓

&arr[0]
```

---

# Question 5

```c
int arr[] = {10,20,30};

int *p = arr;

printf("%d\n", *(p+1));
```

Output

```
20
```

---

# Question 6

```c
int arr[] = {10,20,30};

printf("%d\n", arr[2]);
```

Output

```
30
```

Internally

```c
*(arr+2)
```

---

# Question 7

```c
int arr[] = {10,20,30};

printf("%d\n", 2[arr]);
```

Output

```
30
```

Reason

```
arr[2]

↓

*(arr+2)

↓

*(2+arr)

↓

2[arr]
```

Valid but never use it in production code.

---

# Question 8

```c
int arr[5];

printf("%zu\n", sizeof(arr));
```

Output (assuming `int` is 4 bytes)

```
20
```

Because

```
Entire Array

↓

5 × 4
```

---

# Question 9

```c
void fun(int arr[])
{
    printf("%zu\n", sizeof(arr));
}
```

Output (64-bit)

```
8
```

Reason

```
arr

↓

Pointer Parameter
```

---

# Question 10

```c
int arr[5];

printf("%zu\n", sizeof(&arr));
```

Output (64-bit)

```
8
```

Reason

```
&arr

↓

Address of Entire Array

↓

Pointer
```

Notice

```
sizeof(arr)

≠

sizeof(&arr)
```

---

# Question 11

```c
int arr[5];

printf("%p\n", (void *)arr);

printf("%p\n", (void *)&arr);
```

Output

```
Same Address
```

But

Their **types are different**.

```
arr

↓

int *

(after decay)
```

```
&arr

↓

int (*)[5]
```

This distinction is a favorite interview question.

---

# Question 12

```c
int arr[] = {10,20,30};

int *p = arr;

p++;

printf("%d\n", *p);
```

Output

```
20
```

---

# Question 13

```c
int arr[] = {10,20,30};

int *p = arr;

printf("%d\n", *p++);
```

Output

```
10
```

Why?

Operator precedence.

Equivalent to

```c
*(p++)
```

Execution

```
Read Value

↓

Increment Pointer
```

Pointer moves **after** dereferencing.

---

# Question 14

```c
int arr[] = {10,20,30};

int *p = arr;

printf("%d\n", (*p)++);
```

Output

```
10
```

Now

```
arr[0]

↓

11
```

Because

```
Increment Value

Not Pointer
```

---

# Question 15

```c
int arr[] = {10,20,30};

int *p = arr;

printf("%d\n", *++p);
```

Output

```
20
```

Equivalent to

```c
*(++p)
```

Execution

```
Increment Pointer

↓

Read Value
```

---

# Question 16

```c
int arr[] = {10,20,30};

int *p = arr;

printf("%d\n", ++*p);
```

Output

```
11
```

Array becomes

```
11

20

30
```

---

# Question 17

```c
int x = 5;

int *p = &x;

int **pp = &p;

printf("%d\n", **pp);
```

Output

```
5
```

---

# Question 18

```c
int x = 5;

int *p = &x;

int **pp = &p;

**pp = 50;

printf("%d\n", x);
```

Output

```
50
```

---

# Question 19

```c
int *p = NULL;

printf("%p\n", (void *)p);
```

Output

```
(nil)

or

0x0

or

implementation-defined representation
```

Do **not** rely on the exact printed format.

---

# Question 20

```c
int *p = NULL;

printf("%d\n", *p);
```

Undefined behavior.

Usually crashes.

---

# Question 21

```c
int *p;

printf("%d\n", *p);
```

Undefined behavior.

`p` is a wild pointer.

---

# Question 22

```c
int *p = malloc(sizeof(int));

free(p);

printf("%d\n", *p);
```

Undefined behavior.

Use-after-free.

---

# Question 23

```c
int *p = malloc(sizeof(int));

free(p);

free(p);
```

Undefined behavior.

Double free.

---

# Question 24

```c
int *p = malloc(sizeof(int));

free(p);

p = NULL;

free(p);
```

Correct.

`free(NULL)` is safe.

---

# Question 25

```c
int x = 10;

const int *p = &x;

*p = 20;
```

Compilation Error.

Cannot modify data through

```
Pointer to Constant
```

---

# Question 26

```c
int x = 10;

int * const p = &x;

p = NULL;
```

Compilation Error.

Constant Pointer.

---

# Question 27

```c
int arr[10];

int *p = &arr[8];

int *q = &arr[3];

printf("%td\n", p-q);
```

Output

```
5
```

Difference in

```
Elements

Not Bytes
```

---

# Question 28

```c
int arr[5];

int *p = arr+5;
```

Valid.

But

```c
*p
```

Undefined behavior.

One-past-the-end pointers may exist but must not be dereferenced.

---

# Question 29

```c
char str[] = "ABC";

char *p = str;

printf("%c\n", *(p+2));
```

Output

```
C
```

---

# Question 30

```c
char *str = "ABC";

str[0] = 'X';
```

Undefined behavior.

String literals should be treated as read-only.

If you need to modify characters,

use

```c
char str[] = "ABC";
```

---

# Question 31

```c
int x = 10;

void *p = &x;

printf("%d\n", *(int *)p);
```

Output

```
10
```

---

# Question 32

```c
void *p;

p++;
```

According to the C standard,

Compilation Error.

`void` has no size.

(Some compilers allow it as a non-standard extension.)

---

# Question 33

```c
int x = 5;

int *p = &x;

printf("%zu\n", sizeof(p));
```

Output (64-bit)

```
8
```

Pointer size is independent of the data type it points to.

---

# Question 34

```c
char c;

char *p = &c;

printf("%zu\n", sizeof(p));
```

Output (64-bit)

```
8
```

Same as an `int *`.

---

# Question 35

```c
int x = 5;

int *p = &x;

printf("%zu\n", sizeof(*p));
```

Output

```
4
```

Because

```
*p

↓

int
```

---

# Most Important Interview Questions

These are asked repeatedly in product-based companies.

| Question | Expected Answer |
|-----------|-----------------|
| Are arrays and pointers the same? | No |
| Why is `sizeof(arr)` different from `sizeof(ptr)`? | Array vs Pointer |
| Explain array decay. | Array converts to pointer in most expressions |
| Difference between `arr` and `&arr`? | Same address, different types |
| Difference between `const int *` and `int * const`? | Constant data vs constant pointer |
| Difference between wild and dangling pointers? | Uninitialized vs invalid pointer |
| Why can't `void *` be dereferenced? | Unknown object size |
| Why use `int **`? | Modify caller's pointer |
| Difference between `malloc()` and `calloc()`? | Uninitialized vs zero-initialized |
| Why is `realloc()` assigned to a temporary pointer? | Avoid losing original allocation on failure |
| Explain `*p++`, `(*p)++`, and `*++p`. | Operator precedence |
| Why is `2[arr]` valid? | Array indexing is pointer arithmetic |

---

# Final Pointer Revision

```
Pointer

↓

Stores Address

↓

Pointer Arithmetic

↓

Moves by sizeof(type)

↓

Arrays

↓

Array Decay

↓

Functions

↓

Function Pointers

↓

Double Pointers

↓

void *

↓

Dynamic Memory

↓

malloc()

calloc()

realloc()

free()

↓

NULL

↓

Wild Pointer

↓

Dangling Pointer

↓

const Pointers

↓

Interview Tricks
```

---

# Key Interview Takeaways

✅ Master the difference between `*p++`, `(*p)++`, and `*++p`—they are classic interview questions.

✅ Understand the difference between `arr` and `&arr`; they often print the same address but have different types.

✅ Never dereference `NULL`, wild, dangling, or one-past-the-end pointers.

✅ Remember that pointer arithmetic is based on **elements**, not bytes.

✅ If you can confidently explain every example in this chapter **without running the code**, your pointer fundamentals are strong enough for Qualcomm, NVIDIA, Broadcom, Intel, AMD, and similar systems interviews.

---
