
#  C++ vs Python vs Go — Compilation Process & Memory Model

---

#  1. COMPILATION PROCESS

---

## 🟦 C++ Compilation Process (Fully Compiled Language)

C++ is a statically compiled language → converted directly into machine code.

###  Steps

Source Code (.cpp)  
↓  
Preprocessing  
↓  
Compilation  
↓  
Assembly  
↓  
Linking  
↓  
Executable (a.out / .exe)

### 🔹 Preprocessing
- Handles: #include, #define, macros
- Expands source code before compilation

### 🔹 Compilation
- Converts code → assembly
- Performs syntax + type checking

### 🔹 Assembly
- Converts assembly → object file (.o)

### 🔹 Linking
- Combines object files + libraries
- Produces final executable

###  Example
g++ main.cpp -o app

### Key Features
- Ahead-of-Time (AOT)
- Very fast
- Manual memory control

---

##  Python Compilation Process (Interpreted + Bytecode)

Python is interpreted but internally compiles to bytecode.

###  Steps

Source Code (.py)  
↓  
Bytecode Compilation  
↓  
Bytecode (.pyc)  
↓  
Python Virtual Machine (PVM)  
↓  
Execution  

### 🔹 Bytecode Compilation
- Converts .py → .pyc
- Stored in __pycache__

### 🔹 Python Virtual Machine
- Executes bytecode line-by-line

###  Example
python main.py

### Key Features
- Interpreted at runtime
- Slower than C++
- Highly portable

---

## Go Compilation Process (Fast Compiled Language)

Go is a compiled language optimized for speed.

###  Steps

Source Code (.go)  
↓  
Compilation  
↓  
Machine Code  
↓  
Executable  

###  Example
go build main.go

### Key Features
- Very fast compilation
- Static binaries
- Simple build system

---

#  Compilation Comparison

| Feature      | C++        | Python      | Go         |
|-------------|------------|-------------|------------|
| Type        | Compiled   | Interpreted | Compiled   |
| Output      | Binary     | Bytecode    | Binary     |
| Speed       | Fastest    | Slow        | Fast       |
| Portability | Medium     | High        | High       |

---

#  2. MEMORY MODEL

---

##  C++ Memory Model (Manual Control)

C++ provides full control over memory.

###  Memory Layout

Text Segment → Program code  
Data Segment → Global/static variables  
Heap → Dynamic memory  
Stack → Function calls, local variables  

### 🔹 Stack
- Stores function calls + local variables
- Fast but limited

### 🔹 Heap
- Dynamically allocated memory

Example:
int* p = new int(10);
delete p;

###  Features
- Manual memory management
- Risks: memory leaks, dangling pointers

---

##  Python Memory Model (Automatic + GC)

Python manages memory automatically.

###  Memory Structure
- Stack → function calls
- Heap → all objects

### 🔹 Memory Management
- Reference counting
- Garbage Collector (GC)

Example:
a = 10
b = a

- Reference count increases
- Freed when count = 0

### ⚡ Features
- No manual memory handling
- Safe but slower

---

##  Go Memory Model (Hybrid + GC)

Go uses a hybrid memory model.

###  Memory Structure
- Stack → small, fast allocations
- Heap → large/escaping variables

### 🔹 Escape Analysis
- Compiler decides stack vs heap

Example:
func test() *int {
    x := 10
    return &x
}

### 🔹 Garbage Collector
- Automatically frees memory
- Low-latency design

### Features
- Automatic memory management
- High performance + safety

---

#  Memory Comparison

| Feature            | C++        | Python     | Go         |
|-------------------|------------|------------|------------|
| Memory Control    | Manual     | Automatic  | Automatic  |
| Garbage Collection| No         | Yes        | Yes        |
| Stack Usage       | Heavy      | Limited    | Smart      |
| Heap Usage        | Manual     | All objects| Escape-based|
| Safety            | Low        | High       | High       |
| Performance       | Highest    | Lowest     | High       |

---

#  FINAL SUMMARY

##  C++
- Highest performance
- Full control
- Unsafe if misused

