# Advanced C Interview Coding Solutions - Part 1

## Implementing C Standard Library Functions

Topics covered:

1. strlen()
2. strcpy()
3. memcpy()
4. memmove()

---

# 1. Implement strlen()

## Problem

Implement the string length function without using the C library.

Function prototype:

```c
size_t my_strlen(const char *str);
```

## Requirements

- Count characters until `'\0'`
- Do not modify input string
- Handle empty string
- Time Complexity: O(n)
- Space Complexity: O(1)

---

## Implementation

```c
#include <stddef.h>

size_t my_strlen(const char *str)
{
    const char *ptr = str;

    while (*ptr != '\0')
    {
        ptr++;
    }

    return (size_t)(ptr - str);
}
```

---

## Explanation

Example:

```
str = "hello"

Memory:

Address

1000  h
1001  e
1002  l
1003  l
1004  o
1005  \0


str = 1000

ptr moves until '\0'

ptr - str = 5
```

---

## Test Code

```c
#include <stdio.h>

int main()
{
    char str[] = "hello";

    printf("Length = %zu\n", my_strlen(str));

    return 0;
}
```

Output:

```
Length = 5
```

---

## Edge Cases

### Empty string

```c
char str[] = "";

my_strlen(str);
```

Output:

```
0
```

### NULL pointer

```c
my_strlen(NULL);
```

Result:

Undefined behavior.

A production API may add:

```c
if(str == NULL)
    return 0;
```

depending on design requirements.

---

# 2. Implement strcpy()

## Problem

Copy source string into destination.

Function prototype:

```c
char *my_strcpy(char *dest, const char *src);
```

---

## Requirements

- Copy all characters
- Include terminating '\0'
- Return destination pointer
- Time Complexity: O(n)
- Space Complexity: O(1)

---

## Implementation

```c
char *my_strcpy(char *dest, const char *src)
{
    char *original_dest = dest;

    while((*dest++ = *src++) != '\0')
    {
        ;
    }

    return original_dest;
}
```

---

## Explanation

For:

```
src = "abc"
```

Memory copy:

```
a -> a
b -> b
c -> c
\0 -> \0
```

The expression:

```c
*dest++ = *src++
```

does:

1. Copy character
2. Increment destination pointer
3. Increment source pointer

---

## Test Code

```c
#include <stdio.h>

int main()
{
    char src[] = "hello";
    char dest[20];

    my_strcpy(dest, src);

    printf("%s\n", dest);

    return 0;
}
```

Output:

```
hello
```

---

## Important Interview Points

### strcpy() does not check destination size

Wrong:

```c
char buffer[5];

my_strcpy(buffer, "hello");
```

Required:

```c
char buffer[6];
```

because:

```
h e l l o \0
```

---

### strcpy() does not support overlap

Example:

```
source and destination overlap
```

Use:

```
memmove()
```

instead.

---

# 3. Implement memcpy()

## Problem

Copy raw memory bytes.

Function prototype:

```c
void *my_memcpy(void *dest,
                const void *src,
                size_t n);
```

---

## Difference from strcpy()

| strcpy | memcpy |
|-|-|
| String only | Any memory |
| Stops at '\0' | Copies exact bytes |
| Character based | Byte based |

---

## Implementation

```c
#include <stddef.h>

void *my_memcpy(void *dest,
                const void *src,
                size_t n)
{
    unsigned char *d = (unsigned char *)dest;

    const unsigned char *s =
        (const unsigned char *)src;


    while(n--)
    {
        *d++ = *s++;
    }

    return dest;
}
```

---

## Why unsigned char?

C guarantees:

```c
sizeof(char) == 1
```

`unsigned char` can access any object representation.

Example:

```c
int a = 100;
int b;

my_memcpy(&b, &a, sizeof(int));
```

Copies all bytes of integer.

---

## Test Code

```c
#include <stdio.h>

int main()
{
    char src[] = "abcdef";
    char dest[20];

    my_memcpy(dest, src, sizeof(src));

    printf("%s\n", dest);

    return 0;
}
```

Output:

```
abcdef
```

---

## Important Point

`memcpy()` cannot handle overlapping memory.

Example:

```
Before:

A B C D E


Copy:

A B C -> C D E
```

Result:

Undefined behavior.

Use:

```
memmove()
```

---

# 4. Implement memmove()

## Problem

Copy memory safely when source and destination overlap.

Function prototype:

```c
void *my_memmove(void *dest,
                 const void *src,
                 size_t n);
```

---

## Algorithm

Case 1:

Destination before source:

```
dest < src
```

Copy forward.

---

Case 2:

Destination after source:

```
dest > src
```

Copy backward.

---

## Implementation

```c
#include <stddef.h>

void *my_memmove(void *dest,
                 const void *src,
                 size_t n)
{
    unsigned char *d =
        (unsigned char *)dest;

    const unsigned char *s =
        (const unsigned char *)src;


    if(d == s)
        return dest;


    if(d < s)
    {
        // Forward copy

        while(n--)
        {
            *d++ = *s++;
        }
    }
    else
    {
        // Backward copy

        d = d + n;
        s = s + n;


        while(n--)
        {
            *--d = *--s;
        }
    }


    return dest;
}
```

---

## Example

Input:

```
abcdef
```

Operation:

```c
my_memmove(str + 2, str, 4);
```

Memory before:

```
a b c d e f
```

Copy:

```
a b a b c d
```

Memory after:

```
a b a b c d
```

---

# memcpy vs memmove

| Feature | memcpy | memmove |
|-|-|-|
| Overlap support | No | Yes |
| Speed | Faster | Slightly slower |
| Direction | Forward | Forward/Backward |
| Usage | Independent buffers | Overlapping buffers |

---

# Common Senior Interview Questions

## Q1. Why return destination pointer?

Because C APIs allow chaining.

Example:

```c
printf("%s",
       my_memcpy(buffer,src,10));
```

---

## Q2. Why not copy using int pointer?

Problems:

- Alignment issues
- Strict aliasing violation
- Remaining bytes handling

---

## Q3. How is real memcpy optimized?

Production implementations use:

- CPU word-sized copies
- SIMD instructions
- Cache line optimization
- Alignment detection
- Architecture-specific instructions

---

## Q4. Why does memmove copy backward?

Because forward copying can overwrite source bytes when memory overlaps.

Backward copy preserves original data.

---

# Complexity Summary

| Function | Time | Space |
|-|-|-|
| strlen() | O(n) | O(1) |
| strcpy() | O(n) | O(1) |
| memcpy() | O(n) | O(1) |
| memmove() | O(n) | O(1) |

---

# Next Part

## Part 2: Linked List Interview Implementations

Will cover:

- Node structure
- Insert/Delete
- Reverse linked list
- Recursive reverse
- Detect cycle (Floyd algorithm)
- Find cycle start
- Find middle node

