# Chapter 12 – Command Line Arguments, Environment Variables & Program Startup
# Part 1 – argc, argv & How main() Starts

---

# Contents

1. Program Execution Flow
2. What is main()?
3. Valid Forms of main()
4. argc
5. argv
6. argv Memory Layout
7. Accessing Command-Line Arguments
8. Parsing Numbers
9. Common Interview Questions
10. Best Practices
11. Key Takeaways

---

# 1. Program Execution Flow

One of the most common Linux interview questions is:

> **Does execution start from main()?**

The answer is:

**No.**

Execution starts from a runtime startup routine.

Simplified flow

```
Program Executed

↓

Kernel loads executable

↓

Creates Process

↓

Creates Virtual Memory

↓

Creates Stack

↓

Loads argv

↓

Loads Environment Variables

↓

Calls Runtime Startup

(_start)

↓

C Runtime (CRT)

↓

Calls main()

↓

main() returns

↓

exit()

↓

Cleanup

↓

Kernel destroys process
```

So,

```
main()

is NOT

the first function executed.
```

---

# Linux Startup

```
ELF Executable

↓

Kernel

↓

_start

↓

__libc_start_main()

↓

main()

↓

exit()
```

---

# 2. What is main()?

`main()` is the program's entry point from the perspective of the C language.

The operating system actually calls runtime startup code,

which eventually calls

```
main()
```

---

# 3. Valid Forms of main()

Most common

```c
int main(void)
{
}
```

---

Also valid

```c
int main(int argc, char *argv[])
{
}
```

Equivalent

```c
int main(int argc, char **argv)
{
}
```

Both are identical.

---

Some systems also provide a third parameter

```c
int main(int argc,
         char *argv[],
         char *envp[])
```

but this is **not required by the C standard**.

Portable programs usually use

```c
getenv()
```

instead.

---

# 4. argc

Meaning

```
Argument Count
```

Type

```c
int
```

It contains

```
Number of command-line arguments
```

including the program name.

---

Example

Command

```
./app hello world
```

Then

```
argc = 3
```

Because

```
argv[0]

↓

"./app"

argv[1]

↓

"hello"

argv[2]

↓

"world"
```

---

# Important

Even if no arguments are supplied,

```
argc

is usually

1
```

because

```
argv[0]
```

contains the program name.

---

# 5. argv

Meaning

```
Argument Vector
```

Type

```c
char *argv[]
```

Equivalent

```c
char **argv
```

Each element points to a null-terminated string.

---

Example

Command

```
./calculator 10 20
```

Memory

```
argv

|

|

+--------+

|

v

argv[0]

↓

"./calculator"

argv[1]

↓

"10"

argv[2]

↓

"20"

argv[3]

↓

NULL
```

Notice

```
argv[argc]

↓

NULL
```

This is guaranteed by the C standard.

---

# 6. argv Memory Layout

Suppose

```
./demo apple orange banana
```

Memory

```
Stack

------------------------------------

argv

|

v

+-----+

|  *---------> "./demo"

+-----+

|  *---------> "apple"

+-----+

|  *---------> "orange"

+-----+

|  *---------> "banana"

+-----+

| NULL

------------------------------------
```

Each argument is an independent string.

---

# Accessing Arguments

Example

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}
```

Command

```
./demo one two
```

Output

```
./demo

one

two
```

---

# Access Individual Arguments

Example

```c
printf("%s\n", argv[1]);
```

Command

```
./demo OpenAI
```

Output

```
OpenAI
```

---

# 7. Checking Number of Arguments

Very common interview question.

Example

```c
#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./calc a b\n");
        return 1;
    }

    printf("OK\n");

    return 0;
}
```

Command

```
./calc 10
```

Output

```
Usage: ./calc a b
```

---

# 8. Parsing Numbers

Remember

```
argv

contains strings
```

Not integers.

---

Wrong

```c
int x = argv[1];
```

---

Correct

```c
#include <stdlib.h>

int x = atoi(argv[1]);
```

---

Better

```c
int x = (int)strtol(argv[1], NULL, 10);
```

Why?

`atoi()` cannot detect errors.

`strtol()` provides error checking and handles overflow better.

---

Example

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
        return 1;

    int a = (int)strtol(argv[1], NULL, 10);
    int b = (int)strtol(argv[2], NULL, 10);

    printf("%d\n", a + b);

    return 0;
}
```