##  Python
- Easiest to use
- Fully automatic memory
- Slower execution

##  Go
- Balanced approach
- Fast + safe
- Modern system design

---
---

# 1. VARIABLES & DATA TYPES

## Concept

Store and manipulate data.

### C++

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    float b = 3.5;
    string name = "Ashu";

    cout << a << " " << b << " " << name;
}
```

### Python

```python
a = 10
b = 3.5
name = "Ashu"

print(a, b, name)
```

### Go

```go
package main
import "fmt"

func main() {
    var a int = 10
    b := 3.5
    name := "Ashu"

    fmt.Println(a, b, name)
}
```

---

# 2. CONTROL FLOW (if / else)

### C++

```cpp
int a = 10;

if (a > 5) {
    cout << "Greater";
} else {
    cout << "Smaller";
}
```

### Python

```python
a = 10

if a > 5:
    print("Greater")
elif a == 5:
    print("Equal")
else:
    print("Smaller")
```

### Go

```go
a := 10

if a > 5 {
    fmt.Println("Greater")
} else {
    fmt.Println("Smaller")
}
```

---

# 3. LOOPS (ALL TYPES)

---

## 🔹 C++ LOOPS

### for loop

```cpp
for(int i = 0; i < 5; i++) {
    cout << i << endl;
}
```

### while loop

```cpp
int i = 0;
while(i < 5) {
    cout << i;
    i++;
}
```

### do-while loop

```cpp
int i = 0;
do {
    cout << i;
    i++;
} while(i < 5);
```

---

## PYTHON LOOPS (FULL PRACTICAL COVERAGE)

### 1. for loop with range

```python
for i in range(5):
    print(i)
```

### 2. for loop with list

```python
nums = [10, 20, 30]
for n in nums:
    print(n)
```

### 3. while loop

```python
i = 0
while i < 5:
    print(i)
    i += 1
```

### 4. infinite loop

```python
while True:
    print("Running")
    break
```

### 5. nested loop

```python
for i in range(2):
    for j in range(2):
        print(i, j)
```

### 6. break

```python
for i in range(5):
    if i == 3:
        break
    print(i)
```

### 7. continue

```python
for i in range(5):
    if i == 2:
        continue
    print(i)
```

### 8. pass

```python
for i in range(3):
    pass
```

### 9. else with loop

```python
for i in range(3):
    print(i)
else:
    print("Loop completed")
```

### 10. enumerate

```python
names = ["a", "b"]
for index, value in enumerate(names):
    print(index, value)
```

### 11. zip

```python
a = [1,2]
b = [3,4]

for x, y in zip(a, b):
    print(x, y)
```

### 12. list comprehension

```python
squares = [x*x for x in range(5)]
print(squares)
```

---

## GO LOOPS

### basic for

```go
for i := 0; i < 5; i++ {
    fmt.Println(i)
}
```

### while-style

```go
i := 0
for i < 5 {
    fmt.Println(i)
    i++
}
```

### infinite

```go
for {
    break
}
```

### range loop

```nums := []int{10, 20, 30}
for index, value := range nums {
    fmt.Println(index, value)
}

// Only values
for _, value := range nums {
    fmt.Println(value)
}

// Map iteration
m := map[string]int{"a":1,"b":2}
for k, v := range m {
    fmt.Println(k, v)
}

// String iteration (runes)
s := "Go"
for i, ch := range s {
    fmt.Println(i, string(ch))
}
```

---

# 4. FUNCTIONS (FULL PYTHON COVERAGE)

---

## C++

```cpp
int add(int a, int b) {
    return a + b;
}
```

---

## PYTHON FUNCTIONS (ALL TYPES WITH REAL USE)

### 1. Basic

```python
def add(a, b):
    return a + b

print(add(2,3))
```

---

### 2. Default arguments

```python
def greet(name="Guest"):
    print("Hello", name)

greet()
greet("Ashu")
```

---

### 3. Keyword arguments

```python
def info(name, age):
    print(name, age)

info(age=20, name="Ashu")
```

---

### 4. *args (multiple inputs)

```python
def total(*nums):
    return sum(nums)

