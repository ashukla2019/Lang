C++ shared_ptr Circular Reference and weak_ptr Solution
Introduction

shared_ptr manages the lifetime of an object using reference counting.

Creating a shared_ptr increases the reference count.
Destroying a shared_ptr decreases the reference count.
The object is deleted when the reference count becomes zero.

A problem occurs when shared_ptr objects create a circular reference. The reference count never reaches zero, causing a memory leak.

Problem: Circular Reference Using shared_ptr
#include <iostream>
#include <memory>
using namespace std;

class Node {
public:
    shared_ptr<Node> next;

    ~Node() {
        cout << "Node destroyed\n";
    }
};

int main()
{
    auto node = make_shared<Node>();

    // Initially:
    // Reference count = 1
    //
    // Assigning node to its own shared_ptr member creates another owner.
    // Reference count becomes 2.
    node->next = node;

    // When main ends:
    // The local shared_ptr "node" is destroyed.
    // Reference count decreases from 2 to 1.
    //
    // The object is still alive because node->next
    // is holding another shared_ptr reference.
    //
    // Reference count never becomes 0,
    // so the destructor is never called.

    return 0;
}

Output
(no output)

Explanation

The object holds a shared_ptr to itself.

Reference count flow:

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
        |
        v
Object is never destroyed


This is called a circular reference and causes a memory leak.

Solution: Use weak_ptr

weak_ptr is a non-owning smart pointer.

It can point to an object managed by shared_ptr.
It does not increase the reference count.
It allows the object to be destroyed normally.
Example Using weak_ptr
#include <iostream>
#include <memory>
using namespace std;

class Node {
public:
    weak_ptr<Node> next;

    ~Node() {
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
    // The local shared_ptr "node" is destroyed.
    // Reference count becomes 0.
    //
    // Object is deleted and destructor is called.

    return 0;
}

Output
Node destroyed

shared_ptr vs weak_ptr
shared_ptr	weak_ptr
Owns the object	Does not own the object
Increases reference count	Does not increase reference count
Controls object lifetime	Only observes object
Can create circular references	Breaks circular references
Key Rule

Use:

shared_ptr → when you need shared ownership.
weak_ptr → when you only need to observe an object without owning it.

weak_ptr is commonly used to avoid circular references in relationships like parent-child objects, caches, and observer patterns.