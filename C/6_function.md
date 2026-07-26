# C Interview Handbook
# Chapter 6 – Functions
# Part 1 – Function Basics (Declaration, Definition, Prototype & Call Stack)

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- Why functions are needed
- Function declaration
- Function definition
- Function prototype
- Function call
- Function parameters
- Function return values
- Function call stack
- Stack frame creation
- Common interview questions

---

# Why Do We Need Functions?

Suppose we need to calculate the square of several numbers.

Without functions

```c
#include <stdio.h>

int main()
{
    int a = 5;
    printf("%d\n", a * a);

    int b = 10;
    printf("%d\n", b * b);

    int c = 15;
    printf("%d\n", c * c);
}
```

Problems

- Code duplication
- Hard to maintain
- Difficult to reuse

Instead

```c
int square(int x)
{
    return x * x;
}
```

Now

```c
printf("%d\n", square(5));
printf("%d\n", square(10));
printf("%d\n", square(15));
```

---

# What is a Function?

A function is a named block of code that performs a specific task.

```
Program

↓

Calls Function

↓

Function Executes

↓

Returns Result
```

---

# Anatomy of a Function

Example

```c
int add(int a, int b)
{
    return a + b;
}
```

Breakdown

```
int

↓

Return Type

--------------------

add

↓

Function Name

--------------------

(int a, int b)

↓

Parameters

--------------------

{

}

↓

Function Body
```

---

# Function Definition

A function definition contains the complete implementation.

```c
int multiply(int a, int b)
{
    return a * b;
}
```

This tells the compiler

- Function name
- Return type
- Parameters
- Implementation

---

# Function Declaration (Prototype)

A declaration tells the compiler that a function exists.

```c
int multiply(int, int);
```

Notice

```
No Function Body
```

This is also called a

```
Function Prototype
```

---

# Why Do We Need Prototypes?

Example

```c
#include <stdio.h>

int main()
{
    printf("%d\n", add(10, 20));
}

int add(int a, int b)
{
    return a + b;
}
```

Modern C compilers produce an error because `add()` is used before the compiler has seen its declaration.

Correct

```c
int add(int, int);

int main()
{
    printf("%d\n", add(10, 20));
}

int add(int a, int b)
{
    return a + b;
}
```

---

# Declaration vs Definition

| Declaration | Definition |
|--------------|------------|
| Tells compiler the function exists | Provides the implementation |
| Ends with `;` | Contains function body |
| May appear multiple times (if identical) | Normally appears only once |

---

# Function Call

Example

```c
int add(int a, int b)
{
    return a + b;
}

int main()
{
    int result = add(10, 20);
}
```

Execution

```
main()

↓

Call add()

↓

Execute Function

↓

Return 30

↓

Continue main()
```

---

# Parameter vs Argument

Example

```c
int add(int x, int y)
{
    return x + y;
}

int main()
{
    add(5, 10);
}
```

```
Function Definition

↓

x

↓

Parameter

--------------------

5

↓

Argument
```

Summary

| Parameter | Argument |
|------------|-----------|
| Variable in function definition | Actual value passed during call |

---

# Return Type

Example

```c
int square(int x)
{
    return x * x;
}
```

Return type

```
int
```

Function returns an integer.

---

# Returning Nothing

If a function returns nothing

```c
void printHello()
{
    printf("Hello");
}
```

Return type

```
void
```

---

# Returning Multiple Values?

A function can return only one value directly.

Wrong

```c
return a, b;
```

Instead

- Return a structure
- Pass pointers
- Return an array through pointers

Example

```c
void calculate(int a,
               int b,
               int *sum,
               int *product)
{
    *sum = a + b;
    *product = a * b;
}
```

---

# Function with No Parameters

```c
void hello(void)
{
    printf("Hello");
}
```

Using `void` clearly indicates the function takes no arguments.

---

# Function Call Stack

One of the most important interview topics.

Example

```c
void fun2()
{
}

void fun1()
{
    fun2();
}

int main()
{
    fun1();
}
```

Execution

