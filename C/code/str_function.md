C String and Memory Functions — Easy Implementations

This document contains simple implementations of commonly used C string and memory functions for learning purposes.

Note: These implementations are intended for learning. In production code, prefer the optimized functions provided by the standard library where available.

Table of Contents
String Functions
strlen()
strcpy()
strncpy()
strcat()
strncat()
strcmp()
strncmp()
strchr()
strrchr()
strstr()
strtok()
strspn()
strcspn()
strpbrk()
strdup()
strrev()
strupr()
strlwr()
Memory Functions
memset()
memcpy()
memmove()
memcmp()
memchr()
strerror()
Part 1 — String Functions
1. strlen()
Purpose

Returns the length of a string, excluding the terminating '\0'.

Prototype
size_t my_strlen(const char *str);

Implementation
size_t my_strlen(const char *str)
{
    size_t len = 0;

    while (str[len] != '\0')
        len++;

    return len;
}

Example
char s[] = "Hello";

printf("%zu", my_strlen(s));

Output
5

2. strcpy()
Purpose

Copies one string into another.

Prototype
char *my_strcpy(char *dest, const char *src);

Implementation
char *my_strcpy(char *dest, const char *src)
{
    int i = 0;

    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';

    return dest;
}

Example
char src[] = "OpenAI";
char dest[20];

my_strcpy(dest, src);

printf("%s", dest);

Output
OpenAI

3. strncpy()
Purpose

Copies up to n characters from the source string.

Prototype
char *my_strncpy(char *dest, const char *src, size_t n);

Implementation
char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];

    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }

    return dest;
}

Example
char src[] = "Programming";
char dest[20];

my_strncpy(dest, src, 7);

printf("%s", dest);

Output
Program

4. strcat()
Purpose

Appends one string to another.

Prototype
char *my_strcat(char *dest, const char *src);

Implementation
char *my_strcat(char *dest, const char *src)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
        i++;

    while (src[j] != '\0')
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';

    return dest;
}

Example
char a[30] = "Hello ";
char b[] = "World";

my_strcat(a, b);

printf("%s", a);

Output
Hello World

5. strncat()
Purpose

Appends up to n characters from the source string.

Prototype
char *my_strncat(char *dest, const char *src, size_t n);

Implementation
char *my_strncat(char *dest, const char *src, size_t n)
{
    size_t i = 0;
    size_t j = 0;

    while (dest[i] != '\0')
        i++;

    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';

    return dest;
}

Example
char a[30] = "Hello ";
char b[] = "Programming";

my_strncat(a, b, 7);

printf("%s", a);

Output
Hello Program

6. strcmp()
Purpose

Compares two strings.

Return Value
0 → Strings are equal
< 0 → First string is smaller
> 0 → First string is greater
Prototype
int my_strcmp(const char *s1, const char *s2);

Implementation
int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (unsigned char)s1[i] - (unsigned char)s2[i];

        i++;
    }

    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

Example
printf("%d", my_strcmp("abc", "abc"));

Output
0

7. strncmp()
Purpose

Compares up to n characters of two strings.

Prototype
int my_strncmp(const char *s1, const char *s2, size_t n);

Implementation
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    for (i = 0; i < n; i++)
    {
        if (s1[i] != s2[i] ||
            s1[i] == '\0' ||
            s2[i] == '\0')
        {
            return (unsigned char)s1[i] -
                   (unsigned char)s2[i];
        }
    }

    return 0;
}

Example
printf("%d", my_strncmp("apple", "application", 5));

Output
0

8. strchr()
Purpose

Finds the first occurrence of a character in a string.

Prototype
char *my_strchr(char *str, int ch);

Implementation
char *my_strchr(char *str, int ch)
{
    while (*str)
    {
        if (*str == ch)
            return str;

        str++;
    }

    if (ch == '\0')
        return str;

    return NULL;
}

Example
char s[] = "Computer";

printf("%s", my_strchr(s, 'p'));

Output
puter

9. strrchr()
Purpose

Finds the last occurrence of a character in a string.

Prototype
char *my_strrchr(char *str, int ch);

Implementation
char *my_strrchr(char *str, int ch)
{
    char *last = NULL;

    while (*str)
    {
        if (*str == ch)
            last = str;

        str++;
    }

    if (ch == '\0')
        return str;

    return last;
}

Example
char s[] = "banana";

printf("%s", my_strrchr(s, 'a'));

Output
a

10. strstr()
Purpose

Finds the first occurrence of a substring.

Prototype
char *my_strstr(char *str, char *sub);

Implementation
char *my_strstr(char *str, char *sub)
{
    int i, j;

    for (i = 0; str[i] != '\0'; i++)
    {
        for (j = 0; sub[j] != '\0'; j++)
        {
            if (str[i + j] != sub[j])
                break;
        }

        if (sub[j] == '\0')
            return &str[i];
    }

    return NULL;
}

Example
char s[] = "Embedded Systems";

printf("%s", my_strstr(s, "System"));

Output
Systems

Part 2 — Additional String Functions

The following functions continue the string-function section:

strtok()
strspn()
strcspn()
strpbrk()
strdup()
strrev()
strupr()
strlwr()
Part 3 — Memory Functions
19. memset()
Purpose

Fills a block of memory with a specified byte value.

Prototype
void *my_memset(void *ptr, int value, size_t n);

20. memcpy()
Purpose

Copies n bytes from one memory area to another.

Important

