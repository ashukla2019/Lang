# C String Functions — Complete Interview Notes

This document covers the major C string and byte/memory functions from `<string.h>`, with:
- Purpose
- Syntax
- Usage examples
- Interview points
- Simple C implementations for learning

> **Important:** C strings are null-terminated character arrays. Most string functions require a valid `'\0'`-terminated string. Buffer size and overlap rules must be respected.

---

# 1. C String Basics

A C string is an array of characters terminated by `'\0'`.

```c
char str[] = "Hello";
```

Memory:

```text
H  e  l  l  o  \0
```

Equivalent character representation:

```c
char str[] = {'H', 'e', 'l', 'l', 'o', '\0'};
```

## String vs Character Array

```c
char a[] = "hello";              // C string
char b[] = {'h','e','l','l','o','\0'}; // C string
char c[] = {'h','e','l','l','o'};       // NOT a C string
```

Using string functions on `c` can cause undefined behavior because there is no terminating `'\0'`.

---

# 2. Header

Most standard C string functions are declared in:

```c
#include <string.h>
```

Common categories:

```text
String length
    strlen

String copy
    strcpy
    strncpy

String concatenation
    strcat
    strncat

String comparison
    strcmp
    strncmp
    strcoll
    strxfrm

Character search
    strchr
    strrchr

Substring/search
    strstr
    strpbrk
    strspn
    strcspn

Tokenization
    strtok
    strtok_r (POSIX, not ISO C)

String/error conversion
    strerror
    strerror_s (Annex K, optional/non-portable availability)

Byte/memory functions
    memcpy
    memmove
    memset
    memcmp
    memchr
```

---

# 3. `strlen()`

## Purpose

Returns the number of characters before the terminating `'\0'`.

## Syntax

```c
size_t strlen(const char *s);
```

## Usage

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "Hello";

    printf("%zu\n", strlen(str));   // 5
    return 0;
}
```

## Important

`strlen()` does NOT count `'\0'`.

```text
"Hello"

H e l l o \0
<--- 5 --->
```

## Implementation

```c
size_t my_strlen(const char *s)
{
    size_t len = 0;

    while (s[len] != '\0')
        len++;

    return len;
}
```

## Interview Point

Complexity:

```text
Time:  O(n)
Space: O(1)
```

`strlen()` has to scan the string because normal C strings do not store their length.

---

# 4. `strcpy()`

## Purpose

Copies a null-terminated string from source to destination, including `'\0'`.

## Syntax

```c
char *strcpy(char *dest, const char *src);
```

## Usage

```c
char src[] = "Hello";
char dest[20];

strcpy(dest, src);

printf("%s\n", dest);
```

## Important

Destination must have enough space.

```c
char dest[6];

strcpy(dest, "Hello");  // OK: 5 chars + '\0'
```

This is unsafe:

```c
char dest[5];

strcpy(dest, "Hello");  // BUFFER OVERFLOW
```

## Implementation

```c
char *my_strcpy(char *dest, const char *src)
{
    char *original = dest;

    while ((*dest++ = *src++) != '\0')
        ;

    return original;
}
```

## Interview Point

`strcpy()` performs no destination-size checking.

---

# 5. `strncpy()`

## Purpose

Copies at most `n` characters.

## Syntax

```c
char *strncpy(char *dest, const char *src, size_t n);
```

## Usage

```c
char dest[10];

strncpy(dest, "Hello", sizeof(dest));
```

## Critical Behavior

`strncpy()` does NOT always append `'\0'`.

```c
char dest[5];

strncpy(dest, "Hello", 5);

// dest contains:
// H e l l o
// No '\0'
```

Therefore:

```c
printf("%s", dest);
```

is unsafe because `dest` may not be a valid C string.

A common pattern:

```c
char dest[6];

strncpy(dest, "Hello", sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';
```

## Implementation

```c
char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];

    while (i < n)
        dest[i++] = '\0';

    return dest;
}
```

## Important Difference

```text
strcpy
    Copies until '\0', including '\0'.

strncpy
    Copies at most n bytes.
    If source is shorter, remaining destination bytes are zero-filled.
    If source length >= n, destination is NOT null-terminated.
```

---

# 6. `strcat()`

## Purpose

Appends one string to another.

## Syntax

```c
char *strcat(char *dest, const char *src);
```

## Usage

```c
char dest[20] = "Hello ";
char src[] = "World";