Command

```
./calc 12 8
```

Output

```
20
```

---

# 9. Common Interview Questions

---

## Q1

What is

```c
argc
```

Argument count.

---

## Q2

What is

```c
argv
```

Array of pointers to command-line argument strings.

---

## Q3

Why is

```c
argv

type

char **
```

Because it points to an array of character pointers.

```
argv

↓

char *

↓

char
```

---

## Q4

Is

```c
argv[0]
```

always the executable name?

It is **conventionally** the program name or path used to invoke the program. Programs should not rely on it being a specific filename.

---

## Q5

What is

```c
argv[argc]
```

Always

```
NULL
```

---

## Q6

Difference between

```c
char *argv[]

char **argv
```

None.

They are equivalent in function parameters.

---

## Q7

Can command-line arguments be modified?

The strings pointed to by `argv` are generally modifiable in hosted C implementations, but modifying them is rarely useful and may not be portable across all environments. In practice, treat them as input data.

---

# 10. Best Practices

✓ Validate

```c
argc
```

before accessing

```c
argv
```

---

✓ Prefer

```c
strtol()
```

instead of

```c
atoi()
```

---

✓ Print helpful usage messages.

---

✓ Never access

```c
argv[i]
```

without checking

```c
argc
```

---

✓ Remember

```
argv[argc]

↓

NULL
```

---

# Memory Summary

```
main(argc, argv)

argc

↓

3

argv

↓

+--------+

|

v

"./demo"

"100"

"200"

NULL
```

---

# Quick Revision Table

| Item | Meaning |
|------|----------|
| argc | Number of arguments |
| argv | Array of argument strings |
| argv[0] | Program name/path used to invoke the program |
| argv[argc] | NULL |
| argv[i] | ith argument |

---

# Key Takeaways

- Program execution begins in runtime startup code (`_start`), not directly in `main()`.
- `argc` contains the number of command-line arguments, including the program name.
- `argv` is an array of pointers to null-terminated strings.
- `char *argv[]` and `char **argv` are equivalent in function parameters.
- Always validate `argc` before accessing command-line arguments.
- Prefer `strtol()` over `atoi()` for converting numeric arguments because it supports error handling.

---

# Next Part

**Part 2 – Environment Variables (`getenv`, `envp`), Process Environment & Linux Startup**
--------------------------------------------------------------------
# Chapter 12 – Command Line Arguments, Environment Variables & Program Startup
# Part 2 – Environment Variables (getenv, envp) & Process Environment

---

# Contents

1. What are Environment Variables?
2. How Environment Variables are Created
3. Process Environment
4. envp
5. getenv()
6. setenv(), unsetenv(), putenv()
7. Common Environment Variables
8. Environment Memory Layout
9. Child Process Environment
10. Security Considerations
11. Interview Questions
12. Best Practices
13. Key Takeaways

---

# 1. What are Environment Variables?

Environment variables are

```
Name

↓

Value
```

pairs maintained by the operating system.

Example

```
PATH=/usr/bin:/bin

HOME=/home/user

USER=alice

SHELL=/bin/bash
```

They provide configuration information to programs.

---

Examples

Instead of writing

```c
char home[] = "/home/user";
```

Programs simply ask the operating system

```
Where is the user's home directory?
```

The OS provides

```
HOME
```

---

# Common Uses

Environment variables are used for

- Home directory
- Username
- Search path
- Language
- Timezone
- Proxy settings
- Library search paths
- Application configuration

---

# 2. How Environment Variables are Created

Linux Shell

```bash
export NAME=OpenAI
```

Now

```
Current Shell

↓

NAME=OpenAI
```

Every child process started from this shell inherits the environment.

---

Example

```
Terminal

↓

export MODE=DEBUG

↓

Run Program

↓

Program receives

MODE=DEBUG
```

---

# 3. Process Environment

Every process owns its own copy of the environment.

Memory Layout

```
Process

+--------------------+

Text

+--------------------+

Data

+--------------------+

Heap

+--------------------+

Stack

+--------------------+

Arguments

argc

argv

Environment

envp

+--------------------+
```

The kernel places

```
argv

and

environment strings
```