print(total(1,2,3,4))
```

---

### 5. **kwargs

```python
def show(**data):
    print(data)

show(name="Ashu", age=20)
```

---

### 6. Lambda

```python
square = lambda x: x*x
print(square(5))
```

---

### 7. Recursion

```python
def fact(n):
    if n == 1:
        return 1
    return n * fact(n-1)

print(fact(5))
```

---

### 8. Nested function

```python
def outer():
    def inner():
        print("Inner function")
    inner()

outer()
```

---

### 9. Higher-order function

```python
def apply(func, value):
    return func(value)

print(apply(lambda x: x*2, 5))
```

---

### 10. Decorator

```python
def decorator(func):
    def wrapper():
        print("Before")
        func()
        print("After")
    return wrapper

@decorator
def say():
    print("Hello")

say()
```

---

### 11. Generator

```python
def count():
    for i in range(3):
        yield i

for x in count():
    print(x)
```

---

# Go Functions

## Basic

### a) Basic function
```go
func add(a int, b int) int {
    return a + b
}
```

---

### b) Multiple return values
```go
func divide(a int, b int) (int, int) {
    return a / b, a % b
}

q, r := divide(10, 3)
fmt.Println(q, r) // 3 1
```

---

### c) Variadic functions (like Python *args)
```go
func sum(nums ...int) int {
    total := 0
    for _, n := range nums {
        total += n
    }
    return total
}

fmt.Println(sum(1, 2, 3, 4)) // 10
```

---

### d) Named return values
```go
func swap(a, b int) (x int, y int) {
    x = b
    y = a
    return
}
```

---

### e) Recursive function
```go
func factorial(n int) int {
    if n == 1 {
        return 1
    }
    return n * factorial(n-1)
}

fmt.Println(factorial(5)) // 120
```

---

### f) Anonymous functions and closures

#### Anonymous function
```go
adder := func(a, b int) int {
    return a + b
}

fmt.Println(adder(5, 3)) // 8
```

#### Closure example
```go
funcCounter := func() func() int {
    count := 0
    return func() int {
        count++
        return count
    }
}

counter := funcCounter()
fmt.Println(counter()) // 1
fmt.Println(counter()) // 2
```
```

---

# 5. DATA STRUCTURES

### C++

```cpp
vector<int> v = {1,2,3};
map<string, int> m;
```

### Python

```python
lst = [1,2,3]
d = {"a":1}
```

### Go

```go
nums := []int{1,2,3}
m := map[string]int{"a":1}
```

---

# Exception Handling — C++ vs Python vs Go

---

## 1. What is Exception Handling?

Exception handling is used to **handle runtime errors gracefully** without crashing the program.

### Common Goals

* Prevent crashes
* Handle unexpected situations
* Maintain program flow

---

## 2. C++ Exception Handling

### Syntax

```cpp
try {
    // code that may throw exception
} catch (exception_type e) {
    // handle exception
}
```

### Example

```cpp
#include <iostream>
using namespace std;

int main() {
    try {
        int a = 10, b = 0;

        if (b == 0)
            throw "Division by zero!";

        cout << a / b;
    } 
    catch (const char* msg) {
        cout << "Error: " << msg;
    }
}
```

### Multiple Catch

```cpp
try {
    throw 10;
} 
catch (int e) {
    cout << "Integer exception";
} 
catch (...) {
    cout << "Unknown exception";
}
```

### Standard Exceptions

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        throw runtime_error("Runtime error occurred");
    } 
    catch (exception &e) {
        cout << e.what();
    }
}
```

### Key Points

* Uses `try`, `catch`, `throw`
* Can catch multiple types
* `catch(...)` handles all exceptions
* Uses `<exception>` / `<stdexcept>`

---

## 3. Python Exception Handling

### Syntax

```python
try:
    # risky code
except ExceptionType:
    # handle error
```

### Example

```python
try:
    a = 10
    b = 0
    print(a / b)
except ZeroDivisionError:
    print("Cannot divide by zero")
