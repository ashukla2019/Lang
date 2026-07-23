# C++ Templates Complete Handbook

> **Part 1 - Introduction, Function Templates & Template Instantiation**

---

# Table of Contents

## Part 1
- What are Templates?
- Why Templates?
- Function Templates
- How Compiler Generates Code
- Template Instantiation
- Template Argument Deduction
- Multiple Template Parameters
- Default Template Arguments
- Interview Questions

---

# 1. What are Templates?

## Definition

A **Template** is a blueprint for writing **generic code**.

Instead of writing the same function or class for different data types, we write it **once** using template parameters.

The compiler automatically generates the required code.

Think of a template as:

```text
Blueprint

↓

Compiler

↓

Creates actual code
```

---

# Why were Templates Introduced?

Suppose we want to swap two integers.

```cpp
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
```

Later we need to swap two floats.

```cpp
void swap(float &a, float &b)
{
    float temp = a;
    a = b;
    b = temp;
}
```

Later

```cpp
double

char

string

Employee
```

We keep writing the same logic.

Problem

```text
Same Logic

↓

Repeated Code

↓

Hard to Maintain
```

Templates solve this problem.

---

# Real Life Analogy

Imagine a cookie cutter.

```text
One Cookie Mold

↓

Chocolate Cookie

Vanilla Cookie

Strawberry Cookie
```

The mold remains the same.

Only the ingredient changes.

Templates work exactly like this.

---

# Without Template

```cpp
int maximum(int a, int b)
{
    return a > b ? a : b;
}

float maximum(float a, float b)
{
    return a > b ? a : b;
}

double maximum(double a, double b)
{
    return a > b ? a : b;
}
```

Three identical functions.

---

# With Template

```cpp
template<typename T>
T maximum(T a, T b)
{
    return (a > b) ? a : b;
}
```

One function.

Works for every type.

---

# Template Syntax

```cpp
template<typename T>
```

or

```cpp
template<class T>
```

Both are identical.

```text
typename

==

class
```

There is **no difference** here.

---

# Meaning of T

```cpp
template<typename T>
```

`T` is simply a placeholder.

Later,

Compiler replaces it.

Example

```cpp
maximum<int>()
```

Compiler replaces

```text
T

↓

int
```

---

# First Template Program

```cpp
#include <iostream>
using namespace std;

template<typename T>
T add(T a, T b)
{
    return a + b;
}

int main()
{
    cout << add(10, 20) << endl;

    cout << add(3.5, 2.5) << endl;

    cout << add('A', 2) << endl;
}
```

Output

```text
30

6

67
```

---

# What Happens Internally?

When compiler sees

```cpp
add(10,20);
```

It generates

```cpp
int add(int a, int b)
{
    return a+b;
}
```

When compiler sees

```cpp
add(3.5,2.5);
```

It generates

```cpp
double add(double a,double b)
{
    return a+b;
}
```

Compiler generated both functions automatically.

Diagram

```text
Template

↓

Compiler

↓

add<int>()

↓

add<double>()

↓

add<char>()
```

---

# Function Template Example

```cpp
#include <iostream>
using namespace std;

template<typename T>
void print(T value)
{
    cout << value << endl;
}

int main()
{
    print(100);

    print(3.14);

    print("Hello");
}
```

Output

```text
100

3.14

Hello
```

Notice

Same function

Different types

---

# Template with Multiple Parameters

Example

```cpp
template<typename T1, typename T2>
void show(T1 a, T2 b)
{
    cout << a << " "
         << b << endl;
}

int main()
{
    show(10, "Alice");

    show(3.14, 'A');

    show("Age", 25);
}
```

Output

```text
10 Alice

3.14 A

Age 25
```

Compiler deduces

```text
T1 = int

T2 = string
```

and later

```text
T1 = double

T2 = char
```

---

# Explicit Template Arguments

Usually compiler deduces the type automatically.

```cpp
cout << add(10,20);
```

Equivalent to

```cpp
cout << add<int>(10,20);
```

You can also specify it manually.

```cpp
cout << add<double>(10,20);
```

Output

```text
30
```

Compiler converts integers to doubles.

---

# Template Argument Deduction

Compiler automatically finds the template type.

```cpp
template<typename T>
T square(T value)
{
    return value * value;
}

int main()
{
    cout << square(5);

    cout << square(2.5);
}
```

Compiler deduces

```text
square(5)

↓

T = int

-------------------

square(2.5)

↓

T = double
```

---

# When Deduction Fails

Example

```cpp
template<typename T>
T maximum(T a, T b)
{
    return (a>b)?a:b;
}

maximum(10,3.5);
```

Problem

```text
10

↓

int

3.5

↓

double
```

Compiler cannot decide

Should

```text
T = int ?

or

T = double ?
```

Compilation error.

Solution

```cpp
maximum<double>(10,3.5);
```

or

```cpp
maximum(10.0,3.5);
```

---

# Default Template Arguments

Just like function default arguments.

Example

```cpp
template<typename T = int>
class Number
{
public:

    T value;

    Number(T v)
    {
        value = v;
    }
};

int main()
{
    Number<> n1(100);

    Number<double> n2(5.5);
}
```

Compiler assumes

```text
Number<>

↓

Number<int>
```

---

# Benefits of Templates

- Code Reusability
- Less Duplicate Code
- Type Safety
- Easy Maintenance
- Generic Programming
- Used heavily in STL

---

# Where are Templates Used?

Templates are everywhere in C++.

Examples

```cpp
vector<int>

vector<string>

list<int>

map<int,string>

set<int>

queue<int>

stack<int>

pair<int,string>

tuple<int,double,string>

function<void()>

optional<int>

variant<int,string>
```

Almost every STL container uses templates.

---

# Interview Questions

## Q1. What is a Template?

A template is a blueprint used by the compiler to generate type-safe generic code.

---

## Q2. Why use Templates?

To avoid writing duplicate code for different data types.

---

## Q3. Difference between Macro and Template?

