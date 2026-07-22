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