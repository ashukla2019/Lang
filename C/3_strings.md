# Chapter 3 – Strings
# Part 1 – String Fundamentals

---

# What is a String?

A string is simply an **array of characters** terminated by a special character called the **null character**.

```
String

↓

Characters

↓

Ends with

↓

'\0'
```

Example

```c
"Hello"
```

Internally stored as

```
'H'

'e'

'l'

'l'

'o'

'\0'
```

---

# Character vs String

Character

```c
'A'
```

Type

```c
char
```

Memory

```
+----+
| A  |
+----+
```

Only **one character**.

---

String

```c
"ABC"
```

Memory

```
+----+----+----+----+
| A  | B  | C  |\0  |
+----+----+----+----+
```

Contains multiple characters followed by a null terminator.

---

# Why Do Strings End with '\0'?

Suppose

```c
char str[] = "Hello";
```

Memory

```
Index

0   1   2   3   4   5

+---+---+---+---+---+----+
| H | e | l | l | o |\0  |
+---+---+---+---+---+----+
```

How does

```c
printf("%s", str);
```

know where to stop?

It prints characters until it reaches

```
'\0'
```

Without the null terminator,

the function would continue reading memory beyond the string, resulting in undefined behavior.

---

# Character Array

Example

```c
char str[6] =
{
    'H',
    'e',
    'l',
    'l',
    'o',
    '\0'
};
```

Memory

```
+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  |
+----+----+----+----+----+----+
```

This is exactly equivalent to

```c
char str[] = "Hello";
```

The compiler automatically adds the null terminator.

---

# Compiler Expansion

When you write

```c
char str[] = "Hello";
```

The compiler creates

```c
char str[6] =
{
'H',
'e',
'l',
'l',
'o',
'\0'
};
```

This is one of the most common interview questions.

---

# String Literal

Consider

```c
"Hello"
```

This is called a **string literal**.

A string literal is stored in a read-only section of memory (typically).

Example

```c
char *p = "Hello";
```

Memory

```
Stack

+------+
|  p   |
+------+
    |
    ▼

Read-Only Memory

+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  |
+----+----+----+----+----+----+
```

---

# Character Array vs String Literal

## Character Array

```c
char str[] = "Hello";
```

Memory

```
Stack

+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  |
+----+----+----+----+----+----+
```

The array owns its own copy.

---

## String Literal

```c
char *str = "Hello";
```

Memory

```
Stack

+------+
| str  |
+------+
    |
    ▼

Read-Only Memory

"Hello"
```

The pointer points to an existing string literal.

---

# Important Difference

Example 1

```c
char str[] = "Hello";

str[0] = 'Y';
```

Result

```
Yello
```

Allowed.

---

Example 2

```c
char *str = "Hello";

str[0] = 'Y';
```

Undefined behavior.

On many systems,

the program crashes with a segmentation fault because string literals are typically stored in read-only memory.

---

# Why?

Character array

```
Own Copy

↓

Writable
```

String literal

```
Shared Literal

↓

Read-Only
```

---

# Interview Tip

Although C allows

```c
char *str = "Hello";
```

Modern C code should usually write

```c
const char *str = "Hello";
```

This prevents accidental modification.

---

# Size of Character Array

Example

```c
char str[] = "Hello";
```

Memory

```
H

e

l

l

o

\0
```

Total bytes

```
6
```

Therefore

```c
sizeof(str)
```

returns

```
6
```

---

# strlen()

Example

```c
strlen(str)
```

Counts only characters **before** `'\0'`.

Result

```
5
```

---

# sizeof() vs strlen()

Example

```c
char str[] = "Hello";
```

```
sizeof(str)

↓

6
```

```
strlen(str)

↓

5
```

Reason

```
sizeof

↓

Counts Entire Array

Including '\0'
```

```
strlen

↓

Counts Characters

Excluding '\0'
```

---

# Example

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "Hello";

    printf("%zu\n", sizeof(str));

    printf("%zu\n", strlen(str));

    return 0;
}
```

Output

```
6

5
```

---

# String Without Null Terminator

Example

```c
char str[5] =
{
'H',
'e',
'l',
'l',
'o'
};
```

Memory

```
+----+----+----+----+----+
| H  | e  | l  | l  | o  |
+----+----+----+----+----+
```

Now

```c
printf("%s", str);
```

Undefined behavior.

`printf()` keeps reading memory until it accidentally finds a `'\0'`.

---

# Empty String

Example

```c
char str[] = "";
```

Memory

```
+----+
|\0  |
+----+
```

```
strlen(str)

↓

0
```

```
sizeof(str)

↓

1
```

---

# String Length Examples

```
""

Length = 0

Size = 1
```

---

```
"A"

Length = 1

Size = 2
```

---

```
"Hello"

Length = 5

Size = 6
```

---

# Accessing Characters

```c
char str[] = "Hello";

printf("%c\n", str[1]);
```

Output

```
e
```

Equivalent to

```c
*(str+1)
```

Remember

```
Array Indexing

↓

Pointer Arithmetic
```

---

# Modifying Characters

```c
char str[] = "Hello";

str[1] = 'a';

printf("%s", str);
```

Output

```
Hallo
```

Allowed because it is an array.

---

# String Copy During Initialization

```c
char str[] = "Hello";
```

The compiler copies

```
H

e

l

l

o

\0
```

into the array.

Changing the array does **not** change the original string literal.

---

# Key Interview Takeaways

✅ Every C string ends with a **null terminator (`'\0'`)**.

✅ `char str[] = "Hello";` creates a writable character array.

✅ `char *str = "Hello";` points to a string literal that should be treated as read-only.

✅ `sizeof()` returns the total size of the array (including `'\0'`), while `strlen()` returns only the number of characters before the null terminator.

✅ Array indexing (`str[i]`) is implemented using pointer arithmetic (`*(str + i)`).

---

# Next Part

In **Part 2**, we'll cover the most frequently used string library functions:

- `strlen()`
- `strcpy()`
- `strncpy()`
- Buffer overflows
- Safe string copying
- Interview pitfalls and tricky questions
- ---------------------------------------------------------------
# C Interview Handbook
# Chapter 3 – Strings
# Part 2 – `strlen()`, `strcpy()`, `strncpy()` and Safe String Copying

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Linux Kernel Teams

---

# Standard Header

All string functions are declared in

```c
#include <string.h>
```

---

# strlen()

Prototype

```c
size_t strlen(const char *str);
```

Purpose

```
Counts Characters

↓

Until '\0'
```

---

# Example

```c
char str[] = "Hello";

printf("%zu\n", strlen(str));
```

Output

```
5
```

---

# Memory Diagram

```
Index

0   1   2   3   4   5

+---+---+---+---+---+----+
| H | e | l | l | o |\0  |
+---+---+---+---+---+----+
```

Execution

```
H

↓

e

↓

l

↓

l

↓

o

↓

'\0'

↓

Stop
```

Characters counted

```
5
```

---

# Internal Working of strlen()

A simplified implementation

```c
size_t my_strlen(const char *str)
{
    size_t count = 0;

    while(*str != '\0')
    {
        count++;
        str++;
    }

    return count;
}
```

Execution

```
Pointer

↓

Read Character

↓

Is '\0' ?

↓

No

↓

Move Forward

↓

Repeat
```

---

# Time Complexity

Suppose

```
Length

=

