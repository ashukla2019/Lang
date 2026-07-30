# Chapter 3 – Strings
# Part 1 – String Fundamentals

---

# What is a String?

A **string** is an array of characters terminated by a **null character (`'\0'`)**.

```c
char str[] = "Hello";
```

Memory Layout

```
Index :  0   1   2   3   4   5
        +---+---+---+---+---+----+
Value : | H | e | l | l | o | \0 |
        +---+---+---+---+---+----+
```

The null terminator marks the **end of the string**.

---

# Character vs String

| Character | String |
|-----------|--------|
| `'A'` | `"ABC"` |
| Type: `char` | Type: `char[]` or `char *` |
| Stores one character | Stores multiple characters followed by `'\0'` |

```c
char ch = 'A';
char str[] = "ABC";
```

Memory

```
ch
+---+
| A |
+---+

str
+---+---+---+----+
| A | B | C | \0 |
+---+---+---+----+
```

---

# Why is `'\0'` Needed?

String functions don't know the string length.

```c
char str[] = "Hello";

printf("%s", str);
```

`printf()` prints characters until it encounters `'\0'`.

Without it, the function continues reading memory, causing **undefined behavior**.

---

# Character Array

```c
char str[] = "Hello";
```

Compiler expands it to

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

The compiler **automatically appends the null terminator**.

---

# String Literal

```c
"Hello"
```

is called a **string literal**.

```c
char *p = "Hello";
```

Memory

```
Stack                  Read-Only Memory (.rodata)

+-----+                     +---+---+---+---+---+----+
|  p  | ------------------> | H | e | l | l | o | \0 |
+-----+                     +---+---+---+---+---+----+
```

String literals are **typically stored in read-only memory**.

---

# Character Array vs String Literal

## Character Array

```c
char str[] = "Hello";
```

- Own copy
- Writable

```c
str[0] = 'Y';      // OK
```

Output

```
Yello
```

---

## String Literal

```c
char *str = "Hello";
```

Points to read-only memory.

```c
str[0] = 'Y';      // Undefined Behavior
```

May cause a **segmentation fault**.

---

# Best Practice

Instead of

```c
char *str = "Hello";
```

prefer

```c
const char *str = "Hello";
```

This prevents accidental modification of string literals.

---

# `sizeof()` vs `strlen()`

```c
char str[] = "Hello";
```

| Expression | Result | Includes `'\0'`? |
|------------|-------:|-----------------|
| `sizeof(str)` | 6 | Yes |
| `strlen(str)` | 5 | No |

Example

```c
printf("%zu\n", sizeof(str)); // 6
printf("%zu\n", strlen(str)); // 5
```

> **Interview Tip:** `sizeof()` is evaluated at compile time for arrays, while `strlen()` scans the string at runtime (`O(N)`).

---

# Empty String

```c
char str[] = "";
```

Memory

```
+----+
| \0 |
+----+
```

| Expression | Result |
|------------|-------:|
| `strlen(str)` | 0 |
| `sizeof(str)` | 1 |

---

# String Without `'\0'`

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

```c
printf("%s", str);
```

**Undefined Behavior**

Reason: It is **not** a valid C string because it lacks the null terminator.

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

Array indexing is equivalent to pointer arithmetic.

```c
str[i] == *(str + i)
```

Example

```c
str[2]
```

is identical to

```c
*(str + 2)
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

Allowed because `str` is a writable character array.

---

# Common Interview Pitfalls

### Pitfall 1

```c
char *str = "Hello";

str[0] = 'Y';
```

❌ Undefined Behavior

---

### Pitfall 2

```c
char str[] = {'H','e','l','l','o'};
```

❌ Not a string (missing `'\0'`)

---

### Pitfall 3

```c
char str[] = "Hello";

printf("%zu\n", sizeof(str));
printf("%zu\n", strlen(str));
```

Output

```
6
5
```

---

### Pitfall 4

```c
char str[20] = "Hello";

