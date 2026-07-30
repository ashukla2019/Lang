# Chapter 4 – Structures, Unions & Enums
# Part 1 – Structures (Complete Fundamentals)

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- Why structures exist
- How to define structures
- Declaring and initializing structures
- Accessing members
- Arrays of structures
- Nested structures
- Structure assignment
- Structure comparison
- Passing structures to functions
- Returning structures

---

# Why Do We Need Structures?

Suppose we want to store information about an employee.

Without structures:

```c
int id = 101;
char name[20] = "Alice";
float salary = 85000.0;
```

For one employee, this is manageable.

For 100 employees:

```c
int ids[100];
char names[100][20];
float salaries[100];
```

Keeping related data together becomes difficult.

---

## Solution

A structure groups related variables into one user-defined data type.

```
Employee

↓

+-----------+
| id        |
| name      |
| salary    |
+-----------+
```

Instead of managing three separate variables, we manage a single `Employee`.

---

# What is a Structure?

A structure is a **user-defined data type** that groups variables of different data types under one name.

Example:

```c
struct Employee
{
    int id;
    char name[20];
    float salary;
};
```

Here,

```
Employee

↓

Contains

↓

id

name

salary
```

---

# Defining a Structure

Syntax

```c
struct StructureName
{
    datatype member1;
    datatype member2;
    datatype member3;
};
```

Example

```c
struct Student
{
    int roll;
    char name[30];
    float marks;
};
```

**Note:** The definition only creates a **type**. It does **not** allocate memory.

---

# Declaring Structure Variables

```c
struct Student s1;
```

Now memory is allocated for `s1`.

You can create multiple variables.

```c
struct Student s1;
struct Student s2;
struct Student s3;
```

Memory

```
s1

+-----------+
| roll      |
| name      |
| marks     |
+-----------+

s2

+-----------+
| roll      |
| name      |
| marks     |
+-----------+
```

---

# Initializing Structures

Method 1

```c
struct Student s1 =
{
    1,
    "Rahul",
    95.5
};
```

---

Method 2 (Designated Initializers)

```c
struct Student s2 =
{
    .marks = 88.5,
    .roll = 2,
    .name = "Anita"
};
```

This is clearer and independent of member order.

---

# Accessing Members

Use the **dot operator (`.`)**.

```c
printf("%d\n", s1.roll);
printf("%s\n", s1.name);
printf("%.2f\n", s1.marks);
```

Modify members

```c
s1.roll = 10;

strcpy(s1.name, "John");

s1.marks = 92.0;
```

---

# Complete Example

```c
#include <stdio.h>
#include <string.h>

struct Student
{
    int roll;
    char name[30];
    float marks;
};

int main()
{
    struct Student s1;

    s1.roll = 1;

    strcpy(s1.name, "Rahul");

    s1.marks = 95.5;

    printf("%d\n", s1.roll);
    printf("%s\n", s1.name);
    printf("%.2f\n", s1.marks);

    return 0;
}
```

Output

```
1
Rahul
95.50
```

---

# Array of Structures

Instead of

```
Student

↓

One Object
```

We often need many students.

```c
struct Student class[3];
```

Memory

```
class

+------------+
| Student 1  |
+------------+

+------------+
| Student 2  |
+------------+

+------------+
| Student 3  |
+------------+
```

Example

```c
class[0].roll = 1;

class[1].roll = 2;

class[2].roll = 3;
```

---

## Example Program

```c
#include <stdio.h>

struct Student
{
    int roll;
    float marks;
};

int main()
{
    struct Student s[3] =
    {
        {1,90},
        {2,85},
        {3,95}
    };

    for(int i=0;i<3;i++)
    {
        printf("%d %.1f\n",
               s[i].roll,
               s[i].marks);
    }
}
```

---

# Nested Structures

A structure can contain another structure.

Example

```c
struct Date
{
    int day;
    int month;
    int year;
};

struct Employee
{
    int id;
    char name[20];
    struct Date joiningDate;
};
```

Memory

```
Employee

+----------------+
| id             |
| name           |
| joiningDate    |
| day            |
| month          |
| year           |
+----------------+
```

---

Accessing Nested Members

```c
emp.joiningDate.day = 15;

emp.joiningDate.month = 8;

emp.joiningDate.year = 2025;
```

---

# Structure Assignment

Unlike arrays,

structures can be assigned directly.

```c
struct Student s1 =
{
    1,
    "Rahul",
    90
};

struct Student s2;

s2 = s1;
```

Entire structure is copied.

Memory

Before

```
s1

↓

Data

s2

↓

Empty
```

After

```
s1

↓

Data

↓

Copied

↓

s2
```

---

# Can Structures Be Compared?

This is a common interview question.

```c
if(s1 == s2)
{
}
```

Answer

```
No
```

Compilation Error.

Why?

The C language does **not** define `==` for structures.

Instead compare each member.

```c
if(s1.roll == s2.roll &&
   strcmp(s1.name,s2.name)==0 &&
   s1.marks == s2.marks)
{
    printf("Equal");
}
```

---

# Size of Structure

```c
struct Test
{
    int a;
    char b;
};

printf("%lu\n",
sizeof(struct Test));
```

Many beginners expect

```
5 Bytes
```

But the answer is usually

```
8 Bytes
```

Why?

Because of **padding**.

We'll study padding and alignment in the next part.

---

# Passing Structure to Function

Method 1 – Pass by Value

```c
void printStudent(struct Student s)
{
    printf("%d\n", s.roll);
}
```

Call

```c
printStudent(s1);
```

A complete copy is made.

---

Method 2 – Pass by Pointer (Preferred)

```c
void printStudent(struct Student *s)
{
    printf("%d\n", s->roll);
}
```

Call

```c
printStudent(&s1);
```

Advantages

- No copy
- Faster
- Can modify original object

---

# Returning Structures

C allows returning structures.

```c
struct Point
{
    int x;
    int y;
};

struct Point createPoint()
{
    struct Point p =
    {
        10,
        20
    };

    return p;
}
```

Usage

```c
struct Point p1 =
createPoint();
```

---

# Structures vs Arrays

| Array | Structure |
|--------|-----------|
| Same data type | Different data types |
| Indexed access | Named members |
| Cannot assign | Can assign |
| Elements only | Related fields |

---

# Common Interview Questions

---

## Q1. Why use structures?

To group related variables into a single object.

---

## Q2. Can a structure contain another structure?

Yes.

This is called a **nested structure**.

---

## Q3. Can structures contain arrays?

Yes.

```c
struct Student
{
    char name[20];
};
```

---

## Q4. Can structures contain pointers?

Yes.

```c
struct Node
{
    int data;
    struct Node *next;
};
```

This is how linked lists are implemented.

---

