# C++ Rule of Five - Constructor Call Cases

## Sample Class

``` cpp
#include <iostream>
using namespace std;

class MyClass
{
    int *data;

public:
    MyClass() { data = new int(0); cout<<"Default Constructor\n"; }

    MyClass(int value) {
        data = new int(value);
        cout<<"Parameterized Constructor\n";
    }

    MyClass(const MyClass &other) {
        data = new int(*other.data);
        cout<<"Copy Constructor\n";
    }

    MyClass(MyClass &&other) noexcept {
        data = other.data;
        other.data = nullptr;
        cout<<"Move Constructor\n";
    }

    MyClass& operator=(const MyClass &other) {
        cout<<"Copy Assignment\n";
        if(this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }

    MyClass& operator=(MyClass &&other) noexcept {
        cout<<"Move Assignment\n";
        if(this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    ~MyClass() {
        cout<<"Destructor\n";
        delete data;
    }
};
```

## Cases

### Default Constructor

``` cpp
MyClass a;
```

### Parameterized Constructor

``` cpp
MyClass a(10);
```

### Copy Constructor (new object)

``` cpp
MyClass a(10);
MyClass b(a);
// or
MyClass b = a;
```

### Copy Assignment (existing object)

``` cpp
MyClass a(10);
MyClass b(20);
b = a;
```

### Move Constructor

``` cpp
MyClass a(std::move(MyClass(100)));
// or
MyClass b(std::move(a));
```

### Move Assignment

``` cpp
MyClass a(10);
a = MyClass(50);

// or
MyClass b(20);
b = std::move(a);
```

### Pass by Value

``` cpp
void fun(MyClass obj);

MyClass a(10);
fun(a);              // Copy Constructor
fun(MyClass(10));    // Move Constructor or Copy Elision
```

### Return by Value

``` cpp
MyClass create()
{
    MyClass t(10);
    return t;         // Move Constructor or RVO
}
```

### vector::push_back

``` cpp
vector<MyClass> v;
MyClass a(10);

v.push_back(a);            // Copy Constructor
v.push_back(MyClass(20));  // Move Constructor
```

### vector::emplace_back

``` cpp
vector<MyClass> v;
v.emplace_back(100);       // Parameterized Constructor only
```

## Summary

  Statement                    Calls
  ---------------------------- ------------------------------------
  `MyClass a;`                 Default Constructor
  `MyClass a(10);`             Parameterized Constructor
  `MyClass b(a);`              Copy Constructor
  `MyClass b = a;`             Copy Constructor
  `b = a;`                     Copy Assignment
  `MyClass b(std::move(a));`   Move Constructor
  `b = std::move(a);`          Move Assignment
  `MyClass b = MyClass(10);`   Move Constructor (or Copy Elision)
  `b = MyClass(10);`           Move Assignment
  `fun(a);`                    Copy Constructor
  `fun(MyClass(10));`          Move Constructor (or Copy Elision)
  `return obj;`                Move Constructor (or RVO)
  `push_back(a);`              Copy Constructor
  `push_back(MyClass(10));`    Move Constructor
  `emplace_back(10);`          Parameterized Constructor only

## Easy Rule

-   Creating a **new object** â†’ Constructor.
-   Existing object gets a new value â†’ Assignment operator.
-   Source is an **lvalue** â†’ Copy.
-   Source is an **rvalue/temporary** or `std::move()` â†’ Move.
-   Returning temporaries â†’ Usually Move, but often optimized away by
    RVO/NRVO.