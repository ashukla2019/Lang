# Dynamic Memory Allocation and User Input in C and C++

A practical guide to dynamically allocating memory and taking user input for:

- `char`
- `char *`
- `char **`
- 1D character arrays
- 2D character arrays
- `int`
- `int *`
- `int **`
- 1D integer arrays
- 2D integer arrays
- C-style dynamic allocation
- C++ `new` / `delete`
- Modern C++ `std::string` / `std::vector`

---

## 1. `char` — One Character

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *ch = malloc(sizeof(char));

    printf("Enter a character: ");
    scanf(" %c", ch);

    printf("You entered: %c\n", *ch);

    free(ch);

    return 0;
}
```

**How it works**

```c
char *ch = malloc(sizeof(char));
```

ch stores the address of dynamically allocated memory.

```c
scanf(" %c", ch);
```

scanf needs an address where it can store the character.

```c
*ch
```

accesses the actual character stored at that address.

For a single character, dynamic allocation is normally unnecessary:

```c
char ch;

scanf(" %c", &ch);
```

### C++

```cpp
#include <iostream>

int main() {
    char *ch = new char;

    std::cout << "Enter a character: ";
    std::cin >> *ch;

    std::cout << "You entered: " << *ch << '\n';

    delete ch;
}
```

Using scanf in C++:

```cpp
#include <cstdio>

int main() {
    char *ch = new char;

    scanf(" %c", ch);

    printf("%c\n", *ch);

    delete ch;
}
```

## 2. char * — Dynamically Allocated String

A C string is a sequence of characters ending with '\0'.

For example:

```cpp
Hello\0
```

So if you want to store 5 characters, you need 6 bytes.

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter maximum length: ");
    scanf("%d", &n);

    char *str = malloc((n + 1) * sizeof(char));

    printf("Enter string: ");
    scanf("%s", str);

    printf("String = %s\n", str);

    free(str);

    return 0;
}
```

Because:

```c
str
```

already represents an address, you do:

```c
scanf("%s", str);
```

not:

```
scanf("%s", &str);  // WRONG

Safer scanf
```

If you have a fixed-size buffer:

```c
char str[100];

scanf("%99s", str);
```

The 99 leaves one byte for '\0'.

**Important limitation**

```c
scanf("%s", str);
```

stops at whitespace.

Input:

**Hello World**

results in:

```c
Hello
```

For strings containing spaces, prefer:

```c
fgets(str, size, stdin);
```

### C++

Using new:

```cpp
#include <iostream>

int main() {
    int n;

    std::cout << "Enter maximum length: ";
    std::cin >> n;

    char *str = new char[n + 1];

    std::cout << "Enter string: ";
    std::cin >> str;

    std::cout << "String = " << str << '\n';

    delete[] str;
}
```

Important:

**new char[n + 1]**

must be paired with:

```cpp
delete[] str;
```

## 3. char ** — Pointer to Pointer

Consider:

```cpp
char **p;
```

Conceptually:

```
p
│
▼
address
│
▼
char
```

A very common use of char ** is an array of strings.

For example:

```cpp
Apple
Banana
Mango
```

can be represented as:

```
words
  │
  ▼
+---------+
| pointer | ──────> "Apple"
+---------+
| pointer | ──────> "Banana"
+---------+
| pointer | ──────> "Mango"
+---------+
```

## 4. Dynamically Allocated Array of Strings

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows;

    printf("How many strings? ");
    scanf("%d", &rows);

    char **words = malloc(rows * sizeof(char *));

    for (int i = 0; i < rows; i++) {
        int size;

        printf("Size of string %d: ", i);
        scanf("%d", &size);

        words[i] = malloc((size + 1) * sizeof(char));

        printf("Enter string %d: ", i);
        scanf("%s", words[i]);
    }

    printf("\nStrings:\n");

    for (int i = 0; i < rows; i++) {
        printf("%s\n", words[i]);
    }

    for (int i = 0; i < rows; i++) {
        free(words[i]);
    }

    free(words);

    return 0;
}
```

There are two levels of allocation.

First:

```c
char **words = malloc(rows * sizeof(char *));
```

allocates memory for the pointers.

Then:

```c
words[i] = malloc((size + 1) * sizeof(char));
```

allocates memory for the actual string.

### C++

```cpp
#include <iostream>