## Q5. Can structures be copied?

Yes.

```c
s2 = s1;
```

Copies every member.

---

## Q6. Can structures be compared using `==`?

No.

Compare each member manually.

---

## Q7. Which is better?

```c
void fun(struct Student s);
```

or

```c
void fun(struct Student *s);
```

For large structures,

passing a pointer is preferred because it avoids copying.

---

# Common Interview Traps

### Trap 1

```c
struct Student
{
};
```

Invalid.

A structure must contain at least one member.

---

### Trap 2

```c
struct Student s;

s.name = "Rahul";
```

Wrong.

Arrays cannot be assigned.

Correct

```c
strcpy(s.name, "Rahul");
```

---

### Trap 3

```c
struct Student s1;

struct Student s2;

if(s1==s2)
```

Compilation error.

---

### Trap 4

```c
struct Student
{
    int a;
    char b;
};
```

Many answer

```
5 Bytes
```

Usually incorrect due to padding.

---

# Real Embedded Examples

## Device Configuration

```c
struct UART_Config
{
    int baudRate;
    int dataBits;
    int stopBits;
};
```

---

## Sensor Data

```c
struct Sensor
{
    int id;
    float temperature;
    float humidity;
};
```

---

## Network Packet Header

```c
struct Header
{
    unsigned short type;
    unsigned short length;
};
```

---

# Quick Revision

```
Structure

↓

User Defined Type

↓

Groups Different Data Types

-------------------------

Access

↓

.

Operator

-------------------------

Nested Structure

↓

Structure Inside Structure

-------------------------

Array Of Structures

↓

Many Objects

-------------------------

Structure Assignment

↓

Allowed

-------------------------

Structure Comparison

↓

Not Allowed

-------------------------

Pass To Function

↓

Pointer Preferred

-------------------------

Return Structure

↓

Allowed
```

---

# Key Interview Takeaways

✅ Structures group related variables into a single user-defined type.

✅ Structure variables can be copied directly using the assignment operator.

✅ Structures **cannot** be compared using `==`.

✅ Arrays of structures are widely used to represent collections of records.

✅ Passing structures by pointer is generally preferred for efficiency.

✅ **Padding and alignment** determine the actual size of a structure—one of the most frequently asked embedded interview topics.

---

# Next Part

In **Part 2**, we'll cover **Structure Padding & Memory Alignment**, including:

- Why `sizeof(struct)` is often larger than expected
- Memory alignment rules
- Padding with examples and diagrams
- Reordering members to reduce memory usage
- `#pragma pack`
- `__attribute__((packed))`
- Alignment interview questions from Qualcomm, NVIDIA, Broadcom, and Intel.
- ----------------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 4 – Structures, Unions & Enums
# Part 2 – Structure Padding & Memory Alignment (Most Asked Embedded Topic)

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Why Is This Topic Important?

This is one of the **most frequently asked topics** in embedded interviews.

Interviewers love asking questions like:

- What is padding?
- Why is `sizeof(struct)` larger than expected?
- What is alignment?
- How can we reduce memory usage?
- What is packed structure?
- Why do CPUs need alignment?

Understanding this topic also helps in:

- Device Drivers
- DMA
- Networking
- File Formats
- Embedded Systems
- Linux Kernel

---

# What is Structure Padding?

Padding means adding **unused bytes** between members so that each member starts at an address suitable for the CPU.

Example

```c
struct Test
{
    char c;
    int i;
};
```

Many beginners answer:

```
1 + 4 = 5 Bytes
```

Actual answer on most 32-bit and 64-bit systems:

```
8 Bytes
```

Why?

Padding.

---

# Why Do CPUs Need Alignment?

Modern CPUs access aligned memory much faster.

Suppose an `int` occupies 4 bytes.

Good alignment

```
Address

1000

↓

int
```

Bad alignment

```
Address

1001

↓

int
```

Misaligned accesses may:

- Require multiple memory accesses
- Reduce performance
- Cause exceptions on some architectures (ARM, older processors)

---

# Alignment Rule

A data type generally wants an address that is a multiple of its size.

Typical alignment

| Data Type | Size | Alignment |
|-----------|------|-----------|
| char | 1 | 1 |
| short | 2 | 2 |
| int | 4 | 4 |
| float | 4 | 4 |
| double | 8 | 8 (typically) |
| pointer (64-bit) | 8 | 8 |

---

# Example 1

```c
struct Test
{
    char c;
    int i;
};
```

Without padding

```
Byte

0

↓

char

Byte

1

↓

int starts here ❌
```

`int` should start at address divisible by 4.

Compiler inserts padding.

Memory

```
Offset

0

↓

char

1

↓

Padding

2

↓

Padding

3

↓

Padding

4

↓

int

5

↓

int

6

↓

int

7

↓

int
```

Total

```
8 Bytes
```

---

# Verify

```c
#include <stdio.h>

struct Test
{
    char c;
    int i;
};

int main()
{
    printf("%lu\n",
           sizeof(struct Test));
}
```

Output

```
8
```

---

# Example 2

```c
struct Test
{
    char a;
    char b;
    int c;
};
```

Memory

```
Offset

0

a

1

b

2

Padding

3

Padding

4

int

5

int

6

int

7

int
```

Size

```
8 Bytes
```

---

# Example 3

```c
struct Test
{
    int a;
    char b;
};
```

Memory

```
0

int

1

int

2

int

3

int

4

char

5

Padding

6

Padding

7

Padding
```

Size

```
8 Bytes
```

Notice the **padding at the end**.

---

# Why End Padding?

Consider

```c
struct Test arr[2];
```

Each structure must start at a properly aligned address.

Without end padding

```
Struct 1

↓

5 Bytes

Struct 2

↓

Starts at wrong alignment
```

Compiler pads the structure so every element in the array is aligned.

---

# Example 4

```c
struct Test
{
    char a;
    double b;
};
```

Assume

```
double

↓

8-byte alignment
```

Memory

```
0

char

1-7

Padding

8

double

9

double

10

double

11

double

12

double

13

double

14

double

15

double
```

Total

```
16 Bytes
```

---

# How Compiler Calculates Size

Rule 1

Every member begins at its required alignment.

Rule 2

Compiler inserts padding if necessary.

Rule 3

Entire structure size is rounded up to the largest alignment requirement.

---

# Example 5

```c
struct Test
{
    char a;
    int b;
    short c;
};
```

Step 1

```
char

↓

Offset 0
```

Step 2

```
Padding

↓

1-3
```

Step 3

```
int

↓

4-7
```

Step 4

```
short

↓

8-9
```

Step 5

Largest alignment

```
4
```

Current size

```
10
```

Rounded to next multiple of 4

```
12 Bytes
```

---

# Member Reordering

Bad

