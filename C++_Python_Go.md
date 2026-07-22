---------------------------,-

```
Better: Group by Concept
Basics
CVIC  LEFT FD

Compilation
Variables
Input
Control Flow

Loops
Exceptions
Functions
Type casting

Files
Dynamic memory allocation

---------------

OOP Fundamentals
C E A  I P

Class & Object
Encapsulation
Abstraction
Inheritance
Polymorphism

-----------------

Object Lifecycle
C D

Constructor
Destructor

------------------
Advanced OOP
A S A O F C
Access Specifier
Static Member
Abstract Class
Operator Overloading
Function Overloading
Composition

--------------------
Generic & Parallel Programming
T C

Templates
Concurrency

This grouping is often easier to remember than a single 22-item mnemonic:

Basics → OOP → Lifecycle → Advanced OOP → Generic/Parallel

or

CVCLFEF → CEAIP → CD → ASAOFC → TC
```
--------------------------------

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
```
## Go Compilation Process (Fast Compiled Language)

###  Steps

.go file
↓
go build
↓
Compiler (frontend + backend)
↓
Machine Code
↓
Linker (adds runtime, dependencies)
↓
Standalone Executable
```
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
#include <iostream> //includes the standard input/output library
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
package main //package main tells the Go compiler: This package should be built as an executable program.
import "fmt" //Import standard I/O

func main() {
    var a int = 10
    b := 3.5
    name := "Ashu"

    fmt.Println(a, b, name)
}

Difference Between
var a int = 10
b := 3.5
🔹 1. var a int = 10
✅ Explicit Declaration
You declare type manually

Syntax:
var <name> <type> = <value>
Behavior
a is explicitly int

Compiler does not need to infer type

Use When:
You want clarity

You want a specific type (even if value could imply another)

🔹 2. b := 3.5
✅ Short Variable Declaration
Type is automatically inferred

Syntax:

<name> := <value>
Behavior
b becomes float64 (default for decimal numbers)

Type decided by compiler

Key Differences
Feature	var a int = 10	b := 3.5
Type declaration	Explicit	Inferred
Syntax	Verbose	Short
Usage scope	Anywhere	Only inside functions
Flexibility	High control	Quick & convenient
Important Rule (Very Important)
:= can only be used inside functions

package main
var x := 10 // ERROR
Correct:
var x = 10

🧠 Mental Model
var → "I decide the type"
:=  → "Compiler decides the type"
🚀 Interview Insight
Go prefers:

:= → for most local variables

var → for:
global variables
explicit typing
zero values

```

# 2. User Input Methods in C++, Python, and Go

---
# User Input Comparison: C++ vs Python vs Go

---

# 1. Single Integer Input

| C++ | Python | Go |
|------|---------|-----|
| ```cpp int x; cin >> x; ``` | ```python x = int(input()) ``` | ```go var x int; fmt.Scan(&x) ``` |

Input:

```text
10
```

---

# 2. Single Float Input

| C++ | Python | Go |
|------|---------|-----|
| ```cpp double x; cin >> x; ``` | ```python x = float(input()) ``` | ```go var x float64; fmt.Scan(&x) ``` |

Input:

```text
10.5
```

---

# 3. Single Word String

| C++ | Python | Go |
|------|---------|-----|
| ```cpp string s; cin >> s; ``` | ```python s = input() ``` | ```go var s string; fmt.Scan(&s) ``` |

Input:

```text
John
```

---

# 4. Character Input

| C++ | Python | Go |
|------|---------|-----|
| ```cpp char ch; cin >> ch; ``` | ```python ch = input()[0] ``` | ```go ch, _ := reader.ReadByte() ``` |

Input:

```text
A
```

---

# 5. Multiple Inputs in One Line

Input:

```text
10 20
```

| C++ | Python | Go |
|------|---------|-----|
| ```cpp int a,b; cin >> a >> b; ``` | ```python a,b = map(int,input().split()) ``` | ```go var a,b int; fmt.Scan(&a,&b) ``` |

---

# 6. Array/List Input

Input:

```text
1 2 3 4 5
```

| C++ | Python | Go |
|------|---------|-----|
| ```cpp vector<int> arr(5); for(int &x:arr) cin>>x; ``` | ```python arr=list(map(int,input().split())) ``` | ```go nums:=strings.Fields(line) ``` |

---

# 7. Entire Line Input

Input:

```text
Hello World
```

| C++ | Python | Go |
|------|---------|-----|
| ```cpp getline(cin,line); ``` | ```python line=input() ``` | ```go line,_:=reader.ReadString('\n') ``` |

---

# 8. Multiple Lines Input

Input:

```text
Hello
World
```

| C++ | Python | Go |
|------|---------|-----|
| ```cpp getline(cin,l1); getline(cin,l2); ``` | ```python l1=input(); l2=input() ``` | ```go scanner.Scan(); l1:=scanner.Text() ``` |

---

# 9. Read Until EOF

Useful for competitive programming.

## C++

```cpp
int x;