N
```

`strlen()` checks every character.

Time Complexity

```
O(N)
```

---

# Common Interview Question

Is this efficient?

```c
for(int i=0; i<strlen(str); i++)
{
    printf("%c", str[i]);
}
```

No.

Each iteration calls `strlen()` again.

Complexity

```
N × N

↓

O(N²)
```

Better

```c
size_t len = strlen(str);

for(size_t i=0; i<len; i++)
{
    printf("%c", str[i]);
}
```

Complexity

```
O(N)
```

---

# sizeof() vs strlen()

Example

```c
char str[] = "Hello";
```

```
sizeof(str)

↓

6
```

```
strlen(str)

↓

5
```

Reason

```
sizeof()

↓

Entire Array

↓

Includes '\0'
```

```
strlen()

↓

Characters Only

↓

Stops at '\0'
```

---

# String Copy

Suppose

```c
char src[] = "Hello";
```

Need another copy

```
Hello

↓

Hello
```

Use

```c
strcpy()
```

---

# strcpy()

Prototype

```c
char *strcpy(char *dest,
             const char *src);
```

Purpose

```
Copy Source

↓

Destination

↓

Including '\0'
```

---

# Example

```c
char src[] = "Hello";

char dest[10];

strcpy(dest, src);

printf("%s\n", dest);
```

Output

```
Hello
```

---

# Memory Diagram

Before

```
src

H e l l o \0
```

```
dest

? ? ? ? ? ? ?
```

After

```
src

H e l l o \0
```

```
dest

H e l l o \0
```

---

# Internal Working

Simplified implementation

```c
char *my_strcpy(char *dest,
                const char *src)
{
    char *start = dest;

    while((*dest++ = *src++) != '\0')
    {
    }

    return start;
}
```

Execution

```
Copy One Character

↓

Move Both Pointers

↓

Repeat

↓

Copy '\0'

↓

Stop
```

---

# Why Copy '\0'?

Without it

```
Destination

↓

Not a String
```

Functions like

```c
printf("%s", dest);
```

would read beyond the copied characters.

---

# Destination Must Have Enough Space

Correct

```c
char src[] = "Hello";

char dest[10];

strcpy(dest, src);
```

---

Wrong

```c
char dest[3];

strcpy(dest, "Hello");
```

Memory

```
Destination

+----+----+----+
| ?  | ?  | ?  |
+----+----+----+
```

Need

```
H

e

l

l

o

\0
```

Six bytes.

Result

```
Buffer Overflow
```

Undefined behavior.

---

# Buffer Overflow

Example

```c
char name[5];

strcpy(name, "Robert");
```

Memory

```
name

+----+----+----+----+----+
| R  | o  | b  | e  | r  |
+----+----+----+----+----+

Remaining Bytes

↓

Written Beyond Array
```

This overwrites adjacent memory.

Possible results

- Crash
- Data corruption
- Security vulnerability

---

# strncpy()

Prototype

```c
char *strncpy(char *dest,
              const char *src,
              size_t n);
```

Purpose

```
Copy

↓

At Most

↓

n Characters
```

---

# Example

```c
char src[] = "Hello";

char dest[10];

strncpy(dest, src, 3);

printf("%s\n", dest);
```

Output

May be

```
Hel...
```

or undefined behavior because `dest` is **not guaranteed** to be null-terminated.

This surprises many developers.

---

# Important Difference

`strcpy()`

```
Always Copies

↓

'\0'
```

`strncpy()`

```
Copies

↓

Up To n Characters

↓

May NOT Copy '\0'
```

---

# Example

```c
char src[] = "Hello";

char dest[6];

strncpy(dest, src, 5);
```

Memory

```
H

e

l

l

o

?
```

Notice

```
No '\0'
```

`printf("%s", dest);`

Undefined behavior.

---

# Safe Usage of strncpy()

```c
char dest[6];

strncpy(dest, src, sizeof(dest)-1);

dest[sizeof(dest)-1] = '\0';
```

Now

```
Always

↓

Null Terminated
```

---

# When Source is Smaller

```c
char src[] = "Hi";

char dest[10];

strncpy(dest, src, 10);
```

Memory

```
H

i

\0

\0

\0

\0

...
```

`strncpy()` fills the remaining bytes with `'\0'`.

---

# Key Interview Takeaways

✅ `strlen()` returns the number of characters before `'\0'`.

✅ `strcpy()` copies the entire string including the null terminator.

✅ `strcpy()` never checks whether the destination buffer is large enough.

✅ `strncpy()` limits the number of copied characters but **does not guarantee null termination**.

✅ Never call `strlen()` repeatedly inside a loop when the string doesn't change.

---

# Next Part

In **Part 3**, we'll cover:

- `strcat()`
- `strncat()`
- `strcmp()`
- `strncmp()`
- Lexicographical comparison
- ASCII ordering
- -------------------------------------------------------------
# C Interview Handbook
# Chapter 3 – Strings
# Part 3 – `strcat()`, `strncat()`, `strcmp()`, `strncmp()`

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Linux Kernel Teams

---

# String Concatenation

Concatenation means

```
Join Two Strings

↓

One Larger String
```

Example

```
"Hello"

+

" World"

↓

"Hello World"
```

---

# strcat()

Prototype

```c
char *strcat(char *dest,
             const char *src);
```

Purpose

```
Append

↓

Source

↓

To End Of Destination
```

---

# Example

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char dest[20] = "Hello";

    strcat(dest, " World");

    printf("%s\n", dest);

    return 0;
}
```

Output

```
Hello World
```

---

# How strcat() Works

Suppose

```c
char dest[20] = "Hello";
```

Memory before

```
Index

0 1 2 3 4 5

H e l l o \0
```

Source

```
W o r l d \0
```

---

Execution

Step 1

Find the null terminator.

```
H

↓

e

↓

l

↓

l

↓

o

↓

'\0'
```

---

Step 2

Start copying.

```
H e l l o W o r l d \0
```

Final memory

```
H

e

l

l

o

(space)

W

o

r

l

d

\0
```

---

# Internal Working

Simplified implementation

```c
char *my_strcat(char *dest,
                const char *src)
{
    char *start = dest;

    while(*dest != '\0')
    {
        dest++;
    }

    while((*dest++ = *src++) != '\0')
    {
    }

    return start;
}
```

Execution

```
Find '\0'

↓

Copy Characters

↓

Copy '\0'

↓

Done
```

---

# Destination Must Be Large Enough

Correct

```c
char str[20] = "Hello";

strcat(str, " World");
```

---

Wrong

```c
char str[6] = "Hello";

strcat(str, "World");
```

Need

```
HelloWorld\0

↓

11 Bytes
```

Array has only

```
6 Bytes
```

Result

```
Buffer Overflow
```

Undefined behavior.

---

# Common Interview Question

Why must the destination be initialized?

Correct

```c
char str[20] = "";
```

Wrong

```c
char str[20];

strcat(str, "ABC");
```

Reason

`strcat()` first searches for `'\0'`.

If the array contains garbage,

it may never find a valid null terminator.

---

# strncat()

Prototype

```c
char *strncat(char *dest,
              const char *src,
              size_t n);
```

Purpose

```
Append

↓

At Most

↓

n Characters
```

---

# Example

```c
char str[20] = "Hello";

strncat(str, " World", 3);

printf("%s\n", str);
```

Output

```
Hello Wo
```

Only

```
(space)

W

o
```

are appended.

---

# Important Difference

`strcat()`

```
Append Entire String
```

