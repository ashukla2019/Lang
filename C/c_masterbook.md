# C MASTER HANDBOOK — SUPPLEMENT

## Fills gaps in Pointers, Bit Manipulation, Strings, and adds a new Part 19 — Input Handling

This supplement is written to slot directly into the existing handbook:

```text
Pointer additions   → insert after Part 3 (Pointers), before Part 4
Bit additions        → insert after Part 5 (Bit Manipulation), before Part 6
String additions     → insert after Part 2 (Arrays and Strings), before Part 3
Part 19              → new part, insert after Part 18
```

---

# PART 3 ADDITIONS — POINTERS

# 76a. `container_of`

One of the most common Linux kernel / driver interview questions.

Given a pointer to a member, recover a pointer to the containing structure.

```c
struct device
{
    int id;
    struct list_node node;
};

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))
```

Usage:

```c
struct list_node *n = get_node_from_list();

struct device *d = container_of(n, struct device, node);
```

Conceptually:

```text
struct device
 +-- id
 +-- node  <-- ptr points here
      |
      | subtract offsetof(device, node)
      v
struct device *  <-- recovered
```

This is how Linux implements intrusive linked lists (`list_head`), and why
`offsetof` (Part 7) matters beyond struct layout trivia.

---

# 76b. Reading Complex Pointer Declarations

Senior interviewers sometimes hand you a declaration and ask "what is this?"

Use the **right-left rule**: start at the identifier, alternate reading right
then left around parentheses/brackets.

```c
int *p;
```
→ `p` is a pointer to `int`

```c
int *p[10];
```
→ `p` is an array of 10 pointers to `int`

```c
int (*p)[10];
```
→ `p` is a pointer to an array of 10 `int`

```c
int (*f)(int);
```
→ `f` is a pointer to a function taking `int` returning `int`

```c
int (*(*f)(int))[10];
```
→ `f` is a pointer to a function taking `int`, returning a pointer to an
array of 10 `int`

Parentheses bind the `*` to the identifier first; without them, `[]` and `()`
bind tighter than `*`.

---

# 76c. Pointer Subtraction

Pointer arithmetic also works in reverse — subtracting two pointers into the
same array gives the number of elements between them, typed as `ptrdiff_t`.

```c
int a[10];

int *p = &a[7];
int *q = &a[2];

ptrdiff_t n = p - q;   /* 5 */
```

Valid only when both pointers point into the same array object (or one past
its end). Subtracting pointers into unrelated objects is undefined behavior,
just like relational comparison (Part 40).

---

# 76d. Opaque Pointers / Incomplete Types

A common C encapsulation pattern (used heavily in library and driver APIs):
expose only a pointer to an incomplete type in the header, and define the
real structure privately in the `.c` file.

Header:

```c
typedef struct device device_t;

device_t *device_create(void);
void device_destroy(device_t *d);
int device_get_id(device_t *d);
```

Source file:

```c
struct device
{
    int id;
    /* internal fields hidden from callers */
};
```

Callers can hold and pass `device_t *` freely but cannot see or depend on
its layout — the C equivalent of pImpl. This is how many kernel and
userspace libraries (e.g. `FILE *`) hide implementation details.

---

# 76e. Pointer Arithmetic Out-of-Bounds Without Dereference

A subtle point: forming an out-of-bounds pointer is undefined behavior even
if you never dereference it.

```c
int a[5];

int *p = a + 6;   /* already UB — more than one-past-the-end */
```

Only `a + 0` through `a + 5` (one-past-the-end) are valid pointer values for
a 5-element array. `a + 6` is invalid the moment it is *computed*, not just
when read.

---

# 76f. Function Pointers and `void *`

Standard C does not guarantee that a function pointer can be converted
to/from `void *` — object pointers and function pointers are not
interchangeable in strict ISO C.

```c
void *p = (void *)some_function;   /* not guaranteed portable in strict C */
```

POSIX explicitly relaxes this for APIs like `dlsym()`, which is why it works
in practice on Linux. Know the distinction: portable ISO C code should not
rely on it outside a POSIX context.

---

# 76g. Linked List Interview Problems — Worked

These are named in the original problem list; here they're implemented.

**Reverse a singly linked list:**

```c
struct Node
{
    int value;
    struct Node *next;
};

struct Node *reverse(struct Node *head)
{
    struct Node *prev = NULL;

    while (head != NULL)
    {
        struct Node *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;
}
```

