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