strcat(dest, src);

printf("%s\n", dest);
// Hello World
```

## Implementation

```c
char *my_strcat(char *dest, const char *src)
{
    char *original = dest;

    while (*dest != '\0')
        dest++;

    while ((*dest++ = *src++) != '\0')
        ;

    return original;
}
```

## Complexity

If destination already contains `n` characters and source contains `m`:

```text
O(n + m)
```

Repeated `strcat()` calls can therefore become O(n²).

---

# 7. `strncat()`

## Purpose

Appends at most `n` characters from source.

## Syntax

```c
char *strncat(char *dest, const char *src, size_t n);
```

## Usage

```c
char dest[20] = "Hello ";

strncat(dest, "World", 5);

printf("%s\n", dest);
```

## Important

Unlike `strncpy()`, `strncat()` appends a terminating `'\0'` after the copied characters, assuming sufficient destination space.

Destination must have enough room for:

```text
existing destination
+ up to n source characters
+ '\0'
```

## Implementation

```c
char *my_strncat(char *dest, const char *src, size_t n)
{
    char *original = dest;

    while (*dest != '\0')
        dest++;

    while (n > 0 && *src != '\0')
    {
        *dest++ = *src++;
        n--;
    }

    *dest = '\0';

    return original;
}
```

---

# 8. `strcmp()`

## Purpose

Lexicographically compares two strings.

## Syntax

```c
int strcmp(const char *s1, const char *s2);
```

## Return Value

```text
0       strings equal

< 0     s1 comes before s2

> 0     s1 comes after s2
```

Do NOT assume the return value is exactly `-1` or `1`.

## Usage

```c
if (strcmp("apple", "apple") == 0)
    printf("Equal\n");

if (strcmp("apple", "banana") < 0)
    printf("apple comes first\n");
```

## Implementation

```c
int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    return (unsigned char)*s1 - (unsigned char)*s2;
}
```

## Why `unsigned char`?

Character values may be signed or unsigned depending on implementation. Casting avoids incorrect ordering for characters with values above 127.

---

# 9. `strncmp()`

## Purpose

Compares at most `n` characters.

## Syntax

```c
int strncmp(const char *s1, const char *s2, size_t n);
```

## Usage

```c
if (strncmp("hello123", "hello456", 5) == 0)
    printf("First 5 characters equal\n");
```

## Implementation

```c
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n > 0)
    {
        unsigned char c1 = (unsigned char)*s1;
        unsigned char c2 = (unsigned char)*s2;

        if (c1 != c2)
            return c1 - c2;

        if (c1 == '\0')
            return 0;

        s1++;
        s2++;
        n--;
    }

    return 0;
}
```

---

# 10. `strchr()`

## Purpose

Finds the first occurrence of a character.

## Syntax

```c
char *strchr(const char *s, int c);
```

## Usage

```c
char str[] = "hello";

char *p = strchr(str, 'l');

if (p != NULL)
    printf("%s\n", p);
```

Output:

```text
llo
```

## Implementation

```c
char *my_strchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if ((unsigned char)*s == (unsigned char)c)
            return (char *)s;

        s++;
    }

    if ((unsigned char)c == '\0')
        return (char *)s;

    return NULL;
}
```

## Interview Point

`strchr()` returns a pointer to the matching character, not its index.

Index can be calculated:

```c
char *p = strchr(str, 'l');

if (p)
{
    size_t index = (size_t)(p - str);
}
```

---

# 11. `strrchr()`

## Purpose

Finds the last occurrence of a character.

## Syntax

```c
char *strrchr(const char *s, int c);
```

## Usage

```c
char str[] = "hello";

char *p = strrchr(str, 'l');

printf("%s\n", p);
// lo
```

## Implementation

```c
char *my_strrchr(const char *s, int c)
{
    const char *last = NULL;

    while (*s != '\0')
    {
        if ((unsigned char)*s == (unsigned char)c)
            last = s;

        s++;
    }

    if ((unsigned char)c == '\0')
        return (char *)s;

    return (char *)last;
}
```

---

# 12. `strstr()`

## Purpose

Finds the first occurrence of a substring.

## Syntax

```c
char *strstr(const char *haystack, const char *needle);
```

## Usage

```c
char *p = strstr("Hello World", "World");