while(cin >> x)
{
    cout << x << endl;
}
```

## Python

```python
import sys

for line in sys.stdin:
    print(line)
```

## Go

```go
scanner := bufio.NewScanner(os.Stdin)

for scanner.Scan()
{
    fmt.Println(scanner.Text())
}
```

---

# 10. File Input

## C++

```cpp
ifstream file("data.txt");

int x;
file >> x;
```

## Python

```python
with open("data.txt") as f:
    data = f.read()
```

## Go

```go
file, _ := os.Open("data.txt")
```

---

# 11. Read File Line by Line

## C++

```cpp
string line;

while(getline(file,line))
{
    cout << line << endl;
}
```

## Python

```python
with open("data.txt") as f:
    for line in f:
        print(line)
```

## Go

```go
scanner := bufio.NewScanner(file)

for scanner.Scan()
{
    fmt.Println(scanner.Text())
}
```

---

# 12. Command-Line Arguments

Run:

```bash
app hello
```

## C++

```cpp
int main(int argc, char* argv[])
{
    cout << argv[1];
}
```

## Python

```python
import sys

print(sys.argv[1])
```

## Go

```go
fmt.Println(os.Args[1])
```

---

# 13. Fast Input

## C++

```cpp
ios::sync_with_stdio(false);
cin.tie(nullptr);
```

## Python

```python
import sys

line = sys.stdin.readline()
```

## Go

```go
reader := bufio.NewReader(os.Stdin)
```

---

# Summary

| Purpose | C++ | Python | Go |
|----------|----------|----------|----------|
| Integer | `cin` | `input()` + `int()` | `fmt.Scan()` |
| Float | `cin` | `input()` + `float()` | `fmt.Scan()` |
| String Word | `cin` | `input()` | `fmt.Scan()` |
| Character | `cin` | `input()[0]` | `ReadByte()` |
| Full Line | `getline()` | `input()` | `ReadString()` |
| Multiple Values | `cin >> a >> b` | `split()` | `fmt.Scan()` |
| Array/List | loop + `cin` | `map()` | `Fields()` |
| File Input | `ifstream` | `open()` | `os.Open()` |
| EOF Input | `while(cin>>x)` | `sys.stdin` | `Scanner()` |
| Command-Line Args | `argv` | `sys.argv` | `os.Args` |
| Fast Input | `cin.tie(nullptr)` | `readline()` | `bufio.Reader` |

---

# Rule of Thumb

## C++

```cpp
cin >> value;        // formatted input
getline(cin, line);  // full line
```

## Python

```python
input()                    # line
int(input())               # integer
input().split()            # multiple values
```

## Go

```go
fmt.Scan()                 // formatted input
bufio.Reader               // line input
bufio.Scanner              // multiple lines
```

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
# Python For Loops — Complete Notes

---

## 1. Iterating Over a List

```python
fruits = ["apple", "banana", "cherry"]