```
main()

↓

fun1()

↓

fun2()

↓

Return

↓

fun1()

↓

Return

↓

main()
```

---

# Stack Frames

Every function call creates a

```
Stack Frame
```

It contains

- Local variables
- Function parameters
- Return address
- Saved registers (implementation-dependent)

Example

```c
void fun()
{
    int x = 10;
}
```

Memory

```
+--------------------+
| Return Address     |
+--------------------+
| Parameter(s)       |
+--------------------+
| Local Variable x   |
+--------------------+
```

When the function returns,

the stack frame is removed.

---

# Nested Function Calls

Example

```c
void C()
{
}

void B()
{
    C();
}

void A()
{
    B();
}

int main()
{
    A();
}
```

Call Stack

```
+----------------+
| C              |
+----------------+
| B              |
+----------------+
| A              |
+----------------+
| main           |
+----------------+
```

After `C()` returns

```
+----------------+
| B              |
+----------------+
| A              |
+----------------+
| main           |
+----------------+
```

---

# Lifetime of Local Variables

```c
void fun()
{
    int x = 100;
}
```

```
Call Function

↓

Create x

↓

Return

↓

Destroy x
```

This is why returning the address of a local variable is incorrect.

---

# Scope of Parameters

```c
void add(int a, int b)
{
    printf("%d", a);
}
```

Variables `a` and `b` exist only inside `add()`.

---

# Common Interview Questions

---

## Q1

Difference between declaration and definition?

Declaration

```
Compiler knows function exists.
```

Definition

```
Actual implementation.
```

---

## Q2

Why are function prototypes required?

They allow the compiler to verify:

- Function exists
- Correct return type
- Correct parameter types

before the function is called.

---

## Q3

Can a function return an array?

No.

Instead return

- Pointer
- Structure
- Dynamically allocated memory

---

## Q4

Can a function return a structure?

Yes.

```c
struct Point
{
    int x;
    int y;
};

struct Point getPoint(void)
{
    struct Point p = {10, 20};
    return p;
}
```

---

## Q5

Can a function return another function?

No.

But it can return

```
Pointer To Function
```

---

## Q6

What happens when a function is called?

- Arguments are prepared.
- A stack frame is created.
- Control transfers to the function.
- On return, the stack frame is removed.
- Execution resumes after the call.

---

## Q7

Where are local variables stored?

Normally on the

```
Stack
```

---

# Common Interview Traps

### Trap 1

Calling a function before its declaration.

```c
main()
{
    add();
}
```

Without a prototype, modern C compilers diagnose this as an error.

---

### Trap 2

Returning the address of a local variable.

```c
int *fun()
{
    int x = 10;
    return &x;
}
```

Creates a dangling pointer.

---

### Trap 3

Confusing parameters and arguments.

```
Function Definition

↓

Parameters

Function Call

↓

Arguments
```

---

### Trap 4

Assuming local variables exist after the function returns.

They do not.

---

# Real Embedded Examples

## Driver Initialization

```c
void uart_init(void)
{
    /* Configure UART */
}
```

---

## GPIO Driver

```c
void gpio_set(int pin)
{
    /* Set GPIO pin */
}
```

---

## ADC Reading

```c
int adc_read(int channel)
{
    return value;
}
```

---

## Interrupt Handler Helper

```c
void process_packet(void)
{
    /* Decode packet */
}
```

---

# Quick Revision

```
Function

↓

Reusable Code

------------------------

Prototype

↓

Declaration

↓

No Body

------------------------

Definition

↓

Complete Implementation

------------------------

Call

↓

Create Stack Frame

↓

Execute

↓

Return

↓

Destroy Stack Frame

------------------------

Parameters

↓

Definition

------------------------

Arguments

↓

Function Call
```

---

# Key Interview Takeaways

✅ A function prototype allows the compiler to verify calls before seeing the implementation.

✅ Every function call creates a new stack frame.

✅ Local variables exist only while the function is executing.

✅ Parameters belong to the function definition; arguments are the values passed by the caller.

✅ A function can return a structure or pointer, but not an array or another function directly.

