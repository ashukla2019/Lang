# STL Sequence Containers Cheat Sheet (Vector, List & Deque)

> **Interview Goal:** Know **when to use**, **how it works internally**, **time complexities**, and **important APIs**.

---

# STL Sequence Containers

```
Sequence Containers
│
├── vector   → Dynamic Array
├── list     → Doubly Linked List
└── deque    → Double Ended Queue
```

---

# Comparison

| Feature | vector | list | deque |
|----------|--------|------|-------|
| Internal Structure | Dynamic Array | Doubly Linked List | Multiple Fixed-size Arrays |
| Random Access | ✅ O(1) | ❌ O(n) | ✅ O(1) |
| Insert Front | ❌ O(n) | ✅ O(1) | ✅ O(1) |
| Insert Back | ✅ O(1)* | ✅ O(1) | ✅ O(1) |
| Insert Middle | ❌ O(n) | ✅ O(1)* | ❌ O(n) |
| Delete Front | ❌ O(n) | ✅ O(1) | ✅ O(1) |
| Delete Back | ✅ O(1) | ✅ O(1) | ✅ O(1) |
| Memory | Contiguous | Non-contiguous | Chunked |
| Cache Friendly | ✅ Excellent | ❌ Poor | Good |

\*Ignoring time to find the insertion position.

---

# 1. std::vector

## What is it?

A **dynamic array** that automatically grows when full.

```cpp
template<class T, class Alloc = allocator<T>> //T → Type of elements stored (e.g., int, string)
Alloc → Memory allocator used to allocate and deallocate memory for those elements.
class vector;
```

Default allocator:

```cpp
std::allocator
```

It allocates memory on the heap.

---

# Internal Memory

```
Capacity = 4

+----+----+----+----+
|10  |20  |30  |40  |
+----+----+----+----+

size = 4
capacity = 4
```

Push another element

```
push_back(50)

↓

Allocate capacity 8

+----+----+----+----+----+----+----+----+
|10  |20  |30  |40  |50  |    |    |    |
+----+----+----+----+----+----+----+----+
```

Old memory deleted.

---

# How Vector Grows

When capacity becomes full:

1. Allocate almost **2× bigger memory**
2. Copy/Move all elements
3. Delete old memory

Therefore,

```
push_back()

Normally      → O(1)

Reallocation  → O(n)
```

Average complexity is **Amortized O(1)**.

---

# Characteristics

- Ordered container
- Dynamic size
- Contiguous memory
- Random access
- Cache friendly
- Stores copies of objects

---

# Time Complexity

| Operation | Complexity |
|-----------|------------|
| Access [] | O(1) |
| at() | O(1) |
| front() | O(1) |
| back() | O(1) |
| push_back() | O(1) amortized |
| pop_back() | O(1) |
| insert front | O(n) |
| insert middle | O(n) |
| erase middle | O(n) |
| find | O(n) |

---

# Important APIs

## Creation

```cpp
vector<int> v;

vector<int> v(5);

vector<int> v(5,10);

vector<int> v={1,2,3};
```

---

## Access

```cpp
v[2]

v.at(2)

v.front()

v.back()

v.data()
```

---

## Capacity

```cpp
v.size()

v.capacity()

v.empty()

v.reserve(100)

v.resize(20)

v.shrink_to_fit()
```

---

## Add

```cpp
v.push_back(10);

v.emplace_back(10);

v.insert(v.begin()+2,50);
```

---

## Remove

```cpp
v.pop_back();

v.erase(v.begin());

v.erase(v.begin()+2);

v.clear();
```

---

## Remove all occurrences

```cpp
v.erase(
    remove(v.begin(),v.end(),20),
    v.end()
);
```

Complexity

```
O(n)
```

---

# emplace_back vs push_back

```cpp
push_back(obj)
```

Copies/Moves object.

```cpp
emplace_back(args...)
```

Constructs object directly inside vector.

Prefer

```
emplace_back()
```

for user-defined objects.

---

# When to Use Vector

✅ Random access

✅ Frequent read

✅ Insert/Delete at end

❌ Frequent insert/delete in middle

---

# 2. std::list

## What is it?

A **Doubly Linked List**.

```cpp
template<class T,class Alloc=allocator<T>>
class list;
```

---

# Internal Structure

```
NULL

↓

+------+     +------+     +------+
|10| * |<--->|20| * |<--->|30| * |
+------+     +------+     +------+

↑                                 ↑

NULL                           NULL
```

Each node stores

- Data
- Previous pointer
- Next pointer

---

# Characteristics

- Non-contiguous memory
- Doubly linked list
- No random access
- Fast insertion/deletion
- Extra memory for pointers

---

# Time Complexity

