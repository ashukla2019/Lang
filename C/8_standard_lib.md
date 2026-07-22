# C Interview Handbook
# Part 4 - C Standard Library

---

# Table of Contents

1. What is the C Standard Library?
2. stdio.h
3. stdlib.h
4. string.h
5. ctype.h
6. math.h
7. assert.h
8. errno.h
9. signal.h
10. time.h
11. Common Interview Programs
12. Interview Questions
13. Quick Revision

---

# 1. What is the C Standard Library?

The C Standard Library is a collection of pre-written functions that provide common functionality.

Instead of writing everything from scratch, we use library functions.

Examples

- Input/Output
- Memory Allocation
- String Manipulation
- Mathematical Functions
- Character Handling
- Error Handling
- Time Functions
- Signals

---

# Most Common Header Files

| Header | Purpose |
|---------|---------|
| stdio.h | Input / Output |
| stdlib.h | Memory, Conversion, Process Control |
| string.h | String Handling |
| ctype.h | Character Classification |
| math.h | Mathematical Functions |
| assert.h | Debug Assertions |
| errno.h | Error Reporting |
| signal.h | Signal Handling |
| time.h | Date & Time |

---

# 2. stdio.h

Provides input and output functions.

Common Functions

```c
printf()

scanf()

fprintf()

fscanf()

sprintf()

snprintf()

fgets()

fputs()

fgetc()

fputc()

perror()
```

---

## printf()

Print formatted output.

```c
printf("%d",10);
```

---

## scanf()

Read formatted input.

```c
scanf("%d",&x);
```

Always check its return value in production code.

---

## fgets()

Safely reads a line.

```c
char name[100];

fgets(name,sizeof(name),stdin);
```

Preferred over the removed `gets()` function.

---

## perror()

Prints a descriptive error message for the current value of `errno`.

```c
FILE *fp=fopen("abc.txt","r");

if(fp==NULL)
{
    perror("fopen");
}
```

Example output

```text
fopen: No such file or directory
```

---

# 3. stdlib.h

General-purpose utilities.

Common Functions

```c
malloc()

calloc()

realloc()

free()

exit()

abort()

atoi()

strtol()

qsort()

bsearch()

rand()

srand()
```

---

## atoi()

Converts string to integer.

```c
int x = atoi("123");
```

Note

`atoi()` provides little error reporting.

Prefer `strtol()` for robust code.

---

## strtol()

Converts a string to a long integer with error checking.

```c
char *end;

long value = strtol("123", &end, 10);
```

---

## qsort()

Sorts an array.

```c
qsort(arr,
      n,
      sizeof(int),
      compare);
```

Uses a callback function.

---

## bsearch()

Binary search on sorted arrays.

```c
bsearch(key,
        arr,
        n,
        sizeof(int),
        compare);
```

---

# 4. string.h

String manipulation.

Common Functions

```c
strlen()

strcpy()

strncpy()

strcat()

strncat()

strcmp()

strncmp()

strchr()

strstr()

memcpy()

memmove()

memset()

memcmp()
```

---

## strlen()

Returns string length (excluding the null terminator).

```c
strlen("Hello")
```

Returns

```text
5
```

---

## strcpy()

```c
strcpy(dest,src);
```

Copies a string.

Ensure the destination buffer is large enough.

---

## strncpy()

```c
strncpy(dest,src,n);
```

Copies up to `n` characters.

Be aware that it may not append a null terminator if the source is too long.

---

## strcmp()

```c
strcmp(a,b)
```

Returns

```text
<0

a<b

0

Equal

>0

a>b
```

---

## memcpy()

Copies bytes.

```c
memcpy(dest,src,size);
```

Source and destination must **not overlap**.

---

## memmove()

Copies bytes safely even when the regions overlap.

```c
memmove(dest,src,size);
```

---

## memset()

Initialize memory.

```c
memset(arr,0,sizeof(arr));
```

---

# 5. ctype.h

Character handling.

Functions

