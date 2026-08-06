# Advanced C Interview Solutions - Part 12

# Thread Pool + Producer Consumer + Circular Buffer

Topics covered:

1. Producer-consumer pattern
2. Circular buffer implementation
3. Thread pool design
4. Worker threads
5. Condition variables
6. Task scheduling
7. Shutdown handling

---

# 1. Producer Consumer Pattern

## Problem

One thread produces data.

Another thread consumes data.

Example:

```
Producer

   |
   |
 Queue
   |
   |
Consumer

```

---

# Real-world Examples

- Network packet processing
- Disk IO pipelines
- Log processing
- Job scheduling

---

# Requirements

Need:

- Thread-safe queue
- Blocking when queue full
- Blocking when queue empty

---

# 2. Circular Buffer

A circular buffer uses fixed memory.

Example:

```
Buffer:

+---+---+---+---+
| 0 | 1 | 2 | 3 |
+---+---+---+---+

      ^
      |
    wrap around

```

---

# Advantages

- No memory allocation
- O(1) insert
- O(1) remove
- Cache friendly

---

# Circular Buffer Structure

```c
#define BUFFER_SIZE 1024


typedef struct
{
    int buffer[BUFFER_SIZE];


    int head;


    int tail;


    int count;


    pthread_mutex_t lock;


    pthread_cond_t not_empty;


    pthread_cond_t not_full;


}CircularBuffer;

```

---

# Initialize

```c
void buffer_init(CircularBuffer *cb)
{
    cb->head=0;

    cb->tail=0;

    cb->count=0;


    pthread_mutex_init(
        &cb->lock,
        NULL);


    pthread_cond_init(
        &cb->not_empty,
        NULL);


    pthread_cond_init(
        &cb->not_full,
        NULL);
}

```

---

# Insert Item

## Algorithm

Wait if full.

```
count == BUFFER_SIZE

```

---

```c
void buffer_push(
CircularBuffer *cb,
int value)
{
    pthread_mutex_lock(
        &cb->lock);


    while(cb->count ==
          BUFFER_SIZE)
    {
        pthread_cond_wait(
            &cb->not_full,
            &cb->lock);
    }



    cb->buffer[cb->tail]=value;


    cb->tail =
        (cb->tail+1)
        % BUFFER_SIZE;


    cb->count++;


    pthread_cond_signal(
        &cb->not_empty);


    pthread_mutex_unlock(
        &cb->lock);
}

```

---

# Remove Item

```c
int buffer_pop(
CircularBuffer *cb)
{
    int value;


    pthread_mutex_lock(
        &cb->lock);



    while(cb->count == 0)
    {
        pthread_cond_wait(
            &cb->not_empty,
            &cb->lock);
    }



    value =
        cb->buffer[cb->head];



    cb->head =
        (cb->head+1)
        % BUFFER_SIZE;



    cb->count--;



    pthread_cond_signal(
        &cb->not_full);



    pthread_mutex_unlock(
        &cb->lock);


    return value;
}

```

---

# Circular Buffer Complexity

| Operation | Complexity |
|-|-|
| Insert | O(1) |
| Remove | O(1) |

---

# 3. Thread Pool Design

## Problem

Creating threads repeatedly is expensive.

Bad:

```
Request

 |

Create Thread

 |

Execute

 |

Destroy

```

---

# Better:

Create fixed workers.

```
Thread Pool

Worker1
Worker2
Worker3

       |

     Queue

       |

     Tasks

```

---

# Components

A thread pool contains:

1. Worker threads
2. Task queue
3. Synchronization
4. Shutdown mechanism

---

# Task Structure

```c
typedef struct Task
{
    void (*function)(void *);


    void *argument;


    struct Task *next;


}Task;

```

---

# Thread Pool Structure

```c
typedef struct
{
    pthread_t *threads;


    int thread_count;


    Task *head;


    Task *tail;


    pthread_mutex_t lock;


    pthread_cond_t condition;


    int shutdown;


}ThreadPool;

```

---

# 4. Worker Thread

Worker loop:

```
while running:

    Get task

    Execute task

```

---

```c
void *worker(void *arg)
{
    ThreadPool *pool =
        (ThreadPool *)arg;


    while(1)
    {
        pthread_mutex_lock(
            &pool->lock);



        while(pool->head == NULL &&
              !pool->shutdown)
        {
            pthread_cond_wait(
                &pool->condition,
                &pool->lock);
        }



        if(pool->shutdown)
        {
            pthread_mutex_unlock(
                &pool->lock);

            break;
        }



        Task *task =
            pool->head;



        pool->head =
            task->next;



        pthread_mutex_unlock(
            &pool->lock);



        task->function(
            task->argument);



        free(task);
    }


    return NULL;
}

```

---

# 5. Add Task To Pool

```c
void submit_task(
ThreadPool *pool,
void (*function)(void *),
void *argument)
{

    Task *task =
        malloc(sizeof(Task));


    task->function=function;

    task->argument=argument;

    task->next=NULL;



    pthread_mutex_lock(
        &pool->lock);



    if(pool->tail)
        pool->tail->next=task;
    else
        pool->head=task;



    pool->tail=task;



    pthread_cond_signal(
        &pool->condition);



    pthread_mutex_unlock(
        &pool->lock);
}

```

---

# 6. Shutdown Thread Pool

Steps:

1. Set shutdown flag.
2. Wake sleeping threads.
3. Join threads.
4. Free resources.

---

```c
void destroy_pool(
ThreadPool *pool)
{
    pthread_mutex_lock(
        &pool->lock);



    pool->shutdown=1;



    pthread_cond_broadcast(
        &pool->condition);



    pthread_mutex_unlock(
        &pool->lock);



    for(int i=0;i<pool->thread_count;i++)
    {
        pthread_join(
            pool->threads[i],
            NULL);
    }
}

```

---

# 7. Thread Pool Improvements

Production systems add:

## Work Stealing

Threads steal tasks from others.

Used in:

- JVM
- Go runtime
- Task schedulers

---

## Priority Queue

Execute important jobs first.

---

## Dynamic Scaling

Increase workers during load.

---

## CPU Affinity

Pin threads to CPUs.

---

# 8. Producer Consumer Example Flow

```
Producer Thread

       |
       |
       v

Circular Queue

       |
       |

Consumer Thread

```

---

# 9. Interview Follow-up Questions

## Q1. Why use condition variable instead of polling?

Polling:

- Wastes CPU

Condition variable:

- Sleeps until event occurs

---

## Q2. Why circular buffer?

Advantages:

- Fixed memory
- Fast
- No fragmentation

---

## Q3. Thread pool vs creating threads?

Thread pool:

- Lower latency
- Better resource control
- Reuses threads

---

## Q4. What happens if worker crashes?

Production design:

- Detect failure
- Restart worker
- Preserve task state

---

# 10. High Performance Improvements

For systems like NetApp:

Use:

- Lock-free queues
- Per-thread queues
- Batch processing
- CPU cache alignment
- NUMA awareness

---

# Next Part

## Part 13

Will cover:

1. Complete LRU cache implementation
2. Hash table implementation
3. Memory ownership rules
4. Interview-level testing strategy
5. Production C coding practices