`strncat()`

```
Append

↓

At Most n Characters
```

Unlike `strncpy()`, `strncat()` **always appends a null terminator** (provided the destination buffer has enough space).

---

# String Comparison

Can we compare strings using

```c
==
```

No.

Example

```c
char s1[] = "ABC";
char s2[] = "ABC";

if(s1 == s2)
```

This compares

```
Addresses

NOT

Contents
```

---

# Correct Way

Use

```c
strcmp()
```

---

# strcmp()

Prototype

```c
int strcmp(const char *s1,
           const char *s2);
```

Purpose

```
Compare

↓

Two Strings

↓

Character By Character
```

---

# Return Value

If

```
Strings Equal
```

returns

```
0
```

---

If

```
First String

<

Second String
```

returns

```
Negative Value
```

---

If

```
First String

>

Second String
```

returns

```
Positive Value
```

---

# Example

```c
char s1[] = "ABC";
char s2[] = "ABC";

printf("%d\n", strcmp(s1,s2));
```

Output

```
0
```

---

# Example

```c
strcmp("ABC","ABD")
```

Comparison

```
A == A

↓

B == B

↓

C < D
```

Return

```
Negative
```

---

# Example

```c
strcmp("XYZ","ABC")
```

Comparison

```
X > A
```

Return

```
Positive
```

---

# Lexicographical Order

`strcmp()` compares strings based on **ASCII values**.

Example

```
Apple

↓

Ball

↓

Cat

↓

Dog
```

Alphabetical order follows ASCII ordering.

---

# ASCII Example

```
'A'

↓

65
```

```
'B'

↓

66
```

```
'a'

↓

97
```

Notice

```
'A'

<

'a'
```

Uppercase letters come before lowercase letters in ASCII.

---

# Example

```c
strcmp("Apple","apple")
```

Comparison

```
'A'

↓

65

'a'

↓

97
```

Return

```
Negative
```

because

```
65 < 97
```

---

# Internal Working

Simplified implementation

```c
int my_strcmp(const char *s1,
              const char *s2)
{
    while(*s1 == *s2)
    {
        if(*s1 == '\0')
            return 0;

        s1++;
        s2++;
    }

    return *s1 - *s2;
}
```

---

# strncmp()

Prototype

```c
int strncmp(const char *s1,
            const char *s2,
            size_t n);
```

Purpose

```
Compare

↓

Only First

↓

n Characters
```

---

# Example

```c
strncmp("abcdef",
        "abcxyz",
         3);
```

Comparison

```
abc

↓

abc
```

Return

```
0
```

because only the first three characters are compared.

---

# Another Example

```c
strncmp("abcd",
        "abce",
        4);
```

Comparison

```
a == a

↓

b == b

↓

c == c

↓

d < e
```

Return

```
Negative
```

---

# strcmp() vs strncmp()

| strcmp() | strncmp() |
|-----------|-----------|
| Compare entire string | Compare first n characters |
| Stops at first mismatch or `'\0'` | Stops after n characters or mismatch |
| Used for full comparison | Used for prefix comparison |

---

# Practical Example

Check whether a file starts with

```
PNG
```

```c
if(strncmp(header,
           "PNG",
           3) == 0)
{
    printf("PNG File\n");
}
```

Only the first three characters matter.

---

# Key Interview Takeaways

✅ `strcat()` appends one string to another and requires enough space in the destination buffer.

✅ `strncat()` appends at most `n` characters but still requires a sufficiently large destination buffer.

✅ Never compare strings using `==`; use `strcmp()` or `strncmp()`.

✅ `strcmp()` compares strings lexicographically using ASCII values.

✅ Check the **sign** of `strcmp()`'s return value (`< 0`, `== 0`, `> 0`), not specific values like `-1` or `1`.

---

# Next Part

In **Part 4**, we'll cover advanced string search and tokenization functions:

- `strchr()`
- `strrchr()`
- `strstr()`
- `strtok()`
- `strspn()`
- `strcspn()`
- `strpbrk()`

These functions are commonly used in parsers, command-line utilities, network software, and Linux system programming.
--------------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 3 – Strings
# Part 4 – `strchr()`, `strrchr()`, `strstr()`, `strtok()`, `strspn()`, `strcspn()`, `strpbrk()`

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Linux Kernel Teams

---

# String Search Functions

```
String

↓

Find Character

↓

Find Last Character

↓

Find Substring

↓

Split String

↓

Count Matching Characters
```

---

# strchr()

Prototype

```c
char *strchr(const char *str,
             int ch);
```

Purpose

```
Find

↓

First Occurrence

↓

Of Character
```

---

## Example

```c
#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "Hello";

    char *p = strchr(str, 'l');

    printf("%s\n", p);
}
```

Output

```
llo
```

---

## Memory

```
H

e

l

l

o

\0
      ^
      |
 Returned Pointer
```

It returns a pointer to the **first** matching character.

---

# Character Not Found

```c
char *p = strchr("Hello",'x');

printf("%p\n",(void*)p);
```

Output

```
NULL
```

Always check before dereferencing.

---

# Common Usage

```c
if(strchr(filename,'.'))
{
    printf("Extension Exists\n");
}
```

---

# strchr() Internally

```c
char *my_strchr(const char *str,
                int ch)
{
    while(*str)
    {
        if(*str == ch)
            return (char *)str;

        str++;
    }

    return NULL;
}
```

Complexity

```
O(N)
```

---

# strrchr()

Prototype

```c
char *strrchr(const char *str,
              int ch);
```

Purpose

```
Find

↓

Last Occurrence
```

---

## Example

```c
char str[] = "Hello";

char *p = strrchr(str,'l');

printf("%s\n", p);
```

Output

```
lo
```

---

Memory

```
H

e

l

l

o

\0

        ^
        |
 Last Match
```

---

# Practical Example

Extract file extension

```c
char file[] = "photo.jpeg";

char *ext = strrchr(file,'.');

if(ext)
{
    printf("%s\n", ext);
}
```

Output

```
.jpeg
```

---

# strchr() vs strrchr()

| strchr() | strrchr() |
|-----------|------------|
| First match | Last match |
| Left to Right | Last occurrence returned |

---

# strstr()

Prototype

```c
char *strstr(const char *str,
             const char *substr);
```

Purpose

```
Find

↓

Substring

↓

Inside Another String
```

---

## Example

```c
char str[] = "Welcome to Qualcomm";

char *p = strstr(str,"Qual");

printf("%s\n",p);
```

Output

```
Qualcomm
```

---

Memory

```
Welcome to Qualcomm
           ^
           |
      Returned Pointer
```

---

## Not Found

```c
char *p = strstr("Hello","xyz");
```

Result

```
NULL
```

---

# Internal Idea

```
Start at First Character

↓

Compare Entire Substring

↓

If Match

↓

Return Pointer

↓

Else

↓

Move One Character

↓

Repeat
```

Complexity

```
O(N × M)
```

where

```
N

↓

Main String

M

↓

Substring
```

---

# strtok()

One of the most asked interview functions.

Prototype

```c
char *strtok(char *str,
             const char *delim);
```

Purpose

```
Split

↓

String

↓

Into Tokens
```

---

# Example

```c
char str[] = "Apple,Banana,Mango";

char *token = strtok(str, ",");

while(token)
{
    printf("%s\n", token);

    token = strtok(NULL,",");
}
```

Output

```
Apple

Banana

Mango
```

---

# Memory Before

