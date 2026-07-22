# C Interview Handbook
# Part 5A - Strings Fundamentals

---

# Table of Contents

1. What is a String?
2. Character vs String
3. Null Character ('\0')
4. String Memory Layout
5. String Declaration & Initialization
6. String Input & Output
7. String Literal vs Character Array
8. Array of Strings
9. Common Mistakes
10. Interview Questions
11. Quick Revision

---

# 1. What is a String?

A string is a sequence of characters terminated by a special character called the **null character**.

```text
H
e
l
l
o
\0
```

Unlike some other languages, **C does not have a built-in string data type**.

A string is simply an array of characters.

Example

```c
char str[] = "Hello";
```

---

# 2. Character vs String

Character

```c
char ch = 'A';
```

Memory

```text
+-----+
|  A  |
+-----+
```

Size

```text
1 Byte
```

---

String

```c
char str[] = "A";
```

Memory

```text
+-----+-----+
|  A  | \0  |
+-----+-----+
```

Size

```text
2 Bytes
```

---

Difference

| Character | String |
|-----------|---------|
| Single character | Multiple characters |
| Uses single quotes | Uses double quotes |
| No null terminator | Ends with '\0' |

---

# 3. Null Character ('\0')

The null character marks the end of a string.

ASCII value

```text
0
```

Example

```c
char str[] = "ABC";
```

Memory

```text
Index

0   1   2   3

+---+---+---+----+
| A | B | C | \0 |
+---+---+---+----+
```

Without `'\0'`, library functions don't know where the string ends.

---

# 4. String Memory Layout

Example

```c
char str[] = "OpenAI";
```

Memory

```text
Index

0 1 2 3 4 5 6

+--+--+--+--+--+--+----+
|O |p |e |n |A |I |\0  |
+--+--+--+--+--+--+----+
```

Size

```text
7 Bytes
```

---

# 5. String Declaration

Method 1

```c
char str[] = "Hello";
```

Compiler automatically adds `'\0'`.

---

Method 2

```c
char str[] = {'H','e','l','l','o','\0'};
```

Exactly equivalent to Method 1.

---

Method 3

```c
char str[20] = "Hello";
```

Memory

```text
H e l l o \0 ? ? ? ...
```

Only the required characters are initialized.

The remaining elements are zero-initialized because the array has an initializer.

---

Method 4

```c
char str[6];

strcpy(str, "Hello");
```

Used when the array already exists.

---

# 6. String Input

## scanf()

```c
char str[50];

scanf("%49s", str);
```

Input

```text
Hello World
```

Stored

```text
Hello
```

Stops at the first whitespace.

---

## fgets()

Preferred for reading a line.

```c
char str[50];

fgets(str, sizeof(str), stdin);
```

Input

```text
Hello World
```

Stored

```text
Hello World
```

`fgets()` also stores the newline (`'\n'`) if there is room before the null terminator.

---

# 7. String Output

Using printf()

```c
printf("%s", str);
```

Example

```c
char str[] = "Linux";

printf("%s", str);
```

Output

```text
Linux
```

---

Print Character by Character

```c
for (int i = 0; str[i] != '\0'; i++)
{
    printf("%c", str[i]);
}
```

---

# 8. String Literal vs Character Array

Example 1

```c
char str[] = "Hello";
```

Memory

```text
Stack

+---+---+---+---+---+----+
| H | e | l | l | o | \0 |
+---+---+---+---+---+----+
```

Characters are copied into the array.

Modification

```c
str[0] = 'Y';
```

Valid.

---

Example 2

```c
char *str = "Hello";
```

Pointer

```text
str

↓

"Hello"
```

The pointer points to a string literal.

Attempting to modify the string literal results in **undefined behavior**.

```c
str[0] = 'Y';
```

Do not do this.

---

Difference

| char str[] | char *str |
|------------|-----------|
| Array | Pointer |
| Own copy of characters | Points to string literal |
| Can modify contents | Do not modify contents |
| Size known at compile time | Pointer size only |

---

# 9. Array of Strings

Example

```c
char fruits[3][10] =
{
    "Apple",
    "Mango",
    "Orange"
};
```

Memory