```c
struct Test
{
    char a;
    int b;
    char c;
};
```

Memory

```
16 Bytes
```

Better

```c
struct Test
{
    int b;
    char a;
    char c;
};
```

Memory

```
8 Bytes
```

Same data.

Less memory.

---

# Example

Bad layout

```
char

Padding

int

char

Padding
```

Good layout

```
int

char

char

Padding
```

---

# How to Minimize Padding

Arrange members from **largest** to **smallest**.

Example

Instead of

```c
char
double
char
int
```

Write

```c
double
int
char
char
```

---

# Packed Structures

Sometimes hardware protocols require exact layouts.

Example

```c
#pragma pack(push,1)

struct Packet
{
    char type;
    int length;
};

#pragma pack(pop)
```

Now

```
No Padding
```

Memory

```
0

char

1

int

2

int

3

int

4

int
```

Total

```
5 Bytes
```

---

# GCC Packed Attribute

```c
struct __attribute__((packed))
Packet
{
    char type;
    int length;
};
```

Same effect.

---

# Should We Always Pack Structures?

No.

Packed structures can cause:

- Slower access
- Misaligned memory accesses
- Hardware faults on some processors

Use them only when required:

- Network packets
- Communication protocols
- Hardware registers
- File formats

---

# offsetof()

Find the offset of a member.

```c
#include <stddef.h>

printf("%lu\n",
offsetof(struct Test, b));
```

Useful for:

- Linux Kernel
- Device Drivers
- Serialization
- `container_of()`

---

# Memory Visualization

```c
struct Test
{
    char a;
    int b;
    short c;
};
```

Memory

```
Offset

0

a

1

Padding

2

Padding

3

Padding

4

b

5

b

6

b

7

b

8

c

9

c

10

Padding

11

Padding
```

Total

```
12 Bytes
```

---

# Common Interview Questions

---

## Q1

Why is

```c
sizeof(struct)
```

greater than expected?

Because of alignment and padding.

---

## Q2

Can padding appear in the middle?

Yes.

---

## Q3

Can padding appear at the end?

Yes.

---

## Q4

Why is end padding needed?

So arrays of structures remain properly aligned.

---

## Q5

How can we reduce padding?

Reorder members from largest alignment to smallest.

---

## Q6

Should we always use packed structures?

No.

Only when exact memory layout is required.

---

## Q7

Is structure layout guaranteed by the C standard?

The **order of members is preserved**, but the compiler may insert padding between members and at the end. The exact amount of padding is implementation-dependent.

---

# Common Interview Traps

### Trap 1

```c
struct Test
{
    char c;
    int i;
};
```

Answering

```
5 Bytes
```

Wrong.

Usually

```
8 Bytes
```

---

### Trap 2

Thinking

```
Padding

↓

Always Bad
```

Wrong.

Padding often improves CPU performance.

---

### Trap 3

Using packed structures everywhere.

Can reduce performance and may even cause faults on some architectures.

---

# Real Embedded Examples

## Ethernet Header

Must match protocol exactly.

Packed structures are commonly used.

---

## UART Packet

```
Header

↓

Length

↓

Command

↓

Checksum
```

Often packed.

---

## Hardware Registers

```
GPIO Register

↓

Control

↓

Status

↓

Flags
```

Must match hardware-defined offsets exactly.

---

## File Headers

BMP, ELF, WAV, and many binary file formats rely on exact field layouts.

---

# Quick Revision

```
Padding

↓

Extra Bytes

↓

Alignment

---------------------

Alignment

↓

CPU Efficiency

---------------------

Largest Alignment

↓

Determines

↓

Structure Alignment

---------------------

Member Reordering

↓

Less Padding

↓

Smaller Structure

---------------------

Packed Structure

↓

No Padding

↓

Hardware Protocols

↓

Use Carefully

---------------------

offsetof()

↓

Member Offset
```

---

# Key Interview Takeaways

✅ Padding is inserted to satisfy alignment requirements and improve CPU access efficiency.

✅ The compiler may insert padding **between members** and **at the end** of a structure.

✅ The final size of a structure is typically rounded up to a multiple of its largest alignment requirement.

✅ Reordering members can significantly reduce memory usage.

✅ Packed structures remove padding but should only be used when an exact memory layout is required.

✅ **Structure padding and alignment are among the highest-frequency C questions in Qualcomm, NVIDIA, Broadcom, Intel, and embedded interviews.**

---

# Next Part

In **Part 3**, we'll cover **Structure Pointers, the `->` Operator, Self-Referential Structures, and `typedef struct`**, which are the foundation for linked lists, trees, Linux kernel data structures, and many embedded programming concepts.
----------------------------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 4 – Structures, Unions & Enums
# Part 3 – Structure Pointers, `->` Operator, Self-Referential Structures & typedef

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- Pointer to a structure
- Dot (`.`) vs Arrow (`->`) operator
- Passing structures using pointers
- Dynamic allocation of structures
- Self-referential structures
- `typedef struct`
- Why linked lists use structure pointers
- Common interview questions

---

# Why Use Structure Pointers?

Suppose we have a large structure.

```c
struct Employee
{
    int id;
    char name[100];
    double salary;
    char address[500];
};
```

Passing this structure by value copies the **entire structure**.

```
Function Call

↓

Copy Entire Object

↓

More Memory

↓

More Time
```

Instead, pass only its address.

```
Function Call

↓

Pointer

↓

8 Bytes (64-bit)

↓

No Copy
```

---

# Pointer to Structure

Syntax

```c
struct Student *ptr;
```

Read as

```
ptr

↓

Pointer

↓

to

↓

Student
```

---

## Example

```c
struct Student
{
    int roll;
    float marks;
};

struct Student s1 =
{
    1,
    95.5
};

struct Student *ptr = &s1;
```

Memory

```
ptr

↓

+------+
|1000  |
+------+
    |
    ▼

+------------+
| roll = 1   |
| marks=95.5 |
+------------+
```

---

# Access Using Dot Operator

Without pointer

```c
printf("%d\n", s1.roll);
```

Use

```
Object

↓

.
```

---

# Access Using Pointer

Option 1

```c
printf("%d\n", (*ptr).roll);
```

Explanation

```
ptr

↓

Address

↓

*

↓

Structure

↓

.

↓

Member
```

This is correct but looks complicated.

---

# Arrow Operator

Instead of

```c
(*ptr).roll
```

C provides

```c
ptr->roll
```

Both are identical.

```
ptr->roll

↓

(*ptr).roll
```

---

# Complete Example

```c
#include <stdio.h>

struct Student
{
    int roll;
    float marks;
};

int main()
{
    struct Student s =
    {
        10,
        92.5
    };

    struct Student *ptr = &s;

    printf("%d\n", ptr->roll);
    printf("%.1f\n", ptr->marks);

    return 0;
}
```

