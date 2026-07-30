# Chapter 13 – File Handling (stdio + POSIX File APIs)
# Part 1 – FILE *, fopen(), fclose() & stdio Fundamentals

---

# Contents

1. Why File Handling is Important
2. What is a File?
3. File Types
4. Streams
5. What is FILE *?
6. stdin, stdout, stderr
7. fopen()
8. File Opening Modes
9. fclose()
10. Internal Structure of FILE
11. Complete Flow
12. Interview Questions
13. Best Practices
14. Key Takeaways

---

# 1. Why File Handling is Important

Almost every application interacts with files.

Examples

- Configuration files
- Log files
- Databases
- Images
- Videos
- Source code
- Firmware
- Device files
- Network sockets (treated similarly in Unix)

Linux interviews frequently ask

- FILE *
- fopen()
- File descriptors
- Buffering
- read() vs fread()

Understanding stdio is the foundation before learning POSIX file APIs.

---

# 2. What is a File?

A file is simply a sequence of bytes stored by the operating system.

```
Application

↓

File API

↓

Kernel

↓

Filesystem

↓

Disk
```

Example

```
hello.txt

↓

H

e

l

l

o

\n
```

The operating system does not understand "words" or "lines."

It only stores bytes.

---

# Everything is a File (Unix Philosophy)

Linux treats many resources as files.

Examples

```
Regular File

Document.txt

Character Device

/dev/tty

Block Device

/dev/sda

Pipe

FIFO

Socket

Network Communication
```

This uniform interface is one of Unix's biggest strengths.

---

# 3. File Types

Linux supports multiple file types.

| Type | Example |
|------|----------|
| Regular File | notes.txt |
| Directory | Documents/ |
| Character Device | /dev/tty |
| Block Device | /dev/sda |
| Symbolic Link | link.txt |
| FIFO (Named Pipe) | mkfifo |
| Socket | Network communication |

At the C stdio level, all regular files are typically accessed through `FILE *`.

---

# 4. Streams

The C Standard Library introduces the concept of a **stream**.

A stream is an abstraction that allows reading or writing data without worrying about the underlying device.

```
Program

↓

FILE *

↓

Stream

↓

Operating System

↓

Disk
```

The stream hides details such as buffering and system calls.

---

# Input Stream

```
Keyboard

↓

stdin

↓

Program
```

---

# Output Stream

```
Program

↓

stdout

↓

Terminal
```

---

# File Stream

```
Disk File

↓

FILE *

↓

Program
```

---

# 5. What is FILE *?

One of the most asked interview questions.

Example

```c
FILE *fp;
```

Many beginners think

```
FILE

=

Actual File
```

Wrong.

`FILE` is a library-defined structure used by the C runtime.

`FILE *` points to that structure.

The structure stores information such as

- Buffer
- Current file position
- Error status
- EOF status
- Underlying file descriptor (implementation-specific)

---

Think of it as

```
Application

↓

FILE *

↓

Runtime Information

↓

Kernel File Descriptor

↓

Actual File
```

---

Example

```c
FILE *fp = fopen("test.txt", "r");
```

Memory

```
fp

↓

+----------------------+

FILE Structure

Buffer

Position

Flags

File Descriptor

+----------------------+

↓

Kernel

↓

Disk File
```

---

# 6. Standard Streams

Every C program automatically starts with three open streams.

| Stream | Purpose |
|---------|----------|
| stdin | Standard Input |
| stdout | Standard Output |
| stderr | Standard Error |

---

stdin

Usually

```
Keyboard
```

Example

```c
scanf("%d", &x);
```

Actually reads from

```
stdin
```

---

stdout

Usually

```
Terminal
```

Example

```c
printf("Hello");
```

Writes to

```
stdout
```

---

stderr

Used for error messages.

Example

```c
fprintf(stderr, "File Error\n");
```

Unlike `stdout`, `stderr` is commonly unbuffered when connected to a terminal, making error messages appear immediately.

---

# Standard Stream Diagram