```text
+----------+
| Apple    |
+----------+
| Mango    |
+----------+
| Orange   |
+----------+
```

Access

```c
printf("%s", fruits[1]);
```

Output

```text
Mango
```

---

# 10. Traversing a String

Using Index

```c
for (int i = 0; str[i] != '\0'; i++)
{
    printf("%c ", str[i]);
}
```

---

Using Pointer

```c
char *p = str;

while (*p)
{
    printf("%c ", *p);
    p++;
}
```

---

# 11. Common Mistakes

## Mistake 1

```c
char str[5] = "Hello";
```

Wrong.

Need space for `'\0'`.

Correct

```c
char str[6] = "Hello";
```

---

## Mistake 2

```c
char *str = "Hello";

str[0] = 'Y';
```

Undefined behavior.

---

## Mistake 3

```c
gets(str);
```

Never use `gets()`.

It was removed from the C standard because it cannot prevent buffer overflows.

Use

```c
fgets()
```

instead.

---

## Mistake 4

```c
scanf("%s", str);
```

Without a field width, this can overflow the buffer.

Safer

```c
scanf("%49s", str);
```

for a `char str[50];`.

---

# 12. Frequently Asked Interview Questions

### Q1. Does C have a string data type?

No.

Strings are character arrays terminated by `'\0'`.

---

### Q2. Why is `'\0'` necessary?

It marks the end of the string so library functions know where to stop.

---

### Q3. Difference between

```c
char str[] = "Hello";
```

and

```c
char *str = "Hello";
```

The first creates an array.

The second creates a pointer to a string literal.

---

### Q4. Why prefer `fgets()` over `scanf("%s")`?

`fgets()` can read spaces and allows you to specify the buffer size.

---

### Q5. Why was `gets()` removed?

Because it cannot prevent buffer overflow.

---

# 13. Quick Revision

✓ String = Character array + `'\0'`

✓ Characters use single quotes.

✓ Strings use double quotes.

✓ `printf("%s")` prints a string.

✓ `scanf("%Ns")` limits input length.

✓ `fgets()` is safer for line input.

✓ `char str[]` creates a writable array.

✓ `char *str = "Hello"` points to a string literal.

✓ Never modify a string literal.

✓ Never use `gets()`.

---

# Interview Memory Trick

```text
String

↓

Characters

+

'\0'

Array

↓

Writable

Pointer

↓

String Literal

scanf()

↓

Stops at Space

fgets()

↓

Reads Entire Line
```

---

# Next Part

**Part 5B – C String Library Functions**

Topics

- strlen()
- strcpy()
- strncpy()
- strcat()
- strncat()
- strcmp()
- strncmp()
- strchr()
- strrchr()
- strstr()
- strtok()
- memcpy()
- memmove()
- memset()
- memcmp()
  ---------------------------------------------------------------------------------
  # C Interview Handbook
# Part 1 - C Fundamentals

---

# Table of Contents

1. Introduction to C
2. Structure of a C Program
3. Compilation Process
4. Variables
5. Data Types
6. Constants
7. Operators
8. Type Conversion
9. Storage Classes
10. Scope & Lifetime
11. Keywords
12. Input & Output
13. Important Interview Questions
14. Quick Revision

---

# 1. Introduction to C

## What is C?

C is a

- Procedural Programming Language
- Middle-Level Language
- Compiled Language
- Fast
- Portable
- Efficient

It is widely used for

- Operating Systems
- Device Drivers
- Embedded Systems
- Networking
- Databases
- Compilers

Example

```c
#include <stdio.h>

int main()
{
    printf("Hello World\n");
    return 0;
}
```

---

# 2. Structure of a C Program

```text
+----------------------+
| Header Files         |
+----------------------+
| Global Variables     |
+----------------------+
| Function Declaration |
+----------------------+
| main()               |
+----------------------+
| User Functions       |
+----------------------+
```

Example

```c
#include <stdio.h>

// Global Variable
int x = 10;

// Function Declaration
void display();

int main()
{
    display();
    return 0;
}

void display()
{
    printf("%d\n", x);
}
```

---

# 3. Compilation Process

## Flow