if (p)
    printf("%s\n", p);
```

Output:

```text
World
```

## Simple Implementation

```c
char *my_strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0')
        return (char *)haystack;

    while (*haystack)
    {
        const char *h = haystack;
        const char *n = needle;

        while (*h && *n && *h == *n)
        {
            h++;
            n++;
        }

        if (*n == '\0')
            return (char *)haystack;

        haystack++;
    }

    return NULL;
}
```

## Complexity

Simple implementation:

```text
Worst case: O(n * m)
```

where:

```text
n = haystack length
m = needle length
```

More advanced substring algorithms include KMP and Boyer-Moore.

---

# 13. `strpbrk()`

## Purpose

Finds the first character in a string that matches any character from another string.

## Syntax

```c
char *strpbrk(const char *s, const char *accept);
```

## Usage

```c
char *p = strpbrk("hello123", "0123456789");

if (p)
    printf("%s\n", p);
// 123
```

## Implementation

```c
char *my_strpbrk(const char *s, const char *accept)
{
    while (*s)
    {
        const char *a = accept;

        while (*a)
        {
            if (*s == *a)
                return (char *)s;

            a++;
        }

        s++;
    }

    return NULL;
}
```

---

# 14. `strspn()`

## Purpose

Returns the length of the initial segment containing only characters from `accept`.

## Syntax

```c
size_t strspn(const char *s, const char *accept);
```

## Usage

```c
size_t n = strspn("12345abc", "0123456789");

printf("%zu\n", n);
// 5
```

## Implementation

```c
size_t my_strspn(const char *s, const char *accept)
{
    size_t count = 0;

    while (*s)
    {
        const char *a = accept;
        int found = 0;

        while (*a)
        {
            if (*s == *a)
            {
                found = 1;
                break;
            }

            a++;
        }

        if (!found)
            break;

        count++;
        s++;
    }

    return count;
}
```

---

# 15. `strcspn()`

## Purpose

Returns the length of the initial segment containing none of the characters from `reject`.

## Syntax

```c
size_t strcspn(const char *s, const char *reject);
```

## Usage

```c
size_t n = strcspn("hello,world", ",");

printf("%zu\n", n);
// 5
```

## Implementation

```c
size_t my_strcspn(const char *s, const char *reject)
{
    size_t count = 0;

    while (*s)
    {
        const char *r = reject;

        while (*r)
        {
            if (*s == *r)
                return count;

            r++;
        }

        s++;
        count++;
    }

    return count;
}
```

---

# 16. `strtok()`

## Purpose

Splits a string into tokens using delimiter characters.

## Syntax

```c
char *strtok(char *str, const char *delim);
```

## Usage

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "one,two,three";

    char *token = strtok(str, ",");

    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }

    return 0;
}
```

Output:

```text
one
two
three
```

## Critical Properties

`strtok()`:

- Modifies the input string.
- Replaces delimiters with `'\0'`.
- Maintains internal state.
- Is not thread-safe in the general sense.
- Cannot safely tokenize multiple strings concurrently using the same `strtok()` state.

## Conceptual Implementation

```c
char *my_strtok(char *str, const char *delim)
{
    static char *next;
    char *start;

    if (str != NULL)
        next = str;

    if (next == NULL)
        return NULL;

    while (*next)
    {
        const char *d = delim;
        int is_delim = 0;

        while (*d)
        {
            if (*next == *d)
            {
                is_delim = 1;
                break;
            }
            d++;
        }

        if (!is_delim)
            break;

        next++;
    }

    if (*next == '\0')
    {
        next = NULL;
        return NULL;
    }

    start = next;

    while (*next)
    {
        const char *d = delim;

        while (*d)
        {
            if (*next == *d)
            {
                *next = '\0';
                next++;
                return start;
            }
            d++;
        }

        next++;
    }

    next = NULL;
    return start;
}
```

> This is a learning implementation. The exact standard-library implementation can differ.

---

# 17. `strerror()`

## Purpose

Returns a human-readable description of an error number.

## Syntax

```c
char *strerror(int errnum);
```

## Usage

```c
#include <stdio.h>
#include <string.h>
#include <errno.h>

printf("%s\n", strerror(ENOENT));
```

Possible output:

```text
No such file or directory
```

## Important

