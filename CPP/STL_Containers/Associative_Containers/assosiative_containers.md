# STL Ordered Associative Containers Cheat Sheet (Map, Set, Multimap & Multiset)

> **Interview Goal:** Know **when to use**, **internal implementation (Red-Black Tree)**, **time complexities**, **allocators**, **comparison functions**, and **important APIs**.

---

# STL Ordered Associative Containers

```
Ordered Associative Containers
│
├── set         → Unique Keys
├── multiset    → Duplicate Keys
├── map         → Unique Key-Value Pairs
└── multimap    → Duplicate Key-Value Pairs
```

---

# Comparison

| Feature | set | multiset | map | multimap |
|----------|-----|----------|-----|----------|
| Stores | Keys | Keys | Key-Value Pair | Key-Value Pair |
| Duplicate Keys | ❌ | ✅ | ❌ | ✅ |
| Internal Structure | Red-Black Tree | Red-Black Tree | Red-Black Tree | Red-Black Tree |
| Ordered | ✅ | ✅ | ✅ | ✅ |
| Random Access | ❌ | ❌ | ❌ | ❌ |
| Search | O(log n) | O(log n) | O(log n) | O(log n) |
| Insert | O(log n) | O(log n) | O(log n) | O(log n) |
| Delete | O(log n) | O(log n) | O(log n) | O(log n) |

---

# Why Tree?

All ordered associative containers are typically implemented using a **Red-Black Tree**.

```
           40
         /    \
       20      60
      /  \    /  \
    10   30 50   80
```

A Red-Black Tree is a self-balancing Binary Search Tree.

It guarantees

```
Search
Insert
Delete

↓

O(log n)
```

---

# Tree Node

Each node stores

```
+------------------------+
| Left Pointer           |
| Right Pointer          |
| Parent Pointer         |
| Color (Red/Black)      |
| Data                   |
+------------------------+
```

Memory is **NOT contiguous**.

---

# 1. std::set

## What is it?

Stores **unique keys** in sorted order.

```cpp
template<
    class Key,
    class Compare = less<Key>,
    class Alloc = allocator<Key>
>
class set;
```

---

# Template Parameters

```
Key
```

Element type.

```
Compare
```

Sorting rule.

Default

```cpp
less<Key>
```

Ascending order.

```
Alloc
```

Memory allocator.

Default

```cpp
allocator<Key>
```

Allocates tree nodes.

---

# Internal Structure

```
Insert

20 10 30 5

↓

        20
       /  \
     10    30
    /
   5
```

---

# Characteristics

- Unique elements
- Automatically sorted
- No indexing
- Balanced BST
- Fast lookup

---

# Time Complexity

| Operation | Complexity |
|-----------|------------|
| insert | O(log n) |
| erase | O(log n) |
| find | O(log n) |
| count | O(log n) |
| lower_bound | O(log n) |
| upper_bound | O(log n) |
| begin | O(1) |

---

# Important APIs

## Creation

```cpp
set<int> s;

set<int> s={3,1,5};
```

---

## Insert

```cpp
s.insert(10);

s.emplace(20);
```

---

## Remove

```cpp
s.erase(10);

s.erase(it);

s.clear();
```

---

## Search

```cpp
s.find(20);

s.count(20);

s.contains(20);      // C++20
```

---

## Bounds

```cpp
s.lower_bound(20);

s.upper_bound(20);
```

---

# When to Use Set

✅ Need sorted unique values

✅ Fast searching

✅ Remove duplicates

❌ Need indexing

---

# 2. std::multiset

## What is it?

Stores **duplicate keys**.

```cpp
template<
class Key,
class Compare=less<Key>,
class Alloc=allocator<Key>>
class multiset;
```

---

Example

```cpp
multiset<int> ms;

ms.insert(10);

ms.insert(10);

ms.insert(10);
```

Contents

```
10 10 10
```

---

Extra APIs

```cpp
ms.equal_range(10);

ms.count(10);
```

---

Use When

✅ Need duplicates

Example

- Student marks
- Frequencies
- Event timestamps

---

# 3. std::map

## What is it?

Stores

```
Key

↓

Value
```

