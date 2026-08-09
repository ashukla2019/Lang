C Language — Input Functions
1. scanf()

scanf() is used to take formatted input from the user.

Example
#include <stdio.h>

int main()
{
    int age;
    float marks;
    char grade;

    printf("Enter age: ");
    scanf("%d", &age);

    printf("Enter marks: ");
    scanf("%f", &marks);

    printf("Enter grade: ");
    scanf(" %c", &grade);

    printf("Age = %d\n", age);
    printf("Marks = %.2f\n", marks);
    printf("Grade = %c\n", grade);

    return 0;
}

Common Format Specifiers
Data Type	Format Specifier
int	%d
float	%f
double	%lf
char	%c
string	%s
long int	%ld
unsigned int	%u
Important

For most variables, use & with scanf():

int n;
scanf("%d", &n);


For a character:

char ch;
scanf(" %c", &ch);


Notice the space before %c. It helps skip leftover whitespace/newline characters.

For a string array, don't use &:

char name[50];
scanf("%s", name);

2. getchar()

getchar() reads one character from standard input.

Example
#include <stdio.h>

int main()
{
    char ch;

    printf("Enter a character: ");
    ch = getchar();

    printf("You entered: %c\n", ch);

    return 0;
}

Example Input
A

Output
You entered: A

3. fgets()

fgets() is used to read a string or an entire line.

It is especially useful when the input contains spaces.

Example
#include <stdio.h>

int main()
{
    char name[50];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    printf("Name: %s", name);

    return 0;
}

Example

Input:

Rahul Kumar


Output:

Name: Rahul Kumar


Unlike:

scanf("%s", name);


fgets() can read spaces.

4. gets() — Avoid It

You may see old C programs using:

gets(name);


Do not use gets() in modern C.

It is unsafe because it does not know the size of the input buffer and can cause a buffer overflow.

Use:

fgets(name, sizeof(name), stdin);


instead.

5. getch()

You may encounter:

getch();


in older C programs.

It is commonly associated with:

#include <conio.h>


However, getch() is not part of standard C and is compiler/platform-specific.

For portable C programs, prefer standard functions such as:

getchar();

6. Taking Multiple Inputs

You can use scanf() to take multiple values:

#include <stdio.h>

int main()
{
    int a, b;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    printf("A = %d\n", a);
    printf("B = %d\n", b);

    return 0;
}

Input
10 20

Output
A = 10
B = 20

7. Taking Array Input

You can use a loop with scanf():

#include <stdio.h>

int main()
{
    int arr[5];

    printf("Enter 5 numbers:\n");

    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Array: ");

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}

Input
10 20 30 40 50

Output
Array: 10 20 30 40 50

8. Taking String Input
Using scanf()
char name[50];

scanf("%s", name);


This reads only until whitespace.

For example:

Rahul Kumar


will read only:

Rahul

Using fgets()
char name[50];

fgets(name, sizeof(name), stdin);


This can read:

Rahul Kumar


as a complete line.

Quick Reference
Function	Purpose
scanf()	Formatted input
getchar()	Read one character
fgets()	Read a string/line
gets()	Unsafe — avoid
getch()	Non-standard/compiler-specific
Most Important to Remember
Integer
int n;
scanf("%d", &n);

Float
float f;
scanf("%f", &f);

Character
char ch;
scanf(" %c", &ch);

String without spaces
char name[50];
scanf("%s", name);

String/line with spaces
char name[50];
fgets(name, sizeof(name), stdin);

Recommendation

For modern C programming:

Use scanf() for formatted numeric input.
Use getchar() for a single character.
Use fgets() for strings and complete lines.
Avoid gets().
Avoid relying on getch() if you want portable standard C.
