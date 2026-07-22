# C Interview Handbook
# Part 4A - Bit Manipulation Fundamentals & Bitwise Operators

---

# Table of Contents

1. Introduction to Bits
2. Binary Number System
3. Decimal ↔ Binary Conversion
4. Signed vs Unsigned Numbers
5. 1's Complement
6. 2's Complement
7. Bitwise Operators
8. Operator Precedence
9. Common Interview Questions
10. Quick Revision

---

# 1. What is a Bit?

A bit (Binary Digit) is the smallest unit of data.

A bit can store only two values.

```text
0

or

1
```

---

# 2. Why Binary?

Computers are built using electronic switches.

```text
OFF → 0

ON  → 1
```

Everything inside a computer is ultimately represented using bits.

---

# 3. Common Units

```text
1 Bit  = 0 or 1

8 Bits = 1 Byte

1024 Bytes = 1 KB

1024 KB = 1 MB

1024 MB = 1 GB

1024 GB = 1 TB
```

---

# 4. Binary Number System

Binary uses base 2.

Each position represents a power of 2.

Example

```text
Binary

101101
```

Expand

```text
1×2^5

0×2^4

1×2^3

1×2^2

0×2^1

1×2^0
```

Calculate

```text
32 + 0 + 8 + 4 + 0 + 1

= 45
```

Therefore

```text
101101₂ = 45₁₀
```

---

# 5. Decimal → Binary

Example

Convert

```text
13
```

Repeatedly divide by 2.

```text
13 /2 = 6  remainder 1

6 /2 = 3   remainder 0

3 /2 = 1   remainder 1

1 /2 = 0   remainder 1
```

Read from bottom.

```text
1101
```

Answer

```text
13 = 1101₂
```

---

# 6. Binary → Decimal

Example

```text
1101
```

```text
1×8

1×4

0×2

1×1

=

13
```

---

# 7. Bit Positions

Example

```text
Binary

1 0 1 1 0 1 0 1

Bit

7 6 5 4 3 2 1 0
```

Bit numbering starts from **0** (Least Significant Bit).

---

# 8. Most Significant Bit (MSB)

Leftmost bit.

Example

```text
10110011
^
MSB
```

---

# 9. Least Significant Bit (LSB)

Rightmost bit.

```text
10110011
       ^
      LSB
```

---

# 10. Signed vs Unsigned Numbers

Unsigned (8-bit)

```text
00000000

↓

0
```

```text
11111111

↓

255
```

Range

```text
0

to

255
```

---