Output

```
10
92.5
```

---

# Dot vs Arrow

| Object | Pointer |
|---------|----------|
| `student.roll` | `ptr->roll` |
| `student.marks` | `ptr->marks` |

Rule

```
Structure Object

↓

.

----------------

Structure Pointer

↓

->
```

---

# Modifying Members Through Pointer

```c
ptr->roll = 50;

ptr->marks = 99.0;
```

Equivalent

```c
(*ptr).roll = 50;

(*ptr).marks = 99.0;
```

---

# Passing Structure Pointer to Function

Instead of

```c
void print(struct Student s)
```

Use

```c
void print(struct Student *s)
{
    printf("%d\n", s->roll);
}
```

Call

```c
print(&student);
```

Advantages

- No copy
- Faster
- Can modify original object

---

# Example

```c
#include <stdio.h>

struct Student
{
    int roll;
};

void update(struct Student *s)
{
    s->roll = 100;
}

int main()
{
    struct Student st = {10};

    update(&st);

    printf("%d\n", st.roll);
}
```

Output

```
100
```

---

# Returning Structure Pointer

Example

```c
struct Student*
getStudent()
{
    static struct Student s =
    {
        1
    };

    return &s;
}
```

Notice

```
static

↓

Memory Exists

↓

After Function Returns
```

---

# Wrong Example

```c
struct Student*
getStudent()
{
    struct Student s =
    {
        1
    };

    return &s;
}
```

Wrong.

```
Local Variable

↓

Destroyed

↓

Dangling Pointer
```

---

# Dynamic Allocation

Structures are commonly allocated dynamically.

```c
#include <stdlib.h>

struct Student
{
    int roll;
};

int main()
{
    struct Student *ptr;

    ptr = malloc(sizeof(struct Student));

    ptr->roll = 10;

    printf("%d\n", ptr->roll);

    free(ptr);
}
```

Memory

```
Stack

ptr

↓

Heap

+--------+
| roll   |
+--------+
```

---

# Self-Referential Structure

A structure containing a pointer to the same structure type.

Example

```c
struct Node
{
    int data;

    struct Node *next;
};
```

Memory

```
Node

+---------+
| data    |
| next ---+---->
+---------+
```

---

# Why Not This?

```c
struct Node
{
    int data;

    struct Node next;
};
```

Impossible.

Compiler cannot determine the size.

```
Node

↓

Contains Node

↓

Contains Node

↓

Infinite Size
```

---

# Linked List

```
+------+      +------+      +------+
|10 | o------>|20 | o------>|30 |NULL
+------+      +------+      +------+
```

Each node contains

```
Data

↓

Pointer To Next Node
```

---

# Tree Example

```c
struct Tree
{
    int data;

    struct Tree *left;

    struct Tree *right;
};
```

Memory

```
        10
       /  \
      5    20
```

---

# Why Self-Referential Structures Matter

Used in

- Linked Lists
- Trees
- Graphs
- Queues
- Stacks
- Linux Kernel
- Device Drivers
- Scheduler

---

# typedef with Structures

Without typedef

```c
struct Student
{
    int roll;
};

struct Student s1;
```

Need to write

```
struct

Every Time
```

---

With typedef

```c
typedef struct
{
    int roll;
} Student;
```

Now

```c
Student s1;
```

Cleaner.

---

# Named typedef

```c
typedef struct Student
{
    int roll;
} Student;
```

Both work.

---

# Linux Kernel Style

Linux commonly uses

```c
struct task_struct
{
    ...
};
```

instead of typedef.

Kernel coding style generally avoids `typedef` for structures to keep the type explicit.

---

# Structure Pointer Initialization

Correct

```c
struct Student s;

struct Student *ptr = &s;
```

---

Incorrect

```c
struct Student *ptr;

ptr->roll = 10;
```

Undefined behavior.

Pointer is uninitialized.

---

# NULL Check

Always verify dynamic pointers.

```c
if(ptr != NULL)
{
    ptr->roll = 10;
}
```

---

# Common Interview Questions

---

## Q1

Difference between

```c
.
```

and

```c
->
```

Answer

```
.

↓

Structure Object

-------------------

->

↓

Structure Pointer
```

---

## Q2

Which is better?

```c
(*ptr).roll
```

or

```c
ptr->roll
```

Both are identical.

Arrow is preferred.

---

## Q3

Why pass structure pointers?

Avoid copying large structures.

---

## Q4

What is a self-referential structure?

A structure containing a pointer to its own type.

---

## Q5

Can a structure contain itself?

No.

Only a pointer to itself.

---

## Q6

Why?

Otherwise,

```
Infinite Size

↓

Compilation Error
```

---

## Q7

Where are self-referential structures used?

- Linked Lists
- Trees
- Graphs
- Linux Kernel
- Device Drivers

---

## Q8

Why does Linux use so many structure pointers?

Objects are large.

Pointers avoid copying.

---

# Common Interview Traps

### Trap 1

```c
ptr.roll
```

Wrong.

Use

```c
ptr->roll
```

---

### Trap 2

```c
(*ptr.roll)
```

Wrong.

`.` has higher precedence than `*`.

Correct

```c
(*ptr).roll
```

or simply

```c
ptr->roll
```

---

### Trap 3

```c
return &localStructure;
```

Returns a dangling pointer.

---

### Trap 4

```c
malloc(sizeof(ptr));
```

Usually wrong.

`sizeof(ptr)` is only the pointer size.

Correct

```c
malloc(sizeof(struct Student));
```

or, even better,

```c
malloc(sizeof(*ptr));
```

---

# Real Embedded Examples

## UART Configuration

```c
typedef struct
{
    int baudRate;
    int parity;
} UART_Config;
```

---

## Device Driver

```c
struct Device
{
    int id;

    struct Device *next;
};
```

---

## Linux Kernel

```c
struct list_head
{
    struct list_head *next;
    struct list_head *prev;
};
```

This doubly linked list structure is used throughout the Linux kernel.

---

# Quick Revision

```
Structure Object

↓

.

Operator

--------------------

Structure Pointer

↓

->

Operator

--------------------

(*ptr).member

↓

Same As

↓

ptr->member

--------------------

Self-Referential

↓

Pointer To Same Structure

--------------------

Used In

↓

Linked List

↓

Tree

↓

Graph

--------------------

typedef

↓

Removes

↓

Repeated struct Keyword
```

---

# Key Interview Takeaways

✅ Use `.` for structure objects and `->` for structure pointers.

✅ `ptr->member` is exactly equivalent to `(*ptr).member`.

✅ Pass structures by pointer to avoid unnecessary copying.

