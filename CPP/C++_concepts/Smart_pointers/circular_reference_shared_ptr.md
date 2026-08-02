# C++ shared_ptr Circular Reference and weak_ptr Solution

## Problem: Circular Reference with shared_ptr

`shared_ptr` uses **reference counting** to manage object lifetime.

- Creating a `shared_ptr` increases the reference count.
- Destroying a `shared_ptr` decreases the reference count.
- Object is deleted only when the reference count becomes **zero**.

A circular reference happens when an object holds a `shared_ptr` to itself.  
The reference count never becomes zero, causing a memory leak.

## Example using shared_ptr

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Node
{
public:
    shared_ptr<Node> next;

    ~Node()
    {
        cout << "Node destroyed\n";
    }
};

int main()
{
    auto node = make_shared<Node>();

    // Initially:
    // Reference count = 1
    //
    // Assigning node to its own shared_ptr member.
    // Now the object owns itself.
    //
    // Reference count becomes 2.
    node->next = node;

    // When main ends:
    // Local shared_ptr "node" is destroyed.
    //
    // Reference count decreases from 2 to 1.
    //
    // It never becomes zero because node->next
    // is still holding a shared_ptr.
    //
    // Destructor will not be called.

    return 0;
}
```

### Output

```
(no output)
```

## Why does this happen?

```
make_shared<Node>()
        |
        v
Reference count = 1

node->next = node
        |
        v
Reference count = 2

main() ends
        |
        v
Reference count = 1

Object is never destroyed
```

This is called a **circular reference** and causes a memory leak.

---

# Solution: Use weak_ptr

`weak_ptr` is a non-owning smart pointer.

- It can point to an object managed by `shared_ptr`.
- It does not increase the reference count.
- It allows the object to be destroyed normally.

## Example using weak_ptr

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Node
{
public:
    weak_ptr<Node> next;

    ~Node()
    {
        cout << "Node destroyed\n";
    }
};

int main()
{
    auto node = make_shared<Node>();

    // Reference count = 1
    //
    // weak_ptr only observes the object.
    // It does not increase the reference count.
    node->next = node;

    // When main ends:
    // Local shared_ptr "node" is destroyed.
    //
    // Reference count becomes 0.
    //
    // Object is deleted and destructor is called.

    return 0;
}
```

### Output

```
Node destroyed
```

---

# shared_ptr vs weak_ptr

| shared_ptr | weak_ptr |
|------------|----------|
| Owns the object | Does not own the object |
| Increases reference count | Does not increase reference count |
| Controls object lifetime | Only observes object |
| Can create circular references | Breaks circular references |

---

## Key Point

Use:

- `shared_ptr` → when multiple owners need to share ownership.
- `weak_ptr` → when you need a reference without owning the object.

`weak_ptr` is used to avoid circular references and prevent memory leaks.
