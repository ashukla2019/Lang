# C Pointers — Compact Interview Notes

## 1. Pointer Basics
- A pointer is a variable that stores a **memory address**, not data itself.
- `&x` → address of `x`. `*p` → value stored at the address in `p`.
- Declaration: `int *p;` reads "p is a pointer to int." In an expression, `*p` means "value at address."
- Uninitialized pointer = **wild pointer** (garbage address, UB if used).
- `int *p = NULL;` → points to nothing; always check `if (p != NULL)` before dereferencing. Dereferencing NULL → segfault.
- **Dangling pointer**: was valid, now points to freed/out-of-scope memory (e.g., returning `&local_var`, or using `p` after `free(p)`). Fix: set `p = NULL` after `free(p)`.
- `void *`: generic pointer, can hold any type's address, but **cannot be dereferenced** without a cast (compiler doesn't know size to read). Used by `malloc`, `calloc`, `qsort`, `pthread_create`, etc. Pointer arithmetic on `void *` is not standard (GCC extension only).
- Pointer size is **always the same regardless of pointed-to type** — 8 bytes (64-bit) / 4 bytes (32-bit) — because it only stores an address. `sizeof(*p)` (the pointed-to type) is what varies.
- ASLR (Address Space Layout Randomization) is why the same variable's printed address differs between runs.

## 2. Pointer Arithmetic
- `p + n` moves by `n × sizeof(*p)` bytes, not `n` bytes. Compiler multiplies automatically.
  - `char *` → ±1 byte, `short *` → ±2, `int *` → ±4, `double *` → ±8, `struct S *` → ±`sizeof(struct S)`.
- `p++` / `p--`: move to next/previous element.
- `*p++` = `*(p++)` → read current value, **then** advance pointer.
- `*++p` = `*(++p)` → advance pointer **first**, then read.
- `(*p)++` → increments the *value* pointed to, not the pointer.
- Valid ops: `p+n`, `p-n`, `p++`, `p--`, `p==q`, `p<q`, `p-q` (only if both point into the same array or one-past-end).
- `p - q` returns the **number of elements** between them, not bytes (internally: byte difference ÷ `sizeof(type)`).
- Invalid: `p + q` (adding two addresses is meaningless), `p*n`, `p/n`.
- **One-past-the-end** pointer (`arr + size`) is legal to hold/compare but **illegal to dereference**.
- Pointer arithmetic outside the bounds of an allocated object (including past a freed/OOB pointer) is UB.

## 3. Arrays vs Pointers
- An array is **not** a pointer; in most expressions its name **decays** to `&arr[0]` (a pointer to its first element).
- Decay does **NOT** happen with: `sizeof(arr)`, `&arr`, `_Alignof`, or string-literal array initialization.
- `sizeof(arr)` = total bytes of whole array (`n × sizeof(type)`); `sizeof(p)` = pointer size only (8 on 64-bit).
- Function parameter `void f(int arr[])` is identical to `void f(int *arr)` — the array always decays when passed; `sizeof(arr)` inside such a function gives the pointer size, not the array size. So array functions need an explicit size parameter.
- Arrays can't be reassigned (`arr = arr+1` is a compile error) or incremented — fixed base address. Pointers are variables and can be reassigned/incremented.
- `arr[i]` ≡ `*(arr + i)` ≡ `i[arr]` (commutative addition; never write `i[arr]` in real code).
- `arr` and `&arr` print the same address but differ in **type**: `arr` decays to `int *`, `&arr` is `int (*)[N]` (pointer to the whole array) — arithmetic on `&arr` jumps by the whole array's size, not one element.
- `char name[] = "John"` creates a mutable array (with a `\0`); `char *name = "John"` points to a **read-only** string literal — modifying it is UB.

## 4. Pointer to Pointer (`int **`)
- `int **pp = &p;` stores the address of a pointer. `*pp` → the pointer `p`; `**pp` → the actual value.
- Needed whenever a function must modify the caller's pointer itself (not just the pointee):
  ```c
  void allocate(int **p) { *p = malloc(sizeof(int)); }
  allocate(&ptr);   // ptr now points to new heap memory
  ```
  Passing a plain `int *` only lets you modify the caller's *data*, not repoint the caller's pointer, since the pointer is passed by value.