✅ Self-referential structures are the foundation of linked lists, trees, and many kernel data structures.

✅ Never return the address of a local structure.

✅ `malloc(sizeof(*ptr))` is a robust allocation pattern because it automatically matches the pointer's type.

---

# Next Part

In **Part 4**, we'll cover **Unions**, including:

- Memory layout of unions
- Union vs Structure
- Shared memory
- Type punning
- Endianness
- Embedded use cases
- Interview questions frequently asked by Qualcomm, NVIDIA, Broadcom, and Intel.
- -------------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 4 – Structures, Unions & Enums
# Part 4 – Unions (Memory Sharing & Type Punning)

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- What a union is
- Difference between structure and union
- Memory layout of unions
- Size of a union
- How memory is shared
- Type punning
- Endianness using unions
- Embedded use cases
- Common interview questions

---

# Why Do We Need Unions?

Suppose a sensor can return **only one** of the following values at a time:

- Integer
- Floating point
- Character

Using a structure:

```c
struct Data
{
    int i;
    float f;
    char c;
};
```

Memory

```
+-------+
| int   |
+-------+
| float |
+-------+
| char  |
+-------+
```

Even though only **one value** is used at a time, memory is allocated for all members.

This wastes memory.

---

# Solution

Use a union.

A union allows **all members to share the same memory location**.

```
Union

↓

One Memory Block

↓

Shared By All Members
```

---

# What is a Union?

A union is a user-defined data type where **all members occupy the same memory location**.

Syntax

```c
union Data
{
    int i;
    float f;
    char c;
};
```

Unlike a structure,

```
Structure

↓

Each Member

↓

Own Memory

--------------------

Union

↓

All Members

↓

Same Memory
```

---

# Structure vs Union

Structure

```
+-------+
| int   |
+-------+
| float |
+-------+
| char  |
+-------+
```

Union

```
+-------+
| Shared|
|Memory |
+-------+
```

Only one member should be considered valid at a time.

---

# Example

```c
#include <stdio.h>

union Data
{
    int i;
    float f;
};

int main()
{
    union Data d;

    d.i = 100;

    printf("%d\n", d.i);

    d.f = 10.5;

    printf("%.1f\n", d.f);
}
```

Output

```
100

10.5
```

Notice:

Writing to `f` overwrites the value stored in `i`.

---

# Memory Layout

```c
union Data
{
    int i;
    float f;
};
```

Memory

```
Address

1000

+----------------+
|                |
| Shared Memory  |
|                |
+----------------+

i

↓

Uses Same Memory

f

↓

Uses Same Memory
```

---

# Writing One Member

```c
union Data d;

d.i = 100;
```

Memory

```
Shared Memory

↓

100
```

Now

```c
printf("%d", d.i);
```

prints

```
100
```

---

# Writing Another Member

```c
d.f = 15.5;
```

Memory becomes

```
Shared Memory

↓

15.5
```

The previous integer value is lost.

---

# Size of Union

Question

```c
union Test
{
    int a;
    char b;
    double c;
};
```

What is

```c
sizeof(union Test)
```

Answer

```
Largest Member Size
```

Here

```
int

↓

4

char

↓

1

double

↓

8
```

Result

```
8 Bytes
```

---

# Verify

```c
#include <stdio.h>

union Test
{
    int a;
    char b;
    double c;
};

int main()
{
    printf("%lu\n",
           sizeof(union Test));
}
```

Output

```
8
```

---

# Why Largest Member?

Because every member shares the same memory.

The memory must be large enough for the largest member.

Visualization

```
Largest Member

↓

Defines

↓

Union Size
```

---

# Structure vs Union Example

```c
struct S
{
    int a;
    float b;
    char c;
};

union U
{
    int a;
    float b;
    char c;
};
```

Typical sizes

```
sizeof(struct S)

↓

12

sizeof(union U)

↓

4
```

(Exact structure size depends on padding.)

---

# Union Initialization

```c
union Data d =
{
    .i = 100
};
```

or

```c
union Data d =
{
    100
};
```

Only the **first initialized member** is valid.

---

# Accessing Members

```c
union Data d;

d.i = 10;

printf("%d\n", d.i);
```

Use the dot operator.

Pointer version

```c
union Data *ptr = &d;

ptr->i = 20;
```

Same as structures.

---

# Type Punning

A common embedded technique.

Example

```c
union Data
{
    int i;
    float f;
};
```

```c
union Data d;

d.i = 0x41200000;

printf("%f\n", d.f);
```

The integer bits are interpreted as a floating-point number.

This is called

```
Type Punning
```

---

# Why Type Punning?

Sometimes we want to interpret the **same bits** differently.

Example

```
32 Bits

↓

As Integer

or

↓

As Float
```

Used in:

- Embedded systems
- DSP
- Communication protocols
- Device drivers

---

# Endianness Using Union

One of the most common interview questions.

```c
#include <stdio.h>

union Test
{
    int value;
    char byte[4];
};

int main()
{
    union Test t;

    t.value = 0x12345678;

    printf("%x\n", t.byte[0]);
}
```

If output is

```
78
```

Machine is

```
Little Endian
```

If output is

```
12
```

Machine is

```
Big Endian
```

---

# Memory Illustration

Value

```
0x12345678
```

Little Endian

```
Address

1000

↓

78

1001

↓

56

1002

↓

34

1003

↓

12
```

Big Endian

```
1000

↓

12

1001

↓

34

1002

↓

56

1003

↓

78
```

---

# Tagged Union

A union alone does **not** tell you which member is currently valid.

A common design pattern is to use an enum as a tag.

```c
enum Type
{
    INT_TYPE,
    FLOAT_TYPE
};

struct Value
{
    enum Type type;

    union
    {
        int i;
        float f;
    } data;
};
```

Usage

```c
struct Value v;

v.type = INT_TYPE;
v.data.i = 100;
```

Now the program knows which member is valid.

This pattern is widely used in interpreters, compilers, and protocol parsers.

---

# Common Embedded Uses

## Hardware Registers

Different bit layouts may represent different operating modes.

---

## Communication Packets

Receive raw bytes and interpret them in different ways.

---

## Sensor Data

One message may carry either

- Integer
- Float
- Status code

---

## Protocol Parsing

CAN

UART

SPI

I2C

Bluetooth

Networking

---

# Common Interview Questions

---

## Q1

Difference between structure and union?

| Structure | Union |
|------------|-------|
| Separate memory for each member | Shared memory |
| Larger size | Smaller size |
| All members valid simultaneously | Only one member should be considered valid |

---

## Q2

How is union size calculated?

Answer

```
Largest Member Size

+

Any Required Alignment
```

---

## Q3

Can all members contain valid values simultaneously?

No.

Writing to one member overwrites the others.

---

## Q4