for fruit in fruits:
    print(fruit)
```

**Output:**
```
apple
banana
cherry
```

---

## 2. Iterating Over a String

```python
word = "Python"

for letter in word:
    print(letter)
```

**Output:**
```
P
y
t
h
o
n
```

---

## 3. Using `range()`

The `range()` function generates a sequence of numbers.

### 🔹 Example 1

```python
for i in range(5):
    print(i)
```

**Output:**
```
0
1
2
3
4
```

### 🔹 Example 2 (Start and End)

```python
for i in range(1, 6):
    print(i)
```

**Output:**
```
1
2
3
4
5
```

### 🔹 Example 3 (With Step)

```python
for i in range(0, 10, 2):
    print(i)
```

**Output:**
```
0
2
4
6
8
```

---

## 4. Iterating Over a Dictionary

```python
person = {"name": "Alice", "age": 25, "city": "New York"}

for key, value in person.items():
    print(f"{key}: {value}")
```

**Output:**
```
name: Alice
age: 25
city: New York
```

---

## 5. Nested For Loops

```python
for i in range(3):
    for j in range(2):
        print(f"i={i}, j={j}")
```

**Output:**
```
i=0, j=0
i=0, j=1
i=1, j=0
i=1, j=1
i=2, j=0
i=2, j=1
```

---

## 6. `break` and `continue`

### 🔹 break (Exit loop completely)

```python
for i in range(5):
    if i == 3:
        break
    print(i)
```

**Output:**
```
0
1
2
```

### 🔹 continue (Skip current iteration)

```python
for i in range(5):
    if i == 3:
        continue
    print(i)
```

**Output:**
```
0
1
2
4
```

---

## 7. `else` with For Loop

The `else` block executes only if the loop completes normally (no `break`).

```python
for i in range(5):
    print(i)
else:
    print("Loop finished without a break.")
```

**Output:**
```
0
1
2
3
4
Loop finished without a break.
```

---

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

```
nums := []int{10, 20, 30}
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

### 5. **kwargs(keyword arguments)

```python
def show(**data):
    print(data)
    print(data.get("name")
    print(data.get("age")

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
def divide(a, b):
    if b == 0:
        raise ValueError("Division by zero is not allowed")
    return a / b

result = divide(10, 0)
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
    
    while (true) {
        getline(cin, line);

        if (line == "exit")
            break;

        outfile << line << '\n';
    }

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

# Dynamic memory allocation:
# Dynamic Memory Allocation in C++, Python, and Go

## What is Dynamic Memory Allocation?

Dynamic memory allocation means memory is allocated at **runtime** instead of compile time.

Advantages:

- Size can be determined during execution.
- Memory can outlive the current scope.
- Useful for large data structures.
- Supports dynamic containers such as lists, vectors, maps, etc.

---

# C++

## Stack Allocation

```cpp
int x = 10;
```

Memory is allocated automatically on the stack.

Destroyed automatically when scope ends.

---

## Heap Allocation Using new

```cpp
int* ptr = new int(10);

std::cout << *ptr << std::endl;

delete ptr;
```

Output:

```text
10
```

Memory Layout:

```text
Stack                 Heap
-----                 ----
ptr  ------------->   10
```

---

## Dynamic Array

```cpp
int n = 5;

int* arr = new int[n];

for(int i = 0; i < n; i++)
{
    arr[i] = i + 1;
}

delete[] arr;
```

---

## Modern C++ (Recommended)

### unique_ptr

```cpp
#include <memory>

auto ptr = std::make_unique<int>(10);

std::cout << *ptr;
```

No manual delete required.

---

### shared_ptr

```cpp
#include <memory>

auto ptr = std::make_shared<int>(100);

std::cout << *ptr;
```

Reference-counted ownership.

---

## When Memory Is Released?

```cpp
int* ptr = new int(10);

