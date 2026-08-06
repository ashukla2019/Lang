# Advanced C Interview Coding Solutions - Part 5

# Thread Pool + Circular Buffer

Topics covered:

1. Thread pool design
2. Worker threads
3. Job queue
4. Task submission
5. Thread pool shutdown
6. Circular buffer implementation

---

# 1. Thread Pool

## Problem

Creating a thread for every task is expensive.

Example:

```
Request 1 -> Create Thread
Request 2 -> Create Thread
Request 3 -> Create Thread

```

Problems:

- Thread creation overhead
- Context switching
- Resource usage

Solution:

Create fixed worker threads.

```
                +-------------+
Jobs ---------->| Job Queue   |
                +-------------+
                      |
        +-------------+-------------+
        |             |             |
     Worker 1     Worker 2      Worker 3

```

---

# Thread Pool Design

Components:

1. Worker threads
2. Task queue
3. Mutex
4. Condition variable
5. Shutdown flag

---

# Task Structure

```c
typedef void (*task_function)(void *);


typedef struct Task
{
    task_function function;

    void *argument;


    struct Task *next;

}Task;
```

---

# Thread Pool Structure

```c
#include <pthread.h>


typedef struct
{
    pthread_t *threads;


    int thread_count;


    Task *front;

    Task *rear;


    pthread_mutex_t mutex;


    pthread_cond_t condition;


    int shutdown;


}ThreadPool;

```

---

# 2. Worker Thread Function

## Algorithm

Worker:

1. Lock queue.
2. Wait if no task.
3. Get task.
4. Execute task.
5. Repeat.

---

## Implementation

```c
void *worker_thread(void *arg)
{
    ThreadPool *pool =
        (ThreadPool *)arg;



    while(1)
    {
        pthread_mutex_lock(
            &pool->mutex);



        while(pool->front == NULL &&
              !pool->shutdown)
        {
            pthread_cond_wait(
                &pool->condition,
                &pool->mutex);
        }



        if(pool->shutdown &&
           pool->front == NULL)
        {
            pthread_mutex_unlock(
                &pool->mutex);

            break;
        }



        Task *task =
            pool->front;



        pool->front =
            task->next;



        if(pool->front == NULL)
            pool->rear=NULL;



        pthread_mutex_unlock(
            &pool->mutex);



        task->function(
            task->argument);



        free(task);
    }


    return NULL;
}

```

---

# 3. Create Thread Pool

```c
ThreadPool *threadpool_create(int count)
{
    ThreadPool *pool =
        malloc(sizeof(ThreadPool));


    pool->thread_count=count;

    pool->shutdown=0;


    pool->front=NULL;

    pool->rear=NULL;



    pthread_mutex_init(
        &pool->mutex,
        NULL);



    pthread_cond_init(
        &pool->condition,
        NULL);



    pool->threads =
        malloc(sizeof(pthread_t)*count);



    for(int i=0;i<count;i++)
    {
        pthread_create(
            &pool->threads[i],
            NULL,
            worker_thread,
            pool);
    }


    return pool;
}

```

---

# 4. Submit Task

## Algorithm

1. Create task.
2. Add to queue.
3. Wake worker.


---

```c
void threadpool_submit(ThreadPool *pool,
                       task_function function,
                       void *argument)
{
    Task *task =
        malloc(sizeof(Task));


    task->function=function;

    task->argument=argument;

    task->next=NULL;



    pthread_mutex_lock(
        &pool->mutex);



    if(pool->rear == NULL)
    {
        pool->front=task;

        pool->rear=task;
    }
    else
    {
        pool->rear->next=task;

        pool->rear=task;
    }



    pthread_cond_signal(
        &pool->condition);



    pthread_mutex_unlock(
        &pool->mutex);
}

```

---

# 5. Destroy Thread Pool

## Steps

1. Set shutdown flag.
2. Wake all workers.
3. Join threads.
4. Free resources.


---

