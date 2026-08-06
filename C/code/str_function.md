# C String Functions (Easy Implementations)

This file contains easy implementations of commonly used C string functions for learning purposes.

---

# Table of Contents

1. strlen()
2. strcpy()
3. strncpy()
4. strcat()
5. strncat()
6. strcmp()
7. strncmp()
8. strchr()
9. strrchr()
10. strstr()
11. strtok()
12. strspn()
13. strcspn()
14. strpbrk()
15. strdup()
16. strrev()
17. strupr()
18. strlwr()
19. memset()
20. memcpy()
21. memmove()
22. memcmp()
23. memchr()
24. strerror()

---

# 1. strlen()

### Purpose
Returns the length of a string (excluding `'\0'`).

### Prototype

```c
size_t my_strlen(const char *str);
```

### Implementation

```c
int my_strlen(const char *str)
{
    int len = 0;

    while(str[len] != '\0')
        len++;

    return len;
}
```

### Example

```c
char s[] = "Hello";
printf("%d", my_strlen(s));
```

Output

```
5
```

---

# 2. strcpy()

### Purpose
Copies one string into another.

### Prototype

```c
char *my_strcpy(char *dest,const char *src);
```

### Implementation

```c
char *my_strcpy(char *dest,const char *src)
{
    int i = 0;

    while(src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';

    return dest;
}
```

### Example

```c
char src[]="OpenAI";
char dest[20];

my_strcpy(dest,src);

printf("%s",dest);
```

Output

```
OpenAI
```

---

# 3. strncpy()

### Purpose
Copies first n characters.

### Prototype

```c
char *my_strncpy(char *dest,const char *src,int n);
```

### Implementation

```c
char *my_strncpy(char *dest,const char *src,int n)
{
    int i;

    for(i=0;i<n && src[i]!='\0';i++)
        dest[i]=src[i];

    while(i<n)
    {
        dest[i]='\0';
        i++;
    }

    return dest;
}
```

### Example

```c
char src[]="Programming";
char dest[20];

my_strncpy(dest,src,7);

printf("%s",dest);
```

Output

```
Program
```

---

# 4. strcat()

### Purpose
Appends one string to another.

### Prototype

```c
char *my_strcat(char *dest,const char *src);
```

### Implementation

```c
char *my_strcat(char *dest,const char *src)
{
    int i=0;
    int j=0;

    while(dest[i]!='\0')
        i++;

    while(src[j]!='\0')
    {
        dest[i]=src[j];
        i++;
        j++;
    }

    dest[i]='\0';

    return dest;
}
```

### Example

```c
char a[30]="Hello ";
char b[]="World";

my_strcat(a,b);

printf("%s",a);
```

Output

```
Hello World
```

---

# 5. strncat()

### Purpose
Appends first n characters.

### Prototype

```c
char *my_strncat(char *dest,const char *src,int n);
```

### Implementation

```c
char *my_strncat(char *dest,const char *src,int n)
{
    int i=0;
    int j=0;

    while(dest[i]!='\0')
        i++;

    while(src[j]!='\0' && j<n)
    {
        dest[i]=src[j];
        i++;
        j++;
    }

    dest[i]='\0';

    return dest;
}
```

### Example

```c
char a[30]="Hello ";
char b[]="Programming";

my_strncat(a,b,7);

printf("%s",a);
```

Output

```
Hello Program
```

---

# 6. strcmp()

### Purpose
Compares two strings.

Returns

- 0 → Equal
- >0 → First string greater
- <0 → Second string greater

### Prototype

```c
int my_strcmp(const char *s1,const char *s2);
```

### Implementation

```c
int my_strcmp(const char *s1,const char *s2)
{
    int i=0;

    while(s1[i] && s2[i])
    {
        if(s1[i]!=s2[i])
            return s1[i]-s2[i];

        i++;
    }

    return s1[i]-s2[i];
}
```

### Example

```c
printf("%d",my_strcmp("abc","abc"));
```

Output

```
0
```

---

# 7. strncmp()

### Purpose
Compares first n characters.

### Prototype

```c
int my_strncmp(const char *s1,const char *s2,int n);
```

### Implementation

```c
int my_strncmp(const char *s1,const char *s2,int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        if(s1[i]!=s2[i] || s1[i]=='\0' || s2[i]=='\0')
            return s1[i]-s2[i];
    }

    return 0;
}
```

### Example

```c
printf("%d",my_strncmp("apple","application",5));
```

Output

```
0
```

---

# 8. strchr()

### Purpose
Finds first occurrence of a character.

### Prototype

```c
char *my_strchr(char *str,char ch);
```

### Implementation

```c
char *my_strchr(char *str,char ch)
{
    while(*str)
    {
        if(*str==ch)
            return str;

        str++;
    }

    if(ch=='\0')
        return str;

    return NULL;
}
```

### Example

```c
char s[]="Computer";

printf("%s",my_strchr(s,'p'));
```

Output

```
puter
```

---

# 9. strrchr()

### Purpose
Finds last occurrence of a character.

### Prototype

```c
char *my_strrchr(char *str,char ch);
```

### Implementation

```c
char *my_strrchr(char *str,char ch)
{
    char *last=NULL;

    while(*str)
    {
        if(*str==ch)
            last=str;

        str++;
    }

    if(ch=='\0')
        return str;

    return last;
}
```

### Example

```c
char s[]="banana";

printf("%s",my_strrchr(s,'a'));
```

Output

```
a
```

---

# 10. strstr()

### Purpose
Finds first occurrence of a substring.

### Prototype

```c
char *my_strstr(char *str,char *sub);
```

### Implementation