Why use unions?

- Save memory
- Type punning
- Hardware interfaces
- Communication protocols

---

## Q5

Can a union contain structures?

Yes.

```c
union Data
{
    int value;

    struct
    {
        char a;
        char b;
    } bytes;
};
```

---

## Q6

Can a union contain another union?

Yes.

---

## Q7

Can unions have pointers?

Yes.

Exactly like structures.

---

# Common Interview Traps

### Trap 1

```c
union U
{
    int a;
    float b;
};

u.a = 10;

u.b = 20;
```

Thinking both values exist.

Wrong.

Only the **last written member** should be considered valid.

---

### Trap 2

Assuming

```
sizeof(union)

=

Sum of Members
```

Wrong.

It's the size of the **largest member** (subject to alignment).

---

### Trap 3

Using unions for type punning without understanding that this behavior has portability considerations under the C standard. In interview code it's common, but production code may require care depending on the compiler and optimization settings.

---

# Real Embedded Example

Reading a 32-bit register as bytes.

```c
union Register
{
    uint32_t value;

    uint8_t byte[4];
};
```

Now

```c
reg.value = 0x12345678;
```

Access individual bytes

```c
reg.byte[0]

reg.byte[1]

reg.byte[2]

reg.byte[3]
```

No copying required.

---

# Quick Revision

```
Union

↓

Shared Memory

----------------------

Size

↓

Largest Member

----------------------

Writing One Member

↓

Overwrites Others

----------------------

Used For

↓

Memory Saving

↓

Type Punning

↓

Hardware Registers

↓

Protocol Parsing

----------------------

Tagged Union

↓

Enum

+

Union

↓

Safe Design
```

---

# Key Interview Takeaways

✅ A union allocates a single block of memory shared by all members.

✅ The size of a union is determined by its largest member (plus any alignment requirements).

✅ Only one member should be considered valid at any given time.

✅ Unions are commonly used in embedded systems to conserve memory and reinterpret binary data.

✅ A **tagged union** (`enum` + `union`) is the preferred way to safely track which member is active.

---

# Next Part

In **Part 5**, we'll cover **Enumerations (`enum`)**, including:

- Why enums are better than macros
- Enum values and custom numbering
- Enum size
- Enum vs `#define`
- State machines
- Embedded programming use cases
- Interview questions from Qualcomm, NVIDIA, Broadcom, Intel, and AMD.
- ---------------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 4 – Structures, Unions & Enums
# Part 5 – Enumerations (enum)

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- What is an enum?
- Why use enums instead of macros?
- Default and custom enum values
- Enum size
- Enum with switch-case
- Enum in state machines
- Enum in embedded systems
- Common interview questions

---

# Why Do We Need Enums?

Suppose we are writing software for a traffic light.

Without enums

```c
int signal = 1;

if(signal == 1)
{
    printf("Red");
}
```

Question:

```
What does

1

mean?
```

Nobody knows unless they read the documentation.

Instead use

```c
enum TrafficLight
{
    RED,
    YELLOW,
    GREEN
};
```

Now

```c
enum TrafficLight signal = RED;
```

The code is much easier to read.

---

# What is an Enum?

An enum (enumeration) is a user-defined type that assigns meaningful names to integer constants.

Syntax

```c
enum Color
{
    RED,
    GREEN,
    BLUE
};
```

Internally

```
RED

↓

0

GREEN

↓

1

BLUE

↓

2
```

---

# Default Values

Example

```c
enum Day
{
    MON,
    TUE,
    WED,
    THU,
    FRI
};
```

Values become

| Enumerator | Value |
|------------|------:|
| MON | 0 |
| TUE | 1 |
| WED | 2 |
| THU | 3 |
| FRI | 4 |

---

# Printing Enum Values

```c
#include <stdio.h>

enum Color
{
    RED,
    GREEN,
    BLUE
};

int main()
{
    printf("%d\n", RED);
    printf("%d\n", GREEN);
    printf("%d\n", BLUE);
}
```

Output

```
0
1
2
```

Remember

```
Enum values

↓

Integers
```

---

# Custom Values

We can assign our own values.

```c
enum ErrorCode
{
    SUCCESS = 0,
    FILE_ERROR = 100,
    NETWORK_ERROR = 200,
    MEMORY_ERROR = 300
};
```

Output

```
SUCCESS

↓

0

FILE_ERROR

↓

100

NETWORK_ERROR

↓

200
```

---

# Partial Initialization

```c
enum Number
{
    A = 10,
    B,
    C,
    D = 20,
    E
};
```

Compiler assigns

| Enumerator | Value |
|------------|------:|
| A | 10 |
| B | 11 |
| C | 12 |
| D | 20 |
| E | 21 |

---

# Duplicate Values

Enums may contain duplicate values.

```c
enum Result
{
    PASS = 1,
    SUCCESS = 1,
    FAIL = 0
};
```

This is valid C.

---

# Declaring Enum Variables

```c
enum Color c;
```

Assign value

```c
c = GREEN;
```

Use

```c
if(c == GREEN)
{
    printf("Green");
}
```

---

# Enum in switch

One of the most common uses.

```c
switch(c)
{
case RED:
    printf("Stop");
    break;

case YELLOW:
    printf("Wait");
    break;

case GREEN:
    printf("Go");
    break;
}
```

Much more readable than

```c
switch(value)
{
case 0:
...
```

---

# Enum vs #define

Macros

```c
#define RED 0
#define GREEN 1
#define BLUE 2
```

Enums

```c
enum Color
{
    RED,
    GREEN,
    BLUE
};
```

Comparison

| Macro | Enum |
|--------|------|
| Text replacement | Integer constant |
| No type | User-defined type |
| Harder to debug | Easier to debug |
| No scope | Better readability |

Enums are generally preferred for related constants.

---

# Enum Size

Question

```c
enum Color
{
    RED,
    GREEN,
    BLUE
};

printf("%lu\n",
sizeof(enum Color));
```

Typical output

```
4
```

Usually the size is the same as `int`.

**Interview Note**

The C standard does **not** require an enum to have the size of `int`.

The compiler chooses an integer type capable of storing all enumerator values.

Most desktop compilers use

```
4 Bytes
```

Some embedded compilers may choose a smaller size.

---

# Enum Values Can Be Negative

```c
enum Status
{
    ERROR = -1,
    OK = 0,
    BUSY = 1
};
```

Valid.

---

# Enum in State Machines

One of the biggest embedded uses.

```c
enum State
{
    IDLE,
    START,
    RUNNING,
    STOP,
    ERROR
};
```

Program

```c
enum State state = IDLE;
```

Switch

```c
switch(state)
{
case IDLE:
    ...
    break;

case RUNNING:
    ...
    break;
}
```