sizeof(str)
```

Output

```
20
```

`sizeof()` returns the **array size**, not the string length.

---

# Complexity Summary

| Operation | Complexity |
|-----------|------------|
| `sizeof(array)` | O(1) |
| `strlen()` | O(N) |
| Character access (`str[i]`) | O(1) |

---

# Key Interview Takeaways

- A C string is a **null-terminated character array**.
- `'\0'` marks the end of every valid C string.
- `char str[] = "Hello";` creates a **writable copy**.
- `char *str = "Hello";` points to a **read-only string literal**.
- Prefer `const char *` for string literals.
- `sizeof()` measures the array size (including `'\0'`), while `strlen()` counts characters before `'\0'`.
- `str[i]` is equivalent to `*(str + i)`.
- Forgetting the null terminator results in **undefined behavior**.

---

## Quick Revision

| Concept | Remember |
|----------|----------|
| String | Character array ending with `'\0'` |
| Character Array | Writable |
| String Literal | Read-only (typically) |
| `sizeof()` | Array size (includes `'\0'`) |
| `strlen()` | String length (excludes `'\0'`) |
| `str[i]` | `*(str + i)` |
| Missing `'\0'` | Undefined Behavior |
-----------------------------------------------------------------
# Chapter 3 – Strings
# Part 2 – Core String Functions (`strlen()`, `strcpy()`, `strncpy()`, `memcpy()`)

---

# Standard Header

```c
#include <string.h>
```

---

# `strlen()`

Returns the number of characters **before** the null terminator.

```c
size_t strlen(const char *str);
```

Example

```c
char str[] = "Hello";

printf("%zu\n", strlen(str));
```

Output

```
5
```

---

# How `strlen()` Works

```c
size_t my_strlen(const char *str)
{
    size_t len = 0;

    while (*str++)
        len++;

    return len;
}
```

Memory

```
H -> e -> l -> l -> o -> '\0'
                       ↑
                     Stop
```

### Complexity

| Time | Space |
|------|------|
| O(N) | O(1) |

---

# Common Interview Mistake

❌ Bad

```c
for (int i = 0; i < strlen(str); i++)
{
    printf("%c\n", str[i]);
}
```

Every iteration recalculates the length.

Complexity

```
O(N²)
```

---

✅ Better

```c
size_t len = strlen(str);

for (size_t i = 0; i < len; i++)
{
    printf("%c\n", str[i]);
}
```

Complexity

```
O(N)
```

---

# `strcpy()`

Copies an entire string (including `'\0'`).

```c
char *strcpy(char *dest, const char *src);
```

Example

```c
char src[] = "Linux";
char dest[20];

strcpy(dest, src);
```

Memory

```
Before

dest
+ ? ? ? ? ? +

After

dest
+ L i n u x \0 +
```

---

# Simplified Implementation

```c
char *my_strcpy(char *dest, const char *src)
{
    char *start = dest;

    while ((*dest++ = *src++) != '\0');

    return start;
}
```

---

# Important Rule

Destination **must have enough space**.

✅ Correct

```c
char dest[20];

strcpy(dest, "Linux");
```

❌ Wrong

```c
char dest[5];

strcpy(dest, "Linux");
```

Need

```
L i n u x \0

↓

6 bytes
```

Result

```
Buffer Overflow
```

---

# Buffer Overflow

```c
char name[5];

strcpy(name, "Robert");
```

Memory

```
+---+---+---+---+---+
| R | o | b | e | r |
+---+---+---+---+---+
          ↓
 Continues Writing
```

Possible results

- Crash
- Memory corruption
- Security vulnerability

---

# `strncpy()`

Copies **at most** `n` characters.

```c
char *strncpy(char *dest,
              const char *src,
              size_t n);
```

Example

```c
char src[] = "Linux";
char dest[10];

strncpy(dest, src, 3);
```

Memory

```
dest

L i n ? ? ? ...
```

---

# Important Difference

| `strcpy()` | `strncpy()` |
|------------|-------------|
| Copies entire string | Copies at most `n` characters |
| Always copies `'\0'` | May not copy `'\0'` |
| Faster for normal strings | Used for bounded copy |

---

# Common Pitfall

```c
char src[] = "Hello";
char dest[6];

strncpy(dest, src, 5);

printf("%s\n", dest);
```

❌ Undefined Behavior

Reason

```
No '\0' copied
```

Memory

```
H e l l o ?
```

---

# Safe Usage

```c
char dest[6];

strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';
```

Now the string is always null-terminated.

---

# `memcpy()`

Copies **raw memory**, not strings.

```c
void *memcpy(void *dest,
             const void *src,
             size_t n);
```

Example

```c
char src[] = "Hello";
char dest[10];

memcpy(dest, src, strlen(src) + 1);
```

---

# `memcpy()` vs `strcpy()`

| `memcpy()` | `strcpy()` |
|------------|------------|
| Copies bytes | Copies string |
| Doesn't stop at `'\0'` | Stops after copying `'\0'` |
| Can copy any data | Only strings |
| Requires byte count | No length argument |

---

Example

```c
int a[] = {1,2,3};
int b[3];

