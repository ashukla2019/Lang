# Pair and Tuple in C++

## Overview

`pair` and `tuple` are utility classes in C++ used to store multiple values together.

- `pair` stores **exactly two values**.
- `tuple` stores **multiple values (0 or more)**.

---

# C++ Standard Version

| Feature | Introduced |
|---|---|
| `std::pair` | C++98 |
| `std::make_pair` | C++98 |
| `std::tuple` | C++11 |
| `std::make_tuple` | C++11 |
| `std::get<>` | C++11 |
| Structured bindings | C++17 |

---

# 1. std::pair

## Definition

A pair stores two related values.

Header:

```cpp
#include <utility>
```

Syntax:

```cpp
pair<data_type1, data_type2> variable;
```

Example:

```cpp
#include <iostream>
#include <utility>

using namespace std;

int main()
{
    pair<int, string> p = {1, "Alice"};

    cout << p.first << endl;
    cout << p.second << endl;

    return 0;
}
```

Output:

```
1
Alice
```

---

# Accessing Pair Values

A pair has two members:

| Member | Meaning |
|---|---|
| `.first` | First value |
| `.second` | Second value |

Example:

```cpp
pair<int,int> point = {10,20};

cout << point.first;   // 10
cout << point.second;  // 20
```

---

# Creating Pair Using make_pair()

Instead of explicitly writing types:

```cpp
auto p = make_pair(10, "Hello");
```

Equivalent:

```cpp
pair<int,string> p = {10,"Hello"};
```

---

# Pair Example: Returning Multiple Values

A function can return two values using pair.

Example:

```cpp
pair<int,int> divide(int a, int b)
{
    return {a/b, a%b};
}

int main()
{
    auto result = divide(10,3);

    cout << result.first << endl;   // Quotient
    cout << result.second << endl;  // Remainder
}
```

Output:

```
3
1
```

---

# Pair with Vector

Very common in competitive programming.

Example:

```cpp
vector<pair<int,int>> v;

v.push_back({1,2});
v.push_back({3,4});

for(auto p : v)
{
    cout << p.first << " "
         << p.second << endl;
}
```

Output:

```
1 2
3 4
```

---

# Sorting Vector of Pairs

Pairs are sorted:

1. First by `.first`
2. Then by `.second`

Example:

```cpp
vector<pair<int,int>> v =
{
    {3,100},
    {1,50},
    {2,80}
};

sort(v.begin(), v.end());
```

Result:

```
(1,50)
(2,80)
(3,100)
```

---

# Common Uses of Pair

## Coordinates

```cpp
pair<int,int> point = {x,y};
```

Example:

```
(10,20)
```

---

## Graph Algorithms

Store:

```
(distance, node)
```

Example:

```cpp
pair<int,int> edge = {5,3};
```

Meaning:

```
distance = 5
node = 3
```

---

# 2. std::tuple

## Definition

A tuple can store multiple values of different types.

Header:

```cpp
#include <tuple>
```

Syntax:

```cpp
tuple<type1,type2,type3,...> variable;
```

Example:

```cpp
tuple<int,string,double> student =
{
    1,
    "Alice",
    95.5
};
```

---

# Accessing Tuple Values

Use:

```cpp
get<index>(tuple)
```

Example:

```cpp
tuple<int,string,double> student =
{
    1,
    "Alice",
    95.5
};

cout << get<0>(student) << endl;
cout << get<1>(student) << endl;
cout << get<2>(student) << endl;
```

Output:

```
1
Alice
95.5
```

---

# Tuple Indexing

Tuple indexing starts from zero.

Example:

```cpp
tuple<int,string,double> t;
```

Mapping:

```
get<0>() → int
get<1>() → string
get<2>() → double
```

---

# Creating Tuple Using make_tuple()

Example:

```cpp
auto t = make_tuple(1,"Bob",90.5);
```

Equivalent:

```cpp
tuple<int,string,double> t =
{
    1,
    "Bob",
    90.5
};
```

---

# Tuple Example: Returning Multiple Values

Example:

```cpp
tuple<int,int,int> calculate(int a,int b)
{
    return {a+b, a-b, a*b};
}

int main()
{
    auto result = calculate(10,5);

    cout << get<0>(result) << endl;
    cout << get<1>(result) << endl;
    cout << get<2>(result) << endl;
}
```

Output:

```
15
5
50
```

---

# Structured Binding (C++17)

Before C++17:

```cpp
pair<int,string> p = {1,"Alice"};

cout << p.first;
cout << p.second;
```

C++17 introduced structured binding:

```cpp
auto [id,name] = p;

cout << id;
cout << name;
```

---

# Structured Binding with Tuple

Example:

```cpp
tuple<int,string,double> t =
{
    1,
    "Alice",
    95.5
};

auto [id,name,marks] = t;

cout << id << endl;
cout << name << endl;
cout << marks << endl;
```

Output:

```
1
Alice
95.5
```

---

# Pair vs Tuple

| Feature | Pair | Tuple |
|---|---|---|
| Values stored | 2 | Multiple |
| Header | `<utility>` | `<tuple>` |
| Access | `.first`, `.second` | `get<index>()` |
| Introduced | C++98 | C++11 |
| Common usage | Very frequent | Less frequent |

---

# When to Use Pair?

Use pair when you have exactly two related values.

Examples:

```
(x,y) coordinate

(distance,node)

(start,end)

(key,value)
```

Example:

```cpp
pair<int,int> range = {10,20};
```

---

# When to Use Tuple?

Use tuple when you need three or more values.

Examples:

```
(id,name,salary)

(row,column,distance)

(x,y,z)
```

Example:

```cpp
tuple<int,int,int> cell =
{
    row,
    column,
    distance
};
```

---

# Quick Memory Trick

## Pair

```
pair = exactly 2 things

.first
.second
```

## Tuple

```
tuple = many things

get<0>
get<1>
get<2>
...
```

---

# Summary

- `pair` has existed since **C++98**.
- `tuple` was introduced in **C++11**.
- Structured bindings came in **C++17**.
- Pair is used more often in algorithms.
- Tuple is useful when returning or grouping multiple values.