```c
char *my_strstr(char *str,char *sub)
{
    int i,j;

    for(i=0;str[i]!='\0';i++)
    {
        for(j=0;sub[j]!='\0';j++)
        {
            if(str[i+j]!=sub[j])
                break;
        }

        if(sub[j]=='\0')
            return &str[i];
    }

    return NULL;
}
```

### Example

```c
char s[]="Embedded Systems";

printf("%s",my_strstr(s,"System"));
```

Output

```
Systems
```

---

**End of Part 1**

**Next (Part 2)** will include:

- `strtok()`
- `strspn()`
- `strcspn()`
- `strpbrk()`
- `strdup()`
- `strrev()`
- `strupr()`
- `strlwr()`
- `memset()`
- `memcpy()`
----------------------
---

# 21. memmove()

### Purpose

Copies memory safely when source and destination memory areas overlap.

### Prototype

```c
void *my_memmove(void *dest,const void *src,int n);
```

### Implementation

```c
void *my_memmove(void *dest,const void *src,int n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if(d == s)
        return dest;

    if(d < s)
    {
        // Copy forward
        for(int i=0;i<n;i++)
            d[i]=s[i];
    }
    else
    {
        // Copy backward
        for(int i=n-1;i>=0;i--)
            d[i]=s[i];
    }

    return dest;
}
```

### Example

```c
char str[]="123456789";

my_memmove(str+2,str,5);

printf("%s",str);
```

Output

```
121234589
```

### Difference between memcpy() and memmove()

| Function | Overlapping Memory |
|----------|--------------------|
| memcpy() | Not safe |
| memmove() | Safe |

---

# 22. memcmp()

### Purpose

Compares two memory blocks.

### Prototype

```c
int my_memcmp(const void *ptr1,const void *ptr2,int n);
```

### Implementation

```c
int my_memcmp(const void *ptr1,const void *ptr2,int n)
{
    const unsigned char *a = ptr1;
    const unsigned char *b = ptr2;

    for(int i=0;i<n;i++)
    {
        if(a[i] != b[i])
            return a[i]-b[i];
    }

    return 0;
}
```

### Example

```c
char a[]="ABC";
char b[]="ABC";

printf("%d",my_memcmp(a,b,3));
```

Output

```
0
```

---

# 23. memchr()

### Purpose

Searches for a character in a memory block.

### Prototype

```c
void *my_memchr(const void *ptr,int value,int n);
```

### Implementation

```c
void *my_memchr(const void *ptr,int value,int n)
{
    const unsigned char *p = ptr;

    for(int i=0;i<n;i++)
    {
        if(p[i] == (unsigned char)value)
            return (void *)&p[i];
    }

    return NULL;
}
```

### Example

```c
char str[]="Embedded";

char *p = my_memchr(str,'b',8);

if(p)
    printf("%s",p);
```

Output

```
bedded
```

---

# 24. strerror()

### Purpose

Returns error message string for an error number.

### Prototype

```c
char *my_strerror(int errnum);
```

### Implementation

```c
char *my_strerror(int errnum)
{
    static char *errors[] =
    {
        "No error",
        "Permission denied",
        "File not found",
        "Invalid argument"
    };

    int size = sizeof(errors)/sizeof(errors[0]);

    if(errnum >= 0 && errnum < size)
        return errors[errnum];

    return "Unknown error";
}
```

### Example

```c
printf("%s",my_strerror(2));
```

Output

```
File not found
```

---

# Complete Function Summary

| Function | Purpose |
|----------|---------|
| strlen() | Find string length |
| strcpy() | Copy string |
| strncpy() | Copy first n characters |
| strcat() | Join strings |
| strncat() | Join first n characters |
| strcmp() | Compare strings |
| strncmp() | Compare first n characters |
| strchr() | Find first character |
| strrchr() | Find last character |
| strstr() | Find substring |
| strtok() | Split string into tokens |
| strspn() | Count accepted characters |
| strcspn() | Count until rejected character |
| strpbrk() | Find matching character |
| strdup() | Duplicate string |
| strrev() | Reverse string |
| strupr() | Convert uppercase |
| strlwr() | Convert lowercase |
| memset() | Fill memory |
| memcpy() | Copy memory |
| memmove() | Safe memory copy |
| memcmp() | Compare memory |
| memchr() | Search memory |
| strerror() | Error message |

---

# Time Complexity Summary

| Function | Time Complexity |
|----------|----------------|
| strlen() | O(n) |
| strcpy() | O(n) |
| strncpy() | O(n) |
| strcat() | O(n+m) |
| strncat() | O(n+m) |
| strcmp() | O(n) |
| strncmp() | O(n) |
| strchr() | O(n) |
| strrchr() | O(n) |
| strstr() | O(n*m) |
| strtok() | O(n) |
| strspn() | O(n*m) |
| strcspn() | O(n*m) |
| strpbrk() | O(n*m) |
| strdup() | O(n) |
| strrev() | O(n) |
| strupr() | O(n) |
| strlwr() | O(n) |
| memset() | O(n) |
| memcpy() | O(n) |
| memmove() | O(n) |
| memcmp() | O(n) |
| memchr() | O(n) |
| strerror() | O(1) |

---

# Notes

## Standard Functions

These are available in C standard library:

- strlen
- strcpy
- strncpy
- strcat
- strncat
- strcmp
- strncmp
- strchr
- strrchr
- strstr
- strtok
- strspn
- strcspn
- strpbrk
- strerror
- memset
- memcpy
- memmove
- memcmp
- memchr

Header:

```c
#include <string.h>
```

---

## Non-Standard Functions

These are compiler-dependent:

- strrev()
- strupr()
- strlwr()
- strdup() *(POSIX, not ISO C)*

---

# Final Note

These implementations are written for learning.  
Production code should usually use the optimized versions provided by the C standard library.

