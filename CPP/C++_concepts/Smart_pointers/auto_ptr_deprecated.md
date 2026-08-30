## The Main Problem: Copying Transfers Ownership

Consider:

```cpp
std::auto_ptr<int> p1(new int(10));

std::auto_ptr<int> p2 = p1;

With normal C++ objects, you expect:

p1 ──> object
p2 ──> object

But auto_ptr has unusual behavior.

Before Copying
p1 ──> 10
p2 ──> nothing

After Copying
p1 ──> nothing
p2 ──> 10
