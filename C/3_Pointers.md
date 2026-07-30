# C Pointers — Compact Interview Notes (with Examples)

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

```c
int x = 25;
int *p = &x;          // p stores the address of x

printf("%d\n", x);              // 25        (direct access)
printf("%p\n", (void *)&x);     // e.g. 0x7ffd...  (address of x)
printf("%p\n", (void *)p);      // same address as &x
printf("%d\n", *p);             // 25        (dereference: value at that address)

*p = 99;                        // modifies x indirectly
printf("%d\n", x);               // 99

int *wild;             // wild pointer — no initialization
// *wild = 5;          // UB: garbage address

int *np = NULL;
if (np != NULL) *np = 1;        // safely skipped, np is NULL

void *vp = &x;
// printf("%d", *vp);            // ERROR: can't dereference void*
printf("%d\n", *(int *)vp);      // 99, correct after cast

printf("%zu\n", sizeof(int *));    // 8 (64-bit)
printf("%zu\n", sizeof(double *)); // 8 (64-bit) — same regardless of type
```

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

```c
int arr[] = {10, 20, 30, 40, 50};
int *p = arr;                    // p -> arr[0]

printf("%d\n", *p);              // 10
p++;                              // moves by sizeof(int) = 4 bytes
printf("%d\n", *p);               // 20

printf("%d\n", *(p + 2));         // 40  (arr[3])

printf("%d\n", *p++);             // 20 -> prints current (20), THEN p advances
printf("%d\n", *p);                // 30 (p now points here)

printf("%d\n", *++p);              // advances FIRST -> points to 40, prints 40

int a = 5;
(*p) = a;                          // (*p)++ would increment the VALUE, not p

int arr2[10];
int *x = &arr2[8], *y = &arr2[3];
printf("%td\n", x - y);            // 5 (elements apart, not 20 bytes)

int *end = arr + 5;                // one-past-the-end: legal to hold
// *end;                           // ILLEGAL to dereference
```

## 3. Arrays vs Pointers
- An array is **not** a pointer; in most expressions its name **decays** to `&arr[0]` (a pointer to its first element).
- Decay does **NOT** happen with: `sizeof(arr)`, `&arr`, `_Alignof`, or string-literal array initialization.
- `sizeof(arr)` = total bytes of whole array (`n × sizeof(type)`); `sizeof(p)` = pointer size only (8 on 64-bit).
- Function parameter `void f(int arr[])` is identical to `void f(int *arr)` — the array always decays when passed; `sizeof(arr)` inside such a function gives the pointer size, not the array size. So array functions need an explicit size parameter.
- Arrays can't be reassigned (`arr = arr+1` is a compile error) or incremented — fixed base address. Pointers are variables and can be reassigned/incremented.
- `arr[i]` ≡ `*(arr + i)` ≡ `i[arr]` (commutative addition; never write `i[arr]` in real code).
- `arr` and `&arr` print the same address but differ in **type**: `arr` decays to `int *`, `&arr` is `int (*)[N]` (pointer to the whole array) — arithmetic on `&arr` jumps by the whole array's size, not one element.
- `char name[] = "John"` creates a mutable array (with a `\0`); `char *name = "John"` points to a **read-only** string literal — modifying it is UB.

```c
int arr[5] = {1,2,3,4,5};

printf("%zu\n", sizeof(arr));         // 20  (whole array, 5 * 4 bytes)
int *p = arr;
printf("%zu\n", sizeof(p));            // 8   (just a pointer)

void printSize(int a[]) {
    printf("%zu\n", sizeof(a));         // 8 — decayed to pointer, NOT 20
}
printSize(arr);

printf("%d\n", arr[2]);                 // 30 -> here it's arr[2]=3
printf("%d\n", *(arr + 2));             // same: 3
printf("%d\n", 2[arr]);                  // also 3 (valid, but never write this)

// arr = arr + 1;                       // ERROR: array can't be reassigned
p = p + 1;                                // fine: pointer can move

printf("%p\n", (void *)arr);              // same address...
printf("%p\n", (void *)&arr);             // ...but different type: int(*)[5]
// arr+1 moves 4 bytes; &arr+1 would move 20 bytes (whole array)

char mutable_str[] = "John";
mutable_str[0] = 'X';                     // OK

char *literal_str = "John";
// literal_str[0] = 'X';                  // UB: modifying string literal
```

