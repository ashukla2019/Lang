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
