# Bit Manipulation in C

Bit manipulation is the process of changing or checking individual bits inside an integer.

Assume we are working with 32-bit unsigned integers:

```c
#include <stdio.h>
#include <stdint.h>
```

---

# 1. Set Bit

## Purpose

Set a bit to `1`.

Formula:

```
number = number | (1 << position)
```

## Code

```c
uint32_t set_bit(uint32_t num, int pos)
{
    return num | (1U << pos);
}
```

## Example

```c
num = 00001000

set bit 1

result = 00001010
```

---

# 2. Clear Bit

## Purpose

Set a bit to `0`.

Formula:

```
number = number & ~(1 << position)
```

## Code

```c
uint32_t clear_bit(uint32_t num, int pos)
{
    return num & ~(1U << pos);
}
```

## Example

```
num = 00001110

clear bit 2

result = 00001010
```

---

# 3. Toggle Bit

## Purpose

Change:

```
0 -> 1
1 -> 0
```

Formula:

```
number = number ^ (1 << position)
```

## Code

```c
uint32_t toggle_bit(uint32_t num, int pos)
{
    return num ^ (1U << pos);
}
```

---

# 4. Test Bit

## Purpose

Check whether a bit is set.

## Code

```c
int test_bit(uint32_t num, int pos)
{
    return (num & (1U << pos)) != 0;
}
```

Example:

```c
if(test_bit(status, 3))
{
    printf("Bit is ON");
}
```

---

# 5. Extract Field

## Purpose

Extract multiple bits from a number.

Example:

Extract bits 4 to 7.

## Code

```c
uint32_t extract_field(uint32_t num, int start, int width)
{
    uint32_t mask = (1U << width) - 1;

    return (num >> start) & mask;
}
```

Example:

```
num:

11101100 00000000

extract bits 8-11

result:

1110
```

---

# 6. Insert Field

## Purpose

Insert bits into a specific position.

## Code

```c
uint32_t insert_field(uint32_t num,
                      uint32_t value,
                      int start,
                      int width)
{
    uint32_t mask = ((1U << width) - 1) << start;

    num &= ~mask;

    num |= (value << start);

    return num;
}
```

Example:

```
Before:

00000000

Insert 101 at position 2

After:

00010100
```

---

# 7. Count Set Bits

## Purpose

Count number of `1` bits.

## Method: Brian Kernighan Algorithm

## Code

```c
int count_set_bits(uint32_t num)
{
    int count = 0;

    while(num)
    {
        num = num & (num - 1);

        count++;
    }

    return count;
}
```

Example:

```
101101

Number of set bits = 4
```

---

# 8. Check Power of Two

## Logic

Power of two has only one set bit.

Examples:

```
00010000  -> power of 2
00010100  -> not power of 2
```

## Code

```c
int is_power_of_two(uint32_t num)
{
    return num &&
          !(num & (num - 1));
}
```

---

# 9. Find Lowest Set Bit

## Purpose

Find the lowest bit that is `1`.

Example:

```
10110000

lowest set bit:

00010000
```

## Code

```c
uint32_t lowest_set_bit(uint32_t num)
{
    return num & (~num + 1);
}
```

Alternative:

```c
return num & -num;
```

---

# 10. Reverse Bits

## Purpose

Reverse bit order.

Example:

```
00000101

becomes

10100000
```

## Code

```c
uint32_t reverse_bits(uint32_t num)
{
    uint32_t result = 0;

    for(int i = 0; i < 32; i++)
    {
        result <<= 1;

        result |= (num & 1);

        num >>= 1;
    }

    return result;
}
```

---

# 11. Rotate Bits

## Left Rotation

## Code

```c
uint32_t rotate_left(uint32_t num, int shift)
{
    return (num << shift) |
           (num >> (32 - shift));
}
```

Example:

```
10110000

rotate left by 2

11000010
```

---

## Right Rotation

```c
uint32_t rotate_right(uint32_t num, int shift)
{
    return (num >> shift) |
           (num << (32 - shift));
}
```

---

# 12. Swap Bits

## Purpose

Swap two bit positions.

Example:

```
bit 1 <-> bit 5
```

## Code

```c
uint32_t swap_bits(uint32_t num,
                   int pos1,
                   int pos2)
{
    uint32_t bit1 = (num >> pos1) & 1;
    uint32_t bit2 = (num >> pos2) & 1;

    if(bit1 != bit2)
    {
        num ^= (1U << pos1);
        num ^= (1U << pos2);
    }

    return num;
}
```

---

# 13. Count Bit Transitions

## Purpose

Count changes:

```
0 -> 1
1 -> 0
```

Example:

```
101101

Transitions:

1->0
0->1
1->1
1->0

Count = 3
```

## Code

```c
int count_transitions(uint32_t num)
{
    uint32_t previous = num & 1;

    int count = 0;

    num >>= 1;


    while(num)
    {
        uint32_t current = num & 1;

        if(current != previous)
            count++;

        previous = current;

        num >>= 1;
    }

    return count;
}
```

---

# 14. Find Missing Number Using XOR

## Problem

Array contains numbers from:

```
0 to n
```

One number is missing.

## Logic

XOR cancels equal numbers:

```
A ^ A = 0
```

## Code

```c
int find_missing(int arr[], int n)
{
    int result = n;

    for(int i = 0; i < n; i++)
    {
        result ^= i;
        result ^= arr[i];
    }

    return result;
}
```

Example:

```c
int arr[] = {0,1,3,4};

missing = find_missing(arr,4);
```

Output:

```
2
```

---

# 15. Hardware Register Field Manipulation

Hardware registers are memory locations where each bit controls hardware features.

Example register:

```
CONTROL REGISTER

Bit 0 : Enable
Bit 1 : Interrupt
Bits 4-7 : Mode
```

---

## Define Register

```c
uint32_t CONTROL_REG;
```

---

## Enable Feature (Set Bit)

```c
#define ENABLE_BIT 0

CONTROL_REG |= (1U << ENABLE_BIT);
```

---

## Disable Feature (Clear Bit)

```c
CONTROL_REG &= ~(1U << ENABLE_BIT);
```

---

## Check Status

```c
if(CONTROL_REG & (1U << ENABLE_BIT))
{
    printf("Enabled");
}
```

---

## Write Mode Field

Bits 4-7:

```c
#define MODE_POS 4
#define MODE_WIDTH 4


CONTROL_REG &= ~(((1U << MODE_WIDTH)-1)
                  << MODE_POS);


CONTROL_REG |= (3 << MODE_POS);
```

---

## Read Mode Field

```c
uint32_t mode;

mode = (CONTROL_REG >> MODE_POS)
        & ((1U << MODE_WIDTH)-1);
```

---

# Summary

| Operation | Main Operator |
|-----------|---------------|
| Set bit | OR `|` |
| Clear bit | AND + NOT `& ~` |
| Toggle bit | XOR `^` |
| Test bit | AND `&` |
| Extract field | Shift + Mask |
| Insert field | Clear + OR |
| Count bits | `n & (n-1)` |
| Power of two | `n & (n-1)` |
| Lowest bit | `n & -n` |
| Reverse bits | Shift loop |
| Rotate bits | Shift + OR |
| Swap bits | XOR |
| Missing number | XOR |
| Hardware register | Mask + Shift |
