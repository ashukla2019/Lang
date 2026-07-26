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
# C Interview Handbook
# Chapter 6 – Arrays & Strings
# Part 2 – Multidimensional Arrays & Pointer Relationships

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Cisco • Samsung • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- Multidimensional arrays
- Memory layout of 2D arrays
- Row-major order
- Pointer to array
- Array of pointers
- Pointer to pointer
- Passing 2D arrays to functions
- Dynamic 2D arrays
- Jagged arrays
- Common interview questions

---

# What is a 2D Array?

A 2D array is an array whose elements are themselves arrays.

Example

```c
int matrix[3][4];
```

Read it as

```
matrix

↓

Array of 3 elements

↓

Each element is an array of 4 integers
```

---

# Visualization

```c
int matrix[3][4];
```

```
          Columns

        0   1   2   3

      +---+---+---+---+
Row 0 |10 |20 |30 |40 |
      +---+---+---+---+

Row 1 |50 |60 |70 |80 |
      +---+---+---+---+

Row 2 |90 |100|110|120|
      +---+---+---+---+
```

---

# Declaration

```c
int matrix[3][4];
```

Meaning

```
3 Rows

↓

Each Row

↓

4 Columns
```

---

# Initialization

```c
int matrix[2][3] =
{
    {1,2,3},
    {4,5,6}
};
```

Compiler stores

```
1 2 3 4 5 6
```

continuously in memory.

---

# Memory Layout

Suppose

```c
int matrix[2][3] =
{
    {1,2,3},
    {4,5,6}
};
```

Memory

```
Address      Value

1000  --->   1

1004  --->   2

1008  --->   3

1012  --->   4

1016  --->   5

1020  --->   6
```

Notice

```
Rows

↓

Stored Continuously
```

This is called

```
Row-major Order
```

---

# Row-Major Order

C stores rows one after another.

```
Row 0

↓

Entire Row

↓

Row 1

↓

Entire Row

↓

Row 2
```

It does **not** store columns together.

---

# Address Calculation

General formula

```
Address

=

Base

+

((Row × Columns)

+

Column)

×

sizeof(element)
```

Example

```c
matrix[1][2]
```

For

```
2 Rows

3 Columns
```

Address

```
Base

+

((1×3)+2)

×

4

=

Base + 20
```

---

# Accessing Elements

```c
#include <stdio.h>

int main()
{
    int matrix[2][3] =
    {
        {1,2,3},
        {4,5,6}
    };

    printf("%d\n", matrix[1][2]);
}
```

Output

```
6
```

---

# Internal Representation

Compiler converts

```c
matrix[1][2]
```

into

```c
*(*(matrix+1)+2)
```

Explanation

```
matrix

↓

Move To

Second Row

↓

Dereference

↓

Move

2 Integers

↓

Dereference
```

Very common interview question.

---

# What is matrix?

Given

```c
int matrix[2][3];
```

The type of

```c
matrix
```

is

```c
int (*)[3]
```

Meaning

```
Pointer

↓

To Array

↓

Of 3 Integers
```

---

# matrix vs &matrix

```c
matrix
```

Type

```
int (*)[3]
```

---

```c
&matrix
```

Type

```
int (*)[2][3]
```

Pointer to the entire 2D array.

---

# Why Does matrix+1 Move by an Entire Row?

Suppose

```c
int matrix[2][3];
```

Each row contains

```
3 Integers
```

Each integer

```
4 Bytes
```

Therefore

```
One Row

↓

12 Bytes
```

So

```c
matrix + 1
```

moves

```
12 Bytes
```

not

```
4 Bytes
```

---

# Pointer to Array

Example

```c
int matrix[2][3];

int (*ptr)[3] = matrix;
```

Read from inside out

```
ptr

↓

Pointer

↓

To Array

↓

Of 3 Integers
```

---

# Access Using Pointer

```c
printf("%d\n", ptr[1][2]);
```

or

```c
printf("%d\n",
       *(*(ptr+1)+2));
```

Both produce

```
6
```

---

# Array of Pointers

Example

```c
int a=10,b=20,c=30;

int *ptr[3];

ptr[0]=&a;

ptr[1]=&b;

ptr[2]=&c;
```

Visualization

