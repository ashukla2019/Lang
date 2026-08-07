# C Pointers and Arrays – Consolidated Notes

## 1. What is a Pointer?

A pointer stores the **address** of another variable.

```c
int x = 10;
int *p = &x;
```

Memory:

```
x
+----+
| 10 |
+----+
  ^
  |
  p
```

- `p` stores the address of `x`.
- `*p` gives the value stored at that address (`10`).

---

# 2. `char *` pointing to a single character

```c
char ch = 'A';
char *p = &ch;
```

Memory:

```
ch
+-----+
| 'A' |
+-----+
  ^
  |
  p
```

Access:

```c
printf("%c", *p);   // A
```

Here, `p` points to exactly one character.

---

# 3. `char *` pointing to a string

A string is simply an array of characters ending with `'\0'`.

```c
char str[] = "Hello";
char *p = str;
```

Equivalent to:

```c
char *p = &str[0];
```

Memory:

```
str

+---+---+---+---+---+----+
| H | e | l | l | o | \0 |
+---+---+---+---+---+----+
  ^
  |
  p
```

Access:

```c
*p        // H
*(p+1)    // e
*(p+2)    // l

printf("%s", p);   // Hello
```

### Important

`char *` does **not** point to the whole string.

It points only to the **first character**.

`printf("%s", p)` prints the whole string because it keeps reading characters until it finds `'\0'`.

---

# 4. `int *` pointing to a single integer

```c
int num = 100;
int *p = &num;
```

Memory:

```
+------+
| 100  |
+------+
   ^
   |
   p
```

Access:

```c
*p
```

Output:

```
100
```

---

# 5. `int *` pointing to an integer array

```c
int arr[] = {10,20,30,40};

int *p = arr;
```

Equivalent to

```c
int *p = &arr[0];
```

Memory:

```
+----+----+----+----+
|10  |20  |30  |40  |
+----+----+----+----+
  ^
  |
  p
```

Access:

```c
*p          //10
*(p+1)      //20
*(p+2)      //30
*(p+3)      //40
```

---

# 6. Does `int *` point to an array?

Technically,

**No.**

An `int *` points to **one integer**.

When you assign

```c
int *p = arr;
```

the array name automatically converts (decays) into the address of its first element.

So,

```c
int *p = arr;
```

is exactly the same as

```c
int *p = &arr[0];
```

People often say

> "`int *` points to an array"

What they actually mean is

> "`int *` points to the first element of the array."

---

# 7. Pointer to an Array

Instead of pointing to one element, you can point to the **entire array**.

Example:

```c
int arr[4]={10,20,30,40};

int (*q)[4] = &arr;
```

Read this declaration as

```
q
↓

Pointer
   to
Array of 4 integers
```

Memory:

```
q
|
v

+----+----+----+----+
|10  |20  |30  |40  |
+----+----+----+----+
```

---

# 8. Accessing elements using pointer-to-array

Since `q` points to the whole array,

```c
*q
```

means

```
the whole array
```

Now index it:

```c
(*q)[0]    //10
(*q)[1]    //20
(*q)[2]    //30
(*q)[3]    //40
```

Notice the parentheses.

Without them,

```c
*q[0]
```

means something different.

---

# 9. Pointer arithmetic difference

## `int *`

```c
int *p;
```

`p+1`

moves by

```
sizeof(int)
```

Example

```
10 → 20 → 30 → 40
```

---

## `int (*q)[4]`

```c
int (*q)[4];
```

`q+1`

moves by

```
sizeof(int[4])
```

which is one entire row.

---

# 10. Most common use of pointer-to-array

2D arrays.

Example

```c
int matrix[3][4]={
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12}
};

int (*p)[4]=matrix;
```

Access:

```c
p[0][0]    //1
p[0][2]    //3

p[1][0]    //5
p[2][3]    //12
```

Here

```
p+1
```

moves to the next row.

---

# 11. Pointer-to-array with characters

## Normal string pointer

```c
char str[]="Hello";

char *p=str;
```

Memory

```
H e l l o \0
^
|
p
```

Access

```c
p[0]
p[1]
p[2]
```

---

## Pointer to character array

```c
char arr[5]={'H','e','l','l','o'};

char (*q)[5]=&arr;
```

Access

```c
(*q)[0]
(*q)[1]
(*q)[4]
```

Again,

`q` points to the **whole array**, not just one character.

---

# 12. Pointer-to-array with array of strings

Example

```c
char names[3][10]={
    "Tom",
    "John",
    "Alex"
};

char (*p)[10]=names;
```

Memory

```
+------------+
|Tom         |
+------------+
|John        |
+------------+
|Alex        |
+------------+
```

Access

```c
printf("%s", p[0]);   //Tom

printf("%s", p[1]);   //John

printf("%s", p[2]);   //Alex
```

Here,

`p+1`

moves to the next row (next string), **not** the next character.

---

# Summary Table

| Declaration | Meaning |
|------------|---------|
| `int *p` | Pointer to one integer |
| `char *p` | Pointer to one character |
| `int (*p)[4]` | Pointer to an array of 4 integers |
| `char (*p)[5]` | Pointer to an array of 5 characters |
| `int arr[4]` | Array of 4 integers |
| `char str[6]` | Array of 6 characters |

---

# Key Takeaways

- A pointer stores an address.
- `char *` points to one character.
- `int *` points to one integer.
- When an array name is assigned to a pointer, it **decays into the address of its first element**.
- `int *` does **not** point to an array; it points to the first element.
- `int (*p)[4]` points to the **entire array**.
- Pointer-to-array is mainly used with **2D arrays** and functions that process rows of arrays.
- The same concepts apply to both `int` arrays and `char` arrays.