```
Apple,Banana,Mango
```

---

Memory After

```
Apple\0Banana\0Mango\0
```

Notice

```
','

↓

Replaced

↓

'\0'
```

---

# Why strtok(NULL, "," )?

First call

```c
strtok(str,",");
```

starts parsing.

Later calls

```c
strtok(NULL,",");
```

continue from the previous position.

---

Execution

```
Apple,Banana,Mango

↓

Apple

↓

Banana

↓

Mango

↓

NULL
```

---

# Important Limitation

`strtok()`

**Modifies the original string.**

Example

```c
char str[]="A,B,C";

strtok(str,",");
```

Now

```
A\0B\0C
```

Original string is destroyed.

---

# Cannot Use String Literal

Wrong

```c
char *str = "A,B,C";

strtok(str,",");
```

Undefined behavior.

Because string literals are read-only.

Correct

```c
char str[] = "A,B,C";
```

---

# CSV Parsing

Input

```
John,25,Engineer
```

Program

```c
char data[]="John,25,Engineer";

char *token = strtok(data,",");

while(token)
{
    printf("%s\n",token);

    token = strtok(NULL,",");
}
```

Output

```
John

25

Engineer
```

---

# strspn()

Prototype

```c
size_t strspn(const char *str,
              const char *accept);
```

Purpose

```
Count

↓

Initial Characters

↓

Present In accept
```

---

Example

```c
printf("%zu\n",
strspn("123ABC",
       "0123456789"));
```

Output

```
3
```

Reason

```
123

↓

Digits
```

Stops at

```
A
```

---

# Another Example

```c
strspn("abcdef",
       "abcxyz");
```

Result

```
3
```

Because

```
abc

↓

Match
```

---

# strcspn()

Prototype

```c
size_t strcspn(const char *str,
               const char *reject);
```

Purpose

```
Count

↓

Characters

↓

Until First Reject
```

---

Example

```c
printf("%zu\n",
strcspn("Hello123",
        "0123456789"));
```

Output

```
5
```

Reason

```
Hello

↓

First Digit

↓

Stop
```

---

# strspn() vs strcspn()

Input

```
123ABC
```

```
Accept

↓

Digits
```

`strspn()`

```
3
```

---

Input

```
Hello123
```

Reject

```
Digits
```

`strcspn()`

```
5
```

---

# strpbrk()

Prototype

```c
char *strpbrk(const char *str,
              const char *accept);
```

Purpose

```
Find

↓

First Character

↓

Matching Any Character
```

---

Example

```c
char str[]="Linux123";

char *p = strpbrk(str,"0123456789");

printf("%s\n",p);
```

Output

```
123
```

---

Memory

```
Linux123
     ^
     |
 Returned Pointer
```

---

# Real Interview Examples

## Example 1

Find extension

```c
char *ext = strrchr(file,'.');
```

---

## Example 2

Check file type

```c
if(strstr(filename,".txt"))
```

---

## Example 3

Parse CSV

```c
strtok(data,",");
```

---

## Example 4

Check if a string starts with digits

```c
size_t n = strspn(str,
                  "0123456789");
```

---

## Example 5

Find first vowel

```c
char *p = strpbrk(str,
                  "aeiouAEIOU");
```

---

# Key Interview Takeaways

✅ `strchr()` returns a pointer to the first matching character.

✅ `strrchr()` returns a pointer to the last matching character.

✅ `strstr()` searches for a substring and returns a pointer to its first occurrence.

✅ `strtok()` is widely used for parsing CSV files and command-line input, but it **modifies the original string**.

✅ `strspn()` counts the length of the initial segment containing only accepted characters, while `strcspn()` counts until the first rejected character.

---

# Next Part

In **Part 5**, we'll cover:

- `argc` and `argv`
- Command-line arguments
- Array of strings
- `char **`
- Pointer-to-pointer concepts
- Environment variables (`envp`)
- Frequently asked Qualcomm/NVIDIA interview questions on command-line processing
- -----------------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 3 – Strings
# Part 5 – Command Line Arguments, Array of Strings, `char **`, Environment Variables

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Linux Kernel Teams

---

# Command Line Arguments

Normally,

we run a program like

```
./program
```

Sometimes we want to pass information to it.

Example

```
./program file.txt
```

or

```
./calculator 20 30
```

These values are called

```
Command Line Arguments
```

---

# main() Function

Instead of

```c
int main()
```

we can write

```c
int main(int argc, char *argv[])
```

or

```c
int main(int argc, char **argv)
```

Both are identical.

---

# argc

```
Argument Count
```

Stores

```
Number Of Arguments
```

including the program name.

Example

```
./calculator 10 20
```

Arguments

```
argv[0]

↓

"./calculator"

argv[1]

↓

"10"

argv[2]

↓

"20"
```

Therefore

```
argc

↓

3
```

---

# argv

```
Argument Vector
```

Stores

```
Array Of Pointers

↓

Each Pointer

↓

One String
```

---

# Memory Layout

Command

```
./program apple banana orange
```

Memory

```
argc = 4

argv

+-----+
|  *--|-------> "./program"
+-----+
|  *--|-------> "apple"
+-----+
|  *--|-------> "banana"
+-----+
|  *--|-------> "orange"
+-----+
|NULL |
+-----+
```

Notice

```
argv

↓

Array

↓

Of

↓

Character Pointers
```

---

# Example

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);

    for(int i=0; i<argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}
```

Run

```
./program one two three
```

Output

```
argc = 4

./program

one

two

three
```

---

# Why argv[0]?

By convention,

```
argv[0]
```

contains

```
Program Name
```

or the path used to execute the program.

---

# Numeric Arguments

Command

```
./add 20 30
```

Memory

```
argv[1]

↓

"20"

argv[2]

↓

"30"
```

Notice

They are

```
Strings

Not Integers
```

Need conversion.

Example

```c
#include <stdlib.h>

int a = atoi(argv[1]);

int b = atoi(argv[2]);

printf("%d\n", a+b);
```

Output

```
50
```

---

# Why Strings?

The operating system passes

```
Characters

↓

Not Integers
```

Your program decides how to interpret them.

---

# char *argv[]

Declaration

```c
char *argv[]
```

Meaning

```
argv

↓

Array

↓

Of Character Pointers
```

Each pointer points to one string.

---

# char **argv

Equivalent declaration

```c
char **argv
```

Meaning

```
argv

↓

Pointer

↓

To Pointer

↓

To Character
```

---

# Why Are They Equivalent?

Array parameters decay into pointers.

Function parameter

```c
char *argv[]
```

becomes

```c
char **argv
```

Exactly like

```c
int arr[]
```

becomes

```c
int *arr
```

---

# Visualizing argv

```
argv

↓

+-------+
|   *---|------> "./program"
+-------+
|   *---|------> "input.txt"
+-------+
|   *---|------> "100"
+-------+
| NULL  |
+-------+
```

Each string

```
"./program"

↓

Characters

↓

'\0'
```

---

# Accessing Characters

Example

```c
printf("%c\n", argv[1][0]);
```

Suppose

```
argv[1]

↓

"Apple"
```

Then

```
argv[1][0]

↓

'A'
```

---

# Pointer Interpretation

```
argv

↓

char **

↓

argv[1]

↓

char *

↓

argv[1][2]

↓

char
```

---

# Array of Strings

Example

```c
char *fruits[] =
{
    "Apple",
    "Mango",
    "Orange"
};
```

Memory

```
fruits