delete ptr;
```

Programmer is responsible.

Failure to delete causes:

```text
Memory Leak
```

---

# Python

## Everything is Dynamically Allocated

```python
x = 10
```

Python creates an integer object and stores a reference.

Memory Layout:

```text
x ------> Integer Object(10)
```

---

## List Allocation

```python
arr = [1, 2, 3, 4, 5]
```

List object is allocated dynamically.

---

## Dictionary Allocation

```python
data = {
    "name": "John",
    "age": 25
}
```

Dictionary is allocated dynamically.

---

## Object Allocation

```python
class Employee:
    def __init__(self, name):
        self.name = name

emp = Employee("John")
```

Memory is allocated automatically.

---

## Explicit Allocation Example

```python
arr = [0] * 1000000
```

Creates a dynamically allocated list containing one million elements.

---

## Memory Release

Python uses:

```text
Reference Counting
+
Garbage Collection (GC)
```

Example:

```python
arr = [1, 2, 3]

del arr
```

Memory becomes eligible for cleanup.

Programmer usually does not free memory manually.

---

# Go

## Dynamic Allocation Using new

```go
package main

import "fmt"

func main() {
    ptr := new(int)

    *ptr = 10

    fmt.Println(*ptr)
}
```

Output:

```text
10
```

Memory Layout:

```text
ptr -----> 10
```

---

## Struct Allocation

```go
type Employee struct {
    Name string
}

func main() {
    emp := new(Employee)

    emp.Name = "John"
}
```

Allocated dynamically.

---

## Using Address Operator

```go
x := 10

ptr := &x

fmt.Println(*ptr)
```

Output:

```text
10
```

---

## Slice Allocation

```go
nums := make([]int, 5)
```

Creates:

```text
Length = 5
Capacity = 5
```

Dynamic memory allocated internally.

---

## Map Allocation

```go
data := make(map[string]int)

data["age"] = 25
```

Maps must usually be initialized using `make()`.

---

## Channel Allocation

```go
ch := make(chan int)
```

Channels are dynamically allocated.

---

## Memory Release

Go uses:

```text
Garbage Collection (GC)
```

Example:

```go
func create() {
    arr := make([]int, 1000000)
}
```

After function returns:

```text
No references remain
↓
Garbage Collector frees memory
```

---

# Comparison

| Feature | C++ | Python | Go |
|----------|----------|----------|----------|
| Dynamic Allocation Keyword | new | Automatic | new / make |
| Manual Free Required | Yes | No | No |
| Garbage Collection | No | Yes | Yes |
| Smart Pointers | Yes | No | No |
| Dynamic Arrays | new[] / vector | list | slice |
| Dynamic Maps | unordered_map | dict | map |
| Memory Leak Possible | Yes | Rare | Rare |

---

# Interview Question

## Why is C++ Faster?

Because:

```text
C++
    Manual Memory Management

Python
    Object Creation
    Reference Counting
    Garbage Collection

Go
    Garbage Collection
```

Less runtime overhead generally means higher performance.

---

# Rule of Thumb

## C++

```text
Use:
vector
string
unique_ptr
shared_ptr

Avoid raw new/delete unless necessary.
```

## Python

```text
Memory management is automatic.

Focus on:
list
dict
set
tuple
```

## Go

```text
Use:
slice
map
channel

Use new() rarely.
Use make() for slices, maps, and channels.
```

# Type casting

C-style casts:

```cpp
(Type)value
```

Example:

```cpp
double x = 10.5;

int y = (int)x;
```

Modern C++ prefers explicit cast operators because they are safer and make intent clear.

---

# 1. static_cast

Used for:

- Numeric conversions
- Related pointer conversions
- Upcasting
- Explicit conversions

Example: Numeric Conversion

```cpp
double x = 10.5;

int y = static_cast<int>(x);
```

Output:

```text
10
```

Example: Upcasting

```cpp
class Base {};
class Derived : public Base {};

