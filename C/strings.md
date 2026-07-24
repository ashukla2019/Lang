# C Strings Handbook
# Part 1 - Fundamentals

---

# Table of Contents

1. Introduction
2. What is a String?
3. How Strings are Stored
4. Null Character (`'\0'`)
5. Character vs String
6. Declaring Strings
7. String Initialization
8. Memory Representation
9. Size of String
10. Reading Strings
11. Printing Strings
12. Traversing Strings
13. char[] vs char*
14. String Literals
15. Modifying Strings
16. Pointer to String
17. Pointer Arithmetic
18. const with Strings
19. String Copy vs Pointer Copy
20. Shallow Copy vs Deep Copy
21. Summary

---

# 1. Introduction

Unlike C++, C **does not provide a built-in string data type**.

In C, a string is simply an array of characters terminated by a **null character (`'\0'`)**.

Example

```c
char str[] = "Hello";
```

Memory

```
+---+---+---+---+---+----+
| H | e | l | l | o | \0 |
+---+---+---+---+---+----+
```

Every string in C **must end with `'\0'`**.

---

# 2. What is a String?

Definition

> A string is a sequence of characters stored in contiguous memory and terminated by a null character (`'\0'`).

Example

```c
char name[] = "Coding";
```

Memory

```
+---+---+---+---+---+---+----+
| C | o | d | i | n | g | \0 |
+---+---+---+---+---+---+----+
```

Without `'\0'`, C cannot determine where the string ends.

---

# 3. How Strings are Stored

Example

```c
char city[] = "Pune";
```

Memory

```
Address      Value

1000         P
1001         u
1002         n
1003         e
1004         \0
```

Characters occupy **contiguous memory locations**.

---

# 4. Null Character ('\0')

Every valid C string ends with

```c
'\0'
```

ASCII value

```
0
```

Example

```c
char str[] = {'H','i','\0'};
```

Equivalent to

```c
char str[] = "Hi";
```

Wrong

```c
char str[] = {'H','i'};
```

This is **NOT** a valid C string.

Library functions like

```
strlen()
printf("%s")
strcpy()
strcmp()
```

depend on `'\0'`.

---

# 5. Character vs String

Character

```c
char ch = 'A';
```

Memory

```
+---+
| A |
+---+
```

Only one byte.

---

String

```c
char str[] = "A";
```

Memory

```
+---+----+
| A | \0 |
+---+----+
```

Needs two bytes.

Difference

| Character | String |
|------------|---------|
| 'A' | "A" |
| Single character | Collection of characters |
| char | char[] |

---

# 6. Declaring Strings

Method 1

```c
char str[20];
```

Creates empty character array.

---

Method 2

```c
char str[] = "Hello";
```

Compiler calculates size.

Memory

```
H e l l o \0
```

Size = 6 bytes.

---

Method 3

```c
char str[6] = "Hello";
```

Correct.

---

Method 4

```c
char str[]={'H','e','l','l','o','\0'};
```

Equivalent.

---

Method 5

```c
char str[20] = "";
```

Empty string.

---

# 7. String Initialization

Example

```c
char s1[]="Hello";
```

Example

```c
char s2[20]="Hello";
```

Example

```c
char s3[]={'H','e','l','l','o','\0'};
```

Example

```c
char s4[20]={0};
```

Creates an empty string.

---

# 8. Memory Representation

```c
char str[]="ABC";
```

Memory

```
Address

1000     A

1001     B

1002     C

1003     \0
```

Index

```
Index

0

1

2

3
```

Access

```c
str[0]
```

returns

```
A
```

---

# 9. Size of String

```c
char str[]="Hello";
```

strlen()

```c
strlen(str)
```

returns

```
5
```

sizeof()

```c
sizeof(str)
```

returns

```
6
```

Why?

Because sizeof counts

```
H
e
l
l
o
\0
```

Important Interview Question

| Function | Counts '\0'? |
|------------|-------------|
| strlen() | No |
| sizeof() | Yes (for arrays) |

---

# 10. Reading Strings

## scanf()

```c
scanf("%s",str);
```

Input

```
John Doe
```

Stored

```
John
```

Stops at space.

---

## fgets()

```c
fgets(str,sizeof(str),stdin);
```

Input

```
John Doe
```

Stored

```
John Doe
```

Reads spaces.

Preferred over scanf().

---

## gets()

```c
gets(str);
```

Never use.

Removed from C11.

Reason

Buffer overflow.

---

# 11. Printing Strings

```c
printf("%s",str);
```

Example

```c
char str[]="Hello";

printf("%s",str);
```