| Macro | Template |
|--------|----------|
| Text replacement | Compiler generated |
| No type checking | Type safe |
| Hard to debug | Easy to debug |
| Preprocessor | Compiler |

---

## Q4. Difference between `typename` and `class`?

For template parameters

```cpp
template<typename T>

template<class T>
```

Both mean exactly the same thing.

---

## Q5. Who creates the actual function?

The **compiler** generates the required function during template instantiation.

---

# Memory Trick

```text
Template

↓

Blueprint

↓

Compiler

↓

Generates

↓

int

double

char

string

Employee
```

---

# Summary

```text
Template

↓

Generic Code

↓

One Function

↓

Many Data Types

↓

Compiler Generates

↓

Type Safe

↓

Reusable
```

---

**Next Part (Part 2):**
- Class Templates
- Member Function Templates
- Non-Type Template Parameters
- Template Instantiation in Detail
- Template Compilation Process
- Code Bloat
- Best Practices
- Real-world Examples
--------------------------
# C++ Templates Complete Handbook

> **Part 2 - Class Templates, Non-Type Template Parameters & Template Instantiation**

---

# Table of Contents

1. Class Templates
2. Why Class Templates?
3. Class Template Example
4. Multiple Template Parameters
5. Member Functions
6. Template Instantiation
7. Non-Type Template Parameters
8. Default Template Arguments
9. Code Bloat
10. Best Practices
11. Interview Questions

---

# 1. Class Templates

## Why?

Just like functions, classes may also need to work with different data types.

Suppose we want a class to store one value.

Without templates

```cpp
class IntBox
{
    int value;

public:
    IntBox(int v) : value(v) {}
};
```

Later

```text
Need FloatBox

↓

Need DoubleBox

↓

Need StringBox
```

We keep writing the same class.

---

## Solution

Use a **Class Template**.

```cpp
template<typename T>
class Box
{
    T value;

public:

    Box(T v)
    {
        value = v;
    }

    void print()
    {
        cout << value << endl;
    }
};
```

---

# Using Class Template

```cpp
#include <iostream>
using namespace std;

template<typename T>
class Box
{
    T value;

public:

    Box(T v)
    {
        value = v;
    }

    void print()
    {
        cout << value << endl;
    }
};

int main()
{
    Box<int> b1(100);

    Box<double> b2(5.5);

    Box<string> b3("Hello");

    b1.print();

    b2.print();

    b3.print();
}
```

Output

```text
100

5.5

Hello
```

---

# What Happens Internally?

Compiler generates

```cpp
class Box_int
{
    int value;
};
```

and

```cpp
class Box_double
{
    double value;
};
```

and

```cpp
class Box_string
{
    string value;
};
```

Diagram

```text
Box<T>

↓

Compiler

↓

Box<int>

↓

Box<double>

↓

Box<string>
```

---

# Why Not Use void*?

Old C style

```cpp
void* data;
```

Problems

```text
No Type Safety

↓

Manual Casting

↓

Runtime Errors
```

Templates solve this problem.

---

# 2. Multiple Template Parameters

A class can have multiple template parameters.

```cpp
template<typename T1,
         typename T2>
class Pair
{
    T1 first;

    T2 second;

public:

    Pair(T1 a, T2 b)
    {
        first = a;
        second = b;
    }

    void display()
    {
        cout << first
             << " "
             << second << endl;
    }
};
```

Usage

```cpp
Pair<int,string> p1(10,"Alice");

Pair<double,char> p2(3.5,'A');

p1.display();

p2.display();
```

Output

```text
10 Alice

3.5 A
```

---

# Memory Representation

```text
Pair<int,string>

+----------------+
| int            |
| string         |
+----------------+

-----------------------

Pair<double,char>

+----------------+
| double         |
| char           |
+----------------+
```

Different template arguments create different classes.

---

# 3. Member Functions

Member functions are also generated for each type.

```cpp
template<typename T>
class Number
{
    T value;

public:

    Number(T v)
    {
        value = v;
    }

    T get()
    {
        return value;
    }
};
```

Usage

```cpp
Number<int> n(100);

cout << n.get();
```

Compiler creates

```cpp
int get()
{
    return value;
}
```

---

# 4. Class Template with Multiple Methods

```cpp
template<typename T>
class Calculator
{
public:

    T add(T a,T b)
    {
        return a+b;
    }

    T multiply(T a,T b)
    {
        return a*b;
    }
};
```

Usage

```cpp
Calculator<int> c;

cout << c.add(10,20);

cout << c.multiply(3,4);
```

Output

```text
30

12
```

---

# 5. Template Instantiation

Instantiation means

```text
Compiler creates

Actual Class

or

Actual Function
```

Example

```cpp
Box<int> b1;
```

Compiler creates

```cpp
class Box_int
{
};
```

Later

```cpp
Box<double> b2;
```

Compiler creates

```cpp
class Box_double
{
};
```

---

# Compiler Workflow

```text
Source Code

↓

Template Found

↓

No Object?

↓

No Code Generated

-------------------------

Object Used?

↓

Generate Class

↓

Compile

↓

Executable
```

Important

Templates generate code **only when used**.

---

# Example

```cpp
template<typename T>
class Test
{

};
```

Suppose

```cpp
int main()
{

}
```

Output

```text
No object

↓

Compiler

↓

Does NOT generate Test<int>
```

---

# 6. Non-Type Template Parameters

Template parameters need not always be data types.

They can also be constants.

Example

```cpp
template<int N>
class Array
{
    int arr[N];

public:

    void size()
    {
        cout << N << endl;
    }
};
```

Usage

```cpp
Array<5> a1;

Array<100> a2;

a1.size();

a2.size();
```

Output

```text
5

100
```

---

# Compiler Generates

```cpp
class Array5
{
    int arr[5];
};
```

and

```cpp
class Array100
{
    int arr[100];
};
```

---

# Real STL Example

```cpp
std::array<int,5>
```

Here

```text
int

↓

Type Parameter

------------------

5

↓

Non-Type Parameter
```

---

# Another Example

```cpp
template<char C>
class Printer
{
public:

    void print()
    {
        cout << C << endl;
    }
};

Printer<'A'> p;

p.print();
```