The returned string is managed by the implementation and should not be freed by the caller.

For robust multithreaded POSIX code, `strerror_r()` may be used, noting that there are GNU and POSIX variants with different signatures.

---

# 18. `strcoll()`

## Purpose

Compares strings according to the current locale.

## Syntax

```c
int strcoll(const char *s1, const char *s2);
```

## Usage

```c
#include <locale.h>
#include <string.h>

setlocale(LC_COLLATE, "");

if (strcoll("abc", "abd") < 0)
    printf("s1 comes first\n");
```

## Difference from `strcmp()`

```text
strcmp()
    Usually compares byte values.

strcoll()
    Compares according to locale-specific collation rules.
```

---

# 19. `strxfrm()`

## Purpose

Transforms a string into a form suitable for locale-based comparison.

## Syntax

```c
size_t strxfrm(char *dest, const char *src, size_t n);
```

## Typical Use

Useful when comparing the same strings repeatedly with `strcoll()` semantics.

Conceptually:

```c
strxfrm(a, source_a, size);
strxfrm(b, source_b, size);

strcmp(a, b);
```

The transformed strings can be compared with `strcmp()` to obtain the ordering that `strcoll()` would use.

---

# 20. `memcpy()`

Although `memcpy()` is a memory/byte function rather than a string function, it is extremely important in C interviews.

## Purpose

Copies exactly `n` bytes.

## Syntax

```c
void *memcpy(void *dest, const void *src, size_t n);
```

## Usage

```c
char src[] = "Hello";
char dest[10];

memcpy(dest, src, sizeof(src));
```

## Important

`memcpy()` does NOT stop at `'\0'`.

It copies raw bytes.

## Overlap Rule

Source and destination **must not overlap**.

Overlapping regions result in undefined behavior.

Use `memmove()` when overlap is possible.

## Implementation

```c
void *my_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;

    while (n--)
        *d++ = *s++;

    return dest;
}
```

---

# 21. `memmove()`

## Purpose

Copies `n` bytes safely even when source and destination overlap.

## Syntax

```c
void *memmove(void *dest, const void *src, size_t n);
```

## Example

```c
char str[] = "abcdef";

memmove(str + 2, str, 4);

printf("%s\n", str);
```

## Implementation

If destination is before source:

```text
copy forward
```

If destination is after source:

```text
copy backward
```

```c
void *my_memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;

    if (d == s)
        return dest;

    if (d < s)
    {
        while (n--)
            *d++ = *s++;
    }
    else
    {
        d += n;
        s += n;

        while (n--)
            *--d = *--s;
    }

    return dest;
}
```

## Interview Difference

```text
memcpy
    Faster/simple byte copy
    Source and destination must not overlap

memmove
    Handles overlap safely
```

---

# 22. `memset()`

## Purpose

Sets `n` bytes to a specified byte value.

## Syntax

```c
void *memset(void *s, int c, size_t n);
```

## Usage

```c
char buffer[10];

memset(buffer, 0, sizeof(buffer));
```

## Implementation

```c
void *my_memset(void *s, int c, size_t n)
{
    unsigned char *p = s;

    while (n--)
        *p++ = (unsigned char)c;

    return s;
}
```

## Important Trap

This:

```c
int arr[10];

memset(arr, 1, sizeof(arr));
```

does NOT set every integer to `1`.

It sets every byte to `0x01`.

Typical result on a 32-bit `int`:

```text
0x01010101
```

For zero:

```c
memset(arr, 0, sizeof(arr));
```

is safe for setting integer bytes to zero.

---

# 23. `memcmp()`

## Purpose

Compares exactly `n` bytes.

## Syntax

```c
int memcmp(const void *s1, const void *s2, size_t n);
```

## Usage

```c
char a[] = "abc";
char b[] = "abc";

if (memcmp(a, b, 3) == 0)
    printf("Equal\n");
```

## Implementation

```c
int my_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *a = s1;
    const unsigned char *b = s2;

    while (n--)
    {
        if (*a != *b)
            return *a - *b;

        a++;
        b++;
    }

    return 0;
}
```

## Difference

```text
strcmp()
    Compares strings until '\0'.

memcmp()
    Compares exactly n bytes.
```

---

# 24. `memchr()`

## Purpose

Searches the first `n` bytes for a byte value.

## Syntax

