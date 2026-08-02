# C++ Concurrency Cheat Sheet: `std::thread`, `std::future`, `std::promise`, `std::async`

## Decision Tree

```text
Need to run something concurrently?
        │
        ▼
Does the task return a value?
        │
   ┌────┴────┐
   │         │
  No        Yes
   │         │
std::thread  ▼
             Is it just a function call?
             │
        ┌────┴────┐
        │         │
       Yes       No
        │         │
 std::async    std::promise + std::future
```

---

# 1. std::thread

## When to use

- Run a task in another thread.
- No return value is needed.
- You manage the thread yourself.

### Example

```cpp
#include <iostream>
#include <thread>

void print()
{
    std::cout << "Hello from thread\n";
}

int main()
{
    std::thread t(print);

    t.join();
}
```

### Real-world example

- Logging
- Background cleanup
- Monitoring
- Sending heartbeat packets

---

# 2. std::future

## When to use

Whenever you need a value that will be available **later**.

A future **does not create a thread**.

It only waits for a result.

### Example

```cpp
std::future<int> f = std::async(square, 5);

int result = f.get();
```

Think of it as:

```text
Future = "I will receive the result later."
```

---

# 3. std::promise

## When to use

When **you** want to manually send a value from one thread to another.

One thread produces the result.

Another thread consumes it.

### Example

```cpp
#include <future>
#include <thread>
#include <iostream>

void worker(std::promise<int> p)
{
    p.set_value(50);
}

int main()
{
    std::promise<int> p;

    std::future<int> f = p.get_future();

    std::thread t(worker, std::move(p));

    std::cout << f.get();

    t.join();
}
```

Flow

```text
Worker Thread
      │
      ▼
promise.set_value(50)
      │
--------------------------
      │
future.get()
      │
Main Thread
```

### Real-world example

A worker thread computes:

- Image processing
- Sensor reading
- Database query

and sends the result back.

---

# 4. std::async

## When to use

When you simply want to execute a function asynchronously and receive its return value.

No need to create threads manually.

### Example

```cpp
#include <future>
#include <iostream>

int square(int x)
{
    return x * x;
}

int main()
{
    auto future = std::async(std::launch::async, square, 5);

    std::cout << future.get();
}
```

### Real-world example

- Download a file
- Read a large CSV
- Calculate statistics
- Compress a file

while the main thread continues working.

---

# Which one should I use?

## Scenario 1

"I just want another thread."

Use

```cpp
std::thread
```

---

## Scenario 2

"I want another thread that returns a value."

Use

```cpp
std::async
```

---

## Scenario 3

"I already have a thread and want to manually send a result."

Use

```cpp
std::promise
+
std::future
```

---

## Scenario 4

"I only need to wait for a result."

Use

```cpp
std::future
```

---

# Relationship

```text
              std::async
                   │
          creates internally
                   │
             std::future
```

```text
std::promise
      │
sets value
      ▼
std::future
```

```text
std::thread
      │
runs function
      ▼
No return value
```

---

# Comparison Table

| Feature | std::thread | std::future | std::promise | std::async |
|----------|------------|-------------|--------------|------------|
| Creates thread | ✅ | ❌ | ❌ | ✅ (or deferred) |
| Returns value | ❌ | ✅ | ✅ (via future) | ✅ |
| Manual synchronization | Yes | No | Yes | No |
| Easy to use | Medium | Easy | Medium | Very Easy |
| Best for | Fire-and-forget work | Waiting for result | Thread communication | Asynchronous function calls |

---

# Interview Examples

## Use std::thread

```text
Run a logger continuously.
```

---

## Use std::async

```text
Download a file while UI remains responsive.
```

---

## Use std::promise + future

```text
Worker thread computes an image and sends it back to the main thread.
```

---

## Use future

```text
Wait until the worker finishes computation.
```

---

# Important Notes

## `std::future`

- Can call `get()` only once.
- `get()` blocks until the value is ready.

---

## `std::promise`

- Calls `set_value()`.
- Can also call `set_exception()`.

---

## `std::async`

Returns a future automatically.

Internally, it behaves roughly like:

```text
Create Thread
        +
Create Promise
        +
Return Future
```

This is why **you usually do not combine `std::async` with `std::promise`**—`std::async` already handles the promise/future mechanism for you.

---

# One-line Summary

| Requirement | Use |
|------------|-----|
| Run code concurrently, no result | `std::thread` |
| Run code concurrently and get a result | `std::async` |
| Manually pass a result between threads | `std::promise` + `std::future` |
| Wait for a result produced elsewhere | `std::future` |