+------+
|  *---|-----> "Apple"
+------+
|  *---|-----> "Mango"
+------+
|  *---|-----> "Orange"
+------+
```

Exactly like

```
argv
```

---

# Iterating

```c
for(int i=0;i<3;i++)
{
    printf("%s\n", fruits[i]);
}
```

Output

```
Apple

Mango

Orange
```

---

# Pointer to Pointer Example

```c
char *name = "Linux";

char **pp = &name;

printf("%s\n", *pp);
```

Output

```
Linux
```

---

Memory

```
pp

↓

name

↓

"Linux"
```

---

# Triple Dereference?

Suppose

```c
char c = 'A';

char *p = &c;

char **pp = &p;
```

Then

```
pp

↓

p

↓

c
```

```
**pp

↓

'A'
```

---

# Environment Variables

Programs also receive

```
Environment Variables
```

Example

```
PATH

HOME

USER

SHELL
```

---

Some systems use

```c
int main(int argc,
         char *argv[],
         char *envp[])
```

Here

```
envp

↓

Array Of Strings
```

Similar to

```
argv
```

---

# Printing Environment Variables

```c
#include <stdio.h>

int main(int argc,
         char *argv[],
         char *envp[])
{
    while(*envp)
    {
        printf("%s\n", *envp);

        envp++;
    }

    return 0;
}
```

Output

```
PATH=...

HOME=...

USER=...

...
```

---

# getenv()

Preferred method

```c
#include <stdlib.h>

char *path = getenv("PATH");

printf("%s\n", path);
```

---

# Real Embedded Usage

Command

```
./flash firmware.bin
```

```
argv[1]

↓

firmware.bin
```

Open file

```
fopen(argv[1],"rb");
```

---

Example

```
./logger log.txt
```

```
argv[1]

↓

Log File
```

---

Example

```
./compress input.txt output.zip
```

```
argv[1]

↓

Input

argv[2]

↓

Output
```

---

# Key Interview Takeaways

✅ `argc` stores the number of command-line arguments, including the program name.

✅ `argv` is an array of pointers, where each pointer refers to a null-terminated string.

✅ `char *argv[]` and `char **argv` are equivalent in function parameters.

✅ Command-line arguments are always strings and must be converted before numeric operations.

✅ `argv` is one of the best real-world examples for understanding arrays of pointers and double pointers.

---

# Next Part

In **Part 6**, we'll solve **25+ frequently asked string coding problems**, including:

- Reverse a string
- Reverse words
- Palindrome
- Count words
- Remove duplicate characters
- Remove spaces
- Character frequency
- Anagram check
- String rotation
- Longest word
- Most frequently asked Qualcomm, NVIDIA, and Broadcom coding questions.
- -------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 3 – Strings
# Part 6 – Most Asked String Coding Problems

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Linux Kernel Teams

---

# Problem 1 – Find String Length (Without strlen)

## Problem

Implement your own `strlen()`.

Example

```
Input

Hello

Output

5
```

---

## Approach

```
Start

↓

Read Character

↓

Increment Count

↓

Until '\0'
```

---

## Code

```c
#include <stdio.h>

int my_strlen(const char *str)
{
    int count = 0;

    while(*str)
    {
        count++;
        str++;
    }

    return count;
}

int main()
{
    printf("%d\n", my_strlen("Hello"));
}
```

---

## Complexity

```
Time

O(N)

Space

O(1)
```

---

# Problem 2 – Reverse String

Input

```
Hello
```

Output

```
olleH
```

---

## Approach

```
Left

↓

Right

↓

Swap

↓

Move Towards Center
```

---

## Code

```c
#include <stdio.h>
#include <string.h>

void reverse(char str[])
{
    int left = 0;
    int right = strlen(str) - 1;

    while(left < right)
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;

        left++;
        right--;
    }
}

int main()
{
    char str[] = "Hello";

    reverse(str);

    printf("%s\n", str);
}
```

---

Complexity

```
O(N)
```

---

# Problem 3 – Check Palindrome

Input

```
madam
```

Output

```
Palindrome
```

---

## Approach

Compare

```
First

↓

Last

↓

Second

↓

Second Last
```

---

## Code

```c
#include <stdio.h>
#include <string.h>

int isPalindrome(char str[])
{
    int left = 0;
    int right = strlen(str)-1;

    while(left < right)
    {
        if(str[left] != str[right])
            return 0;

        left++;
        right--;
    }

    return 1;
}

int main()
{
    char str[] = "madam";

    if(isPalindrome(str))
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");
}
```

---

Complexity

```
O(N)
```

---

# Problem 4 – Count Words

Input

```
I love C programming
```

Output

```
4
```

---

## Approach

Count transitions

```
Space

↓

Character
```

---

## Code

```c
#include <stdio.h>

int countWords(char str[])
{
    int count = 0;
    int inWord = 0;

    while(*str)
    {
        if(*str != ' ' && !inWord)
        {
            count++;
            inWord = 1;
        }
        else if(*str == ' ')
        {
            inWord = 0;
        }

        str++;
    }

    return count;
}

int main()
{
    char str[] = "I love C programming";

    printf("%d\n", countWords(str));
}
```

---

Complexity

```
O(N)
```

---

# Problem 5 – Count Vowels

Input

```
Interview
```

Output

```
4
```

---

## Code

```c
#include <stdio.h>

int countVowels(char str[])
{
    int count = 0;

    while(*str)
    {
        switch(*str)
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                count++;
        }

        str++;
    }

    return count;
}

int main()
{
    char str[] = "Interview";

    printf("%d\n", countVowels(str));
}
```

---

# Problem 6 – Count Character Frequency

Input

```
banana
```

Output

```
a : 3

b : 1

n : 2
```

---

## Approach

ASCII table

```
256 Counters
```

---

## Code

```c
#include <stdio.h>

int main()
{
    char str[] = "banana";

    int freq[256] = {0};

    int i = 0;

    while(str[i])
    {
        freq[(unsigned char)str[i]]++;
        i++;
    }

    for(i=0;i<256;i++)
    {
        if(freq[i])
            printf("%c : %d\n", i, freq[i]);
    }
}
```

---

Complexity

```
O(N)
```

---

# Problem 7 – Remove Spaces

Input

```
I Love C
```

Output

```
ILoveC
```

---

## Code

```c
#include <stdio.h>

void removeSpaces(char str[])
{
    int i = 0;
    int j = 0;

    while(str[i])
    {
        if(str[i] != ' ')
            str[j++] = str[i];

        i++;
    }

    str[j] = '\0';
}

int main()
{
    char str[] = "I Love C";

    removeSpaces(str);

    printf("%s\n", str);
}
```

---

Complexity

```
O(N)
```

---

# Problem 8 – Convert to Uppercase

Input

```
hello
```

Output

```
HELLO
```

---

## Code

```c
#include <stdio.h>

void upper(char str[])
{
    while(*str)
    {
        if(*str >= 'a' && *str <= 'z')
            *str -= ('a' - 'A');

        str++;
    }
}

int main()
{
    char str[] = "hello";

    upper(str);

    printf("%s\n", str);
}
```

---

# Problem 9 – Convert to Lowercase

```c
#include <stdio.h>

void lower(char str[])
{
    while(*str)
    {
        if(*str >= 'A' && *str <= 'Z')
            *str += ('a' - 'A');

        str++;
    }
}

