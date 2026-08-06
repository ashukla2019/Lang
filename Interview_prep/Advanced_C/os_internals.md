# Advanced C Interview Notes - Part 9

# Operating System Internals

Topics covered:

1. Virtual memory
2. Page tables
3. TLB
4. Page faults
5. Memory allocation
6. CPU scheduling
7. Mutex vs semaphore vs spinlock
8. Deadlocks
9. Linux kernel concepts

---

# 1. Virtual Memory

## Why Virtual Memory?

Problems with physical memory:

- Limited RAM
- Process isolation
- Memory sharing
- Security

Virtual memory provides:

- Each process gets its own address space
- Memory protection
- Efficient memory usage

---

# Address Translation

CPU generates:

```
Virtual Address

        |

        v

Memory Management Unit (MMU)

        |

        v

Physical Address

```

---

# Virtual Address Layout

Example:

```
High Address

+----------------+
| Stack          |
|      Down      |
+----------------+
|                |
| Shared Memory  |
|                |
+----------------+
| Heap           |
|      Up        |
+----------------+
| BSS            |
+----------------+
| Data           |
+----------------+
| Text           |
+----------------+

Low Address

```

---

# 2. Pages and Frames

Virtual memory is divided into:

```
Pages

```

Physical memory is divided into:

```
Frames

```

Example:

```
Virtual:

Page 0
Page 1
Page 2


Physical:

Frame 5
Frame 8
Frame 12

```

Mapping:

```
Page 0 ---> Frame 5

Page 1 ---> Frame 8

```

---

# 3. Page Table

Stores mapping:

```
Virtual Page -> Physical Frame

```

Example:

```
+---------+---------+
| Page    | Frame   |
+---------+---------+
| 0       | 5       |
| 1       | 8       |
| 2       | 12      |
+---------+---------+

```

---

# Page Table Entry Contains

- Frame number
- Valid bit
- Dirty bit
- Access permissions
- Present bit

---

# 4. Multi-Level Page Tables

Problem:

Single page table consumes huge memory.

Solution:

Hierarchical tables.

Example:

```
Virtual Address

+------+-------+------+
| P1   | P2    | Off  |
+------+-------+------+

   |
   v

Page Directory

   |
   v

Page Table

   |
   v

Physical Frame

```

---

# 5. TLB (Translation Lookaside Buffer)

## Problem

Every memory access requires:

1. Access page table
2. Access actual memory

Two memory accesses.

---

# Solution

Cache page table entries.

```
CPU

 |

TLB

 |

Memory

```

---

# TLB Hit

Entry found:

```
Fast access

```

---

# TLB Miss

Need:

```
Page table lookup

```

then update TLB.

---

# 6. Page Fault

Occurs when required page is not in RAM.

Example:

```
Process accesses page

        |

        v

Not present in RAM

        |

        v

Page Fault

```

---

# Page Fault Handling

Steps:

1. CPU traps to kernel.
2. OS checks validity.
3. Find free frame.
4. Load page from disk.
5. Update page table.
6. Resume execution.

---

# Types of Page Fault

## Minor Fault

Page already in memory.

Example:

```
Shared library mapping

```

---

## Major Fault

Requires disk IO.

Slow.

---

# 7. Copy-On-Write

Used by:

```
fork()

```

Before modification:

```
Parent
 |
 +---- Same Page
 |
Child

```

After modification:

```
Parent ---> Page A

Child  ---> New Page

```

Benefits:

- Faster fork
- Saves memory

---

# 8. Memory Allocation

## Stack Allocation

Example:

```c
void func()
{
    int x;
}

```

Characteristics:

- Automatic
- Fast
- Limited size

---

## Heap Allocation

Example:

```c
int *p;

p = malloc(sizeof(int));

```

Characteristics:

- Dynamic
- Manual management
- Fragmentation possible

---

# 9. CPU Scheduling

The OS decides:

```
Which process runs next?

```

---

# Scheduling Algorithms

## First Come First Serve

FCFS

Simple.

Problem:

Long jobs block short jobs.

---

## Round Robin

Each process gets:

```
Time slice

```

Example:

```
P1 -> P2 -> P3 -> P1

```

Good for interactive systems.

---

## Priority Scheduling

Higher priority runs first.

Problem:

Starvation.

Solution:

Aging.

---

# 10. Context Switching

Switching CPU from one task to another.

Steps:

Save:

- Registers
- Program counter
- Stack pointer

Restore:

- New task state

---

# Context Switch Cost

Includes:

- Cache pollution
- TLB effects
- Register save/restore

---

# 11. Process vs Thread

| Process | Thread |
|-|-|
| Own address space | Shares process memory |
| Heavyweight | Lightweight |
| IPC required | Shared variables |
| More isolation | Faster communication |

---

# 12. Mutex

Mutex provides:

```
Only one owner

```

Example:

```c
pthread_mutex_lock();

critical section

pthread_mutex_unlock();

```

---

# 13. Semaphore

Counter-based synchronization.

Example:

```
Available resources = 5

Semaphore = 5

```

Operations:

wait:

```
decrement

```

signal:

```
increment

```

---
