# Chapter 2 – Storage Classes
# Part 1 – Fundamentals of Storage Classes

---

# Contents

# 1. What are Storage Classes?

Every variable in C has several properties besides its data type.

For example,

```c
int x;
```

The compiler needs to know:

- Where should `x` be stored?
- Who can access it?
- When is it created?
- When is it destroyed?
- Can another source file access it?

These properties are determined by the **Storage Class**.

A storage class specifies:

- Storage location
- Scope (Visibility)
- Lifetime (Existence)
- Linkage (Accessibility across source files)


# 2. Why are Storage Classes Needed?

Consider the following program.

void fun()
{
    int count = 0;

    count++;

    printf("%d\n", count);
}

Calling

fun();

Output

1

Why?

Because

count

is created every time the function is called.

Now change it to

static int count = 0;


2
3

The storage class changes the variable's lifetime.


# 3. Scope, Lifetime and Linkage

Before studying storage classes, understand these three terms.

Many interviewers ask them directly.


# Scope

Scope defines **where a variable can be accessed**.

Example

    int x = 10;

    printf("%d", x);

Valid

printf("%d", x);

inside the function.

Invalid

int main()

because `x` is outside its scope.


## Types of Scope

### Block Scope

Variables declared inside

{}

are visible only inside that block.


    {
        int x = 10;
    }

    printf("%d", x);      // Error


### File Scope

Variables declared outside every function.


int x = 100;


Visible from the declaration to the end of the source file (subject to linkage).


# Lifetime

Lifetime defines **how long the variable exists in memory**.


    int x = 5;

Memory is allocated

Function starts

Memory is released

Function ends


Static variable

static int x = 5;

Memory

Program starts

↓

Program ends


# Linkage

Linkage determines whether an identifier can be referred to from another source file.

There are three types.

### No Linkage

Local variables.


    int x;

Cannot be accessed outside the block.


### Internal Linkage

Visible only inside the current source file.

Created using

static

for global variables.


### External Linkage

Accessible from multiple source files.


extern

or by defining a global variable without `static`.


# Summary

| Property | Meaning |
|-----------|---------|
| Scope | Where can it be accessed? |
| Lifetime | How long does it exist? |
| Linkage | Can another source file access it? |


# 4. Types of Storage Classes

C provides four storage classes.

| Storage Class | Keyword |
|---------------|---------|
| Automatic | auto |
| Register | register |
| Static | static |
| External | extern |


# 5. auto Storage Class

This is the default storage class for local variables.


    auto int x = 10;

is exactly the same as


The compiler automatically assumes

auto


## Properties

| Property | Value |
|----------|-------|
| Scope | Block |
| Lifetime | Function Call |
| Storage | Stack |
| Initial Value | Garbage (indeterminate if not initialized) |
| Linkage | None |


## Example

#include <stdio.h>

    auto int x = 1;

    printf("%d\n", x);

    fun();



Each function call creates a new variable.


## Memory Diagram

Function Call


Stack

+---------+

x = 1



Function Ends


Memory Removed


# 6. register Storage Class

`register` suggests that the compiler keep the variable in a CPU register for faster access.


register int i;

Modern compilers decide automatically whether to use a register, so this keyword is only a hint and may be ignored.



| Storage | CPU Register (if possible) |



void sum()
    register int i;

    for(i = 0; i < 1000; i++)


## Why Use register?

Frequently used variables.

Examples

- Loop counters
- Small calculations
- Temporary values

Today, compiler optimizations generally make explicit `register` unnecessary.


## Limitation

You cannot apply the address-of operator to a register variable.

register int x = 10;

int *p = &x;      // Error

Reason

A register variable may not have a memory location that the program can take the address of.


# 7. static Storage Class

One of the most important interview topics.

`static` behaves differently depending on where it is used.

There are three common cases:

- Static local variable
- Static global variable
- Static function

We cover the first two in this part.


# Static Local Variable


    static int count = 0;








## Why?

Memory is allocated only once.

Program Starts


Memory Allocated


Function Called


Value Updated