int main()
{
    char str[] = "HELLO";

    lower(str);

    printf("%s\n", str);
}
```

---

# Problem 10 – Compare Two Strings (Without strcmp)

```c
#include <stdio.h>

int mystrcmp(char s1[],
             char s2[])
{
    while(*s1 && *s2)
    {
        if(*s1 != *s2)
            return *s1 - *s2;

        s1++;
        s2++;
    }

    return *s1 - *s2;
}

int main()
{
    printf("%d\n",
        mystrcmp("ABC","ABD"));
}
```

---

# Problem 11 – Copy String (Without strcpy)

```c
#include <stdio.h>

void mycopy(char dest[],
            char src[])
{
    while((*dest++ = *src++));
}

int main()
{
    char src[] = "Linux";
    char dest[20];

    mycopy(dest, src);

    printf("%s\n", dest);
}
```

---

# Problem 12 – Concatenate Strings (Without strcat)

```c
#include <stdio.h>

void mycat(char dest[],
           char src[])
{
    while(*dest)
        dest++;

    while((*dest++ = *src++));
}

int main()
{
    char str[30] = "Hello";

    mycat(str," World");

    printf("%s\n",str);
}
```

---

# Problem 13 – Find First Occurrence of Character

```c
#include <stdio.h>

int find(char str[],
         char ch)
{
    int i=0;

    while(str[i])
    {
        if(str[i]==ch)
            return i;

        i++;
    }

    return -1;
}

int main()
{
    printf("%d\n",
           find("Qualcomm",'c'));
}
```

---

# Problem 14 – Remove Duplicate Characters

Input

```
programming
```

Output

```
progamin
```

---

## Approach

```
Visited Array

↓

256 Entries
```

---

```c
#include <stdio.h>

void removeDuplicates(char str[])
{
    int visited[256] = {0};
    int i = 0, j = 0;

    while(str[i])
    {
        unsigned char ch = str[i];

        if(!visited[ch])
        {
            visited[ch] = 1;
            str[j++] = str[i];
        }

        i++;
    }

    str[j] = '\0';
}

int main()
{
    char str[] = "programming";

    removeDuplicates(str);

    printf("%s\n", str);
}
```

---

# Problem 15 – Check Anagram

Input

```
listen

silent
```

Output

```
Anagram
```

---

## Approach

```
Count Frequency

↓

Compare
```

---

```c
#include <stdio.h>

int isAnagram(char s1[],
              char s2[])
{
    int freq[256] = {0};

    while(*s1)
        freq[(unsigned char)*s1++]++;

    while(*s2)
        freq[(unsigned char)*s2++]--;

    for(int i=0;i<256;i++)
        if(freq[i])
            return 0;

    return 1;
}
```

---

# Problem 16 – Reverse Words

Input

```
I Love C
```

Output

```
C Love I
```

---

**Interview Note**

This is a common Qualcomm/NVIDIA question.

Typical approach:

```
Reverse Entire String

↓

Reverse Individual Words
```

Complexity

```
O(N)
```

---

# Problem 17 – Check Rotation

Input

```
ABCD

CDAB
```

Output

```
Rotation
```

---

Approach

```
ABCDABCD

↓

Search

↓

CDAB
```

Use

```c
strstr()
```

Complexity

```
O(N)
```

---

# Problem 18 – Longest Word

Input

```
I love embedded systems
```

Output

```
embedded
```

Approach

```
Scan Words

↓

Track Longest
```

Complexity

```
O(N)
```

---

# Most Asked Qualcomm/NVIDIA Questions

These appear frequently in embedded interviews:

| Problem | Difficulty |
|----------|------------|
| Reverse string | ⭐ |
| Palindrome | ⭐ |
| Remove spaces | ⭐ |
| Count words | ⭐ |
| Character frequency | ⭐ |
| Reverse words | ⭐⭐ |
| Remove duplicates | ⭐⭐ |
| Anagram | ⭐⭐ |
| String rotation | ⭐⭐ |
| Longest word | ⭐⭐ |
| Implement `strlen()` | ⭐ |
| Implement `strcpy()` | ⭐ |
| Implement `strcmp()` | ⭐ |
| First non-repeating character | ⭐⭐⭐ |
| Compress string | ⭐⭐⭐ |
| Run Length Encoding | ⭐⭐⭐ |
| Replace substring | ⭐⭐⭐ |
| Pattern matching | ⭐⭐⭐ |

---

# Key Interview Takeaways

✅ Be able to implement `strlen()`, `strcpy()`, `strcmp()`, and `strcat()` **without using library functions**.

✅ Most string interview problems can be solved using:
- Two pointers
- Frequency arrays (`int freq[256]`)
- In-place modification
- Careful handling of the null terminator

✅ Always analyze:
- Time complexity
- Space complexity
- Buffer boundaries
- Null termination

---

# Next Part

In **Part 7**, we'll cover **Advanced String Concepts & Undefined Behavior**, including:

- Why string literals are read-only
- Why `gets()` was removed
- `fgets()` vs `gets()`
- Buffer overflow attacks
- Secure string handling
- Undefined behavior examples
- Memory layout of string literals
- Frequently asked theory questions from Qualcomm, NVIDIA, Broadcom, and Intel.
- -----------------------------------------------------------------
# C Interview Handbook
# Chapter 3 – Strings
# Part 7 – Advanced String Concepts, Memory Layout & Undefined Behavior

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Linux Kernel Teams

---

# Memory Layout of a C Program

A C program is divided into several memory regions.

```
High Address
+-----------------------+
|       Stack           |
| Local Variables       |
+-----------------------+
|        Heap           |
| malloc(), calloc()    |
+-----------------------+
|   BSS Segment         |
| Uninitialized Globals |
+-----------------------+
|   Data Segment        |
| Initialized Globals   |
+-----------------------+
| Read-Only Data (.rodata)
| String Literals       |
+-----------------------+
| Code (.text)          |
| Program Instructions  |
+-----------------------+
Low Address
```

---

# Where Are String Literals Stored?

Example

```c
char *str = "Hello";
```

Memory

```
Stack

+--------+
|  str   |
+--------+
     |
     ▼

Read-Only Memory (.rodata)

+----+----+----+----+----+----+
| H  | e  | l  | l  | o  |\0  |
+----+----+----+----+----+----+
```

The pointer lives on the stack.

The string literal usually lives in the read-only section.

---

# Why Read-Only?

Suppose

```c
char *str = "Hello";
```

If every function modified it,

other code using the same literal could also be affected.

Compilers often share identical string literals.

Example

```c
char *s1 = "Linux";
char *s2 = "Linux";
```

Compiler may generate

```
Stack

s1 ----+

        |

s2 ----+

        |

        ▼

"Linux"
```

Both pointers may point to the same memory.

---

# Modifying String Literal

```c
char *str = "Hello";

str[0] = 'Y';
```

Result

```
Undefined Behavior
```

Often

```
Segmentation Fault
```

---

# Why Does This Work?

```c
char str[] = "Hello";

str[0] = 'Y';
```

Memory

```
Stack

H

e

l

l

o

\0
```

Compiler copies the literal into your array.

Now you own the memory.

---

# Interview Question

Which is better?

```c
char *str = "Hello";
```

or

```c
const char *str = "Hello";
```

Preferred

```c
const char *str = "Hello";
```

Reason

```
Compiler Prevents

↓