This is exactly how many embedded firmware state machines are written.

---

# Enum in Device Drivers

```c
enum UART_State
{
    UART_IDLE,
    UART_BUSY,
    UART_ERROR
};
```

Instead of

```c
int state = 2;
```

Use

```c
enum UART_State state =
UART_BUSY;
```

Much easier to understand.

---

# Enum in Communication Protocols

Example

```c
enum PacketType
{
    DATA_PACKET,
    ACK_PACKET,
    ERROR_PACKET
};
```

Used in

- UART
- SPI
- I2C
- CAN
- Ethernet
- Bluetooth

---

# Enum with typedef

Without typedef

```c
enum Color color;
```

With typedef

```c
typedef enum
{
    RED,
    GREEN,
    BLUE
} Color;
```

Now

```c
Color color;
```

Cleaner syntax.

---

# Enum Inside Structures

Very common.

```c
enum Status
{
    READY,
    BUSY,
    FAILED
};

struct Device
{
    int id;

    enum Status status;
};
```

Usage

```c
device.status = READY;
```

---

# Common Interview Questions

---

## Q1

What is an enum?

A user-defined type that gives meaningful names to integer constants.

---

## Q2

What is the default value of the first enumerator?

```
0
```

---

## Q3

Can enum values be changed at runtime?

No.

Enumerator values are compile-time constants.

However, enum variables can hold different enumerators.

---

## Q4

Can enum values be duplicated?

Yes.

```c
enum Test
{
    A = 1,
    B = 1
};
```

Valid.

---

## Q5

Can enum values be negative?

Yes.

---

## Q6

Can we assign any integer to an enum variable?

```c
enum Color c;

c = 100;
```

The C language allows this, although `100` is not one of the defined enumerators.

Good practice is to assign only valid enum values.

---

## Q7

Which is better?

```c
#define RED 0
```

or

```c
enum Color
{
    RED
};
```

Usually

```
enum
```

because it improves readability and debugging.

---

## Q8

Where are enums used?

- State machines
- Drivers
- Operating systems
- Communication protocols
- Kernel code
- Device firmware

---

# Common Interview Traps

### Trap 1

Thinking

```c
enum
```

stores strings.

Wrong.

It stores integers.

---

### Trap 2

Thinking

```
RED

↓

"RED"
```

Wrong.

Actually

```
RED

↓

0
```

---

### Trap 3

Printing

```c
printf("%s", RED);
```

Wrong.

Use

```c
printf("%d", RED);
```

---

### Trap 4

Assuming

```
sizeof(enum)

↓

Always 4
```

Usually true, but not guaranteed by the C standard.

---

# Real Embedded Examples

## Operating System States

```c
enum TaskState
{
    READY,
    RUNNING,
    BLOCKED,
    SUSPENDED
};
```

---

## Network Driver

```c
enum LinkStatus
{
    LINK_DOWN,
    LINK_UP
};
```

---

## DMA Controller

```c
enum DMA_State
{
    DMA_IDLE,
    DMA_BUSY,
    DMA_COMPLETE
};
```

---

## Bootloader

```c
enum BootMode
{
    NORMAL_BOOT,
    RECOVERY_BOOT,
    UPDATE_BOOT
};
```

---

# Quick Revision

```
Enum

↓

Named Integer Constants

----------------------

Default Values

↓

0

1

2

3

----------------------

Custom Values

↓

Allowed

----------------------

Enum Variable

↓

Stores Enumerator

----------------------

Used In

↓

Switch

↓

State Machines

↓

Drivers

↓

Protocols

----------------------

Preferred Over

↓

#define

For Related Constants
```

---

# Key Interview Takeaways

✅ Enums improve readability by replacing numeric constants with meaningful names.

✅ By default, enumerator values start at `0` and increase by `1`.

✅ Custom and duplicate values are allowed.

✅ Enums are heavily used in embedded firmware, device drivers, protocol stacks, and operating-system state machines.

✅ The size of an enum is implementation-defined, although it is commonly `4` bytes on desktop systems.

---

# Next Part

In **Part 6**, we'll cover **Advanced Structure & Union Interview Questions**, including:

- `const struct` vs `struct const`
- Structure copying internals
- Flexible Array Members (FAM)
- Anonymous structs/unions
- Bit-fields
- `container_of()` (Linux kernel)
- `offsetof()`
- 25+ Qualcomm/NVIDIA/Broadcom interview questions with detailed explanations.
- ----------------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 4 – Structures, Unions & Enums
# Part 6 – Advanced Structure & Union Interview Questions

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

This chapter covers advanced concepts frequently asked in embedded and systems interviews.

Topics include:

- Flexible Array Members (FAM)
- Bit-fields
- Anonymous Structures & Unions
- offsetof()
- container_of() (Linux Kernel)
- Structure Copying
- const with Structures
- volatile Structures
- Memory Mapping
- 30+ Interview Questions

---

# 1. Flexible Array Members (FAM)

One of the most common embedded interview questions.

Suppose we receive packets of different sizes.

Bad approach

```c
struct Packet
{
    int length;
    char data[1000];
};
```

Every packet wastes memory.

Instead use

```c
struct Packet
{
    int length;
    char data[];
};
```

Notice

```
[]

↓

No Size
```

This is called a

```
Flexible Array Member
```

---

## Allocation

```c
#include <stdlib.h>

struct Packet
{
    int length;
    char data[];
};

int main()
{
    int n = 100;

    struct Packet *p =
        malloc(sizeof(struct Packet) + n);

    p->length = n;

    free(p);
}
```

Memory

```
+----------------+
| length         |
+----------------+
| data[100]      |
+----------------+
```

---

## Rules

Flexible array member

- Must be the **last member**
- Only one flexible array member is allowed
- Cannot appear in the middle

Wrong

```c
struct Test
{
    char data[];

    int x;
};
```

---

# Why Use FAM?

Widely used in

- Linux Kernel
- Network packets
- Variable-length messages
- IPC
- Device drivers

---

# 2. Bit-fields

Bit-fields allow members to occupy specific numbers of bits instead of bytes.

Example

```c
struct Status
{
    unsigned ready : 1;
    unsigned error : 1;
    unsigned mode  : 2;
};
```

Memory

```
Bit

0

↓

ready

1

↓

error

2-3

↓

mode
```

---

## Usage

```c
struct Status s = {0};

s.ready = 1;

s.error = 0;

s.mode = 2;
```

---

## Why Bit-fields?

Hardware registers often define individual bits.

Instead of

```c
reg |= (1 << 3);
```

We can use

```c
status.enable = 1;
```

---

## Interview Note

Although convenient, bit-field layout is **implementation-defined**.

For hardware registers, many projects prefer explicit bit masking.

---

# 3. Anonymous Structures