Derived d;

Base* ptr = static_cast<Base*>(&d);
```

---

# 2. dynamic_cast

# dynamic_cast

## What is dynamic_cast?

`dynamic_cast` is a C++ cast operator used for

- Safe upcasting
- Runtime type checking
- Polymorphic classes

Unlike `static_cast`, `dynamic_cast` checks **at runtime** whether the cast is valid.

---

# Why do we need dynamic_cast?

Consider the inheritance hierarchy:

```
        Base
          ▲
          │
      Derived
```

Suppose we have

```cpp
Base* ptr = new Derived();
```

Memory

```
ptr
 │
 ▼
+--------------------+
| Base Part          |
|--------------------|
| Derived Part       |
+--------------------+
```

Although the pointer type is `Base*`, the actual object is a `Derived`.

Sometimes we want to access members of `Derived`.

Example

```cpp
ptr->show();
```

❌ Compilation Error

Because `Base` has no member named `show()`.

We first need to convert

```
Base*

↓

Derived*
```

This is called **Downcasting**.

---

# Upcasting vs Downcasting

## Upcasting (Always Safe)

```
Derived*

↓

Base*
```

```cpp
Derived d;

Base* ptr = &d;
```

Every `Derived` **is a** `Base`.

Compiler allows it automatically.

---

## Downcasting (May Be Unsafe)

```
Base*

↓

Derived*
```

```cpp
Base* ptr;

Derived* d = ????
```

Question:

Is the actual object really a `Derived`?

Compiler doesn't know.

This is why `dynamic_cast` exists.

---

# Example 1 : Successful Cast

```cpp
#include <iostream>
using namespace std;

class Base
{
public:
    virtual ~Base() {}
};

class Derived : public Base
{
public:
    void show()
    {
        cout << "Derived Object";
    }
};

int main()
{
    Base* ptr = new Derived();

    Derived* dptr = dynamic_cast<Derived*>(ptr);

    if(dptr)
    {
        dptr->show();
    }

    delete ptr;
}
```

Output

```
Derived Object
```

---

# Step-by-Step

### Step 1

```
Base* ptr = new Derived();
```

Memory

```
ptr
 │
 ▼
+----------------------+
| Base                 |
|----------------------|
| Derived              |
+----------------------+
```

Pointer type

```
Base*
```

Actual object

```
Derived
```

---

### Step 2

```
dynamic_cast<Derived*>(ptr)
```

Compiler checks **at runtime**

```
Is the object actually Derived?
```

Answer

```
YES
```

Return

```
Derived*
```

```
dptr
 │
 ▼
+----------------------+
| Base                 |
|----------------------|
| Derived              |
+----------------------+
```

Now we can access

```cpp
dptr->show();
```

---

# Example 2 : Failed Cast

```cpp
Base* ptr = new Base();

Derived* dptr = dynamic_cast<Derived*>(ptr);

if(dptr == nullptr)
{
    cout << "Invalid Cast";
}
```

Output

```
Invalid Cast
```

---

# Why?

Memory

```
ptr
 │
 ▼
+---------+
| Base    |
+---------+
```

There is **no Derived part**.

When C++ checks

```
Is this object Derived?
```

Answer

```
NO
```

Return

```
nullptr
```

---

# Why not use static_cast?

```cpp
Derived* dptr = static_cast<Derived*>(ptr);
```

Compiler allows it.

But

```
Base* ptr = new Base();
```

Memory

```
+---------+
| Base    |
+---------+
```

After

```
static_cast
```

```
dptr
 │
 ▼
+---------+
| Base    |
+---------+
```

Compiler **assumes** it's a `Derived`.

Now

```cpp
dptr->show();
```

This is **Undefined Behavior** because the object isn't actually a `Derived`.

`static_cast` performs **no runtime check**.

---

# Why is a Virtual Function Required?

```cpp
class Base
{
public:
    virtual ~Base() {}
};
```

Without a virtual function

```cpp
class Base
{
};
```

Compilation Error

```
dynamic_cast requires polymorphic type
```

---

# Why?

`dynamic_cast` uses **Run-Time Type Information (RTTI)**.

Only **polymorphic classes** (classes with at least one virtual function) contain RTTI.

Memory

```
Derived Object

