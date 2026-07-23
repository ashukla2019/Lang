# C++11 Multithreading Interview Handbook
# Part 1 - Thread Basics

---

# Contents

1. Introduction
2. Process vs Thread
3. Why Multithreading?
4. Thread Life Cycle
5. Creating a Thread
6. join()
7. detach()
8. joinable()
9. Passing Arguments
10. Passing Arguments by Reference
11. Lambda Thread
12. Member Function Thread
13. Multiple Threads
14. Thread ID
15. hardware_concurrency()
16. Interview Questions

---

# 1. What is a Thread?

A **thread** is the smallest unit of execution inside a process.

A process can contain one or more threads.

Example:

```
Google Chrome Process

│
├── UI Thread
├── Network Thread
├── Rendering Thread
├── JavaScript Thread
└── Audio Thread
```

All these threads belong to the same process.

---

# 2. Process vs Thread

| Process | Thread |
|----------|---------|
| Independent program | Smallest execution unit |
| Has separate memory | Shares process memory |
| Heavyweight | Lightweight |
| Process creation is slow | Thread creation is faster |
| Communication via IPC | Communication via shared memory |

Memory Layout

```
Process

+----------------------+
| Code                 |
+----------------------+
| Global Variables     |
+----------------------+
| Heap                 |
+----------------------+

        Shared

+----------------------+
| Thread 1 Stack       |
+----------------------+

+----------------------+
| Thread 2 Stack       |
+----------------------+

+----------------------+
| Thread 3 Stack       |
+----------------------+
```

Shared by all threads

- Code
- Global variables
- Heap

Private to each thread

- Stack
- Registers
- Program Counter

---

# 3. Why Multithreading?

Without threads

```
Download File

↓

Read Disk

↓

Update UI

↓

Play Music
```

Everything executes one after another.

With threads

```
Download Thread

UI Thread

Audio Thread

Disk Thread
```

Everything can execute simultaneously.

Advantages

- Better CPU utilization
- Better responsiveness
- Parallel execution
- Faster applications

---

# 4. Thread Life Cycle

```
Created

↓

Runnable

↓

Running

↓

Blocked / Waiting

↓

Running

↓

Finished
```

---

# Header Files

```cpp
#include <thread>
#include <iostream>

using namespace std;
```

---

# 5. Creating First Thread

```cpp
#include <iostream>
#include <thread>

using namespace std;

void display()
{
    cout << "Child Thread\n";
}

int main()
{
    thread t(display);

    t.join();

    cout << "Main Thread\n";
}
```

Output

```
Child Thread
Main Thread
```

Explanation

```
Main Thread

↓

Create thread

↓

Child starts

↓

join()

↓

Wait

↓

Child finishes

↓

Main continues
```

---

# 6. Why join()?

join()

means

```
Main thread waits until child thread finishes.
```

Example

```cpp
#include <iostream>
#include <thread>

using namespace std;

void work()
{
    cout << "Working...\n";
}

int main()
{
    thread t(work);

    t.join();

    cout << "Finished\n";
}
```

Output

```
Working...
Finished
```

---

Without join()

```cpp
thread t(work);
```

Program terminates with

```
std::terminate()
```

because

```
Thread object destroyed

↓

Still running

↓

Program aborts
```

Interview Question

Why must we call join()?

Answer

Because every std::thread must either

- join()
- detach()

before destruction.

Otherwise std::terminate() is called.

---

# 7. detach()

detach()

means

```
Run independently.
```

Main thread does NOT wait.

Example

```cpp
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void work()
{
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Child Thread\n";
}

int main()
{
    thread t(work);

    t.detach();

    cout << "Main Finished\n";
}
```

Possible Output

```
Main Finished
```

or

```
Main Finished
Child Thread
```

Reason

Detached threads execute independently.

Main thread may exit before child finishes.

---

# join() vs detach()

| join() | detach() |
|---------|----------|
| Waits | Doesn't wait |
| Synchronization | Independent |
| Safe | Use carefully |
| Can access shared resources safely | Risky |

---

# 8. joinable()

Checks whether thread owns a thread.

Example

```cpp
thread t(work);

if(t.joinable())
{
    t.join();
}
```

After join

```
joinable()

↓

false
```

---

# 9. Passing Arguments