Accidental Modification
```

---

# String Literal vs Character Array

| Character Array | String Literal |
|-----------------|----------------|
| Writable | Read-only (typically) |
| Own copy | Shared literal |
| Stored in array memory | Stored in `.rodata` |
| Can modify | Should never modify |

---

# gets()

Prototype

```c
gets(char *str);
```

Purpose

```
Read Input

↓

Until Newline
```

---

# Example

```c
char name[10];

gets(name);
```

Looks simple,

but has a huge problem.

---

# Buffer Overflow

Suppose

```
Buffer

↓

10 Bytes
```

User enters

```
ABCDEFGHIJKLMNOPQRSTUVWXYZ
```

Memory

```
+----+----+----+----+----+
| A  | B  | C  | D  | E  |
+----+----+----+----+----+
             ↓
 Continues Writing...
```

Program writes beyond the array.

Result

```
Undefined Behavior
```

Possible consequences

- Crash
- Data corruption
- Security vulnerability

---

# Why Was gets() Removed?

`gets()`

```
Never Knows

↓

Buffer Size
```

Impossible to prevent overflow.

Therefore,

```
gets()

↓

Removed

↓

C11 Standard
```

---

# Safe Alternative

Use

```c
fgets()
```

---

# fgets()

Prototype

```c
char *fgets(char *str,
            int size,
            FILE *stream);
```

Example

```c
char name[20];

fgets(name,
      sizeof(name),
      stdin);
```

Now

```
Maximum Characters

↓

Known
```

Overflow is prevented.

---

# Difference Between gets() and fgets()

| gets() | fgets() |
|---------|----------|
| Removed from C11 | Recommended |
| No length check | Length specified |
| Unsafe | Safer |
| Causes overflow | Prevents overflow |

---

# Newline Issue

Suppose user types

```
Linux
```

`fgets()`

stores

```
L

i

n

u

x

\n

\0
```

Notice

```
Newline Included
```

---

# Removing Newline

```c
str[strcspn(str,"\n")] = '\0';
```

Example

```c
char str[20];

fgets(str,sizeof(str),stdin);

str[strcspn(str,"\n")] = '\0';
```

---

# Undefined Behavior Examples

---

## Example 1

```c
char *str = "Hello";

strcpy(str,"ABC");
```

Undefined behavior.

Destination points to read-only memory.

---

## Example 2

```c
char str[5];

strcpy(str,"Hello");
```

Need

```
6 Bytes
```

Buffer overflow.

---

## Example 3

```c
char str[5];

printf("%s",str);
```

Uninitialized array.

Undefined behavior.

---

## Example 4

```c
char str[5];

scanf("%s",str);
```

No width specified.

Potential overflow.

Safer

```c
scanf("%4s", str);
```

or

```c
fgets()
```

---

## Example 5

```c
char str[] = {'H','i'};
```

Not a string.

Missing

```
'\0'
```

---

## Example 6

```c
char *p = NULL;

printf("%s",p);
```

Undefined behavior.

---

## Example 7

```c
char str[10];

strlen(str);
```

Undefined behavior.

String not initialized.

---

# Secure String Handling

Always

```
Know Buffer Size

↓

Copy Safely

↓

Check Length

↓

Avoid Overflow
```

---

# Common Secure Practices

Instead of

```c
gets(str);
```

Use

```c
fgets(str,
      sizeof(str),
      stdin);
```

---

Instead of

```c
strcpy(dest,src);
```

Consider

```c
strncpy(dest,
        src,
        sizeof(dest)-1);

dest[sizeof(dest)-1]='\0';
```

---

Instead of

```c
scanf("%s",str);
```

Use

```c
scanf("%19s",str);
```

or preferably

```c
fgets()
```

---

# Interview Question

Why is

```c
char *str="Hello";
```

still allowed?

For backward compatibility.

Modern code should prefer

```c
const char *str="Hello";
```

---

# Memory Comparison

## Character Array

```c
char str[]="Hello";
```

```
Stack

H

e

l

l

o

\0
```

---

## Pointer

```c
char *str="Hello";
```

```
Stack

Pointer

↓

Read-Only Memory

Hello
```

---

# Frequently Asked Interview Questions

## Q1. Why are string literals read-only?

Because compilers typically place them in read-only memory and may share them between multiple pointers.

---

## Q2. Why was `gets()` removed?

Because it cannot prevent buffer overflow.

---

## Q3. Which is safer?

```c
gets()
```

or

```c
fgets()
```

Always

```
fgets()
```

---

## Q4. Can string literals be shared?

Yes.

Compiler optimization may reuse identical literals.

---

## Q5. Why use

```c
const char *
```

instead of

```c
char *
```

To prevent accidental modification of string literals.

---

## Q6. Why does `fgets()` store `'\n'`?

Because it reads the newline if there is room in the buffer.

---

## Q7. Why is

```c
strlen(uninitialized_array)
```

undefined?

Because `strlen()` expects a properly null-terminated string.

---

# Real Embedded Examples

### Reading Configuration

```c
char config[128];

fgets(config,
      sizeof(config),
      file);
```

---

### Parsing UART Command

```
LED ON
```

Read safely into a fixed-size buffer before parsing.

---

### Reading File Names

```c
char filename[256];

fgets(filename,
      sizeof(filename),
      stdin);
```

---

# Key Interview Takeaways

✅ String literals are typically stored in the read-only section (`.rodata`).

✅ `char *str = "Hello";` should be treated as read-only; `const char *` is the preferred declaration.

✅ `gets()` was removed because it cannot prevent buffer overflows.

✅ `fgets()` is the recommended replacement because it limits the number of characters read.

✅ Most string-related security bugs come from writing past buffer boundaries or forgetting the null terminator.

---

# Next Part

In **Part 8**, we'll cover **50+ Qualcomm/NVIDIA/Broadcom String Interview Questions**, including:

- Output prediction
- Pointer and string puzzles
- `sizeof()` vs `strlen()`
- String literal vs character array
- Undefined behavior questions
- Frequently asked coding snippets
- Rapid revision sheet for interviews
- -------------------------------------------------------------------------
# C Interview Handbook
# Chapter 3 – Strings
# Part 8 – 50+ Qualcomm/NVIDIA/Broadcom String Interview Questions

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Q1

```c
char str[] = "Hello";

printf("%lu\n", sizeof(str));
printf("%lu\n", strlen(str));
```

Output

```
6
5
```

Explanation

```
sizeof()

↓

Entire Array

↓

Includes '\0'

----------------

strlen()

↓

Characters Only

↓

Stops Before '\0'
```

---

# Q2

```c
char *str = "Hello";

printf("%lu\n", sizeof(str));
printf("%lu\n", strlen(str));
```

Output (64-bit system)

```
8
5
```

Explanation

```
sizeof(str)

↓

Pointer Size

↓

8 Bytes

strlen()

↓

Length Of String
```

---

# Q3

```c
char str[] = {'H','e','l','l','o'};
printf("%s\n", str);
```

Answer

```
Undefined Behavior
```

Reason

Missing

```
'\0'
```

---

# Q4

```c
char str[] = {'H','e','l','l','o','\0'};

printf("%s\n",str);
```

Output

```
Hello
```

---

# Q5

```c
char str[] = "Hello";

str[0] = 'Y';

printf("%s\n", str);
```

Output

```
Yello
```

---

# Q6

```c
char *str = "Hello";

str[0] = 'Y';
```

Answer

```
Undefined Behavior
```

Usually

```
Segmentation Fault
```

---

# Q7

```c
char str[] = "ABC";