+----------------------+
| vptr                 |
| Base Data            |
| Derived Data         |
+----------------------+
```

The **vptr** points to the **vtable**, which contains RTTI.

Using RTTI,

`dynamic_cast` can determine

```
Actual Object Type

↓

Derived
```

Without a virtual function,

there is **no vptr**, **no vtable**, and **no RTTI**.

So runtime type checking is impossible.

---

# Pointer vs Reference

## Pointer

```cpp
Derived* d = dynamic_cast<Derived*>(ptr);
```

Failure

```
nullptr
```

---

## Reference

```cpp
Derived& d = dynamic_cast<Derived&>(obj);
```

Failure

Throws

```cpp
std::bad_cast
```

Example

```cpp
try
{
    Derived& d = dynamic_cast<Derived&>(*ptr);
}
catch(const bad_cast&)
{
    cout << "Invalid Cast";
}
```

---

# static_cast vs dynamic_cast

| Feature | static_cast | dynamic_cast |
|----------|-------------|--------------|
| Runtime Check | ❌ No | ✅ Yes |
| Downcasting | Unsafe | Safe |
| Upcasting | ✅ Yes | ✅ Yes |
| Needs Virtual Function | ❌ No | ✅ Yes |
| Failed Pointer Cast | Undefined Behavior | `nullptr` |
| Failed Reference Cast | Undefined Behavior | `std::bad_cast` |

---

# When to Use dynamic_cast

✅ Safe downcasting

✅ Runtime type checking

✅ Polymorphic hierarchy

Examples

- Game engines
- GUI frameworks
- Plugin systems
- Serialization
- Compiler design

---

# Interview Answer (30 Seconds)

`dynamic_cast` is used for **safe downcasting** in a polymorphic class hierarchy. It performs a **runtime check** using RTTI to verify whether the object is actually of the requested derived type. If the cast is valid, it returns the converted pointer; otherwise, it returns `nullptr` (or throws `std::bad_cast` for references). Because RTTI is stored in the virtual table, the base class must have at least one virtual function.

---

# 3. const_cast

Used for:

- Adding const
- Removing const

Example:

```cpp
int x = 10;

const int* ptr = &x;

int* p = const_cast<int*>(ptr);

*p = 20;
```

Now:

```text
x = 20
```

Common Use Case

```cpp
void print(char* str)
{
    cout << str;
}

const char* name = "John";

print(const_cast<char*>(name));
```

Warning:

Removing const from an actually constant object and modifying it causes Undefined Behavior.

Bad Example:

```cpp
const int x = 10;

int* p = const_cast<int*>(&x);

*p = 20;   // Undefined Behavior
```

---

# 4. reinterpret_cast

Used for:

- Low-level memory manipulation
- Converting unrelated pointer types
- Integer ↔ Pointer conversions

Example:

```cpp
int x = 10;

int* ptr = &x;