Signed (Two's Complement)

MSB represents the sign.

```text
0

↓

Positive
```

```text
1

↓

Negative
```

Range (8-bit)

```text
-128

to

127
```

---

# 11. 1's Complement

Invert every bit.

Example

```text
Original

00001101
```

1's Complement

```text
11110010
```

---

# 12. 2's Complement

Take 1's complement.

Add 1.

Example

```text
13

00001101
```

Invert

```text
11110010
```

Add 1

```text
11110011
```

This represents **-13** in 8-bit two's complement.

---

# Why 2's Complement?

Advantages

- One representation of zero
- Simple hardware
- Easy addition/subtraction
- Used by almost all modern CPUs

---

# 13. Bitwise Operators

C provides six bitwise operators.

| Operator | Meaning |
|----------|---------|
| `&` | AND |
| `\|` | OR |
| `^` | XOR |
| `~` | NOT |
| `<<` | Left Shift |
| `>>` | Right Shift |

---

# 14. Bitwise AND (&)

Rule

```text
1 & 1 = 1

1 & 0 = 0

0 & 1 = 0

0 & 0 = 0
```

Truth Table

| A | B | A&B |
|---|---|-----|
|0|0|0|
|0|1|0|
|1|0|0|
|1|1|1|

Example

```c
int x = 10;
int y = 12;

printf("%d", x & y);
```

Binary

```text
10

1010

12

1100

AND

1000
```

Answer

```text
8
```

Common Uses

- Check bit
- Create mask
- Clear bits

---

# 15. Bitwise OR (|)

Rule

```text
0 | 0 = 0

1 | 0 = 1

0 | 1 = 1

1 | 1 = 1
```

Truth Table

|A|B|A\|B|
|--|--|----|
|0|0|0|
|0|1|1|
|1|0|1|
|1|1|1|

Example

```text
1010

1100

OR

1110
```

Answer

```text
14
```

Common Uses

- Set bits
- Combine flags

---

# 16. Bitwise XOR (^)

Rule

```text
Same

↓

0

Different

↓

1
```

Truth Table

|A|B|A^B|
|--|--|---|
|0|0|0|
|0|1|1|
|1|0|1|
|1|1|0|

Example

```text
1010

1100

XOR

0110
```

Answer

```text
6
```

Important Properties

```text
a ^ a = 0

a ^ 0 = a

a ^ b ^ a = b
```

Used in many interview problems.

---

# 17. Bitwise NOT (~)

Flips every bit.

Example

```text
1010

↓

0101
```

Example

```c
unsigned char x = 10;

printf("%u", (unsigned char)~x);
```

Binary

```text
00001010

↓

11110101
```

For signed integers, the result depends on the representation (modern systems use two's complement).

---

# 18. Left Shift (<<)

Moves bits to the left.

Example

```text
5

00000101
```

```text
5 << 1
```

Result

```text
00001010

↓

10
```

Another Example

```text
5 << 2

↓

20
```

For non-overflowing unsigned values

```text
x << n

↓

x × 2ⁿ
```

---

# 19. Right Shift (>>)

Moves bits to the right.

Example

```text
20

00010100
```

```text
20 >> 2
```

Result

```text
00000101

↓

5
```

For non-negative values

```text
x >> n

↓

x / 2ⁿ
```

(integer division)

---

# Arithmetic vs Logical Right Shift

Unsigned

```text
0's shifted in
```

Signed

Many systems perform **arithmetic right shift** (copies the sign bit), but for negative signed values this behavior is implementation-defined in C.

---

# 20. Operator Precedence

Higher

```text
~

<< >>

&

^

|

Lower
```

Always use parentheses when mixing operators.

Example

```c
(a & b) << 2
```

---

# 21. Common Interview Questions

### Q1. Why does a computer use binary?

Electronic circuits naturally represent two stable states: ON and OFF.

---

### Q2. Why is two's complement preferred?

- Simple arithmetic
- One zero
- Efficient hardware implementation

---

### Q3. Difference between AND and OR?

AND

```text
Keeps only common 1 bits.
```

OR

```text
Sets a bit if either input has a 1.
```

---

### Q4. Why is XOR important?

Useful for

- Swapping
- Finding unique numbers
- Bit toggling
- Error detection
- Parity calculations

---

### Q5. Difference between `<<` and `>>`?

`<<`

Moves bits left.

`>>`

Moves bits right.

---

# 22. Quick Revision

✓ Binary uses base 2.

✓ MSB is the leftmost bit.

✓ LSB is the rightmost bit.

✓ Two's complement represents negative numbers.

✓ `&` checks or clears bits.

✓ `|` sets bits.

✓ `^` toggles bits and has useful algebraic properties.

✓ `~` flips all bits.

✓ `<<` shifts left.

✓ `>>` shifts right.

---

# Interview Memory Trick

```text
&

↓

Keep Common Bits

|

↓

Set Bits

^

↓

Toggle / Difference

~

↓

Invert Bits

<<

↓

Multiply by 2ⁿ
(for non-overflowing unsigned values)

>>

↓

Divide by 2ⁿ
(for non-negative values)
```

---

# Next Part

**Part 4B – Bit Manipulation Techniques**

Topics

- Get ith Bit
- Set ith Bit
- Clear ith Bit
- Toggle ith Bit
- Update ith Bit
- Bit Masks
- Extract Multiple Bits
- Real Embedded Register Examples
- Interview Questions
-----------------------------
# C Interview Handbook
# Part 4B - Bit Manipulation Techniques

---

# Table of Contents

1. Bit Masks
2. Get ith Bit
3. Set ith Bit
4. Clear ith Bit
5. Toggle ith Bit
6. Update ith Bit
7. Clear Last i Bits
8. Clear Bits in a Range
9. Extract Bits
10. Check Odd/Even
11. Multiply & Divide by 2
12. Common Interview Questions
13. Quick Revision

---

# 1. What is a Bit Mask?

A bit mask is a binary value used to operate on selected bits.

Example

```text
Number

10110110

Mask

00000100
```

The mask selects Bit 2.

Most masks are created using left shift.

```c
1 << i
```

Example

```text
1 << 3

00001000
```

---

# 2. Get ith Bit

Goal

Return whether bit i is 0 or 1.

Formula

```c
(number >> i) & 1
```

or

```c
number & (1 << i)
```

Example

```text
Number = 22

Binary

00010110
```

Check Bit 2

```text
Mask

00000100

AND

00000100
```

Result

```text
Bit is SET
```

Code

```c
int getBit(int n, int i)
{
    return (n >> i) & 1;
}
```

---

# 3. Set ith Bit

Goal

Make bit i = 1.

Formula

```c
number | (1 << i)
```

Example

```text
Number

00010010

Set Bit 2

Mask

00000100

Result

00010110
```

Code

```c
int setBit(int n, int i)
{
    return n | (1 << i);
}
```

---

# 4. Clear ith Bit

Goal

Make bit i = 0.

Formula

```c
number & ~(1 << i)
```

Example

```text
Number

00010110

Mask

00000100

Invert Mask

11111011

AND

00010010
```

Code

```c
int clearBit(int n, int i)
{
    return n & ~(1 << i);
}
```

---

# 5. Toggle ith Bit

Goal

Reverse the bit.

```text
0 → 1

1 → 0
```

Formula

```c
number ^ (1 << i)
```

Example

```text
10110110

Toggle Bit 1

↓

10110100
```

Code

```c
int toggleBit(int n, int i)
{
    return n ^ (1 << i);
}
```

---

# 6. Update ith Bit

Goal

Change bit to a desired value.

Method

First clear the bit.

Then OR the new value.

Code

```c
int updateBit(int n, int i, int value)
{
    n = n & ~(1 << i);

    return n | (value << i);
}
```

Example

```text
Value = 1

↓

Set

Value = 0

↓

Clear
```

---

# 7. Clear Last i Bits

Formula

```c
number & (~0 << i)
```

Example

```text
Number

11101111

Clear Last 4 Bits

11110000

Result

11100000
```

Code

```c
int clearLastBits(int n, int i)
{
    return n & (~0 << i);
}
```

---

# 8. Clear Bits in Range

Suppose

```text
Clear bits

2

to

5
```

Method

Create left mask

Create right mask

Combine them.

Code

```c
int clearRange(int n, int i, int j)
{
    int left = (~0) << (j + 1);

    int right = (1 << i) - 1;

    int mask = left | right;

    return n & mask;
}
```

Example

```text
11111111

↓

11000011
```

---

# 9. Extract Bits

Suppose

```text
Number

11011010

Extract lowest 4 bits
```

Mask

```text
00001111
```

Operation

```c
number & 0xF
```

Result

```text
00001010
```

General Formula

```c
(number >> start) & ((1 << count) - 1)
```

---

# 10. Check Odd or Even

Rule

LSB tells whether a number is odd.

```text
Odd

↓

LSB = 1

Even

↓

LSB = 0
```

Code

```c
if (number & 1)
{
    printf("Odd");
}
else
{
    printf("Even");
}
```

Example

```text
13

1101

↓

Odd

14

1110

↓

Even
```

---

# 11. Multiply by 2

```c
x << 1
```

Example

```text
7

↓

14
```

Multiply by 8

```c
x << 3
```

Example

```text
5

↓

40
```

For unsigned values where overflow does not occur, left shifting by `n` multiplies by `2ⁿ`.

---

# 12. Divide by 2

```c
x >> 1
```

Example

```text
20

↓

10
```

Divide by 4

```c
x >> 2
```

Example

```text
36

↓

9
```

For non-negative integers, right shifting by `n` divides by `2ⁿ` using integer division.

---

# 13. Real Embedded Example

Suppose a hardware register

```text
Bit 0

↓

Power

Bit 1

↓

Interrupt

Bit 2

↓

Timer
```

Enable Timer

```c
register |= (1 << 2);
```

Disable Timer

```c
register &= ~(1 << 2);
```

Toggle Timer

```c
register ^= (1 << 2);
```

Check Timer

```c
if (register & (1 << 2))
{
}
```

This pattern is used in device drivers and embedded firmware.

---

# 14. Common Interview Questions

### Q1. How do you check whether a bit is set?

```c
number & (1 << i)
```

---

### Q2. How do you set a bit?

```c
number | (1 << i)
```

---

### Q3. How do you clear a bit?

```c
number & ~(1 << i)
```

---

### Q4. How do you toggle a bit?

```c
number ^ (1 << i)
```

---

### Q5. How do you know if a number is odd?

```c
number & 1
```

---

### Q6. Why use bit masks?

To efficiently manipulate selected bits without affecting others.

---

# 15. Quick Revision

✓ `1 << i` creates a mask for bit `i`.

✓ `&` checks or clears bits.

✓ `|` sets bits.

✓ `^` toggles bits.

✓ `~` inverts bits.

✓ `number & 1` checks odd/even.

✓ `(n >> i) & 1` gets bit `i`.

✓ `n & ~(1 << i)` clears bit `i`.

✓ `n | (1 << i)` sets bit `i`.

✓ `n ^ (1 << i)` toggles bit `i`.

---

# Interview Memory Trick

```text
CHECK

↓

&

SET

↓

|

CLEAR

↓

& ~

TOGGLE

↓

^

MASK

↓

1 << i
```

---

# Next Part

**Part 4C – Bit Manipulation Interview Tricks**

Topics

- Power of 2
- Brian Kernighan Algorithm
- Count Set Bits
- Find Single Number
- XOR Properties
- Swap Without Temp
- Missing Number
- Two Unique Numbers
- Reverse Bits
- Count Leading/Trailing Zeros
- MAANG Interview Problems
-----------------------------
# C Interview Handbook
# Part 4C - Bit Manipulation Interview Tricks

---

# Table of Contents

1. XOR Properties
2. Check Power of Two
3. Count Set Bits
4. Brian Kernighan's Algorithm
5. Find Single Number
6. Find Two Unique Numbers
7. Missing Number
8. Swap Without Temporary Variable
9. Reverse Bits
10. Count Leading & Trailing Zeros
11. Common Interview Questions
12. Quick Revision

---

# 1. XOR Properties

XOR is the foundation of many interview problems.

Important properties

```text
a ^ a = 0

a ^ 0 = a

a ^ b = b ^ a

(a ^ b) ^ c = a ^ (b ^ c)
```

Example

```text
5 ^ 5 = 0

5 ^ 0 = 5

3 ^ 4 ^ 3 = 4
```

---

# 2. Check if Number is Power of Two

Observation

A power of two has exactly **one set bit**.

Examples

```text
1   = 0001

2   = 0010

4   = 0100

8   = 1000

16  = 10000
```

Formula

```c
n > 0 && (n & (n - 1)) == 0
```

Example

```text
8

1000

7

0111

AND

0000
```

Code

```c
int isPowerOfTwo(unsigned int n)
{
    return n != 0 && (n & (n - 1)) == 0;
}
```

---

# 3. Count Set Bits (Method 1)

Count bits one by one.

```c
int countBits(unsigned int n)
{
    int count = 0;

    while (n)
    {
        count += n & 1;

        n >>= 1;
    }

    return count;
}
```

Complexity

```text
O(number of bits)
```

---

# 4. Brian Kernighan's Algorithm

Idea

Every iteration removes the **rightmost set bit**.

Formula

```c
n = n & (n - 1)
```

Example

```text
n = 44

101100

n - 1

101011

AND

101000
```

One set bit is removed.

Code

```c
int countBits(unsigned int n)
{
    int count = 0;

    while (n)
    {
        n = n & (n - 1);

        count++;
    }

    return count;
}
```

Complexity

```text
O(number of set bits)
```

---

# 5. Find Single Number

Problem

Every number appears twice except one.

Example

```text
2 3 5 3 2
```

Answer

```text
5
```

Solution

```c
int singleNumber(int arr[], int n)
{
    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        ans ^= arr[i];
    }

    return ans;
}
```

Why?

```text
2 ^ 2 = 0

3 ^ 3 = 0

Remaining = 5
```

Complexity

```text
O(n)

O(1) space
```

---

# 6. Find Two Unique Numbers

Problem

Every element appears twice except two numbers.

Example

```text
1 2 3 2 1 5
```

Answer

```text
3

5
```

Idea

1. XOR all elements.
2. Result = `a ^ b`.
3. Find a set bit where `a` and `b` differ.
4. Divide numbers into two groups.
5. XOR each group separately.

Complexity

```text
O(n)
```

---

# 7. Missing Number

Problem

Numbers

```text
0

1

2

4

5
```

Missing

```text
3
```

Solution

XOR all indices and all values.

Code

```c
int missingNumber(int arr[], int n)
{
    int ans = n;

    for (int i = 0; i < n; i++)
    {
        ans ^= i;
        ans ^= arr[i];
    }

    return ans;
}
```

Complexity

```text
O(n)
```

---

# 8. Swap Without Temporary Variable

Method

```c
a ^= b;
b ^= a;
a ^= b;
```

Example

Before

```text
a = 10

b = 20
```

After

```text
a = 20

b = 10
```

Note

Modern compilers optimize normal swaps well. Use this trick mainly to understand XOR properties or when specifically asked in an interview.

---

# 9. Reverse Bits

Example

```text
Input

00010110

Output

01101000
```

Code

```c
unsigned int reverseBits(unsigned int n)
{
    unsigned int rev = 0;

    for (int i = 0; i < 32; i++)
    {
        rev <<= 1;

        rev |= (n & 1);

        n >>= 1;
    }

    return rev;
}
```

---

# 10. Count Leading Zeros

Leading zeros

```text
00000101
^^^^^
```

Many compilers provide built-in functions.

Example (GCC/Clang)

```c
__builtin_clz(x)
```

Returns the number of leading zero bits.

Note

Passing `0` is undefined behavior.

---

# 11. Count Trailing Zeros

Example

```text
101000
   ^^^
```

Built-in

```c
__builtin_ctz(x)
```

Returns the number of trailing zero bits.

Note

Passing `0` is undefined behavior.

---

# 12. Isolate Rightmost Set Bit

Formula

```c
n & -n
```

Example

```text
n

10110000

-n

01010000

AND

00010000
```

Result

Only the rightmost set bit remains.

Useful in advanced XOR problems.

---

# 13. Remove Rightmost Set Bit

Formula

```c
n & (n - 1)
```

Example

```text
101100

↓

101000
```

Exactly one set bit is removed.

---

# 14. Check Opposite Signs

Formula

```c
(a ^ b) < 0
```

If true (on typical two's complement systems),

the numbers have opposite signs.

---

# 15. Common Interview Questions

### Q1. Why does `n & (n - 1)` work?

It clears the rightmost set bit.

---

### Q2. Why use XOR for the Single Number problem?

Duplicate values cancel out because

```text
a ^ a = 0
```

---

### Q3. Which algorithm counts set bits faster?

Brian Kernighan's Algorithm.

---

### Q4. Why is XOR useful?

- Unique element problems
- Swapping
- Parity
- Bit toggling
- Error detection

---

### Q5. How do you isolate the rightmost set bit?

```c
n & -n
```

---

# 16. Quick Revision

✓ `a ^ a = 0`

✓ `a ^ 0 = a`

✓ Power of 2

```c
n && !(n & (n - 1))
```

✓ Remove rightmost set bit

```c
n & (n - 1)
```

✓ Isolate rightmost set bit

```c
n & -n
```

✓ Brian Kernighan

```c
while (n)
{
    n &= (n - 1);
    count++;
}
```

✓ Single Number → XOR all values.

✓ Missing Number → XOR indices and array values.

---

# Interview Memory Trick

```text
Power of 2

↓

n & (n-1)

Single Number

↓

XOR

Count Bits

↓

Brian Kernighan

Rightmost Bit

↓

n & -n

Remove Rightmost Bit

↓

n & (n-1)
```

---

# Next Part

**Part 4D – Advanced Bit Programming**

Topics

- Bit Fields
- Bit Packing
- Bit Unpacking
- Endianness
- Hardware Registers
- Linux Kernel Bit Macros
- Embedded Programming Examples
- Network Protocol Flags
- Bitmap Data Structures
--------------------------
# C Interview Handbook
# Part 4D - Advanced Bit Programming

---

# Table of Contents

1. Bit Fields
2. Bit Packing
3. Bit Unpacking
4. Endianness
5. Hardware Register Programming
6. Linux Kernel Bit Macros
7. Network Protocol Flags
8. Bitmap Data Structures
9. Common Interview Questions
10. Quick Revision

---

# 1. Bit Fields

Sometimes we don't need an entire byte or integer for every value.

Example

```text
Status

Bit 0 -> Ready

Bit 1 -> Error

Bit 2 -> Busy

Bit 3 -> Reset
```

Instead of

```c
int ready;
int error;
int busy;
```

we can store all flags inside one integer.

---

Bit Field Syntax

```c
struct Status
{
    unsigned ready : 1;
    unsigned error : 1;
    unsigned busy  : 1;
    unsigned reset : 1;
};
```

Memory

```text
Bit

3 2 1 0

R B E R
```

Advantages

- Saves memory
- Cleaner representation

Limitations

- Layout is implementation-defined.
- Avoid for hardware protocols or portable file formats.

---

# 2. Bit Packing

Packing stores multiple values inside one integer.

Example

Store

```text
Age

0-127

↓

7 bits

Gender

↓

1 bit

Country

↓

8 bits
```

Inside one 16-bit integer.

Layout

```text
15........8

Country

7

Gender

6........0

Age
```

Packing

```c
unsigned short value = 0;

value |= age;

value |= (gender << 7);

value |= (country << 8);
```

---

# 3. Bit Unpacking

Extract values.

Age

```c
age = value & 0x7F;
```

Gender

```c
gender = (value >> 7) & 1;
```

Country

```c
country = (value >> 8) & 0xFF;
```

---

# 4. Endianness

Endianness defines the byte order used to store multi-byte values.

Example

```text
0x12345678
```

---

Little Endian

Lowest-addressed byte contains the least significant byte.

```text
Address

100

78

101

56

102

34

103

12
```

Used by

- x86
- x86-64
- Most ARM systems (configurable)

---

Big Endian

Lowest-addressed byte contains the most significant byte.

```text
Address

100

12

101

34

102

56

103

78
```

Historically used by some networking hardware and certain CPU architectures.

---

How to Detect

```c
#include <stdio.h>

int main()
{
    unsigned int x = 1;

    char *p = (char *)&x;

    if (*p == 1)
        printf("Little Endian");
    else
        printf("Big Endian");

    return 0;
}
```

---

# 5. Hardware Register Programming

Embedded systems access registers using bit operations.

Register

```text
Bit 0

Enable

Bit 1

Interrupt

Bit 2

Timer

Bit 3

Reset
```

Enable Timer

```c
reg |= (1 << 2);
```

Disable Timer

```c
reg &= ~(1 << 2);
```

Check Timer

```c
if (reg & (1 << 2))
{
}
```

Toggle Timer

```c
reg ^= (1 << 2);
```

---

# 6. volatile Registers

Hardware registers can change independently of program flow.

Declare them as

```c
volatile unsigned int *reg;
```

Why?

Without `volatile`, the compiler may optimize away repeated reads or writes.

---

Example

```c
while ((*reg & (1 << 0)) == 0)
{
}
```

The compiler must read the register every iteration.

---

# 7. Linux Kernel Bit Macros

The Linux kernel provides helper macros for bit operations.

Examples

```c
BIT(n)
```

Equivalent conceptually to

```c
1UL << n
```

---

```c
GENMASK(h, l)
```

Creates a mask covering bits `h` down to `l`.

Example

```text
GENMASK(7,4)

↓

11110000
```

---

These macros improve readability and portability within the kernel.

---

# 8. Network Protocol Flags

TCP Header

```text
FIN

SYN

RST

PSH

ACK

URG

ECE

CWR
```

Each flag occupies one bit.

Example

```text
ACK

↓

00010000
```

Check ACK

```c
if (flags & ACK_MASK)
{
}
```

Enable ACK

```c
flags |= ACK_MASK;
```

Clear ACK

```c
flags &= ~ACK_MASK;
```

---

# 9. Bitmap Data Structures

A bitmap stores boolean values using bits instead of bytes.

Example

Need to store

```text
1000

true/false values
```

Normal array

```text
1000 bytes
```

Bitmap

```text
1000 bits

≈ 125 bytes
```

Much more memory efficient.

---

Set Bit

```c
bitmap[index / 8] |= (1 << (index % 8));
```

Clear Bit

```c
bitmap[index / 8] &= ~(1 << (index % 8));
```

Check Bit

```c
bitmap[index / 8] & (1 << (index % 8))
```

Applications

- Memory allocators
- CPU affinity masks
- File system block allocation
- Resource tracking

---

# 10. Common Interview Questions

### Q1. What is endianness?

The byte order used to store multi-byte values in memory.

---

### Q2. Difference between little and big endian?

Little endian stores the least significant byte first.

Big endian stores the most significant byte first.

---

### Q3. Why use volatile for registers?

Because hardware may change register values outside the program's control.

---

### Q4. Why use bitmaps?

To store many boolean values efficiently.

---

### Q5. Why are network flags stored as bits?

To minimize space and allow efficient testing and modification.

---

### Q6. Are C bit-fields portable?

No.

Their layout, ordering, and alignment are implementation-defined.

---

# 11. Quick Revision

✓ Bit fields store small values compactly.

✓ Packing combines multiple values into one integer.

✓ Unpacking extracts them with shifts and masks.

✓ Endianness defines byte order.

✓ Use `volatile` for hardware registers.

✓ Linux provides helper macros such as `BIT()` and `GENMASK()`.

✓ Network headers use bit flags.

✓ Bitmaps efficiently represent boolean states.

---

# Interview Memory Trick

```text
Packing

↓

Store Together

Unpacking

↓

Extract

Little Endian

↓

LSB First

Big Endian

↓

MSB First

volatile

↓

Always Read Hardware

Bitmap

↓

Many Booleans

Few Bytes
```

---

# Next Part

**Part 4E – Bit Manipulation Interview Question Bank**

Topics

- 50+ Output-Based Questions
- 40+ Coding Problems
- Pattern Recognition
- Optimized Solutions
- MAANG Interview Questions
- Linux & Embedded Bit Problems

 ---------------------------------------------------------------------------------------------------  
 