```
ptr

+-----+
|  •--+---->10
+-----+

|  •--+---->20
+-----+

|  •--+---->30
+-----+
```

Each element is a pointer.

---

# Pointer to Pointer

Example

```c
int x = 10;

int *p = &x;

int **pp = &p;
```

Diagram

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

# Difference

| Declaration | Meaning |
|------------|---------|
| `int (*p)[5]` | Pointer to array |
| `int *p[5]` | Array of pointers |
| `int **p` | Pointer to pointer |

One of the most common interview questions.

---

# Passing a 2D Array to a Function

Correct

```c
void print(int arr[][3])
{
}
```

or

```c
void print(int arr[2][3])
{
}
```

or

```c
void print(int (*arr)[3])
{
}
```

---

# Why Must the Column Size Be Known?

Compiler needs it for address calculation.

Formula

```
Base

+

(Row × Columns)

+

Column
```

Without knowing

```
Columns
```

the compiler cannot calculate the address.

---

# Wrong Declaration

```c
void print(int arr[][])
{
}
```

Compiler Error.

Column size is mandatory.

---

# Dynamic 2D Array (Single Allocation)

```c
int rows = 3;
int cols = 4;

int *matrix =
malloc(rows * cols * sizeof(int));
```

Access

```c
matrix[i * cols + j]
```

Visualization

```
1 2 3 4 5 6 7 8 9 ...
```

One contiguous memory block.

Advantages

- Cache friendly
- Faster traversal
- Easy to free

---

# Dynamic 2D Array (Array of Pointers)

```c
int **matrix =
malloc(rows * sizeof(int*));

for(int i=0;i<rows;i++)
{
    matrix[i] =
    malloc(cols*sizeof(int));
}
```

Visualization

```
matrix

↓

+----+
| •----> Row0
+----+

| •----> Row1
+----+

| •----> Row2
+----+
```

Each row is allocated separately.

---

# Differences

| Single Allocation | Multiple Allocation |
|------------------|---------------------|
| Contiguous | Non-contiguous |
| Better cache locality | Poorer cache locality |
| One `free()` | Multiple `free()` calls |
| Preferred for numerical data | Flexible row sizes |

---

# Jagged Arrays

Rows may have different lengths.

Example

```
Row 0

1 2

Row 1

3 4 5 6

Row 2

7
```

Possible only using

```
Array Of Pointers
```

---

# Traversing a 2D Array

```c
for(int i=0;i<2;i++)
{
    for(int j=0;j<3;j++)
    {
        printf("%d ",
               matrix[i][j]);
    }

    printf("\n");
}
```

Output

```
1 2 3

4 5 6
```

---

# sizeof() with 2D Arrays

```c
int matrix[2][3];
```

Suppose

```
sizeof(int)=4
```

Then

```c
sizeof(matrix)
```

```
24
```

---

```c
sizeof(matrix[0])
```

```
12
```

---

```c
sizeof(matrix[0][0])
```

```
4
```

Useful for calculating dimensions.

---

# Common Interview Questions

---

## Q1

How are 2D arrays stored?

```
Row-major Order
```

---

## Q2

What is

```c
matrix[1][2]
```

internally?

```c
*(*(matrix+1)+2)
```

---

## Q3

Can a 2D array be passed as

```c
int **
```

No.

A 2D array and `int **` have different memory layouts and types.

---

## Q4

Difference between

```c
int (*p)[3]
```

and

```c
int *p[3]
```

| Pointer to Array | Array of Pointers |
|------------------|-------------------|
| One pointer | Three pointers |
| Contiguous rows | Independent pointers |

---

## Q5

Why is the column size required?

Because the compiler needs it to compute element addresses.

---

## Q6

Which dynamic allocation method is faster?

```
Single Allocation
```

Better cache locality.

---

# Common Interview Traps

### Trap 1

Thinking

```c
int matrix[3][4]
```

is the same as

```c
int **matrix
```

Wrong.

---

### Trap 2

Forgetting to free every row when using multiple allocations.

---

### Trap 3

Confusing

```c
int (*p)[4]
```

with

```c
int *p[4]
```

---

### Trap 4

Assuming columns are stored together.

C uses row-major order.

---

# Real Embedded Examples

## Image Buffer

```c
uint8_t image[480][640];
```

Each row is stored continuously.

---

## Sensor Matrix