Output

```text
A
```

---

# 7. Default Template Arguments

Example

```cpp
template<typename T=int>
class Number
{
};
```

Usage

```cpp
Number<> n1;

Number<double> n2;
```

Equivalent

```text
Number<>

↓

Number<int>
```

---

# 8. Code Bloat

Templates generate separate code for each type.

Example

```cpp
maximum<int>()

maximum<double>()

maximum<char>()

maximum<float>()
```

Compiler generates four versions.

Diagram

```text
One Template

↓

Many Types

↓

Many Functions

↓

Larger Binary
```

This is called

```text
Code Bloat
```

---

# Advantages

- Generic Programming
- Compile-time Type Safety
- Easy Maintenance
- No Duplicate Code
- Faster than `void*`
- Strongly Typed

---

# Disadvantages

- Larger executable
- Longer compile time
- Complex compiler errors
- Can increase binary size

---

# Real STL Containers

Every STL container is a template.

```cpp
vector<int>

vector<string>

list<double>

deque<int>

stack<int>

queue<int>

set<int>

unordered_set<int>

map<int,string>

unordered_map<int,string>

pair<int,string>

tuple<int,double,string>

optional<int>

variant<int,string>
```

---

# Why STL Uses Templates

Suppose `vector` were only for integers.

We would need

```text
vectorInt

vectorFloat

vectorDouble

vectorString

vectorEmployee
```

Impossible to maintain.

Templates solve this by creating the required type automatically.

---

# Interview Questions

## Q1. What is a Class Template?

A class template is a blueprint that allows the compiler to generate classes for different data types.

---

## Q2. When is a template instantiated?

Only when it is used.

---

## Q3. What is a Non-Type Template Parameter?

A template parameter that represents a compile-time constant instead of a type.

Example

```cpp
template<int N>
```

---

## Q4. Why are templates faster than `void*`?

Because templates are type-safe and resolved at compile time, eliminating runtime casts.

---

## Q5. What is Code Bloat?

When the compiler generates multiple copies of template code for different types, increasing executable size.

---

# Memory Trick

```text
Function Template

↓

Creates Functions

---------------------

Class Template

↓

Creates Classes

---------------------

Type Parameter

↓

typename T

---------------------

Non-Type Parameter

↓

int N

char C

bool Flag
```

---

# Summary

```text
Class Template

↓

Blueprint

↓

Compiler Creates

↓

Actual Classes

↓

int

double

string

Employee

--------------------------

Non-Type Template

↓

Compile-Time Constant

↓

Array Size

Buffer Size

Character

Boolean

--------------------------

Instantiation

↓

Only When Used
```

---

## Next Part (Part 3)

- Function Template Overloading
- Template Specialization
- Full Specialization
- Partial Specialization
- Member Function Specialization
- Real-world Examples
- Interview Questions
-----------------------------
# C++ Templates Complete Handbook

> **Part 3 - Template Specialization & Function Template Overloading**

---

# Table of Contents

1. Why Template Specialization?
2. Function Template Overloading
3. Function Template Specialization
4. Full Specialization
5. Class Template Specialization
6. Partial Specialization
7. Member Function Specialization
8. Real-world Examples
9. Interview Questions

---

# 1. Why Template Specialization?

Normally, a template works for **all data types**.

Example

```cpp
template<typename T>
T maximum(T a, T b)
{
    return (a > b) ? a : b;
}
```

Works for

```text
int

double

float

char
```

But suppose we use

```cpp
string
```

Comparison using `>` may not be what we want.

Sometimes one data type requires **different logic**.

This is where **Template Specialization** is used.

---

# Real-Life Analogy

Suppose every employee gets a bonus.

```text
Employee

↓

10%
```

But

```text
Manager

↓

20%
```

Everyone follows the general rule except Managers.

This is specialization.

---

# 2. Function Template Overloading

Templates can also be overloaded.

Example

```cpp
#include <iostream>
using namespace std;

template<typename T>
void print(T value)
{
    cout << "One Value : "
         << value << endl;
}

template<typename T>
void print(T a, T b)
{
    cout << a
         << " "
         << b << endl;
}

int main()
{
    print(10);

    print(10,20);
}
```

Output

```text
One Value : 10

10 20
```

Compiler selects the correct overload.

---

# 3. Function Template Specialization

General template

```cpp
template<typename T>
void display(T value)
{
    cout << value << endl;
}
```

Suppose for `char*` we want

```text
String Received
```

instead of printing normally.

---

# Full Specialization

```cpp
template<>
void display<char*>(char* value)
{
    cout << "String : "
         << value << endl;
}
```

Usage

```cpp
display(10);

display(3.5);

char name[] = "Alice";

display(name);
```

Output

```text
10

3.5

String : Alice
```

---

# How Compiler Works

```text
display(10)

↓

General Template

---------------------

display(char*)

↓

Specialized Version
```

Compiler always prefers

```text
Specialization

↓

General Template
```

when an exact match exists.

---

# 4. Class Template Specialization

General Version

```cpp
template<typename T>
class Printer
{
public:

    void print()
    {
        cout << "General Version\n";
    }
};
```

Specialized Version

```cpp
template<>
class Printer<int>
{
public:

    void print()
    {
        cout << "Integer Version\n";
    }
};
```

Usage

```cpp
Printer<double> p1;

Printer<int> p2;

p1.print();

p2.print();
```

Output

```text
General Version

Integer Version
```

---

# Internal Working

Compiler sees

```cpp
Printer<int>
```

↓

Looks for

```cpp
Printer<int>
```

Specialization exists

↓

Uses it

Otherwise

↓

Uses

```cpp
Printer<T>
```

---

# 5. Full Specialization

A specialization where **all template parameters** are fixed.

Example

```cpp
template<typename T>
class Test
{

};
```

Full specialization

```cpp
template<>
class Test<int>
{

};
```

Meaning

```text
Only

int

gets a different implementation.
```

---

# Another Example

General

