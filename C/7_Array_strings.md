# C Interview Handbook
# Chapter 6 – Arrays & Strings
# Part 1 – Arrays Fundamentals

---

# Objectives

After completing this chapter, you should understand:

- What an array is
- Why arrays are used
- Memory layout of arrays
- Array declaration and initialization
- Array indexing
- Array decay
- Arrays vs pointers
- Pointer arithmetic with arrays
- Passing arrays to functions
- Common interview questions

---

# What is an Array?

An array is a collection of **elements of the same data type** stored in **contiguous memory locations**.

Example

```c
int arr[5];
```

Memory Layout

```
+-----+-----+-----+-----+-----+
| 10  | 20  | 30  | 40  | 50  |
+-----+-----+-----+-----+-----+

 arr[0] arr[1] arr[2] arr[3] arr[4]
```

Each element occupies the same amount of memory.

---

# Why Do We Need Arrays?

Without arrays

```c
int a;
int b;
int c;
int d;
int e;
```

With arrays

```c
int arr[5];
```

Advantages

- Easy iteration
- Less code
- Better cache locality
- Continuous memory
- Faster indexed access

---

# Declaration

Syntax

```c
datatype array_name[size];
```

Example

```c
int marks[100];

char name[20];

float salary[10];
```

---

# Initialization

Method 1

```c
int arr[5] =
{
    10,
    20,
    30,
    40,
    50
};
```

---

Method 2

```c
int arr[] =
{
    10,
    20,
    30
};
```

Compiler automatically determines the size.

---

Method 3

```c
int arr[5] =
{
    10,
    20
};
```

Remaining elements become

```
0
```

Memory

```
10 20 0 0 0
```

---

# Memory Layout

Suppose

```c
int arr[5];
```

Assume

```
sizeof(int) = 4
```

Suppose the first element starts at address

```
1000
```

Memory

```
Address      Value

1000  --->   arr[0]

1004  --->   arr[1]

1008  --->   arr[2]

1012  --->   arr[3]

1016  --->   arr[4]
```

Every element occupies 4 bytes.

---

# Why is Array Indexing Zero-Based?

Consider

```c
arr[0]
```

Internally

```
Base Address

+

0 × sizeof(int)
```

For

```c
arr[3]
```

```
Base Address

+

3 × sizeof(int)
```

General formula

```
Address(arr[i])

=

Base Address

+

i × sizeof(element)
```

Zero-based indexing makes this calculation simple.

---

# Accessing Elements

```c
#include <stdio.h>

int main()
{
    int arr[5] =
    {
        10,20,30,40,50
    };

    printf("%d\n", arr[2]);

    arr[2] = 100;

    printf("%d\n", arr[2]);
}
```

Output

```
30

100
```

---

# Internal Representation

Compiler converts

```c
arr[2]
```

into

```c
*(arr + 2)
```

Explanation

```
arr

↓

Base Address

↓

Move

2 Integers

↓

Dereference
```

This is one of the most important interview concepts.

---

# Pointer Arithmetic

Suppose

```
arr

↓

1000
```

Then

```
arr + 1

↓

1004
```

Not

```
1001
```

Reason

```
Pointer Arithmetic

↓

Moves

sizeof(type)

Bytes
```

---

# Example

```c
#include <stdio.h>

int main()
{
    int arr[] =
    {
        10,20,30
    };

    printf("%d\n", *arr);

    printf("%d\n", *(arr+1));

    printf("%d\n", *(arr+2));
}
```

Output

```
10

20

30
```

---

# Array Name

Array name represents

```
Address Of

↓

First Element
```

Example

```c
int arr[5];
```

Then

```c
arr
```

is equivalent to

```c
&arr[0]
```

in most expressions.

---

# Is an Array Name a Pointer?

Interview Question.

Answer

```
No.
```

An array is **not** a pointer.

However,

it **decays** into a pointer to its first element in most expressions.

---

# Array Decay

Example

```c
int arr[5];

int *ptr = arr;
```

Internally

```
arr

↓

&arr[0]
```

The array decays into a pointer.

---

# When Does an Array NOT Decay?

Three important cases.

---

## 1. sizeof()

```c
int arr[5];

sizeof(arr)
```

Output

```
20
```

Not

```
8
```

because the compiler knows the array size.

---

## 2. Address Operator

```c
&arr
```

Type

```
Pointer To Entire Array
```

Not

```
Pointer To First Element
```

---

## 3. _Alignof (C11)

Alignment is computed for the array object itself.