---

# Next Part

In **Part 2**, we'll cover one of the most frequently asked interview topics:

- Call by Value
- Passing Pointers
- Simulating Call by Reference
- Returning Pointers
- Returning Structures
- Returning Static Variables
- Returning Dynamic Memory
- 30+ Qualcomm, NVIDIA, Broadcom, AMD, and Intel interview questions.
- -----------------------------------------------------------------------------
# C Interview Handbook
# Chapter 6 – Functions
# Part 2 – Call by Value, Pointers, Returning Values & Common Interview Questions

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- Call by Value
- Why C has no Call by Reference
- Passing Pointers
- Simulating Call by Reference
- Returning Values
- Returning Pointers
- Returning Structures
- Returning Static Variables
- Returning Dynamic Memory
- Common interview mistakes

---

# How Are Arguments Passed in C?

One of the most frequently asked interview questions.

**Important:**

> **C supports only Call by Value.**

There is **no Call by Reference** in C.

---

# Call by Value

Example

```c
#include <stdio.h>

void change(int x)
{
    x = 100;
}

int main()
{
    int a = 10;

    change(a);

    printf("%d\n", a);
}
```

Output

```
10
```

---

# Why Didn't It Change?

When calling

```c
change(a);
```

Memory

```
main()

a = 10

↓

Copy

↓

change()

x = 10
```

Both variables are different.

```
a

↓

10

----------------

x

↓

10
```

Changing

```
x
```

does **not** affect

```
a
```

---

# Stack View

Before function call

```
main()

+---------+
| a = 10  |
+---------+
```

During function call

```
change()

+---------+
| x = 10  |
+---------+

main()

+---------+
| a = 10  |
+---------+
```

Two separate variables exist.

---

# Example

```c
void fun(int x)
{
    x++;

    printf("%d\n", x);
}

int main()
{
    int a = 5;

    fun(a);

    printf("%d\n", a);
}
```

Output

```
6
5
```

---

# Can We Modify the Original Variable?

Yes.

Pass its address.

---

# Passing a Pointer

Example

```c
void change(int *ptr)
{
    *ptr = 100;
}

int main()
{
    int a = 10;

    change(&a);

    printf("%d\n", a);
}
```

Output

```
100
```

---

# Memory Diagram

```
main()

a

↓

10

Address

↓

1000
```

Call

```c
change(&a);
```

Function

```
ptr

↓

1000
```

Now

```c
*ptr = 100;
```

changes

```
Address

1000

↓

a
```

---

# Why Does This Work?

The pointer itself is still passed **by value**.

```
main()

&a

↓

1000

↓

Copied

↓

ptr

↓

1000
```

The pointer is copied,

but both pointers refer to the **same memory location**.

---

# Interview Question

**Does C support Call by Reference?**

Answer

```
No.

C supports only

↓

Call by Value.
```

Passing pointers only **simulates** reference behavior.

---

# Swapping Two Numbers

Wrong

```c
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}
```

Main

```c
int x = 10;
int y = 20;

swap(x, y);
```

Output

```
10 20
```

Nothing changes.

---

# Correct Swap

```c
void swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;

    *b = temp;
}
```

Main

```c
swap(&x, &y);
```

Output

```
20 10
```

---

# Returning a Value

Simplest case.

```c
int square(int x)
{
    return x * x;
}
```

---

# Returning a Structure

Allowed.

```c
struct Point
{
    int x;
    int y;
};

struct Point getPoint(void)
{
    struct Point p = {10, 20};

    return p;
}
```

---

# Returning a Pointer

Allowed,

but be careful.

---

## Wrong Example

```c
int* fun()
{
    int x = 10;

    return &x;
}
```

Memory

```
Function Called

↓

x Created

↓

Function Returns

↓

x Destroyed

↓

Returned Pointer

↓

Dangling
```

---

# Correct Example 1

Return dynamically allocated memory.

```c
int* fun()
{
    int *p =
    malloc(sizeof(int));

    if(p != NULL)
        *p = 10;

    return p;
}
```