```
Keyboard

↓

stdin

↓

Program

↓

stdout

↓

Terminal

Program

↓

stderr

↓

Error Output
```

---

# 7. fopen()

Prototype

```c
#include <stdio.h>

FILE *fopen(const char *filename,
            const char *mode);
```

Returns

```
FILE *

↓

Success
```

or

```
NULL

↓

Failure
```

---

Example

```c
FILE *fp = fopen("data.txt", "r");

if(fp == NULL)
{
    printf("Open Failed\n");
}
```

Always check for `NULL`.

---

# 8. File Opening Modes

## Read

```c
"r"
```

Requirements

- File must exist.

Position

```
Beginning
```

---

## Write

```c
"w"
```

Behavior

- Creates file if it doesn't exist.
- Truncates existing file to zero length.

---

## Append

```c
"a"
```

Behavior

- Creates file if needed.
- Writes always occur at the end of the file.

---

## Read + Write

```c
"r+"
```

- File must exist.
- Reading and writing allowed.

---

## Write + Read

```c
"w+"
```

- Creates file if needed.
- Truncates existing file.

---

## Append + Read

```c
"a+"
```

- Read anywhere.
- All writes occur at the end of the file.

---

# Binary Modes

Examples

```
rb

wb

ab

rb+

wb+
```

On Linux,

text mode and binary mode behave the same.

On Windows,

binary mode prevents newline translation.

---

# Summary

| Mode | Read | Write | Create | Truncate |
|------|------|-------|---------|-----------|
| r | ✓ | ✗ | ✗ | ✗ |
| w | ✗ | ✓ | ✓ | ✓ |
| a | ✗ | ✓ | ✓ | ✗ |
| r+ | ✓ | ✓ | ✗ | ✗ |
| w+ | ✓ | ✓ | ✓ | ✓ |
| a+ | ✓ | ✓ | ✓ | ✗ |

---

# 9. fclose()

Prototype

```c
int fclose(FILE *stream);
```

Purpose

- Flush buffered output
- Close the underlying file
- Release associated resources

---

Example

```c
FILE *fp = fopen("test.txt", "r");

if(fp)
{
    fclose(fp);
}
```

Return

```
0

↓

Success
```

Non-zero

↓

Error.

---

Important

After

```c
fclose(fp);
```

the pointer becomes invalid for file operations.

Good practice

```c
fclose(fp);

fp = NULL;
```

---

# 10. Internal Structure of FILE

The exact implementation differs across C libraries.

Conceptually

```
FILE

+----------------------+

Buffer

Current Position

EOF Flag

Error Flag

File Descriptor

Buffering State

+----------------------+
```

Applications should **never** access these members directly.

Always use the standard library functions.

---

# 11. Complete Flow

Opening a File

```
Application

↓

fopen()

↓

C Library

↓

open()

↓

Kernel

↓

Filesystem

↓

Disk

↓

Return FILE *
```

Closing

```
fclose()

↓

Flush Buffer

↓

close()

↓

Kernel

↓

Release Resources
```

---

# 12. Frequently Asked Interview Questions

---

## Q1

What is `FILE *`?

A pointer to a C library stream object that manages buffered file I/O.

---

## Q2

Is `FILE *` the same as a file descriptor?

No.

`FILE *`

- C library abstraction
- Buffered

File descriptor

- Kernel integer handle
- Unbuffered by default

---

## Q3

What does `fopen()` return on failure?

```
NULL
```

---

## Q4

Difference between

```
r

w
```

`r`

Requires the file to exist.

`w`

Creates the file if needed and truncates it if it already exists.

---

## Q5

Difference between

```
w

a
```

`w`

Starts from an empty file.

`a`

Always appends to the end.

---

## Q6

Why call `fclose()`?

To flush buffers, close the file, and release resources.

---

## Q7

Can we use a `FILE *` after `fclose()`?

No.

Doing so results in **undefined behavior**.

---

# 13. Best Practices

✓ Always verify that `fopen()` succeeded.

✓ Always call `fclose()` exactly once for every successful `fopen()`.