```c
float sensor[8][16];
```

---

## Neural Network Weight Matrix

```c
float weights[256][128];
```

Used in AI and DSP applications.

---

## Frame Buffer

```c
uint32_t framebuffer[1080][1920];
```

Used in graphics programming.

---

# Quick Revision

```
2D Array

↓

Array Of Arrays

-------------------------

Stored In

↓

Row-major Order

-------------------------

matrix[i][j]

↓

*(*(matrix+i)+j)

-------------------------

matrix

↓

Pointer To Row

-------------------------

int (*p)[3]

↓

Pointer To Array

-------------------------

int *p[3]

↓

Array Of Pointers

-------------------------

int **

↓

Pointer To Pointer
```

---

# Key Interview Takeaways

✅ A 2D array is an array of arrays.

✅ C stores multidimensional arrays in **row-major order**.

✅ `matrix[i][j]` is equivalent to `*(*(matrix+i)+j)`.

✅ `int (*)[N]` and `int **` are completely different types.

✅ A single contiguous allocation generally provides better cache performance than allocating each row separately.

---

# Next Part

**Part 3 – Strings**

We'll cover:

- Character arrays
- String literals
- `char *` vs `char[]`
- String library functions
- String memory layout
- Common string algorithms
- ---------------------------------------------------------------------------
# Chapter 5 – Arrays and Strings
# Part 3 – Strings

---

# What is a String?

In C, a string is simply an array of characters terminated by a special character:

```
'\0'
```

called the **null character**.

Example:

```c
char str[] = "Hello";
```

Memory:

```
+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  |
+----+----+----+----+----+----+
```

The compiler automatically adds the null character.

Without '\0', functions like printf("%s") cannot know where the string ends.

---

# Character Array vs String

Character array:

```c
char arr[] = {'H','e','l','l','o'};
```

Memory:

```
H e l l o
```

No null terminator.

Printing:

```c
printf("%s", arr);
```

Undefined behavior.

---

Proper string:

```c
char arr[] = {'H','e','l','l','o','\0'};
```

or

```c
char arr[] = "Hello";
```

Both are identical.

---

# String Literal

A string literal is enclosed in double quotes.

```c
"Hello"
"Linux"
"Qualcomm"
```

These are stored in the program's read-only memory.

Example:

```c
char *p = "Hello";
```

Memory:

```
Read-only section

+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  |
+----+----+----+----+----+----+

        ^
        |
        p
```

---

# char[] vs char *

One of the most frequently asked interview questions.

## Case 1

```c
char str[] = "Hello";
```

Memory:

```
Stack

+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  |
+----+----+----+----+----+----+
```

Modifying:

```c
str[0] = 'Y';
```

Allowed.

Result:

```
Yello
```

---

## Case 2

```c
char *str = "Hello";
```

Memory:

```
Read-only memory

Hello
 ^
 |
str
```

Attempt:

```c
str[0]='Y';
```

Undefined behavior.

Usually crashes with segmentation fault.

---

# Difference Summary

| char[] | char * |
|---------|---------|
| Array | Pointer |
| Stored on stack (if local) | Points to literal |
| Can modify | Cannot modify literal |
| Size known | Pointer size only |
| Owns memory | Doesn't own memory |

---

# sizeof Difference

```c
char str[] = "Hello";

printf("%zu", sizeof(str));
```

Output:

```
6
```

Five characters + '\0'

---

Pointer:

```c
char *str = "Hello";

printf("%zu", sizeof(str));
```

64-bit machine:

```
8
```

Because it's just a pointer.

Very common interview question.

---

# Initializing Strings

Method 1

```c
char str[] = "Linux";
```

---

Method 2

```c
char str[20] = "Linux";
```

Remaining bytes become zero.

Memory:

```
L i n u x \0 0 0 0 ...
```

---

Method 3

```c
char str[] =
{
'L',
'i',
'n',
'u',
'x',
'\0'
};
```

---

# Reading Strings

Using scanf

```c
char name[30];

scanf("%s", name);
```

Input:

```
John
```

Works.

Input:

```
John Smith
```

Only reads:

```
John
```

Stops at first whitespace.

---

# fgets()

Preferred method.

```c
char name[100];

fgets(name, sizeof(name), stdin);
```

Input:

```
John Smith
```

Entire line is stored.

Safer than gets().

---

# Why gets() is Dangerous

```c
char str[10];

gets(str);
```

Input:

```
This is a very long sentence...
```

Buffer overflow.

Never use gets().

It has been removed from the C standard.

Interview answer:

> gets() cannot perform bounds checking.

---

# Printing Strings

```c
printf("%s", str);
```

or

```c
puts(str);
```

Difference:

```
puts()
```

Automatically prints a newline.

---

# String Length

Library function:

```c
strlen(str)
```

Example:

```c
char str[]="Linux";

printf("%zu", strlen(str));
```

Output

```
5
```

Not 6.

strlen does NOT count '\0'.

---

# Implementing strlen()

Interview favorite.

```c
int mystrlen(char *s)
{
    int count = 0;

    while(*s != '\0')
    {
        count++;
        s++;
    }

    return count;
}
```

Time Complexity

```
O(n)
```

---

# strcpy()

Copies one string into another.

```c
char src[]="Linux";
char dst[20];

strcpy(dst, src);
```

Memory

Before

```
dst

?
?
?
?
```

After

```
Linux
```

---

# Implement strcpy()

```c
void mystrcpy(char *dst, char *src)
{
    while(*src)
    {
        *dst = *src;
        dst++;
        src++;
    }

    *dst = '\0';
}
```

---

# strncpy()

```c
strncpy(dst, src, n);
```

Copies at most n characters.

Safer.

Common interview discussion:

It may not append '\0' if the source length is greater than or equal to `n`, so you may need to terminate the destination manually.

---

# strcat()

Append strings.

```c
char a[30]="Hello ";

char b[]="World";

strcat(a,b);
```

Output

```
Hello World
```

---

Implementation idea

Move to end of first string.

Then copy second string.

---

# strcmp()

Compare strings.

```c
strcmp(a,b)
```

Returns

```
0
```

Strings equal.

Negative

```
a<b
```

Positive

```
a>b
```

Comparison is lexicographical (dictionary order).

---

Example

```c
strcmp("abc","abc")
```

Returns

```
0
```

---

```c
strcmp("abc","abd")
```

Returns

Negative value.

---

```c
strcmp("cat","bat")
```

Returns

Positive value.

---

# Implement strcmp()

```c
int mystrcmp(char *a, char *b)
{
    while(*a && *b)
    {
        if(*a != *b)
            return *a - *b;

        a++;
        b++;
    }

    return *a - *b;
}
```

---

# strchr()

Find first occurrence.

```c
char str[]="Embedded";

char *p = strchr(str,'b');
```

Points to

```
bedded
```

---

# strstr()

Find substring.

```c
char str[]="OperatingSystem";

char *p = strstr(str,"System");
```

Points to

```
System
```

Returns NULL if not found.

---

# strtok()

Used for tokenizing strings.

Example

```c
char str[]="red,green,blue";

char *token = strtok(str, ",");
```

Produces

```
red
green
blue
```

Remember:

`strtok()` modifies the original string and is not thread-safe because it keeps internal state. POSIX provides `strtok_r()` as a reentrant alternative.

---

# Common Interview Algorithms

## Reverse String

```c
void reverse(char s[])
{
    int i = 0;
    int j = strlen(s) - 1;

    while(i < j)
    {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;

        i++;
        j--;
    }
}
```

Complexity

```
O(n)
```

---

## Count Characters

```c
int count = 0;

for(int i=0; str[i]; i++)
    count++;
```

Equivalent to

```
strlen()
```

---

## Count Words

```c
int words = 0;
int inWord = 0;

for(int i = 0; str[i] != '\0'; i++)
{
    if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
    {
        if(!inWord)
        {
            words++;
            inWord = 1;
        }
    }
    else
    {
        inWord = 0;
    }
}
```

Example

```
Linux Kernel Interview
```

Output

```
3
```

---

## Count Vowels

```c
int vowels = 0;

for(int i=0; str[i]; i++)
{
    char c = tolower((unsigned char)str[i]);

    if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
        vowels++;
}
```

---

## Check Palindrome

```c
int isPalindrome(char s[])
{
    int i = 0;
    int j = strlen(s) - 1;

    while(i < j)
    {
        if(s[i] != s[j])
            return 0;

        i++;
        j--;
    }

    return 1;
}
```