```c
void threadpool_destroy(ThreadPool *pool)
{
    pthread_mutex_lock(
        &pool->mutex);



    pool->shutdown=1;



    pthread_cond_broadcast(
        &pool->condition);



    pthread_mutex_unlock(
        &pool->mutex);



    for(int i=0;i<pool->thread_count;i++)
    {
        pthread_join(
            pool->threads[i],
            NULL);
    }



    free(pool->threads);


    pthread_mutex_destroy(
        &pool->mutex);


    pthread_cond_destroy(
        &pool->condition);


    free(pool);
}

```

---

# Thread Pool Complexity

| Operation | Complexity |
|-|-|
| Submit task | O(1) |
| Execute task | Depends on task |
| Shutdown | O(number of threads) |

---

# Thread Pool Interview Discussion

## Why fixed number of threads?

Avoid:

- Unlimited thread creation
- Memory exhaustion
- CPU oversubscription

---

## How to choose thread count?

Depends on workload.

CPU bound:

```
threads ~= CPU cores

```

I/O bound:

```
threads > CPU cores

```

---

## Improvements

Production systems add:

- Bounded queue
- Priority queue
- Worker stealing
- Task cancellation
- Statistics
- Dynamic resizing

---

# 6. Circular Buffer

## Problem

Fixed-size queue using array.

Used in:

- Network buffers
- Audio buffers
- Kernel queues
- Producer-consumer systems


---

# Design

```
             size = 5


Index:

0   1   2   3   4

+---+---+---+---+---+
|10 |20 |30 |   |   |
+---+---+---+---+---+

 ^
 |
read

         ^
         |
        write

```

---

# Circular Buffer Structure

```c
typedef struct
{
    int *buffer;


    int capacity;


    int head;


    int tail;


    int count;


}CircularBuffer;

```

---

# 7. Create Buffer

```c
CircularBuffer *buffer_create(int size)
{
    CircularBuffer *cb =
        malloc(sizeof(CircularBuffer));


    cb->buffer =
        malloc(sizeof(int)*size);


    cb->capacity=size;


    cb->head=0;

    cb->tail=0;

    cb->count=0;


    return cb;
}

```

---

# 8. Check Full

```c
int buffer_full(CircularBuffer *cb)
{
    return cb->count ==
           cb->capacity;
}

```

---

# 9. Check Empty

```c
int buffer_empty(CircularBuffer *cb)
{
    return cb->count == 0;
}

```

---

# 10. Write Data

```c
int buffer_write(CircularBuffer *cb,
                 int value)
{
    if(buffer_full(cb))
        return -1;



    cb->buffer[cb->tail]=value;



    cb->tail =
        (cb->tail + 1)
        % cb->capacity;



    cb->count++;


    return 0;
}

```

---

# 11. Read Data

```c
int buffer_read(CircularBuffer *cb,
                int *value)
{
    if(buffer_empty(cb))
        return -1;



    *value =
        cb->buffer[cb->head];



    cb->head =
        (cb->head + 1)
        % cb->capacity;



    cb->count--;


    return 0;
}

```

---

# 12. Destroy Buffer

```c
void buffer_destroy(CircularBuffer *cb)
{
    free(cb->buffer);

    free(cb);
}

```

---

# Circular Buffer Complexity

| Operation | Complexity |
|-|-|
| Write | O(1) |
| Read | O(1) |
| Full check | O(1) |
| Empty check | O(1) |

---

# Senior Interview Follow-ups

## Thread safety

How to make circular buffer thread-safe?

Answer:

Use:

- Mutex
- Condition variables

or:

- Atomic head/tail indexes
- Lock-free design

---

## Why use modulo?

Because:

```c
(index + 1) % size
```

wraps around.

Example:

```
0 1 2 3 4

next after 4:

(4+1)%5 = 0

```

---

# Complete Coding Set Finished

Covered:

✓ strlen  
✓ strcpy  
✓ memcpy  
✓ memmove  
✓ Linked list  
✓ Hash table  
✓ LRU cache  
✓ Memory pool allocator  
✓ Thread-safe queue  
✓ Thread pool  
✓ Circular buffer  

---

# Next Advanced Topics

Recommended next modules:

1. Lock-free queue using atomics
2. Custom malloc implementation
3. Read-write lock implementation
4. B+ Tree implementation
5. Key-value store design
6. Storage system design (NetApp style)