Caller

```c
int *ptr = fun();

free(ptr);
```

---

# Correct Example 2

Return a static variable.

```c
int* fun()
{
    static int x = 10;

    return &x;
}
```

Static variables live until the program ends.

---

# Static Variable Example

```c
#include <stdio.h>

int* counter()
{
    static int count = 0;

    count++;

    return &count;
}

int main()
{
    printf("%d\n", *counter());

    printf("%d\n", *counter());

    printf("%d\n", *counter());
}
```

Output

```
1
2
3
```

---

# Returning Dynamically Allocated Arrays

Correct

```c
int* createArray(void)
{
    int *arr =
    malloc(5 * sizeof(int));

    if(arr == NULL)
        return NULL;

    for(int i = 0; i < 5; i++)
        arr[i] = i + 1;

    return arr;
}
```

Caller

```c
int *arr = createArray();

/* Use arr */

free(arr);
```

---

# Returning String Literals

Correct

```c
const char* fun()
{
    return "Qualcomm";
}
```

String literals remain valid throughout program execution.

Never modify them.

---

# Returning Local Character Arrays

Wrong

```c
char* fun()
{
    char str[20] = "Hello";

    return str;
}
```

Reason

```
Local Array

↓

Stack

↓

Destroyed

↓

Dangling Pointer
```

---

# Correct Version

```c
char* fun()
{
    static char str[] = "Hello";

    return str;
}
```

or

```c
char* fun()
{
    char *str =
    malloc(20);

    strcpy(str, "Hello");

    return str;
}
```

Caller must call

```c
free(str);
```

---

# Returning Multiple Values

Method 1

Use pointers.

```c
void calculate(int a,
               int b,
               int *sum,
               int *product)
{
    *sum = a + b;

    *product = a * b;
}
```

---

Method 2

Return a structure.

```c
struct Result
{
    int sum;
    int product;
};

struct Result calculate(int a, int b)
{
    struct Result r;

    r.sum = a + b;
    r.product = a * b;

    return r;
}
```

---

# Common Interview Questions

---

## Q1

Does C support Call by Reference?

No.

Only

```
Call by Value
```

---

## Q2

Why does passing a pointer allow modification?

Because the copied pointer still points to the same object.

---

## Q3

Can a function return an array?

No.

Return

- Pointer
- Structure

instead.

---

## Q4

Can a function return a structure?

Yes.

Perfectly valid.

---

## Q5

Can a function return a pointer?

Yes.

But never return the address of a local variable.

---

## Q6

Where should returned memory come from?

Safe sources include:

- Static storage
- Dynamically allocated memory
- String literals (as `const char *`)

Unsafe source:

- Local variables

---

## Q7

Why is returning a local variable wrong?

Because its stack frame is destroyed after the function returns.

---

## Q8

Who frees dynamically allocated memory returned by a function?

The caller.

---

## Q9

Can we return `NULL`?

Yes.

This is the standard way to indicate failure for pointer-returning functions.

---

## Q10

How do C++ references differ?

C++

```cpp
void fun(int &x)
```

supports true reference parameters.

C has no reference type.

---

# Common Interview Traps

### Trap 1

```c
void swap(int a, int b);
```

Expecting caller variables to change.

---

### Trap 2

```c
return &localVariable;
```

Creates a dangling pointer.

---

### Trap 3

Returning heap memory

```c
malloc()
```

and forgetting

```c
free()
```

Memory leak.

---

### Trap 4

Returning a pointer to a string literal

```c
char *p = "Hello";

p[0] = 'h';
```

Undefined behavior.

Use

```c
const char *p = "Hello";
```

---

# Real Embedded Examples

## Reading Sensor Data

```c
void readSensor(int *temperature)
{
    *temperature = 42;
}
```

---

## Driver Initialization

```c
int driver_init(void)
{
    return 0;
}
```

---

## Packet Parsing

```c
struct Packet parse(void)
{
    struct Packet p;

    return p;
}
```

---

## Buffer Allocation

```c
char* allocateBuffer(size_t size)
{
    return malloc(size);
}
```