## 4. Pointer to Pointer (`int **`)
- `int **pp = &p;` stores the address of a pointer. `*pp` → the pointer `p`; `**pp` → the actual value.
- Needed whenever a function must modify the caller's pointer itself (not just the pointee).
- Dynamic 2D array: array of row-pointers, each `malloc`'d separately. `matrix[i][j]` ≡ `*(*(matrix+i)+j)`. Free each row, then the row-pointer array.
- `char **argv` is the decayed form of `char *argv[]` — an array of string pointers.
- `int ***` and beyond are legal but rare (compilers/OS-level code).

```c
int x = 10;
int *p = &x;
int **pp = &p;

printf("%d\n", **pp);          // 10 -> *pp is p, **pp is x's value
**pp = 500;
printf("%d\n", x);              // 500

void allocate(int **p) { *p = malloc(sizeof(int)); }
int *ptr = NULL;
allocate(&ptr);                 // must pass &ptr, not ptr, to modify caller's pointer
*ptr = 42;
printf("%d\n", *ptr);            // 42
free(ptr);

// 2D dynamic array
int rows = 2, cols = 3;
int **matrix = malloc(rows * sizeof(int *));
for (int i = 0; i < rows; i++)
    matrix[i] = malloc(cols * sizeof(int));
matrix[1][2] = 7;
printf("%d\n", *(*(matrix + 1) + 2));   // 7, same as matrix[1][2]
for (int i = 0; i < rows; i++) free(matrix[i]);
free(matrix);
```

