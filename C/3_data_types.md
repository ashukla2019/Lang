# Understanding C Data Types
# long, long long, float, double - Complete Notes

---

# Why Do We Need Different Data Types?

A computer stores everything in **bits (0s and 1s)**.

Different data types exist because different kinds of data require different:

- Memory
- Precision
- Range
- Performance

Example

```c
int age = 25;
float salary = 35000.75;
char grade = 'A';
```

An age doesn't need decimal places.

A salary may need decimals.

Hence different data types.

---

# Integer Family

The integer family stores **whole numbers**.

```
char

short

int

long

long long
```

As we move downward

```
Larger Range

↓

More Memory
```

---

# int

The most commonly used integer type.

```c
int x = 100;
```

Typical size

```
4 bytes
```

Range (32-bit)

```
-2,147,483,648

to

2,147,483,647
```

Memory

```
+--------+--------+--------+--------+
| Byte 1 | Byte 2 | Byte 3 | Byte 4 |
+--------+--------+--------+--------+
```

Suitable for

- Age
- Count
- Marks
- Array index

---

# Why long?

Suppose you want to store

```
5,000,000,000
```

Can int store it?

```
No
```

Because maximum int is

```
2,147,483,647
```

So C provides

```
long
```

Example

```c
long population = 5000000000L;
```

The suffix

```
L
```

means

```
Long Integer
```

Typical size

```
Linux (64-bit)

8 bytes

--------------------

Windows

4 bytes
```

Always check

```c
printf("%zu", sizeof(long));
```

---

# Why long long?

Sometimes even long is not enough (or for portability across platforms).

Example

```
Number of stars

Scientific calculations

Database IDs

File sizes

Nanoseconds
```

Example

```c
long long distance = 9876543212345LL;
```

Suffix

```
LL
```

means

```
Long Long
```

Typical size

```
8 bytes
```

Range

```
-9,223,372,036,854,775,808

to

9,223,372,036,854,775,807
```

Huge range.

---

# Comparison

| Type | Typical Size | Approx Range |
|------|--------------|--------------|
| short | 2 Bytes | ±32 Thousand |
| int | 4 Bytes | ±2 Billion |
| long | 4 or 8 Bytes | Platform dependent |
| long long | 8 Bytes | ±9 Quintillion |

---

# Why float?

Integers cannot store decimals.

Example

```c
int x = 3.14;
```

Output

```
3
```

Decimal lost.

Need

```
float
```

Example

```c
float pi = 3.14f;
```

Notice

```
f
```

Without it

```c
3.14
```

is considered

```
double
```

---

# float Memory

Typical size

```
4 Bytes
```

IEEE 754 representation

```
+--------+------------+-----------------------+
| Sign   | Exponent   | Fraction (Mantissa)  |
+--------+------------+-----------------------+

1 bit      8 bits          23 bits
```

You don't need to memorize the bit layout for most interviews, but know that a float stores:

- Sign
- Exponent
- Fraction (Mantissa)

---

# Float Precision

A float stores about

```
6-7 decimal digits
```

Example

```c
float x = 123456789.123f;

printf("%f", x);
```

Output

```
123456792.000000
```

Why?

Not enough precision.

---

# Why double?

Need higher precision.

Example

```c
double pi = 3.141592653589793;
```

Size

```
8 Bytes
```

Precision

```
15-16 decimal digits
```

Memory

```
+--------+-------------+------------------------+
| Sign   | Exponent    | Fraction              |
+--------+-------------+------------------------+

1 bit      11 bits         52 bits
```

---

# long double

Even higher precision.

```c
long double x = 3.141592653589793238462L;
```

Size

Depends on compiler

Usually

```
16 Bytes

or

12 Bytes

or

8 Bytes
```

---

# Comparison

| Type | Size | Precision |
|------|------|-----------|
| float | 4 Bytes | 6-7 digits |
| double | 8 Bytes | 15-16 digits |
| long double | 12/16 Bytes | 18+ digits |

---

# Why Not Always Use double?

Because

- More memory
- Slightly slower on some embedded systems
- Large arrays consume more RAM

Example

```
1 Million floats

≈4 MB

----------------

1 Million doubles

≈8 MB
```

Twice the memory.

---

# Integer vs Float

```c
int a = 5;
int b = 2;

printf("%d", a/b);
```

Output

```
2
```

Because integer division.

Now

```c
float a = 5;
float b = 2;

printf("%f", a/b);
```

Output

```
2.500000
```

---

# Mixing Types

```c
int a = 5;

float b = 2.5;

printf("%f", a+b);
```

Output

```
7.500000
```

Compiler converts

```
int

↓

float
```

Automatically.

---

# Type Promotion

```c
int a = 5;

double b = 2.5;

double c = a+b;
```

Memory

```
int

↓

double

↓

Addition
```

The smaller type is promoted.

---

# Literal Suffixes

```
100

int
```

```
100L

long
```

```
100LL

long long
```

```
3.14

double
```

```
3.14f

float
```

```
3.14L

long double
```

---

# sizeof()

Always verify sizes on your platform.

```c
printf("%zu\n", sizeof(short));

printf("%zu\n", sizeof(int));

printf("%zu\n", sizeof(long));

printf("%zu\n", sizeof(long long));

printf("%zu\n", sizeof(float));

printf("%zu\n", sizeof(double));

printf("%zu\n", sizeof(long double));
```

Possible Linux Output

```
short       2

int         4

long        8

long long   8

float       4

double      8

long double 16
```

---

# When Should You Use What?

Use **int**

- Loop counters
- Age
- Marks
- Number of students

Use **long**

- Large file sizes
- Population
- Large counters

Use **long long**

- Nanoseconds
- Database IDs
- Scientific values
- Huge counts

Use **float**

- Graphics
- Games
- Sensors
- Embedded systems

Use **double**

- Scientific calculations
- Finance
- Engineering
- Mathematical computations

Use **long double**

- High-precision scientific applications
- Numerical analysis

---

# Interview Questions

### Why is `long` sometimes 4 bytes and sometimes 8 bytes?

The C standard specifies **minimum ranges**, not exact sizes. The actual size depends on the platform's data model (e.g., LP64 on Linux, LLP64 on Windows).

---

### Why use `long long` instead of `long`?

`long long` is guaranteed to be **at least 64 bits**, making it more portable for storing very large integers.

---

### Why use `float` instead of `double`?

`float` uses half the memory of `double` and is often sufficient for graphics, games, and embedded systems where memory and performance are important.

---

### Why can't `float` represent every decimal exactly?

Floating-point numbers are stored in **binary (IEEE 754 format)**. Many decimal fractions (like 0.1) cannot be represented exactly in binary, so they are stored as approximations.

---

# Key Takeaways

- `int` stores whole numbers and is the default integer type.
- `long` extends the integer range but its size is platform-dependent.
- `long long` is guaranteed to be at least 64 bits and is used for very large integers.
- `float` stores decimal values with about **6–7 digits** of precision.
- `double` stores decimal values with about **15–16 digits** of precision.
- `long double` provides even higher precision where supported.
- Use suffixes (`L`, `LL`, `f`) to indicate the intended literal type.
- Use `sizeof()` to determine the actual size of types on your platform.