int main() {
    int rows;

    std::cout << "How many strings? ";
    std::cin >> rows;

    char **words = new char*[rows];

    for (int i = 0; i < rows; i++) {
        int size;

        std::cout << "Size of string " << i << ": ";
        std::cin >> size;

        words[i] = new char[size + 1];

        std::cout << "Enter string " << i << ": ";
        std::cin >> words[i];
    }

    std::cout << "\nStrings:\n";

    for (int i = 0; i < rows; i++) {
        std::cout << words[i] << '\n';
    }

    for (int i = 0; i < rows; i++) {
        delete[] words[i];
    }

    delete[] words;
}
```

## 5. char ** as a 2D Character Array

You can use:

```cpp
char **arr;
```

to create a dynamically allocated 2D character array.

Memory conceptually looks like:

```
arr
 │
 ├──> [ ][ ][ ][ ]
 │
 ├──> [ ][ ][ ][ ]
 │
 └──> [ ][ ][ ][ ]
```

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;

    printf("Rows: ");
    scanf("%d", &rows);

    printf("Columns: ");
    scanf("%d", &cols);

    char **arr = malloc(rows * sizeof(char *));

    for (int i = 0; i < rows; i++) {
        arr[i] = malloc(cols * sizeof(char));
    }

    printf("Enter characters:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf(" %c", &arr[i][j]);
        }
    }

    printf("\nArray:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", arr[i][j]);
        }

        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }

    free(arr);

    return 0;
}
```

Access:

```c
arr[i][j]
```

### C++

```cpp
#include <iostream>

int main() {
    int rows, cols;

    std::cout << "Rows: ";
    std::cin >> rows;

    std::cout << "Columns: ";
    std::cin >> cols;

    char **arr = new char*[rows];

    for (int i = 0; i < rows; i++) {
        arr[i] = new char[cols];
    }

    std::cout << "Enter characters:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> arr[i][j];
        }
    }

    std::cout << "\nArray:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << arr[i][j] << ' ';
        }

        std::cout << '\n';
    }

    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }

    delete[] arr;
}
```

## 6. 2D char Array — One Contiguous Block

Another way is to allocate the entire matrix as one block.

```cpp
char *arr = malloc(rows * cols * sizeof(char));
```

Instead of:

```cpp
arr[i][j]
```

you access:

```cpp
arr[i * cols + j]
```

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3;
    int cols = 4;

    char *arr = malloc(rows * cols * sizeof(char));

    printf("Enter characters:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf(" %c", &arr[i * cols + j]);
        }
    }

    printf("\nArray:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", arr[i * cols + j]);
        }

        printf("\n");
    }

    free(arr);

    return 0;
}
```

Memory:

```
arr
 │
 ▼
+---+---+---+---+---+---+---+---+---+---+---+---+
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |
+---+---+---+---+---+---+---+---+---+---+---+---+
      row 0          row 1          row 2
```

Formula:

```c
arr[i * cols + j]
```

For cols = 4:

```
arr[0][0] → arr[0]
arr[0][1] → arr[1]
arr[1][0] → arr[4]
arr[2][3] → arr[11]
```

### C++

```cpp
#include <iostream>

int main() {
    int rows = 3;
    int cols = 4;

    char *arr = new char[rows * cols];

    std::cout << "Enter characters:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> arr[i * cols + j];
        }
    }

    std::cout << "\nArray:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << arr[i * cols + j] << ' ';
        }

        std::cout << '\n';
    }

    delete[] arr;
}
```

## 7. char ** + One Contiguous Block

You can have:

```cpp
arr[i][j]
```

syntax while keeping the actual character data contiguous.

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3;
    int cols = 4;

    char **arr = malloc(rows * sizeof(char *));
    char *data = malloc(rows * cols * sizeof(char));

    for (int i = 0; i < rows; i++) {
        arr[i] = data + i * cols;
    }

    printf("Enter characters:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf(" %c", &arr[i][j]);
        }
    }

    printf("\nArray:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", arr[i][j]);
        }

        printf("\n");
    }

    free(data);
    free(arr);

    return 0;
}
```

Memory:

```
arr
 │
 ├──> pointer ──┐
 ├──> pointer ──┼────> contiguous character data
 └──> pointer ──┘
```

## 8. int — One Integer

The same concepts apply to integers.

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *num = malloc(sizeof(int));

    printf("Enter an integer: ");
    scanf("%d", num);

    printf("You entered: %d\n", *num);

    free(num);

    return 0;
}
```

Here:

```c
int *num = malloc(sizeof(int));
```

allocates memory for one integer.

Because num already contains an address:

```c
scanf("%d", num);
```

is correct.

The value is accessed using:

```c
*num
```

For a normal integer:

```c
int num;

scanf("%d", &num);
```

### C++

```cpp
#include <iostream>

int main() {
    int *num = new int;

    std::cout << "Enter an integer: ";
    std::cin >> *num;

    std::cout << "You entered: " << *num << '\n';

    delete num;
}
```

Using scanf:

```cpp
#include <cstdio>

int main() {
    int *num = new int;

    scanf("%d", num);

    printf("%d\n", *num);

    delete num;
}
```

## 9. int * — Dynamically Allocated Integer Array

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("How many integers? ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));

    printf("Enter %d integers:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nArray:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    free(arr);

    return 0;
}
```

Memory:

```
arr
 │
 ▼
+----+----+----+----+----+
| 10 | 20 | 30 | 40 | 50 |
+----+----+----+----+----+
```

Access:

```c
arr[i]
```

Input:

```c
scanf("%d", &arr[i]);
```

**Why &arr[i]?**

Because:

```c
arr[i]
```

is an int.

scanf needs the address of that int:

```c
&arr[i]
```

### C++

```cpp
#include <iostream>

int main() {
    int n;

    std::cout << "How many integers? ";
    std::cin >> n;

    int *arr = new int[n];

    std::cout << "Enter integers:\n";

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << "\nArray:\n";

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }

    std::cout << '\n';

    delete[] arr;
}
```

Using scanf:

```cpp
#include <cstdio>

int main() {
    int n;

    scanf("%d", &n);

    int *arr = new int[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    delete[] arr;
}
```

## 10. int ** — Dynamically Allocated 2D Integer Array

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;

    printf("Rows: ");
    scanf("%d", &rows);

    printf("Columns: ");
    scanf("%d", &cols);

    int **arr = malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {
        arr[i] = malloc(cols * sizeof(int));
    }

    printf("Enter integers:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("\nArray:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }

        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }

    free(arr);

    return 0;
}
```

Memory:

```
arr
 │
 ├──> [10][20][30]
 │
 ├──> [40][50][60]
 │
 └──> [70][80][90]
```

Access:

```c
arr[i][j]
```

### C++

```cpp
#include <iostream>

int main() {
    int rows, cols;

    std::cout << "Rows: ";
    std::cin >> rows;

    std::cout << "Columns: ";
    std::cin >> cols;

    int **arr = new int*[rows];

    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }

    std::cout << "Enter integers:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> arr[i][j];
        }
    }

    std::cout << "\nArray:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << arr[i][j] << ' ';
        }

        std::cout << '\n';
    }

    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }

    delete[] arr;
}
```

Using scanf:

```cpp
#include <cstdio>

int main() {
    int rows, cols;

    scanf("%d", &rows);
    scanf("%d", &cols);

    int **arr = new int*[rows];

    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }

        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }

    delete[] arr;
}
```

## 11. 2D int Array — One Contiguous Block

Instead of:

```cpp
int **arr;
```

you can allocate:

```cpp
int *arr = malloc(rows * cols * sizeof(int));
```

Then access:

```cpp
arr[i * cols + j]
```

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;

    printf("Rows: ");
    scanf("%d", &rows);

    printf("Columns: ");
    scanf("%d", &cols);

    int *arr = malloc(rows * cols * sizeof(int));

    printf("Enter integers:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i * cols + j]);
        }
    }

    printf("\nArray:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i * cols + j]);
        }

        printf("\n");
    }

    free(arr);

    return 0;
}
```

Memory:

```
arr
 │
 ▼
+----+----+----+----+----+----+----+----+----+
| 10 | 20 | 30 | 40 | 50 | 60 | 70 | 80 | 90 |
+----+----+----+----+----+----+----+----+----+
      row 0       row 1       row 2
```

