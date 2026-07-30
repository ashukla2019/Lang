# Chapter 8 – Bit Manipulation
# Part 1 – Bit Fundamentals

---

# Contents

1. Why Bit Manipulation?
2. What is a Bit?
3. Bits, Nibbles, Bytes and Words
4. Number Systems
5. Binary ↔ Decimal Conversion
6. Binary ↔ Hexadecimal Conversion
7. Binary Arithmetic
8. Signed vs Unsigned Integers
9. One's Complement
10. Two's Complement
11. Most Significant Bit (MSB) and Least Significant Bit (LSB)
12. Integer Memory Representation
13. Endianness
14. Checking Machine Endianness
15. Interview Questions
16. Key Takeaways

---

# 1. Why Bit Manipulation?

Bit manipulation is one of the most important topics for:

- Qualcomm
- NVIDIA
- AMD
- Intel
- Broadcom
- Samsung
- Apple Silicon
- Linux Kernel
- Embedded Systems
- Device Drivers
- Networking
- Firmware

Almost every hardware register, interrupt controller, DMA engine, timer, GPIO controller, and communication peripheral is controlled by manipulating individual bits.

Example

Suppose a hardware register is

```
00000101
```

Bit 0

```
Enable UART
```

Bit 2

```
Enable DMA
```

Instead of changing the entire register, we modify only the required bits.

This is exactly what bit manipulation is used for.

---

# 2. What is a Bit?

A **bit (Binary Digit)** is the smallest unit of information in a computer.

A bit can contain only one of two values.

```
0

or

1
```

Everything inside a computer is represented using bits.

Examples

```
Characters

Integers

Floating point numbers

Pointers

Instructions

Images

Videos
```

Everything eventually becomes

```
010101001011001...
```

---

# 3. Bits, Nibbles, Bytes and Words

## Bit

Smallest storage unit.

```
0

or

1
```

---

## Nibble

```
4 Bits
```

Example

```
1101
```

One hexadecimal digit represents one nibble.

Example

```
A

↓

1010
```

---

## Byte

```
8 Bits
```

Example

```
10101100
```

One byte can represent

```
2⁸

=

256

different values.
```

---

## Word

A word is the natural data size processed by a CPU.

Examples

| Processor | Word Size |
|------------|-----------|
| 8-bit MCU | 8 bits |
| 16-bit MCU | 16 bits |
| 32-bit ARM | 32 bits |
| 64-bit x86 | 64 bits |

Interview Note

A **word** is CPU-dependent.

A byte is always 8 bits on modern systems.

---

## Double Word (DWORD)

```
32 bits
```

---

## Quad Word (QWORD)

```
64 bits
```

---

# 4. Number Systems

Humans use

```
Decimal

(Base 10)
```

Computers use

```
Binary

(Base 2)
```

Programmers commonly use

```
Hexadecimal

(Base 16)
```

Older systems sometimes use

```
Octal

(Base 8)
```

---

# Decimal Number System

Digits

```
0-9
```

Example

```
527
```

Meaning

```
5 × 10²

+

2 × 10¹

+

7 × 10⁰

=

527
```

---

# Binary Number System

Digits

```
0

1
```

Example

```
1101₂
```

Calculation

```
1 × 2³

+

1 × 2²

+

0 × 2¹

+

1 × 2⁰

=

13
```

---

# Hexadecimal

Digits

```
0-9

A

B

C

D

E

F
```

Values

```
A = 10

B = 11

C = 12

D = 13

E = 14

F = 15
```

---

# Why Hexadecimal?

Compare

Binary

```
1111111110101010
```

Hex

```
FFAA
```

Hex is easier to read and is used extensively in:

- Debuggers
- Memory dumps
- Registers
- Memory addresses
- Embedded systems

---

# 5. Binary ↔ Decimal Conversion

## Binary to Decimal

Example

```
101101
```

Weights

```
32

16

8

4

2

1
```

Calculation

```
1×32

+

0×16

+

1×8

+

1×4

+

0×2

+

1×1
```

Answer

```
45
```

---

## Another Example

```
11101010
```

Calculation

```
128

+

64

+

32

+

8

+

2

=

234
```

---

## Decimal to Binary

Method

Repeatedly divide by 2.

Example

Convert

```
25
```

```
25 /2 =12 R1

12 /2 =6 R0

6 /2 =3 R0

3 /2 =1 R1

1 /2 =0 R1
```

Read from bottom

```
11001
```

Therefore

```
25

↓

11001₂
```

---

# Quick Practice

| Decimal | Binary |
|----------|---------|
| 5 | 101 |
| 8 | 1000 |
| 10 | 1010 |
| 15 | 1111 |
| 20 | 10100 |
| 32 | 100000 |

---

# 6. Binary ↔ Hexadecimal Conversion

Rule

```
Group binary into 4 bits
```

Example

```
11010111
```

Split

```
1101

0111
```

Convert

```
1101

↓

D
```

```
0111

↓

7
```

Answer

```
D7
```

---

## Hex to Binary

Example

```
3A
```

```
3

↓

0011
```

```
A

↓

1010
```

Answer

```
00111010
```

---

## Hex Conversion Table

| Binary | Hex |
|----------|-----|
|0000|0|
|0001|1|
|0010|2|
|0011|3|
|0100|4|
|0101|5|
|0110|6|
|0111|7|
|1000|8|
|1001|9|
|1010|A|
|1011|B|
|1100|C|
|1101|D|
|1110|E|
|1111|F|

**Interview Tip:** Memorize this table.

---

# 7. Binary Arithmetic

## Binary Addition

Example

```
  1010
+ 0011
------
  1101
```

Decimal

```
10

+

3

=

13
```

---

## Binary Addition with Carry

```
 1111
+0001
-----
10000
```

---

## Binary Subtraction

Example

```
1000

-

0011

=

0101
```

Decimal

```
8

-

3

=

5
```

---

# 8. Signed vs Unsigned Integers

