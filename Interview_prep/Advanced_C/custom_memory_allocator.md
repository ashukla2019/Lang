# Advanced C Interview Coding Solutions - Part 6

# Custom Memory Allocator + Lock-Free Programming Basics

Topics covered:

1. How malloc works internally
2. Implementing a simple malloc allocator
3. Free list management
4. Block splitting
5. Block merging
6. Atomic operations
7. Lock-free stack
8. ABA problem

---

# 1. How malloc() Works Internally

A simplified malloc implementation:

```
Application

    |
    v

malloc(size)

    |
    v

Memory Allocator

    |
    +---- Free List
    |
    +---- System Memory

    |
    v

Heap

```

The allocator manages:

- Memory blocks
- Free blocks
- Allocation metadata

---

# Memory Block Design

Each allocation contains:

```
+----------------+
| Metadata       |
+----------------+
| User Data      |
+----------------+

```

Metadata stores:

- Block size
- Free/used status
- Next block pointer

---

# 2. Block Structure

```c
#include <stdio.h>
#include <unistd.h>


typedef struct BlockHeader
{
    size_t size;

    int free;


    struct BlockHeader *next;


}BlockHeader;
```

---

# Global Free List

```c
static BlockHeader *free_list = NULL;

```

---

# 3. Find Free Block

Search existing free memory.

```c
BlockHeader *find_free_block(size_t size)
{
    BlockHeader *current =
        free_list;


    while(current)
    {
        if(current->free &&
           current->size >= size)
        {
            return current;
        }


        current=current->next;
    }


    return NULL;
}

```

---

# 4. Request Memory From OS

Uses:

```c
sbrk()
```

which expands process heap.

---

```c
BlockHeader *request_memory(size_t size)
{
    void *request =
        sbrk(size + sizeof(BlockHeader));


    if(request == (void *)-1)
        return NULL;



    BlockHeader *block =
        (BlockHeader *)request;


    block->size=size;

    block->free=0;

    block->next=NULL;


    return block;
}

```

---

# 5. Custom malloc()

## Algorithm

1. Search free list.
2. If found, reuse block.
3. Otherwise request memory.

---

```c
void *my_malloc(size_t size)
{
    BlockHeader *block;


    if(size == 0)
        return NULL;



    block =
        find_free_block(size);



    if(block == NULL)
    {
        block =
            request_memory(size);


        if(block == NULL)
            return NULL;
    }
    else
    {
        block->free=0;
    }



    return (block + 1);
}

```

---

# Why return block + 1?

Example:

```
Address

1000
 |
 v

+--------------+
| Metadata     |
+--------------+
| User memory  |
+--------------+

```

If block is at 1000:

```
block + 1

```

points after metadata.

---

# 6. Custom free()

## Algorithm

1. Move pointer back to header.
2. Mark block free.

---

```c
void my_free(void *ptr)
{
    if(ptr == NULL)
        return;


    BlockHeader *block =
        ((BlockHeader *)ptr) - 1;


    block->free=1;
}

```

---

# 7. Block Splitting

Problem:

Free block is larger than requested.

Example:

```
Free block:

100 bytes


Request:

20 bytes


Before:

+----------------+
| 100 bytes      |
+----------------+


After:

+------+---------+
|20    | 80 free |
+------+---------+

```

Benefits:

- Reduces waste
- Improves reuse

---

# 8. Block Merging

Problem:

Fragmentation.

Example:

```
+----+----+----+
|Free|Free|Used|
+----+----+----+

```

Merge adjacent free blocks:

```
+----------+----+
| Free     |Used|
+----------+----+

```

---

# Allocator Improvements

Production allocators use:

- Multiple free lists
- Size classes
- Thread local caches
- Memory arenas
- mmap()
- Alignment handling

Examples:

- glibc malloc
- jemalloc
- tcmalloc

---

# 9. Atomic Operations

## Problem

Race condition:

```c
counter++;

```

Actually:

```
Read

Modify

Write

```

Two threads can overwrite each other.

---

# Atomic Increment

Using C11 atomics:

```c
#include <stdatomic.h>


atomic_int counter;


void increment()
{
    atomic_fetch_add(
        &counter,
        1);
}

```

---

# Atomic Guarantees

Atomic operation:

- Cannot be interrupted
- Visible between threads
- Provides ordering guarantees

---

# 10. Lock-Free Stack

## Design

Stack:

```
Top

 |
 v

Node1
 |
Node2

```

Operations:

- Push
- Pop

Use:

Compare-And-Swap (CAS)

---

# Node Structure

```c
typedef struct StackNode
{
    int data;


    struct StackNode *next;


}StackNode;


_Atomic(StackNode *) top;

```

---

# 11. Lock-Free Push

Algorithm:

1. Create node.
2. Point node to current top.
3. CAS updates top.

---

```c
void push(StackNode *node)
{
    StackNode *old_top;


    do
    {
        old_top =
            atomic_load(&top);


        node->next =
            old_top;


    }
    while(!atomic_compare_exchange_weak(
              &top,
              &old_top,
              node));
}

```

---

# 12. Lock-Free Pop

Algorithm:

1. Read top.
2. Move top to next.
3. CAS update.

---

```c
StackNode *pop()
{
    StackNode *old_top;


    StackNode *next;


    do
    {
        old_top =
            atomic_load(&top);


        if(old_top == NULL)
            return NULL;


        next =
            old_top->next;


    }
    while(!atomic_compare_exchange_weak(
              &top,
              &old_top,
              next));



    return old_top;
}

```

---

# 13. ABA Problem

Important senior interview topic.

Example:

Thread 1:

```
Reads top = A

```

Thread 2:

```
A removed

B inserted

A inserted again

```

Thread 1:

```
CAS sees A

Assumes nothing changed

```

Problem:

Value same, state changed.

---

# Solutions

## 1. Tagged pointers

Store:

```
Pointer + version counter

```

Example:

```
(A,1)

(A,2)

```

---

## 2. Hazard pointers

Threads announce memory they are using.

Prevents unsafe reclamation.

---

## 3. Epoch based reclamation

Delay freeing until safe.

---

# Senior Interview Questions

## Q1. Why is volatile not enough for multithreading?

Answer:

volatile only prevents compiler optimization.

It does not provide:

- Atomicity
- Ordering
- Synchronization

---

## Q2. Mutex vs Atomic?

Mutex:

- Multiple operations
- Blocking

Atomic:

- Single variable operations
- Lock-free possibility

---

## Q3. Why lock-free is difficult?

Need to handle:

- Memory ordering
- ABA problem
- Memory reclamation
- CPU architecture differences

---

# Next Part

## Part 7

Will cover:

1. Read-write lock implementation
2. Semaphore implementation concepts
3. B+ Tree basics
4. Key-value store design
5. Storage-system design questions for NetApp