memcpy() should not be used when the source and destination memory regions overlap.

Prototype
void *my_memcpy(void *dest, const void *src, size_t n);

21. memmove()
Purpose

Copies memory safely when the source and destination memory areas overlap.

Prototype
void *my_memmove(void *dest, const void *src, size_t n);

Implementation
void *my_memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (d == s)
        return dest;

    if (d < s)
    {
        /* Copy forward */
        for (size_t i = 0; i < n; i++)
            d[i] = s[i];
    }
    else
    {
        /* Copy backward */
        for (size_t i = n; i > 0; i--)
            d[i - 1] = s[i - 1];
    }

    return dest;
}

Example
char str[] = "123456789";

my_memmove(str + 2, str, 5);

printf("%s", str);

Output
121234589

memcpy() vs memmove()
Function	Overlapping Memory
memcpy()	❌ Not safe
memmove()	✅ Safe
22. memcmp()
Purpose

Compares two blocks of memory byte by byte.

Prototype
int my_memcmp(const void *ptr1, const void *ptr2, size_t n);

Implementation
int my_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
    const unsigned char *a = ptr1;
    const unsigned char *b = ptr2;

    for (size_t i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return a[i] - b[i];
    }

    return 0;
}

Example
char a[] = "ABC";
char b[] = "ABC";

printf("%d", my_memcmp(a, b, 3));

Output
0

23. memchr()
Purpose

Searches for a byte in a block of memory.

Prototype
void *my_memchr(const void *ptr, int value, size_t n);

Implementation
void *my_memchr(const void *ptr, int value, size_t n)
{
    const unsigned char *p = ptr;

    for (size_t i = 0; i < n; i++)
    {
        if (p[i] == (unsigned char)value)
            return (void *)&p[i];
    }

    return NULL;
}

Example
char str[] = "Embedded";

char *p = my_memchr(str, 'b', 8);

if (p)
    printf("%s", p);

Output
bedded

24. strerror()
Purpose

Returns an error message corresponding to an error number.

Prototype
char *my_strerror(int errnum);

Implementation
char *my_strerror(int errnum)
{
    static char *errors[] =
    {
        "No error",
        "Permission denied",
        "File not found",
        "Invalid argument"
    };

    int size = sizeof(errors) / sizeof(errors[0]);

    if (errnum >= 0 && errnum < size)
        return errors[errnum];

    return "Unknown error";
}

Example
printf("%s", my_strerror(2));

Output
File not found

Complete Function Summary
#	Function	Purpose
1	strlen()	Find string length
2	strcpy()	Copy string
3	strncpy()	Copy first n characters
4	strcat()	Join strings
5	strncat()	Join first n characters
6	strcmp()	Compare strings
7	strncmp()	Compare first n characters
8	strchr()	Find first character
9	strrchr()	Find last character
10	strstr()	Find substring
11	strtok()	Split string into tokens
12	strspn()	Count accepted characters
13	strcspn()	Count characters until a rejected character
14	strpbrk()	Find first matching character
15	strdup()	Duplicate a string
16	strrev()	Reverse a string
17	strupr()	Convert string to uppercase
18	strlwr()	Convert string to lowercase
19	memset()	Fill memory
20	memcpy()	Copy memory
21	memmove()	Safely copy overlapping memory
22	memcmp()	Compare memory
23	memchr()	Search memory
24	strerror()	Return error message
Time Complexity Summary
Function	Time Complexity
strlen()	O(n)
strcpy()	O(n)
strncpy()	O(n)
strcat()	O(n + m)
strncat()	O(n + m)
strcmp()	O(n)
strncmp()	O(n)
strchr()	O(n)
strrchr()	O(n)
strstr()	O(n × m)
strtok()	O(n)
strspn()	O(n × m)
strcspn()	O(n × m)
strpbrk()	O(n × m)
strdup()	O(n)
strrev()	O(n)
strupr()	O(n)
strlwr()	O(n)
memset()	O(n)
memcpy()	O(n)
memmove()	O(n)
memcmp()	O(n)
memchr()	O(n)
strerror()	O(1)

Note: The exact complexity of library implementations can vary. The table above describes the straightforward implementations used for learning.

Standard C Functions

The following functions are part of the C standard library:

strlen()
strcpy()
strncpy()
strcat()
strncat()
strcmp()
strncmp()
strchr()
strrchr()
strstr()
strtok()
strspn()
strcspn()
strpbrk()
strerror()
memset()
memcpy()
memmove()
memcmp()
memchr()
Header
#include <string.h>

Non-Standard / Platform-Specific Functions

These functions are not part of ISO C:

strrev()
strupr()
strlwr()

strdup() is commonly available on POSIX systems, but it is not part of the ISO C standard.

Important Learning Notes
1. Use size_t for sizes

For functions dealing with string lengths or memory sizes, size_t is preferred over int.

size_t len;
size_t n;

2. Always ensure enough destination memory

For example:

char src[] = "Hello";
char dest[6];

my_strcpy(dest, src);


The destination needs space for:

H e l l o \0


which is 6 bytes.

3. memcpy() and overlapping memory

Do not use:

my_memcpy(str + 2, str, 5);


when the regions overlap.

Use:

my_memmove(str + 2, str, 5);


instead.

Final Note

These implementations are intentionally simple and are designed for learning, interviews, and understanding how C string/memory functions work internally.

For production applications, prefer the implementations provided by the C standard library because they are generally well-tested and optimized.