```c
isalpha()

isdigit()

isalnum()

islower()

isupper()

tolower()

toupper()

isspace()
```

Example

```c
if(isdigit(ch))
{
}
```

---

# 6. math.h

Mathematical functions.

Functions

```c
sqrt()

pow()

sin()

cos()

tan()

log()

exp()

fabs()

ceil()

floor()
```

Example

```c
double x = sqrt(25);
```

Returns

```text
5
```

Note

Some systems require linking with the math library (for example using `-lm` with GCC).

---

# 7. assert.h

Used during debugging.

```c
assert(pointer != NULL);
```

If the condition is false,

the program terminates with a diagnostic message.

Assertions are commonly disabled in release builds by defining `NDEBUG`.

---

# 8. errno.h

Provides the global error indicator `errno`.

Example

```c
FILE *fp=fopen("abc.txt","r");

if(fp==NULL)
{
    perror("fopen");
}
```

Some library functions set `errno` when an error occurs.

---

# 9. signal.h

Signal handling.

Register a signal handler.

```c
signal(SIGINT,handler);
```

Signals include

```text
SIGINT

SIGTERM

SIGABRT

SIGSEGV
```

Example

```c
void handler(int sig)
{
    printf("Signal %d\n",sig);
}
```

---

# 10. time.h

Date and time.

Common Functions

```c
time()

clock()

difftime()

localtime()

gmtime()

strftime()
```

Example

```c
time_t t = time(NULL);

printf("%ld",(long)t);
```

---

# 11. Common Interview Programs

## Reverse String

```c
char s[]="hello";
```

Use

```text
strlen()

Swap

Two Pointers
```

---

## Copy Memory

Use

```text
memcpy()

or

memmove()
```

depending on whether the regions overlap.

---

## Compare Strings

Use

```text
strcmp()
```

Never compare strings with

```c
==
```

---

## Sort Array

Use

```text
qsort()
```

---

## Binary Search

Use

```text
bsearch()
```

---

# 12. Frequently Asked Interview Questions

## Q1. Difference between

```text
memcpy()

and

memmove()
```

`memcpy()`

```
Faster

No overlap allowed
```

`memmove()`

```
Handles overlap safely
```

---

## Q2. Difference between

```text
strcpy()

and

strncpy()
```

`strcpy()`

Copies until the null terminator.

`strncpy()`

Copies up to `n` characters and may not null-terminate the destination.

---

## Q3. Why use `snprintf()`?

To avoid writing beyond the destination buffer.

---

## Q4. Why prefer `strtol()` over `atoi()`?

`strtol()` provides better error detection and reports where parsing stopped.

---

## Q5. Why use `assert()`?

To catch programming errors during development.

---

## Q6. Difference between `printf()` and `fprintf()`?

`printf()`

Writes to standard output.

`fprintf()`

Writes to a specified stream (such as a file).

---

# 13. Quick Revision

✓ `stdio.h` → Input/Output.

✓ `stdlib.h` → Memory, conversion, sorting.

✓ `string.h` → Strings and memory.

✓ `ctype.h` → Character functions.

✓ `math.h` → Mathematics.

✓ `assert.h` → Debug checks.

✓ `errno.h` → Error reporting.

✓ `signal.h` → Signals.

✓ `time.h` → Time functions.

✓ Prefer `memmove()` when memory regions overlap.

---

# Interview Memory Trick

```text
stdio

↓

Input / Output

stdlib

↓

Memory

Conversion

Sorting

string

↓

Strings

ctype

↓

Characters

math

↓

Math

assert

↓

Debug

errno

↓

Errors

signal

↓

Signals

time

↓

Time
```

---

# Next Part

**Part 5 - Frequently Asked C Interview Programs**

Topics

- String Programs
- Pointer Programs
- Array Programs
- Memory Programs
- Bit Manipulation
- Structures
- File Handling
- Dynamic Memory
- Pattern-Based Coding Questions
- Top 100 Interview Programs