```text
Source Code (.c)

↓

Preprocessor

↓

Compiler

↓

Assembler

↓

Object File (.o)

↓

Linker

↓

Executable
```

### Step 1 - Preprocessor

Processes

- #include
- #define
- #ifdef
- Macros

Output

```text
Expanded Source Code
```

---

### Step 2 - Compiler

Converts C code into Assembly.

Checks

- Syntax
- Type Errors

Output

```text
Assembly Code (.s)
```

---

### Step 3 - Assembler

Converts

```text
Assembly

↓

Machine Code
```

Output

```text
Object File (.o)
```

---

### Step 4 - Linker

Links

- Object files
- Libraries

Produces

```text
Executable
```

---

# Interview Question

Difference between Compiler and Linker?

Compiler

- Converts C → Assembly
- Detects syntax errors

Linker

- Combines object files
- Resolves function references

---

# 4. Variables

Variable is a named memory location.

Example

```c
int age = 20;
```

Memory

```text
Address      Value

1000         20
```

Variable

```text
age

↓

1000
```

---

## Variable Naming Rules

Allowed

```text
age
student1
total_marks
```

Not Allowed

```text
1age
total-marks
float
```

---

# 5. Data Types

## Integer

```c
int
short
long
long long
```

---

## Floating Point

```c
float
double
long double
```

---

## Character

```c
char
```

Stores

```text
One Character
```

Example

```c
char ch='A';
```

---

## Void

Represents

```text
No Value
```

Example

```c
void display();
```

---

# sizeof()

Returns memory occupied.

Example

```c
printf("%zu", sizeof(int));
```

Typical output

```text
4
```

---

# 6. Constants

## Literal

```c
10
3.14
'A'
"Hello"
```

---

## const

```c
const int MAX = 100;
```

Cannot modify later.

---

## #define

```c
#define PI 3.14159
```

No memory allocated.

Replaced during preprocessing.

---

Interview

Difference between const and #define?

const

- Has type
- Memory allocated
- Checked by compiler

#define

- Text replacement
- No type
- No memory

---

# 7. Operators

## Arithmetic

```text
+
-
*
/
%
```

---

## Relational

```text
<
>
<=
>=
==
!=
```

Returns

```text
0 or 1
```

---

## Logical

```text
&&
||
!
```

---

## Assignment

```text
=
+=
-=
*=
/=
```

---

## Increment

```text
++
--
```

Example

```c
int x = 5;

printf("%d", x++);
```

Output

```text
5
```

Now

```text
x = 6
```

---

Example

```c
int x=5;

printf("%d", ++x);
```

Output

```text
6
```

---

## Bitwise

```text
&
|
^
~
<<
>>
```

---

## Conditional Operator

```c
(condition) ? value1 : value2;
```

Example

```c
int max=(a>b)?a:b;
```

---

# 8. Type Conversion

## Implicit

Done automatically.

Example

```c
int x=10;

float y=x;
```

---

## Explicit

Done by programmer.

```c
float x=10.5;

int y=(int)x;
```

Output

```text
10
```

---

# 9. Storage Classes

## auto

Default local variable.

```c
void fun()
{
    auto int x=10;
}
```

---

## static

Value persists across function calls.

```c
void fun()
{
    static int count=0;

    count++;

    printf("%d",count);
}
```

Output

```text
1
2
3
```

---

## extern

Used to access global variables from another file.

```c
extern int total;
```

---

## register

Suggests storing variable in CPU register.

```c
register int i;
```

Compiler may ignore it.

---

# Interview Table

| Storage Class | Scope | Lifetime |
|---------------|-------|----------|
| auto | Local | Function |
| static(local) | Local | Entire Program |
| static(global) | File | Entire Program |
| extern | Global | Entire Program |
| register | Local | Function |

---

# 10. Scope and Lifetime

## Local Variable

Accessible only inside function.

```c
void fun()
{
    int x=10;
}
```

---

## Global Variable

Accessible everywhere after declaration.

```c
int x=100;
```

---

## Lifetime

Local

```text
Function starts

↓

Variable Created

↓

Function Ends

↓

Destroyed
```

Static

```text
Program Starts

↓

Variable Created

↓

Program Ends

↓

Destroyed
```

---

# 11. Important Keywords