char* cptr = reinterpret_cast<char*>(ptr);
```

Example:

```cpp
uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
```

Example:

```cpp
int* ptr = reinterpret_cast<int*>(0x12345678);
```

Warning:

Very dangerous.

Compiler performs almost no safety checks.

Use only in low-level systems programming.

---

# Cast Comparison

| Cast | Safe | Runtime Check | Typical Usage |
|--------|--------|--------|--------|
| static_cast | Yes | No | Numeric conversion, upcasting |
| dynamic_cast | Yes | Yes | Safe downcasting |
| const_cast | Limited | No | Add/remove const |
| reinterpret_cast | No | No | Low-level memory operations |

---

# C-style Cast vs Modern Cast

Old Style:

```cpp
int y = (int)x;
```

Modern Style:

```cpp
int y = static_cast<int>(x);
```

Modern C++ recommends:

```cpp
static_cast
dynamic_cast
const_cast
reinterpret_cast
```

instead of C-style casts because intent is explicit and safer.

---

# Python Equivalent

Python does not have:

```text
static_cast
dynamic_cast
const_cast
reinterpret_cast
```

Instead it uses conversion functions:

```python
int()
float()
str()
bool()
```

Python references are type-safe and managed by the runtime.

---

# Go Equivalent

Go does not have:

```text
static_cast
dynamic_cast
const_cast
reinterpret_cast
```

Most conversions use:

```go
Type(value)
```

Example:

```go
float64(x)
int(y)
```

Low-level reinterpretation exists through:

```go
unsafe.Pointer
```

which is similar in spirit to C++'s `reinterpret_cast`.
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

# Constructors and Object Lifecycle

## C++ vs Python vs Go

---

# 1. Default Constructor

Creates an object with default values.

## C++

```cpp
class Employee
{
public:
    int id;

    Employee()
    {
        id = 0;
    }
};

Employee e;
```

## Python

```python
class Employee:
    def __init__(self):
        self.id = 0

e = Employee()
```

## Go

```go
type Employee struct {
    Id int
}

func NewEmployee() Employee {
    return Employee{Id: 0}
}

e := NewEmployee()
```

---

# 2. Parameterized Constructor

Pass values during object creation.

## C++

```cpp
class Employee
{
public:
    int id;

    Employee(int i)
    {
        id = i;
    }
};

Employee e(10);
```

## Python

```python
class Employee:
    def __init__(self, id):
        self.id = id

e = Employee(10)
```

## Go

```go
type Employee struct {
    Id int
}

func NewEmployee(id int) Employee {
    return Employee{Id: id}
}

e := NewEmployee(10)
```

---

# 3. Copy Constructor

Creates a new object from another object.

## C++

```cpp
class Employee
{
public:
    int id;

    Employee(int i)
    {
        id = i;
    }

    Employee(const Employee& other)
    {
        id = other.id;
    }
};

Employee e1(10);
Employee e2(e1);
```

## Python

```python
import copy

class Employee:
    def __init__(self, id):
        self.id = id

e1 = Employee(10)
e2 = copy.copy(e1)
```

## Go

```go
type Employee struct {
    Id int
}

e1 := Employee{Id: 10}
e2 := e1
```

---

# 4. Copy Assignment Operator

Assign existing object to another existing object.

## C++

```cpp
class Employee
{
public:
    int id;

    Employee& operator=(const Employee& other)
    {
        id = other.id;
        return *this;
    }
};

Employee e1(10);
Employee e2(20);

e2 = e1;
```

## Python

```python
e2 = e1
```

Actual copy:

```python
import copy

e2 = copy.copy(e1)
```

## Go

```go
e2 = e1
```

---

# 5. Move Constructor

Transfers ownership instead of copying.

## C++

```cpp
#include <vector>

class Employee
{
public:
    std::vector<int> data;

    Employee(Employee&& other)
    {
        data = std::move(other.data);
    }
};

Employee e1;
Employee e2(std::move(e1));
```

## Python

Not supported.

Python uses references and garbage collection.

```python
a = [1, 2, 3]
b = a
```

## Go

Not supported.

Go uses value semantics and garbage collection.

---

# 6. Move Assignment Operator

Move data into an existing object.

## C++

```cpp
class Employee
{
public:
    std::vector<int> data;

    Employee& operator=(Employee&& other)
    {
        data = std::move(other.data);
        return *this;
    }
};

e2 = std::move(e1);
```

## Python

Not available.

## Go

Not available.

---

# 7. Delegating Constructor

One constructor calls another.

## C++

```cpp
class Employee
{
public:
    int id;

    Employee() : Employee(0)
    {
    }