Example

```
madam
```

Output

```
Palindrome
```

---

# Frequently Asked Interview Questions

### Q1. Difference between char array and string?

A string is a character array terminated by `'\0'`. A character array without a null terminator is **not** a C string.

---

### Q2. Why is '\0' required?

It marks the end of the string. Standard library functions such as `printf`, `strlen`, and `strcpy` stop processing when they encounter it.

---

### Q3. Why can't we modify string literals?

String literals are typically stored in read-only memory. Attempting to modify them results in undefined behavior.

---

### Q4. Why is strlen() O(n)?

Because it scans each character until it reaches the null terminator.

---

### Q5. Which is safer: scanf("%s") or fgets()?

`fgets()` is generally safer because it limits the number of characters read, helping prevent buffer overflows.

---

### Q6. Difference between strlen() and sizeof()?

`strlen()` returns the number of characters before `'\0'`.

`sizeof()` returns the total size of the object in bytes (for arrays, including the null terminator if present).

---

# Interview Tips

- Always allocate one extra byte for the null terminator.
- Never use `gets()`.
- Prefer `fgets()` for reading input.
- Know how to implement `strlen()`, `strcpy()`, and `strcmp()`.
- Understand why `char *p = "Hello";` should not be modified.
- Be comfortable explaining the difference between `char[]` and `char *`.
- Expect coding questions on reversing strings, palindrome checking, counting words, removing duplicates, and implementing common string functions without using the standard library.

---

## What's Next

**Part 4 – Advanced String Problems**

We'll cover interview-oriented coding problems such as:

- Remove duplicate characters
- String rotation
- Anagram checking
- Run-Length Encoding (RLE)
- Longest common prefix
- First non-repeating character
- Reverse words in a sentence
- Implement `atoi()`
- Implement `itoa()`
- Implement `memcpy()`, `memmove()`, `memcmp()`, and `memset()`
- Frequently asked Qualcomm, NVIDIA, Broadcom, AMD, Intel, and Linux kernel string interview questions

```----------------------------------------------------------------------------------------
# Chapter 5 – Arrays and Strings
# Part 4 – Advanced String Problems

---

# 1. Remove Duplicate Characters

## Problem

Input

```
programming
```

Output

```
progamin
```

(Keep only the first occurrence.)

---

## Brute Force

For every character,

search all previous characters.

```
O(n²)
```

---

## Optimal

Maintain a frequency array.

```c
void removeDuplicates(char str[])
{
    int freq[256] = {0};
    int j = 0;

    for(int i = 0; str[i] != '\0'; i++)
    {
        unsigned char ch = str[i];

        if(freq[ch] == 0)
        {
            freq[ch] = 1;
            str[j++] = str[i];
        }
    }

    str[j] = '\0';
}
```

Complexity

```
Time : O(n)

Space : O(1)
```

---

# 2. Check Anagram

Two strings are anagrams if they contain exactly the same characters with the same frequency.

Example

```
listen
silent
```

Answer

```
Yes
```

---

## Frequency Array Method

```c
int isAnagram(char a[], char b[])
{
    int freq[256] = {0};

    for(int i=0; a[i]; i++)
        freq[(unsigned char)a[i]]++;

    for(int i=0; b[i]; i++)
        freq[(unsigned char)b[i]]--;

    for(int i=0;i<256;i++)
        if(freq[i]!=0)
            return 0;

    return 1;
}
```

Complexity

```
Time : O(n)

Space : O(1)
```

Interview Tip

If the strings have different lengths, immediately return false.

---

# 3. Reverse Words in a Sentence

Input

```
I Love Linux
```

Output

```
Linux Love I
```

---

## Algorithm

```
Reverse entire string

↓

Reverse every word
```

Example

```
I Love Linux

↓

xuniL evoL I

↓

Linux Love I
```

Complexity

```
O(n)
```

Very common interview problem.

---

# 4. Reverse Each Word

Input

```
Linux Kernel
```

Output

```
xuniL lenreK
```

Reverse characters between spaces.

Complexity

```
O(n)
```

---

# 5. Check Palindrome Ignoring Case

Input

```
Madam
```

Output

```
Palindrome
```

Convert both characters to lowercase before comparison.

```c
while(i<j)
{
    if(tolower((unsigned char)str[i]) !=
       tolower((unsigned char)str[j]))
        return 0;

    i++;
    j--;
}
```

---

# 6. Ignore Spaces While Checking Palindrome

Input

```
nurses run
```

Output

```
Palindrome
```

Technique

```
Skip spaces