memcpy(b, a, sizeof(a));
```

This cannot be done using `strcpy()`.

---

# `memcpy()` Caveat

`memcpy()` **does not** append a null terminator.

```c
char src[] = "Hello";
char dest[10];

memcpy(dest, src, 5);

printf("%s\n", dest);
```

❌ Undefined Behavior

Need

```c
memcpy(dest, src, 6);
```

or

```c
memcpy(dest, src, strlen(src) + 1);
```

---

# `memcpy()` vs `memmove()`

| `memcpy()` | `memmove()` |
|------------|-------------|
| Faster | Slightly slower |
| Source/Destination must not overlap | Safe for overlapping memory |
| Undefined behavior if overlap | Handles overlap correctly |

Example

```c
char str[] = "abcdef";

memmove(str + 2, str, 4);
```

Safe because source and destination overlap.

---

# Interview Comparison

| Function | Purpose | Complexity | Common Pitfall |
|----------|----------|------------|----------------|
| `strlen()` | Find length | O(N) | Calling repeatedly inside loops |
| `strcpy()` | Copy string | O(N) | Buffer overflow |
| `strncpy()` | Limited copy | O(N) | Missing `'\0'` |
| `memcpy()` | Copy bytes | O(N) | Doesn't treat data as strings |
| `memmove()` | Copy overlapping memory | O(N) | Slightly slower than `memcpy()` |

---

# Common Interview Questions

### Q1. Why is `strlen()` O(N)?

It scans characters until it finds `'\0'`.

---

### Q2. Why is `strcpy()` unsafe?

It performs **no bounds checking** on the destination buffer.

---

### Q3. Why can `strncpy()` still be unsafe?

It **does not guarantee null termination** when the source length is greater than or equal to `n`.

---

### Q4. When should `memcpy()` be preferred?

When copying **raw memory** (arrays, structures, binary data), not null-terminated strings.

---

### Q5. When should `memmove()` be used?

When the source and destination **overlap**.

---

# Key Interview Takeaways

- `strlen()` counts characters until `'\0'`.
- Never call `strlen()` repeatedly inside a loop.
- `strcpy()` copies the entire string including `'\0'`.
- `strcpy()` performs **no** boundary checking.
- `strncpy()` limits copied characters but may not append `'\0'`.
- `memcpy()` copies raw bytes and requires the byte count.
- `memmove()` is the safe choice for overlapping memory regions.
- Buffer overflow is one of the most common causes of security vulnerabilities in C.

---

## Quick Revision

| Function | Use |
|----------|-----|
| `strlen()` | String length |
| `strcpy()` | Copy string |
| `strncpy()` | Bounded string copy |
| `memcpy()` | Copy raw memory |
| `memmove()` | Copy overlapping memory |
| `strlen()` Complexity | O(N) |
| `strcpy()` Safety | No bounds checking |
| `strncpy()` Pitfall | May not append `'\0'` |
--------------------------------------------------------------------
# Chapter 3 – Strings
# Part 3 – Concatenation & Comparison (`strcat()`, `strncat()`, `strcmp()`, `strncmp()`, `memcmp()`)

---

# String Concatenation

Concatenation means **appending one string to another**.

```
"Hello" + " World"
        ↓
"Hello World"
```

---

# `strcat()`

Appends the source string to the destination string.

```c
char *strcat(char *dest, const char *src);
```

Example

```c
char str[20] = "Hello";

strcat(str, " World");

printf("%s\n", str);
```

Output

```
Hello World
```

---

# How `strcat()` Works

1. Find the `'\0'` in the destination.
2. Copy the source (including `'\0'`).

```
Before

H e l l o \0

Append

W o r l d \0

↓

After

H e l l o   W o r l d \0
```

---

# Simplified Implementation

```c
char *my_strcat(char *dest, const char *src)
{
    char *start = dest;

    while (*dest)
        dest++;

    while ((*dest++ = *src++) != '\0');

    return start;
}
```

---

# Important Rule

Destination must have enough space.

✅ Correct

```c
char str[20] = "Hello";

strcat(str, " World");
```

❌ Wrong

```c
char str[6] = "Hello";

strcat(str, "World");
```

Result

```
Buffer Overflow
```

---

# `strncat()`

Appends **at most** `n` characters.

```c
char *strncat(char *dest,
              const char *src,
              size_t n);
