# C++11 Multithreading Interview Handbook
# Part 3A - Condition Variable (wait, notify_one, notify_all)

---

# Contents

1. Why Condition Variable?
2. Busy Waiting Problem
3. What is a Condition Variable?
4. Components Required
5. wait()
6. notify_one()
7. notify_all()
8. Predicate Version of wait()
9. Spurious Wakeups
10. Simple Producer-Consumer Example
11. Interview Questions

---

# 1. Why do we need Condition Variables?

Suppose one thread produces data.

Another thread consumes data.

Example

```
Producer

↓

Push Data

↓

Queue
```

```
Consumer

↓

Read Queue

↓

Process Data
```

Question

What should the consumer do when the queue is empty?

Option 1

Keep checking continuously.

```
while(queue.empty())
{
}
```

Problem

```
CPU = 100%
```

Consumer wastes CPU time doing nothing.

This is called **Busy Waiting**.

---

# 2. Busy Waiting

Example

```cpp
while(queue.empty())
{
    // Keep checking
}
```

Flow

```
Queue Empty

↓

Consumer checks

↓

Still Empty

↓

Checks again

↓

Checks again

↓

Checks again

↓

CPU keeps running
```

This wastes CPU cycles.

---

# Better Solution

Consumer should

```
Sleep

↓

Wake only when Producer inserts data
```

This is exactly what **condition_variable** does.

---

# 3. What is std::condition_variable?

A condition variable allows one thread to **wait** until another thread notifies it.

Think of it as a **doorbell**.

```
Consumer

↓

Sleeping

↓

Producer rings bell

↓

Consumer wakes
```

Header

```cpp
#include <condition_variable>
```

---

# Components Required

A condition variable always works with

```
mutex

+

unique_lock

+

condition_variable
```

Why not lock_guard?

Because `wait()` temporarily unlocks and relocks the mutex.

Only `unique_lock` supports that.

---

# Required Objects

```cpp
mutex m;

condition_variable cv;
```

---

# 4. wait()

Syntax

```cpp
cv.wait(lock);
```

This does **three things** automatically.

```
1. Unlock mutex

↓

2. Sleep

↓

3. Wake up

↓

4. Lock mutex again
```

This is the most important interview point.

---

# Why unlock the mutex?

Suppose Consumer holds the mutex while sleeping.

```
Consumer

↓

Lock mutex

↓

Sleep
```

Producer now wants to push data.

```
Producer

↓

Needs mutex

↓

Blocked
```

Producer cannot insert data.

Consumer waits forever.

Deadlock.

So `wait()` automatically unlocks the mutex before sleeping.

---

# Execution Flow

Consumer

```
Lock mutex

↓

Queue Empty

↓

wait()

↓

Unlock mutex

↓

Sleep
```

Producer

```
Lock mutex

↓

Push Data

↓

Unlock mutex

↓

notify_one()
```

Consumer

```
Wake

↓

Lock mutex again

↓

Continue
```

---

# Example

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;

condition_variable cv;

bool ready = false;

void consumer()
{
    unique_lock<mutex> lock(m);

    cv.wait(lock);

    cout << "Consumer Received Signal\n";
}

void producer()
{
    {
        lock_guard<mutex> lock(m);

        ready = true;
    }

    cv.notify_one();
}

int main()
{
    thread t1(consumer);

    thread t2(producer);

    t1.join();

    t2.join();
}
```

Output

```
Consumer Received Signal
```

---

# What happens internally?

Consumer

```
Lock

↓

wait()

↓

Unlock

↓

Sleep
```

Producer

```
Lock

↓

ready=true

↓

Unlock

↓

notify_one()
```

Consumer

```
Wake

↓

Lock Again

↓

Continue
```

---

# 5. notify_one()

Wakes exactly one waiting thread.

Example

Suppose

```
Consumer 1

Waiting
```

```
Consumer 2

Waiting
```

```
Consumer 3

Waiting
```

Producer

```
notify_one()
```

Only one wakes.

```
Consumer 2

Running
```

Others continue sleeping.

---

# notify_all()

Wakes every waiting thread.

```
Consumer 1

Wake
```

```
Consumer 2