Caller owns the returned buffer.

---

# Quick Revision

```
C

↓

Only Call by Value

------------------------

Pass Address

↓

Modify Original Variable

------------------------

Safe Return

↓

Value

↓

Structure

↓

Static Variable

↓

Heap Memory

------------------------

Unsafe Return

↓

Local Variable

↓

Local Array

------------------------

Heap Memory

↓

Caller Must free()
```

---

# Key Interview Takeaways

✅ C always passes arguments by value.

✅ Passing pointers allows functions to modify the caller's data.

✅ Never return the address of a local variable or local array.

✅ Returning structures is completely valid in C.

✅ If a function returns dynamically allocated memory, the caller is responsible for freeing it.

---

# Next Part

In **Part 3**, we'll cover advanced function topics that are asked very frequently in Qualcomm, NVIDIA, Broadcom, AMD, and Intel interviews:

- Recursion
- Tail Recursion
- Stack Growth During Recursion
- Mutual Recursion
- Function Pointer Basics
- Arrays of Function Pointers
- Callback Functions
- Variable Argument Functions (`va_list`, `va_start`, `va_arg`, `va_end`)
- `inline` Functions
- `static` Functions
- `extern` Functions
- 60+ interview questions.
- ---------------------------------------------------------------------------------
# C Interview Handbook
# Chapter 6 – Functions
# Part 3 – Recursion, Function Pointers, Callbacks & Variable Arguments

> **Target Companies:** Qualcomm • NVIDIA • Broadcom • AMD • Intel • Samsung • Cisco • Linux Kernel Teams

---

# Objectives

After completing this chapter, you should understand:

- Recursion
- Call Stack Growth
- Tail Recursion
- Mutual Recursion
- Function Pointers
- Arrays of Function Pointers
- Callback Functions
- Variable Argument Functions (`stdarg.h`)
- `inline` Functions
- `static` Functions
- `extern` Functions
- Common interview questions

---

# What is Recursion?

A function calling itself is known as **recursion**.

Example

```c
void fun()
{
    printf("Hello\n");

    fun();
}
```

Execution

```
fun()

↓

fun()

↓

fun()

↓

fun()

↓

...
```

Eventually,

```
Stack Overflow
```

because there is no stopping condition.

---

# Base Case

Every recursive function **must** have a base case.

Example

```c
void print(int n)
{
    if(n == 0)
        return;

    printf("%d ", n);

    print(n - 1);
}
```

Output

```
5 4 3 2 1
```

---

# How Recursion Works

Example

```c
print(3);
```

Execution

```
print(3)

↓

print(2)

↓

print(1)

↓

print(0)

↓

Return

↓

Return

↓

Return
```

---

# Call Stack During Recursion

```c
print(3);
```

Stack

```
+----------------+
| print(0)       |
+----------------+
| print(1)       |
+----------------+
| print(2)       |
+----------------+
| print(3)       |
+----------------+
| main()         |
+----------------+
```

Each function call creates a **new stack frame**.

---

# Factorial Example

```c
int factorial(int n)
{
    if(n == 0)
        return 1;

    return n * factorial(n - 1);
}
```

Call

```c
factorial(4);
```

Execution

```
factorial(4)

↓

4 * factorial(3)

↓

4 * 3 * factorial(2)

↓

4 * 3 * 2 * factorial(1)

↓

4 * 3 * 2 * 1

↓

24
```

---

# Recursive vs Iterative

Recursive

```c
int factorial(int n)
{
    if(n == 0)
        return 1;

    return n * factorial(n - 1);
}
```

Iterative

```c
int factorial(int n)
{
    int result = 1;

    while(n > 1)
    {
        result *= n;
        n--;
    }

    return result;
}
```

---

# Which is Better?

| Recursive | Iterative |
|-----------|-----------|
| Cleaner for recursive problems | Usually faster |
| Uses stack space | Constant stack space |
| Easier for trees/graphs | Better for simple loops |

---

# Tail Recursion

A recursive function is **tail recursive** when the recursive call is the **last operation**.

