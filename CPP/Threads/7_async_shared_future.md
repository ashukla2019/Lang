# C++11 Multithreading Interview Handbook
# Part 4B - std::async & std::shared_future

---

# Contents

1. Why std::async?
2. std::async()
3. How async Works
4. Launch Policies
5. launch::async
6. launch::deferred
7. async vs thread
8. async vs promise
9. std::shared_future
10. future vs shared_future
11. Best Practices
12. Common Mistakes
13. Interview Questions

---

# 1. Why std::async?

Suppose you want

- Create a thread
- Return a value
- Handle exceptions
- Join automatically

Using std::thread you need

```
thread

+

promise

+

future

+

join()
```

Too much work.

Instead

```
std::async()
```

does everything automatically.

---

# Traditional Approach

```
Main

↓

Create Thread

↓

Promise

↓

Future

↓

Join

↓

Result
```

---

# Using async

```
Main

↓

async()

↓

Result (future)

↓

get()
```

Much simpler.

---

# 2. std::async()

Header

```cpp
#include <future>
```

Syntax

```cpp
future<ReturnType> f =
    async(function,args...);
```

Example

```cpp
#include <iostream>
#include <future>

using namespace std;

int square(int x)
{
    return x*x;
}

int main()
{
    future<int> f =
        async(square,5);

    cout<<f.get();
}
```

Output

```
25
```

---

# What happened internally?

```
Main

↓

async()

↓

Create Worker Thread

↓

Run square()

↓

Store Result

↓

Shared State

↓

future.get()

↓

25
```

---

# async Internally

Interview Question

Does async use

```
thread

+

promise

+

future
```

Internally?

Conceptually

Yes.

It creates

```
Task

↓

Shared State

↓

Future
```

The exact implementation is library-dependent, but from a user's perspective it behaves like a higher-level abstraction over threads and futures.

---

# 3. Return Values

Example

```cpp
int add(int a,int b)
{
    return a+b;
}

future<int> f =
    async(add,10,20);

cout<<f.get();
```

Output

```
30
```

---

# Returning Objects

```cpp
string hello()
{
    return "Hello";
}

future<string> f =
    async(hello);

cout<<f.get();
```

Output

```
Hello
```

---

# Returning Containers

```cpp
vector<int> create()
{
    return {1,2,3};
}

future<vector<int>> f =
    async(create);

auto v = f.get();
```

Works perfectly.

---

# Exception Handling

Worker

```cpp
int divide()
{
    throw runtime_error("Divide Error");
}
```

Main

```cpp
future<int> f =
    async(divide);

try
{
    f.get();
}
catch(exception &e)
{
    cout<<e.what();
}
```

Output

```
Divide Error
```

No promise required.

---

# 4. Launch Policies

There are two launch policies.

```
launch::async
```

and

```
launch::deferred
```

---

# Default Policy

```cpp
async(function);
```

Actually means

```cpp
async(
launch::async |
launch::deferred,
function);
```

Compiler decides.

---

# 5. launch::async

Forces immediate execution.

Example

```cpp
future<int> f =
async(
launch::async,
square,
5);
```

Execution

```
Main

↓

Create Thread

↓

Run Immediately

↓

Result

↓

Future
```

---

# Example

```cpp
#include <iostream>
#include <future>

using namespace std;

int work()
{
    cout<<"Worker\n";

    return 100;
}

int main()
{
    future<int> f =
    async(
    launch::async,
    work);

    cout<<"Main\n";

    cout<<f.get();
}
```

Possible Output

```
Main

Worker

100
```

or

```
Worker

Main

100
```

Scheduling depends on OS.

---

# 6. launch::deferred

No thread created immediately.

Function runs only when

```
get()

or

wait()
```

is called.

Example

```cpp
future<int> f =
async(
launch::deferred,
square,
5);
```

Nothing executes yet.

Only

```cpp
f.get();
```

starts execution.

---

# Execution Flow

```
Main

↓

async()

↓

Task Stored

↓

No Thread Yet

↓

get()

↓

Execute Function

↓

Return Result
```

---

# Example

```cpp
int work()
{
    cout<<"Worker\n";

    return 50;
}

int main()
{
    auto f =
    async(
    launch::deferred,
    work);

    cout<<"Main\n";

    cout<<f.get();
}
```

Output

```
Main

Worker

50
```

Notice

Worker starts only at get().