✓ Set pointers to `NULL` after closing if they may be reused.

✓ Use binary mode (`rb`, `wb`) when handling binary data for portable code.

✓ Prefer `stderr` for error messages.

---

# Quick Revision Table

| Function | Purpose |
|----------|----------|
| `fopen()` | Open file |
| `fclose()` | Close file |
| `stdin` | Standard input |
| `stdout` | Standard output |
| `stderr` | Standard error |
| `FILE *` | Buffered stream object |

---

# Key Takeaways

- A file is treated as a sequence of bytes by the operating system.
- `FILE *` is a pointer to a C library stream object, not the actual file.
- `fopen()` creates a stream and returns a `FILE *` on success or `NULL` on failure.
- `fclose()` flushes buffers, closes the underlying file, and releases resources.
- The C standard library provides three standard streams: `stdin`, `stdout`, and `stderr`.
- Understanding `FILE *` is essential before learning `fread()`, `fwrite()`, buffering, and POSIX file APIs.

---

# Next Part

## **Part 2 – Reading & Writing Files (`fgetc`, `fgets`, `fputc`, `fputs`, `fprintf`, `fscanf`, `fread`, `fwrite`)**

We'll cover:

- Character I/O
- Line I/O
- Formatted I/O
- Binary I/O
- EOF handling
- Error handling (`feof`, `ferror`, `clearerr`)
- Text vs Binary files
- Common interview pitfalls
- -----------------------------------------------------------------
# Chapter 13 – File Handling (stdio + POSIX File APIs)
# Part 2 – Reading & Writing Files (Text & Binary I/O)

---

# Contents

1. Character I/O
2. Line I/O
3. Formatted I/O
4. Binary I/O
5. EOF Handling
6. Error Handling
7. Text vs Binary Files
8. Common Mistakes
9. Interview Questions
10. Best Practices
11. Key Takeaways

---

# 1. Character I/O

The simplest form of file I/O is reading and writing one character at a time.

Functions

```c
fgetc()

fputc()
```

---

## fgetc()

Prototype

```c
int fgetc(FILE *stream);
```

Reads

```
One Character
```

Returns

```
Character

or

EOF
```

Notice the return type is **int**, not `char`.

Reason

The function must be able to return every valid character value **and** the special value `EOF`.

---

Example

```c
FILE *fp = fopen("test.txt", "r");

int ch;

while((ch = fgetc(fp)) != EOF)
{
    putchar(ch);
}

fclose(fp);
```

Suppose file contains

```
Hello
```

Output

```
Hello
```

---

## Why int?

Wrong

```c
char ch;

while((ch = fgetc(fp)) != EOF)
{
}
```

`char` cannot reliably represent the special value `EOF`.

Always use

```c
int ch;
```

---

## fputc()

Prototype

```c
int fputc(int c, FILE *stream);
```

Writes one character.

Example

```c
FILE *fp = fopen("out.txt", "w");

fputc('A', fp);
fputc('\n', fp);

fclose(fp);
```

File

```
A
```

---

# Character I/O Flow

```
Program

↓

fgetc()

↓

Buffer

↓

Kernel

↓

Disk
```

---

# 2. Line I/O

Functions

```c
fgets()

fputs()
```

These operate on entire strings instead of single characters.

---

## fgets()

Prototype

```c
char *fgets(char *str,
            int size,
            FILE *stream);
```

Reads

- At most `size - 1` characters
- Stops at newline or EOF
- Always null-terminates if successful

---

Example

Suppose file

```
OpenAI

Linux

Kernel
```

Program

```c
char buffer[100];

while(fgets(buffer, sizeof(buffer), fp))
{
    printf("%s", buffer);
}
```

Output

```
OpenAI

Linux

Kernel
```

---

Memory

```
buffer

↓

+-------------------+

O p e n A I \n \0

+-------------------+
```

Notice

The newline is stored if there is room.

---

## fputs()

Prototype

```c
int fputs(const char *str,
          FILE *stream);
```

