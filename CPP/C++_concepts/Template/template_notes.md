# C++ Templates Handbook Roadmap

> **Goal:** Learn C++ Templates by first understanding **what problem they solve**, then learning each template feature as a solution to the limitations of the previous approach.

---

# Why Templates?

Before learning the syntax, ask yourself:

> **Why were templates introduced?**

Without templates, we have to write the **same logic repeatedly** for different data types.

Example:

```cpp
int add(int a, int b)
{
    return a + b;
}

double add(double a, double b)
{
    return a + b;
}

float add(float a, float b)
{
    return a + b;
}
```

Problems

```text
Duplicate Code
      ↓
Hard to Maintain
      ↓
Need a New Function
for Every Data Type
```

Templates solve this problem by allowing us to write **generic code** that works for multiple data types.

---

# Learning Roadmap

Each chapter introduces a **new problem** and then explains how templates solve it.

---

# Chapter 1 - Function Templates

## Problem

Duplicate functions for every data type.

```cpp
int add(int, int);
double add(double, double);
float add(float, float);
```

## Solution

Function Templates

```cpp
template<typename T>
T add(T a, T b)
{
    return a + b;
}
```

## Learn

- What is `template`?
- What is `typename`?
- Why use `T`?
- Template syntax
- Compiler-generated functions (Template Instantiation)
- Type deduction

---

# Chapter 2 - Class Templates

## Problem

Duplicate classes.

```cpp
class IntStack
{
};

class FloatStack
{
};

class StringStack
{
};
```

## Problem

```text
Duplicate Classes
      ↓
Same Logic
Different Data Types
```

## Solution

```cpp
template<typename T>
class Stack
{
};
```

## Learn

- Class template syntax
- Creating objects
- Compiler-generated classes
- Different template instantiations

---

# Chapter 3 - Multiple Template Parameters

## Problem

Need multiple data types.

Example

```cpp
Pair<int, string>
```

## Solution

```cpp
template<typename T, typename U>
class Pair
{
};
```

## Learn

- Multiple template parameters
- Why more than one type?
- Real-world examples

---

# Chapter 4 - Non-Type Template Parameters

## Problem

Need compile-time constants.

Instead of

```cpp
int arr[10];
```

Need

```cpp
Array<int, 10>
```

## Solution

```cpp
template<typename T, int Size>
class Array
{
};
```

## Learn

- Compile-time constants
- Fixed-size arrays
- Matrix class
- Stack implementation

---

# Chapter 5 - Template Specialization

## Problem

Generic code doesn't work correctly for every type.

Example

```cpp
char*
```

may require different logic.

## Solution

```cpp
template<>
class MyClass<char*>
{
};
```

## Learn

- Full specialization
- Why specialization is needed
- Compiler selection

---

# Chapter 6 - Partial Specialization

## Problem

Need different implementation for some categories of types.

Examples

```cpp
vector<T>

vector<int>

vector<T*>
```

## Solution

Partial Specialization

## Learn

- Partial specialization
- Compiler matching rules
- Common STL examples

---

# Chapter 7 - Template Instantiation

## How Templates Work

```text
Source Code
      ↓
Compiler
      ↓
Template Instantiation
      ↓
Generate Real Functions / Classes
      ↓
Object File
```

Example

```cpp
add<int>()

add<double>()
```

## Learn

- Implicit instantiation
- Explicit instantiation
- When code is generated

---

# Chapter 8 - Template Type Deduction

## Problem

Compiler needs to determine template types automatically.

Example

```cpp
add(10, 20);
```

Compiler deduces

```text
T = int
```

## Learn

- Type deduction
- `const`
- References
- Pointers
- Arrays

---

# Chapter 9 - Variadic Templates

## Problem

Need functions with any number of arguments.

Without templates

```cpp
sum(1);

sum(1,2);

sum(1,2,3);

sum(1,2,3,4);
```

Need many overloads.

## Solution

```cpp
template<typename... Args>
```

## Learn

- Parameter packs
- Pack expansion
- Recursive templates
- Fold Expressions (C++17)

---

# Chapter 10 - Alias Templates

## Problem

Long template names reduce readability.

Instead of

```cpp
std::vector<int>
```

Create

```cpp
using IntVector = std::vector<int>;
```

## Learn

- Alias templates
- Simplifying complex template types

---

# Chapter 11 - Template Template Parameters

## Problem

Need algorithms that work with different container types.

Examples

```text
vector

list

deque
```

## Solution

```cpp
template<
    template<typename> class Container
>
```

## Learn

- Template template parameters
- Generic containers

---

# Chapter 12 - SFINAE

## Problem

Some template instantiations should be enabled only for valid types.

Need to

```text
Enable

or

Disable

Templates
```

## Learn

- SFINAE
- `std::enable_if`
- `std::type_traits`
- Compile-time constraints

---

# Chapter 13 - constexpr & if constexpr

## Problem

Need compile-time branching.

Instead of using template specialization.

Use

```cpp
if constexpr
```

## Learn

- Compile-time conditions
- Replacing many specializations
- Cleaner generic code

---

# Chapter 14 - Concepts (C++20)

## Problem

Templates often produce long and difficult compiler errors.

## Solution

```cpp
template<Integral T>
```

## Learn

- Concepts
- Constraints
- Better compiler diagnostics

---

# Chapter 15 - STL Templates

Understand how templates power the STL.

Examples

- `vector`
- `list`
- `deque`
- `map`
- `set`
- `queue`
- `stack`
- `priority_queue`
- `pair`
- `tuple`
- `optional`
- `variant`

---

# Chapter 16 - Interview Questions

Common interview topics

- Why templates?
- Why `typename`?
- `typename` vs `class`
- When is template code generated?
- Why are template definitions usually placed in header files?
- What is template bloat?
- Function template vs Class template
- Template specialization vs Function overloading
- SFINAE
- CTAD (Class Template Argument Deduction)
- Fold Expressions
- Perfect Forwarding

---

# Learning Flow

```text
Duplicate Functions
        ↓
Function Templates
        ↓
Duplicate Classes
        ↓
Class Templates
        ↓
Need Multiple Types
        ↓
Multiple Template Parameters
        ↓
Need Compile-time Values
        ↓
Non-Type Template Parameters
        ↓
Generic Code Doesn't Work
        ↓
Template Specialization
        ↓
Partial Specialization
        ↓
Need Flexible Arguments
        ↓
Variadic Templates
        ↓
Template Instantiation
        ↓
Type Deduction
        ↓
Need Compile-time Decisions
        ↓
SFINAE
        ↓
if constexpr
        ↓
Concepts (C++20)
        ↓
STL Templates
        ↓
Interview Questions
```

---

# Final Goal

After completing this roadmap, you should be able to:

- Write generic function templates
- Write generic class templates
- Understand compiler template instantiation
- Use multiple and non-type template parameters
- Implement template specialization
- Use variadic templates and fold expressions
- Understand SFINAE and `enable_if`
- Read and write STL template code confidently
- Answer common C++ template interview questions
- Understand modern template features introduced in C++17 and C++20