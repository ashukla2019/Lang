# Advanced C Interview Solutions - Part 7

# Read-Write Lock + B+ Tree Basics + Key Value Store Design

Topics covered:

1. Read-write lock implementation
2. Reader starvation handling
3. B+ Tree concepts
4. B+ Tree node structure
5. Key-value store architecture
6. Storage interview discussion points

---

# 1. Read-Write Lock

## Problem

Many systems have:

- Many readers
- Few writers

Example:

Database:

```
1000 readers

1 writer

```

A normal mutex allows only one thread.

A read-write lock allows:

```
Multiple readers together

OR

One writer exclusively

```

---

# Lock States

```
No lock

Readers:
R1 R2 R3

Writer:
W

```

Rules:

1. Multiple readers allowed.
2. Writer gets exclusive access.
3. Readers cannot enter during writing.

---

# Data Structure

```c
#include <pthread.h>


typedef struct
{
    pthread_mutex_t mutex;


    pthread_cond_t readers_ok;

    pthread_cond_t writers_ok;


    int readers;

    int writers;


    int waiting_writers;


}RWLock;

```

---

# 2. Initialize Lock

```c
void rwlock_init(RWLock *lock)
{
    pthread_mutex_init(
        &lock->mutex,
        NULL);


    pthread_cond_init(
        &lock->readers_ok,
        NULL);


    pthread_cond_init(
        &lock->writers_ok,
        NULL);


    lock->readers=0;

    lock->writers=0;

    lock->waiting_writers=0;
}

```

---

# 3. Acquire Read Lock

## Logic

Reader waits if:

```
writer active

OR

writer waiting

```

Second condition prevents writer starvation.

---

```c
void read_lock(RWLock *lock)
{
    pthread_mutex_lock(
        &lock->mutex);



    while(lock->writers ||
          lock->waiting_writers)
    {
        pthread_cond_wait(
            &lock->readers_ok,
            &lock->mutex);
    }



    lock->readers++;



    pthread_mutex_unlock(
        &lock->mutex);
}

```

---

# 4. Release Read Lock

```c
void read_unlock(RWLock *lock)
{
    pthread_mutex_lock(
        &lock->mutex);



    lock->readers--;



    if(lock->readers == 0)
    {
        pthread_cond_signal(
            &lock->writers_ok);
    }



    pthread_mutex_unlock(
        &lock->mutex);
}

```

---

# 5. Acquire Write Lock

```c
void write_lock(RWLock *lock)
{
    pthread_mutex_lock(
        &lock->mutex);



    lock->waiting_writers++;



    while(lock->writers ||
          lock->readers)
    {
        pthread_cond_wait(
            &lock->writers_ok,
            &lock->mutex);
    }



    lock->waiting_writers--;


    lock->writers=1;



    pthread_mutex_unlock(
        &lock->mutex);
}

```

---

# 6. Release Write Lock

```c
void write_unlock(RWLock *lock)
{
    pthread_mutex_lock(
        &lock->mutex);



    lock->writers=0;



    if(lock->waiting_writers)
    {
        pthread_cond_signal(
            &lock->writers_ok);
    }
    else
    {
        pthread_cond_broadcast(
            &lock->readers_ok);
    }



    pthread_mutex_unlock(
        &lock->mutex);
}

```

---

# Read-Write Lock Complexity

| Operation | Time |
|-|-|
| Lock | O(1) |
| Unlock | O(1) |

---

# Interview Discussion

## Reader starvation

Problem:

Continuous readers prevent writer execution.

Solution:

Track:

```c
waiting_writers
```

Give writers priority.

---

# 2. B+ Tree Basics

Used in:

- Databases
- File systems
- Storage systems

Examples:

- MySQL indexes
- Filesystem metadata

---

# Why B+ Tree?

Binary tree:

```
Height = large

```

B+ Tree:

```
High fanout

Small height

```

---

# Structure

Example order 4:

```
              [20 40]

            /    |    \

       [10] [30] [50 60]


Leaf nodes contain data.

```

---

# Properties

1. Balanced tree.
2. All data stored in leaves.
3. Internal nodes store keys only.
4. Leaves linked together.

---

# Leaf Link

```
Leaf1 ---> Leaf2 ---> Leaf3

```

Benefits:

Range queries:

```
Find keys 100-200

```

---

# 3. B+ Tree Node Structure

```c
#define ORDER 4


typedef struct BPlusNode
{
    int keys[ORDER];


    void *values[ORDER];


    struct BPlusNode *children[ORDER+1];


    int key_count;


    int is_leaf;


    struct BPlusNode *next;


}BPlusNode;

```

---

# 4. Search Operation

Algorithm:

1. Start root.
2. Compare key.
3. Follow child.
4. Continue until leaf.

Complexity:

```
O(log n)

```

---

# 5. Insert Operation

Steps:

1. Find leaf.
2. Insert key.
3. If overflow:
   - Split node
   - Push middle key upward

---

Example:

Before:

```
[10 20 30 40]

```

Overflow:

```
[10 20 30 40 50]

```

Split:

```
        30

   [10 20] [40 50]

```

---

# B+ Tree Interview Questions

## Why are leaves linked?

For fast range scans.

---

## Why not binary tree?

Disk access is expensive.

B+ Tree minimizes height.

---

# 6. Key Value Store Design

Example:

```
put("user1","John")

get("user1")

```

---

# Architecture

```
Client

 |

API Layer

 |

Memory Cache

 |

Storage Engine

 |

Disk

```

---

# Components

## 1. API Layer

Handles:

- Requests
- Validation

---

## 2. Cache

Examples:

- LRU cache
- Hash map

---

## 3. Storage Engine

Options:

- Hash table
- B+ Tree
- Log structured merge tree

---

## 4. Write Ahead Log

Before modifying data:

```
Write operation

      |

      v

     WAL

      |

      v

    Memory

```

Purpose:

Crash recovery.

---

# 7. Simple KV Store Data Structures

```c
typedef struct KVNode
{
    char key[64];

    char value[256];


    struct KVNode *next;

}KVNode;

```

---

# Operations

## PUT

Average:

```
O(1)

```

using hash table.

---

## GET

Average:

```
O(1)

```

---

## DELETE

Average:

```
O(1)

```

---

# Storage System Interview Mapping

For companies like NetApp:

Expect discussions around:

## Cache

- LRU
- Write-back cache
- Dirty pages

---

## Metadata

- B+ Tree
- Hash indexes
- Snapshots

---

## Reliability

- WAL
- Journaling
- Replication

---

## Performance

- Lock contention
- CPU cache
- IO batching

---

# Next Part

## Part 8

Will cover:

1. Linux system programming
2. mmap()
3. epoll()
4. File descriptors
5. Socket programming
6. Zero-copy networking
7. Debugging tools (gdb, valgrind, strace)