Pairs.

Keys are unique.

---

Template

```cpp
template<
class Key,
class T,
class Compare=less<Key>,
class Alloc=allocator<pair<const Key,T>>
>
class map;
```

---

# Why pair<const Key,T>?

Map stores

```cpp
pair<const Key,T>
```

Example

```cpp
map<int,string> m;

m[1]="One";
```

Stored object

```cpp
pair<const int,string>
```

The key is **const** because changing it would violate the tree's ordering.

---

# Internal Structure

```
      (5,"Five")
      /        \
 (3,"Three") (8,"Eight")
```

Each node stores

```
pair<const Key,T>
```

---

# Characteristics

- Sorted by key
- Unique keys
- Value lookup
- Balanced BST

---

# Time Complexity

| Operation | Complexity |
|-----------|------------|
| insert | O(log n) |
| erase | O(log n) |
| find | O(log n) |
| operator[] | O(log n) |
| at | O(log n) |

---

# Important APIs

## Creation

```cpp
map<int,string> m;
```

---

## Insert

```cpp
m.insert({1,"One"});

m.emplace(2,"Two");

m[3]="Three";
```

---

## Access

```cpp
m[1];

m.at(1);
```

---

## Search

```cpp
m.find(2);

m.contains(2);    // C++20
```

---

## Remove

```cpp
m.erase(2);

m.clear();
```

---

## Bounds

```cpp
m.lower_bound(5);

m.upper_bound(5);
```

---

# When to Use Map

✅ Dictionary

✅ Phone Book

✅ Frequency Counter

✅ Ordered lookup

---

# 4. std::multimap

Stores duplicate keys.

```cpp
multimap<int,string> mm;

mm.insert({1,"A"});

mm.insert({1,"B"});
```

Contents

```
1 A

1 B
```

Cannot use

```cpp
mm[1]
```

because multiple values exist for the same key.

---

# Allocator

## set

```cpp
template<
class Key,
class Compare=less<Key>,
class Alloc=allocator<Key>>
```

Allocator allocates **tree nodes** containing a key.

---

## map

```cpp
template<
class Key,
class T,
class Compare=less<Key>,
class Alloc=allocator<pair<const Key,T>>
>
```

Allocator allocates **tree nodes** containing

```cpp
pair<const Key,T>
```

---

Unlike vector

```
vector

↓

Contiguous Array

↓

allocator<T>
```

Map and Set allocate **individual Red-Black Tree nodes**, not one large block of memory.

---

# Common Functions

| Function | set | multiset | map | multimap |
|----------|-----|----------|-----|----------|
| begin() | ✅ | ✅ | ✅ | ✅ |
| end() | ✅ | ✅ | ✅ | ✅ |
| insert() | ✅ | ✅ | ✅ | ✅ |
| emplace() | ✅ | ✅ | ✅ | ✅ |
| erase() | ✅ | ✅ | ✅ | ✅ |
| find() | ✅ | ✅ | ✅ | ✅ |
| count() | ✅ | ✅ | ✅ | ✅ |
| lower_bound() | ✅ | ✅ | ✅ | ✅ |
| upper_bound() | ✅ | ✅ | ✅ | ✅ |
| clear() | ✅ | ✅ | ✅ | ✅ |
| size() | ✅ | ✅ | ✅ | ✅ |

---

# Which Container Should I Choose?

```
Need unique sorted values?
        │
       YES
        │
       set
```

```
Need duplicate sorted values?
        │
       YES
        │
    multiset
```

```
Need key-value mapping?
        │
       YES
        │
Need duplicate keys?
        │
   NO ─────► map
        │
   YES ─────► multimap
```

---

# Interview Tips

### Use **set**

- Remove duplicates
- Keep data sorted
- Fast searching

---

### Use **multiset**

- Sorted collection with duplicates

---

### Use **map**

- Dictionary
- Lookup table
- Frequency counter
- Configuration storage

---

### Use **multimap**

- One key → Multiple values
- Student → Multiple courses
- Employee → Multiple projects

---

# Quick Revision