C11 allows unnamed structures.

Example

```c
struct
{
    int x;
    int y;
} point;
```

Access

```c
point.x = 10;
```

No structure name exists.

---

# 4. Anonymous Union

Example

```c
struct Data
{
    int type;

    union
    {
        int i;
        float f;
    };
};
```

Now

```c
d.i = 10;
```

Instead of

```c
d.value.i
```

Used frequently in embedded libraries.

---

# 5. Structure Copy

Question

```c
s2 = s1;
```

What happens?

Compiler copies every member.

Equivalent to

```c
s2.a = s1.a;

s2.b = s1.b;

...
```

---

## Does It Perform Deep Copy?

No.

Example

```c
struct Test
{
    int *ptr;
};
```

```c
s2 = s1;
```

Memory

```
s1.ptr

↓

1000

s2.ptr

↓

1000
```

Only pointer values are copied.

Both structures point to the same memory.

This is called

```
Shallow Copy
```

---

# Deep Copy

Suppose

```c
struct Student
{
    char *name;
};
```

Deep copy requires

```c
s2.name = malloc(strlen(s1.name)+1);

strcpy(s2.name,
       s1.name);
```

Now each structure owns its own memory.

---

# 6. const Structure

Example

```c
const struct Student s =
{
    1
};
```

Now

```c
s.roll = 10;
```

Compilation error.

Entire object is read-only.

---

# Pointer Variations

## Pointer to const structure

```c
const struct Student *p;
```

Cannot modify structure through pointer.

```
p->roll = 10

↓

Error
```

Pointer may point elsewhere.

---

## Constant Pointer

```c
struct Student *const p = &s;
```

Pointer cannot change.

```
p = &other

↓

Error
```

But

```c
p->roll = 10;
```

Allowed.

---

## Constant Pointer to Constant Structure

```c
const struct Student *const p = &s;
```

Neither pointer nor object can change.

---

# 7. volatile Structure

Very common in embedded interviews.

Suppose hardware updates registers automatically.

```c
volatile struct UART
{
    int status;
    int data;
};
```

Without

```
volatile
```

Compiler may optimize away repeated reads.

With

```
volatile
```

Every read goes to hardware.

---

# 8. Memory Mapped Registers

Embedded example

```c
#define GPIO ((volatile GPIO_Type *)0x40020000)
```

Structure

```c
typedef struct
{
    unsigned MODER;
    unsigned IDR;
    unsigned ODR;
} GPIO_Type;
```

Usage

```c
GPIO->ODR = 1;
```

Much cleaner than

```c
*(volatile unsigned *)
0x40020008 = 1;
```

---

# 9. offsetof()

Find offset of member.

```c
#include <stddef.h>

offsetof(struct Student,
         marks)
```

Example

```c
printf("%zu\n",
offsetof(struct Student,
         marks));
```

Very common in

- Linux Kernel
- Serialization
- Embedded drivers

---

# 10. container_of()

One of the most famous Linux macros.

Suppose

```c
struct Node
{
    int data;
};

struct Student
{
    int id;

    struct Node node;
};
```

Given

```
Node*

↓

Need

↓

Student*
```

Linux uses

```c
container_of()
```

to compute the address of the containing structure.

Concept

```
Structure

↓

Member

↓

Address Of Member

↓

Subtract Offset

↓

Structure Address
```

---

Example

```c
Student Address

1000

↓

node Offset

4

↓

Node Address

1004

↓

container_of()

↓

1000
```

---

# Why Linux Uses container_of()

Used throughout

- Linked Lists
- Device Drivers
- Networking
- Process Scheduler
- File Systems

It avoids duplicate objects and enables generic data structures.

---

# Common Interview Questions

---

## Q1

Difference between shallow copy and deep copy?

**Shallow copy**

Copies pointer values.

**Deep copy**

Copies pointed-to data as well.

---

## Q2

Can structures contain flexible arrays?

Yes.

Only as the last member.

---

## Q3

Can flexible arrays have a size?

No.

Wrong

```c
char data[10];
```

Correct

```c
char data[];
```

---

## Q4

Where are flexible arrays used?

- Linux Kernel
- Packets
- Drivers
- IPC
- Networking

---

## Q5

Why is `volatile` used with structures?

For hardware registers.

---

## Q6

What is `offsetof()`?

Returns the byte offset of a member within a structure.

---

## Q7

What is `container_of()`?

Returns the address of the containing structure given a pointer to one of its members.

---

## Q8

Difference between

```c
struct
```

and

```c
union
```

Structure

```
Separate Memory
```

Union

```
Shared Memory
```

---

## Q9

Can a structure contain itself?

No.

It can contain only a pointer to itself.

---

## Q10

Can bit-fields replace bit masking?

Sometimes.

However, for portable hardware code, explicit bit masking is often preferred because bit-field layout is implementation-defined.

---

# Common Interview Traps

### Trap 1

```c
struct Test
{
    char data[];

    int x;
};
```

Invalid.

Flexible array must be last.

---

### Trap 2

```c
s2 = s1;
```

Thinking

```
Deep Copy
```

Wrong.

It's a shallow copy when pointers are involved.

---

### Trap 3

```c
volatile

↓

Thread Synchronization
```

Wrong.

`volatile` does **not** make code thread-safe.

Use mutexes or atomic operations for synchronization.

---

### Trap 4

Thinking

```
const

↓

Object Stored In ROM
```

Wrong.

`const` means read-only through that access path. The actual storage location depends on the compiler and linker.

---

### Trap 5

Using bit-fields for communication protocols without checking compiler behavior.

Bit ordering and layout are implementation-defined.

---

# Real Embedded Examples

## Linux Kernel

```c
struct list_head
{
    struct list_head *next;
    struct list_head *prev;
};
```

Used with `container_of()`.

---

## Ethernet Packet

```c
struct Packet
{
    int length;
    char data[];
};
```

Flexible array member.

---

## GPIO Registers

```c
typedef struct
{
    unsigned MODER;
    unsigned IDR;
    unsigned ODR;
} GPIO_Type;
```

Memory-mapped register access.

---

## UART Status Register

```c
struct Status
{
    unsigned txReady : 1;
    unsigned rxReady : 1;
    unsigned error   : 1;
};
```

Represents hardware status bits.

---

# Quick Revision

```
Flexible Array

↓

Variable Size Data

------------------------

Bit-fields

↓

Bit-Level Storage

------------------------

offsetof()

↓

Member Offset

------------------------

container_of()

↓

Member Pointer

↓

Structure Pointer

------------------------

volatile Structure

↓

Hardware Registers

------------------------

Structure Copy

↓

Shallow Copy

------------------------

Deep Copy

↓

Allocate New Memory

↓

Copy Data
```

---