Example

```c
FILE *fp = fopen("data.txt", "w");

fputs("OpenAI\n", fp);

fputs("GPT\n", fp);

fclose(fp);
```

File

```
OpenAI

GPT
```

Unlike `puts()`, `fputs()` does **not** automatically append a newline.

---

# 3. Formatted I/O

Functions

```c
fprintf()

fscanf()
```

Very similar to

```c
printf()

scanf()
```

except they operate on files.

---

## fprintf()

Prototype

```c
int fprintf(FILE *stream,
            const char *format,
            ...);
```

Example

```c
FILE *fp = fopen("emp.txt", "w");

fprintf(fp,
        "%s %d\n",
        "Alice",
        25);

fclose(fp);
```

File

```
Alice 25
```

---

## fscanf()

Prototype

```c
int fscanf(FILE *stream,
           const char *format,
           ...);
```

Example

```c
char name[20];
int age;

FILE *fp = fopen("emp.txt", "r");

fscanf(fp,
       "%19s %d",
       name,
       &age);

printf("%s %d\n",
       name,
       age);

fclose(fp);
```

Output

```
Alice 25
```

Notice the width specifier `%19s`, which helps prevent buffer overflow.

---

# Formatted I/O Flow

```
Disk

↓

Buffer

↓

fprintf/fscanf

↓

Variables
```

---

# 4. Binary I/O

Functions

```c
fread()

fwrite()
```

These read/write raw bytes.

They are heavily used for

- Images
- Audio
- Databases
- Structures
- Firmware
- Binary protocols

---

## fread()

Prototype

```c
size_t fread(void *ptr,
             size_t size,
             size_t count,
             FILE *stream);
```

Meaning

```
Read

count

objects

each of

size

bytes
```

---

Example

```c
int arr[5];

FILE *fp = fopen("data.bin", "rb");

fread(arr,
      sizeof(int),
      5,
      fp);

fclose(fp);
```

---

## fwrite()

Prototype

```c
size_t fwrite(const void *ptr,
              size_t size,
              size_t count,
              FILE *stream);
```

Example

```c
int arr[5] =
{
    1,2,3,4,5
};

FILE *fp = fopen("data.bin", "wb");

fwrite(arr,
       sizeof(int),
       5,
       fp);

fclose(fp);
```

---

Memory

```
Array

↓

1

2

3

4

5

↓

Binary Bytes

↓

File
```

---

## Reading Structures

Example

```c
typedef struct
{
    int id;
    float salary;
} Employee;
```

Write

```c
Employee e =
{
    1,
    5000
};

fwrite(&e,
       sizeof(Employee),
       1,
       fp);
```

Read

```c
Employee e;

fread(&e,
      sizeof(Employee),
      1,
      fp);
```

Interview Note

Writing structures directly is fine for temporary files on the same platform, but it is **not portable** across different compilers, architectures, endianness, or structure packing rules.

---

# 5. EOF Handling

End Of File

```
EOF
```

is a special constant.

Most reading functions detect it.

Example

```c
int ch;

while((ch = fgetc(fp)) != EOF)
{
    putchar(ch);
}
```

Loop ends

when

```
End of File
```

is reached.

---

# feof()

Prototype

```c
int feof(FILE *stream);
```

Returns non-zero if the EOF indicator has been set.

Important

EOF is set **after** an attempt to read past the end of the file.

---

Wrong

```c
while(!feof(fp))
{
    fscanf(fp,"%d",&x);
}
```

Common interview mistake.

---

Correct

```c
while(fscanf(fp,"%d",&x) == 1)
{
}
```

Always check the return value of the input function.

---

# 6. Error Handling

---

## ferror()

Prototype

```c
int ferror(FILE *stream);
```

Checks

```
Read/Write Error
```

---

## clearerr()

Prototype

```c
void clearerr(FILE *stream);
```

Clears

- EOF flag
- Error flag

---

Example

```c
if(ferror(fp))
{
    printf("Read Error\n");
}
```

---

# 7. Text vs Binary Files