```c
void *memchr(const void *s, int c, size_t n);
```

## Usage

```c
char data[] = "abcdef";

char *p = memchr(data, 'd', sizeof(data));

if (p)
    printf("%s\n", p);
```

## Implementation

```c
void *my_memchr(const void *s, int c, size_t n)
{
    const unsigned char *p = s;

    while (n--)
    {
        if (*p == (unsigned char)c)
            return (void *)p;

        p++;
    }

    return NULL;
}
```

---

# 25. `memset()` vs `strcpy()` vs `memcpy()`

| Function | Works on | Stops at `'\0'`? | Size parameter |
|---|---|---:|---:|
| `strcpy` | Strings | Yes | No |
| `strncpy` | Strings/bytes | Usually | Yes |
| `memcpy` | Raw bytes | No | Yes |
| `memmove` | Raw bytes | No | Yes |
| `memset` | Raw bytes | No | Yes |

---

# 26. `strcmp()` vs `memcmp()`

```text
strcmp("abc", "abc")
    Compares until '\0'

memcmp(a, b, n)
    Compares exactly n bytes
```

Example:

```c
char a[] = {'a', 'b', 'c', '\0', 'x'};
char b[] = {'a', 'b', 'c', '\0', 'y'};

strcmp(a, b);
```

Result:

```text
0
```

because both strings end at `'\0'`.

But:

```c
memcmp(a, b, sizeof(a));
```

detects the difference after the null byte.

---

# 27. `strchr()` vs `strrchr()`

```text
strchr()
    first occurrence

strrchr()
    last occurrence
```

Example:

```c
char *s = "hello";

strchr(s, 'l');   // first l
strrchr(s, 'l');  // last l
```

---

# 28. `strstr()` vs `strchr()`

```text
strchr()
    Searches for one character.

strstr()
    Searches for a substring.
```

Example:

```c
strchr("hello", 'l');

strstr("hello world", "world");
```

---

# 29. `strspn()` vs `strcspn()`

```text
strspn()
    Count initial characters FROM accepted set.

strcspn()
    Count initial characters NOT FROM rejected set.
```

Example:

```c
strspn("123abc", "0123456789");
// 3

strcspn("abc,def", ",");
// 3
```

---

# 30. `strcpy()` vs `strncpy()` — Important Interview Question

```text
strcpy:
    No length parameter.
    Copies until '\0'.
    Destination must be large enough.

strncpy:
    Has a maximum count.
    May not terminate with '\0'.
    May zero-fill destination.
```

A common misconception:

> "`strncpy()` is always a safer `strcpy()`."

Not necessarily. It prevents copying more than `n` bytes, but its null-termination behavior can still cause bugs.

---

# 31. `memcpy()` vs `memmove()` — Very Important

Suppose:

```text
src:  [A B C D]
        ↓
dest:    [      ]
```

No overlap:

```text
memcpy()  → OK
memmove() → OK
```

With overlap:

```text
[A B C D E]
  ↑
  destination overlaps source
```

Use:

```c
memmove();
```

because:

```text
memcpy()
    overlapping source/destination → undefined behavior

memmove()
    overlapping source/destination → supported
```

---

# 32. Complete Function Quick Reference

## Standard string functions

```text
strlen()
    String length

strcpy()
    Copy string

strncpy()
    Copy up to n characters

strcat()
    Concatenate string

strncat()
    Concatenate up to n characters

strcmp()
    Compare strings

strncmp()
    Compare up to n characters

strchr()
    Find first character

strrchr()
    Find last character

strstr()
    Find substring

strpbrk()
    Find first character belonging to a set

strspn()
    Length of initial accepted-character segment

strcspn()
    Length of initial rejected-character-free segment

strtok()
    Tokenize string

strcoll()
    Locale-aware string comparison

strxfrm()
    Transform string for locale-aware comparison

strerror()
    Convert error number to message
```

## Standard byte/memory functions

```text
memcpy()
    Copy bytes; no overlap allowed

memmove()
    Copy bytes; overlap allowed

memset()
    Fill bytes

memcmp()
    Compare bytes

memchr()
    Search bytes
```

---

# 33. POSIX Functions Commonly Asked in Linux Interviews

These are not all ISO C standard functions, but are commonly encountered in Linux/system-programming interviews.

## `strdup()`

