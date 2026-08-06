# Advanced C Interview Coding Solutions - Part 4

# Memory Pool Allocator + Thread Safe Queue

Topics covered:

1. Memory pool design
2. Pool creation
3. Allocation
4. Free operation
5. Destroy pool
6. Thread-safe queue
7. Mutex
8. Condition variables
9. Producer-consumer pattern

---

# 1. Memory Pool Allocator

## Problem

Frequent calls to:

```c
malloc()
free()
```

can cause:

- Heap fragmentation
- Performance overhead
- Unpredictable latency

A memory pool allocates a large block once and manages smaller objects from it.

---

# Memory Pool Design

```
Memory Pool

+----+----+----+----+----+
|Free|Free|Used|Free|Used|
+----+----+----+----+----+

```

Maintain:

- Memory block
- Free list

---

# Data Structures

```c
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


typedef struct Block
{
    struct Block *next;

}Block;



typedef struct
{
    void *memory;

    Block *free_list;


    size_t block_size;

    size_t total_blocks;


}MemoryPool;

```

---

# 2. Create Memory Pool

## Algorithm

1. Allocate large memory area.
2. Divide into blocks.
3. Link all blocks.

---

## Implementation

```c
MemoryPool *pool_create(size_t block_size,
                        size_t count)
{
    MemoryPool *pool =
        malloc(sizeof(MemoryPool));


    if(pool == NULL)
        return NULL;


    pool->block_size =
        block_size < sizeof(Block)
        ? sizeof(Block)
        : block_size;


    pool->total_blocks = count;


    pool->memory =
        malloc(pool->block_size * count);



    if(pool->memory == NULL)
    {
        free(pool);

        return NULL;
    }


    pool->free_list = NULL;



    char *ptr =
        (char *)pool->memory;



    for(size_t i=0;i<count;i++)
    {
        Block *block =
            (Block *)(ptr +
            i * pool->block_size);



        block->next =
            pool->free_list;


        pool->free_list =
            block;
    }


    return pool;
}
```

---

# 3. Allocate From Pool

## Algorithm

Remove first free block.

---

```c
void *pool_alloc(MemoryPool *pool)
{
    if(pool->free_list == NULL)
        return NULL;


    Block *block =
        pool->free_list;


    pool->free_list =
        block->next;


    return block;
}
```

---

# 4. Free Memory Back To Pool

```c
void pool_free(MemoryPool *pool,
               void *ptr)
{
    if(ptr == NULL)
        return;


    Block *block =
        (Block *)ptr;


    block->next =
        pool->free_list;


    pool->free_list =
        block;
}
```

---

# 5. Destroy Pool

```c
void pool_destroy(MemoryPool *pool)
{
    if(pool == NULL)
        return;


    free(pool->memory);

    free(pool);
}
```

---

# Memory Pool Complexity

| Operation | Complexity |
|-|-|
| Allocate | O(1) |
| Free | O(1) |
| Create | O(n) |

---

# Memory Pool Interview Points

## Advantages

- Fast allocation
- No fragmentation
- Predictable latency

Used in:

- Network buffers
- Database engines
- Operating systems

---

## Limitations

- Fixed object size
- Memory wastage possible
- Need ownership discipline

---

# 2. Thread Safe Queue

## Problem

Multiple threads accessing shared queue.

Need:

- Mutual exclusion
- Blocking when empty
- Blocking when full

---

# Design

Use:

- Linked list queue
- Mutex
- Condition variables


```
Producer

    |
    v

+-----+-----+-----+
| 10  | 20  | 30 |
+-----+-----+-----+

    ^
    |
 Consumer

```

---

# Queue Node

```c
typedef struct QueueNode
{
    void *data;

    struct QueueNode *next;

}QueueNode;

```

---

# Queue Structure

```c
#include <pthread.h>


typedef struct
{
    QueueNode *front;

    QueueNode *rear;


    int size;


    pthread_mutex_t mutex;


    pthread_cond_t not_empty;


}ThreadQueue;

```

---

# 3. Initialize Queue

```c
void queue_init(ThreadQueue *queue)
{
    queue->front = NULL;

    queue->rear = NULL;

    queue->size = 0;


    pthread_mutex_init(
        &queue->mutex,
        NULL);


    pthread_cond_init(
        &queue->not_empty,
        NULL);
}

```

---

# 4. Enqueue Operation

## Algorithm

1. Lock mutex.
2. Add node.
3. Signal waiting consumer.
4. Unlock.


---

```c
void enqueue(ThreadQueue *queue,
             void *data)
{
    QueueNode *node =
        malloc(sizeof(QueueNode));


    node->data=data;

    node->next=NULL;



    pthread_mutex_lock(
        &queue->mutex);



    if(queue->rear == NULL)
    {
        queue->front =
            node;

        queue->rear =
            node;
    }
    else
    {
        queue->rear->next =
            node;

        queue->rear =
            node;
    }


    queue->size++;


    pthread_cond_signal(
        &queue->not_empty);



    pthread_mutex_unlock(
        &queue->mutex);
}

```

---

# 5. Dequeue Operation

## Algorithm

If queue empty:

Wait.

Otherwise:

Remove front node.

---

```c
void *dequeue(ThreadQueue *queue)
{
    pthread_mutex_lock(
        &queue->mutex);



    while(queue->front == NULL)
    {
        pthread_cond_wait(
            &queue->not_empty,
            &queue->mutex);
    }



    QueueNode *node =
        queue->front;



    queue->front =
        node->next;



    if(queue->front == NULL)
    {
        queue->rear=NULL;
    }


    queue->size--;



    void *data =
        node->data;


    free(node);



    pthread_mutex_unlock(
        &queue->mutex);



    return data;
}

```

---

# 6. Destroy Queue

```c
void queue_destroy(ThreadQueue *queue)
{
    pthread_mutex_destroy(
        &queue->mutex);


    pthread_cond_destroy(
        &queue->not_empty);
}

```

---

# Producer Consumer Example

## Producer

```c
void *producer(void *arg)
{
    ThreadQueue *q =
        (ThreadQueue *)arg;


    for(int i=0;i<10;i++)
    {
        int *value =
            malloc(sizeof(int));


        *value=i;


        enqueue(q,value);
    }


    return NULL;
}

```

---

## Consumer

```c
void *consumer(void *arg)
{
    ThreadQueue *q =
        (ThreadQueue *)arg;


    for(int i=0;i<10;i++)
    {
        int *value =
            dequeue(q);


        printf("%d\n",
               *value);


        free(value);
    }


    return NULL;
}

```

---

# Thread Safety Discussion

## Mutex

Provides:

```
Only one thread enters critical section

```

---

## Condition Variable

Provides:

```
Sleep until condition becomes true

```

---

## Why while() around pthread_cond_wait()?

Wrong:

```c
if(queue empty)
 wait();

```

Correct:

```c
while(queue empty)
 wait();

```

because of:

- Spurious wakeups
- Another thread consuming data first

---

# Common Senior Interview Follow-ups

1. How to make queue bounded?
2. How to avoid mutex contention?
3. How to implement lock-free queue?
4. How to handle shutdown?
5. How to wake all waiting threads?
6. How to debug deadlock?

---

# Next Part

## Part 5

Will cover:

1. Thread Pool Implementation
2. Worker Threads
3. Job Queue
4. Task Submission
5. Shutdown Handling
6. Circular Buffer Implementation

