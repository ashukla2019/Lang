# C Input/Output Functions
# gets(), puts(), getchar(), putchar(), fgets(), fputs(), scanf(), printf()

---

# Table of Contents

1. Introduction
2. Character Input/Output
3. String Input/Output
4. Formatted Input/Output
5. File Input/Output
6. Function Comparison
7. Interview Questions
8. Summary

---

# 1. Introduction

C provides several input/output functions.

These can be divided into four categories.

```
Input

↓

Character Input
String Input
Formatted Input
File Input
```

```
Output

↓

Character Output
String Output
Formatted Output
File Output
```

---

# Character I/O

## getchar()

Reads **one character** from standard input (keyboard).

Prototype

```c
int getchar(void);
```

Example

```c
#include <stdio.h>

int main()
{
    char ch;

    printf("Enter a character: ");

    ch = getchar();

    printf("You entered: %c", ch);

    return 0;
}
```

Input

```
A
```

Output

```
You entered: A
```

---

### Why does getchar() return int?

Prototype

```c
int getchar(void);
```

It returns an **int** instead of **char** because it must also return

```
EOF
```

which is usually

```
-1
```

Correct usage

```c
int ch;

while((ch = getchar()) != EOF)
{
    putchar(ch);
}
```

---

## putchar()

Writes one character to standard output.

Prototype

```c
int putchar(int ch);
```

Example

```c
putchar('A');
```

Output

```
A
```

Example

```c
char ch='X';

putchar(ch);
```

Output

```
X
```

---

# String I/O

## gets()  ❌ (Deprecated)

Prototype

```c
char *gets(char *str);
```

Example

```c
char name[20];

gets(name);
```

Problem

```
No boundary checking
```

Input

```
ABCDEFGHIJKLMNOPQRSTUVWXYZ
```

If array size is only

```
20
```

Memory overflow occurs.

Because of this,

```
gets()

↓

Removed from C11
```

Never use it.

---

## puts()

Writes a string to standard output.

Prototype

```c
int puts(const char *str);
```

Example

```c
char name[]="Programming";

puts(name);
```

Output

```
Programming
```

Difference from printf()

```c
puts(name);
```

prints

```
Programming

```

Notice

```
puts()

↓

Automatically prints '\n'
```

Equivalent

```c
printf("%s\n",name);
```

---

## fgets()

Safely reads a string.

Prototype

```c
char *fgets(char *str,int size,FILE *stream);
```

Example

```c
char name[20];

fgets(name,sizeof(name),stdin);

puts(name);
```

Input

```
John Smith
```

Output

```
John Smith
```

Unlike

```c
scanf("%s")
```

it reads spaces.

---

Memory

```
Input

John Smith

↓

Array

J o h n ' ' S m i t h \n \0
```

Notice

```
fgets()

↓

Stores newline

'\n'

if space permits.
```

Removing newline

```c
name[strcspn(name,"\n")] = '\0';
```

---

## fputs()

Writes string to file or stdout.

Prototype

```c
int fputs(const char *str,FILE *stream);
```

Example

```c
fputs("Hello",stdout);
```

Output

```
Hello
```

Unlike puts(),

```
No automatic newline.
```

---

# Formatted I/O

## scanf()

Reads formatted input.

Prototype

```c
int scanf(const char *format,...);
```

Example

```c
int age;

scanf("%d",&age);
```

Input

```
25
```

Output

```
age = 25
```

Reads according to format specifier.

---

## printf()

Formatted output.

Prototype

```c
int printf(const char *format,...);
```

Example

```c
printf("Age=%d",25);
```

Output

```
Age=25
```

---

# File Character I/O

## fgetc()

Reads one character from file.

Prototype

```c
int fgetc(FILE *fp);
```

Example

```c
FILE *fp=fopen("a.txt","r");

int ch;

while((ch=fgetc(fp))!=EOF)
{
    putchar(ch);
}
```

---

## fputc()

Writes one character.

Prototype

```c
int fputc(int ch,FILE *fp);
```

Example

```c
fputc('A',stdout);
```

Output

```
A
```