Example

```cpp
#include <iostream>
#include <thread>

using namespace std;

void print(int x)
{
    cout << x << endl;
}

int main()
{
    thread t(print,100);

    t.join();
}
```

Output

```
100
```

---

Multiple arguments

```cpp
void add(int a,int b)
{
    cout<<a+b;
}

thread t(add,10,20);
```

Output

```
30
```

---

# 10. Passing by Reference

Wrong

```cpp
void increment(int &x)
{
    x++;
}

int n=10;

thread t(increment,n);
```

Compilation error.

Reason

Thread copies arguments.

Correct

```cpp
thread t(increment,ref(n));
```

Output

```
11
```

Interview Question

Why std::ref()?

Because std::thread copies arguments by default.

std::ref()

forces reference passing.

---

# 11. Lambda Thread

Example

```cpp
#include <iostream>
#include <thread>

using namespace std;

int main()
{
    thread t([]()
    {
        cout<<"Hello Thread\n";
    });

    t.join();
}
```

Output

```
Hello Thread
```

Advantages

- Small code
- No separate function
- Interview favorite

---

# 12. Member Function Thread

Example

```cpp
#include <iostream>
#include <thread>

using namespace std;

class Demo
{
public:

    void display()
    {
        cout<<"Member Function\n";
    }
};

int main()
{
    Demo d;

    thread t(&Demo::display,&d);

    t.join();
}
```

Explanation

```
&Demo::display

↓

Function Pointer

↓

Need object

↓

&d
```

---

# 13. Multiple Threads

Example

```cpp
#include <iostream>
#include <thread>

using namespace std;

void task(int id)
{
    cout<<"Thread "<<id<<endl;
}

int main()
{
    thread t1(task,1);

    thread t2(task,2);

    thread t3(task,3);

    t1.join();

    t2.join();

    t3.join();
}
```

Output

Order is NOT guaranteed.

Possible

```
Thread 2

Thread 1

Thread 3
```

or

```
Thread 3

Thread 2

Thread 1
```

Scheduler decides.

---

# 14. Thread ID

```cpp
#include <iostream>
#include <thread>

using namespace std;

void work()
{
    cout<<this_thread::get_id()<<endl;
}

int main()
{
    thread t(work);

    cout<<this_thread::get_id()<<endl;

    t.join();
}
```

Output

```
12345

54321
```

Different IDs.

---

# 15. hardware_concurrency()

Returns number of hardware threads.

```cpp
#include <iostream>
#include <thread>

using namespace std;

int main()
{
    cout<<thread::hardware_concurrency();
}
```

Output

```
8
```

Depends on machine.

---

# Interview Questions

## Q1 Why use join()?

Main thread waits for child thread.

---

## Q2 What happens if neither join() nor detach() is called?

```
std::terminate()
```

---

## Q3 Can join() be called twice?

No.

After first join

```
joinable()==false
```

Second join

Undefined behavior.

---

## Q4 Can detached thread be joined?

No.

Detached thread loses ownership.

---

## Q5 Why std::ref()?

Because std::thread copies arguments by default.

---

## Q6 Is execution order guaranteed?

No.

Thread scheduling depends on Operating System.

---

# Summary

✓ Process vs Thread

✓ Thread Life Cycle

✓ std::thread

✓ join()

✓ detach()

✓ joinable()

✓ Passing Arguments

✓ std::ref()

✓ Lambda Threads

✓ Member Function Threads

✓ Multiple Threads

✓ Thread ID

✓ hardware_concurrency()
------------------------------------------------------------------------------------
# C++11 Multithreading Interview Handbook
# Part 2 - Mutex, Race Condition and Synchronization

---

# Contents

1. What is a Race Condition?
2. Critical Section
3. std::mutex
4. lock()
5. unlock()
6. RAII
7. std::lock_guard
8. std::unique_lock
9. lock_guard vs unique_lock
10. Deadlock
11. std::lock()
12. std::adopt_lock
13. std::try_lock()
14. Common Interview Questions

---

# 1. What is a Race Condition?

A **Race Condition** occurs when two or more threads access the same shared data simultaneously and at least one thread modifies it.

The final result becomes unpredictable.

Example

```
Counter = 0

Thread A
Counter++

Thread B
Counter++
```