Output

```
Hello
```

Printing one character

```c
printf("%c",str[0]);
```

Output

```
H
```

---

# 12. Traversing Strings

Method 1

Using index

```c
for(int i=0;str[i]!='\0';i++)
{
    printf("%c",str[i]);
}
```

Output

```
H
e
l
l
o
```

---

Method 2

Using pointer

```c
char *p=str;

while(*p)
{
    printf("%c",*p);
    p++;
}
```

Same output.

---

# 13. char[] vs char*

## char[]

```c
char str[]="Hello";
```

Memory

```
Stack

+---+---+---+---+---+----+
| H | e | l | l | o | \0 |
+---+---+---+---+---+----+
```

Characteristics

- Owns memory
- Characters modifiable
- Array size fixed

---

## char*

```c
char *p=str;
```

Memory

```
p
|
v

+---+---+---+---+---+----+
| H | e | l | l | o | \0 |
+---+---+---+---+---+----+
```

Pointer only stores address.

Does not own memory.

---

Difference

| char[] | char* |
|---------|--------|
| Owns storage | Stores address |
| Fixed size | Can point elsewhere |
| sizeof gives array size | sizeof gives pointer size |

---

# 14. String Literals

```c
char *p="Hello";
```

Memory

```
Read Only Memory

Hello\0
```

Pointer

```
p

↓

Hello
```

Modern C

```c
const char *p="Hello";
```

is preferred.

---

# 15. Modifying Strings

Case 1

```c
char str[]="Hello";
```

Allowed

```c
str[0]='Y';
```

Output

```
Yello
```

---

Case 2

```c
char *p="Hello";
```

Not allowed

```c
p[0]='Y';
```

Undefined Behavior.

May crash.

---

Case 3

```c
const char *p="Hello";
```

Compiler prevents modification.

---

# 16. Pointer to String

```c
char str[]="Hello";

char *p=str;
```

Memory

```
p

↓

H e l l o \0
```

Access

```c
*p
```

Output

```
H
```

```c
*(p+1)
```

Output

```
e
```

---

# 17. Pointer Arithmetic

```c
char str[]="ABC";

char *p=str;
```

```
*p

A
```

```
*(p+1)

B
```

```
*(p+2)

C
```

Traversal

```c
while(*p)
{
    printf("%c",*p);
    p++;
}
```

---

# 18. const with Strings

## const char*

```c
const char *p="Hello";
```

Meaning

Characters cannot change.

Pointer can change.

Allowed

```c
p="World";
```

Not allowed

```c
p[0]='A';
```

---

## char *const

```c
char str[]="Hello";

char *const p=str;
```

Pointer cannot change.

Characters can.

Allowed

```c
p[0]='Y';
```

Not allowed

```c
char another[]="ABC";

p=another;
```

---

## const char *const

```c
const char *const p="Hello";
```

Neither pointer nor characters can change.

---

# 19. String Copy vs Pointer Copy

Pointer Copy

```c
char str[]="Hello";

char *p1=str;

char *p2=p1;
```

Memory

```
      p1
       |
       |
       v

H e l l o

       ^
       |
      p2
```

Both point to same memory.

Changing

```c
p2[0]='Y';
```

Output

```
Yello
```

---

String Copy

```c
char str[]="Hello";

char copy[20];

strcpy(copy,str);
```

Memory

```
str

Hello

copy

Hello
```

Independent copies.

Changing

```c
copy[0]='Y';
```

Output

```
str

Hello

copy

Yello
```

---

# 20. Shallow Copy vs Deep Copy

Shallow Copy

Copies address only.

```c
char *p2=p1;
```

Advantages

- Fast
- No extra memory

Disadvantages

- Shared data

---

Deep Copy

Copies actual characters.

```c
strcpy(copy,str);
```

Advantages

- Independent memory

Disadvantages

- Uses more memory

---

# 21. Summary

## Remember

✓ Every C string ends with `'\0'`

✓ `strlen()` ignores `'\0'`

✓ `sizeof()` includes `'\0'` for arrays

✓ `char[]` owns memory

✓ `char*` stores address

✓ Never modify string literals

✓ Use `const char*` for read-only strings

✓ Prefer `fgets()` over `scanf()` and never use `gets()`

✓ Arrays cannot be assigned directly

✓ Copy strings using `strcpy()`, not `=`

---

# What's Next?

Part 2 covers all important **`<string.h>` and `<ctype.h>` functions** in detail with:
- Syntax
- Memory diagrams
- Examples
- Time complexity
- Common interview questions
- Edge cases
```