```text
auto
break
case
char
const
continue
default
do
double
else
enum
extern
float
for
goto
if
inline
int
long
register
return
short
signed
sizeof
static
struct
switch
typedef
union
unsigned
void
volatile
while
```

---

# 12. Input & Output

## printf()

```c
printf("Age=%d", age);
```

---

## scanf()

```c
scanf("%d",&age);
```

Remember

```text
&
```

passes the variable's address so `scanf()` can modify it.

---

# Common Format Specifiers

| Type | Specifier |
|------|-----------|
| int | %d |
| char | %c |
| float | %f |
| double | %lf |
| string | %s |
| pointer | %p |

---

# 13. Frequently Asked Interview Questions

### Q1. Why is C called a middle-level language?

Because it supports

- High-level programming features
- Low-level memory access using pointers

---

### Q2. Difference between Compiler and Interpreter?

Compiler

- Converts entire program before execution.
- Faster execution.
- Generates executable.

Interpreter

- Executes line by line.
- Slower execution.
- No separate executable.

---

### Q3. Difference between const and #define?

See Section 6.

---

### Q4. Difference between ++i and i++?

`++i` (Pre-increment)
- Increment first.
- Then use the value.

`i++` (Post-increment)
- Use the current value.
- Increment afterward.

---

### Q5. Difference between local and global variables?

Local
- Declared inside a function.
- Limited scope.
- Exists only during the function call.

Global
- Declared outside functions.
- Visible according to scope rules.
- Exists for the entire program.

---

### Q6. What is sizeof()?

Returns the size (in bytes) of a type or object.

Example

```c
int a;
printf("%zu\n", sizeof(a));
```

---

### Q7. What is the default storage class?

`auto` for local variables.

---

# 14. Quick Revision

✓ C is procedural and compiled.

✓ Compilation flow

```text
.c
↓

Preprocessor

↓

Compiler

↓

Assembler

↓

Object

↓

Linker

↓

Executable
```

✓ Variable stores data in memory.

✓ `const` is typed and occupies storage; `#define` is a preprocessor text replacement.

✓ Learn all operators, especially increment/decrement and bitwise operators.

✓ Understand implicit vs explicit type conversion.

✓ Master storage classes: `auto`, `static`, `extern`, and `register`.

✓ Understand scope (where a name is visible) and lifetime (how long an object exists).

✓ Remember common `printf()` and `scanf()` format specifiers.

---

# Next Part

Part 2 - Memory Management

- Memory Layout
- Stack
- Heap
- malloc()
- calloc()
- realloc()
- free()
- Memory Leak
- Dangling Pointer
- Wild Pointer
- NULL Pointer
- Memory Corruption
- Best Practices
- -------------------------------------------------------------------
# C Interview Handbook
# Part 5C - String Algorithms

---

# Table of Contents

1. Reverse a String
2. Check Palindrome
3. Check Anagram
4. Character Frequency
5. Count Vowels & Consonants
6. Remove Duplicate Characters
7. Reverse Words in a String
8. Left & Right Rotation
9. Run-Length Encoding (RLE)
10. Pattern Searching Basics
11. Common Interview Questions
12. Quick Revision

---

# 1. Reverse a String

Problem

```text
Input

Hello

Output

olleH
```

Approach

Use two pointers.

```text
H e l l o
^       ^

Swap

↓

o e l l H

 ^     ^

Swap

↓

o l l e H
```

Code

```c
#include <string.h>

void reverse(char str[])
{
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right)
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;

        left++;
        right--;
    }
}
```

Complexity

```text
Time : O(n)

Space: O(1)
```

---

# 2. Check Palindrome

Problem

```text
madam

↓

Palindrome
```

Algorithm

Compare both ends.

```text
m a d a m
^       ^

↓

Equal

↓

Move inward
```

Code

```c
#include <string.h>

int isPalindrome(char str[])
{
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right)
    {
        if (str[left] != str[right])
            return 0;

        left++;
        right--;
    }

    return 1;
}
```

Complexity

```text
O(n)
```

---

# 3. Check Anagram

Definition

Two strings contain the same characters with the same frequencies.

Example

```text
listen

silent
```

Method