```cpp
template<typename T>
class Calculator
{
public:

    void show()
    {
        cout << "General\n";
    }
};
```

Specialization

```cpp
template<>
class Calculator<string>
{
public:

    void show()
    {
        cout << "String Calculator\n";
    }
};
```

Usage

```cpp
Calculator<int> c1;

Calculator<string> c2;

c1.show();

c2.show();
```

Output

```text
General

String Calculator
```

---

# 6. Partial Specialization

Only available for **class templates**.

Function templates **cannot** be partially specialized.

---

General template

```cpp
template<typename T1,
         typename T2>
class Data
{

};
```

Partial specialization

```cpp
template<typename T>
class Data<T,int>
{

};
```

Meaning

```text
First Type

↓

Anything

Second Type

↓

Must be int
```

---

# Example

```cpp
#include <iostream>
using namespace std;

template<typename T1,
         typename T2>
class Data
{
public:

    void show()
    {
        cout << "General\n";
    }
};

template<typename T>
class Data<T,int>
{
public:

    void show()
    {
        cout << "Second is int\n";
    }
};

int main()
{
    Data<double,double> d1;

    Data<double,int> d2;

    d1.show();

    d2.show();
}
```

Output

```text
General

Second is int
```

---

# Partial Specialization Diagram

```text
General

Data<T1,T2>

↓

Works for

Anything

-------------------------

Partial

Data<T,int>

↓

Second Must Be int
```

---

# Why Functions Cannot Be Partially Specialized?

Suppose

```cpp
template<typename T1,
         typename T2>
void show(T1,T2);
```

Partial specialization would make overload resolution ambiguous.

Instead,

C++ uses **function overloading**.

---

# 7. Member Function Specialization

Template class

```cpp
template<typename T>
class Printer
{
public:

    void show();
};
```

General implementation

```cpp
template<typename T>
void Printer<T>::show()
{
    cout << "General\n";
}
```

Specialized implementation

```cpp
template<>
void Printer<int>::show()
{
    cout << "Integer\n";
}
```

Usage

```cpp
Printer<double> p1;

Printer<int> p2;

p1.show();

p2.show();
```

Output

```text
General

Integer
```

---

# Real-World Example

Suppose we are writing a logger.

General version

```cpp
Logger<T>
```

works for every type.

But

```cpp
Logger<string>
```

needs

```text
Encryption

Formatting

Mask Password
```

Instead of changing the general logger,

we specialize only for

```cpp
string
```

---

# When Should You Specialize?

Use specialization when

- One type needs different logic.
- Performance optimization is required.
- General implementation is incorrect for one type.

---

# Template Specialization vs Overloading

| Overloading | Specialization |
|-------------|----------------|
| New function | Custom template implementation |
| Different parameters | Same parameters, specific type |
| Compiler chooses best overload | Compiler chooses specialized version |

---

# Compiler Preference

Suppose both exist

```cpp
General Template

↓

Specialized Template
```

Compiler always checks

```text
Specialized Version

↓

If Found

↓

Use It

Else

↓

General Version
```

---

# Advantages

- Reuse generic implementation
- Customize specific types
- Better performance
- Cleaner code
- Easier maintenance

---

# Disadvantages

- More complex
- Can confuse beginners
- Too many specializations reduce readability

---

# Interview Questions

## Q1. What is Template Specialization?

Providing a custom implementation of a template for a particular type.

---

## Q2. What is Full Specialization?

All template parameters are fixed.

Example

```cpp
Printer<int>
```

---

## Q3. What is Partial Specialization?

Only some template parameters are fixed.

Only **class templates** support partial specialization.

---

## Q4. Can Function Templates be Partially Specialized?

**No.**

Use function overloading instead.

---

## Q5. Which version does the compiler prefer?

```text
Specialized Version

↓

General Version
```

Compiler always selects the specialized template if it exactly matches.

---

# Memory Trick

```text
General Template

↓

Works for Everyone

------------------------

Specialization

↓

Special Rule

For One Type

------------------------

Full

↓

All Parameters Fixed

------------------------

Partial

↓

Some Parameters Fixed

(Class Templates Only)
```

---

# Summary

```text
Template

↓

General Solution

↓

Need Different Logic?

↓

Yes

↓

Specialization

↓

Full

or

Partial

↓

Compiler Chooses

Most Specific Match
```

---

## Next Part (Part 4)

- Variadic Templates
- Parameter Packs
- Fold Expressions (C++17)
- Perfect Forwarding
- Universal References
- `std::forward`
- Practical STL Examples
--------------------------------
# C++ Templates Complete Handbook

> **Part 4 - Variadic Templates, Parameter Packs & Fold Expressions (C++17)**

---

# Table of Contents

1. Why Variadic Templates?
2. Parameter Packs
3. Recursive Variadic Templates
4. sizeof...
5. Fold Expressions (C++17)
6. Left Fold
7. Right Fold
8. Unary & Binary Fold
9. Practical Examples
10. Interview Questions

---

# 1. Why Variadic Templates?

Before C++11, if we wanted a function to accept different numbers of arguments, we had to overload it.

Example

```cpp
int add(int a,int b)
{
    return a+b;
}

int add(int a,int b,int c)
{
    return a+b+c;
}

int add(int a,int b,int c,int d)
{
    return a+b+c+d;
}
```

Problem

```text
Need more parameters

↓

Need more overloads

↓

Duplicate code
```

---

## C++11 Solution

Variadic Templates.

A template can accept **any number of template arguments**.

Example

```cpp
template<typename... Args>
```

Notice

```text
...

↓

Means

Zero or More
```

---

# 2. Parameter Pack

```cpp
template<typename... Args>
```

`Args...` is called a **template parameter pack**.

It represents

```text
1 Type

or

2 Types

or

100 Types
```

Example

```cpp
template<typename... Args>
void show(Args... args)
{

}
```

---

# What Happens?

Suppose

```cpp
show(10);
```

Compiler sees

```text
Args

↓

int
```

---

Suppose

```cpp
show(10,3.5);
```

Compiler sees

```text
Args

↓

int

double
```