Example

```c
void print(int n)
{
    if(n == 0)
        return;

    printf("%d ", n);

    print(n - 1);
}
```

The recursive call is the final statement.

---

# Non-Tail Recursion

```c
void print(int n)
{
    if(n == 0)
        return;

    print(n - 1);

    printf("%d ", n);
}
```

Here,

```
print()

↓

Returns

↓

printf()
```

Work remains after the recursive call.

---

# Tail Call Optimization (TCO)

Some compilers optimize tail recursion into a loop.

Benefits

- No stack growth
- Better performance

**Interview Note**

The C standard **does not require** tail-call optimization. Whether it happens depends on the compiler and optimization settings.

---

# Mutual Recursion

Two functions call each other.

```c
void odd(int);

void even(int n)
{
    if(n == 0)
        return;

    printf("%d ", n);

    odd(n - 1);
}

void odd(int n)
{
    if(n == 0)
        return;

    printf("%d ", n);

    even(n - 1);
}
```

Execution

```
even()

↓

odd()

↓

even()

↓

odd()
```

---

# Function Pointer

One of the most frequently asked interview topics.

Every function has an address.

```c
int add(int a, int b)
{
    return a + b;
}
```

Memory

```
add()

↓

Address

↓

0x5000
```

We can store this address in a pointer.

---

# Function Pointer Syntax

```c
int (*fp)(int, int);
```

Read it from the variable name outward:

```
fp

↓

Pointer

↓

Function

↓

Returns int
```

---

# Assigning a Function

```c
int add(int a, int b)
{
    return a + b;
}

int (*fp)(int, int);

fp = add;
```

Calling

```c
printf("%d\n", fp(10, 20));
```

or

```c
printf("%d\n", (*fp)(10, 20));
```

Output

```
30
```

Both forms are equivalent.

---

# Why Parentheses?

Wrong

```c
int *fp(int, int);
```

Meaning

```
Function

↓

Returns

↓

Pointer
```

Correct

```c
int (*fp)(int, int);
```

Meaning

```
Pointer

↓

To Function
```

---

# Passing Function Pointer

```c
int add(int a, int b)
{
    return a + b;
}

void calculate(int x,
               int y,
               int (*operation)(int, int))
{
    printf("%d\n",
           operation(x, y));
}

int main()
{
    calculate(10, 20, add);
}
```

Output

```
30
```

---

# Callback Function

A callback is simply a function passed to another function.

```
main()

↓

calculate()

↓

Calls

↓

add()
```

Real-life examples

- `qsort()`
- Interrupt handlers
- Event handlers
- Driver frameworks

---

# qsort() Callback

```c
int compare(const void *a,
            const void *b)
{
    return (*(int*)a - *(int*)b);
}
```

Used as

```c
qsort(array,
      size,
      sizeof(int),
      compare);
```

The sorting algorithm calls `compare()` whenever it needs to compare two elements.

---

# Array of Function Pointers

```c
int add(int,int);
int sub(int,int);
int mul(int,int);

int (*operations[])(int,int) =
{
    add,
    sub,
    mul
};
```

Call

```c
operations[0](5, 3);
```

Result

```
8
```

Useful for implementing menus, command tables, and state machines.

---

# Variable Argument Functions

Header

```c
#include <stdarg.h>
```

Useful when the number of arguments is unknown.

Example

```c
printf()
```

accepts a variable number of arguments.

---

# Important Macros

```
va_list

↓

Stores Argument List

-----------------------

va_start()

↓

Initialize

-----------------------

va_arg()

↓

Read Next Argument

-----------------------

va_end()

↓

Cleanup
```

---

# Example

```c
#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...)
{
    va_list args;

    va_start(args, count);

    int total = 0;

    for(int i = 0; i < count; i++)
    {
        total += va_arg(args, int);
    }

    va_end(args);

    return total;
}

int main()
{
    printf("%d\n",
           sum(4, 10, 20, 30, 40));
}
```

Output

```
100
```

---

# inline Function

