# 🚀 C++ vs Python vs Go — COMPLETE PRACTICAL GUIDE

---

# 📌 1. VARIABLES & DATA TYPES

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

# 🔀 2. CONTROL FLOW (if / else)

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

# 🔁 3. LOOPS (ALL TYPES)

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

## 🔹 PYTHON LOOPS (FULL PRACTICAL COVERAGE)

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

## 🔹 GO LOOPS

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

# 🔧 4. FUNCTIONS (FULL PYTHON COVERAGE)

---

## 🔹 C++

```cpp
int add(int a, int b) {
    return a + b;
}
```

---

## 🔹 PYTHON FUNCTIONS (ALL TYPES WITH REAL USE)

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

# 📦 5. DATA STRUCTURES

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

# ⚠️ 6. ERROR HANDLING

### C++

```cpp
try {
    throw 1;
} catch(int e) {
    cout << "Error";
}
```

### Python

```python
try:
    x = 1/0
except:
    print("Error")
```

### Go

```go
if err != nil {
    fmt.Println(err)
}
```

---

# 🧵 7. CONCURRENCY

### Go (example)

```go
go func() {
    fmt.Println("Running in goroutine")
}()
```

---

# 🔑 FINAL TAKEAWAY

If you master:

* Loops
* Functions
* Data structures

👉 You can switch between languages easily.

---

# ✅ END
