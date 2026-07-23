# C++11 Multithreading Interview Handbook
# Part 4A-2 - std::promise

---

# Contents

1. What is std::promise?
2. Why do we need promise?
3. Promise + Future Relationship
4. Shared State
5. set_value()
6. Returning Values from Threads
7. Passing Promise to Thread
8. set_exception()
9. Complete Examples
10. Promise vs Future
11. Interview Questions

---

# 1. What is std::promise?

A **std::promise** is an object used by one thread to **send a value or an exception** to another thread.

Think of it as a **writer**.

```
Producer Thread

↓

Promise

↓

Shared State

↓

Future

↓

Consumer Thread
```

Promise **writes**.

Future **reads**.

---

# Think of it Like a Courier

Suppose you want to send a package.

```
Sender

↓

Courier Office

↓

Receiver
```

Here

```
Sender

↓

Promise
```

```
Courier Office

↓

Shared State
```

```
Receiver

↓

Future
```

Promise puts the value into the shared state.

Future later retrieves it.

---

# 2. Why do we need Promise?

Suppose a worker thread computes

```
100
```

How can it send this value back?

Without promise

```
Worker Thread

↓

100

↓

Lost
```

With promise

```
Worker

↓

Promise

↓

Shared State

↓

Future

↓

Main Thread
```

---

# 3. Promise + Future Relationship

A promise and future always work together.

```
Promise

↓

set_value()

↓

Shared State

↓

future.get()
```

One promise

↓

One future

---

# Creating Them

```cpp
promise<int> p;

future<int> f = p.get_future();
```

Explanation

```
Promise

↓

Create Shared State

↓

Future connected
```

Now both communicate through the same shared state.

---

# 4. Shared State

Interview Question

Where is the result stored?

Answer

Inside the **Shared State**.

```
Promise

↓

Shared State

↓

Future
```

Promise stores the value here.

Future reads the value from here.

Neither stores it internally.

---

# 5. set_value()

Used by the producer thread.

Syntax

```cpp
p.set_value(value);
```

Example

```cpp
#include <iostream>
#include <future>

using namespace std;

int main()
{
    promise<int> p;

    future<int> f = p.get_future();

    p.set_value(100);

    cout << f.get() << endl;
}
```

Output

```
100
```

Flow

```
Promise

↓

set_value(100)

↓

Shared State

↓

Future

↓

get()

↓

100
```

---

# 6. Returning Value from Thread

This is the most common interview example.

```cpp
#include <iostream>
#include <thread>
#include <future>

using namespace std;

void square(promise<int> p, int x)
{
    p.set_value(x * x);
}

int main()
{
    promise<int> p;

    future<int> f = p.get_future();

    thread t(square, move(p), 5);

    cout << f.get() << endl;

    t.join();
}
```

Output

```
25
```

Execution Flow

```
Main

↓

Promise

↓

Future

↓

Create Thread

↓

Thread computes

↓

25

↓

set_value()

↓

Shared State

↓

future.get()

↓

25
```

---

# Why std::move(p)?

Question

Why not

```cpp
thread t(square, p, 5);
```

Answer

Because

```
std::promise

↓

Non-copyable
```

Promise owns the shared state.

Two promises cannot own the same shared state.

Therefore

```
Copy

↓

Not Allowed
```

Instead

```
Move Ownership

↓

std::move()
```

---

# Memory Diagram

Before move

```
Main

Promise

↓

Shared State

↓

Future
```

After

```cpp
std::move(p)
```

```
Main Promise

↓

Empty
```

```
Thread Promise

↓

Shared State

↓

Future
```

Ownership transferred.

---

# 7. Passing Promise by Reference

Another valid approach.

```cpp
void work(promise<int>& p)
{
    p.set_value(500);
}

int main()
{
    promise<int> p;

    future<int> f = p.get_future();

    thread t(work, ref(p));

    cout << f.get();

    t.join();
}
```

Output

```
500
```

This avoids moving the promise.

---

# 8. set_exception()

Suppose worker throws an exception.

Without promise

```
Worker

↓

Exception

↓

Program terminates
```

With promise

```
Worker

↓

Catch Exception

↓

set_exception()

↓

Shared State

↓

Future

↓

Main catches
```

---

# Example

```cpp
#include <iostream>
#include <thread>
#include <future>

using namespace std;

void work(promise<int> p)
{
    try
    {
        throw runtime_error("Calculation Failed");
    }
    catch(...)
    {
        p.set_exception(current_exception());
    }
}

int main()
{
    promise<int> p;

    future<int> f = p.get_future();

    thread t(work, move(p));

    try
    {
        cout << f.get();
    }
    catch(const exception& e)
    {
        cout << e.what() << endl;
    }

    t.join();
}
```

Output

```
Calculation Failed
```

---

# How Exception Travels

```
Worker

↓

throw

↓

catch(...)

↓

set_exception()

↓

Shared State

↓

future.get()

↓

throw again

↓

Main catches
```

---

# What if set_value() is Never Called?

Suppose

```cpp
promise<int> p;

future<int> f = p.get_future();
```

Thread exits without

```cpp
set_value();
```

Then

```cpp
f.get();
```

throws

```
std::future_error
```

Reason

No value was placed in the shared state.

---

# Complete Example

```cpp
#include <iostream>
#include <thread>
#include <future>

using namespace std;

void calculate(promise<int> p)
{
    int result = 10 * 20;

    p.set_value(result);
}

int main()
{
    promise<int> p;

    future<int> f = p.get_future();

    thread worker(calculate, move(p));

    cout << "Waiting...\n";

    cout << "Answer = "
         << f.get()
         << endl;

    worker.join();
}
```

Output

```
Waiting...

Answer = 200
```

---

# Promise vs Future

| Promise | Future |
|----------|--------|
| Produces value | Consumes value |
| Calls set_value() | Calls get() |
| Calls set_exception() | Receives exception |
| Writer | Reader |

Think of them as

```
Promise

↓

Write
```

```
Future

↓

Read
```

---

# Common Mistakes

## Forgetting get_future()

Wrong

```cpp
promise<int> p;

p.set_value(10);
```

No future exists to receive the value.

---

## Calling set_value() Twice

Wrong

```cpp
p.set_value(10);

p.set_value(20);
```

Throws

```
future_error
```

Only one result can be stored.

---

## Forgetting std::move()

Wrong

```cpp
thread t(work, p);
```

Compilation error.

Correct

```cpp
thread t(work, move(p));
```

---

## Calling get() Before Thread Finishes

This is actually safe.

```cpp
f.get();
```

automatically waits until

```
set_value()
```

is called.

---

# Interview Questions

## Difference between Promise and Future?

Promise writes.

Future reads.

---

## Why is promise non-copyable?

Because it owns the shared state.

Ownership cannot be duplicated.

---

## Why use std::move() with promise?

To transfer ownership of the promise to another thread.

---

## What happens if set_value() is never called?

`future.get()` throws `std::future_error`.

---

## Can promise send exceptions?

Yes.

Using

```cpp
set_exception(current_exception());
```

---

## Can one promise have multiple futures?

No.

One promise creates exactly one future.

(If multiple readers are needed, use `std::shared_future`, covered later.)

---

# Summary

✔ std::promise

✔ Promise + Future

✔ Shared State

✔ set_value()

✔ Returning Values from Threads

✔ Passing Promise using std::move()

✔ Passing Promise by Reference

✔ set_exception()

✔ Exception Propagation

✔ Promise vs Future

✔ Interview Questions