Formula:

```c
arr[i * cols + j]
```

### C++

```cpp
#include <iostream>

int main() {
    int rows, cols;

    std::cout << "Rows: ";
    std::cin >> rows;

    std::cout << "Columns: ";
    std::cin >> cols;

    int *arr = new int[rows * cols];

    std::cout << "Enter integers:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> arr[i * cols + j];
        }
    }

    std::cout << "\nArray:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << arr[i * cols + j] << ' ';
        }

        std::cout << '\n';
    }

    delete[] arr;
}
```

## 12. int ** + One Contiguous Block

You can have:

```cpp
arr[i][j]
```

syntax while keeping all integers in one contiguous block.

### C

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;

    printf("Rows: ");
    scanf("%d", &rows);

    printf("Columns: ");
    scanf("%d", &cols);

    int **arr = malloc(rows * sizeof(int *));
    int *data = malloc(rows * cols * sizeof(int));

    for (int i = 0; i < rows; i++) {
        arr[i] = data + i * cols;
    }

    printf("Enter integers:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("\nArray:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }

        printf("\n");
    }

    free(data);
    free(arr);

    return 0;
}
```

Memory:

```
arr
 │
 ├──> pointer ──┐
 ├──> pointer ──┼────> contiguous integer data
 └──> pointer ──┘
```

## 13. C++ Modern Way — std::string

In modern C++, prefer std::string instead of manually managing:

**`char *`**

Example:

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str;

    std::cout << "Enter string: ";
    std::cin >> str;

    std::cout << "String: " << str << '\n';
}
```

For input containing spaces:

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str;

    std::cout << "Enter string: ";
    std::getline(std::cin, str);

    std::cout << "String: " << str << '\n';
}
```

## 14. C++ Modern Way — std::vector<int>

Instead of:

```cpp
int *arr = new int[n];
```

prefer:

```cpp
std::vector<int> arr(n);
```

Example:

```cpp
#include <iostream>
#include <vector>

int main() {
    int n;

    std::cout << "How many integers? ";
    std::cin >> n;

    std::vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }

    std::cout << '\n';
}
```

No delete[] is required.

```cpp
std::vector automatically manages its memory.
```

## 15. C++ Modern Way — 2D vector

For a dynamic 2D integer array:

```cpp
#include <iostream>
#include <vector>

int main() {
    int rows, cols;

    std::cin >> rows >> cols;

    std::vector<std::vector<int>> arr(
```

```
        rows,
```

```cpp
        std::vector<int>(cols)
    );

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> arr[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << arr[i][j] << ' ';
        }

        std::cout << '\n';
    }
}
```

For a dynamic 2D character array:

```cpp
#include <iostream>
#include <vector>

int main() {
    int rows, cols;

    std::cin >> rows >> cols;

    std::vector<std::vector<char>> arr(
```

```
        rows,
```

```cpp
        std::vector<char>(cols)
    );

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> arr[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << arr[i][j] << ' ';
        }

        std::cout << '\n';
    }
}
```

## 16. scanf Cheat Sheet

| Variable | Declaration | scanf |
| --- | --- | --- |
| Character | char c; | scanf(" %c", &c); |
| Integer | int n; | scanf("%d", &n); |
| Float | float x; | scanf("%f", &x); |
| Double | double x; | scanf("%lf", &x); |
| String | char str[100]; | scanf("%99s", str); |
| Dynamic string | char *str; | scanf("%99s", str); |
| Dynamic int array | int *arr; | scanf("%d", &arr[i]); |
| Array of strings | char **arr; | scanf("%s", arr[i]); |
| 2D char array | char arr[][]; | scanf(" %c", &arr[i][j]); |
| 2D int array | int arr[][]; | scanf("%d", &arr[i][j]); |

## 17. Why Does scanf Sometimes Need &?

Suppose:

```cpp
int x;
```

x contains a value:

```
x
└── 10
```

scanf needs the address of x:

```cpp
scanf("%d", &x);
```

because:

```cpp
&x
```

```
 │
 ▼
address of x
```

Now suppose:

```cpp
int *p = malloc(sizeof(int));
```

Here:

```
p
 │
 ▼
