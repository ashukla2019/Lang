# Basic Vector Class Implementation in C++

This is a simplified implementation of `std::vector` to understand how a dynamic array works internally.

---

# Features

- Dynamic array
- `push_back()`
- `pop_back()`
- `operator[]`
- `size()`
- `capacity()`
- Automatic resizing
- Destructor

---

# Data Members

```cpp
template<typename T>
class Vector
{
private:
    T* data;          // Pointer to dynamic array
    size_t sz;        // Number of elements
    size_t cap;       // Allocated capacity

public:
```

---

# Constructor

Initially no memory is allocated.

```cpp
    Vector()
        : data(nullptr), sz(0), cap(0)
    {
    }
```

---

# Destructor

Free allocated memory.

```cpp
    ~Vector()
    {
        delete[] data;
    }
```

---

# size()

Returns number of stored elements.

```cpp
    size_t size() const
    {
        return sz;
    }
```

---

# capacity()

Returns allocated capacity.

```cpp
    size_t capacity() const
    {
        return cap;
    }
```

---

# operator[]

Access elements like an array.

```cpp
    T& operator[](size_t index)
    {
        return data[index];
    }

    const T& operator[](size_t index) const
    {
        return data[index];
    }
```

---

# resize()

Allocates a larger array and copies existing elements.

```cpp
private:

    void resize(size_t newCapacity)
    {
        T* newData = new T[newCapacity];

        for(size_t i = 0; i < sz; i++)
        {
            newData[i] = data[i];
        }

        delete[] data;

        data = newData;
        cap = newCapacity;
    }
```

---

# push_back()

Adds a new element at the end.

```cpp
public:

    void push_back(const T& value)
    {
        if(sz == cap)
        {
            size_t newCapacity = (cap == 0) ? 1 : cap * 2;
            resize(newCapacity);
        }

        data[sz++] = value;
    }
```

---

# pop_back()

Removes the last element.

```cpp
    void pop_back()
    {
        if(sz > 0)
        {
            sz--;
        }
    }
```

---

# Complete Code

```cpp
#include <iostream>

template<typename T>
class Vector
{
private:
    T* data;
    size_t sz;
    size_t cap;

    void resize(size_t newCapacity)
    {
        T* newData = new T[newCapacity];

        for(size_t i = 0; i < sz; i++)
        {
            newData[i] = data[i];
        }

        delete[] data;

        data = newData;
        cap = newCapacity;
    }

public:

    Vector()
        : data(nullptr), sz(0), cap(0)
    {
    }

    ~Vector()
    {
        delete[] data;
    }

    void push_back(const T& value)
    {
        if(sz == cap)
        {
            size_t newCapacity = (cap == 0) ? 1 : cap * 2;
            resize(newCapacity);
        }

        data[sz++] = value;
    }

    void pop_back()
    {
        if(sz > 0)
            sz--;
    }

    size_t size() const
    {
        return sz;
    }

    size_t capacity() const
    {
        return cap;
    }

    T& operator[](size_t index)
    {
        return data[index];
    }

    const T& operator[](size_t index) const
    {
        return data[index];
    }
};

int main()
{
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    std::cout << "Size     : " << v.size() << std::endl;
    std::cout << "Capacity : " << v.capacity() << std::endl;

    for(size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }

    std::cout << std::endl;

    v.pop_back();

    std::cout << "After pop_back()" << std::endl;

    for(size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }

    std::cout << std::endl;
}
```

---

# Memory Growth

Initially

```
Size = 0
Capacity = 0
```

After `push_back(10)`

```
Capacity = 1

+----+
|10  |
+----+
```

After `push_back(20)`

```
Capacity doubles to 2

+----+----+
|10  |20  |
+----+----+
```

After `push_back(30)`

```
Capacity doubles to 4

+----+----+----+----+
|10  |20  |30  |    |
+----+----+----+----+
```

After `push_back(40)`

```
+----+----+----+----+
|10  |20  |30  |40  |
+----+----+----+----+
```

---

# Time Complexity

| Operation | Complexity |
|-----------|------------|
| push_back() | O(1) amortized |
| pop_back() | O(1) |
| operator[] | O(1) |
| size() | O(1) |
| capacity() | O(1) |
| resize() | O(n) |

---

# Limitations of This Basic Implementation

This simplified version **does not implement**:

- Copy constructor
- Copy assignment operator
- Move constructor
- Move assignment operator
- `reserve()`
- `resize()` (public version)
- `clear()`
- `insert()`
- `erase()`
- Iterators
- Exception safety
- Custom allocator
- Placement `new`
- Perfect forwarding (`emplace_back()`)

It is intended to demonstrate the core idea behind how `std::vector` manages a dynamic array.