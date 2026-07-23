# C++11 Multithreading Interview Handbook
# Part 4A-1 - std::future

---

# Contents

1. Why Threads Cannot Return Values
2. What is std::future?
3. Shared State
4. future::get()
5. future::wait()
6. future::wait_for()
7. future::valid()
8. Complete Examples
9. Execution Flow
10. Interview Questions

---

# 1. Why can't std::thread return a value?

Suppose you write

```cpp
int add(int a, int b)
{
    return a + b;
}

int main()
{
    std::thread t(add, 10, 20);
}
```

Question

Where does

```
30
```

go?

Answer

Nowhere.

A thread starts independently.

The return value is discarded.

Unlike

```cpp
int ans = add(10,20);
```

there is no variable waiting to receive the result.

Therefore

```
std::thread

↓

Cannot directly return values.
```

---

# Solution

Use

```
promise

+

future
```

or

```
async
```

These provide a communication channel between threads.

---

# 2. What is std::future?

A **future** is an object that represents a value that will become available later.

Think of it as a **placeholder**.

```
Main Thread

↓

future

↓

Waiting...
```

Worker Thread

```
Computing...

↓

Result Ready

↓

future receives value
```

---

# Real World Analogy

Suppose you order food.

Restaurant

```
Cooking

↓

Preparing

↓

Packing
```

You receive

```
Token Number
```

You don't get food immediately.

You wait.

Later

```
Token

↓

Food Ready
```

Future works exactly the same way.

Future = Token.

---

# Header Files

```cpp
#include <future>
#include <thread>
```

---

# 3. Shared State

Interview Question

Where does the result live?

Answer

Between promise and future there exists an internal object called the

```
Shared State
```

Diagram

```
Worker Thread

↓

Promise

↓

Shared State

↓

Future

↓

Main Thread
```

Future does NOT store the value.

Promise does NOT store the value.

Both communicate through the Shared State.

---

# 4. future::get()

Most important function.

Syntax

```cpp
future.get();
```

Meaning

```
Wait until result is ready

↓

Return value

↓

Future becomes empty
```

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

    cout<<f.get()<<endl;
}
```

Output

```
25
```

Flow

```
Main

↓

future

↓

Worker computes

↓

25

↓

get()

↓

25 returned
```

---

# Important Rule

get()

can be called

```
Only Once
```

Example

```cpp
cout<<f.get();

cout<<f.get();
```

Second call

```
Throws exception

future_error
```

Reason

After get()

Future no longer owns the result.

---

# Why only once?

Imagine

```
Result = 100
```

Future

```
↓

get()

↓

Take ownership

↓

Shared State becomes empty
```

Nothing remains.

Hence

```
Second get()

↓

Error
```

---

# 5. future::wait()

Sometimes

You don't need the result immediately.

You only want to know

```
Has thread finished?
```

Use

```cpp
future.wait();
```

Example

```cpp
#include <iostream>
#include <future>

using namespace std;

int work()
{
    return 100;
}

int main()
{
    future<int> f =
        async(work);

    cout<<"Waiting...\n";

    f.wait();

    cout<<"Done\n";

    cout<<f.get()<<endl;
}
```

Output

```
Waiting...

Done

100
```

---

# Difference

wait()

```
Wait

↓

No value returned
```

get()

```
Wait

↓

Return value
```

---

# Execution Flow

```
Main

↓

wait()

↓

Worker Running

↓

Finished

↓

wait() returns

↓

get()

↓

Value
```

---

# 6. future::wait_for()

Wait only for a limited time.

Syntax

```cpp
future.wait_for(
chrono::seconds(2));
```

Example

```cpp
#include <iostream>
#include <future>
#include <chrono>

using namespace std;

int work()
{
    this_thread::sleep_for(
        chrono::seconds(5));

    return 10;
}

int main()
{
    future<int> f =
        async(work);

    auto status =
        f.wait_for(
        chrono::seconds(2));

    if(status==
        future_status::timeout)
    {
        cout<<"Timeout\n";
    }
}
```

Output

```
Timeout
```

Worker still continues.

---

# Possible Status Values

```
future_status::ready
```

Result available.

---

```
future_status::timeout
```

Still running.

---

```
future_status::deferred
```

Task has not started yet.

(Used with launch::deferred)

---

# wait_for() Flow

```
Main

↓

wait_for(2 sec)

↓

Worker Running

↓

2 sec expired

↓

Timeout
```

Worker continues independently.

---

# 7. future::valid()

Checks whether future still owns a result.

Example

```cpp
future<int> f =
    async(square,5);

cout<<f.valid()<<endl;
```

Output

```
1
```

After

```cpp
f.get();
```

Now

```cpp
cout<<f.valid();
```

Output

```
0
```

Reason

Result already consumed.

---

# Example

```cpp
future<int> f =
    async(square,5);

cout<<f.valid()<<endl;

f.get();

cout<<f.valid()<<endl;
```

Output

```
1

0
```

---

# Complete Example

```cpp
#include <iostream>
#include <future>
#include <thread>

using namespace std;

int calculate()
{
    cout<<"Worker Started\n";

    this_thread::sleep_for(
        chrono::seconds(2));

    cout<<"Worker Finished\n";

    return 500;
}

int main()
{
    future<int> f =
        async(calculate);

    cout<<"Main Waiting\n";

    f.wait();

    cout<<"Result = "
        <<f.get()<<endl;
}
```

Output

```
Main Waiting

Worker Started

Worker Finished

Result = 500
```

---

# Complete Execution Flow

```
Main Thread

↓

async()

↓

Worker Thread Starts

↓

future returned

↓

wait()

↓

Worker computes

↓

Stores result

↓

Shared State

↓

wait() returns

↓

get()

↓

500
```

---

# wait() vs get()

| wait() | get() |
|---------|--------|
| Waits | Waits |
| Doesn't return value | Returns value |
| Future remains valid | Future becomes invalid |
| Can call multiple times | Only once |

---

# valid()

| Before get() | true |
|--------------|------|
| After get() | false |

---

# Common Mistakes

## Calling get() Twice

Wrong

```cpp
cout<<f.get();

cout<<f.get();
```

Reason

Future owns result only once.

---

## Forgetting get()

Suppose

```cpp
future<int> f =
    async(square,5);
```

Never calling

```
get()
```

means

Result is never retrieved.

---

## Confusing wait() with get()

```
wait()

↓

Synchronization
```

```
get()

↓

Synchronization

+

Retrieve Result
```

---

# Interview Questions

## Why can't std::thread return values?

Because std::thread has no mechanism to transfer a return value back to the creator.

---

## What is std::future?

A placeholder for a value that will be available later.

---

## Why can get() be called only once?

Because it transfers ownership of the stored result from the shared state.

---

## Difference between wait() and get()?

```
wait()

↓

Blocks

↓

No value
```

```
get()

↓

Blocks

↓

Returns value
```

---

## Why use wait_for()?

To avoid blocking forever by specifying a timeout.

---

# Summary

✔ Why std::thread cannot return values

✔ std::future

✔ Shared State

✔ future::get()

✔ future::wait()

✔ future::wait_for()

✔ future::valid()

✔ Complete Examples

✔ Execution Flow

✔ Interview Questions