---

Suppose

```cpp
show(10,3.5,"ABC");
```

Compiler sees

```text
Args

↓

int

double

const char*
```

---

Diagram

```text
Args...

↓

Compiler Expands

↓

int

double

string

char

...
```

---

# 3. Recursive Variadic Template

Before C++17, we usually processed parameter packs recursively.

Example

```cpp
#include <iostream>
using namespace std;

// Base case
void print()
{
    cout << endl;
}

// Recursive case
template<typename T,
         typename... Args>
void print(T first, Args... rest)
{
    cout << first << " ";

    print(rest...);
}

int main()
{
    print(10,20,30,"Hello",5.5);
}
```

Output

```text
10 20 30 Hello 5.5
```

---

# How Does It Work?

Call

```cpp
print(10,20,30);
```

Step 1

```text
first = 10

rest = 20,30
```

↓

Calls

```cpp
print(20,30);
```

---

Step 2

```text
first = 20

rest = 30
```

↓

Calls

```cpp
print(30);
```

---

Step 3

```text
first = 30

rest = empty
```

↓

Calls

```cpp
print();
```

---

Base case

```cpp
void print()
{
}
```

Stops recursion.

---

Diagram

```text
print(10,20,30)

↓

10

↓

print(20,30)

↓

20

↓

print(30)

↓

30

↓

print()

↓

Stop
```

---

# Why Base Case?

Without it,

```cpp
print(rest...);
```

would keep calling forever.

Compiler needs one function to stop recursion.

---

# 4. sizeof...

Suppose we want to know

```text
How many arguments?

How many template types?
```

Use

```cpp
sizeof...
```

Example

```cpp
template<typename... Args>
void count(Args... args)
{
    cout << sizeof...(Args) << endl;

    cout << sizeof...(args) << endl;
}
```

Usage

```cpp
count(10,20,30);
```

Output

```text
3

3
```

---

Example

```cpp
count(1,2,3,4,5);
```

Output

```text
5

5
```

---

# 5. Fold Expressions (C++17)

One of the biggest improvements in C++17.

Before C++17

We used recursion.

```cpp
add(1,2,3,4)

↓

Recursive Calls
```

---

C++17

Compiler expands automatically.

Example

```cpp
template<typename... Args>
auto sum(Args... args)
{
    return (... + args);
}
```

Usage

```cpp
cout << sum(1,2,3,4,5);
```

Output

```text
15
```

---

# How Compiler Expands It

```cpp
(... + args)
```

becomes

```cpp
((((1+2)+3)+4)+5)
```

Diagram

```text
1

↓

+

↓

2

↓

+

↓

3

↓

+

↓

4

↓

+

↓

5
```

---

# Another Example

Multiplication

```cpp
template<typename... Args>
auto multiply(Args... args)
{
    return (... * args);
}
```

Usage

```cpp
multiply(2,3,4);
```

Compiler expands

```text
((2*3)*4)
```

Output

```text
24
```

---

# Logical AND

```cpp
template<typename... Args>
bool allTrue(Args... args)
{
    return (... && args);
}
```

Usage

```cpp
allTrue(true,true,true);
```

Output

```text
true
```

---

Example

```cpp
allTrue(true,false,true);
```

Output

```text
false
```

---

# Logical OR

```cpp
template<typename... Args>
bool anyTrue(Args... args)
{
    return (... || args);
}
```

---

# Left Fold

Syntax

```cpp
(... + args)
```

Expansion

```text
(((1+2)+3)+4)
```

Diagram

```text
Left

↓

(((A+B)+C)+D)
```

---

# Right Fold

Syntax

```cpp
(args + ...)
```

Expansion

```text
(1+(2+(3+4)))
```

Diagram

```text
Right

↓

(A+(B+(C+D)))
```

---

# Difference

Addition

```text
1+2+3+4
```

Both produce

```text
10
```

No difference.

---

Subtraction

Left Fold

```text
((10-2)-3)

↓

5
```

Right Fold

```text
10-(2-3)

↓

11
```

Different results.

---

# Unary Fold

One operator.

Example

```cpp
(... + args)
```

---

# Binary Fold

Has an initial value.

Example

```cpp
template<typename... Args>
auto sum(Args... args)
{
    return (100 + ... + args);
}
```

Usage

```cpp
sum(10,20);
```

Expansion

```text
100+10+20
```

Output

```text
130
```

---

# Practical Example

Print all arguments

```cpp
template<typename... Args>
void print(Args... args)
{
    ((cout << args << " "), ...);
}
```

Usage

```cpp
print(10,20,"ABC",5.5);
```

Output

```text
10 20 ABC 5.5
```

---

# Another Practical Example

Average

```cpp
template<typename... Args>
double average(Args... args)
{
    return (args + ...) / sizeof...(args);
}
```

Usage

```cpp
average(10,20,30);
```

Output

```text
20
```

---

# Advantages

- Less code
- No recursion
- Faster compilation
- Cleaner syntax
- Easier maintenance

---

# Interview Questions

## Q1. What is a Variadic Template?

A template that accepts any number of template arguments.

---

## Q2. What is a Parameter Pack?

A collection of template parameters.

Example

```cpp
Args...
```

---

## Q3. Why was Fold Expression introduced?

To eliminate recursive variadic template code and simplify parameter-pack processing.

---

## Q4. Difference between Left Fold and Right Fold?

Left Fold

```text
(((A+B)+C)+D)
```

Right Fold

```text
(A+(B+(C+D)))
```

They produce different results for non-associative operators like `-` and `/`.

---

## Q5. What does `sizeof...(Args)` return?

The number of template arguments in the parameter pack.

---

# Memory Trick

```text
Variadic Template

↓

Many Arguments

↓

Parameter Pack

↓

Args...

↓

Need Processing?

↓

Before C++17

↓

Recursion

↓

After C++17

↓

Fold Expression

↓

Cleaner

↓

Faster
```

---

# Summary