Memory Retained


Next Call Uses Same Variable


Program Ends


Memory Released



| Lifetime | Entire Program |
| Storage | Data/BSS Segment |



Data Segment

+-----------+

count = 0



Call 1

count = 1


Call 2

count = 2


Call 3

count = 3


# Static Global Variable


static int counter = 100;

This variable is visible only inside the current source file.

Other files cannot access it.



| Scope | File |
| Linkage | Internal |


# Why Use Static Globals?

To hide implementation details.


driver.c


static int deviceState;

Only code inside


can access `deviceState`.

This is a common pattern in embedded software and Linux kernel code.


# 8. extern Storage Class

`extern` is used to access a global variable defined in another source file.



### file1.c

int counter = 100;


### file2.c

extern int counter;

void printCounter()
    printf("%d\n", counter);

The variable is defined only once, but can be used in multiple files.



| Linkage | External |


## Definition vs Declaration

Definition

int x = 10;

Creates storage.


Declaration

extern int x;

Does **not** create storage.

It tells the compiler that the variable exists elsewhere.


# Memory Summary




register

---------------------



Initialized static

Initialized global


BSS


Uninitialized static

Uninitialized global


Text


Functions


# Comparison Table

| Feature | auto | register | static (local) | static (global) | extern |
|----------|------|----------|----------------|-----------------|--------|
| Scope | Block | Block | Block | File | File |
| Lifetime | Function call | Function call | Entire Program | Entire Program | Entire Program |
| Linkage | None | None | None | Internal | External |
| Default Value | Garbage | Garbage | 0 | 0 | Defined elsewhere |
| Storage | Stack | Register/Stack | Data/BSS | Data/BSS | Data/BSS |


# Frequently Asked Interview Questions

### Q1. What are storage classes?

Storage classes define a variable's **scope, lifetime, storage location, and linkage**.


### Q2. What is the default storage class of a local variable?



### Q3. Why is `register` rarely used today?

Modern compilers perform register allocation automatically and usually make better decisions than manual hints.


### Q4. Difference between `static` and `extern`?

`static` (global)

- Internal linkage
- Visible only within the current source file

`extern`

- External linkage
- Refers to a variable defined in another source file


### Q5. Difference between a static local variable and a normal local variable?

Normal local variable

- Created on each function call
- Destroyed when the function returns

Static local variable

- Created once
- Retains its value across function calls


### Q6. Where are static variables stored?

In the **Data Segment** (initialized) or **BSS Segment** (uninitialized), not on the stack.


### Q7. What is the difference between declaration and definition?

A **declaration** tells the compiler that a variable or function exists.

A **definition** allocates storage (for variables) or provides the implementation (for functions).


# Key Takeaways

- Storage classes determine **scope, lifetime, storage location, and linkage**.
- `auto` is the default for local variables.
- `register` is a compiler hint and is rarely needed with modern optimizers.
- `static` local variables preserve their values between function calls.
- `static` global variables provide **internal linkage**, making them visible only within the current source file.
- `extern` allows access to global variables defined in other source files and provides **external linkage**.
- Understanding **scope**, **lifetime**, and **linkage** is essential for C interviews and for writing modular, maintainable programs.
-----------------------------------------------------------------------------------
# Part 2 – Scope, Linkage & Multi-File Programming (Interview Deep Dive)



1. Scope vs Lifetime vs Linkage
2. Block Scope
3. Function Scope
4. File Scope
5. Linkage
6. Internal Linkage
7. External Linkage
8. No Linkage
9. static Functions
10. Multiple Source Files
11. extern with Functions
12. Global Variables
13. Common Interview Questions
14. Best Practices
15. Key Takeaways


# 1. Scope vs Lifetime vs Linkage

These three terms are one of the most frequently asked interview topics.

Many candidates confuse them.

Think of them as answering three different questions.

| Property | Question |
|----------|----------|
| Scope | Where can I access it? |



Here

Scope


Inside fun()

Lifetime


Only during function execution

Linkage


None


# 2. Block Scope