```

### Multiple Exceptions

```python
try:
    x = int("abc")
except ValueError:
    print("Invalid conversion")
except Exception:
    print("Some error occurred")
```

### else & finally

```python
try:
    x = 10 / 2
except:
    print("Error")
else:
    print("Success:", x)
finally:
    print("Always runs")
```

### Raising Exception

```python
raise ValueError("Custom error")
```

### Key Points

* Uses `try`, `except`, `else`, `finally`
* No strict type declaration required
* Dynamic and flexible
* Rich built-in exceptions

---

## 4. Go Error Handling (No Exceptions )

Go does **NOT use exceptions** like C++/Python.
Instead, it uses **error values**.

### 🔹 Basic Pattern

```go
result, err := function()
if err != nil {
    // handle error
}
```

### 🔹 Example

```go
package main

import (
    "fmt"
    "errors"
)

func divide(a, b int) (int, error) {
    if b == 0 {
        return 0, errors.New("division by zero")
    }
    return a / b, nil
}

func main() {
    res, err := divide(10, 0)

    if err != nil {
        fmt.Println("Error:", err)
        return
    }

    fmt.Println("Result:", res)
}
```

### 🔹 Custom Error

```go
type MyError struct {
    msg string
}

func (e MyError) Error() string {
    return e.msg
}
```

### 🔹 Panic & Recover (Advanced)

```go
package main

import "fmt"

func main() {
    defer func() {
        if r := recover(); r != nil {
            fmt.Println("Recovered:", r)
        }
    }()

    panic("Something went wrong")
}
```

### 🔹 Key Points

* No `try-catch`
* Errors are explicit return values
* Encourages predictable flow
* `panic` = crash
* `recover` = handle panic

---

## 5. Side-by-Side Comparison

| Feature           | C++         | Python     | Go                  |
| ----------------- | ----------- | ---------- | ------------------- |
| Mechanism         | try-catch   | try-except | error return values |
| Throw Error       | throw       | raise      | return error        |
| Catch Error       | catch       | except     | if err != nil       |
| Multiple Handling | Yes         | Yes        | Manual              |
| Finally Block     | RAII        | Yes        | defer               |
| Crash Handling    | terminate() | Exception  | panic               |

---

## 6. Mental Model (Easy Way to Remember)

```
C++    → THROW → CATCH
Python → TRY → EXCEPT → FINALLY
Go     → RETURN error → CHECK manually
```

---

## 7. When to Use What?

* **C++** → System-level, performance-critical applications
* **Python** → Fast development, flexible handling
* **Go** → Clean, scalable backend systems

---


```

### Go

```go
if err != nil {
    fmt.Println(err)
}
```

---


```
# File Handling (C++, Python, Go)

This document shows basic file operations: **write, read, and append** in C++, Python, and Go.

---

## C++

```cpp
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    // Write to file
    ofstream outfile("example.txt");
    outfile << "Hello C++ File!\n";
    outfile.close();

    // Read from file
    ifstream infile("example.txt");
    string line;
    while (getline(infile, line)) {
        cout << line << endl;
    }
    infile.close();

    return 0;
}
```

---

## Python

```python
# Write to file
with open("example.txt", "w") as f:
    f.write("Hello Python File!\n")

# Read from file
with open("example.txt", "r") as f:
    for line in f:
        print(line.strip())
```

---

## Go

```go
package main

import (
    "fmt"
    "io/ioutil"
    "os"
)

func main() {
    // Write to file
    ioutil.WriteFile("example.txt", []byte("Hello Go File!\n"), 0644)

    // Read from file
    data, _ := ioutil.ReadFile("example.txt")
    fmt.Println(string(data))

    // Append to file
    f, _ := os.OpenFile("example.txt", os.O_APPEND|os.O_WRONLY, 0644)
    defer f.Close()
    f.WriteString("Appending new line\n")
}
```

---

## Summary

| Language | Write              | Read              | Append                   |
| -------- | ------------------ | ----------------- | ------------------------ |
| C++      | `ofstream`         | `ifstream`        | Requires manual handling |
| Python   | `open(..., "w")`   | `open(..., "r")`  | `open(..., "a")`         |
| Go       | `ioutil.WriteFile` | `ioutil.ReadFile` | `os.OpenFile`            |

---

## Notes

* Always close files after use.
* Prefer proper error handling in real applications.
* File paths can be relative or absolute.

---

# Object-Oriented Programming (OOP) – C++, Python, Go

This document covers **all major OOP concepts** across:

* C++
* Python
* Go (OOP-like features)

---

# 1. Class & Object

## C++

```cpp
class Car {
public:
    string brand;
    void show() { cout << brand; }
};

