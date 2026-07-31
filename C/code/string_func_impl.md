# C String Functions Implementation

Custom implementations of common C string functions from `<string.h>`.

Functions covered:

- `strlen()`
- `strcpy()`
- `strcat()`
- `strchr()`
- `strstr()`
- `strtok()`

---

# 1. strlen()

## Purpose

Returns the length of a null-terminated string (excluding `'\0'`).

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