```text
Variadic Template

↓

Accept Any Number Of Arguments

↓

Parameter Pack

↓

Recursive Expansion

(C++11)

↓

Fold Expression

(C++17)

↓

Simple

↓

Efficient

↓

Modern C++
```

---

## Next Part (Part 5)

- Template Type Deduction
- `auto`
- `decltype`
- Trailing Return Types
- Perfect Forwarding
- Universal (Forwarding) References
- `std::forward`
- `std::move`
- Real-world Generic Programming Examples
--------------------------------
# C++ Templates Complete Handbook

> **Part 5 - Template Type Deduction, auto, decltype, Perfect Forwarding & std::forward**

---

# Table of Contents

1. Template Type Deduction
2. auto
3. decltype
4. Trailing Return Type
5. Universal (Forwarding) References
6. std::move
7. std::forward
8. Perfect Forwarding
9. Generic Factory Function
10. Interview Questions

---

# 1. Template Type Deduction

## What is Type Deduction?

Type deduction means the compiler automatically determines the template type.

Example

```cpp
template<typename T>
void show(T value)
{
    cout << value << endl;
}

int main()
{
    show(10);

    show(3.14);

    show("Hello");
}
```

Compiler deduces

```text
show(10)

↓

T = int

------------------

show(3.14)

↓

T = double

------------------

show("Hello")

↓

T = const char*
```

You don't have to write

```cpp
show<int>(10);
```

The compiler figures it out.

---

# How Compiler Works

```text
show(100)

↓

Argument

↓

int

↓

Compiler

↓

Creates

show<int>()
```

---

# Another Example

```cpp
template<typename T>
void print(T value)
{
    cout << typeid(T).name() << endl;
}

int main()
{
    print(100);

    print(2.5);

    print('A');
}
```

Compiler creates

```text
print<int>()

print<double>()

print<char>()
```

---

# 2. auto

## Why auto?

Before C++11

```cpp
vector<pair<int,string>>::iterator it;
```

Long and difficult.

C++11

```cpp
auto it = vec.begin();
```

Compiler determines the type.

---

## Example

```cpp
auto x = 10;

auto y = 3.5;

auto name = string("Alice");
```

Compiler deduces

```text
x

↓

int

-----------------

y

↓

double

-----------------

name

↓

string
```

---

# auto with STL

Before

```cpp
vector<int>::iterator it = v.begin();
```

After

```cpp
auto it = v.begin();
```

Much cleaner.

---

# auto with Range-based for

```cpp
vector<int> v = {10,20,30};

for(auto value : v)
{
    cout << value << endl;
}
```

Output

```text
10

20

30
```

---

# auto with Lambda

Without auto

```text
Very Long Type
```

With auto

```cpp
auto add =
[](int a,int b)
{
    return a+b;
};
```

---

# 3. decltype

## Why?

Suppose we want the compiler to tell us the type of an expression.

Use

```cpp
decltype
```

---

Example

```cpp
int x = 100;

decltype(x) y = 50;
```

Compiler deduces

```text
decltype(x)

↓

int
```

Equivalent

```cpp
int y = 50;
```

---

# Another Example

```cpp
double price = 99.5;

decltype(price) discount = 10.5;
```

Compiler creates

```cpp
double discount;
```

---

# decltype(Expression)

Example

```cpp
int a = 10;

int b = 20;

decltype(a+b) c = 100;
```

Expression

```text
a+b

↓

int

↓

c

↓

int
```

---

# auto vs decltype

```cpp
auto x = 10;
```

Compiler uses

```text
Initializer

↓

10

↓

int
```

---

```cpp
decltype(x)
```

Uses

```text
Declared Type

↓

int
```

---

Comparison

| auto | decltype |
|------|-----------|
| Deduces from value | Deduces from expression |
| Needs initializer | Uses existing type |
| Creates new variable | Gets type of expression |

---

# 4. Trailing Return Type

Sometimes return type depends on template parameters.

Instead of

```cpp
template<typename T1,
         typename T2>
???
add(T1 a,T2 b)
```

Use

```cpp
template<typename T1,
         typename T2>
auto add(T1 a,T2 b)
-> decltype(a+b)
{
    return a+b;
}
```

Usage

```cpp
cout << add(10,3.5);
```

Compiler

```text
a+b

↓

double

↓

Return Type

↓

double
```

---

# 5. Universal (Forwarding) Reference

One of the most important C++11 features.

Example

```cpp
template<typename T>
void func(T&& value)
{

}
```

Notice

```text
T&&

↓

Not Always

Rvalue Reference
```

It is called a **Forwarding Reference** (formerly "Universal Reference") when `T` is deduced.

---

# How Does It Work?

Call

```cpp
int x = 10;

func(x);
```

Compiler

```text
x

↓

Lvalue

↓

T = int&
```

---

Call

```cpp
func(100);
```

Compiler

```text
100

↓

Rvalue

↓

T = int
```

Same function accepts both.

---

# Why Needed?

Suppose we write

```cpp
void process(const string& s)
{
}

void process(string&& s)
{
}
```

Two overloads.

Perfect forwarding avoids writing multiple overloads.

---

# 6. std::move

Purpose

```text
Convert

Lvalue

↓

Rvalue
```

Example

```cpp
string name = "Alice";

string temp =
std::move(name);
```

Memory

Before

```text
name

↓

"Alice"
```

After move

```text
temp

↓

"Alice"

name

↓

Valid

But Unspecified State
```

`std::move` **does not move anything by itself**. It simply casts its argument to an rvalue, allowing move constructors or move assignment operators to be selected.

---

# 7. std::forward

Purpose

```text
Preserve

Original Value Category
```

Unlike

```cpp
std::move()
```

which always converts to rvalue,

```cpp
std::forward()
```

keeps

```text
Lvalue

↓

Lvalue

-------------------

Rvalue

↓

Rvalue
```

---

# Example

```cpp
template<typename T>
void wrapper(T&& value)
{
    process(
        std::forward<T>(value)
    );
}
```

If caller passes

```cpp
string s;

wrapper(s);
```

Compiler forwards

```text
Lvalue

↓

Lvalue
```

---

If caller passes