---

# File String I/O

## fgets()

Reading from file

```c
FILE *fp=fopen("a.txt","r");

char str[100];

fgets(str,100,fp);
```

---

## fputs()

Writing to file

```c
FILE *fp=fopen("a.txt","w");

fputs("Hello",fp);

fclose(fp);
```

---

# Comparison

## getchar() vs scanf("%c")

| getchar() | scanf("%c") |
|------------|-------------|
| Reads one character | Reads one character |
| Simpler | Formatted input |
| Returns int | Returns number of items read |

---

## puts() vs printf()

| puts() | printf() |
|---------|----------|
| String only | Any format |
| Adds newline automatically | Does not |
| Simpler | More flexible |

---

## gets() vs fgets()

| gets() | fgets() |
|---------|----------|
| Unsafe | Safe |
| No size checking | Size specified |
| Removed from C11 | Recommended |
| Can overflow | Prevents overflow |

---

## puts() vs fputs()

| puts() | fputs() |
|---------|----------|
| Appends newline | Does not |
| stdout only | Any FILE* |
| Simpler | More flexible |

---

## getchar() vs fgetc()

| getchar() | fgetc() |
|------------|----------|
| Reads from stdin | Reads from any file |
| No arguments | Requires FILE* |

---

## putchar() vs fputc()

| putchar() | fputc() |
|------------|----------|
| Writes to stdout | Writes to any file |

---

# Which Function Should You Use?

| Requirement | Function |
|-------------|----------|
| Read one character | getchar() |
| Print one character | putchar() |
| Read one word | scanf("%s") |
| Read one line safely | fgets() |
| Print string with newline | puts() |
| Print string without newline | fputs() |
| Read character from file | fgetc() |
| Write character to file | fputc() |
| Read formatted input | scanf() |
| Print formatted output | printf() |

---

# Interview Questions

### Why was gets() removed?

Because it performs **no bounds checking**. If the user enters more characters than the buffer can hold, it causes **buffer overflow**, leading to undefined behavior and security vulnerabilities.

---

### Why is fgets() safer?

It requires the buffer size:

```c
fgets(buffer, sizeof(buffer), stdin);
```

This prevents writing past the end of the array.

---

### Why does puts() print a newline?

The C standard defines `puts()` to write the string followed by a newline character (`'\n'`).

---

### Why does fgets() store '\n'?

If there is room in the buffer and the input line ends with a newline, `fgets()` stores it before appending the null terminator.

---

### Why does getchar() return int?

To represent **all possible character values** plus the special value `EOF`.

---

### Which functions return EOF?

- `getchar()`
- `fgetc()`

They return `EOF` when the end of input is reached or on a read error.

---

# Summary

| Function | Purpose | Safe | Reads Spaces | Adds Newline |
|----------|---------|------|--------------|--------------|
| getchar() | Read one character | ✅ | Yes | No |
| putchar() | Print one character | ✅ | N/A | No |
| gets() | Read a line | ❌ | Yes | N/A |
| puts() | Print a string | ✅ | N/A | **Yes** |
| fgets() | Read a line | ✅ | Yes | Stores `'\n'` if present |
| fputs() | Print a string | ✅ | N/A | **No** |
| scanf() | Formatted input | ✅* | Depends on format | No |
| printf() | Formatted output | ✅ | N/A | No |
| fgetc() | Read one character from a file | ✅ | Yes | No |
| fputc() | Write one character to a file | ✅ | N/A | No |

> **Note:** `scanf()` is safe only when used carefully. For example, use a field width for strings (`%19s` for a 20-byte buffer) to avoid buffer overflows.

---

# Key Takeaways

- Use **`getchar()`** and **`putchar()`** for single-character I/O.
- Use **`fgets()`** instead of **`gets()`** for reading lines safely.
- Use **`puts()`** when you want to print a string followed by a newline.
- Use **`fputs()`** when writing a string to a file or when you do not want an automatic newline.
- Use **`scanf()`** and **`printf()`** for formatted input and output.
- Use **`fgetc()`** and **`fputc()`** when working with character I/O on files.