Count character frequencies.

Code

```c
int isAnagram(char a[], char b[])
{
    int freq[256] = {0};

    int i;

    for (i = 0; a[i]; i++)
        freq[(unsigned char)a[i]]++;

    for (i = 0; b[i]; i++)
        freq[(unsigned char)b[i]]--;

    for (i = 0; i < 256; i++)
    {
        if (freq[i] != 0)
            return 0;
    }

    return 1;
}
```

Complexity

```text
O(n)
```

---

# 4. Character Frequency

Problem

```text
banana
```

Output

```text
a = 3

b = 1

n = 2
```

Code

```c
int freq[256] = {0};

for (int i = 0; str[i]; i++)
{
    freq[(unsigned char)str[i]]++;
}
```

Applications

- Histogram
- Anagram
- Compression
- Parsing

---

# 5. Count Vowels & Consonants

Code

```c
int vowels = 0;
int consonants = 0;

for (int i = 0; str[i]; i++)
{
    char ch = str[i];

    if ((ch >= 'A' && ch <= 'Z') ||
        (ch >= 'a' && ch <= 'z'))
    {
        switch (ch)
        {
            case 'a': case 'e':
            case 'i': case 'o':
            case 'u':
            case 'A': case 'E':
            case 'I': case 'O':
            case 'U':
                vowels++;
                break;

            default:
                consonants++;
        }
    }
}
```

---

# 6. Remove Duplicate Characters

Problem

```text
programming
```

Output

```text
progamin
```

Method

Use a visited array.

Code

```c
int visited[256] = {0};

for (int i = 0; str[i]; i++)
{
    if (!visited[(unsigned char)str[i]])
    {
        putchar(str[i]);

        visited[(unsigned char)str[i]] = 1;
    }
}
```

Complexity

```text
O(n)
```

---

# 7. Reverse Words

Problem

```text
Hello Linux World
```

Output

```text
World Linux Hello
```

Method

1. Reverse entire string.
2. Reverse every word.

Example

```text
Hello Linux

↓

xuniL olleH

↓

Linux Hello
```

This is a common interview problem.

---

# 8. Rotate String

Left Rotation

```text
ABCDE

↓

BCDEA
```

Right Rotation

```text
ABCDE

↓

EABCD
```

One approach

1. Save characters.
2. Shift remaining characters.
3. Insert saved characters.

Time

```text
O(n)
```

---

# 9. Run-Length Encoding (RLE)

Compress consecutive repeated characters.

Input

```text
aaabbcccc
```

Output

```text
a3b2c4
```

Algorithm

```text
Count repeated characters

↓

Print character

↓

Print count

↓

Continue
```

Applications

- Compression
- Image formats
- Data encoding

---

# 10. Pattern Searching Basics

Problem

Find

```text
cat
```

inside

```text
The cat sat.
```

Naive Algorithm

Compare every possible starting position.

```text
abcdef

 ^

abc

↓

Move

abcdef

  ^

abc
```

Complexity

```text
O(n × m)
```

where

```text
n

↓

Text Length

m

↓

Pattern Length
```

Advanced algorithms

- KMP
- Rabin-Karp
- Boyer-Moore

These are typically covered in DSA.

---

# 11. Common Interview Questions

### Q1. Best way to reverse a string?

Two pointers.

---

### Q2. Best way to check palindrome?

Compare characters from both ends.

---

### Q3. Best way to check anagram?

Frequency array.

---

### Q4. Why use a frequency array of size 256?

To cover all possible byte values in an ASCII-compatible character set.

---

### Q5. What is Run-Length Encoding?

A simple compression technique that stores repeated characters as a character followed by its count.

---

### Q6. Complexity of reversing a string?

```text
O(n)
```

---

# 12. Quick Revision

✓ Reverse → Two pointers.

✓ Palindrome → Compare ends.

✓ Anagram → Frequency count.

✓ Character count → Frequency array.

✓ Remove duplicates → Visited array.

✓ Reverse words → Reverse whole string, then each word.

✓ Rotation → Shift characters.

✓ RLE → Character + Count.

✓ Pattern search → Compare each position.

---

# Interview Memory Trick