Wake
```

```
Consumer 3

Wake
```

Every waiting thread becomes runnable.

---

# When should we use notify_one()?

When only one thread should process one resource.

Example

```
Queue

↓

One Item

↓

One Consumer
```

notify_one()

---

# When should we use notify_all()?

When all threads should wake.

Example

```
Shutdown Signal

↓

Wake everyone
```

---

# 6. Predicate Version of wait()

Instead of

```cpp
cv.wait(lock);
```

use

```cpp
cv.wait(lock, []{
    return ready;
});
```

This is the recommended approach.

---

# Why?

Suppose Producer calls

```
notify_one()
```

before Consumer starts waiting.

Consumer later executes

```
wait()
```

No notification exists anymore.

Consumer sleeps forever.

Predicate prevents this.

---

# Predicate Example

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;

condition_variable cv;

bool ready = false;

void consumer()
{
    unique_lock<mutex> lock(m);

    cv.wait(lock, []{
        return ready;
    });

    cout<<"Consumer Started\n";
}

void producer()
{
    {
        lock_guard<mutex> lock(m);

        ready = true;
    }

    cv.notify_one();
}

int main()
{
    thread t1(consumer);

    thread t2(producer);

    t1.join();

    t2.join();
}
```

---

# What is the Predicate Doing?

Equivalent to

```cpp
while(!ready)
{
    cv.wait(lock);
}
```

The library repeatedly checks

```
ready ?

↓

No

↓

Sleep

↓

Wake

↓

Check Again

↓

Yes

↓

Continue
```

---

# 7. Spurious Wakeup

Interview favorite.

A thread may wake **without any notify()**.

Yes, it can happen.

Reason

Operating system or implementation.

Therefore

Never write

```cpp
cv.wait(lock);
```

Instead

```cpp
cv.wait(lock, []{
    return ready;
});
```

or

```cpp
while(!ready)
{
    cv.wait(lock);
}
```

Always recheck the condition.

---

# Wrong

```cpp
cv.wait(lock);

processData();
```

Consumer may wake accidentally.

Queue may still be empty.

---

# Correct

```cpp
cv.wait(lock, []{
    return !queue.empty();
});
```

or

```cpp
while(queue.empty())
{
    cv.wait(lock);
}
```

---

# 8. Simple Producer-Consumer

```cpp
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<int> q;

mutex m;

condition_variable cv;

void producer()
{
    {
        lock_guard<mutex> lock(m);

        q.push(10);

        cout<<"Produced 10\n";
    }

    cv.notify_one();
}

void consumer()
{
    unique_lock<mutex> lock(m);

    cv.wait(lock, []{
        return !q.empty();
    });

    cout<<"Consumed "<<q.front()<<endl;

    q.pop();
}

int main()
{
    thread t1(producer);

    thread t2(consumer);

    t1.join();

    t2.join();
}
```

Possible Output

```
Produced 10

Consumed 10
```

---

# Execution Flow

```
Consumer

↓

Queue Empty

↓

wait()

↓

Sleep
```

Producer

```
Push 10

↓

notify_one()
```

Consumer

```
Wake

↓

Queue Not Empty

↓

Pop

↓

Done
```

---

# Interview Questions

## Why not use Busy Waiting?

Because it wastes CPU.

---

## Why is unique_lock required?

Because wait()

```
Unlocks mutex

↓

Sleeps

↓

Locks mutex again
```

lock_guard cannot unlock and relock.

---

## Difference between notify_one() and notify_all()

notify_one()

```
Wake one thread
```

notify_all()

```
Wake all waiting threads
```

---

## Why use Predicate?

To protect against

- missed notifications
- spurious wakeups

---

## What happens inside wait()?

```
Lock

↓

Unlock

↓

Sleep

↓

Wake

↓

Lock Again

↓

Return
```

This automatic unlock/relock behavior is why `std::unique_lock` is mandatory.

---

# Summary

✔ Busy Waiting

✔ Condition Variable

✔ wait()

✔ notify_one()

✔ notify_all()

✔ Predicate Version

✔ Spurious Wakeups

✔ Basic Producer-Consumer

✔ Interview Questions