printf("%c\n", *(str+1));
```

Output

```
B
```

---

# Q8

```c
char str[] = "Linux";

printf("%s\n", str+2);
```

Output

```
nux
```

Memory

```
L i n u x \0
    ^
```

---

# Q9

```c
char str[] = "Hello";

printf("%c\n", *str);
```

Output

```
H
```

---

# Q10

```c
char str[] = "Hello";

printf("%c\n", *(str+4));
```

Output

```
o
```

---

# Q11

```c
char str[] = "ABCDE";

printf("%s\n", str+3);
```

Output

```
DE
```

---

# Q12

```c
char str[] = "Hello";

printf("%c\n", str[2]);
```

Output

```
l
```

---

# Q13

```c
char str[] = "Hello";

printf("%c\n", 2[str]);
```

Output

```
l
```

Explanation

```
a[b]

↓

*(a+b)

↓

*(b+a)

↓

b[a]
```

---

# Q14

```c
char str[] = "ABCDE";

printf("%c\n", *(2+str));
```

Output

```
C
```

---

# Q15

```c
char str[] = "Hello";

printf("%lu\n", sizeof(str)/sizeof(str[0]));
```

Output

```
6
```

Includes

```
'\0'
```

---

# Q16

```c
char str[20] = "Hello";

printf("%lu\n", sizeof(str));
```

Output

```
20
```

Because

```
Array Size

↓

20 Bytes
```

---

# Q17

```c
char *str = "ABC";

printf("%c\n", *++str);
```

Output

```
B
```

---

# Q18

```c
char str[] = "ABC";

printf("%c\n", *str++);
```

Answer

```
Compilation Error
```

Reason

Array names are **not modifiable lvalues**.

---

# Q19

```c
char *str = "ABC";

printf("%c\n", *str++);
printf("%c\n", *str);
```

Output

```
A
B
```

---

# Q20

```c
char str[] = "Hello";

printf("%s\n",&str[1]);
```

Output

```
ello
```

---

# Q21

```c
char str[] = "Hello";

printf("%s\n",str+1);
```

Output

```
ello
```

---

# Q22

```c
char str[]="ABC";

printf("%c\n",str[strlen(str)-1]);
```

Output

```
C
```

---

# Q23

```c
char str[]="ABC";

printf("%c\n",*(str+strlen(str)-1));
```

Output

```
C
```

---

# Q24

```c
char str[]="ABC";

printf("%d\n",
strcmp("ABC","ABC"));
```

Output

```
0
```

---

# Q25

```c
printf("%d\n",
strcmp("ABC","ABD"));
```

Output

Negative value

---

# Q26

```c
printf("%d\n",
strcmp("ABD","ABC"));
```

Output

Positive value

---

# Q27

```c
char str[]="Embedded";

printf("%s\n",
strchr(str,'d'));
```

Output

```
dded
```

---

# Q28

```c
char str[]="banana";

printf("%s\n",
strrchr(str,'a'));
```

Output

```
a
```

(last occurrence)

---

# Q29

```c
char str[]="Linux Kernel";

printf("%s\n",
strstr(str,"Kernel"));
```

Output

```
Kernel
```

---

# Q30

```c
char str[]="ABC";

printf("%p\n",
(void*)strchr(str,'Z'));
```

Output

```
NULL
```

---

# Q31

```c
char str[]="Apple,Banana";

char *p=strtok(str,",");
```

After execution

Memory

```
Apple\0Banana
```

---

# Q32

```c
char str[]="ABC";

printf("%d\n",
strlen(str));
```

Output

```
3
```

---

# Q33

```c
char str[]="";

printf("%d\n",
strlen(str));
```

Output

```
0
```

---

# Q34

```c
char str[10];

strcpy(str,"Linux");

printf("%s\n",str);
```

Output

```
Linux
```

---

# Q35

```c
char str[5];

strcpy(str,"Linux");
```

Answer

```
Buffer Overflow

↓

Undefined Behavior
```

---

# Q36

```c
char str[]="Linux";

printf("%c\n",
str[strlen(str)]);
```

Output

```
'\0'
```

---

# Q37

```c
char str[]="ABC";

printf("%d\n",
str[3]);
```

Output

```
0
```

Because

```
str[3]

↓

'\0'
```

---

# Q38

```c
char *p=NULL;

printf("%s\n",p);
```

Answer

```
Undefined Behavior
```

---

# Q39

```c
char str[10];

printf("%lu\n",
sizeof(str));
```

Output

```
10
```

---

# Q40

```c
char str[]="ABC";

printf("%lu\n",
sizeof(str));
```

Output

```
4
```

---

# Q41

```c
char str[]="ABC";

printf("%lu\n",
strlen(str+1));
```

Output

```
2
```

---

# Q42

```c
char str[]="ABC";

printf("%s\n",
str+strlen(str));
```

Output

Empty line

Because pointer points to

```
'\0'
```

---

# Q43

```c
char str[]="ABCDE";

printf("%c\n",
*(str+strlen(str)));
```

Output

```
'\0'
```

---

# Q44

```c
char str[]="Embedded";

printf("%c\n",
*strstr(str,"bed"));
```

Output

```
b
```

---

# Q45

```c
char str[]="Qualcomm";

printf("%c\n",
*(strchr(str,'c')));
```

Output

```
c
```

---

# Q46

```c
char str[]="Apple";

printf("%c\n",
*(strrchr(str,'p')));
```

Output

```
p
```

(second `p`)

---

# Q47

```c
char str[]="abc";

printf("%d\n",
strcmp(str,"abc"));
```

Output

```
0
```

---

# Q48

```c
char *s1="Linux";
char *s2="Linux";

printf("%d\n", s1==s2);
```

Answer

```
Compiler Dependent
```

Many compilers share identical string literals, so it may print `1`, but **you must not rely on it**.

---

# Q49

```c
char str[]="Linux";

char *p=str;

printf("%c\n",*p++);
printf("%c\n",*p);
```

Output

```
L
i
```

---

# Q50

```c
char str[]="Hello";

printf("%s\n",
str+strlen(str)-2);
```

Output

```
lo
```

---

# Top Theory Questions

### Why is `strlen()` O(N)?

Because it scans the string until it finds `'\0'`.

---

### Why is `sizeof()` O(1)?

Because the compiler knows the size at compile time for arrays.

---

### Why doesn't `sizeof()` work like `strlen()`?

`sizeof()` measures memory occupied by the object.

`strlen()` counts characters until `'\0'`.

---

### Why is `strtok()` not thread-safe?

Because it uses **internal static state** to remember the next token.

For multithreaded code, use the reentrant version (`strtok_r()` on POSIX systems).

---

### Why does `argv` use `char **`?

Because it is a pointer to an array of character pointers (an array of strings).

---

# Rapid Revision Sheet

```
sizeof(array)

↓

Array Size

--------------------

sizeof(pointer)

↓

Pointer Size

--------------------

strlen()

↓

Character Count

--------------------

String Literal

↓

Read Only

--------------------

Character Array

↓

Writable

--------------------

strchr()

↓

First Character

--------------------

strrchr()

↓

Last Character

--------------------

strstr()

↓

Substring

--------------------

strtok()

↓

Split String

↓

Modifies Original

↓

Not Thread Safe

--------------------

strcmp()

↓

0

Equal

↓

<0

First Smaller

↓

>0

First Greater
```

---