address
 │
 ▼
integer
```

p is already an address.

Therefore:

```cpp
scanf("%d", p);
```

is correct.

You do NOT write:

```cpp
scanf("%d", &p);
```

because &p is the address of the pointer itself.

## 18. char vs char * vs char **

Think about the number of pointer levels.

```cpp
char c;
```

means:

```
c
└── character
```

```cpp
char *p;
```

means:

```
p
└── address
    └── character
```

```cpp
char **p;
```

means:

```
p
└── address
    └── address
        └── character
```

Example:

```cpp
char c = 'A';

char *p = &c;

char **pp = &p;
```

Then:

```
c       // 'A'
*p      // 'A'
**pp    // 'A'
```

## 19. int vs int * vs int **

Exactly the same idea applies to integers.

```cpp
int x;
```

```
x
└── integer
```

```cpp
int *p;
```

```
p
└── address
    └── integer
```

```cpp
int **pp;
```

```
pp
└── address
    └── address
        └── integer
```

Example:

```cpp
int x = 10;

int *p = &x;

int **pp = &p;
```

Then:

```
x       // 10
*p      // 10
**pp    // 10
```

## 20. Important malloc Patterns in C

**Single value**

```c
int *p = malloc(sizeof(int));

char *p = malloc(sizeof(char));
```

**1D array**

```c
int *arr = malloc(n * sizeof(int));

char *arr = malloc(n * sizeof(char));
```

**Array of pointers**

```c
int **arr = malloc(rows * sizeof(int *));

char **arr = malloc(rows * sizeof(char *));
```

**2D array — separate rows**

Integer:

```c
int **arr = malloc(rows * sizeof(int *));

for (int i = 0; i < rows; i++) {
    arr[i] = malloc(cols * sizeof(int));
}
```

Character:

```c
char **arr = malloc(rows * sizeof(char *));

for (int i = 0; i < rows; i++) {
    arr[i] = malloc(cols * sizeof(char));
}
```

**2D array — contiguous memory**

Integer:

```c
int *arr = malloc(rows * cols * sizeof(int));
```

Access:

```c
arr[i * cols + j]
```

Character:

```c
char *arr = malloc(rows * cols * sizeof(char));
```

Access:

```c
arr[i * cols + j]
```

## 21. Important new Patterns in C++

**Single value**

```cpp
int *p = new int;

char *p = new char;
```

**1D array**

```cpp
int *arr = new int[n];

char *arr = new char[n];
```

**Array of pointers**

```cpp
int **arr = new int*[rows];

char **arr = new char*[rows];
```

**2D array**

```cpp
int **arr = new int*[rows];

for (int i = 0; i < rows; i++) {
    arr[i] = new int[cols];
}
```

Character:

```cpp
char **arr = new char*[rows];

for (int i = 0; i < rows; i++) {
    arr[i] = new char[cols];
}
```

Free it using:

```cpp
for (int i = 0; i < rows; i++) {
    delete[] arr[i];
}

delete[] arr;
```

## 22. malloc/free vs new/delete

### C

Use:

```c
malloc
calloc
realloc
free
```

Example:

```c
int *arr = malloc(n * sizeof(int));

free(arr);
```

### C++

Manual dynamic allocation uses:

```cpp
new
delete
new[]
delete[]
```

Example:

```cpp
int *arr = new int[n];

delete[] arr;
```

**Do not mix them**

Wrong:

```cpp
int *p = new int;

free(p);
```

Wrong:

```cpp
int *p = malloc(sizeof(int));

delete p;
```

Correct pairs:

```
malloc  → free

calloc  → free

realloc → free

new     → delete

new[]   → delete[]
```

## 23. sizeof and Dynamic Allocation

A common pattern in C is:

```cpp
int *arr = malloc(n * sizeof(int));
```

This means:

**number of elements × size of one element**

For example, if:

**n = 5**

**sizeof(int) = 4**

then:

**5 × 4 = 20 bytes**

For characters:

```cpp
char *arr = malloc(n * sizeof(char));
```

Since:

**sizeof(char) == 1**

this is equivalent to:

```cpp
char *arr = malloc(n);
```

For a 2D array:

```cpp
int *arr = malloc(rows * cols * sizeof(int));
```

means:

**rows × columns × size of int**

## 24. Always Check malloc

In production C code, check whether allocation succeeded.

```c
int *arr = malloc(n * sizeof(int));