```cpp
wrapper(string("ABC"));
```

Compiler forwards

```text
Rvalue

↓

Rvalue
```

---

# std::move vs std::forward

| std::move | std::forward |
|------------|--------------|
| Always rvalue | Preserves original category |
| Forces move | Conditionally forwards |
| Used when object won't be reused | Used inside templates |

---

# 8. Perfect Forwarding

## Problem

Suppose

```cpp
void process(const string&)
{
    cout << "Copy\n";
}

void process(string&&)
{
    cout << "Move\n";
}
```

Wrapper

```cpp
template<typename T>
void wrapper(T&& value)
{
    process(value);
}
```

Problem

```text
value

↓

Named Variable

↓

Always Lvalue
```

Even if caller passed an rvalue.

---

# Solution

```cpp
template<typename T>
void wrapper(T&& value)
{
    process(
        std::forward<T>(value)
    );
}
```

Now

```text
Lvalue

↓

Copy Version

-------------------

Rvalue

↓

Move Version
```

Correct overload selected.

---

# Perfect Forwarding Flow

```text
Caller

↓

wrapper(T&&)

↓

std::forward<T>()

↓

Original Type Preserved

↓

Correct Function Called
```

---

# 9. Generic Factory Example

Without templates

```cpp
Employee* e =
new Employee();
```

Generic version

```cpp
template<typename T,
         typename... Args>
T* create(Args&&... args)
{
    return new T(
        std::forward<Args>(args)...
    );
}
```

Usage

```cpp
auto emp =
create<Employee>(
    101,
    "Alice"
);
```

Compiler forwards constructor arguments exactly as they were received.

---

# Real STL Usage

Functions such as

```cpp
std::make_unique()

std::make_shared()

std::emplace_back()

std::emplace()

std::thread()

std::async()
```

internally use

```text
Perfect Forwarding
```

to avoid unnecessary copies.

---

# Interview Questions

## Q1. What is Template Type Deduction?

The compiler automatically determines template parameter types from function arguments.

---

## Q2. Difference between auto and decltype?

`auto` deduces the type from an initializer.

`decltype` determines the type of an existing variable or expression.

---

## Q3. What is Perfect Forwarding?

Passing arguments while preserving whether they are lvalues or rvalues.

---

## Q4. Why use std::forward?

To preserve the original value category inside a forwarding-reference template.

---

## Q5. Difference between std::move and std::forward?

| std::move | std::forward |
|------------|--------------|
| Converts to rvalue | Preserves value category |
| Used when moving | Used for forwarding in templates |

---

# Memory Trick

```text
Template

↓

Compiler Deduces Type

↓

auto

↓

Variable Type

-----------------------

decltype

↓

Expression Type

-----------------------

T&&

↓

Forwarding Reference

-----------------------

std::move

↓

Force Move

-----------------------

std::forward

↓

Preserve Lvalue/Rvalue

-----------------------

Perfect Forwarding

↓

No Extra Copies
```

---

# Summary

```text
Type Deduction

↓

Compiler Finds Type

↓

auto

↓

Easy Variable Declaration

↓

decltype

↓

Find Expression Type

↓

Forwarding Reference

↓

std::forward()

↓

Perfect Forwarding

↓

Efficient Generic Code
```

---

## Next Part (Part 6)

- SFINAE
- `std::enable_if`
- Type Traits
- `constexpr` Templates
- Variable Templates
- Alias Templates
- Generic Programming
- Modern C++ Template Best Practices
---------------------------
# C++ Templates Complete Handbook

> **Part 6 - SFINAE, Type Traits, std::enable_if, Alias Templates & Variable Templates**

---

# Table of Contents

1. Why SFINAE?
2. Type Traits
3. std::enable_if
4. SFINAE
5. Alias Templates
6. Variable Templates
7. constexpr Templates
8. Generic Programming
9. Interview Questions

---

# 1. Why SFINAE?

Suppose we have

```cpp
template<typename T>
void print(T value)
{
    cout << value << endl;
}
```

Works for

```text
int

double

string
```

Now suppose we want this function to work **only for integers**.

How?

One way is

```cpp
if(...)
```

But

```text
Function Still Exists

↓

Compiler Checks Later
```

Instead,

we want the compiler to completely remove the function if the type is invalid.

This is where **SFINAE** comes in.

---

# What is SFINAE?

SFINAE stands for

```text
Substitution Failure

Is

Not

An

Error
```

Meaning

```text
Compiler Tries

↓

Replace Template Type

↓

Replacement Fails

↓

Ignore This Template

↓

Try Another One
```

Instead of producing a compilation error.

---

# Example

Suppose we have

```cpp
show(10);
```

Compiler checks

```text
show<int>()
```

Exists?

↓

Yes

↓

Use It
```

Now

```cpp
show("Hello");
```

Compiler checks

```text
show<const char*>()
```

If substitution fails,

Compiler simply ignores that overload.

---

# Real Life Analogy

Imagine applying for jobs.

```text
Company Needs

↓

10 Years Experience
```

You have

```text
3 Years
```

Company rejects only **your application**,

not the entire hiring process.

Compiler behaves similarly.

---

# 2. Type Traits

Type traits help the compiler answer questions about types.

Examples

```text
Is this an integer?

Is this a pointer?

Is this const?

Is this floating point?

Is this an array?
```

Header

```cpp
#include <type_traits>
```

---

# is_integral

```cpp
#include <iostream>
#include <type_traits>

using namespace std;

int main()
{
    cout << is_integral<int>::value << endl;

    cout << is_integral<double>::value << endl;
}
```

Output

```text
1

0
```

Meaning

```text
int

↓

Integral

----------------

double

↓

Not Integral
```

---

# is_floating_point

```cpp
cout << is_floating_point<float>::value;

cout << is_floating_point<int>::value;
```

Output

```text
1

0
```

---

# is_pointer

```cpp
cout << is_pointer<int*>::value;

cout << is_pointer<int>::value;
```

Output

```text
1