- Dynamic 2D array: array of row-pointers, each `malloc`'d separately. `matrix[i][j]` ≡ `*(*(matrix+i)+j)`. Free each row, then the row-pointer array.
- `char **argv` is the decayed form of `char *argv[]` — an array of string pointers.
- `int ***` and beyond are legal but rare (compilers/OS-level code).

## 5. Function Pointers
- Declaration: `return_type (*fp)(params);` — parentheses around `*fp` are mandatory (`int *fp(int,int)` instead declares a function returning `int *`, not a function pointer).
- `fp = funcName;` (same as `fp = &funcName`). Call with `fp(args)` or `(*fp)(args)` — equivalent.
- **Callback**: a function passed as an argument and invoked later (e.g., `qsort`'s comparator, GUI event handlers, `struct` of driver ops in the Linux kernel).
- Array of function pointers = **jump table**, e.g. `int (*ops[])(int,int) = {add, sub, mul};` then `ops[choice](a,b)` — replaces long `switch`/`if-else` chains; used for dispatch tables, state machines, drivers.
- Functions cannot return functions, only **pointers to functions**: `int (*getOp(void))(int,int);`
- Use `typedef` to simplify: `typedef int (*Operation)(int,int); Operation fp;`

## 6. Advanced Declarations
- Read declarations from the variable name **outward**, respecting parentheses.
- `int (*p)[5]` → **pointer to an array** of 5 ints (one pointer; `p++` jumps by 20 bytes, i.e. the whole array).
- `int *p[5]` → **array of 5 pointers** to int (five separate addresses) — commonly used for arrays of strings (`char *names[] = {...}`).
- `int *(*fp)(void)` → pointer to a function taking no args, returning `int *`.
- Functions can't return arrays, but can return pointers. Returning a pointer to a **local (stack) variable** is UB (dangling); returning a pointer to a **static** or heap-allocated variable is safe.

## 7. `const` Pointers
| Declaration | Meaning | Can reassign pointer? | Can modify data? |
|---|---|---|---|
| `const int *p` (= `int const *p`) | pointer to constant int | Yes | No |
| `int * const p` | constant pointer to int | No | Yes |
| `const int * const p` | constant pointer to constant int | No | No |

Trick: read right-to-left from the variable name.

## 8. Dynamic Memory Allocation
- **Stack**: automatic alloc/free, fast, fixed size, scoped to function lifetime.
- **Heap**: manual alloc/free via `malloc`/`calloc`/`realloc`/`free`; flexible size/lifetime; programmer must free it; slower.
- `malloc(size)` → uninitialized memory, returns `void *`; must check for `NULL` (allocation failure).
- `calloc(count, size)` → zero-initialized memory; two-argument version of malloc.
- `realloc(ptr, newSize)` → resizes; may return a **new address** (copies old data over) or fail (`NULL`). Always assign to a **temporary pointer** first (`tmp = realloc(...); if (tmp) p = tmp;`) — direct reassignment risks losing the original block on failure (leak).
- `free(ptr)` releases heap memory; the pointer variable still holds the old (now dangling) address — set it to `NULL` afterward. `free(NULL)` is a safe no-op.
- **Memory leak**: allocated memory whose only pointer is lost (goes out of scope) before `free()`.
- **Double free**: calling `free()` twice on the same pointer → UB/crash/heap corruption.
- **Use-after-free**: dereferencing a pointer after it's been freed → UB.
- 2D heap array: allocate array of row pointers, then `malloc` each row; free rows first, then the row-pointer array.

## 9. Classic Gotchas (quick answers)
- `*p++` reads then increments; `*++p` increments then reads; `(*p)++` increments the pointed-to value.
- `arr` vs `&arr`: same numeric address, different types (`int*` vs `int(*)[N]`); arithmetic behaves differently.
- `sizeof(arr)` (whole array) vs `sizeof(&arr)`/`sizeof(ptr)` (always pointer size, 8 bytes on 64-bit).
- `p - q` gives element count, not byte count.
- `2[arr]` works (≡ `arr[2]`) because array indexing is just pointer arithmetic — never use this style in real code.
- `void *` needs an explicit cast before dereferencing.
- Returning `&local_var` from a function → dangling pointer; use `static` or heap allocation instead.