on the initial process stack before the C runtime starts.

---

# Parent → Child

```
Parent Process

↓

fork()

↓

Child Process

↓

Same Environment
```

Initially,

both have identical environment variables.

---

After

```c
setenv(...)
```

inside the child,

only the child changes.

The parent's environment is unaffected.

---

# 4. envp

Some systems pass environment variables directly to `main()`.

Example

```c
int main(int argc,
         char *argv[],
         char *envp[])
{
}
```

Here

```
envp

↓

Array of pointers

↓

Environment Strings
```

Like

```
argv
```

it ends with

```
NULL
```

---

Memory

```
envp

↓

PATH=/usr/bin

↓

HOME=/home/user

↓

USER=alice

↓

NULL
```

---

Important

The third parameter

```c
envp
```

is **not part of the ISO C standard**.

Many Unix-like systems support it,

but portable programs should use

```c
getenv()
```

---

# 5. getenv()

The standard C function

```c
#include <stdlib.h>

char *getenv(const char *name);
```

Returns

```
Pointer

↓

Environment Value
```

or

```
NULL
```

if the variable does not exist.

---

Example

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *home = getenv("HOME");

    if(home)
        printf("%s\n", home);

    return 0;
}
```

Possible Output

```
/home/alice
```

---

Variable Missing

```c
char *x = getenv("XYZ");
```

Result

```
NULL
```

Always check before using the returned pointer.

---

# 6. setenv(), unsetenv(), putenv()

These are POSIX functions (not ISO C).

---

## setenv()

```c
#include <stdlib.h>

setenv("MODE", "DEBUG", 1);
```

Parameters

```
Name

↓

MODE

Value

↓

DEBUG

Overwrite?

↓

1
```

---

Read Again

```c
printf("%s", getenv("MODE"));
```

Output

```
DEBUG
```

---

## unsetenv()

Remove a variable.

```c
unsetenv("MODE");
```

Now

```c
getenv("MODE")
```

returns

```
NULL
```

---

## putenv()

```c
putenv("MODE=DEBUG");
```

This directly installs the supplied string into the environment.

Because of its ownership semantics,

`setenv()` is generally preferred in new code.

---

# 7. Common Environment Variables

Linux

| Variable | Purpose |
|----------|----------|
| HOME | User's home directory |
| PATH | Executable search path |
| USER | Login name |
| SHELL | Login shell |
| PWD | Current working directory |
| LANG | Language/locale |
| TERM | Terminal type |
| LOGNAME | User login |

---

Example

```c
printf("%s\n", getenv("PATH"));
```

Possible Output

```
/usr/local/bin:/usr/bin:/bin
```

---

# PATH

One of the most important variables.

Suppose

```
PATH

=

/usr/bin:/bin
```

User types

```
gcc
```

Shell searches

```
/usr/bin/gcc

↓

Found

↓

Execute
```

Without

```
PATH
```

the shell would require

```
/usr/bin/gcc
```

every time.

---

# 8. Environment Memory Layout

Initial Stack

```
High Address

----------------------

Environment Strings

----------------------

argv Strings

----------------------

envp[]

----------------------

argv[]

----------------------

argc

----------------------

Low Address
```

The runtime builds

```
argc

argv

envp
```

from this initial stack before calling `main()`.

---

# 9. Child Process Environment

Example

```c
fork();
```

Child receives

```
Complete Copy

↓

Environment
```

---

Then

Child

```c
setenv("MODE", "TEST", 1);
```

Parent

```
MODE

unchanged
```

because each process has its own environment after `fork()`.

---

After exec()

Suppose

```
execve(...)
```

The caller can provide

```
New Environment
```

or pass the existing one.

This is how shells launch programs with customized environments.

---

# 10. Security Considerations

Environment variables come from outside the program.

Never blindly trust them.

---

Example

```c
char *path = getenv("PATH");
```

Validate before use.

---

Sensitive Programs

Examples

- `sudo`
- Setuid executables
- Authentication utilities

often ignore or sanitize certain environment variables to avoid attacks.

---

Variables like

```
LD_PRELOAD

LD_LIBRARY_PATH
```

can influence dynamic linking.

Improper handling can introduce security vulnerabilities.

---

# 11. Frequently Asked Interview Questions

---

## Q1

What is an environment variable?

A name/value pair inherited by a process and used for configuration.

---

## Q2

Difference between

```
argv