Car c;
c.brand = "BMW";
c.show();
```

## Python

```python
class Car:
    def __init__(self, brand):
        self.brand = brand

    def show(self):
        print(self.brand)

c = Car("BMW")
c.show()
```

## Go (Struct instead of class)

```go
type Car struct {
    brand string
}

func (c Car) show() {
    fmt.Println(c.brand)
}
```

---

# 2. Encapsulation (Data Hiding)

## C++

```cpp
class Person {
private:
    int age;
public:
    void setAge(int a){ age = a; }
    int getAge(){ return age; }
};
```

## Python

```python
class Person:
    def __init__(self):
        self.__age = 0   # private

    def set_age(self, a):
        self.__age = a

    def get_age(self):
        return self.__age
```

## Go

```go
type Person struct {
    age int   // lowercase = private
}
```

---

# 3. Abstraction

## C++

```cpp
class Shape {
public:
    virtual void draw() = 0; // pure virtual
};
```

## Python

```python
from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def draw(self):
        pass
```

## Go (Interface)

```go
type Shape interface {
    draw()
}
```

---

# 4. Inheritance

## C++

```cpp
class Animal {
public:
    void eat(){ cout<<"Eating"; }
};

class Dog : public Animal {};
```

## Python

```python
class Animal:
    def eat(self):
        print("Eating")

class Dog(Animal):
    pass
```

## Go

No inheritance
Uses composition instead

```go
type Animal struct{}

func (a Animal) eat() {
    fmt.Println("Eating")
}

type Dog struct {
    Animal
}
```

---

# 5. Polymorphism

## (a) Compile-time (Function Overloading)

### C++

```cpp
int add(int a, int b);
double add(double a, double b);
```

### Python

```python
def add(a, b, c=0):
    return a + b + c
```

### Go

Not supported directly

---

## (b) Runtime (Method Overriding)

### C++

```cpp
class Base {
public:
    virtual void show(){ cout<<"Base"; }
};

class Derived : public Base {
public:
    void show(){ cout<<"Derived"; }
};
```

### Python

```python
class Base:
    def show(self):
        print("Base")

class Derived(Base):
    def show(self):
        print("Derived")
```

### Go

```go
type Shape interface {
    area() float64
}
```

---

# 6. Constructor

## C++

```cpp
class A {
public:
    A(){ cout<<"Constructor"; }
};
```

## Python

```python
class A:
    def __init__(self):
        print("Constructor")
```

## Go

```go
func NewA() *A {
    return &A{}
}
```

---

# 7. Destructor

## C++

```cpp
~A(){ cout<<"Destructor"; }
```

## Python

```python
def __del__(self):
    print("Destructor")
```

## Go

No destructor (Garbage Collector handles memory)

---

# 8. Access Specifiers

| Concept   | C++       | Python  | Go             |
| --------- | --------- | ------- | -------------- |
| Public    | public    | default | Capital letter |
| Private   | private   | __var   | lowercase      |
| Protected | protected | _var    | not supported  |

---

# 9. Static Members

## C++

```cpp
class A {
public:
    static int count;
};
```

## Python

```python
class A:
    count = 0
```

## Go

```go
var count int
```

---

# 10. Interface / Abstract Class

## C++

```cpp
class A {
    virtual void show() = 0;
};
```

## Python

```python
from abc import ABC
```

## Go

```go
type A interface {
    show()
}
```

---

# 11. Operator Overloading

## C++

```cpp
class A {
public:
    A operator+(A obj) { }
};
```

## Python

```python
def __add__(self, other):
    return self.value + other.value