---

# launch::async vs launch::deferred

| async | deferred |
|--------|----------|
| Creates thread immediately | Delays execution |
| Parallel execution | Same thread executes |
| Better responsiveness | Saves resources |
| Good for CPU work | Good for lazy evaluation |

---

# 7. async vs thread

| thread | async |
|----------|-------|
| Manual join | Automatic synchronization through future |
| No return value | Returns future |
| No exception propagation | Exceptions propagate via future |
| Lower level | Higher level |
| Need promise for results | Built-in support |

---

# Example

Using thread

```cpp
thread t(work);

t.join();
```

Using async

```cpp
future<int> f =
async(work);

cout<<f.get();
```

Much simpler.

---

# 8. async vs promise

Promise

```
Programmer

↓

Creates Promise

↓

Future

↓

Thread

↓

set_value()
```

async

```
async()

↓

Everything Automatic
```

---

# When to use Promise?

Need manual communication between threads.

---

# When to use async?

Need asynchronous execution with returned value.

---

# 9. std::shared_future

Problem with future

```
future.get()

↓

Only Once
```

Example

```cpp
future<int> f =
async(square,5);

cout<<f.get();

cout<<f.get();
```

Second get()

```
future_error
```

---

# Solution

```
shared_future
```

Allows multiple readers.

---

# Creating shared_future

```cpp
future<int> f =
async(square,5);

shared_future<int> sf =
f.share();
```

Now

```cpp
cout<<sf.get();

cout<<sf.get();

cout<<sf.get();
```

Output

```
25

25

25
```

Unlimited reads.

---

# Why?

shared_future shares ownership of the shared state.

Diagram

```
Shared State

↓

shared_future 1

↓

shared_future 2

↓

shared_future 3
```

All can read the same result.

---

# Example

```cpp
#include <iostream>
#include <future>

using namespace std;

int square(int x)
{
    return x*x;
}

int main()
{
    future<int> f =
        async(square,5);

    shared_future<int> sf =
        f.share();

    cout<<sf.get()<<endl;

    cout<<sf.get()<<endl;

    cout<<sf.get()<<endl;
}
```

Output

```
25

25

25
```

---

# future vs shared_future

| future | shared_future |
|----------|---------------|
| One reader | Multiple readers |
| get() once | get() many times |
| Move only | Copyable |
| Unique ownership | Shared ownership |

---

# Memory Diagram

future

```
Shared State

↓

future

↓

get()

↓

Destroyed
```

shared_future

```
Shared State

↓

shared_future

↓

shared_future

↓

shared_future

↓

All read same value
```

---

# Best Practices

Prefer

```
async()
```

over

```
thread

+

promise
```

when

- Return value needed
- Simple asynchronous task
- Exception handling required

---

Use

```
launch::async
```

when immediate execution is required.

---

Use

```
launch::deferred
```

for lazy evaluation.

---

Use

```
shared_future
```

when multiple threads need the same result.

---

# Common Mistakes

## Calling future.get() twice

Wrong

```cpp
f.get();

f.get();
```

---

## Forgetting launch policy

```cpp
async(work);
```

Execution policy is implementation-defined.

If you specifically need a new thread, use

```cpp
async(launch::async, work);
```

---

## Using shared_future unnecessarily

If only one reader exists,

```
future
```

is sufficient.

---

# Interview Questions

## Why async over thread?

Because async

- Returns values
- Propagates exceptions
- Simplifies thread management

---

## Difference between launch::async and launch::deferred?

```
async

↓

Runs immediately
```

```
deferred

↓

Runs only when get()/wait() is called
```

---

## Why shared_future?

Allows multiple threads to read the same result.

---

## Can shared_future call get() multiple times?

Yes.

Unlimited.

---

## Difference

future

↓

One consumer

shared_future

↓

Multiple consumers

---

# Interview Cheat Sheet

```
thread

↓

Low Level
```

```
promise

↓

Write Value
```

```
future

↓

Read Value Once
```

```
shared_future

↓

Read Value Multiple Times
```

```
async

↓

Automatic Thread + Future
```

---

# Summary

✔ std::async

✔ launch::async

✔ launch::deferred

✔ Automatic Future

✔ Exception Propagation

✔ async vs thread

✔ async vs promise

✔ std::shared_future

✔ future vs shared_future

✔ Best Practices

✔ Interview Questions