↓

Compare remaining characters
```

Often extended to ignore punctuation as well.

---

# 7. Longest Common Prefix

Input

```
flower

flow

flight
```

Output

```
fl
```

---

Algorithm

Compare character by character.

Stop at first mismatch.

Complexity

```
O(n × m)

n = number of strings

m = shortest length
```

---

# 8. First Non-Repeating Character

Input

```
aabbccddefg
```

Output

```
e
```

---

Algorithm

Step 1

Frequency array.

Step 2

Scan again.

First frequency == 1

Answer.

```c
char firstUnique(char str[])
{
    int freq[256]={0};

    for(int i=0;str[i];i++)
        freq[(unsigned char)str[i]]++;

    for(int i=0;str[i];i++)
        if(freq[(unsigned char)str[i]]==1)
            return str[i];

    return '\0';
}
```

Complexity

```
O(n)
```

---

# 9. First Repeating Character

Input

```
abcdefga
```

Output

```
a
```

Maintain frequency.

First character whose frequency becomes two.

---

# 10. Character Frequency Count

Input

```
banana
```

Output

```
a → 3

b → 1

n → 2
```

Useful for

- Anagram
- Huffman Coding
- Compression
- Parsing

---

# 11. String Rotation

Input

```
abcde

cdeab
```

Output

```
Yes
```

---

Trick

Append first string to itself.

```
abcdeabcde
```

Search second string.

```c
strstr(temp,s2)
```

If found

Rotation.

Complexity

```
O(n)
```

---

# 12. Run-Length Encoding (RLE)

Input

```
aaabbcccc
```

Output

```
a3b2c4
```

Algorithm

```
Count consecutive characters.

↓

Print character + count.
```

Complexity

```
O(n)
```

Frequently asked in embedded interviews.

---

# 13. String Compression

Input

```
aaabbc
```

Output

```
a3b2c1
```

Same idea as RLE.

---

# 14. Remove All Spaces

Input

```
Linux Kernel
```

Output

```
LinuxKernel
```

```c
void removeSpaces(char str[])
{
    int j=0;

    for(int i=0;str[i];i++)
    {
        if(str[i]!=' ')
            str[j++]=str[i];
    }

    str[j]='\0';
}
```

Complexity

```
O(n)
```

---

# 15. Remove Consecutive Duplicates

Input

```
aaabbbccddd
```

Output

```
abcd
```

Different from removing all duplicates.

Only adjacent duplicates disappear.

---

# 16. Count Words

Input

```
Linux Kernel Interview
```

Output

```
3
```

Use

```
space → word transition
```

Complexity

```
O(n)
```

---

# 17. Count Sentences

Input

```
Hi.

How are you?

I am fine!
```

Output

```
3
```

Count

```
.

?

!
```

---

# 18. Count Digits, Alphabets, Special Characters

Input

```
abc123$%
```

Output

```
Letters : 3

Digits : 3

Special : 2
```

Use

```
isalpha()

isdigit()

ispunct()
```

---

# 19. Convert Uppercase to Lowercase

Library

```c
tolower()
```

Manual

```c
if(ch>='A' && ch<='Z')
    ch += 32;
```

ASCII

```
A = 65

a = 97

Difference = 32
```

---

# 20. Convert Lowercase to Uppercase

```c
if(ch>='a' && ch<='z')
    ch -= 32;
```

---

# 21. Toggle Case

Input

```
LiNuX
```

Output

```
lInUx
```

---

# 22. Implement atoi()

Converts string to integer.

Input

```
"12345"
```

Output

```
12345
```

Implementation

```c
int myAtoi(char str[])
{
    int num = 0;

    for(int i=0; str[i]; i++)
    {
        if(str[i]<'0' || str[i]>'9')
            break;

        num = num*10 + (str[i]-'0');
    }

    return num;
}
```

Interview Discussion

Real `atoi()` also handles:

- Leading spaces
- '+' sign
- '-' sign
- Integer overflow

---

# 23. Implement itoa()

Reverse of atoi.

```
1234