Expected

```
Counter = 2
```

Possible Result

```
Counter = 1
```

because both threads read the same value before writing.

---

# Why does it happen?

Consider

```cpp
counter++;
```

Many people think this is one instruction.

Actually it is three operations.

```
Load counter

↓

Increment

↓

Store counter
```

Suppose

```
Counter = 5
```

Thread 1

```
Read 5
```

Context switch

Thread 2

```
Read 5

Increment

Store 6
```

Context switch

Thread 1

```
Increment

Store 6
```

Expected

```
7
```

Actual

```
6
```

This is a Race Condition.

---

# Example without Mutex

```cpp
#include <iostream>
#include <thread>

using namespace std;

int counter = 0;

void increment()
{
    for(int i=0;i<100000;i++)
        counter++;
}

int main()
{
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << counter << endl;
}
```

Expected

```
200000
```

Possible Outputs

```
187452

195638

199832
```

Different every run.

---

# 2. Critical Section

A **Critical Section** is the part of code that accesses shared data.

Example

```cpp
counter++;
```

This is the critical section because multiple threads access the same variable.

Only one thread should execute it at a time.

---

# 3. std::mutex

A **mutex** (Mutual Exclusion) allows only one thread to enter the critical section.

```
Thread 1

↓

Lock

↓

Critical Section

↓

Unlock

↓

Thread 2 enters
```

Header

```cpp
#include <mutex>
```

---

# Example using Mutex

```cpp
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;

mutex m;

void increment()
{
    for(int i=0;i<100000;i++)
    {
        m.lock();

        counter++;

        m.unlock();
    }
}

int main()
{
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << counter << endl;
}
```

Output

```
200000
```

Always correct.

---

# How lock() Works

Suppose

```
Thread A

↓

lock()

↓

Critical Section
```

Now

```
Thread B

↓

lock()
```

Since mutex is already locked,

Thread B waits.

```
Thread A

↓

unlock()

↓

Thread B gets mutex

↓

Critical Section
```

Only one thread executes at a time.

---

# Problem with Manual lock()/unlock()

Example

```cpp
m.lock();

counter++;

return;

m.unlock();
```

Problem

```
return

↓

unlock() never executed

↓

Mutex remains locked

↓

Deadlock
```

Similarly

```cpp
m.lock();

throw exception;

m.unlock();
```

Again

```
unlock()

never executes.
```

This is why we use RAII.

---

# 4. RAII

RAII

```
Resource Acquisition Is Initialization
```

Acquire resource in constructor.

Release resource in destructor.

The destructor executes automatically.

This guarantees cleanup even if

- return
- exception
- multiple exit paths

---

# 5. std::lock_guard

Recommended way to lock a mutex.

Example

```cpp
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;

mutex m;

void increment()
{
    for(int i=0;i<100000;i++)
    {
        lock_guard<mutex> lock(m);

        counter++;
    }
}

int main()
{
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << counter << endl;
}
```

Output

```
200000
```

---

# How lock_guard Works

When created

```cpp
lock_guard<mutex> lock(m);
```

Constructor

```
m.lock()
```

When scope ends

Destructor

```
m.unlock()
```

Compiler automatically unlocks.

Flow

```
Enter Scope

↓

lock_guard Constructor

↓

lock()

↓

Critical Section

↓

Leave Scope

↓

lock_guard Destructor

↓

unlock()
```

---

# Example with Exception

```cpp
void work()
{
    lock_guard<mutex> lock(m);

    throw runtime_error("Error");
}
```

Even after exception

```
Destructor

↓

unlock()

executed automatically.
```

---

# 6. std::unique_lock

More flexible than lock_guard.

Supports

- unlock()
- lock()
- defer_lock
- try_lock

Example

```cpp
unique_lock<mutex> lock(m);

counter++;

lock.unlock();

cout<<"Unlocked\n";

lock.lock();

counter++;
```

Unlike lock_guard,

mutex can be unlocked and locked again.

---

# defer_lock

Does not lock immediately.

```cpp
unique_lock<mutex> lock(m,defer_lock);

cout<<"Not locked yet\n";

lock.lock();

counter++;
```

Useful when locking multiple mutexes.

---

# try_lock

Attempts to lock without waiting.