have block scope.


    int a = 10;

        int b = 20;

        printf("%d\n", b);

    printf("%d\n", a);


20
10

Trying to access

b

outside the block

printf("%d", b);

Compiler Error


## Nested Blocks


        int y = 10;

        {
            int z = 15;
        }

Visibility

Outer Block


x


Inner Block


y


Innermost Block


z

Variables from outer blocks are visible in inner blocks.

Reverse is NOT true.


# Variable Shadowing


    int x = 20;




The local variable hides the global variable.



int value = 100;

    int value = 50;

    printf("%d\n", value);




100
50


# 3. Function Scope

Only labels have function scope.


start:

    printf("Hello");

    goto start;

The label

start

is visible everywhere inside that function.

It cannot be accessed from another function.


# 4. File Scope

Variables declared outside every function have file scope.


int count = 100;



The variable


can be used anywhere below its declaration in the same source file.


# 5. Linkage

Linkage determines whether an identifier can be shared across multiple source files.


No Linkage

Internal Linkage

External Linkage


# 6. No Linkage

Local variables have no linkage.



Another function cannot access



# 7. Internal Linkage



at file scope.


static int deviceState = 0;

Only

device.c

can access it.

Another source file

main.c

cannot use it.





deviceState

Visible only inside



# Internal Linkage Example

## driver.c

static int counter = 0;

void increment()
    counter++;


## main.c


    printf("%d", counter);

Compilation

Undefined Reference

Linker Error


counter

has internal linkage.


# 8. External Linkage

Default for global variables.


## file1.c

int counter = 10;


## file2.c









Shared by

file1.c

file2.c


# 9. static Functions

Many people know about static variables.

Fewer know about static functions.


static void helper()
    printf("Helper");

Only this source file can call

helper()



It hides implementation details.


uart.c


static parsePacket()


static checksum()


uart_send()



is exposed.

Everything else remains private.

This is similar to **private helper functions** in other languages.


# 10. Multiple Source Files

Suppose

Project




driver.h



void driverInit(void);



#include "driver.h"

void driverInit()




    driverInit();

Header files contain declarations.

Source files contain definitions.


# 11. extern with Functions

Functions are

by default




is equivalent to

extern void fun()

Therefore

extern void fun();

is usually unnecessary in header files.


# 12. Global Variables

Global variables should be minimized.

Bad

int temperature;

int pressure;

int speed;

int state;

int error;

Every file can modify them.

Difficult to debug.


Better

static int state;

Provide access through functions.

void setState(int s)
    state = s;

int getState()
    return state;

Encapsulation improves maintainability.


# Lifetime of Globals

Global variables





Remain Alive





Regardless of whether they are accessed.


# 13. Frequently Asked Interview Questions

## Q1. Difference between scope and linkage?




Can another source file access it?


## Q2. Difference between file scope and block scope?

Block Scope

Visible only inside {}

File Scope

Visible throughout the source file


## Q3. Difference between static local and static global?

Static Local


Program Lifetime


Static Global





## Q4. Difference between global and extern?

Global Variable

int count;



Extern Variable

extern int count;

Creates NO storage.

Only declares that storage exists elsewhere.


## Q5. Why make helper functions static?

To prevent accidental use from other source files and avoid namespace pollution.


## Q6. Can two files have static variables with the same name?

Yes.




static int count;




Both are completely independent because each has internal linkage.


## Q7. What happens if two source files define the same global variable?



int counter;



Result

Multiple Definition


Only one definition should exist.

Other files should use



# 14. Best Practices

✓ Prefer local variables over global variables.

✓ Use `static` for helper functions that should not be visible outside the file.

✓ Use `static` globals to hide module implementation details.

✓ Avoid exposing writable global variables.

✓ Share data across files using `extern` only when necessary.

✓ Place declarations in header files and definitions in source files.

✓ Keep global state minimal to improve modularity and testability.