Both occupy the same memory.

Difference is **how the bits are interpreted**.

---

## Unsigned Integer

Example

```
8-bit

11111111
```

Value

```
255
```

Range

```
0

↓

255
```

Formula

```
0

↓

2ⁿ−1
```

---

## Signed Integer

Uses **Two's Complement** representation.

MSB is interpreted as the sign.

```
0

↓

Positive
```

```
1

↓

Negative
```

Range

```
-128

↓

127
```

for an 8-bit integer.

Formula

```
-(2ⁿ⁻¹)

↓

2ⁿ⁻¹−1
```

---

## Example

```
00000101

↓

+5
```

```
11111011

↓

-5
```

(using two's complement)

---

# 9. One's Complement

One's complement is obtained by flipping every bit.

Example

```
00001101
```

becomes

```
11110010
```

Problem

There are two representations of zero.

```
00000000

+

11111111
```

Because of this ambiguity, modern computers do **not** use one's complement for signed integers.

---

# 10. Two's Complement

Two's complement is the standard representation for signed integers.

To obtain the negative of a number:

Step 1

Invert all bits.

Step 2

Add 1.

Example

```
5

↓

00000101
```

Invert

```
11111010
```

Add 1

```
11111011
```

This represents

```
-5
```

---

## Why Two's Complement?

Advantages

- Only one representation of zero
- Simplifies hardware design
- Addition and subtraction use the same circuitry
- No special handling for negative numbers

This is why virtually every modern CPU uses two's complement.

---

# 11. Most Significant Bit (MSB) and Least Significant Bit (LSB)

Consider

```
10110110
```

Bit positions

```
7 6 5 4 3 2 1 0
```

---

## MSB

```
10110110

^

Bit 7
```

Uses

- Highest value bit
- Sign bit in signed integers
- Overflow detection

---

## LSB

```
10110110

       ^

      Bit 0
```

Uses

- Odd/Even detection
- Bit masking
- Hardware flags

---

## Odd / Even Trick

Even

```
1010

↓

LSB = 0
```

Odd

```
1011

↓

LSB = 1
```

Code

```c
if(num & 1)
    printf("Odd");
else
    printf("Even");
```

This is one of the most common bit interview questions.

---

# 12. Integer Memory Representation

Suppose

```c
int x = 25;
```

Binary

```
00000000 00000000 00000000 00011001
```

On a 32-bit integer

```
Byte 3

00000000

Byte 2

00000000

Byte 1

00000000

Byte 0

00011001
```

The order these bytes are stored depends on **endianness**.

---

# 13. Endianness

Endianness determines the order in which bytes are stored in memory.

---

## Little Endian

Least significant byte stored first.

Value

```
0x12345678
```

Memory

```
Address

100

101

102

103
```

Contents

```
78

56

34

12
```

Used by

- x86
- x86-64
- Most ARM systems (default)

---

## Big Endian

Most significant byte stored first.

Memory

```
Address

100

101

102

103
```

Contents

```
12

34

56

78
```

Used in

- Some networking protocols
- Some embedded processors
- Historical architectures

---

## Network Byte Order

Network protocols use

```
Big Endian
```

Functions like

```c
htonl()
htons()
ntohl()
ntohs()
```

convert between host byte order and network byte order.

---

# 14. Program to Check Endianness

```c
#include <stdio.h>

int main()
{
    unsigned int x = 1;

    char *p = (char *)&x;

    if(*p == 1)
        printf("Little Endian\n");
    else
        printf("Big Endian\n");

    return 0;
}
```

### Explanation

Memory for `x = 1` (32-bit)

```
00000000 00000000 00000000 00000001
```

Little Endian

```
Lowest Address

↓

01 00 00 00
```

`p` points to the first byte.

```
*p == 1
```

Therefore

```
Little Endian
```

---

# Frequently Asked Interview Questions

### Q1. Why is hexadecimal preferred over binary?

Because it is much shorter and each hexadecimal digit represents exactly four binary bits.

---

### Q2. Why do modern CPUs use two's complement?

- Single representation of zero
- Easier arithmetic
- Simpler hardware implementation

---

### Q3. Difference between signed and unsigned integers?

Unsigned uses all bits for the value.

Signed uses two's complement to represent both positive and negative values.

---

### Q4. What is the range of an unsigned 8-bit integer?

```
0

↓

255
```

---

### Q5. What is the range of a signed 8-bit integer?

```
-128

↓

127
```

---

### Q6. How do you determine whether a number is odd or even?

```c
num & 1
```

---

### Q7. What is endianness?

It defines the order in which bytes are stored in memory.

---

### Q8. Which endianness does x86 use?

Little Endian.

---

### Q9. What is network byte order?

Big Endian.

---

# Key Takeaways

- A **bit** stores either `0` or `1`.
- A **byte** consists of **8 bits**.
- Binary is **base 2**; hexadecimal is **base 16**.
- One hexadecimal digit corresponds to **4 binary bits**.
- Modern CPUs represent signed integers using **two's complement**.
- The **MSB** is the highest-order bit; the **LSB** is the lowest-order bit.
- `num & 1` is the standard and efficient way to check if a number is odd or even.
- Endianness affects **byte order in memory**, not the value of the integer itself.
- Most desktop and server CPUs today are **little-endian**, while network protocols use **big-endian** byte order.
-------------------------------------------------------------------------------------
# Chapter 8 – Bit Manipulation
# Part 2 – Bitwise Operators

---

# Contents

1. Introduction to Bitwise Operators
2. Bitwise AND (&)
3. Bitwise OR (|)
4. Bitwise XOR (^)
5. Bitwise NOT (~)
6. Left Shift (<<)
7. Right Shift (>>)
8. Arithmetic vs Logical Shift
9. Operator Precedence
10. Common Interview Questions
11. Key Takeaways

---

# 1. Introduction to Bitwise Operators

Bitwise operators work **directly on the binary representation** of numbers.

Unlike arithmetic operators, they operate **bit-by-bit**.

C provides six bitwise operators.

| Operator | Name |
|-----------|------|
| & | AND |
| \| | OR |
| ^ | XOR |
| ~ | NOT |
| << | Left Shift |
| >> | Right Shift |

These operators are heavily used in:

- Embedded Systems
- Device Drivers
- Linux Kernel
- Networking
- Hardware Register Programming
- Compression
- Cryptography

---

# Binary Refresher

Consider

```
13
```

Binary

```
00001101
```

Another number

```
10
```

Binary

```
00001010
```

We'll use these numbers throughout this chapter.

---

# 2. Bitwise AND (&)

## Definition

AND returns **1 only if both bits are 1**.

Truth Table

| A | B | A & B |
|---|---|-------|
|0|0|0|
|0|1|0|
|1|0|0|
|1|1|1|

---

## Example

```
13 & 10
```

Binary

```
13

00001101

10

00001010

----------------

00001000
```

Result

```
8
```

---

## Why?

```
1 & 1 = 1

Everything else = 0
```

---

## Common Uses

### Check Whether a Bit is Set

```c
if(num & (1 << n))
{
    printf("Bit is set");
}
```

---

### Masking

Suppose

```
Register

10110110
```

Need only lower four bits.

Mask

```
00001111
```

```
10110110

&

00001111

------------

00000110
```

Upper bits become zero.

---

### Check Odd or Even

```c
if(num & 1)
```

Reason

```
Even

↓

Last bit = 0
```

```
Odd

↓

Last bit = 1
```

---

# 3. Bitwise OR (|)

## Definition

OR returns **1 if either bit is 1**.

Truth Table

|A|B|A \| B|
|---|---|------|
|0|0|0|
|0|1|1|
|1|0|1|
|1|1|1|

---

## Example

```
13 | 10
```

Binary

```
13

00001101

10

00001010

--------------

00001111
```

Result

```
15
```

---

## Common Uses

### Set a Bit

Need to set bit 2.

```c
num |= (1 << 2);
```

Example

Before

```
00000001
```

Mask

```
00000100
```

Result

```
00000101
```

Bit becomes set.

---

### Enable Hardware Features

Example

```c
UART_CTRL |= UART_ENABLE;
```

Only the required bit changes.

Everything else remains unchanged.

---

# 4. Bitwise XOR (^)

## Definition

XOR returns **1 only when the bits are different**.

Truth Table

|A|B|A ^ B|
|---|---|------|
|0|0|0|
|0|1|1|
|1|0|1|
|1|1|0|

---

## Example

```
13 ^ 10
```

Binary

```
13

00001101

10

00001010

--------------

00000111
```

Result

```
7
```

---

# Important XOR Properties

## Property 1

```
A ^ 0 = A
```

Example

```
1010

^

0000

=

1010
```

---

## Property 2

```
A ^ A = 0
```

Example

```
1010

^

1010

=

0000
```

---

## Property 3

```
A ^ B ^ A

=

B
```

Because

```
A ^ A = 0
```

---

## Property 4

XOR is commutative.

```
A ^ B

=

B ^ A
```

---

## Property 5

XOR is associative.

```
A ^ (B ^ C)

=

(A ^ B) ^ C
```

These properties are extremely useful in interview problems.

---

## Common Uses

### Toggle a Bit

```c
num ^= (1 << n);
```

If bit is

```
0

↓

1
```

If bit is

```
1

↓

0
```

---

### Swap Without Temporary Variable

```c
a ^= b;
b ^= a;
a ^= b;
```

Example

```
a = 5

b = 8
```

After execution

```
a = 8

b = 5
```

**Interview Note**

This works, but using a temporary variable is generally preferred today because it is easier to read and modern compilers optimize it well.

---

### Find Unique Number

Array

```
5 4 2 4 5
```

Perform XOR.

```
5 ^ 5 = 0

4 ^ 4 = 0

Remaining

2
```

Answer

```
2
```

Very common interview question.

---

# 5. Bitwise NOT (~)

## Definition

NOT flips every bit.

```
0

↓

1
```

```
1

↓

0
```

---

## Example

8-bit

```
00001101
```

After NOT

```
11110010
```

---

## Example in C

```c
int x = 5;

printf("%d", ~x);
```

Output

```
-6
```

Why?

Because C uses **two's complement** representation.

---

### Step-by-Step

```
5

00000101
```

Invert

```
11111010
```

This bit pattern represents

```
-6
```

---

## Common Uses

### Clear Bits

```c
num &= ~(1 << n);
```

---

### Create Masks

```c
~0U
```

Produces

```
11111111111111111111111111111111
```

(all bits set for an unsigned integer)

---

# 6. Left Shift (<<)

## Definition

Left shift moves bits to the left.

Zeros are inserted from the right.

Example

```
5 << 1
```

Binary

```
00000101

↓

00001010
```

Result

```
10
```

---

Another Example

```
5 << 2
```

```
00000101

↓

00010100
```

Result

```
20
```

---

## Multiplication by Powers of Two

```
x << n

=

x × 2ⁿ
```

Examples

```
6 << 1

=

12
```

```
6 << 2

=

24
```

---

## Overflow

Example

```
11110000

<<1

=

11100000
```

The leftmost bit is discarded.

---

## Interview Note

Left shifting a **signed integer** so that the result cannot be represented by its type results in **undefined behavior**.

Prefer unsigned integers for bit manipulation.

---

# 7. Right Shift (>>)

## Definition

Moves bits toward the right.

---

Example

```
20 >> 1
```

Binary

```
00010100

↓

00001010
```

Result

```
10
```

---

Another Example

```
20 >> 2
```

Binary

```
00010100

↓

00000101
```

Result

```
5
```

---

## Division by Powers of Two

For non-negative integers,

```
x >> n

=

x / 2ⁿ
```

Examples

```
40 >> 3

=

5
```

---

## Caution

For **negative signed integers**, right shift behavior is **implementation-defined**.

Do not assume all compilers behave the same.

---

# 8. Arithmetic vs Logical Shift

One of the most common interview questions.

---

## Logical Right Shift

Fill new bits with zero.

Example

```
10110000

>>

1

↓

01011000
```

Typically used for **unsigned** integers.

---

## Arithmetic Right Shift

Copies the sign bit (MSB).

Positive

```
00010100

>>

1

↓

00001010
```

Negative

```
11110100

>>

1

↓

11111010
```

Most modern compilers perform arithmetic right shift for signed integers, but the C standard leaves this implementation-defined.

---

# Left Shift vs Right Shift

| Left Shift | Right Shift |
|------------|-------------|
|Moves bits left|Moves bits right|
|Zeros inserted from right|Behavior depends on type|
|Approximate multiplication by 2ⁿ|Approximate division by 2ⁿ (non-negative values)|

---

# 9. Operator Precedence

Many interview bugs happen because of precedence.

Example

```c
if(num & 1 == 0)
```

Is interpreted as

```c
num & (1 == 0)
```

NOT

```c
(num & 1) == 0
```

Correct code

```c
if((num & 1) == 0)
```

Always use parentheses.

---

Another Example

Wrong

```c
value = a << b + 1;
```

Actual interpretation

```c
value = a << (b + 1);
```

If your intention is different, add parentheses.

---

# Common Interview Questions

### Q1. Why is `num & 1` used to check odd/even?

The least significant bit is:

```
0 → Even

1 → Odd
```

---

### Q2. Difference between `&` and `&&`?

| & | && |
|---|----|
|Bitwise operator|Logical operator|
|Works on bits|Works on boolean expressions|
|Evaluates both operands|Short-circuits if first operand is false|

---

### Q3. Difference between `|` and `||`?

| \| | \|\| |
|-----|------|
|Bitwise OR|Logical OR|
|Operates on bits|Operates on boolean expressions|
|Evaluates both operands|Short-circuits if first operand is true|

---

### Q4. Why is XOR useful?

Because:

```
A ^ A = 0

A ^ 0 = A
```

Useful for:

- Finding unique elements
- Toggling bits
- Checksums
- Error detection

---

### Q5. Why shouldn't signed integers be used for heavy bit manipulation?

Because shifting signed integers can produce **undefined** or **implementation-defined** behavior.

Prefer

```c
unsigned int
```

or fixed-width unsigned types such as

```c
uint32_t
```

---

### Q6. What is the difference between arithmetic and logical right shift?

Logical shift inserts zeros.

Arithmetic shift preserves the sign bit.

---

# Key Takeaways

- `&` is used for **masking**, checking bits, and testing odd/even.
- `|` is used to **set bits** without affecting other bits.
- `^` is used for **toggling bits**, XOR tricks, and finding unique elements.
- `~` flips every bit and is commonly used for creating masks and clearing bits.
- `<<` shifts bits left and approximates multiplication by powers of two for values that remain representable.
- `>>` shifts bits right and approximates division by powers of two for non-negative values.
- Always use **parentheses** with bitwise expressions to avoid precedence bugs.
- For portable bit manipulation code, prefer **unsigned integer types**.
- ------------------------------------------------------------------------------
# Chapter 8 – Bit Manipulation
# Part 3 – Common Bit Manipulation Techniques

---

# Contents

1. Introduction
2. Set nth Bit
3. Clear nth Bit
4. Toggle nth Bit
5. Check nth Bit
6. Update nth Bit
7. Check Odd or Even
8. Count Number of Set Bits
9. Brian Kernighan Algorithm
10. Built-in Bit Functions
11. Check Power of Two
12. Check Power of Four
13. Isolate Rightmost Set Bit
14. Clear Rightmost Set Bit
15. Set Rightmost Unset Bit
16. Count Leading Zeros
17. Count Trailing Zeros
18. Reverse Bits
19. Rotate Bits
20. Swap Odd and Even Bits
21. Common Interview Questions
22. Key Takeaways

---

# 1. Introduction

Most semiconductor interviews do **not** ask about the operators themselves.

Instead, they ask problems like:

- Set bit 5
- Clear bit 7
- Is bit 3 set?
- Count set bits
- Find the only unique number
- Check power of two
- Reverse bits
- Rotate bits

These questions are solved using a few standard bit manipulation techniques.

---

# Bit Numbering

Assume

```
Number = 45

Binary

00101101
```

```
Bit Position

7 6 5 4 3 2 1 0

0 0 1 0 1 1 0 1
```

Bit numbering always starts from **0** at the least significant bit.

---

# 2. Set nth Bit

## Problem

Set bit **n** to **1**.

If the bit is already 1, it remains unchanged.

---

## Formula

```c
num |= (1U << n);
```

---

## Example

```
num = 8

00001000
```

Set bit 1

Mask

```
00000010
```

Operation

```
00001000

|

00000010

------------

00001010
```

Result

```
10
```

---

## Complete Program

```c
unsigned int setBit(unsigned int num, int n)
{
    return num | (1U << n);
}
```

Complexity

```
Time  : O(1)

Space : O(1)
```

---

# 3. Clear nth Bit

## Problem

Set bit **n** to **0**.

---

## Formula

```c
num &= ~(1U << n);
```

---

## Example

```
num = 13

00001101
```

Clear bit 2

Mask

```
00000100

↓

NOT

11111011
```

Operation

```
00001101

&

11111011

------------

00001001
```

Result

```
9
```

---

## Complete Program

```c
unsigned int clearBit(unsigned int num, int n)
{
    return num & ~(1U << n);
}
```

---

# 4. Toggle nth Bit

## Problem

If bit is

```
0

↓

1
```

If bit is

```
1

↓

0
```

---

## Formula

```c
num ^= (1U << n);
```

---

## Example

```
10

00001010
```

Toggle bit 1

```
00001010

^

00000010

------------

00001000
```

Result

```
8
```

---

## Program

```c
unsigned int toggleBit(unsigned int num, int n)
{
    return num ^ (1U << n);
}
```

---

# 5. Check nth Bit

## Formula

```c
if(num & (1U << n))
```

or

```c
((num >> n) & 1U)
```

---

## Example

```
13

00001101
```

Check bit 2

```
00001101

&

00000100

------------

00000100
```

Non-zero

Bit is set.

---

## Program

```c
int isBitSet(unsigned int num, int n)
{
    return (num & (1U << n)) != 0;
}
```

---

# 6. Update nth Bit

Sometimes we need to assign

```
bit = 0

or

bit = 1
```

---

## Method

First clear.

Then set if needed.

```c
unsigned int updateBit(unsigned int num, int n, int value)
{
    num &= ~(1U << n);

    if(value)
        num |= (1U << n);

    return num;
}
```

---

# 7. Check Odd or Even

Only the least significant bit matters.

```
Even

↓

LSB = 0
```

```
Odd

↓

LSB = 1
```

Program

```c
if(num & 1U)
    printf("Odd");
else
    printf("Even");
```

Example

```
14

1110

↓

Even
```

```
15

1111

↓

Odd
```

---

# 8. Count Number of Set Bits

## Method 1

Check every bit.

```c
int countBits(unsigned int num)
{
    int count = 0;

    while(num)
    {
        count += num & 1U;
        num >>= 1;
    }

    return count;
}
```

Example

```
13

1101
```

Set bits

```
3
```

Complexity

```
O(number of bits)
```

---

# 9. Brian Kernighan Algorithm

One of the most frequently asked interview questions.

---

## Observation

```
n & (n - 1)
```

removes the **rightmost set bit**.

---

Example

```
12

1100
```

```
11

1011
```

```
1100

&

1011

----------

1000
```

One set bit disappears.

---

Continue

```
1000

↓

0000
```

---

## Program

```c
int countSetBits(unsigned int num)
{
    int count = 0;

    while(num)
    {
        num &= (num - 1);
        count++;
    }

    return count;
}
```

Complexity

```
O(number of set bits)
```

Much faster for sparse bit patterns.

---

# 10. Built-in Bit Functions

GCC and Clang provide optimized functions.

---

## Count Set Bits

```c
__builtin_popcount(x)
```

64-bit

```c
__builtin_popcountll(x)
```

---

## Count Leading Zeros

```c
__builtin_clz(x)
```

---

## Count Trailing Zeros

```c
__builtin_ctz(x)
```

---

## Parity

```c
__builtin_parity(x)
```

---

Interview Tip

These are optimized using CPU instructions on many architectures.

---

# 11. Check Power of Two

Power of two numbers

```
1

2

4

8

16

32
```

Binary

```
1

10

100

1000

10000
```

Notice

Only one bit is set.

---

## Formula

```c
num && !(num & (num - 1))
```

---

Program

```c
int isPowerOfTwo(unsigned int num)
{
    return num && !(num & (num - 1));
}
```

---

Example

```
16

10000
```

```
15

01111
```

```
10000

&

01111

=

0
```

Power of two.

---

# 12. Check Power of Four

Power of four

```
1

4

16

64
```

Need

- Power of two
- Set bit at even position

Program

```c
int isPowerOfFour(unsigned int n)
{
    return n &&
           !(n & (n - 1)) &&
           (n & 0x55555555U);
}
```

---

# 13. Isolate Rightmost Set Bit

Formula

```c
num & (-num)
```

Example

```
12

1100
```

```
-12

0100
```

Result

```
0100
```

Useful in many interview problems.

---

# 14. Clear Rightmost Set Bit

Formula

```c
num &= (num - 1);
```

Example

```
101100
```

Result

```
101000
```

One set bit removed.

---

# 15. Set Rightmost Unset Bit

Formula

```c
num | (num + 1)
```

Example

```
10101111
```

Result

```
10111111
```

---

# 16. Count Leading Zeros

Leading zeros

```
00000101
```

Answer

```
5
```

Compiler support

```c
__builtin_clz(num)
```

Useful for:

- Logarithm calculations
- Priority encoders
- CPU instructions

---

# 17. Count Trailing Zeros

Example

```
101000
```

Trailing zeros

```
3
```

Compiler

```c
__builtin_ctz(num)
```

Useful for alignment and memory allocation.

---

# 18. Reverse Bits

Example

```
00000101
```

Reverse

```
10100000
```

Simple algorithm

```c
unsigned int reverseBits(unsigned int n)
{
    unsigned int rev = 0;

    for(int i = 0; i < 32; i++)
    {
        rev <<= 1;
        rev |= (n & 1U);
        n >>= 1;
    }

    return rev;
}
```

Complexity

```
O(32)
```

---

# 19. Rotate Bits

Unlike shifts, rotations do **not** lose bits.

---

## Rotate Left

```c
unsigned int rotateLeft(unsigned int n, int d)
{
    return (n << d) | (n >> (32 - d));
}
```

---

## Rotate Right

```c
unsigned int rotateRight(unsigned int n, int d)
{
    return (n >> d) | (n << (32 - d));
}
```

Used in

- Cryptography
- Hash functions
- Embedded systems

---

# 20. Swap Odd and Even Bits

Example

```
10110010

↓

01110001
```

Program

```c
unsigned int swapOddEvenBits(unsigned int n)
{
    return ((n & 0xAAAAAAAAU) >> 1) |
           ((n & 0x55555555U) << 1);
}
```

Very common Qualcomm interview question.

---

# Common Interview Questions

### Q1. Why does `n & (n - 1)` remove the rightmost set bit?

Subtracting 1 flips the rightmost set bit to 0 and all lower bits to 1. Performing AND clears that set bit while leaving higher bits unchanged.

---

### Q2. Why use `1U << n` instead of `1 << n`?

`1U` is an unsigned integer. It avoids issues related to signed integer overflow and sign extension during shifts.

---

### Q3. Why is Brian Kernighan's algorithm faster?

It loops only once for each **set bit**, not once for every bit position.

---

### Q4. Difference between shifting and rotating?

Shift:

```
Bits shifted out are discarded.
```

Rotate:

```
Bits shifted out re-enter from the opposite side.
```

---

### Q5. When should built-in functions be used?

Use compiler built-ins when available for performance, especially in production code. During interviews, also know how to implement the underlying algorithms manually.

---

# Key Takeaways

- `num | (1U << n)` → Set a bit.
- `num & ~(1U << n)` → Clear a bit.
- `num ^ (1U << n)` → Toggle a bit.
- `num & (1U << n)` → Check whether a bit is set.
- `n & (n - 1)` → Clear the rightmost set bit and test for powers of two.
- `n & (-n)` → Isolate the rightmost set bit.
- Brian Kernighan's algorithm counts set bits efficiently.
- Prefer compiler built-ins such as `__builtin_popcount()` when performance matters, but understand the manual algorithms.
- Use `unsigned` types for portable bit manipulation.
- -----------------------------------------------------------------------------
# Chapter 8 – Bit Manipulation
# Part 4 – Advanced Bit Manipulation & Interview Problems

---

# Contents

1. XOR Based Interview Problems
2. Missing Number
3. Single Number
4. Two Non-Repeating Numbers
5. Find Duplicate Number using XOR
6. Subsets using Bit Masking
7. Gray Code
8. Hamming Distance
9. Parity Bit
10. Bitmap
11. Permission Bits
12. Feature Flags
13. Register Programming
14. Memory-Mapped Registers
15. Atomic Bit Operations
16. Linux Kernel Bit Macros
17. Frequently Asked Interview Questions
18. Key Takeaways

---

# 1. XOR Based Interview Problems

Most semiconductor companies love XOR questions because they test whether you truly understand the properties of XOR.

Recall:

```
A ^ A = 0

A ^ 0 = A

A ^ B ^ A = B
```

These three properties solve many interview problems.

---

# 2. Missing Number

## Problem

Array contains numbers from

```
0 to n
```

One number is missing.

Example

```
0 1 2 4 5
```

Missing

```
3
```

---

## XOR Solution

Step 1

XOR all numbers from

```
0...n
```

Step 2

XOR every array element.

Everything cancels except the missing number.

---

Example

```
0^1^2^3^4^5

^

0^1^2^4^5

↓

3
```

---

## Code

```c
int missingNumber(int arr[], int n)
{
    int ans = 0;

    for(int i = 0; i <= n; i++)
        ans ^= i;

    for(int i = 0; i < n; i++)
        ans ^= arr[i];

    return ans;
}
```

Complexity

```
Time : O(n)

Space : O(1)
```

---

# 3. Single Number

## Problem

Every element appears twice.

Only one appears once.

Example

```
5 4 7 5 4
```

Answer

```
7
```

---

## XOR Solution

```
5^5 =0

4^4 =0

Remaining

7
```

---

## Code

```c
int singleNumber(int arr[], int n)
{
    int ans = 0;

    for(int i = 0; i < n; i++)
        ans ^= arr[i];

    return ans;
}
```

Very common Qualcomm/NVIDIA interview problem.

---

# 4. Two Non-Repeating Numbers

## Problem

```
2 5 7 5 8 7
```

Answer

```
2

8
```

---

## Idea

Step 1

XOR all numbers.

```
2 ^ 8
```

Step 2

Find any set bit.

Step 3

Split numbers into two groups.

Each group now contains one unique number.

---

## Why?

The chosen set bit differs between the two unique numbers, so they end up in different groups while duplicate values stay together and cancel out.

Complexity

```
O(n)
```

Very common interview question.

---

# 5. Find Duplicate Number using XOR

Example

```
1 2 3 4 4 5
```

Duplicate

```
4
```

Idea

XOR numbers and expected range.

(Works only when the input satisfies the required constraints.)

---

# 6. Generate All Subsets using Bit Masking

Suppose

```
A B C
```

Every subset corresponds to one binary number.

```
000

{}

001

{C}

010

{B}

011

{B,C}

100

{A}

101

{A,C}

110

{A,B}

111

{A,B,C}
```

---

## Code

```c
void subsets(int arr[], int n)
{
    int total = 1 << n;

    for(int mask = 0; mask < total; mask++)
    {
        printf("{ ");

        for(int i = 0; i < n; i++)
        {
            if(mask & (1 << i))
                printf("%d ", arr[i]);
        }

        printf("}\n");
    }
}
```

Complexity

```
Time

O(n × 2ⁿ)
```

---

# 7. Gray Code

Gray Code changes only **one bit** between consecutive numbers.

Binary

```
000

001

010

011
```

Gray

```
000

001

011

010
```

---

## Formula

```
Gray = Binary ^ (Binary >> 1)
```

Code

```c
unsigned int gray(unsigned int n)
{
    return n ^ (n >> 1);
}
```

---

## Applications

- Rotary encoders
- Position sensors
- Hardware counters
- Digital communication

---

# 8. Hamming Distance

Definition

Number of bit positions that differ.

Example

```
1011

1001
```

Difference

```
1
```

---

## Formula

```
A ^ B

↓

Count set bits
```

Code

```c
int hammingDistance(int a, int b)
{
    return __builtin_popcount((unsigned int)(a ^ b));
}
```

---

Applications

- Error detection
- Networking
- Coding theory
- DNA comparison

---

# 9. Parity Bit

Parity is used for simple error detection.

---

Even Parity

```
1011001
```

Set bits

```
4
```

Parity

```
0
```

Already even.

---

Odd Parity

If count is even,

append

```
1
```

---

Compiler

```c
__builtin_parity(x)
```

---

# 10. Bitmap

Instead of storing

```
100000 Boolean values
```

Use bits.

Example

```
100000 bits

↓

12500 bytes
```

Huge memory saving.

---

Applications

- Operating systems
- Databases
- Memory allocators
- Linux kernel

---

Example

```
Bit

0

↓

Page free
```

```
Bit

1

↓

Page allocated
```

---

# 11. Permission Bits

Unix file permissions use bit masks.

Example

```
755
```

Binary

```
111

101

101
```

Meaning

Owner

```
Read

Write

Execute
```

Group

```
Read

Execute
```

Others

```
Read

Execute
```

---

Bit Values

| Permission | Value |
|------------|-------|
| Read | 4 |
| Write | 2 |
| Execute | 1 |

---

# 12. Feature Flags

Many applications enable features using individual bits.

Example

```c
#define WIFI      (1U << 0)
#define BLUETOOTH (1U << 1)
#define GPS       (1U << 2)
#define NFC       (1U << 3)
```

Enable

```c
flags |= WIFI;
```

Disable

```c
flags &= ~WIFI;
```

Check

```c
if(flags & WIFI)
```

---

# 13. Register Programming

Embedded systems control peripherals through registers.

Example

```
31...............0
```

```
Enable

Interrupt

DMA

Reset

Reserved
```

---

Enable DMA

```c
REG |= DMA_ENABLE;
```

Disable DMA

```c
REG &= ~DMA_ENABLE;
```

Toggle DMA

```c
REG ^= DMA_ENABLE;
```

---

# 14. Memory-Mapped Registers

Example

```c
#define GPIO_BASE 0x40020000U

volatile unsigned int *GPIO =
    (volatile unsigned int *)GPIO_BASE;
```

Enable bit

```c
*GPIO |= (1U << 5);
```

---

Why

```
volatile
```

Because hardware can change the register independently of the CPU.

The compiler must not optimize away reads or writes.

---

# 15. Atomic Bit Operations

Problem

Two threads execute

```c
REG |= MASK;
```

at the same time.

Sequence

```
Read

Modify

Write
```

If both threads interleave, one update may overwrite the other (lost update).

---

Solutions

- Atomic CPU instructions
- Interrupt disable (embedded)
- Mutex
- Spinlock

---

# 16. Linux Kernel Bit Macros

The Linux kernel provides useful macros.

---

## BIT()

```c
BIT(5)
```

Expands to

```c
(1UL << 5)
```

---

## GENMASK()

Example

```c
GENMASK(7,4)
```

Produces

```
11110000
```

Useful for extracting bit fields.

---

## test_bit()

```c
test_bit(bit, addr);
```

Checks whether a bit is set.

---

## set_bit()

```c
set_bit(bit, addr);
```

Atomically sets a bit.

---

## clear_bit()

```c
clear_bit(bit, addr);
```

Atomically clears a bit.

---

## change_bit()

```c
change_bit(bit, addr);
```

Atomically toggles a bit.

---

# Frequently Asked Interview Questions

### Q1. Why is XOR useful for finding unique numbers?

Because identical numbers cancel each other.

```
A ^ A = 0
```

---

### Q2. Why are bit masks preferred over multiple Boolean variables?

They reduce memory usage and allow multiple flags to be stored in a single integer.

---

### Q3. Why must hardware registers be declared `volatile`?

The value may change outside the program's control, so every read and write must actually access memory.

---

### Q4. Why is `REG |= MASK` not always atomic?

It performs three separate operations:

```
Read

↓

Modify

↓

Write
```

Another thread or interrupt can modify the register between these steps.

---

### Q5. Where is Gray code used?

- Rotary encoders
- Position sensors
- Hardware counters
- Analog-to-digital converters
- Digital communication systems

---

### Q6. What is the advantage of a bitmap?

It stores one Boolean value per **bit**, greatly reducing memory usage compared to storing one Boolean value per byte or integer.

---

### Q7. What are Linux kernel bit macros used for?

They provide efficient, readable, and often atomic operations for manipulating bits in kernel data structures and hardware drivers.

---

# Key Takeaways

- XOR is the foundation for many interview problems involving unique or missing elements.
- Bit masking provides an efficient way to represent flags and permissions.
- Gray code ensures only one bit changes between consecutive values.
- Hamming distance can be computed by XOR followed by counting set bits.
- Hardware registers should generally be accessed through `volatile` pointers.
- Read-modify-write operations are **not inherently atomic** and require synchronization when shared.
- The Linux kernel provides helper macros such as `BIT()`, `GENMASK()`, `set_bit()`, and `test_bit()` to simplify and optimize bit operations.
- Mastering these patterns covers a large portion of bit manipulation questions asked in embedded, firmware, and systems programming interviews.
- ---------------------------------------------------------------------------------------
# Chapter 8 – Bit Manipulation
# Part 5 – Interview Cheat Sheet & Practice Questions

---

# Contents

1. One-Page Cheat Sheet
2. Important Formulas
3. Common Bit Masks
4. GCC/Clang Built-in Functions
5. Frequently Asked Interview Questions
6. Qualcomm/NVIDIA/AMD Style Coding Questions
7. Common Mistakes
8. Summary

---

# 1. One-Page Cheat Sheet

| Operation | Formula |
|-----------|---------|
| Set nth bit | `n \|= (1U << k)` |
| Clear nth bit | `n &= ~(1U << k)` |
| Toggle nth bit | `n ^= (1U << k)` |
| Check nth bit | `(n & (1U << k)) != 0` |
| Update nth bit | Clear then Set |
| Odd/Even | `n & 1U` |
| Multiply by 2 | `n << 1` |
| Divide by 2 | `n >> 1` (non-negative) |
| Remove rightmost set bit | `n &= (n-1)` |
| Isolate rightmost set bit | `n & (-n)` |
| Set rightmost zero bit | `n \| (n+1)` |
| Power of 2 | `n && !(n & (n-1))` |
| Count bits | Brian Kernighan |
| Reverse bits | Shift + OR |
| Rotate Left | `(n<<d) \| (n>>(32-d))` |
| Rotate Right | `(n>>d) \| (n<<(32-d))` |

---

# 2. Important Formulas

## Set Bit

```c
num |= (1U << k);
```

---

## Clear Bit

```c
num &= ~(1U << k);
```

---

## Toggle Bit

```c
num ^= (1U << k);
```

---

## Check Bit

```c
(num & (1U << k))
```

---

## Remove Rightmost Set Bit

```c
num &= (num - 1);
```

---

## Isolate Rightmost Set Bit

```c
num & (-num)
```

---

## Check Power of Two

```c
num && !(num & (num - 1))
```

---

## Count Set Bits

```c
while(num)
{
    num &= (num - 1);
    count++;
}
```

---

## Gray Code

```c
gray = n ^ (n >> 1);
```

---

## Hamming Distance

```c
__builtin_popcount(a ^ b)
```

---

# 3. Common Bit Masks

## Lowest Bit

```text
00000001
```

---

## Highest Bit (32-bit)

```text
10000000 00000000 00000000 00000000
```

---

## Lower 8 Bits

```text
0xFF
```

---

## Lower 16 Bits

```text
0xFFFF
```

---

## Upper 16 Bits

```text
0xFFFF0000
```

---

## Alternate Bits

```text
0xAAAAAAAA
```

Binary

```text
10101010...
```

---

## Alternate Bits

```text
0x55555555
```

Binary

```text
01010101...
```

---

## All Bits Set

```c
0xFFFFFFFFU
```

or

```c
~0U
```

---

# 4. GCC / Clang Built-in Functions

## Count Set Bits

```c
__builtin_popcount(x)
```

---

## 64-bit Version

```c
__builtin_popcountll(x)
```

---

## Leading Zeros

```c
__builtin_clz(x)
```

---

## Trailing Zeros

```c
__builtin_ctz(x)
```

---

## Parity

```c
__builtin_parity(x)
```

---

# 5. Frequently Asked Interview Questions

## Basic

✓ What is a bit?

✓ Difference between byte and word?

✓ Why hexadecimal?

✓ What is two's complement?

✓ Why do computers use two's complement?

✓ Difference between signed and unsigned?

✓ Explain endianness.

---

## Intermediate

✓ Difference between `&` and `&&`

✓ Difference between `|` and `||`

✓ Difference between `^` and `|`

✓ Difference between shift and rotate

✓ Arithmetic vs Logical shift

✓ Why use unsigned integers for bit operations?

✓ What is a bit mask?

✓ What is a bitmap?

---

## Advanced

✓ Explain Brian Kernighan Algorithm.

✓ Why does

```c
n & (n-1)
```

work?

✓ Explain

```c
n & (-n)
```

✓ Reverse bits.

✓ Swap odd and even bits.

✓ Find unique element using XOR.

✓ Find two unique numbers.

✓ Missing number using XOR.

✓ Generate subsets using bitmasking.

✓ Explain Gray code.

✓ Explain Hamming distance.

✓ Explain parity bit.

---

## Embedded Questions

✓ Why are hardware registers volatile?

✓ Explain memory-mapped I/O.

✓ Explain register masking.

✓ Explain read-modify-write.

✓ Why isn't

```c
REG |= MASK;
```

atomic?

✓ Difference between polling and interrupts.

✓ Explain Linux BIT() macro.

✓ Explain GENMASK().

---

# 6. Qualcomm / NVIDIA / AMD Style Coding Questions

### Easy

□ Check odd/even

□ Count set bits

□ Set nth bit

□ Clear nth bit

□ Toggle nth bit

□ Reverse bits

□ Rotate bits

□ Power of two

□ Power of four

---

### Medium

□ Missing number

□ Single number

□ Two unique numbers

□ Hamming distance

□ Gray code

□ Generate subsets

□ Swap odd/even bits

□ Reverse bytes

□ Count trailing zeros

---

### Advanced

□ Bitmap implementation

□ Bloom filter basics

□ CRC basics

□ Permission system

□ Register driver

□ GPIO manipulation

□ Interrupt controller simulation

□ Feature flag manager

---

# 7. Common Mistakes

## Mistake 1

```c
1 << 31
```

Problem

Left shifting a signed integer into the sign bit may result in undefined behavior.

Correct

```c
1U << 31
```

---

## Mistake 2

```c
if(num & 1 == 0)
```

Wrong precedence.

Correct

```c
if((num & 1) == 0)
```

---

## Mistake 3

Using signed integers for hardware registers.

Prefer

```c
uint32_t
```

---

## Mistake 4

Forgetting

```c
volatile
```

for memory-mapped registers.

---

## Mistake 5

Using XOR swap in production code.

Modern compilers optimize

```c
temp = a;
a = b;
b = temp;
```

very efficiently.

---

## Mistake 6

Assuming

```c
REG |= MASK;
```

is atomic.

It is actually

```
Read

↓

Modify

↓

Write
```

which can lead to race conditions.

---

# 8. Summary

After completing this chapter, you should be comfortable with:

- Binary and hexadecimal representations
- Signed and unsigned integers
- Two's complement
- Endianness
- All six bitwise operators
- Common bit manipulation techniques
- XOR-based interview problems
- Bit masks and feature flags
- Register programming
- Memory-mapped I/O
- Linux kernel bit macros
- Atomicity issues in read-modify-write operations
- Compiler built-in bit functions

These concepts are frequently tested in embedded, firmware, kernel, networking, and systems programming interviews. Mastering them provides a solid foundation for working with low-level software and hardware interfaces.

---

# Next Chapter

**Chapter 9 – Searching Algorithms**

Topics include:

- Linear Search
- Binary Search
- Lower Bound
- Upper Bound
- First & Last Occurrence
- Rotated Sorted Array
- Binary Search on Answer
- Peak Element
- Matrix Search
- Interview Patterns
- 40+ Coding Problems