```cpp
if(m.try_lock())
{
    cout<<"Locked\n";

    m.unlock();
}
else
{
    cout<<"Busy\n";
}
```

No blocking.

---

# lock_guard vs unique_lock

| lock_guard | unique_lock |
|------------|-------------|
| Lightweight | Slightly heavier |
| Auto lock | Auto or manual |
| Cannot unlock | Can unlock |
| No defer_lock | Supports defer_lock |
| No try_lock | Supports try_lock |
| Fast | Flexible |

Interview Rule

Use

```
lock_guard
```

when simple locking is enough.

Use

```
unique_lock
```

when flexibility is required.

---

# 7. Deadlock

Deadlock occurs when two or more threads wait forever for each other.

Example

Thread 1

```
lock(A)

↓

lock(B)
```

Thread 2

```
lock(B)

↓

lock(A)
```

Suppose

Thread 1 locks

```
A
```

Thread 2 locks

```
B
```

Now

Thread 1 waits for

```
B
```

Thread 2 waits for

```
A
```

Neither can continue.

```
Forever Waiting
```

Deadlock.

---

# Deadlock Example

```cpp
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1,m2;

void task1()
{
    lock_guard<mutex> l1(m1);

    this_thread::sleep_for(chrono::milliseconds(100));

    lock_guard<mutex> l2(m2);

    cout<<"Task1\n";
}

void task2()
{
    lock_guard<mutex> l1(m2);

    this_thread::sleep_for(chrono::milliseconds(100));

    lock_guard<mutex> l2(m1);

    cout<<"Task2\n";
}

int main()
{
    thread t1(task1);
    thread t2(task2);

    t1.join();
    t2.join();
}
```

Program may hang forever.

---

# Avoiding Deadlock

Use

```cpp
std::lock()
```

instead of locking separately.

---

# std::lock()

Locks multiple mutexes safely.

Example

```cpp
mutex m1,m2;

void task()
{
    lock(m1,m2);

    lock_guard<mutex> l1(m1,adopt_lock);

    lock_guard<mutex> l2(m2,adopt_lock);

    cout<<"Safe\n";
}
```

No deadlock.

---

# Why adopt_lock?

Normally

```cpp
lock_guard<mutex> lock(m);
```

calls

```
lock()
```

But

```cpp
std::lock(m1,m2);
```

already locked them.

If lock_guard locks again,

```
Deadlock
```

So

```cpp
adopt_lock
```

means

```
Mutex is already locked.

Just take ownership.

Don't call lock().
```

---

# try_lock()

Returns immediately.

```cpp
if(m.try_lock())
{
    cout<<"Success\n";

    m.unlock();
}
else
{
    cout<<"Mutex Busy\n";
}
```

Unlike

```
lock()
```

it never waits.

---

# Common Interview Questions

## Q1 What is a race condition?

Multiple threads access shared data simultaneously and at least one modifies it, leading to unpredictable results.

---

## Q2 Why do we need mutex?

To ensure only one thread accesses the critical section at a time.

---

## Q3 Why is lock_guard preferred?

Because it automatically unlocks the mutex even if exceptions or early returns occur.

---

## Q4 lock_guard vs unique_lock?

```
lock_guard

↓

Simple
↓

Fast
↓

Automatic
```

```
unique_lock

↓

Flexible

↓

unlock()

↓

lock()

↓

defer_lock

↓

try_lock()
```

---

## Q5 What is a deadlock?

Two or more threads wait forever for each other to release resources.

---

## Q6 How can deadlock be avoided?

- Lock mutexes in the same order.
- Use `std::lock()`.
- Keep critical sections short.
- Avoid nested locks when possible.

---

# Summary

✔ Race Condition

✔ Critical Section

✔ std::mutex

✔ lock()

✔ unlock()

✔ RAII

✔ lock_guard

✔ unique_lock

✔ defer_lock

✔ try_lock()

✔ Deadlock

✔ std::lock()

✔ adopt_lock

✔ Interview Questions
-------------------------------------------------------------------------------------
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
-------------------------------------------------------------------------------
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
---------------------------------------------------------------------------
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
--------------------------------------------------------------------------------
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
--------------------------------------------------------------------------------
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
-----------------------------------------------------------------------
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