- **Scope** determines where an identifier is visible.
- **Lifetime** determines how long it exists in memory.
- **Linkage** determines whether it can be shared across source files.
- Local variables have **block scope** and **no linkage**.
- Global variables have **file scope** and, by default, **external linkage**.
- `static` at file scope gives **internal linkage**, restricting visibility to one source file.
- `static` functions are private to their source file and are commonly used for helper routines.
- `extern` declares identifiers defined in another translation unit without allocating storage.
- Understanding how declarations, definitions, scope, lifetime, and linkage interact is essential for writing modular C programs and for succeeding in systems programming interviews.
- -----------------------------------------------------------------
# Part 3 – Memory Layout, Initialization & Advanced Interview Concepts



1. Variable Initialization
2. Where Variables are Stored
3. Stack vs Data vs BSS
4. Static Initialization Rules
5. extern and Initialization
6. Tentative Definitions
7. Declaration vs Definition
8. Common Linker Errors
9. Storage Classes and Recursion
10. Storage Classes and Threads
11. Storage Classes Summary
12. Interview Questions
13. Key Takeaways


# 1. Variable Initialization

One of the most common interview questions is:

> Which variables are initialized automatically?

The answer depends on the storage class.

| Variable Type | Default Value |
|--------------|---------------|
| Local (auto) | Garbage (Indeterminate) |
| register | Garbage (Indeterminate) |
| static | 0 |
| Global | 0 |





Garbage value (Undefined Behavior if read)



static int x;



0

because static variables are automatically initialized.


# 2. Where Variables are Stored

Consider

int global = 100;

static int staticGlobal = 50;

    int local = 10;

    static int counter = 0;

    char *p = malloc(100);

Memory Layout

+----------------------+
|      Stack           |
|----------------------|
| local                |

|      Heap            |
| malloc(100)          |

| Data Segment         |
| global               |
| staticGlobal         |
| counter              |

| Text Segment         |
| main()               |


# 3. Data Segment vs BSS

The compiler divides global/static variables into two sections.


## Data Segment

Initialized globals/statics.



static int y = 20;

Stored in



## BSS Segment

Uninitialized globals/statics.



static int total;



Both become


before

main()

starts.





Initialized Data




Heap




# 4. Static Initialization Rules

Only **constant expressions** can initialize static/global variables.

Correct

static int x = 100;


static int y = 10 + 20;

Wrong

int fun();

static int z = fun();



Static initialization happens **before program execution**, so function calls are not allowed.


# 5. extern and Initialization


/* file1.c */


/* file2.c */




extern int counter = 100;

This is **actually a definition**, not just a declaration.

If another file also defines


the linker reports

Multiple Definition Error


# 6. Tentative Definitions

One of the most misunderstood C topics.



Is this a declaration or a definition?

Answer

It is a **tentative definition**.

If no other definition exists,


becomes

int x = 0;





Compiler behaves as if


exists.




int x = 20;

Valid.

The second line is the actual definition.


# 7. Declaration vs Definition

Very common interview question.



Introduces a name.

No storage allocated.







int count = 0;




void fun();




Summary

| Statement | Declaration | Definition |
|-----------|-------------|------------|
| `extern int x;` | Yes | No |
| `int x;` | Yes | Tentative Definition |
| `int x = 10;` | Yes | Yes |
| `void fun();` | Yes | No |
| `void fun(){}` | Yes | Yes |


# 8. Common Linker Errors


## Multiple Definition


int count = 10;


int count = 20;


Multiple definition of count


## Undefined Reference



No source file defines



Undefined reference to count


## Static Visibility


static int count = 10;




Undefined reference

because


is hidden inside



# 9. Storage Classes and Recursion

Normal Local Variable

    int x = 0;

    x++;



Every recursive call gets a **new copy** of `x`.


Static Local Variable

    static int x = 0;





4
5
...

All recursive calls share the same variable.



Recursive Calls


Same static variable


# 10. Storage Classes and Threads



Two threads execute

counter++;

Problem

Both threads access the same variable.

Possible Result

Race Condition

Static **does not** provide thread safety.

Synchronization such as a mutex or atomic operations is still required.


# 11. Storage Classes Summary