0
```

---

# More Useful Type Traits

| Trait | Meaning |
|--------|----------|
| is_integral | Integer? |
| is_floating_point | Float/Double? |
| is_pointer | Pointer? |
| is_reference | Reference? |
| is_const | Const? |
| is_same | Same type? |
| is_array | Array? |
| is_class | Class? |
| is_enum | Enum? |

---

# 3. std::enable_if

Suppose

```cpp
template<typename T>
void print(T value)
{

}
```

We want

```text
Only Integer Types
```

Solution

```cpp
#include <type_traits>

template<
typename T,
typename =
enable_if_t<
is_integral_v<T>
>>
void print(T value)
{
    cout << value << endl;
}
```

Usage

```cpp
print(100);
```

Works.

---

Now

```cpp
print(3.14);
```

Compiler

```text
is_integral<double>

↓

false

↓

Template Removed

↓

Compilation Error

(No Matching Function)
```

Notice

Compiler does **not** report an error inside the template.

The template simply disappears from overload resolution.

---

# Another Example

Floating Point Only

```cpp
template<
typename T,
typename =
enable_if_t<
is_floating_point_v<T>
>>
void square(T value)
{
    cout << value*value;
}
```

Works

```cpp
square(3.5);
```

Fails

```cpp
square(10);
```

---

# 4. SFINAE Example

Suppose

```cpp
template<typename T>
enable_if_t<
is_integral_v<T>
>
show(T value)
{
    cout << "Integer";
}
```

Second version

```cpp
template<typename T>
enable_if_t<
is_floating_point_v<T>
>
show(T value)
{
    cout << "Float";
}
```

Usage

```cpp
show(10);

show(3.5);
```

Output

```text
Integer

Float
```

Compiler removes the invalid overload automatically.

---

# Compiler Flow

```text
show(10)

↓

Template 1

↓

Valid

↓

Selected

---------------------

Template 2

↓

Invalid

↓

Ignored
```

---

# 5. Alias Templates

Suppose we repeatedly write

```cpp
std::vector<int>
```

Instead,

create an alias.

```cpp
template<typename T>
using Vec = vector<T>;
```

Usage

```cpp
Vec<int> numbers;

Vec<string> names;
```

Equivalent

```cpp
vector<int>

vector<string>
```

Cleaner.

---

# Another Example

```cpp
template<typename T>
using Ptr = T*;
```

Usage

```cpp
Ptr<int> p;
```

Compiler creates

```cpp
int*
```

---

# 6. Variable Templates (C++14)

Templates are not limited to

```text
Functions

Classes
```

Variables can also be templates.

Example

```cpp
template<typename T>
constexpr T PI =
3.1415926535;
```

Usage

```cpp
cout << PI<float>;

cout << PI<double>;
```

Compiler creates

```text
PI<float>

↓

float

----------------

PI<double>

↓

double
```

---

# Why Useful?

Instead of

```cpp
const double PI;
```

You can have

```text
PI<float>

PI<double>

PI<long double>
```

---

# 7. constexpr Templates

Templates can also be evaluated completely at compile time.

Example

```cpp
template<typename T>
constexpr T square(T x)
{
    return x*x;
}
```

Usage

```cpp
constexpr int x =
square(5);
```

Compiler calculates

```text
5*5

↓

25

↓

Before Program Starts
```

No runtime calculation.

---

# 8. Generic Programming

Templates are the foundation of

```text
Generic Programming
```

Meaning

```text
Write Once

↓

Work With

int

double

string

Employee

Your Own Classes
```

Example

```cpp
template<typename T>
void swapValues(T& a,T& b)
{
    T temp = a;

    a = b;

    b = temp;
}
```

Usage

```cpp
int x = 10;
int y = 20;

swapValues(x,y);

string a = "Hello";
string b = "World";

swapValues(a,b);
```

Same algorithm.

Different types.

---

# STL Uses Generic Programming

Almost every STL component uses templates.

Examples

```cpp
vector<T>

list<T>

deque<T>

queue<T>

stack<T>

map<K,V>

set<T>

pair<T1,T2>

tuple<...>

optional<T>

variant<...>
```

Templates make STL reusable.

---

# Best Practices

✅ Prefer templates over macros.

✅ Use type traits instead of manual type checks.

✅ Use `enable_if` (or in modern C++, Concepts) to restrict templates.

✅ Keep template implementations in header files.

✅ Don't over-specialize unless necessary.

---

# Interview Questions

## Q1. What is SFINAE?

Substitution Failure Is Not An Error.

If template substitution fails, the compiler silently removes that template from overload resolution.

---

## Q2. Why use std::enable_if?

To enable or disable a template based on compile-time conditions.

---

## Q3. What are Type Traits?

Compile-time utilities that provide information about types.

Example

```cpp
is_integral

is_pointer

is_same
```

---

## Q4. What is an Alias Template?

A template that creates a shorter name for another type.

Example

```cpp
template<typename T>
using Vec = vector<T>;
```

---

## Q5. What is a Variable Template?

A variable that depends on a template parameter.

Example

```cpp
template<typename T>
constexpr T PI = 3.14;
```

---

# Memory Trick

```text
Templates

↓

Need Restrictions?

↓

Type Traits

↓

enable_if

↓

SFINAE

↓

Compiler Removes Invalid Templates

------------------------

Need Short Name?

↓

Alias Template

------------------------

Need Generic Constant?

↓

Variable Template

------------------------

Compile-Time Calculation?

↓

constexpr Template
```

---

# Summary

```text
Type Traits

↓

Know About Types

↓

enable_if

↓

Restrict Templates

↓

SFINAE

↓

Ignore Invalid Templates

↓

Alias Templates

↓

Cleaner Code

↓

Variable Templates

↓

Generic Constants

↓

constexpr

↓

Compile-Time Evaluation
```

---

## Next Part (Part 7)

- Template Metaprogramming (TMP)
- Recursive Compile-Time Computation
- `std::integer_sequence`
- CRTP (Curiously Recurring Template Pattern)
- Policy-Based Design
- STL Internals
- Real Interview Questions
- Common Template Errors & Debugging