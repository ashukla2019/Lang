C++ shared_ptr Circular Reference and weak_ptr Solution
Problem: Circular Reference Using shared_ptr

A shared_ptr keeps an object alive using a reference count.

When a shared_ptr is created, the reference count increases.
When a shared_ptr is destroyed, the reference count decreases.
The object is deleted only when the reference count becomes zero.

In the example below, an object stores a shared_ptr to itself. This creates a circular reference.

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

    // node reference count = 1
    // The object now stores another shared_ptr pointing to itself.
    // Reference count becomes 2.
    node->next = node;

    // When main ends, local shared_ptr "node" is destroyed.
    // Reference count decreases from 2 to 1.
    // It never becomes 0 because node->next is still holding the object.
    // Therefore destructor is never called.
    
    return 0;
}

Output
(no output)

Problem

The object is never released because the shared_ptr keeps itself alive.

This is called a circular reference (not a deadlock). It causes a memory leak.

Solution: Use weak_ptr

weak_ptr is a non-owning pointer.

It can observe an object managed by shared_ptr.
It does not increase the reference count.
It allows the object to be destroyed when no shared_ptr owns it.
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

    // node reference count = 1
    // weak_ptr stores the reference but does not increase count.
    node->next = node;

    // When main ends, local shared_ptr "node" is destroyed.
    // Reference count becomes 0.
    // Object is deleted and destructor is called.

    return 0;
}

Output
Node destroyed

Key Difference
shared_ptr	weak_ptr
Owns the object	Does not own the object
Increases reference count	Does not increase reference count
Can cause circular reference	Breaks circular reference
Object deleted when count reaches zero	Allows proper cleanup

Rule: Use shared_ptr for ownership and weak_ptr for observing an object without owning it.