| Feature | auto | register | static Local | static Global | extern |
|---------|------|----------|--------------|---------------|--------|
| Lifetime | Function | Function | Entire Program | Entire Program | Entire Program |
| Default Value | Garbage | Garbage | 0 | 0 | Defined Elsewhere |



                Program Memory

+------------------------------+
| Text Segment                 |
|------------------------------|
| Functions                    |

| Initialized Data             |
| Global = 10                  |
| static = 20                  |

| BSS                          |
| Global                       |
| static                       |

| Heap                         |
| malloc(), calloc()           |

| Stack                        |
| auto                         |
| register                     |
| Function Frames              |



### Q1. Why are static variables initialized only once?

Memory is allocated before `main()` starts and remains allocated until the program exits.


### Q2. Can a static variable be initialized using a function call?

No.

Only constant expressions are allowed for static and global initialization.


### Q3. What is a tentative definition?

A declaration like


that becomes a definition if no other definition exists in the translation unit.


### Q4. Why does `extern` not allocate memory?

`extern` only informs the compiler that the object is defined elsewhere.


### Q5. Can static variables cause race conditions?


`static` controls **lifetime and linkage**, not synchronization.


### Q6. Where are global variables stored?

- Initialized globals → Data Segment
- Uninitialized globals → BSS Segment


### Q7. Why are automatic variables not initialized?

Automatically initializing every local variable would incur runtime overhead. The language leaves them indeterminate unless explicitly initialized.


### Q8. Is `register` guaranteed to place a variable in a CPU register?


It is only a compiler hint. Modern optimizing compilers decide the best storage location.


# Best Practices

✓ Initialize local variables before use.

✓ Minimize global variables.

✓ Use `static` to hide implementation details.

✓ Use `extern` only for shared interfaces.

✓ Prefer passing data through function parameters rather than global state.

✓ Keep one definition of every global variable.

✓ Declare shared globals in a header using `extern` and define them in exactly one source file.



- Automatic (`auto`) and `register` variables have automatic storage duration and are not automatically initialized.
- Global and `static` variables have static storage duration and are zero-initialized if no explicit initializer is provided.
- Initialized globals/statics are stored in the **Data Segment**; uninitialized ones are stored in the **BSS**.
- `extern` declares an object or function defined elsewhere and does not allocate storage.
- A tentative definition (`int x;`) becomes the definition if no other definition exists.
- `static` affects visibility and lifetime, but **does not provide thread safety**.
- Understanding declarations, definitions, memory layout, and linker behavior is essential for debugging multi-file C projects and for systems programming interviews.


# Next Part

**Part 4 – 70+ Storage Class Interview Questions & Coding Problems**
---------------------------------------------------------------
# Part 4 – 70+ Storage Class Interview Questions & Coding Problems



1. Conceptual Interview Questions
2. Predict the Output Questions
3. Multi-file Programming Questions
4. Memory Layout Questions
5. Coding Problems
6. Common Mistakes
7. Company-Specific Questions
8. Key Takeaways


# 1. Conceptual Interview Questions

## Q1. What is a storage class?

**Answer**


- Storage duration (lifetime)
- Scope
- Linkage
- Storage location (conceptually)


## Q2. How many storage classes are there?

There are four storage class specifiers commonly used in C:

- auto
- register
- static
- extern