and

Environment
```

| argv | Environment |
|-------|-------------|
| Command-line input | Process configuration |
| Passed by the user when launching the program | Inherited from the parent process (or supplied to `exec`) |
| Usually changes each invocation | Often remains constant across launches |

---

## Q3

Which function reads environment variables?

```c
getenv()
```

---

## Q4

What happens if

```c
getenv()
```

cannot find a variable?

Returns

```
NULL
```

---

## Q5

Can a child modify the parent's environment?

No.

Each process maintains its own environment.

---

## Q6

Is

```c
envp
```

standard C?

No.

It is a common extension on Unix-like systems.

---

## Q7

How does a child process receive environment variables?

Through

```
fork()

↓

Inherited copy
```

or by a new environment supplied to `execve()`.

---

## Q8

What is PATH?

A list of directories searched for executable programs.

---

# Practical Example

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const char *user = getenv("USER");
    const char *home = getenv("HOME");

    if(user)
        printf("User : %s\n", user);

    if(home)
        printf("Home : %s\n", home);

    return 0;
}
```

Possible Output

```
User : alice

Home : /home/alice
```

---

# Best Practices

✓ Always check the return value of `getenv()` for `NULL`.

✓ Prefer `getenv()` over the non-standard `envp` parameter for portable programs.

✓ Use `setenv()` instead of `putenv()` in new POSIX code.

✓ Never trust environment variables in security-sensitive applications.

✓ Remember that environment variables belong to the process, not the entire system.

---

# Quick Revision Table

| Function | Purpose |
|----------|----------|
| `getenv()` | Read environment variable |
| `setenv()` | Create/update variable (POSIX) |
| `unsetenv()` | Remove variable (POSIX) |
| `putenv()` | Install environment string (POSIX, legacy style) |

---

# Key Takeaways

- Every process has its own environment consisting of name/value pairs.
- Environment variables are inherited from the parent process and are commonly used for configuration.
- `getenv()` is the standard C function for retrieving environment variables.
- `envp` is a common Unix extension but is not part of ISO C.
- `fork()` copies the environment, while `execve()` can replace it with a new one.
- Environment variables should be treated as untrusted input in security-sensitive software.

---

# Next Part

## **Part 3 – Process Startup, `_start`, CRT, `exit()`, `atexit()`, and Program Termination**

Topics include:

- What happens before `main()`
- `_start`
- `__libc_start_main()`
- C Runtime (CRT)
- `exit()`, `_exit()`, `abort()`
- `atexit()` handlers
- Process cleanup
- Complete Linux program lifecycle
- 50+ interview questions
- ---------------------------------------------------------------------------------
# Chapter 12 – Command Line Arguments, Environment Variables & Program Startup
# Part 3 – Process Startup, C Runtime (CRT), _start, exit() & Program Termination

---

# Contents

1. Complete Program Startup Flow
2. What Happens Before main()?
3. ELF Loader
4. Process Memory Creation
5. _start
6. C Runtime (CRT)
7. __libc_start_main()
8. Calling main()
9. Returning from main()
10. exit(), _exit(), abort()
11. atexit()
12. Process Cleanup
13. Complete Program Lifecycle
14. Interview Questions
15. Best Practices
16. Key Takeaways

---

# 1. Complete Program Startup Flow

Many interviewers ask

> Explain everything that happens after executing

```
./program
```

Complete Flow

```
User

↓

Shell

↓

fork()

↓

Child Process

↓

execve()

↓

Kernel

↓

Load ELF

↓

Create Process

↓

Virtual Memory

↓

Stack

↓

Heap

↓

Arguments

↓

Environment

↓

Dynamic Linker

↓

_start

↓

C Runtime (CRT)

↓

__libc_start_main()

↓

main()

↓

return

↓

exit()

↓

Cleanup

↓

Kernel destroys process
```

Understanding this flow is useful for Linux system programming interviews.

---

# 2. What Happens Before main()?

Many beginners think

```
main()

↓

Program Starts
```

Wrong.

Actually

```
Kernel

↓

Runtime Startup

↓

main()
```

Several important initialization steps occur before your code executes.

---