```c
inline int square(int x)
{
    return x * x;
}
```

Meaning

```
Compiler

↓

May Replace

↓

Function Call

↓

With Function Body
```

This is only a request to the compiler, not a guarantee.

---

# static Function

```c
static void helper(void)
{
}
```

Meaning

```
Visible

↓

Only Inside Current Source File
```

Useful for internal helper functions.

---

# extern Function

Functions have external linkage by default.

```c
extern void uart_init(void);
```

This declaration indicates the function is defined in another translation unit (source file).

---

# Common Interview Questions

---

## Q1

Why is recursion slower?

Each recursive call creates a new stack frame.

---

## Q2

What happens if recursion has no base case?

```
Infinite Recursion

↓

Stack Overflow
```

---

## Q3

Difference between recursion and iteration?

| Recursion | Iteration |
|-----------|-----------|
| Uses call stack | Uses loops |
| Elegant for recursive problems | Usually more efficient |

---

## Q4

What is a function pointer?

A pointer that stores the address of a function.

---

## Q5

Why are function pointers used?

- Callbacks
- Driver tables
- State machines
- Interrupt handlers
- Dynamic behavior

---

## Q6

What is a callback?

A function passed as an argument to another function.

---

## Q7

What does `va_start()` do?

Initializes access to the variable argument list.

---

## Q8

Does `inline` guarantee inlining?

No.

The compiler decides whether to inline the function.

---

## Q9

Why use `static` functions?

To hide implementation details within a source file and avoid symbol conflicts.

---

## Q10

What is the difference between

```c
fp()
```

and

```c
(*fp)()
```

None.

Both invoke the function pointed to by `fp`.

---

# Common Interview Traps

### Trap 1

Forgetting the base case in recursion.

---

### Trap 2

Confusing

```c
int *fp();
```

with

```c
int (*fp)();
```

---

### Trap 3

Forgetting

```c
va_end();
```

after using `va_list`.

---

### Trap 4

Assuming `inline` always removes function call overhead.

It may not.

---

# Real Embedded Examples

## Interrupt Vector Table

```c
void (*vectorTable[])(void) =
{
    resetHandler,
    timerHandler,
    uartHandler
};
```

---

## State Machine

```c
void (*state[])(void) =
{
    idleState,
    runState,
    errorState
};
```

---

## Driver Callback

```c
registerCallback(uartRxHandler);
```

---

## Generic Sort

```c
qsort(data,
      count,
      sizeof(data[0]),
      compare);
```

---

# Quick Revision

```
Recursion

↓

Function Calls Itself

↓

Needs Base Case

------------------------

Tail Recursion

↓

Recursive Call Last

------------------------

Function Pointer

↓

Stores Function Address

------------------------

Callback

↓

Function Passed

↓

To Another Function

------------------------

Variable Arguments

↓

va_list

↓

va_start

↓

va_arg

↓

va_end

------------------------

inline

↓

Compiler Hint

------------------------

static Function

↓

File Scope Only
```

---

# Key Interview Takeaways

✅ Every recursive call creates a new stack frame.

✅ Tail recursion may be optimized, but it is not guaranteed in C.

✅ Function pointers are essential for callbacks, driver frameworks, interrupt tables, and state machines.

✅ `qsort()` is the classic interview example demonstrating callbacks.

✅ `va_list` enables functions like `printf()` to accept a variable number of arguments.

✅ `static` functions limit visibility to a single source file, improving encapsulation.

---

# Next Chapter

**Chapter 7 – Arrays & Strings**

We'll cover:

- 1D and 2D Arrays
- Arrays vs Pointers
- Multidimensional Arrays
- Character Arrays
- Strings and String Literals
- String Functions (`strlen`, `strcpy`, `strncpy`, `strcmp`, `strtok`, etc.)
- Array Decay
- Variable Length Arrays (VLAs)
- Flexible Array Members
- Memory Layout of Arrays
- 80+ interview questions from Qualcomm, NVIDIA, Broadcom, AMD, Intel, and Linux kernel interviews.
- -------------------------------------------------------------------------------