```text
Reverse

↓

Two Pointers

Palindrome

↓

Compare Ends

Anagram

↓

Frequency

Duplicates

↓

Visited Array

Words

↓

Reverse Twice

Compression

↓

RLE
```

---

# Coding Pattern Summary

| Problem | Best Technique | Time | Space |
|---------|----------------|------|-------|
| Reverse String | Two Pointers | O(n) | O(1) |
| Palindrome | Two Pointers | O(n) | O(1) |
| Anagram | Frequency Array | O(n) | O(1) |
| Character Count | Frequency Array | O(n) | O(1) |
| Remove Duplicates | Visited Array | O(n) | O(1) |
| Reverse Words | Reverse + Reverse Words | O(n) | O(1)\* |
| Rotate String | Shift/Reversal | O(n) | O(1) |
| RLE | Linear Scan | O(n) | O(1) |

\* Depending on the implementation.

---

# Next Part

**Part 5D – Advanced Strings & Memory**

Topics

- ASCII
- Unicode
- UTF-8 Basics
- String Literals
- const char *
- Dynamic Strings
- Buffer Overflow
- Safe String Handling
- Interview Pitfalls
- -------------------------------------------------------------------------------
# C Interview Handbook
# Part 5D - Advanced Strings & Memory

---

# Table of Contents

1. ASCII Character Set
2. Unicode
3. UTF-8 Encoding
4. String Literals
5. const char * vs char *
6. char[] vs char *
7. Dynamic Strings
8. Buffer Overflow
9. Safe String Handling
10. Common String Vulnerabilities
11. Linux & System Programming Examples
12. Interview Questions
13. Quick Revision

---

# 1. ASCII Character Set

ASCII (American Standard Code for Information Interchange) is a 7-bit character encoding standard.

Range

```text
0 - 127
```

Examples

| Character | ASCII Value |
|-----------|------------:|
| A | 65 |
| Z | 90 |
| a | 97 |
| z | 122 |
| 0 | 48 |
| 9 | 57 |
| Space | 32 |
| '\n' | 10 |
| '\0' | 0 |

Example

```c
char ch = 'A';

printf("%d\n", ch);
```

Output

```text
65
```

---

# 2. Unicode

ASCII supports only 128 characters.

Unicode supports characters from almost every language.

Examples

```text
English

Hello

Hindi

नमस्ते

Japanese

こんにちは

Emoji

😊
```

Unicode is a **character set**, not an encoding.

---

# 3. UTF-8 Encoding

UTF-8 is the most common encoding for Unicode.

Properties

- Variable length
- Backward compatible with ASCII
- Uses 1–4 bytes per character

Examples

```text
A

↓

1 Byte

₹

↓

3 Bytes

😊

↓

4 Bytes
```

Why interviewers ask

Many bugs occur because **characters** and **bytes** are different concepts in UTF-8.

---

# 4. String Literals

Example

```c
char *str = "Linux";
```

Memory

```text
Pointer

↓

+------------------+
| L i n u x \0     |
+------------------+
```

String literals typically reside in read-only memory.

Attempting to modify them causes **undefined behavior**.

Wrong

```c
str[0] = 'W';
```

---

# 5. const char * vs char *

Preferred

```c
const char *name = "Linux";
```

Meaning

```text
Characters

↓

Read Only
```

Not allowed

```c
name[0] = 'W';
```

---

Normal Pointer

```c
char *ptr;
```

Means

Pointer may point to writable or read-only memory depending on what it references.

The type alone does not guarantee writability.

---

# 6. char[] vs char *

Array

```c
char str[] = "Linux";
```

Memory

```text
Stack

L i n u x \0
```

Characters are copied into the array.

Can modify

```c
str[0] = 'W';
```

---

Pointer

```c
char *str = "Linux";
```

Memory

```text
Pointer

↓

String Literal
```

Do not modify.

---

Comparison

| char[] | char * |
|----------|---------|
| Own memory | Pointer only |
| Writable | Depends on what it points to |
| Array size known | Pointer size only |

---

# 7. Dynamic Strings

Allocate memory at runtime.

Example

```c
#include <stdlib.h>

char *str = malloc(50);

if (str == NULL)
{
    return;
}
```