↓

"1234"
```

Algorithm

```
Repeatedly divide by 10

↓

Store remainder

↓

Reverse string
```

---

# 24. Implement memcpy()

Copies memory.

```c
void *myMemcpy(void *dest,const void *src,size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;

    while(n--)
        *d++ = *s++;

    return dest;
}
```

Important

Undefined behavior if memory overlaps.

---

# 25. Implement memmove()

Handles overlapping memory safely.

Idea

If

```
Destination > Source
```

Copy backwards.

Else

Copy forwards.

Common interview question.

---

# 26. Implement memcmp()

Compare memory.

```c
int myMemcmp(const void *a,const void *b,size_t n)
{
    const unsigned char *p1=a;
    const unsigned char *p2=b;

    while(n--)
    {
        if(*p1!=*p2)
            return *p1-*p2;

        p1++;
        p2++;
    }

    return 0;
}
```

---

# 27. Implement memset()

```c
void *myMemset(void *ptr,int value,size_t n)
{
    unsigned char *p = ptr;

    while(n--)
        *p++ = (unsigned char)value;

    return ptr;
}
```

Complexity

```
O(n)
```

---

# 28. strstr() Implementation Idea

Search pattern inside string.

Naive

```
For every position

↓

Compare entire pattern
```

Complexity

```
O(nm)
```

Advanced

```
KMP

Rabin-Karp

Boyer-Moore
```

---

# 29. Substring Search

Input

```
OperatingSystem

System
```

Output

```
Found
```

Very common.

---

# 30. Lexicographical Comparison

Dictionary order.

```
apple

banana
```

Since

```
a < b
```

Answer

```
apple smaller
```

Used by

```
strcmp()
```

---

# Important Interview Questions

### Q1. Why is memcpy() faster than a normal loop?

Library implementations are highly optimized and may use architecture-specific instructions, vectorization (SIMD), alignment optimizations, and word-sized copies instead of copying one byte at a time.

---

### Q2. Difference between memcpy() and memmove()?

| memcpy() | memmove() |
|-----------|------------|
| Faster | Slightly slower |
| No overlap allowed | Overlap allowed |
| Undefined behavior on overlap | Safe for overlap |

---

### Q3. Difference between strcmp() and memcmp()?

| strcmp() | memcmp() |
|-----------|-----------|
| Stops at '\0' | Compares exactly `n` bytes |
| For C strings | For any memory block |
| Null-terminated | Works with binary data |

---

### Q4. Why does atoi() return 0 for invalid strings?

The standard `atoi()` has limited error reporting. Modern code generally prefers `strtol()`, which provides better error detection and overflow handling.

---

### Q5. Why use unsigned char in string functions?

Using `unsigned char` avoids undefined behavior when passing negative `char` values to functions like `tolower()` or when indexing a 256-element frequency array on systems where `char` is signed.

---

# High-Frequency Interview Problems

Easy

- Reverse String
- Reverse Words
- Palindrome
- Remove Spaces
- Count Words
- Character Frequency
- Remove Duplicates
- Toggle Case

Medium

- Anagram
- String Rotation
- Run-Length Encoding
- Longest Common Prefix
- First Non-Repeating Character
- Implement atoi()
- Reverse Each Word

Advanced

- KMP Pattern Matching
- Rabin-Karp
- Boyer-Moore
- Trie-based Dictionary Search
- Longest Palindromic Substring
- Longest Repeating Substring
- Edit Distance
- Minimum Window Substring
- Z Algorithm
- Suffix Array
- Suffix Tree

---

# Interview Tips

- Know the difference between `char[]`, `char *`, and string literals.
- Be able to implement `strlen()`, `strcpy()`, `strcmp()`, `memcpy()`, `memmove()`, `memcmp()`, `memset()`, and a basic `atoi()` without using the standard library.
- Understand why `memmove()` is required for overlapping memory regions.
- Use a frequency array for anagrams, duplicate removal, and first unique character problems.
- Practice the "reverse whole string, then reverse each word" technique—it appears frequently in interviews.
- For embedded and systems interviews, expect questions about memory functions (`memcpy`, `memmove`, `memset`) and their edge cases, not just high-level string manipulation.
- -------------------------------------------------------------------