(C11 also introduces `_Thread_local`, which we'll cover later.)


## Q3. What is the default storage class of a local variable?



## Q4. What is the default storage class of a global variable?

Global variables have:

- Static storage duration
- External linkage (unless declared `static`)


## Q5. What is the lifetime of


variables?

Only during function execution.


## Q6. What is the lifetime of



Entire program execution.


## Q7. What is the difference between scope and lifetime?


Where variable is visible.


How long memory exists.


## Q8. What is linkage?

Whether the identifier can be referred to from another translation unit (source file).


## Q9. Difference between


and


| static | extern |
|---------|---------|
| Internal linkage | External linkage |
| Hidden from other files | Shared across files |


## Q10. What is the difference between declaration and definition?






# 2. Predict the Output Questions


## Question 1




    printf("%d ", x);



1 1 1


Each function call creates a new local variable.


## Question 2







1 2 3


## Question 3







Local variable shadows the global variable.


## Question 4








## Question 5







## Question 6


    static int x;





0 1 2


## Question 7


int fun()
    static int x = 5;

    return x++;

    printf("%d ", fun());


5 6 7


## Question 8


    register int x = 5;






## Question 9

register int x = 5;

Is it valid?


❌ No.

`register` can only be applied to objects with automatic storage duration (typically local variables or function parameters).


## Question 10


int *p = &x;


Compiler Error.

The address of a register variable cannot be taken.


# 3. Multi-file Programming Questions


## Question 11





Valid?

✅ Yes.


## Question 12


static int count = 100;






## Question 13






Multiple definition

(On many modern toolchains using `-fno-common`; historically some linkers accepted tentative definitions. Know the compiler/toolchain behavior.)


## Question 14

Which file should contain



Usually

header file


## Question 15

Where should


be written?

Exactly one

source file


# 4. Memory Layout Questions


## Question 16

Where is


declared globally stored?




## Question 17



stored?




## Question 18



inside a function stored?



## Question 19





(or Data segment if initialized with a non-zero constant.)


## Question 20


malloc()

memory stored?



# 5. Coding Problems


## Problem 1

Write a function that counts how many times it has been called.

Solution


void counter()



    counter();




## Problem 2

Generate unique IDs.

int getNextID()
    static int id = 1000;

    return id++;


1000

1001

1002


## Problem 3

Count recursive calls.


void recur(int n)
    static int calls = 0;

    calls++;

    printf("Call %d\n", calls);

    if(n)
        recur(n - 1);

    recur(4);


Call 4
Call 5


## Problem 4

Hide a module variable.

/* driver.c */

static int state = 0;


int getState(void)

Only `driver.c` can directly access `state`.


## Problem 5

Implement a singleton-like configuration.

typedef struct
    int timeout;
    int retries;
} Config;

Config *getConfig(void)
    static Config cfg = {10, 3};

    return &cfg;


# 6. Common Mistakes


## Mistake 1

Confusing


with


They are independent concepts.


## Mistake 2

Thinking


means

Global

It does **not**.

It changes meaning depending on where it is used.


## Mistake 3

Using


without an actual definition.




## Mistake 4

Defining globals inside header files.


/* config.h */


Every source file including the header creates another definition.




/* config.c */



## Mistake 5

Using too many global variables.

Large embedded projects avoid this because it increases coupling and makes testing harder.


# 7. Company-Specific Questions

These questions are frequently asked in Qualcomm, NVIDIA, AMD, Broadcom, Intel, Samsung, and Linux kernel interviews.

### Easy

- What is the default storage class of a local variable?
- Difference between auto and static?
- What is extern?
- Where are global variables stored?
- Difference between stack and heap?


### Medium

- Explain scope, lifetime, and linkage.
- Difference between static local and static global.
- Difference between declaration and definition.
- Why use static helper functions?
- What happens if two source files define the same global?


### Advanced

- Explain tentative definitions.
- Explain BSS vs Data segment.
- Can `static` cause race conditions?
- Can `register` variables be optimized away?
- How does the linker resolve `extern` variables?
- What is a translation unit?
- Why should global variables be minimized in embedded software?


# Quick Revision Sheet

| Keyword | Scope | Lifetime | Linkage |
|----------|--------|----------|----------|
| auto | Block | Function | None |
| register | Block | Function | None |
| static local | Block | Program | None |
| static global | File | Program | Internal |
| extern | File | Program | External |



- Master **scope**, **lifetime**, and **linkage**—they are foundational interview topics.
- Understand how `static` behaves differently for local variables, global variables, and functions.
- Use `extern` for declarations shared across translation units, with exactly one definition.
- Avoid defining global variables in header files.
- Know where different kinds of variables reside in memory (Stack, Heap, Data, BSS).
- Be familiar with linker errors such as **multiple definition** and **undefined reference** and how to fix them.