if (arr == NULL) {
    printf("Memory allocation failed\n");
    return 1;
}
```

For a 2D array:

```c
int **arr = malloc(rows * sizeof(int *));

if (arr == NULL) {
    printf("Memory allocation failed\n");
    return 1;
}
```

The same applies to every dynamic allocation.

## 25. calloc

calloc is another C allocation function.

Unlike malloc, it initializes the allocated memory to zero.

```c
int *arr = calloc(n, sizeof(int));
```

Equivalent size:

**n × sizeof(int)**

Example:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    scanf("%d", &n);

    int *arr = calloc(n, sizeof(int));

    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);

    return 0;
}
```

Output will initially be:

**0 0 0 0 0**

## 26. realloc

realloc allows you to resize an existing allocation.

Example:

```c
int *arr = malloc(5 * sizeof(int));

arr = realloc(arr, 10 * sizeof(int));
```

Now the allocation has space for 10 integers.

A safer pattern is:

```c
int *temp = realloc(arr, 10 * sizeof(int));

if (temp == NULL) {
    free(arr);
    return 1;
}

arr = temp;
```

## 27. Common Mistakes

**Mistake 1 — Forgetting &**

Wrong:

```c
int x;

scanf("%d", x);
```

Correct:

```c
scanf("%d", &x);
```

**Mistake 2 — Adding & to a string**

Wrong:

```c
char str[100];

scanf("%s", &str);
```

Correct:

```c
scanf("%s", str);
```

**Mistake 3 — Adding & to an allocated string**

Wrong:

```c
char *str = malloc(100);

scanf("%s", &str);
```

Correct:

```c
scanf("%s", str);
```

**Mistake 4 — Forgetting space for '\0'**

Wrong:

```c
char *str = malloc(5);
```

for:

```c
Hello
```

Correct:

```c
char *str = malloc(6);
```

because:

```c
H e l l o \0
```

**Mistake 5 — Using delete instead of delete[]**

Wrong:

```c
int *arr = new int[10];

delete arr;
```

Correct:

```c
delete[] arr;
```

**Mistake 6 — Mixing malloc and delete**

Wrong:

```c
int *p = malloc(sizeof(int));

delete p;
```

Use:

```c
free(p);
```

**Mistake 7 — Mixing new and free**

Wrong:

```c
int *p = new int;

free(p);
```

Use:

```c
delete p;
```

**Mistake 8 — Forgetting to free every row**

If you do:

```c
int **arr = malloc(rows * sizeof(int *));

for (int i = 0; i < rows; i++) {
    arr[i] = malloc(cols * sizeof(int));
}
```

you must do:

```c
for (int i = 0; i < rows; i++) {
    free(arr[i]);
}

free(arr);
```

## 28. Quick Comparison

| Requirement | C | C++ |
| --- | --- | --- |
| One char | char c; | char c; |
| Dynamic char | malloc(sizeof(char)) | new char |
| String | char *str | std::string |
| Dynamic C string | malloc(n + 1) | new char[n + 1] |
| One int | int x; | int x; |
| Dynamic int | malloc(sizeof(int)) | new int |
| 1D int array | malloc(n * sizeof(int)) | new int[n] |
| 1D char array | malloc(n * sizeof(char)) | new char[n] |
| 2D int | int ** + rows | int ** + rows |
| 2D char | char ** + rows | char ** + rows |
| Modern dynamic array | — | std::vector |
| Modern string | — | std::string |

## 29. scanf Format Specifiers

| Type | Format |
| --- | --- |
| char | %c |
| short | %hd |
| int | %d |
| long | %ld |
| long long | %lld |
| unsigned int | %u |
| float | %f |
| double | %lf |
| long double | %Lf |
| string | %s |

Examples:

```c
char c;
int i;
float f;
double d;

scanf(" %c", &c);
scanf("%d", &i);
scanf("%f", &f);
scanf("%lf", &d);
```

## 30. The Most Important Mental Model

Think about pointers in terms of pointer levels.

```
char
└── value
```

