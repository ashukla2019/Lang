# PART 19 — USER INPUT HANDLING

---

# Why Do We Need User Input?

Almost every C program interacts with users, files, sockets, or hardware.

Typical input sources are:

```text
Keyboard
Files
Network
Pipes
Serial Port
UART
```

Example:

```c
Enter age: 25
```

The program must safely read the input before processing it.

---

# User Input APIs

The standard C library provides several input functions.

```text
scanf()
fscanf()
sscanf()
fgets()
getline()
getchar()
ungetc()
```

Some older functions are dangerous.

```text
gets()   ← Removed from C11
```

---

# Choosing the Right Function

| Function | Reads From | Safe | Typical Use |
|-----------|------------|------|-------------|
| scanf() | stdin | ⚠ Depends | Simple formatted input |
| fscanf() | File | ✓ | Read formatted file |
| sscanf() | String | ✓ | Parse strings |
| fgets() | stdin/File | ✓ | Read a line |
| getline() | stdin/File | ✓✓ | Unknown length input |
| getchar() | stdin | ✓ | One character |
| ungetc() | stdin/File | ✓ | Push character back |
| strtol() | String | ✓✓ | Safe integer parsing |

---

# 1. scanf()

Reads formatted input from **stdin**.

Prototype

```c
int scanf(const char *format, ...);
```

Example

```c
#include <stdio.h>

int main(void)
{
    int age;

    printf("Enter age: ");

    scanf("%d", &age);

    printf("Age = %d\n", age);

    return 0;
}
```

Output

```
Enter age: 25
Age = 25
```

---

## Memory

Before input

```text
age

+------+
| ???? |
+------+
```

After input

```text
age

+------+
| 25   |
+------+
```

---

## Why "&" is Needed

Wrong

```c
int age;

scanf("%d", age);
```

Correct

```c
scanf("%d", &age);
```

Reason

```text
scanf()

needs

address

↓

stores data there
```

---

## Return Value

```c
int ret = scanf("%d", &age);
```

Return value

```text
1
```

means

One value successfully read.

```
0
```

means

Input doesn't match.

```
EOF
```

means

End of input or error.

Always check.

```c
if (scanf("%d", &age) != 1)
{
    printf("Invalid input\n");
}
```

---

# Reading Multiple Values

```c
int x, y;

scanf("%d %d", &x, &y);
```

Input

```
10 20
```

Result

```text
x = 10
y = 20
```

---

# Reading Different Types

```c
int age;
float salary;
char grade;

scanf("%d %f %c",
      &age,
      &salary,
      &grade);
```

Input

```
25
1200.5
A
```

---

# Width Specifiers

Without limit

```c
char name[10];

scanf("%s", name);
```

Problem

```
VeryLongNameHere
```

causes

```text
Buffer Overflow
```

Correct

```c
scanf("%9s", name);
```

Maximum

```text
9 characters

+

'\0'
```

---

# Why "%s" is Dangerous

```c
char name[5];

scanf("%s", name);
```

Input

```
Christopher
```

Memory

```text
+---+---+---+---+---+
| C | h | r | i | s |
+---+---+---+---+---+

continues writing...

↓

Buffer Overflow
```

This is one of the most common interview questions.

---

# Common scanf Mistakes

Wrong

```c
scanf("%d", age);
```

Wrong

```c
scanf("%f", value);
```

Wrong

```c
scanf("%s", buffer);
```

without width.

Wrong

Ignoring return value.

Correct

```c
if (scanf("%d", &age) != 1)
{
    /* Handle error */
}
```

---

# Interview Questions

Q. Why does scanf need "&"?

Answer

Because scanf stores data into variables.

It needs their addresses.

---

Q. Why is "%s" dangerous?

Answer

Because scanf does not know buffer size.

It may overflow.

Always specify width.

Example

```c
scanf("%31s", name);
```

---

Q. What does scanf return?

Answer

Number of successfully converted fields.

---

Q. Why should return value be checked?

Answer

To detect invalid input.

Example

```c
if(scanf("%d",&x)!=1)
```

---

# 2. fscanf()

Reads formatted data from a file.

Prototype

```c
int fscanf(FILE *stream,
           const char *format,
           ...);
```

Example

Suppose

```
data.txt

10
20
30
```

Program

```c
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("data.txt", "r");

    int value;

    while (fscanf(fp, "%d", &value) == 1)
    {
        printf("%d\n", value);
    }

    fclose(fp);
}
```

Output

```
10
20
30
```

---

# fscanf vs scanf

```text
scanf()

↓

stdin
```

```
fscanf()

↓

FILE *
```

Everything else works similarly.

---

# 3. sscanf()

Reads formatted data from a string.

Prototype

```c
int sscanf(const char *str,
           const char *format,
           ...);
```

Example

```c
#include <stdio.h>

int main(void)
{
    char str[] = "100 200";

    int a;
    int b;

    sscanf(str,
           "%d %d",
           &a,
           &b);

    printf("%d %d\n",
           a,
           b);
}
```

Output

```
100 200
```

---

# Why sscanf() is Useful

Instead of reading directly

```text
Keyboard

↓

scanf()
```

You can

```text
Read line

↓

Parse

↓

Validate
```

Example

```c
char line[100];

fgets(line,
      sizeof(line),
      stdin);

int age;

if(sscanf(line,"%d",&age)==1)
{
    printf("Valid\n");
}
else
{
    printf("Invalid\n");
}
```

This is considered much safer than using scanf() directly.

---

# Interview Questions

Q. Difference between scanf and sscanf?

Answer

```text
scanf()

↓

stdin

sscanf()

↓

String
```

Useful for parsing configuration files, CSV data, command-line input, and network messages.

---

# Summary

| Function | Source |
|-----------|--------|
| scanf() | stdin |
| fscanf() | File |
| sscanf() | String |