# 3. ELF Loader

Linux executables usually use the

```
ELF

Executable and Linkable Format
```

When

```
./program
```

is executed,

the kernel

- Opens the executable
- Reads the ELF header
- Maps program segments
- Creates the process address space

---

Typical Memory

```
High Address

Stack

↓

Shared Libraries

↓

Heap

↓

BSS

↓

Data

↓

Read-only Data

↓

Text

Low Address
```

---

# 4. Process Memory Creation

Kernel prepares

- Virtual Address Space
- Stack
- Heap
- Program Segments
- File Descriptors
- Signal Handlers
- Environment
- Command-Line Arguments

---

Memory

```
+----------------------+

Stack

↓

argc

↓

argv

↓

envp

+----------------------+

Heap

+----------------------+

BSS

+----------------------+

Initialized Data

+----------------------+

Read-only Data

+----------------------+

Text

+----------------------+
```

After this,

execution still has **not** reached `main()`.

---

# 5. _start

Actual execution begins here.

```
_start
```

is supplied by the runtime startup code (CRT), not written by the programmer.

Its responsibilities include

- Preparing arguments
- Initializing runtime support
- Invoking the C runtime

Simplified

```
Kernel

↓

_start
```

---

You normally never write

```c
_start()
```

yourself.

---

# 6. C Runtime (CRT)

CRT means

```
C Runtime
```

It initializes the C execution environment.

Examples

- Runtime initialization
- Standard library setup
- Constructor execution (for C++ and certain runtime components)
- Preparing arguments
- Calling `main()`

Think of CRT as the bridge between

```
Operating System

↓

Your C Program
```

---

# 7. __libc_start_main()

On glibc-based Linux systems,

`_start` eventually calls

```
__libc_start_main()
```

This function

- Completes libc initialization
- Invokes constructors
- Calls `main()`
- Handles program termination

Simplified Flow

```
_start

↓

__libc_start_main()

↓

main()
```

---

# 8. Calling main()

Finally

```
main(argc, argv)
```

is called.

Example

```c
int main(int argc,
         char *argv[])
{
    printf("Hello\n");

    return 0;
}
```

Everything before this point was handled by

- Kernel
- Runtime Startup
- C Library

---

# 9. Returning from main()

Example

```c
return 0;
```

Many people think

```
Program Ends
```

Actually

```
return

↓

exit()

↓

Cleanup

↓

Kernel
```

Returning from `main()` is equivalent to calling

```c
exit(0);
```

---

# 10. exit()

Prototype

```c
#include <stdlib.h>

void exit(int status);
```

Example

```c
exit(0);
```

Status

```
0

↓

Success
```

Non-zero

↓

Error.

---

What does `exit()` do?

- Calls registered `atexit()` handlers
- Flushes and closes standard I/O streams
- Performs C library cleanup
- Returns the status to the operating system

---

# Example

```c
#include <stdlib.h>

int main(void)
{
    exit(0);
}
```

---

# 11. _exit()

Prototype

```c
#include <unistd.h>

void _exit(int status);
```

Unlike

```
exit()
```

it

- Does **not** call `atexit()` handlers
- Does **not** flush stdio buffers

It terminates the process immediately.

---

Common Usage

After

```
fork()
```

if the child must terminate without running the parent's buffered I/O cleanup.

---

Comparison

| exit() | _exit() |
|---------|----------|
| Flushes stdio | No |
| Calls atexit() | No |
| Library cleanup | No |
| Immediate termination | Yes |

---

# Example

```c
pid_t pid = fork();

if(pid == 0)
{
    _exit(0);
}
```

---

# 12. abort()

Prototype

```c
#include <stdlib.h>

void abort(void);
```

Purpose

Terminate the program abnormally.

Usually

- Raises `SIGABRT`
- Produces abnormal termination
- May generate a core dump (system dependent)

---

Example

```c
if(ptr == NULL)
{
    abort();
}
```

---

Comparison

| Function | Purpose |
|-----------|----------|
| exit() | Normal termination |
| _exit() | Immediate termination |
| abort() | Abnormal termination |

---

# 13. atexit()

Prototype

```c
#include <stdlib.h>

int atexit(void (*func)(void));
```

Registers a function that executes during normal termination.

---

Example