```

## Go

Not supported

---

# 12. Method Overloading

| Language | Support                |
| -------- | ---------------------- |
| C++      | Yes                    |
| Python   | No (default args used) |
| Go       | No                     |

---

# 13. Multiple Inheritance

| Language | Support              |
| -------- | -------------------- |
| C++      | Yes                  |
| Python   | Yes                  |
| Go       | No (uses interfaces) |

---

# 14. Composition

## C++

```cpp
class Engine {};
class Car {
    Engine e;
};
```

## Python

```python
class Engine: pass
class Car:
    def __init__(self):
        self.e = Engine()
```

## Go

```go
type Engine struct{}
type Car struct {
    Engine
}
```

---

# 15. Message Passing

* Objects communicate via method calls.

---

# 16. Dynamic Binding

* Method resolved at runtime (virtual functions / overriding)

---

# 17. Friend Function (C++ only)

```cpp
class A {
    friend void func(A obj);
};
```

---

# 18. Garbage Collection

| Language | GC       |
| -------- | -------- |
| C++      | Manual |
| Python   | Yes    |
| Go       | Yes    |

---

# Final Notes

* C++ → Fully OOP
* Python → Fully OOP + dynamic
* Go → Not pure OOP, uses composition & interfaces

---
# Accessing Private / Protected Members

### (C++ vs Python vs Go)

This document explains how **private/protected members** are accessed and whether a **`friend`-like mechanism** exists.

---

# 🔹 C++

## ✔ Supports `friend`

C++ allows controlled access to private/protected members using the `friend` keyword.

### Example

```cpp id="cppfriend1"
#include <iostream>
using namespace std;

class A {
private:
    int x;

public:
    A() { x = 10; }

    // Friend function declaration
    friend void show(A obj);
};

// Friend function
void show(A obj) {
    cout << obj.x << endl; // Allowed
}

int main() {
    A a;
    show(a);
}
```

### Key Points

* `friend` can access **private + protected**
* Can be:

  * Friend function
  * Friend class
* Breaks strict encapsulation (use carefully)

---

# Python

## No `friend` keyword

Python does **not enforce strict access control**.

### Example

```python id="pyfriend1"
class A:
    def __init__(self):
        self.__x = 10  # "private" (name mangling)

def show(obj):
    # Accessing mangled name
    print(obj._A__x)

a = A()
show(a)
```

### Key Points

* `__x` → name mangling (`_ClassName__x`)
* Still accessible (not truly private)
* Uses **convention, not restriction**

### Protected Convention

```python id="pyprotected1"
class A:
    def __init__(self):
        self._x = 10  # protected (by convention)
```

* `_x` → should not be accessed outside class/subclass (but still possible)

---

# 🔹 Go

## No `friend`, No `protected`

Go controls access using **package-level visibility**.

### Example

```go id="gofriend1"
package main

import "fmt"

type A struct {
    x int // private (unexported)
}

// Function in same package can access
func show(a A) {
    fmt.Println(a.x)
}

func main() {
    a := A{x: 10}
    show(a)
}
```

### Key Points

* `x` → private (lowercase)
* `X` → public (uppercase)
* No class-level access control
* Access allowed **within same package**

---

# Comparison Table

| Feature           | C++      | Python            | Go                       |
| ----------------- | -------- | ----------------- | ------------------------ |
| Private Members   | Strict | Weak            | Package-level          |
| Protected Members | Yes    | Convention      | No                     |
| Friend Support    | Yes    | No              | No                     |
| Access Mechanism  | Keywords | Naming convention | Capitalization + package |

---

# Summary

* **C++** → Strong encapsulation + `friend` for controlled access
* **Python** → Flexible, relies on developer discipline
* **Go** → Simple model using **packages instead of classes**

---
# Templates / Generics (C++ vs Python vs Go)

This document explains whether **templates** exist and how each language handles **generic programming**.

---

# 🔹 C++

## ✔ Yes — Templates Supported

C++ provides **templates** for generic programming.

### Example (Function Template)

```cpp id="cpptemp1"
#include <iostream>
using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(2, 3) << endl;        // int
    cout << add(2.5, 3.5) << endl;    // double
}
```

### Example (Class Template)

```cpp id="cpptemp2"
template <class T>
class Box {
public:
    T value;
};
```

### Key Points

* Compile-time polymorphism
* Type-safe
* Works for functions and classes

---

# 🔹 Python

##  No Templates (Dynamic Typing Instead)

Python does **not need templates** because it is dynamically typed.

### Example

```python id="pytemp1"
def add(a, b):
    return a + b