**`char *`**

```
└── address
    └── char
```

**`char **`**

```
└── address
    └── address
        └── char
```

Exactly the same for int:

```
int
└── value
```

**`int *`**

```
└── address
    └── int
```

**`int **`**

```
└── address
    └── address
        └── int
```

The number of * represents pointer levels.

## 31. scanf Mental Model

The most important rule:

scanf needs the address of the variable where it will store the input.

Normal variable:

```c
int x;

scanf("%d", &x);
```

Because:

```
x  → value
&x → address of value
```

Pointer to allocated integer:

```c
int *x = malloc(sizeof(int));

scanf("%d", x);
```

Because:

```
x → address of allocated integer
```

Array element:

```c
int arr[10];

scanf("%d", &arr[i]);
```

2D array element:

```c
int arr[10][10];

scanf("%d", &arr[i][j]);
```

String:

```c
char str[100];

scanf("%s", str);
```

Because an array name already gives the address of its first element in this context.

Array of strings:

```c
char **arr;

scanf("%s", arr[i]);
```

because arr[i] is already a char *.

## 32. Final Cheat Sheet

**C — Single Values**

```c
char c;
scanf(" %c", &c);

int x;
scanf("%d", &x);
```

**C — Dynamically Allocated Single Values**

```c
char *c = malloc(sizeof(char));
scanf(" %c", c);

int *x = malloc(sizeof(int));
scanf("%d", x);

free(c);
free(x);
```

**C — 1D Arrays**

```c
char *chars = malloc(n * sizeof(char));

for (int i = 0; i < n; i++) {
    scanf(" %c", &chars[i]);
}

free(chars);

int *numbers = malloc(n * sizeof(int));

for (int i = 0; i < n; i++) {
    scanf("%d", &numbers[i]);
}

free(numbers);
```

**C — 2D Arrays**

Separate rows:

```c
char **chars = malloc(rows * sizeof(char *));

for (int i = 0; i < rows; i++) {
    chars[i] = malloc(cols * sizeof(char));
}

int **numbers = malloc(rows * sizeof(int *));

for (int i = 0; i < rows; i++) {
    numbers[i] = malloc(cols * sizeof(int));
}
```

Input:

```c
scanf(" %c", &chars[i][j]);

scanf("%d", &numbers[i][j]);
```

Free:

```c
for (int i = 0; i < rows; i++) {
    free(chars[i]);
}

free(chars);

for (int i = 0; i < rows; i++) {
    free(numbers[i]);
}

free(numbers);
```

**C++ — Single Values**

```c
char c;
std::cin >> c;

int x;
std::cin >> x;
```

**C++ — Dynamic Single Values**

```c
char *c = new char;
std::cin >> *c;

int *x = new int;
std::cin >> *x;

delete c;
delete x;
```

**C++ — 1D Arrays**

```c
char *chars = new char[n];

for (int i = 0; i < n; i++) {
    std::cin >> chars[i];
}

delete[] chars;

int *numbers = new int[n];

for (int i = 0; i < n; i++) {
    std::cin >> numbers[i];
}

delete[] numbers;
```

**C++ — 2D Arrays**

```c
char **chars = new char*[rows];

for (int i = 0; i < rows; i++) {
    chars[i] = new char[cols];
}

int **numbers = new int*[rows];

for (int i = 0; i < rows; i++) {
    numbers[i] = new int[cols];
}
```

Input:

```c
std::cin >> chars[i][j];

std::cin >> numbers[i][j];
```

Free:

```c
for (int i = 0; i < rows; i++) {
    delete[] chars[i];
}

delete[] chars;

for (int i = 0; i < rows; i++) {
    delete[] numbers[i];
}

delete[] numbers;
```

## 33. Recommended Approach

For learning C, understand all of these:

```c
malloc
calloc
realloc
free

char
```

**`char *`**

**`char **`**

```c
int
```

**`int *`**

**`int **`**

**1D arrays**

**2D arrays**

**contiguous memory**

**pointer arithmetic**

For modern C++, understand the pointer-based approach, but normally prefer:

```c
std::string
std::vector
std::vector<std::vector<int>>
std::vector<std::vector<char>>
```

over manual:

```c
new
delete
new[]
delete[]
```