Duplicates a string by allocating memory.

```c
char *p = strdup("hello");

if (p != NULL)
{
    printf("%s\n", p);
    free(p);
}
```

Conceptual implementation:

```c
char *my_strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char *p = malloc(len);

    if (p == NULL)
        return NULL;

    memcpy(p, s, len);

    return p;
}
```

Important:

```text
strdup()
    Allocates memory.

Caller must free the returned pointer.
```

---

# 34. `strndup()` — POSIX

Duplicates at most `n` characters and returns a null-terminated string.

```c
char *p = strndup("hello world", 5);

printf("%s\n", p);
// hello

free(p);
```

---

# 35. `strcasecmp()` — POSIX

Case-insensitive comparison.

```c
if (strcasecmp("Hello", "hello") == 0)
    printf("Equal\n");
```

Not part of ISO C.

---

# 36. `strncasecmp()` — POSIX

Case-insensitive comparison of at most `n` characters.

```c
strncasecmp("HELLO123", "hello456", 5);
```

First five characters compare equal.

---

# 37. `strtok_r()` — POSIX

Reentrant/thread-friendly variant of `strtok()`.

```c
char str[] = "one,two,three";
char *saveptr;

char *token = strtok_r(str, ",", &saveptr);

while (token != NULL)
{
    printf("%s\n", token);
    token = strtok_r(NULL, ",", &saveptr);
}
```

Main advantage:

```text
strtok()
    Internal state

strtok_r()
    Caller provides state
```

This allows multiple tokenization contexts.

---

# 38. Common String Bugs

## 1. Missing null terminator

```c
char buf[5];

strncpy(buf, "hello", sizeof(buf));

printf("%s", buf);  // unsafe
```

## 2. Buffer overflow

```c
char buf[5];

strcpy(buf, "hello world");  // overflow
```

## 3. String literal modification

```c
char *p = "hello";

p[0] = 'H';  // undefined behavior
```

Prefer:

```c
char p[] = "hello";

p[0] = 'H';  // valid
```

## 4. Using `sizeof` incorrectly

```c
char *p = malloc(100);

sizeof(p)
```

returns the size of the pointer, NOT 100.

---

# 39. String Literal vs Character Array

```c
char *p = "hello";
```

`p` points to a string literal. Do not modify it.

```c
char a[] = "hello";
```

`a` is a writable array initialized with the characters and `'\0'`.

```c
a[0] = 'H';   // valid
```

---

# 40. Important Interview Implementations to Memorize

For a senior C interview, be able to write these without looking them up:

```c
size_t strlen(const char *s);

char *strcpy(char *dest, const char *src);

char *strncpy(char *dest, const char *src, size_t n);

char *strcat(char *dest, const char *src);

char *strncat(char *dest, const char *src, size_t n);

int strcmp(const char *s1, const char *s2);

int strncmp(const char *s1, const char *s2, size_t n);

char *strchr(const char *s, int c);

char *strrchr(const char *s, int c);

char *strstr(const char *haystack, const char *needle);

void *memcpy(void *dest, const void *src, size_t n);

void *memmove(void *dest, const void *src, size_t n);

void *memset(void *s, int c, size_t n);

int memcmp(const void *s1, const void *s2, size_t n);

void *memchr(const void *s, int c, size_t n);
```

---

# 41. Senior Interview Questions

## Basic

1. What is a C string?
2. Why is `'\0'` required?
3. Difference between `strlen()` and `sizeof()`.
4. Difference between `strcpy()` and `memcpy()`.
5. Difference between `strcmp()` and `memcmp()`.
6. Difference between `strchr()` and `strstr()`.
7. Difference between `strcpy()` and `strncpy()`.
8. Difference between `memcpy()` and `memmove()`.

## Intermediate

9. Why can `strncpy()` be dangerous?
10. Why can `strcat()` be inefficient?
11. How would you implement `strlen()`?
12. Implement `strcpy()`.
13. Implement `strcmp()`.
14. Implement `strstr()`.
15. Implement `memcpy()`.
16. Implement `memmove()`.
17. Implement `memset()`.
18. Implement `strtok()`.

## Senior

