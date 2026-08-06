# Advanced C Interview Solutions - Part 8

# Linux System Programming + Networking Basics

Topics covered:

1. Linux process model
2. File descriptors
3. System calls
4. mmap()
5. epoll()
6. Socket programming
7. Zero-copy networking
8. Debugging tools

---

# 1. Linux Process Model

A process contains:

```
+------------------+
| Stack            |
+------------------+
| Heap             |
+------------------+
| BSS              |
+------------------+
| Data             |
+------------------+
| Text             |
+------------------+

```

---

# Process Creation

Main APIs:

```
fork()
exec()
wait()

```

---

# 2. fork()

Creates a new process.

Example:

```c
#include <unistd.h>
#include <stdio.h>


int main()
{
    pid_t pid;


    pid = fork();


    if(pid == 0)
    {
        printf("Child\n");
    }
    else
    {
        printf("Parent\n");
    }


    return 0;
}

```

---

# fork() Behavior

Before:

```
Parent

Memory

```

After:

```
Parent

Memory copy-on-write


Child

Memory copy-on-write

```

---

# Copy-On-Write

Initially:

```
Parent
 |
 +---- Page A


Child
 |
 +---- Same Page A

```

When child modifies:

```
Parent -> Page A

Child  -> New Page

```

---

# 3. exec()

Replaces current process image.

Example:

```c
execl(
"/bin/ls",
"ls",
NULL);

```

After exec:

Old program:

```
Removed

```

New program:

```
Loaded

```

---

# 4. wait()

Parent waits for child.

```c
wait(NULL);

```

Used to:

- Collect exit status
- Prevent zombie processes

---

# 5. File Descriptors

Linux represents resources as integers.

Example:

```
0 stdin

1 stdout

2 stderr

```

---

# open()

Example:

```c
int fd =
open(
"file.txt",
O_RDONLY);

```

Returns:

```
file descriptor

```

---

# read()

```c
read(
fd,
buffer,
size);

```

---

# write()

```c
write(
fd,
buffer,
size);

```

---

# close()

```c
close(fd);

```

---

# File Descriptor Table

Process:

```
FD Table


0 ---> Terminal

1 ---> Terminal

2 ---> Terminal

3 ---> file.txt

```

---

# 6. mmap()

## Purpose

Maps files or memory into process address space.

---

# Traditional Read

```
Disk

 |

read()

 |

Kernel buffer

 |

User buffer

```

Two copies.

---

# mmap()

```
Disk

 |

Memory mapping

 |

User address space

```

Fewer copies.

---

# mmap Example

```c
#include <sys/mman.h>


void *addr;


addr = mmap(
NULL,
4096,
PROT_READ|PROT_WRITE,
MAP_PRIVATE|MAP_ANONYMOUS,
-1,
0);

```

---

# mmap Uses

- Shared memory
- Memory allocators
- Databases
- File mapping

---

# munmap()

Release mapping.

```c
munmap(addr,4096);

```

---

# 7. epoll()

## Problem

select():

```
Check every socket

O(n)

```

For thousands of connections:

Slow.

---

# epoll

Event based:

```
Kernel monitors sockets

Returns only ready ones

```

Complexity:

```
O(active events)

```

---

# epoll Workflow

```
Create epoll

       |

Register sockets

       |

Wait events

       |

Process ready sockets

```

---

# Create epoll

```c
int epfd =
epoll_create1(0);

```

---

# Add Socket

```c
struct epoll_event event;


event.events =
EPOLLIN;


event.data.fd =
sockfd;


epoll_ctl(
epfd,
EPOLL_CTL_ADD,
sockfd,
&event);

```

---

# Wait Events

```c
epoll_wait(
epfd,
events,
MAX_EVENTS,
timeout);

```

---

# epoll Interview Points

## Level Triggered

Default.

Event remains until handled.

---

## Edge Triggered

Notify only on transition.

Requires:

```
non-blocking IO

```

---

# 8. Socket Programming

Basic TCP server:

```
socket()

 |

bind()

 |

listen()

 |

accept()

 |

read/write()

```

---

# Create Socket

```c
int fd =
socket(
AF_INET,
SOCK_STREAM,
0);

```

---

# Bind

```c
bind(
fd,
address,
sizeof(address));

```

---

# Listen

```c
listen(fd,10);

```

---

# Accept

```c
int client =
accept(
fd,
NULL,
NULL);

```

---

# Receive Data

```c
read(
client,
buffer,
size);

```

---

# Send Data

```c
write(
client,
buffer,
size);

```

---

# TCP Server Model

Simple:

```
One thread per client

```

Better:

```
epoll

+

thread pool

```

---

# 9. Zero-Copy Networking

## Problem

Traditional path:

```
Disk

 |

Kernel buffer

 |

User buffer

 |

Socket buffer

```

Multiple copies.

---

# Zero Copy

Avoid unnecessary copying.

Techniques:

## sendfile()

```c
sendfile(
socket,
file,
offset,
size);

```

---

## mmap()

Map file directly.

---

## DMA

Hardware transfers directly.

---

# Used In

- Web servers
- Storage systems
- High performance networking

---

# 10. Debugging Tools

---

# gdb

Debugger.

Common commands:

Start:

```
gdb ./program

```

Run:

```
run

```

Breakpoint:

```
break main

```

Step:

```
next

```

Inspect:

```
print variable

```

Backtrace:

```
bt

```

---

# Valgrind

Memory debugging.

Finds:

- Memory leaks
- Invalid access
- Double free

Example:

```
valgrind ./program

```

---

# Address Sanitizer

Compiler option:

```bash
gcc -fsanitize=address test.c

```

Detects:

- Buffer overflow
- Use after free
- Stack corruption

---

# strace

Shows system calls.

Example:

```
strace ./program

```

Output:

```
open()

read()

write()

close()

```

---

# lsof

Lists open files.

Example:

```
lsof -p PID

```

Shows:

- Files
- Sockets
- Pipes

---

# Senior Interview Questions

## Q1. Difference between mmap and read?

read:

- Explicit copy
- Kernel buffer involved

mmap:

- Memory mapping
- Lazy page loading

---

## Q2. Why epoll is faster than select?

select:

- Copies fd set
- Checks all descriptors

epoll:

- Kernel maintained interest list
- Returns ready descriptors

---

## Q3. What happens during context switch?

CPU saves:

- Registers
- Program counter
- Stack pointer

Loads next process/thread state.

---

## Q4. Why use non-blocking sockets?

To support:

- Thousands of connections
- Event-driven servers

---

# Next Part

## Part 9

Will cover:

1. Operating System internals
2. Virtual memory
3. Page tables
4. TLB
5. Scheduling
6. Mutex vs semaphore vs spinlock
7. Deadlock handling
8. Linux kernel concepts

