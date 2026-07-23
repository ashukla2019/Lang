# C++11 Multithreading Interview Handbook
# Part 3B - Producer Consumer & Thread Safe Queue

---

# Contents

1. Producer Consumer Problem
2. Thread Safe Queue
3. Multiple Producers & Consumers
4. wait_for()
5. wait_until()
6. Complete Example
7. Best Practices
8. Common Mistakes
9. Interview Questions

---

# 1. Producer Consumer Problem

Suppose we have

```
Producer

↓

Queue

↓

Consumer
```

Producer

- Creates data
- Pushes into queue

Consumer

- Waits for data
- Removes data
- Processes data

---

# Why Queue?

Producer and Consumer usually run at different speeds.

Example

```
Producer

1 ms
```

Consumer

```
5 ms
```

Queue stores temporary data.

```
Producer

↓

Queue

↓

Consumer
```

---

# Components Required

```
queue

+

mutex

+

condition_variable
```

---

# 2. Thread Safe Queue

A thread-safe queue protects shared data using mutex and condition_variable.

Example class

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template<typename T>
class ThreadSafeQueue
{
private:

    queue<T> q;

    mutex m;

    condition_variable cv;

public:

    void push(T value)
    {
        {
            lock_guard<mutex> lock(m);

            q.push(value);
        }

        cv.notify_one();
    }

    T pop()
    {
        unique_lock<mutex> lock(m);

        cv.wait(lock,[this]
        {
            return !q.empty();
        });

        T value = q.front();

        q.pop();

        return value;
    }
};
```

---

# Why notify_one() outside the lock?

Notice

```cpp
{
    lock_guard<mutex> lock(m);

    q.push(value);
}

cv.notify_one();
```

Why?

Because

```
Push data

↓

Unlock mutex

↓

Wake consumer
```

Consumer can immediately acquire mutex.

If notify is inside lock

```
Push

↓

Notify

↓

Consumer wakes

↓

Still waiting for mutex
```

Works, but causes unnecessary contention.

Best practice:

```
Unlock first

↓

Notify later
```

---

# Using ThreadSafeQueue

```cpp
ThreadSafeQueue<int> q;
```

Producer

```cpp
q.push(100);
```

Consumer

```cpp
int value = q.pop();
```

Very simple.

---

# 3. Multiple Producers and Consumers

Example

```
Producer 1

↓

Queue
```

```
Producer 2

↓

Queue
```

```
Consumer 1
```

```
Consumer 2
```

All share

```
Mutex

+

Condition Variable
```

Only one thread modifies queue at a time.

---

# Example

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

void producer(int id)
{
    for(int i=1;i<=5;i++)
    {
        {
            lock_guard<mutex> lock(m);

            q.push(i);

            cout<<"Producer "<<id
                <<" produced "<<i<<endl;
        }

        cv.notify_one();
    }
}

void consumer(int id)
{
    for(int i=1;i<=5;i++)
    {
        unique_lock<mutex> lock(m);

        cv.wait(lock,[]
        {
            return !q.empty();
        });

        cout<<"Consumer "<<id
            <<" consumed "
            <<q.front()<<endl;

        q.pop();
    }
}

int main()
{
    thread p1(producer,1);

    thread p2(producer,2);

    thread c1(consumer,1);

    thread c2(consumer,2);

    p1.join();

    p2.join();

    c1.join();

    c2.join();
}
```

Output

Order is unpredictable.

Possible

```
Producer 1 produced 1

Producer 2 produced 1

Consumer 1 consumed 1

Consumer 2 consumed 1
```

Scheduling depends on OS.

---

# Execution Flow

```
Producer 1

↓

Push

↓

Notify
```

```
Producer 2

↓

Push

↓

Notify
```

```
Consumer

↓

Wake

↓

Pop

↓

Sleep Again
```

---

# 4. wait_for()

Waits only for a limited time.

Syntax