Use

```c
strcpy(str, "Linux");
```

Release memory

```c
free(str);
```

Always free dynamically allocated memory.

---

# 8. Buffer Overflow

Most common C programming bug.

Example

```c
char name[5];

strcpy(name, "Programming");
```

Memory

```text
+-----+
|name |
+-----+

↓

Overflow
```

Effects

- Crash
- Corrupted data
- Security vulnerabilities
- Arbitrary code execution

---

# 9. Safe String Handling

Prefer

```c
fgets()
```

instead of

```c
gets()
```

---

Prefer

```c
snprintf()
```

instead of

```c
sprintf()
```

---

When copying

- Ensure destination is large enough.
- Verify null termination.
- Check function return values when appropriate.

---

# 10. Common String Vulnerabilities

## Buffer Overflow

Writing past array bounds.

---

## Missing Null Terminator

Example

```c
char str[5];

strncpy(str, "Hello", 5);
```

No guaranteed

```text
'\0'
```

---

## Dangling Pointer

Example

```c
char *ptr = malloc(20);

free(ptr);

/* ptr still holds the old address */
```

The pointer is dangling after `free()`.

Good practice

```c
ptr = NULL;
```

---

## Memory Leak

Example

```c
char *p = malloc(100);

/* Forgot free(p); */
```

Memory remains allocated until program termination.

---

# 11. Linux & System Programming Examples

Read one line

```c
char buffer[128];

if (fgets(buffer,
          sizeof(buffer),
          stdin) != NULL)
{
    printf("%s", buffer);
}
```

---

Read file

```c
FILE *fp = fopen("data.txt", "r");

char line[100];

while (fgets(line,
             sizeof(line),
             fp))
{
    printf("%s", line);
}

fclose(fp);
```

---

Copy packet data

```c
memcpy(destination,
       source,
       packetSize);
```

Use `memmove()` instead if the source and destination regions overlap.

---

Clear packet buffer

```c
memset(buffer,
       0,
       sizeof(buffer));
```

Common in networking and embedded systems.

---

# 12. Frequently Asked Interview Questions

### Q1. Difference between ASCII and Unicode?

ASCII

```text
128 characters
```

Unicode

```text
Supports almost all languages
```

---

### Q2. Difference between Unicode and UTF-8?

Unicode defines characters.

UTF-8 defines how those characters are encoded into bytes.

---

### Q3. Why use `const char *`?

To prevent accidental modification of read-only character data.

---

### Q4. Why is `gets()` dangerous?

It cannot limit input size and may cause buffer overflows.

---

### Q5. Why prefer `snprintf()`?

It limits the number of bytes written, helping prevent buffer overflows.

---

### Q6. Why is UTF-8 widely used?

It is compact for ASCII text and supports the full Unicode character set.

---

# 13. Quick Revision

✓ ASCII → 128 characters.

✓ Unicode → Character set.

✓ UTF-8 → Encoding.

✓ String literals are typically read-only.

✓ Prefer `const char *` for string literals.

✓ `char[]` stores its own copy.

✓ `malloc()` allocates memory.

✓ `free()` releases memory.

✓ Avoid buffer overflows.

✓ Use `fgets()` instead of `gets()`.

✓ Use `snprintf()` instead of `sprintf()`.

---

# Interview Memory Trick

```text
ASCII

↓

128 Characters

Unicode

↓

Character Set

UTF-8

↓

Encoding

char[]

↓

Own Memory

char *

↓

Pointer

malloc()

↓

Allocate

free()

↓

Release

Overflow

↓

Most Dangerous Bug
```

---

# Common Interview Pitfalls

| Problem | Correct Solution |
|---------|------------------|
| Reading a line | `fgets()` |
| Formatting into a buffer | `snprintf()` |
| Copying overlapping memory | `memmove()` |
| Copying strings | Ensure destination is large enough |
| String literal | Treat as read-only |
| Dynamic memory | Always `free()` when done |

---

# Next Part

**Part 5E – String Interview Problems**

Topics

- 50+ Most Asked String Problems
- MAANG Patterns
- Linux & Embedded Examples
- Memory-Based Questions
- Optimization Techniques
- Complete Coding Solutions
