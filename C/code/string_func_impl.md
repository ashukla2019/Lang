# C String Functions Implementation

Custom implementations of common C string functions from `<string.h>`.

Implemented functions:

- `strlen()`
- `strcpy()`
- `strcat()`
- `strchr()`
- `strstr()`
- `strtok()`

---

# 1. strlen()

## Purpose

Returns the length of a null-terminated string excluding the `'\0'` character.

## Implementation

```c
#include <stddef.h>

size_t my_strlen(const char *str)
{
    size_t len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}
```

## Example

```c
printf("%zu", my_strlen("hello"));
```

Output:

```
5
```

---

# 2. strcpy()

## Purpose

Copies the source string into the destination buffer including the terminating `'\0'`.

## Implementation

```c
char *my_strcpy(char *dest, const char *src)
{
    char *original = dest;

    while ((*dest++ = *src++) != '\0')
    {
        ;
    }

    return original;
}
```

## Example

```c
char buffer[20];

my_strcpy(buffer, "hello");

printf("%s", buffer);
```

Output:

```
hello
```

---

# 3. strcat()

## Purpose

Appends the source string to the end of the destination string.

## Implementation

```c
char *my_strcat(char *dest, const char *src)
{
    char *original = dest;

    while (*dest != '\0')
    {
        dest++;
    }

    while ((*dest++ = *src++) != '\0')
    {
        ;
    }

    return original;
}
```

## Example

```c
char str[30] = "Hello ";

my_strcat(str, "World");

printf("%s", str);
```

Output:

```
Hello World
```

---

# 4. strchr()

## Purpose

Finds the first occurrence of a character in a string.

Returns a pointer to the character if found, otherwise returns `NULL`.

## Implementation

```c
#include <stddef.h>

char *my_strchr(const char *str, int ch)
{
    while (*str != '\0')
    {
        if (*str == ch)
        {
            return (char *)str;
        }

        str++;
    }

    if (ch == '\0')
    {
        return (char *)str;
    }

    return NULL;
}
```

## Example

```c
char *p = my_strchr("hello", 'l');

printf("%s", p);
```

Output:

```
llo
```

---

# 5. strstr()

## Purpose

Finds the first occurrence of a substring inside another string.

## Implementation

```c
char *my_strstr(const char *str, const char *sub)
{
    if (*sub == '\0')
    {
        return (char *)str;
    }

    while (*str)
    {
        const char *s1 = str;
        const char *s2 = sub;

        while (*s1 && *s2 && (*s1 == *s2))
        {
            s1++;
            s2++;
        }

        if (*s2 == '\0')
        {
            return (char *)str;
        }

        str++;
    }

    return NULL;
}
```

## Example

```c
char *p = my_strstr("hello world", "world");

printf("%s", p);
```

Output:

```
world
```

---

# 6. strtok()

## Purpose

Splits a string into tokens using delimiters.

Example:

Input:

```
hello,world,test
```

Delimiter:

```
,
```

Tokens:

```
hello
world
test
```

## Implementation

```c
char *my_strtok(char *str, const char *delim)
{
    static char *next;

    if (str != NULL)
    {
        next = str;
    }

    if (next == NULL)
    {
        return NULL;
    }


    // Skip delimiters

    while (*next)
    {
        const char *d = delim;
        int found = 0;

        while (*d)
        {
            if (*next == *d)
            {
                found = 1;
                break;
            }

            d++;
        }

        if (!found)
        {
            break;
        }

        next++;
    }


    if (*next == '\0')
    {
        return NULL;
    }


    char *start = next;


    // Find token end

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

    return start;
}
```

## Example

```c
#include <stdio.h>

int main()
{
    char str[] = "hello,world,test";

    char *token;

    token = my_strtok(str, ",");

    while (token)
    {
        printf("%s\n", token);

        token = my_strtok(NULL, ",");
    }

    return 0;
}
```

Output:

```
hello
world
test
```

---

# Concepts Learned

| Function | Main Concept |
|----------|--------------|
| strlen  | Pointer traversal |
| strcpy  | Copying null-terminated strings |
| strcat  | Finding string end and appending |
| strchr  | Returning pointers |
| strstr  | Nested pointer traversal |
| strtok  | Static variables and state management |

---

# Additional Practice

Implement these next:

- `strcmp()`
- `strncmp()`
- `memcmp()`
- `memcpy()`
- `memmove()`
- `memset()`

These functions help build a strong understanding of:

- pointers
- arrays
- memory layout
- dynamic memory
- the C standard library internals