**Detect a cycle (Floyd's tortoise and hare):**

```c
int has_cycle(struct Node *head)
{
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return 1;
    }

    return 0;
}
```

**Find the middle node (same slow/fast idea):**

```c
struct Node *find_middle(struct Node *head)
{
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
```

Concepts tested: pointer traversal, `NULL` checks, aliasing, two-pointer
technique.

---

# PART 5 ADDITIONS — BIT MANIPULATION

# 95a. Two's Complement

Signed integers on essentially all modern platforms use two's complement
representation.

To negate a value: invert all bits, then add 1.

```text
   00000101   (5)
   11111010   (invert)
 + 00000001
 ----------
   11111011   (-5)
```

This is why a single `0` bit pattern represents zero (no separate +0/−0),
and why the range is asymmetric: an 8-bit signed type covers `-128..127`,
not `-127..127`.

---

# 95b. Find the Single Unique Number (XOR)

Classic interview problem: every element in an array appears twice except
one — find it in O(n) time, O(1) space.

```c
int find_unique(int *a, size_t n)
{
    int result = 0;

    for (size_t i = 0; i < n; i++)
        result ^= a[i];

    return result;
}
```

Works because `x ^ x == 0` and `x ^ 0 == x` — every paired value cancels
out, leaving only the unpaired one. Directly builds on the XOR-swap trick
already in the handbook (Part 106).

---

# 95c. Detecting Opposite Signs with XOR

```c
int opposite_signs(int a, int b)
{
    return (a ^ b) < 0;
}
```

XOR of the sign bits leaves the result's sign bit set only when exactly one
of `a`/`b` is negative — avoids overflow-prone approaches like checking
`a * b < 0`.

---

# 95d. Runtime Endianness Check

Endianness is discussed conceptually in the original handbook (Part 117)
but never demonstrated. The classic runtime check:

```c
int is_little_endian(void)
{
    uint32_t x = 1;
    unsigned char *p = (unsigned char *)&x;

    return p[0] == 1;
}
```

If the least-significant byte of `x` is stored first in memory, the machine
is little-endian.

---

# 95e. `htons` / `htonl` / `ntohs` / `ntohl`

Network protocols conventionally use big-endian ("network byte order").
POSIX provides conversion functions so code is portable across host
endianness:

```c
#include <arpa/inet.h>

uint16_t port_be  = htons(port_host);   /* host  -> network, 16-bit */
uint32_t addr_be  = htonl(addr_host);   /* host  -> network, 32-bit */

uint16_t port_host = ntohs(port_be);    /* network -> host, 16-bit */
uint32_t addr_host = ntohl(addr_be);    /* network -> host, 32-bit */
```

On a big-endian host these are no-ops; on little-endian hosts they byte-swap.
Always use them at protocol/wire boundaries rather than hand-rolled swaps.

---

# 95f. Compiler Bit-Counting Builtins

The handbook implements set-bit counting by hand (Part 103). In practice,
GCC/Clang provide intrinsics that map to dedicated CPU instructions where
available:

```c
__builtin_popcount(x);   /* number of set bits */
__builtin_clz(x);        /* count leading zeros (x must be non-zero) */
__builtin_ctz(x);        /* count trailing zeros (x must be non-zero) */
```

These are typically faster than a hand-written loop and are worth mentioning
in an interview even if you also show the manual version — it demonstrates
awareness of what the toolchain offers versus portable-C fallbacks.

---

# PART 2 ADDITIONS — STRINGS

# 20a. `memcpy` vs `memmove`

Both copy raw bytes, but they differ on overlapping regions.

```c
void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
```

`memcpy` assumes the regions do **not** overlap — behavior is undefined if
they do. `memmove` explicitly handles overlap correctly (conceptually by
copying through a temporary or choosing a safe copy direction).

```c
char buf[10] = "abcdefghi";

memmove(buf + 2, buf, 5);   /* safe: overlapping, shifts right */
memcpy(buf + 2, buf, 5);    /* undefined behavior: overlapping regions */
```

Rule of thumb: if source and destination might overlap and you aren't
certain, use `memmove`.

---

# 20b. `memcmp` vs `strcmp`

```c
int memcmp(const void *a, const void *b, size_t n);
int strcmp(const char *a, const char *b);
```

`strcmp` compares characters until it hits a `'\0'` in either string.
`memcmp` compares exactly `n` bytes regardless of embedded null bytes —
important when comparing fixed-size binary buffers, structs, or strings that
may legitimately contain `'\0'` before their logical end.

Using `strcmp` on non-null-terminated binary data can read past the buffer;
using `memcmp` on two strings of different lengths without checking lengths
first can miss the actual point of difference. Pick the one that matches
what you're actually comparing.

---

# 20c. Worked Implementations

The original handbook lists `strlen`, `strcpy`, `strcmp`, `strstr` as things
you should "be able to implement." Here they are:

```c
size_t my_strlen(const char *s)
{
    const char *p = s;

    while (*p != '\0')
        p++;

    return (size_t)(p - s);
}

char *my_strcpy(char *dst, const char *src)
{
    char *ret = dst;

    while ((*dst++ = *src++) != '\0')
        ;

    return ret;
}

int my_strcmp(const char *a, const char *b)
{
    while (*a != '\0' && *a == *b)
    {
        a++;
        b++;
    }

    return (unsigned char)*a - (unsigned char)*b;
}

char *my_strstr(const char *haystack, const char *needle)
{
    if (*needle == '\0')
        return (char *)haystack;

    for (; *haystack != '\0'; haystack++)
    {
        const char *h = haystack;
        const char *n = needle;

        while (*h != '\0' && *n != '\0' && *h == *n)
        {
            h++;
            n++;
        }

        if (*n == '\0')
            return (char *)haystack;
    }

    return NULL;
}
```

---

# 20d. Safe Integer Parsing — `strtol` / `strtoul`

`atoi()` has no error reporting — it silently returns 0 on invalid input
with no way to distinguish that from an actual "0". Prefer `strtol`:

```c
#include <errno.h>
#include <stdlib.h>

char *endptr;
errno = 0;

long value = strtol(str, &endptr, 10);

if (endptr == str)
{
    /* no digits were parsed */
}
else if (errno == ERANGE)
{
    /* value out of range for long */
}
else if (*endptr != '\0')
{
    /* trailing non-numeric characters */
}
```

Three things to check: `endptr == str` (nothing parsed), `errno == ERANGE`
(overflow/underflow), and whatever `*endptr` points to (trailing garbage).
`strtoul` follows the same pattern for unsigned values.

---

# 20e. `strtok` and Why It's Dangerous

```c
char *token = strtok(str, ",");

while (token != NULL)
{
    token = strtok(NULL, ",");
}
```

Two problems senior interviewers expect you to know:

```text
1. It modifies the input string in place (writes '\0' at delimiters).
2. It keeps internal static state — not thread-safe, and calls cannot
   be interleaved/nested (e.g. tokenizing two strings at once breaks).
```

Prefer the reentrant `strtok_r` (POSIX) when thread-safety or nested
tokenizing is required — it takes an explicit `saveptr` argument instead of
hidden static state.

---

# 20f. `strdup`

```c
char *copy = strdup(original);

/* ... */

free(copy);
```

Allocates a new buffer and copies the string, including the terminator.
Not part of ISO C (it's POSIX), but extremely commonly used. Ownership is
clear: the caller receives allocated memory and is responsible for
`free()`-ing it — ties directly back to the ownership discipline in
Part 71/127.

---

# PART 19 — INPUT HANDLING

# 200a. Buffered stdio vs Raw Syscalls

The original handbook (Part 14) covers `open`/`read`/`write`/`close` — raw,
unbuffered Linux syscalls. Most C programs instead go through the C
library's buffered stdio layer:

```text
Application
    ↓
stdio (FILE *, buffered)
    ↓
read() / write() syscalls
    ↓
Kernel
```

`FILE *` functions (`fgets`, `fread`, `fprintf`, ...) batch small reads/writes
into fewer syscalls for efficiency. Raw syscalls give you direct control but
no buffering — you manage that yourself.

---

# 200b. `scanf` and Why `%s` Is Dangerous

```c
char buf[16];

scanf("%s", buf);   /* no bound — classic buffer overflow */
```

`%s` with no width specifier reads until whitespace with **no bound
checking**, and will happily overflow `buf` given long enough input.

Safer:

```c
scanf("%15s", buf);   /* bounded to 15 chars + '\0' */
```

Still awkward for general line input — see `fgets`/`getline` below.
`scanf` is also error-prone for numeric input: on a match failure it leaves
the offending characters in the stream, which can desync subsequent calls.
Always check its return value (number of successful conversions).

---

# 200c. `gets()` — Removed From the Standard

```c
char buf[16];

gets(buf);   /* DO NOT USE — removed from C11 */
```

`gets()` has no way to bound how much it reads — it was formally removed
from the C standard in C11 specifically because it cannot be used safely.
If you see it in legacy code, replace it with `fgets`.

---

# 200d. `fgets` — the Safe Line-Reading Function

```c
char buf[128];

if (fgets(buf, sizeof(buf), stdin) != NULL)
{
    /* success */
}
```

Bounded by the buffer size, and null-terminates the result. Important
quirk: if a full line fits, `fgets` keeps the trailing `'\n'` in the buffer
— callers typically strip it:

```c
size_t len = strlen(buf);

if (len > 0 && buf[len - 1] == '\n')
    buf[len - 1] = '\0';
```

Also returns `NULL` on EOF or error before reading anything — always check
before using the buffer.

---

# 200e. `getline` — Dynamically Growing Input

POSIX `getline` reads an entire line of arbitrary length, growing the
buffer as needed:

```c
char *line = NULL;
size_t cap = 0;

ssize_t n = getline(&line, &cap, stdin);

if (n != -1)
{
    /* line contains n bytes, including '\n' if present */
}

free(line);
```

`line` may be reallocated internally — always pass its address and free it
yourself when done. Useful when input length isn't known ahead of time,
avoiding the fixed-buffer limitation of `fgets`.

---

# 200f. `getchar` / `putchar` and EOF

```c
int c;

while ((c = getchar()) != EOF)
{
    putchar(c);
}
```

`getchar()` returns `int`, not `char` — this matters because `EOF` is
typically `-1`, and on platforms where `char` is unsigned, comparing a
`char`-truncated value against `EOF` can never be true, causing an infinite
loop. Always store the return value in an `int` before comparing to `EOF`.

---

# 200g. The `scanf` + `fgets` Buffering Gotcha

A very common real bug:

```c
int n;
char name[64];

scanf("%d", &n);       /* leaves trailing '\n' in stdin */
fgets(name, sizeof(name), stdin);   /* reads the leftover '\n', not input */
```

`scanf("%d", ...)` consumes only the digits, leaving the newline in the
input buffer. The following `fgets` immediately reads that leftover `'\n'`
and returns an empty line instead of waiting for the user.

Fix: consume the rest of the line after `scanf`, or avoid mixing `scanf`
and `fgets` — prefer `fgets` + `sscanf`/`strtol` for all input instead:

```c
char line[64];

fgets(line, sizeof(line), stdin);
int n = (int)strtol(line, NULL, 10);
```

---

# 200h. `fread` / `fwrite` for Binary Data

Text-oriented functions (`scanf`, `fgets`) are unsuitable for binary data.
Use `fread`/`fwrite` for fixed-size binary records:

```c
struct Record r;

size_t got = fread(&r, sizeof(r), 1, fp);

if (got != 1)
{
    /* short read / EOF / error */
}
```

Always check the returned element count, not just that the call "ran" —
a short read (fewer elements than requested) can mean EOF or a partial
record, and the struct's contents should not be trusted if the count is
short. Also be mindful of struct padding (Part 79) when reading/writing
binary records across different compilers/platforms.

---

# 200i. Input Handling Interview Questions

```text
1. Why is gets() unsafe, and what replaced it?
2. Why is scanf("%s", buf) dangerous?
3. What does fgets do with the trailing newline?
4. Why does getchar() return int, not char?
5. Why can mixing scanf and fgets cause a skipped read?
6. When would you use getline over fgets?
7. Why check fread's return value instead of just calling it?
8. Buffered stdio vs raw read()/write() — what's the tradeoff?
9. How do you safely parse a number from user input?
10. Why is strtok unsafe in multithreaded code, and what replaces it?
```

---

# UPDATED FINAL CHECKLIST — ADDITIONS

```text
[ ] container_of
[ ] Reading complex pointer declarations (right-left rule)
[ ] Pointer subtraction / ptrdiff_t
[ ] Opaque pointers / incomplete types
[ ] Pointer arithmetic UB without dereference
[ ] Function pointer <-> void* portability
[ ] Reverse / cycle-detect / find-middle on a linked list (implemented)
[ ] Two's complement
[ ] XOR: find unique element, opposite-sign check
[ ] Runtime endianness check
[ ] htons/htonl/ntohs/ntohl
[ ] __builtin_popcount/clz/ctz
[ ] memcpy vs memmove
[ ] memcmp vs strcmp
[ ] strlen/strcpy/strcmp/strstr implemented from scratch
[ ] strtol/strtoul safe parsing (errno, endptr)
[ ] strtok danger + strtok_r
[ ] strdup and ownership
[ ] scanf("%s") overflow risk
[ ] gets() removal from C11
[ ] fgets newline handling
[ ] getline dynamic input
[ ] getchar/EOF int-vs-char pitfall
[ ] scanf + fgets leftover-newline bug
[ ] fread/fwrite for binary data
```

# END — SUPPLEMENT