print(add(2, 3))        # int
print(add(2.5, 3.5))    # float
print(add("A", "B"))    # string
```

### Optional: Type Hints (Generic Style)

```python id="pytemp2"
from typing import TypeVar

T = TypeVar('T')

def add(a: T, b: T) -> T:
    return a + b
```

### Key Points

* No compile-time templates
* Uses **duck typing**
* Generics only for **type hints (optional)**

---

# 🔹 Go

## ✔ Yes — Generics (Since Go 1.18)

Go introduced **generics**, similar to templates but simpler.

### Example

```go id="gotemp1"
package main

import "fmt"

func add[T int | float64](a T, b T) T {
    return a + b
}

func main() {
    fmt.Println(add(2, 3))
    fmt.Println(add(2.5, 3.5))
}
```
# 🚀 Concurrency & Threads — C++ vs Python vs Go (Complete Notes)

---

## 1. What is Concurrency?

Concurrency is the ability of a program to **handle multiple tasks at the same time**.

> Not always parallel (true parallelism = multiple CPUs/cores)

---

## 2. Key Concepts

### 🔹 Process vs Thread

| Concept | Description                                    |
| ------- | ---------------------------------------------- |
| Process | Independent program with its own memory        |
| Thread  | Lightweight unit of execution inside a process |

---

### 🔹 Concurrency vs Parallelism

| Type        | Meaning                                    |
| ----------- | ------------------------------------------ |
| Concurrency | Multiple tasks managed at once             |
| Parallelism | Tasks executed simultaneously (multi-core) |

---

### 🔹 Common Problems

* Race Condition
* Deadlock
* Starvation
* Data inconsistency

---

### 🔹 Synchronization Tools

* Mutex (Lock)
* Semaphore
* Condition Variable
* Atomic Operations

---

##  3. C++ Concurrency (Threads)

### 🔹 Thread Creation

```cpp id="cpp1"
#include <iostream>
#include <thread>
using namespace std;

void task() {
    cout << "Thread running\n";
}

int main() {
    thread t(task);
    t.join(); // wait for thread
}
```

---

### 🔹 Passing Arguments

```cpp id="cpp2"
void print(int x) {
    cout << x;
}

thread t(print, 5);
t.join();
```

---

### 🔹 Mutex (Synchronization)

```cpp id="cpp3"
#include <mutex>

mutex m;

void safe_task() {
    m.lock();
    // critical section
    m.unlock();
}
```

---

### 🔹 Lock Guard (Better Way)

```cpp id="cpp4"
#include <mutex>

mutex m;

void safe_task() {
    lock_guard<mutex> lock(m);
    // auto unlock
}
```

---

### 🔹 Lambda Thread

```cpp id="cpp5"
thread t([]() {
    cout << "Lambda thread";
});
t.join();
```

---

### 🔹 Key Points

* Uses `<thread>` library
* Requires manual synchronization
* Powerful but complex
* Risk of race conditions

---

##  4. Python Concurrency

>  Python has **GIL (Global Interpreter Lock)**
> → Only one thread executes Python bytecode at a time

---

### 🔹 Threading

```python id="py1"
import threading

def task():
    print("Thread running")

t = threading.Thread(target=task)
t.start()
t.join()
```

---

### 🔹 Multiple Threads

```python id="py2"
for i in range(3):
    t = threading.Thread(target=task)
    t.start()
```

---

### 🔹 Lock

```python id="py3"
import threading

lock = threading.Lock()