| Operation | Complexity |
|-----------|------------|
| front() | O(1) |
| back() | O(1) |
| push_front() | O(1) |
| push_back() | O(1) |
| pop_front() | O(1) |
| pop_back() | O(1) |
| insert(iterator) | O(1) |
| erase(iterator) | O(1) |
| find | O(n) |
| Access by index | O(n) |

---

# Why No [] ?

Nodes are scattered in memory.

Need traversal.

```cpp
auto it = next(lst.begin(),2);
```

Cannot do

```cpp
lst[2]
```

---

# Important APIs

## Creation

```cpp
list<int> l;

list<int> l(5);

list<int> l(5,10);

list<int> l={1,2,3};
```

---

## Access

```cpp
l.front();

l.back();
```

---

## Add

```cpp
l.push_front(10);

l.push_back(20);

l.insert(it,50);

l.emplace_front(5);

l.emplace_back(100);
```

---

## Remove

```cpp
l.pop_front();

l.pop_back();

l.erase(it);

l.remove(20);

l.clear();
```

---

# When to Use List

✅ Frequent insertion/deletion

✅ Queue implementation

✅ LRU Cache

❌ Random access

❌ Binary Search

---

# 3. std::deque

## What is it?

Deque means

```
Double Ended Queue
```

Supports insertion/removal from

- Front
- Back

in O(1).

```cpp
template<class T,class Alloc=allocator<T>>
class deque;
```

---

# Internal Structure

Unlike vector,

deque is **NOT contiguous**.

```
Map

↓

+-----+-----+-----+

↓

Block1

10 20 30

↓

Block2

40 50 60

↓

Block3

70 80
```

Multiple fixed-size memory blocks.

---

# Characteristics

- Random access
- Fast front insertion
- Fast back insertion
- No large reallocations
- Slightly slower than vector for indexing

---

# Time Complexity

| Operation | Complexity |
|-----------|------------|
| [] | O(1) |
| front() | O(1) |
| back() | O(1) |
| push_front() | O(1) |
| push_back() | O(1) |
| pop_front() | O(1) |
| pop_back() | O(1) |
| insert middle | O(n) |
| erase middle | O(n) |

---

# Important APIs

## Creation

```cpp
deque<int> d;

deque<int> d(5);

deque<int> d={1,2,3};
```

---

## Access

```cpp
d[2];

d.at(2);

d.front();

d.back();
```

---

## Add

```cpp
d.push_front(5);

d.push_back(10);

d.emplace_front(1);

d.emplace_back(20);
```

---

## Remove

```cpp
d.pop_front();

d.pop_back();

d.erase(d.begin());

d.clear();
```

---

# When to Use Deque

✅ Need fast insertion at both ends

✅ Sliding Window problems

✅ Monotonic Queue

✅ BFS

❌ Frequent middle insertion

---

# Common Functions (All Three)

| Function | vector | list | deque |
|----------|--------|------|-------|
| begin() | ✅ | ✅ | ✅ |
| end() | ✅ | ✅ | ✅ |
| rbegin() | ✅ | ✅ | ✅ |
| rend() | ✅ | ✅ | ✅ |
| size() | ✅ | ✅ | ✅ |
| empty() | ✅ | ✅ | ✅ |
| clear() | ✅ | ✅ | ✅ |
| swap() | ✅ | ✅ | ✅ |
| emplace() | ✅ | ✅ | ✅ |
| emplace_back() | ✅ | ✅ | ✅ |

---

# Which Container Should I Choose?

```
Need random access?
        │
       YES
        │
 Insert/Delete only at end?
        │
   YES ─────► vector
        │
        NO
        │
Need fast front insertion?
        │
       YES
        │
      deque
```

```
Need frequent insert/delete in middle?
        │
       YES
        │
       list
```

---

# Interview Tips

### Use **vector** when

- Random access is required
- Mostly reading data
- Insertion/deletion at end

---

### Use **list** when

- Frequent insertion/deletion
- Iterator stability is important
- Random access is not needed

---

### Use **deque** when

- Need queue from both ends
- Sliding window
- BFS
- Monotonic queue

---

# Quick Revision

| Container | Best Feature | Biggest Limitation |
|-----------|--------------|--------------------|
| **vector** | Fast random access | Slow front/middle insertion |
| **list** | Fast insertion/deletion anywhere (with iterator) | No random access |
| **deque** | Fast insertion at both ends | Middle operations are slow |

---

# Memory Trick

```
Vector
↓
Dynamic Array
↓
Fast Index
↓
Slow Middle Insert

List
↓
Doubly Linked List
↓
Fast Insert/Delete
↓
Slow Indexing

Deque
↓
Double Ended Queue
↓
Fast Front + Back
↓
Random Access Supported
```