| Container | Best Feature | Biggest Limitation |
|-----------|--------------|--------------------|
| **set** | Unique sorted keys | No indexing |
| **multiset** | Sorted duplicates | No indexing |
| **map** | Sorted key-value lookup | Keys are unique |
| **multimap** | Multiple values per key | No `operator[]` |

---

# Memory Trick

```
set
↓
Unique
↓
Sorted
↓
Red-Black Tree

multiset
↓
Duplicates
↓
Sorted
↓
Red-Black Tree

map
↓
Key → Value
↓
Unique Keys
↓
Red-Black Tree

multimap
↓
Key → Multiple Values
↓
Sorted
↓
Red-Black Tree
```

# Common STL APIs Comparison (set & map)

---

## 1. Creation

| Operation | set | map |
|-----------|-----|-----|
| Empty | `set<int> s;` | `map<int,string> m;` |
| Initializer List | `set<int> s={3,1,2};` | `map<int,string> m={{1,"One"},{2,"Two"}};` |
| Copy | `set<int> s2(s1);` | `map<int,string> m2(m1);` |
| Custom Comparator | `set<int, greater<int>> s;` | `map<int,string, greater<int>> m;` |

---

## 2. Access

| Operation | set | map |
|-----------|-----|-----|
| First Element | `*s.begin()` | `m.begin()->first` / `m.begin()->second` |
| Last Element | `*prev(s.end())` | `prev(m.end())->first` |
| Search | `find(key)` | `find(key)` |
| Count | `count(key)` | `count(key)` |
| Contains *(C++20)* | `contains(key)` | `contains(key)` |
| Lower Bound | `lower_bound(key)` | `lower_bound(key)` |
| Upper Bound | `upper_bound(key)` | `upper_bound(key)` |
| Equal Range | `equal_range(key)` | `equal_range(key)` |
| Access Value | ❌ | `m[key]`, `m.at(key)` |

> **Note:** `set` stores only keys, so there is no value to access.

---

## 3. Add

| Operation | set | map |
|-----------|-----|-----|
| Insert | `s.insert(10);` | `m.insert({1,"One"});` |
| Emplace | `s.emplace(20);` | `m.emplace(2,"Two");` |
| Insert with Hint | `s.insert(it,30);` | `m.insert(it,{3,"Three"});` |
| Update Value | ❌ | `m[1]="New Value";` |

---

## 4. Remove

| Operation | set | map |
|-----------|-----|-----|
| Erase by Key | `s.erase(10);` | `m.erase(1);` |
| Erase by Iterator | `s.erase(it);` | `m.erase(it);` |
| Erase Range | `s.erase(first,last);` | `m.erase(first,last);` |
| Clear | `s.clear();` | `m.clear();` |

---

## 5. Capacity

| Operation | set | map |
|-----------|-----|-----|
| Size | `size()` | `size()` |
| Empty | `empty()` | `empty()` |
| Maximum Size | `max_size()` | `max_size()` |

---

## 6. Utility Functions

| Operation | set | map |
|-----------|-----|-----|
| `begin()` | ✅ | ✅ |
| `end()` | ✅ | ✅ |
| `rbegin()` | ✅ | ✅ |
| `rend()` | ✅ | ✅ |
| `cbegin()` | ✅ | ✅ |
| `cend()` | ✅ | ✅ |
| `swap()` | ✅ | ✅ |

---

# Quick Interview Revision

| Requirement | Use |
|-------------|-----|
| Store unique sorted values | `set` |
| Store sorted key-value pairs | `map` |
| Fast search | Both (`O(log n)`) |
| Update value by key | `map` |
| Remove duplicates | `set` |
| Dictionary / Lookup Table | `map` |
| Frequency Counter | `map` |
| Ordered Collection | `set` |

---

# Important Difference

| Feature | set | map |
|----------|-----|-----|
| Stores | Keys | Key-Value Pairs |
| Duplicate Keys | ❌ | ❌ |
| Value Access | ❌ | `[]`, `at()` |
| Key Type | `Key` | `Key` |
| Value Type | Same as Key | Separate (`T`) |
| Internal Node | `Key` | `pair<const Key, T>` |
| Internal Structure | Red-Black Tree | Red-Black Tree |