```cpp
cv.wait_for(lock,
            chrono::seconds(5),
            predicate);
```

Example

```cpp
if(cv.wait_for(lock,
               chrono::seconds(5),
               []{
                   return ready;
               }))
{
    cout<<"Received\n";
}
else
{
    cout<<"Timeout\n";
}
```

If Producer never sends data

```
5 seconds

↓

Timeout
```

Useful in

- Network programming
- Servers
- Device Drivers
- Embedded Systems

---

# wait_until()

Wait until a specific time.

Example

```cpp
auto timeout =
chrono::steady_clock::now()
+
chrono::seconds(5);

cv.wait_until(lock,
              timeout,
              []{
                  return ready;
              });
```

Difference

```
wait_for()

↓

Relative Time
```

```
wait_until()

↓

Absolute Time
```

---

# Complete Producer Consumer

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

bool finished=false;

void producer()
{
    for(int i=1;i<=5;i++)
    {
        {
            lock_guard<mutex> lock(m);

            q.push(i);

            cout<<"Produced "<<i<<endl;
        }

        cv.notify_one();
    }

    {
        lock_guard<mutex> lock(m);

        finished=true;
    }

    cv.notify_all();
}

void consumer()
{
    while(true)
    {
        unique_lock<mutex> lock(m);

        cv.wait(lock,[]
        {
            return !q.empty()
                || finished;
        });

        while(!q.empty())
        {
            cout<<"Consumed "
                <<q.front()<<endl;

            q.pop();
        }

        if(finished)
            break;
    }
}

int main()
{
    thread p(producer);

    thread c(consumer);

    p.join();

    c.join();
}
```

Output

```
Produced 1

Consumed 1

Produced 2

Consumed 2

...
```

---

# Why finished flag?

Suppose Producer exits.

Queue becomes empty.

Consumer executes

```
wait()
```

No Producer exists.

Consumer waits forever.

```
Deadlock
```

So Producer sets

```cpp
finished=true;
```

Consumer checks

```cpp
finished
```

and exits safely.

---

# Best Practices

Always

```
wait(lock,predicate)
```

Never

```
wait(lock)
```

Always

```
unlock

↓

notify
```

Keep critical sections small.

Never perform long computations while holding mutex.

---

# Common Mistakes

## Busy Waiting

Wrong

```cpp
while(queue.empty())
{
}
```

---

## Forgetting Predicate

Wrong

```cpp
cv.wait(lock);
```

Correct

```cpp
cv.wait(lock,[]
{
    return !queue.empty();
});
```

---

## Forgetting notify()

Producer pushes

```
Queue

↓

No notify
```

Consumer sleeps forever.

---

## Holding Lock Too Long

Wrong

```cpp
lock();

processHugeFile();

unlock();
```

Other threads wait unnecessarily.

---

# Interview Questions

## Why unique_lock instead of lock_guard?

Because

```
wait()

↓

Unlocks mutex

↓

Sleeps

↓

Locks mutex again
```

Only unique_lock supports this.

---

## Why notify outside lock?

To reduce contention.

Consumer can immediately acquire mutex.

---

## Why use predicate?

Protects against

- Spurious wakeups
- Missed notifications

---

## Difference

wait_for()

```
Relative timeout
```

wait_until()

```
Absolute timeout
```

---

## What happens if Producer exits first?

Use

```
finished flag
```

Otherwise Consumer waits forever.

---

# Real World Uses

Condition Variables are used in

- Thread Pools
- Database Servers
- Web Servers
- Task Queues
- Job Scheduling
- Logging Systems
- Network Servers
- Message Queues
- Operating Systems
- Device Drivers

---

# Summary

✔ Producer Consumer

✔ Thread Safe Queue

✔ Multiple Producers

✔ Multiple Consumers

✔ wait_for()

✔ wait_until()

✔ finished Flag

✔ Best Practices

✔ Common Mistakes

✔ Interview Questions