def safe_task():
    with lock:
        # critical section
        pass
```

---

### 🔹 Multiprocessing (True Parallelism)

```python id="py4"
from multiprocessing import Process

def task():
    print("Process running")

p = Process(target=task)
p.start()
p.join()
```

---

### 🔹 Async (Modern Concurrency)

```python id="py5"
import asyncio

async def task():
    print("Hello")
    await asyncio.sleep(1)

asyncio.run(task())
```

---

### 🔹 Key Points

* Threading limited by GIL
* Use multiprocessing for CPU tasks
* Use asyncio for IO tasks
* Easy to use

---

##  5. Go Concurrency (Best )

> Go is built for concurrency

---

### 🔹 Goroutine

```go id="go1"
package main

import "fmt"

func task() {
    fmt.Println("Running")
}

func main() {
    go task()
}
```

---

### 🔹 WaitGroup (Wait for Threads)

```go id="go2"
package main

import (
    "fmt"
    "sync"
)

func task(wg *sync.WaitGroup) {
    defer wg.Done()
    fmt.Println("Done")
}

func main() {
    var wg sync.WaitGroup

    wg.Add(1)
    go task(&wg)

    wg.Wait()
}
```

---

### 🔹 Channel (Communication)

```go id="go3"
package main

import "fmt"

func main() {
    ch := make(chan int)

    go func() {
        ch <- 10
    }()

    val := <-ch
    fmt.Println(val)
}
```

---

### 🔹 Buffered Channel

```go id="go4"
ch := make(chan int, 2)
ch <- 1
ch <- 2
```

---

### 🔹 Select (Multiple Channels)

```go id="go5"
select {
case msg := <-ch1:
    fmt.Println(msg)
case msg := <-ch2:
    fmt.Println(msg)
}
```

---

### 🔹 Key Points

* Lightweight goroutines
* Channels instead of locks
* Built-in concurrency model
* Very efficient

---

## 6. Comparison Table

| Feature       | C++ Threads   | Python        | Go         |
| ------------- | ------------- | ------------- | ---------- |
| Thread Model  | OS Threads    | Threads + GIL | Goroutines |
| Parallelism   | Yes           | Limited (GIL) | Yes        |
| Ease of Use   | Medium/Hard   | Easy          | Very Easy  |
| Communication | Shared memory | Shared memory | Channels   |
| Performance   | High          | Medium        | Very High  |

---

## 7. Mental Model (Easy Trick)

```id="mental1"
C++    → Threads + Mutex (Manual control)
Python → Threads + GIL / Async / Multiprocessing
Go     → Goroutines + Channels (Built-in magic)
```

---

## 8. When to Use What?

* **C++** → High-performance systems, game engines
* **Python** → Scripts, IO-bound apps, data pipelines
* **Go** → Backend, microservices, scalable systems

---

## 9. Real-World Tips 

* Avoid shared state when possible
* Prefer message passing (Go style)
* Always use locks carefully
* Debugging concurrency is hard 
* Start simple → then optimize

---

## 10. Common Interview Questions

* What is race condition?
* What is deadlock?
* Difference between concurrency and parallelism?
* What is GIL in Python?
* Goroutines vs Threads?
* Mutex vs Channel?

---

##  Final Summary

* **C++** → Powerful but complex
* **Python** → Easy but limited (GIL)
* **Go** → Best for concurrency

---



### Key Points

* Introduced in Go 1.18
* Uses **type parameters**
* More restricted than C++ templates
* Safer and simpler

---

#  Comparison Table

| Feature       | C++          | Python    | Go               |
| ------------- | ------------ | --------- | ---------------- |
| Templates     | Yes        | No      | ✔ Yes (Generics) |
| Type Checking | Compile-time | Runtime   | Compile-time     |
| Flexibility   | Very high    | Very high | Moderate         |
| Complexity    | High         | Low       | Medium           |

---

# Summary

* **C++** → Powerful templates (full generic programming)
* **Python** → No templates (dynamic typing replaces need)
* **Go** → Supports generics (modern, simplified approach)

---


---