```

Example

```c
char str[20] = "Hello";

strncat(str, " World", 3);

printf("%s\n", str);
```

Output

```
Hello Wo
```

---

# `strcat()` vs `strncat()`

| `strcat()` | `strncat()` |
|------------|-------------|
| Appends entire string | Appends at most `n` characters |
| No length limit | Length limited |
| Requires enough buffer | Still requires enough buffer |

> **Note:** `strncat()` appends a null terminator if sufficient space exists.

---

# Why Can't We Use `==`?

```c
char s1[] = "ABC";
char s2[] = "ABC";

if (s1 == s2)
```

This compares **addresses**, not contents.

---

# `strcmp()`

Compares two strings lexicographically.

```c
int strcmp(const char *s1,
           const char *s2);
```

---

# Return Value

| Result | Meaning |
|---------|---------|
| `0` | Strings are equal |
| `< 0` | `s1` is smaller |
| `> 0` | `s1` is greater |

---

# Examples

```c
strcmp("ABC", "ABC");
```

Returns

```
0
```

---

```c
strcmp("ABC", "ABD");
```

Returns

```
Negative
```

---

```c
strcmp("ABD", "ABC");
```

Returns

```
Positive
```

---

# Internal Working

```c
int my_strcmp(const char *s1,
              const char *s2)
{
    while (*s1 == *s2)
    {
        if (*s1 == '\0')
            return 0;

        s1++;
        s2++;
    }

    return *s1 - *s2;
}
```

---

# ASCII Ordering

`strcmp()` compares **ASCII values**.

```
'A' = 65
'a' = 97
```

Example

```c
strcmp("Apple", "apple");
```

Result

```
Negative
```

because

```
'A' < 'a'
```

---

# `strncmp()`

Compares only the first `n` characters.

```c
int strncmp(const char *s1,
            const char *s2,
            size_t n);
```

Example

```c
strncmp("abcdef",
        "abcxyz",
        3);
```

Returns

```
0
```

because only `"abc"` is compared.

---

# `strcmp()` vs `strncmp()`

| `strcmp()` | `strncmp()` |
|------------|-------------|
| Compare entire string | Compare first `n` characters |
| Stops at `'\0'` or mismatch | Stops after `n` characters or mismatch |
| Full comparison | Prefix comparison |

---

# `memcmp()`

Compares **raw memory**, not strings.

```c
int memcmp(const void *p1,
           const void *p2,
           size_t n);
```

Example

```c
char a[] = {'A','B','C'};
char b[] = {'A','B','D'};

memcmp(a, b, 3);
```

Returns

```
Negative
```

---

# `memcmp()` vs `strcmp()`

| `memcmp()` | `strcmp()` |
|-------------|------------|
| Compares raw bytes | Compares strings |
| Requires byte count | Stops at `'\0'` |
| Works with binary data | Works only with strings |

Example

```c
int a[] = {1,2,3};
int b[] = {1,2,3};

memcmp(a, b, sizeof(a));
```

Cannot be done using `strcmp()`.

---

# Complexity

| Function | Complexity |
|----------|------------|
| `strcat()` | O(N + M) |
| `strncat()` | O(N + M) |
| `strcmp()` | O(N) |
| `strncmp()` | O(min(N, n)) |
| `memcmp()` | O(N) |

---

# Common Interview Questions

### Q1. Why is `strcat()` O(N + M)?

It first scans the destination to find `'\0'`, then copies the source.

---

### Q2. Why shouldn't strings be compared with `==`?

Because `==` compares **addresses**, not string contents.

---

### Q3. Should we check for `strcmp() == 1`?

❌ No.

Correct

```c
if (strcmp(a, b) > 0)
```

Only the **sign** of the return value is guaranteed.

---

### Q4. When should `memcmp()` be used?

For comparing **binary data**, structures, arrays, or memory blocks.

---

### Q5. Which is faster: `memcmp()` or `strcmp()`?

Neither is universally faster.

- `strcmp()` stops at `'\0'`.
- `memcmp()` always compares exactly `n` bytes.

---

# Key Interview Takeaways

- `strcat()` appends one string to another.
- Destination buffer must have enough space.
- `strncat()` limits the number of appended characters.
- Never compare strings using `==`.
- `strcmp()` returns **negative, zero, or positive**—never rely on exact values like `-1` or `1`.
- `strncmp()` is useful for prefix comparisons.
- `memcmp()` compares raw memory and is commonly used for binary data.

---

-----------------------------------------------------------------------