---

# arr vs &arr

Suppose

```c
int arr[5];
```

```
arr

↓

int *

↓

Pointer To First Element

-------------------------

&arr

↓

int (*)[5]

↓

Pointer To Entire Array
```

The addresses printed look the same.

The types are different.

---

# Example

```c
#include <stdio.h>

int main()
{
    int arr[5];

    printf("%p\n", (void*)arr);

    printf("%p\n", (void*)&arr);
}
```

Both print the same numeric address.

---

# Why Types Matter

Suppose

```c
int arr[5];
```

Then

```c
arr + 1
```

moves

```
4 Bytes
```

But

```c
&arr + 1
```

moves

```
20 Bytes
```

because it skips the entire array.

---

# Arrays vs Pointers

| Array | Pointer |
|--------|----------|
| Owns memory | Points to memory |
| Fixed size | Can point elsewhere |
| Cannot be assigned | Can be reassigned |
| `sizeof()` gives array size | `sizeof()` gives pointer size |

---

# Example

Wrong

```c
arr = ptr;
```

Compiler Error.

Correct

```c
ptr = arr;
```

---

# sizeof(Array) vs sizeof(Pointer)

```c
int arr[10];

int *ptr = arr;

printf("%zu\n", sizeof(arr));

printf("%zu\n", sizeof(ptr));
```

Typical 64-bit Output

```
40

8
```

---

# Passing Arrays to Functions

Example

```c
void print(int arr[])
{
    printf("%zu\n", sizeof(arr));
}
```

Output on a 64-bit machine

```
8
```

Why?

Because

```
Function Parameter

↓

Array Decays

↓

Pointer
```

Equivalent declaration

```c
void print(int *arr)
{
}
```

---

# Finding Array Size

Correct

```c
int arr[10];

size_t n =
sizeof(arr) /
sizeof(arr[0]);
```

Output

```
10
```

---

# Why Doesn't This Work Inside Functions?

```c
void print(int arr[])
{
    printf("%zu",
           sizeof(arr));
}
```

Because

```
arr

↓

Pointer

↓

Not Array
```

Pass the size separately.

```c
void print(int arr[],
           size_t size)
{
}
```

---

# Common Interview Questions

---

## Q1

Where are array elements stored?

```
Contiguous Memory
```

---

## Q2

Why does indexing start from 0?

Because

```
Address

=

Base

+

Index × Size
```

---

## Q3

What is

```c
arr[3]
```

internally?

```c
*(arr + 3)
```

---

## Q4

Is an array name a pointer?

No.

It decays to a pointer in most expressions.

---

## Q5

Difference between

```c
arr
```

and

```c
&arr
```

```
arr

↓

Pointer To First Element

--------------------------

&arr

↓

Pointer To Entire Array
```

---

## Q6

Can arrays be assigned?

Wrong

```c
arr1 = arr2;
```

Correct

Copy elements individually or use `memcpy()` where appropriate.

---

## Q7

Why does

```c
sizeof(arr)
```

change inside functions?

Because the parameter is actually a pointer.

---

# Common Interview Traps

### Trap 1

```c
arr++;
```

Not allowed.

Array names are not modifiable.

---

### Trap 2

```c
sizeof(parameter)
```

Returns pointer size.

Not array size.

---

### Trap 3

Confusing

```c
arr
```

with

```c
&arr
```

Same address.

Different types.

---

### Trap 4

Thinking arrays and pointers are identical.

They are closely related but different language constructs.

---

# Real Embedded Examples

## ADC Samples

```c
int adcSamples[256];
```

---

## UART Receive Buffer

```c
char rxBuffer[512];
```

---

## Sensor Values

```c
float temperature[24];
```

---

## CRC Lookup Table

```c
const uint32_t crcTable[256];
```

---

# Quick Revision

```
Array

↓

Contiguous Memory

------------------------

arr[i]

↓

*(arr+i)

------------------------

Array Name

↓

Decays To Pointer

------------------------

sizeof(array)

↓

Entire Array

------------------------

sizeof(pointer)

↓

Pointer Size

------------------------

Array

≠

Pointer
```

---

# Key Interview Takeaways

✅ Arrays store elements in contiguous memory.

✅ `arr[i]` is exactly equivalent to `*(arr + i)`.

✅ Array names are **not pointers**, but they decay to pointers in most expressions.

✅ Arrays and pointers are different types.

✅ `sizeof(array)` works only where the compiler knows the complete array object.

---

```
-------------------------------------------------------------------------------