## 5. Function Pointers
- Declaration: `return_type (*fp)(params);` — parentheses around `*fp` are mandatory (`int *fp(int,int)` instead declares a function returning `int *`, not a function pointer).
- `fp = funcName;` (same as `fp = &funcName`). Call with `fp(args)` or `(*fp)(args)` — equivalent.
- **Callback**: a function passed as an argument and invoked later (e.g., `qsort`'s comparator, GUI event handlers, `struct` of driver ops in the Linux kernel).
- Array of function pointers = **jump table** — replaces long `switch`/`if-else` chains; used for dispatch tables, state machines, drivers.
- Functions cannot return functions, only **pointers to functions**.
- Use `typedef` to simplify complex declarations.

```c
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int (*fp)(int, int) = add;      // parentheses around *fp are required
printf("%d\n", fp(5, 3));        // 8
printf("%d\n", (*fp)(5, 3));     // 8, equivalent call syntax

fp = sub;
printf("%d\n", fp(5, 3));         // 2

// Jump table
int (*ops[])(int, int) = { add, sub };
printf("%d\n", ops[1](10, 4));    // 6, calls sub(10,4)

// Callback example
void execute(void (*task)(void)) { task(); }
void hello(void) { printf("Hello\n"); }
execute(hello);                    // "Hello"

typedef int (*Operation)(int, int);
Operation op2 = add;                // same as int (*op2)(int,int) = add;
```

## 6. Advanced Declarations
- Read declarations from the variable name **outward**, respecting parentheses.
- `int (*p)[5]` → **pointer to an array** of 5 ints (one pointer; `p++` jumps by 20 bytes, i.e. the whole array).
- `int *p[5]` → **array of 5 pointers** to int (five separate addresses) — commonly used for arrays of strings (`char *names[] = {...}`).
- `int *(*fp)(void)` → pointer to a function taking no args, returning `int *`.
- Functions can't return arrays, but can return pointers. Returning a pointer to a **local (stack) variable** is UB (dangling); returning a pointer to a **static** or heap-allocated variable is safe.

```c
int arr[5] = {1,2,3,4,5};

int (*pArr)[5] = &arr;            // pointer to WHOLE array
printf("%d\n", (*pArr)[2]);        // 3
pArr++;                            // would jump by 20 bytes (past the whole array)

int a=1, b=2, c=3;
int *pArrOfPtrs[3] = {&a, &b, &c}; // array of 3 pointers
printf("%d\n", *pArrOfPtrs[1]);     // 2

char *names[] = {"Alice", "Bob"};    // array of string pointers
printf("%s\n", names[1]);             // Bob

int *getStatic(void) {
    static int val = 100;
    return &val;                       // OK: static lives beyond function return
}
// int *getBad(void) { int x=5; return &x; }  // UB: dangling, x destroyed on return

typedef int *(*FuncReturningPtr)(void);
FuncReturningPtr gf = getStatic;
printf("%d\n", *gf());                 // 100
```

## 7. `const` Pointers
| Declaration | Meaning | Can reassign pointer? | Can modify data? |
|---|---|---|---|
| `const int *p` (= `int const *p`) | pointer to constant int | Yes | No |
| `int * const p` | constant pointer to int | No | Yes |
| `const int * const p` | constant pointer to constant int | No | No |

Trick: read right-to-left from the variable name.

```c
int x = 10, y = 20;

const int *p1 = &x;
p1 = &y;              // OK: pointer can move
// *p1 = 5;           // ERROR: can't modify data through p1

int * const p2 = &x;
*p2 = 5;               // OK: data can change
// p2 = &y;            // ERROR: pointer is constant, can't move

const int * const p3 = &x;
// *p3 = 5;            // ERROR
// p3 = &y;            // ERROR
```

## 8. Dynamic Memory Allocation
- **Stack**: automatic alloc/free, fast, fixed size, scoped to function lifetime.
- **Heap**: manual alloc/free via `malloc`/`calloc`/`realloc`/`free`; flexible size/lifetime; programmer must free it; slower.
- `malloc(size)` → uninitialized memory, returns `void *`; must check for `NULL` (allocation failure).
- `calloc(count, size)` → zero-initialized memory; two-argument version of malloc.
- `realloc(ptr, newSize)` → resizes; may return a **new address** (copies old data over) or fail (`NULL`). Always assign to a **temporary pointer** first — direct reassignment risks losing the original block on failure (leak).
- `free(ptr)` releases heap memory; the pointer variable still holds the old (now dangling) address — set it to `NULL` afterward. `free(NULL)` is a safe no-op.
- **Memory leak**: allocated memory whose only pointer is lost (goes out of scope) before `free()`.
- **Double free**: calling `free()` twice on the same pointer → UB/crash/heap corruption.
- **Use-after-free**: dereferencing a pointer after it's been freed → UB.
- 2D heap array: allocate array of row pointers, then `malloc` each row; free rows first, then the row-pointer array.

```c
int *p = malloc(sizeof(int));
if (p == NULL) { printf("Allocation failed\n"); return 1; }
*p = 100;
printf("%d\n", *p);                 // 100

int *arr = calloc(5, sizeof(int));  // {0,0,0,0,0} — zero-initialized
free(arr);

int *buf = malloc(5 * sizeof(int));
int *tmp = realloc(buf, 10 * sizeof(int));  // resize to 10 ints
if (tmp != NULL) buf = tmp;                  // safe pattern: check before reassigning
free(buf);

int *q = malloc(sizeof(int));
free(q);
q = NULL;           // avoids dangling pointer
free(q);            // safe: free(NULL) is a no-op

// Memory leak example:
void leak(void) {
    int *p = malloc(sizeof(int));
    *p = 10;
}   // p goes out of scope, memory never freed -> leak

// Use-after-free / double-free (both UB, shown for recognition only):
// int *r = malloc(sizeof(int)); free(r); *r = 5;   // use-after-free
// free(r); free(r);                                  // double free
```

## 9. Classic Gotchas (quick answers)
- `*p++` reads then increments; `*++p` increments then reads; `(*p)++` increments the pointed-to value.
- `arr` vs `&arr`: same numeric address, different types (`int*` vs `int(*)[N]`); arithmetic behaves differently.
- `sizeof(arr)` (whole array) vs `sizeof(&arr)`/`sizeof(ptr)` (always pointer size, 8 bytes on 64-bit).
- `p - q` gives element count, not byte count.
- `2[arr]` works (≡ `arr[2]`) because array indexing is just pointer arithmetic — never use this style in real code.
- `void *` needs an explicit cast before dereferencing.
- Returning `&local_var` from a function → dangling pointer; use `static` or heap allocation instead.

```c
int arr[] = {10, 20, 30};
int *p = arr;

printf("%d\n", *p++);   // 10 (reads first, then p moves to arr[1])
printf("%d\n", *p);      // 20
printf("%d\n", *++p);     // 30 (moves first, then reads)

int arr2[10];
printf("%td\n", &arr2[9] - &arr2[2]);   // 7 elements, not 28 bytes

char *str = "ABCDE";
printf("%c\n", 2[str]);                  // 'C', same as str[2] — never write this
```