```c
#include <stdio.h>
#include <stdlib.h>

void cleanup(void)
{
    printf("Cleaning...\n");
}

int main(void)
{
    atexit(cleanup);

    printf("Main\n");

    return 0;
}
```

Output

```
Main

Cleaning...
```

---

Multiple Handlers

```c
atexit(f1);

atexit(f2);

atexit(f3);
```

Execution order

```
f3

↓

f2

↓

f1
```

LIFO (Last In, First Out)

---

Typical Uses

- Closing log files
- Freeing global resources
- Saving configuration
- Cleaning temporary files

---

# 14. Process Cleanup

Normal termination

```
main()

↓

return

↓

exit()

↓

Flush stdio

↓

Run atexit()

↓

Close files

↓

Free process resources

↓

Kernel destroys process
```

The operating system also reclaims

- Virtual memory
- Open file descriptors
- Kernel objects owned by the process

---

# 15. Complete Lifecycle

```
Shell

↓

fork()

↓

Child

↓

execve()

↓

Kernel

↓

ELF Loader

↓

Memory Creation

↓

Dynamic Linker

↓

_start

↓

CRT

↓

__libc_start_main()

↓

main()

↓

return

↓

exit()

↓

atexit()

↓

Cleanup

↓

Kernel destroys process
```

---

# 16. Frequently Asked Interview Questions

---

## Q1

Does execution begin at

```c
main()
```

No.

Execution begins at

```
_start
```

after the kernel loads the executable.

---

## Q2

Who calls

```c
main()
```

The C runtime,

typically through `__libc_start_main()` on glibc-based Linux systems.

---

## Q3

What happens before

```c
main()
```

- ELF loading
- Process creation
- Memory mapping
- Runtime initialization
- Dynamic linking (when applicable)
- C runtime initialization

---

## Q4

Difference between

```
exit()

_exit()
```

| exit() | _exit() |
|---------|----------|
| Flushes stdio | No |
| Calls atexit() | No |
| Normal cleanup | No |
| Library cleanup | No |

---

## Q5

Difference between

```
exit()

abort()
```

`exit()`

Normal termination.

`abort()`

Abnormal termination by raising `SIGABRT`.

---

## Q6

What is

```
atexit()
```

Registers cleanup functions executed during normal program termination.

---

## Q7

How are multiple

```
atexit()
```

functions executed?

Reverse registration order (LIFO).

---

## Q8

What happens after

```
return 0;
```

Equivalent to

```c
exit(0);
```

---

## Q9

Who destroys the process?

The operating system kernel.

---

# Best Practices

✓ Return from `main()` or use `exit()` for normal termination.

✓ Use `_exit()` in child processes after `fork()` when appropriate.

✓ Register cleanup handlers using `atexit()` for global cleanup tasks.

✓ Do not rely on `atexit()` handlers after `abort()` or abnormal termination.

✓ Keep cleanup functions simple and reliable.

---

# Quick Revision Table

| Component | Purpose |
|------------|----------|
| `_start` | Runtime entry point |
| CRT | Initializes C runtime |
| `__libc_start_main()` | Calls `main()` (glibc) |
| `main()` | User program |
| `exit()` | Normal termination |
| `_exit()` | Immediate termination |
| `abort()` | Abnormal termination |
| `atexit()` | Register cleanup handlers |

---

# Complete Startup & Shutdown Diagram

```
User

↓

Shell

↓

fork()

↓

execve()

↓

Kernel

↓

ELF Loader

↓

Memory Setup

↓

Dynamic Linker

↓

_start

↓

CRT

↓

__libc_start_main()

↓

main()

↓

return

↓

exit()

↓

atexit()

↓

Cleanup

↓

Kernel destroys process
```

---

# Key Takeaways

- Program execution begins at `_start`, **not** at `main()`.
- The kernel loads the ELF executable, creates the process, and prepares its address space before user code runs.
- The C Runtime (CRT) initializes the execution environment and eventually calls `main()`.
- Returning from `main()` is equivalent to calling `exit()` with the same return value.
- `exit()` performs normal cleanup, while `_exit()` terminates immediately without C library cleanup.
- `abort()` terminates the program abnormally by raising `SIGABRT`.
- `atexit()` allows registration of cleanup functions that execute in reverse order of registration.

---