---

Text File

```
123

ABC

Hello
```

Readable by humans.

Opened using

```
r

w
```

---

Binary File

```
0x45

0xAB

0x11

0x9C
```

Not human readable.

Opened using

```
rb

wb
```

---

Comparison

| Text | Binary |
|------|---------|
| Human-readable | Raw bytes |
| Uses formatted I/O | Uses raw byte I/O |
| Newline translation may occur (platform-dependent) | No text translation |
| Good for logs/configs | Good for images/databases |

---

# 8. Common Mistakes

---

## Mistake 1

Using

```c
char
```

with

```c
fgetc()
```

Correct

```c
int ch;
```

---

## Mistake 2

Using

```c
while(!feof(fp))
```

Wrong.

Always check the return value of the read function.

---

## Mistake 3

Ignoring return values.

Wrong

```c
fread(arr,
      sizeof(int),
      5,
      fp);
```

Correct

```c
size_t n = fread(arr,
                 sizeof(int),
                 5,
                 fp);

if(n != 5)
{
    /* Handle partial read */
}
```

---

## Mistake 4

Using

```c
fwrite()
```

to store structures permanently.

Padding, alignment, and endianness may differ between systems.

---

# 9. Frequently Asked Interview Questions

---

## Q1

Difference between

```c
fgetc()

fgets()
```

`fgetc()`

Reads one character.

`fgets()`

Reads one line (up to a limit).

---

## Q2

Difference between

```c
fprintf()

fwrite()
```

`fprintf()`

Writes formatted text.

`fwrite()`

Writes raw bytes.

---

## Q3

Difference between

```c
fscanf()

fread()
```

`fscanf()`

Parses formatted text.

`fread()`

Reads binary data.

---

## Q4

Why does

```c
fgetc()

return

int
```

To represent all character values plus the special value `EOF`.

---

## Q5

Why is

```c
while(!feof(fp))
```

wrong?

Because the EOF indicator is set **only after** a read attempt reaches the end of the file.

---

## Q6

What does

```c
fread()
```

return?

The number of objects successfully read.

---

## Q7

Difference between

```
Text File

Binary File
```

Text files contain encoded characters.

Binary files contain raw bytes.

---

# 10. Best Practices

✓ Always check return values from input/output functions.

✓ Use `int` with `fgetc()`.

✓ Prefer `fgets()` over unsafe functions like `gets()` (removed from the C standard).

✓ Use width specifiers with `%s` in `fscanf()`.

✓ Open binary files using `rb` and `wb`.

✓ Check the number of objects returned by `fread()` and `fwrite()`.

---

# Quick Revision Table

| Function | Purpose |
|----------|----------|
| `fgetc()` | Read one character |
| `fputc()` | Write one character |
| `fgets()` | Read one line |
| `fputs()` | Write one string |
| `fprintf()` | Formatted output |
| `fscanf()` | Formatted input |
| `fread()` | Read binary data |
| `fwrite()` | Write binary data |
| `feof()` | Check EOF flag |
| `ferror()` | Check error flag |
| `clearerr()` | Clear EOF/error flags |

---

# Key Takeaways

- `fgetc()` and `fputc()` perform character-by-character I/O.
- `fgets()` and `fputs()` operate on strings and are safer than character loops for many text-processing tasks.
- `fprintf()` and `fscanf()` provide formatted file I/O similar to `printf()` and `scanf()`.
- `fread()` and `fwrite()` transfer raw binary data efficiently.
- Always check the return values of file I/O functions instead of relying on `feof()`.
- Binary serialization of structures is convenient but generally not portable across different platforms.

---

# Next Part

## **Part 3 – File Positioning, Buffering & stdio Internals**

We'll cover:

- `fseek()`
- `ftell()`
- `rewind()`
- `fflush()`
- `setbuf()`
- `setvbuf()`
- Line buffering vs full buffering vs no buffering
- How stdio buffers work internally
- `FILE *` internals
- 50+ interview questions
- ---------------------------------------------------------
