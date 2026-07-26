# C++ Functors and Lambda Expressions

## Functors (Function Objects)

A **functor** (or **function object**) is an object of a class that behaves like a function by overloading the `operator()`.

### Why use Functors?

- Can be called like normal functions.
- Can store additional data (state).
- State is initialized through constructors.
- Each object maintains its own state, making it safer than using static variables.
- Frequently used with STL algorithms like `std::for_each`, `std::sort`, etc.

### Function Pointer vs Functor

| Function Pointer | Functor |
|------------------|----------|
| Points to a function | Object with overloaded `operator()` |
| Cannot store state | Can store member variables (state) |
| Less flexible | Highly customizable |
| No constructor | Constructor can initialize state |

---

## Example: Function Pointer vs Functor

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Normal function
void print(int val)
{
    cout << "Value: " << val << endl;
}

// Functor class
class PrintVal
{
    int val;    // Stores state

public:

    // Default constructor
    PrintVal() = default;

    // Constructor initializes state
    PrintVal(int value)
        : val(value)
    {
    }

    // Function call operator
    void operator()(int x)
    {
        if (x > val)
        {
            cout << x << " is greater than " << val << endl;
        }
    }
};

int main()
{
    vector<int> vec{10,20,30,40};

    // Function Pointer
    void (*func_ptr)(int) = &print;

    // STL calling function pointer
    for_each(vec.begin(), vec.end(), func_ptr);

    cout << endl;

    // STL calling normal function directly
    for_each(vec.begin(), vec.end(), print);

    cout << endl;

    // Functor storing state (10)
    PrintVal p(10);

    // STL calling functor
    for_each(vec.begin(), vec.end(), p);

    return 0;
}
```

### Output

```
Value: 10
Value: 20
Value: 30
Value: 40

Value: 10
Value: 20
Value: 30
Value: 40

20 is greater than 10
30 is greater than 10
40 is greater than 10
```

### Explanation

```cpp
class PrintVal
{
    int val;
```

- Stores a member variable.
- This is the **state** of the functor.

---

```cpp
PrintVal(int value)
    : val(value)
{
}
```

- Constructor initializes the state.

---

```cpp
void operator()(int x)
```

- Overloading `operator()` makes an object callable like a function.

```cpp
PrintVal p(10);

p(20);      // Actually calls p.operator()(20)
```

---

```cpp
for_each(vec.begin(), vec.end(), p);
```

Internally, STL performs something similar to:

```cpp
for(auto element : vec)
{
    p(element);
}
```

---

## Why not Function Pointer?

Function pointer

```cpp
void print(int x);
```

can receive only the parameter supplied by STL.

It **cannot** remember additional information like:

- threshold value
- counter
- running sum
- configuration

Functors solve this by storing member variables.

---

# Lambda Expressions

A **Lambda Expression** is an **anonymous functor**.

Instead of creating a class with `operator()`, the compiler creates it automatically.

## Syntax

```cpp
[capture](parameters)
mutable
exception
constexpr
-> return_type
{
    // body
}
```

If `mutable`, `constexpr`, or exception specifications are used, the parameter list `()` becomes mandatory.

---

# 1. Basic Lambda

```cpp
#include <iostream>

int main()
{
    auto greet = []()
    {
        std::cout << "Hello Lambda!\n";
    };

    greet();
}
```

### Explanation

- `[]` → nothing captured.
- `()` → no parameters.
- `greet` stores the lambda object.

Output

```
Hello Lambda!
```

---

# 2. Lambda with Parameters

```cpp
auto add = [](int a, int b)
{
    return a + b;
};

std::cout << add(3,4);
```

Output

```
7
```

---

# 3. Lambda with Explicit Return Type

```cpp
auto divide = [](double a, double b) -> double
{
    if(b==0)
        return 0;

    return a/b;
};
```

### Why use `-> double`?

Sometimes the compiler cannot deduce the return type.

---

# 4. Capture by Value `[=]`

```cpp
int x = 5;

auto print = [=]()
{
    std::cout << x;
};

print();
```

Output

```
5
```

### Explanation

The lambda stores a **copy** of every used local variable.

Changing the original variable later doesn't affect the copied value.

---

# 5. Capture by Reference `[&]`

```cpp
int x = 5;

auto modify = [&]()
{
    x = 10;
};

modify();

std::cout << x;
```

Output

```
10
```

### Explanation

The lambda uses the original variable, not a copy.

---

# 6. Mixed Capture

```cpp
int a = 1;
int b = 2;

auto lam = [a, &b]()
{
    std::cout << a << " " << b;
};
```

Meaning

- `a` copied
- `b` referenced

---

# 7. Mutable Lambda

Normally captured-by-value variables are read-only.

```cpp
int x = 10;

auto lam = [x]() mutable
{
    x++;
    std::cout << x;
};

lam();

std::cout << x;
```

Output

```
11
10
```

Explanation

The lambda modifies only its own copy.

---

# 8. Generic Lambda (C++14)

```cpp
auto add = [](auto a, auto b)
{
    return a+b;
};

std::cout << add(2,3);
std::cout << add(2.5,3.1);
```

The compiler generates different versions automatically.

---

# 9. Lambda in STL

```cpp
std::vector<int> v={1,2,3,4,5};

std::for_each(v.begin(),v.end(),
[](int n)
{
    std::cout<<n<<" ";
});
```

Output

```
1 2 3 4 5
```

---

# 10. Lambda as Function Pointer

```cpp
void callFunc(void (*func)())
{
    func();
}

int main()
{
    auto lam=[]()
    {
        std::cout<<"Called";
    };

    callFunc(lam);
}
```

Only lambdas **without captures** can convert to function pointers.

---

# 11. std::function

```cpp
#include <functional>

std::function<int(int,int)> func =
[](int a,int b)
{
    return a+b;
};

std::cout<<func(5,3);
```

Output

```
8
```

Useful when storing different callable objects using the same interface.

---

# 12. Capturing `this`

```cpp
class MyClass
{
    int value=10;

public:

    void show()
    {
        auto lambda=[this]()
        {
            std::cout<<value;
        };

        value=20;

        lambda();
    }
};
```

Output

```
20
```

The lambda accesses the original object through the `this` pointer.

---

# 13. Capturing `*this` (C++17)

```cpp
class MyClass
{
    int value=10;

public:

    void show()
    {
        auto lambda=[*this]()
        {
            std::cout<<value;
        };

        value=20;

        lambda();
    }
};
```

Output

```
10
```

`[*this]` creates a copy of the entire object.

---

# 14. Immediately Invoked Lambda (IIFE)

```cpp
int result =
[](int x,int y)
{
    return x+y;
}(5,3);
```

Output

```
8
```

Useful for one-time calculations.

---

# 15. Nested Lambda

```cpp
auto outer=[](int a)
{
    return [a](int b)
    {
        return a+b;
    };
};

auto inner=outer(10);

std::cout<<inner(5);
```

Output

```
15
```

The outer lambda returns another lambda.

---

# 16. Generic Lambda Example

```cpp
auto add=[](auto x,auto y)
{
    return x+y;
};

std::cout<<add(3,4)<<'\n';

std::cout<<add(2.5,1.5)<<'\n';

std::cout<<add(std::string("Hi "), "there");
```

Output

```
7
4
Hi there
```

---

# Functor vs Lambda

| Functor | Lambda |
|----------|---------|
| Requires a class | No class needed |
| Can store state | Can capture state |
| Good for reusable logic | Best for short operations |
| Verbose | Concise |
| Reusable in many places | Usually local and inline |

---

# When to Use Which?

### Use a Function Pointer

- Calling existing C-style APIs
- No extra state required

### Use a Functor

- Stateful algorithms
- Reusable objects
- Custom comparators
- Performance-critical code

### Use a Lambda

- Short callbacks
- STL algorithms
- Inline operations
- Event handlers
- Local helper functions

---

# Key Points

- A **functor** is a class with `operator()`.
- Lambdas are compiler-generated functors.
- Function pointers cannot store state.
- Functors and lambdas can store state.
- `[]` defines the capture list.
- `[=]` captures by value.
- `[&]` captures by reference.
- `[this]` captures the current object by reference.
- `[*this]` captures a copy of the current object.
- Generic lambdas (`auto` parameters) were introduced in C++14.
- Lambdas without captures can convert to function pointers.
- `std::function` can store functions, functors, and lambdas using a common interface.