    Employee(int i)
    {
        id = i;
    }
};
```

## Python

```python
class Employee:
    def __init__(self, id=0):
        self.id = id
```

## Go

```go
func NewEmployee() Employee {
    return NewEmployeeWithId(0)
}

func NewEmployeeWithId(id int) Employee {
    return Employee{Id: id}
}
```

---

# 8. Conversion Constructor

Converts one type into another.

## C++

```cpp
class Employee
{
public:
    int id;

    Employee(int i)
    {
        id = i;
    }
};

Employee e = 10;
```

Prevent implicit conversion:

```cpp
class Employee
{
public:
    int id;

    explicit Employee(int i)
    {
        id = i;
    }
};
```

## Python

```python
class Employee:
    def __init__(self, value):
        self.id = int(value)

e = Employee("10")
```

## Go

```go
func NewEmployee(value string) Employee {
    id, _ := strconv.Atoi(value)
    return Employee{Id: id}
}
```

---

# 9. Destructor

Called when object is destroyed.

## C++

```cpp
class Employee
{
public:
    ~Employee()
    {
        std::cout << "Destroyed\n";
    }
};
```

## Python

```python
class Employee:
    def __del__(self):
        print("Destroyed")
```

## Go

No destructor.

Use:

```go
defer file.Close()
```

---

# Rule of 3

If a class manages resources and defines one of these:

```text
Destructor
Copy Constructor
Copy Assignment Operator
```

it usually needs all three.

---

# Rule of 5

Modern C++ adds move semantics.

```text
Destructor
Copy Constructor
Copy Assignment Operator
Move Constructor
Move Assignment Operator
```

Example:

```cpp
class Employee
{
public:
    Employee();

    ~Employee();

    Employee(const Employee&);
    Employee& operator=(const Employee&);

    Employee(Employee&&);
    Employee& operator=(Employee&&);
};
```

---

# Rule of 0

Prefer letting the compiler generate everything.

```cpp
class Employee
{
public:
    std::string name;
    int age;
};
```

No destructor.
No copy constructor.
No move constructor.
No assignment operators.

Compiler-generated versions are sufficient.

---

# Quick Comparison

| Feature                   | C++ | Python               | Go               |
| ------------------------- | --- | -------------------- | ---------------- |
| Default Constructor       | Yes | Yes                  | Factory Function |
| Parameterized Constructor | Yes | Yes                  | Factory Function |
| Copy Constructor          | Yes | No                   | Struct Copy      |
| Copy Assignment           | Yes | Reference Assignment | Value Assignment |
| Move Constructor          | Yes | No                   | No               |
| Move Assignment           | Yes | No                   | No               |
| Delegating Constructor    | Yes | Default Arguments    | Factory Function |
| Conversion Constructor    | Yes | Dynamic Conversion   | Factory Function |
| Destructor                | Yes | **del**              | No               |
| Rule of 3                 | Yes | No                   | No               |
| Rule of 5                 | Yes | No                   | No               |
| Rule of 0                 | Yes | N/A                  | N/A              |

---

# Easy Way To Remember

```text
C++
 ├─ Constructor
 │   ├─ Default
 │   ├─ Parameterized
 │   ├─ Copy
 │   ├─ Move
 │   └─ Delegating
 │
 ├─ Assignment
 │   ├─ Copy Assignment
 │   └─ Move Assignment
 │
 └─ Destructor

Python
 ├─ __init__()
 ├─ copy.copy()
 ├─ copy.deepcopy()
 ├─ Reference Assignment
 └─ __del__()

Go
 ├─ Struct Literal
 ├─ Factory Function
 ├─ Value Copy
 ├─ Pointer Sharing
 └─ Garbage Collector
```

---

# One-Line Summary

```text
C++  -> Explicit ownership (copy, move, destroy)
Python -> Reference-based objects (copy when needed)
Go -> Value semantics by default (copy structs, share pointers)
```

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