19. How would you prevent buffer overflow in string handling?
20. Why does `memcpy()` have undefined behavior for overlapping regions?
21. How does `memmove()` handle overlapping regions?
22. How would you optimize repeated string concatenation?
23. How would you implement a high-performance substring search?
24. What is the complexity of `strlen()`?
25. Why can repeated `strcat()` become O(n²)?
26. Why should `strcmp()` implementations use unsigned character values?
27. What happens if a string is not null-terminated?
28. What are the security implications of `strcpy()`?
29. How would you safely copy a string into a fixed-size buffer?
30. Which string functions modify their input?
31. Is `strtok()` thread-safe?
32. What is the difference between `strtok()` and `strtok_r()`?
33. Which functions operate on strings and which operate on raw bytes?
34. What happens when `memset()` is used on an `int` array with value `1`?
35. Can `memcpy()` be used for copying structures?
36. What issues can arise when copying structures containing pointers?

---

# 42. Most Important Functions for Interviews

If you have limited time, prioritize:

```text
★★★★★  strlen
★★★★★  strcpy
★★★★★  strncpy
★★★★★  strcmp
★★★★★  strncmp
★★★★★  strcat
★★★★★  strchr
★★★★★  strstr

★★★★★  memcpy
★★★★★  memmove
★★★★★  memset
★★★★★  memcmp
★★★★★  memchr

★★★★☆  strtok
★★★★☆  strrchr
★★★★☆  strspn
★★★★☆  strcspn
★★★★☆  strpbrk

★★★☆☆  strcoll
★★★☆☆  strxfrm
★★★☆☆  strerror
```

For Linux/system interviews, additionally know:

```text
strdup
strndup
strcasecmp
strncasecmp
strtok_r
```

---

# 43. One-Page Mental Model

```text
                    C STRING FUNCTIONS
                           |
        +------------------+------------------+
        |                  |                  |
      Length             Copy              Concatenate
        |                  |                  |
     strlen          strcpy/strncpy       strcat/strncat
        |
        |
   +----+-----------------------------+
   |                                  |
 Compare                            Search
   |                                  |
strcmp/strncmp              +---------+---------+
                            |         |         |
                         strchr    strrchr    strstr
                            |
                         strpbrk
                         strspn
                         strcspn

                 BYTE / MEMORY FUNCTIONS
                           |
        +------------------+------------------+
        |                  |                  |
      Copy               Fill              Compare
        |                  |                  |
 memcpy / memmove       memset             memcmp
                                             |
                                           memchr
```

---

# 44. Final Interview Cheat Sheet

```text
strlen
    Count characters before '\0'.

strcpy
    Copy complete string including '\0'.

strncpy
    Copy at most n bytes; may not append '\0'.

strcat
    Append source to destination.

strncat
    Append at most n characters and terminate with '\0'
    if destination has sufficient space.

strcmp
    Compare strings until difference or '\0'.

strncmp
    Compare at most n characters.

strchr
    First occurrence of character.

strrchr
    Last occurrence of character.

strstr
    First occurrence of substring.

strpbrk
    First character matching any character in a set.

strspn
    Initial segment containing only accepted characters.

strcspn
    Initial segment containing none of rejected characters.

strtok
    Tokenize by delimiters; modifies input and maintains state.

strcoll
    Locale-aware comparison.

strxfrm
    Prepare string for locale-aware comparison.

strerror
    Error number → human-readable message.

memcpy
    Copy n bytes; overlap is not allowed.

memmove
    Copy n bytes; overlap is allowed.

memset
    Set n bytes to a byte value.

memcmp
    Compare n bytes.

memchr
    Search n bytes for a byte.
```

# 45. Golden Rules

```text
1. C strings must normally end with '\0'.

2. Always verify destination capacity before copying/concatenating.

3. strcpy() does not know destination size.

4. strncpy() does not guarantee null termination when source length >= n.

5. memcpy() does not handle overlapping memory.

6. memmove() handles overlapping memory.

7. memset() works byte-by-byte.

8. strlen() does not count '\0'.

9. sizeof(pointer) is not the allocated buffer size.

10. String literals must not be modified.

11. strcmp() returns <0, 0, or >0; do not rely on exact -1/+1.

12. strcmp() is string-oriented; memcmp() is byte-oriented.

13. strtok() modifies its input.

14. Always consider integer overflow, buffer size, and null pointers in production code.

15. For security-sensitive code, prefer APIs and patterns that make buffer sizes explicit and validate all lengths.
```
