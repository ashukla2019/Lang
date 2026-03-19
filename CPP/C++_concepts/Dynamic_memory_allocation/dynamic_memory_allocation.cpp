Memory Management Functions in C:
malloc() : Allocates single block of requested memory
calloc() : Allocate multiple blocks of requested memory
realloc() : Reallocated the memory occupied by malloc() or calloc() function
free() : frees the dynamically allocated memory

Ex: 
#include <stdio.h>
#include <stdlib.h>

int main() {
  int *p = (int*) malloc(sizeof(int));
  *p = 5;
  printf("%d\n", *p);
  free(p);
}
------------------------------------------------------------------------------------------------------------
Memory Management Operators in C++
C++ introduced new ways of managing dynamic memory. Two new operators, called new and delete, were added to C++ for performing 
tasks related to dynamic memory management.

Here is the similar program in C++, written using these new operators.

#include <iostream>

int main() {
  int *p = new int(5);
  cout << p << endl;
  delete p;
}  

These new operators provides an easy to use interface and brings in the following benefits —

No need to specify the size of memory; Implicitly determined by the data type.
No need for explicit type-casting of the pointer.
Memory allocation and initialisation can be done in a single step.
To allocate dynamic memory for array, C++ introduced two new operators new[] and delete[]. Here is how to use them —

#include <iostream>

int main() {
  int *p = new int[3];
  p[0] = 0; p[1] = 10; p[2] = 100;
  delete[] p;
}
Note that operators new[] and operator delete[] are different from operator new and operator delete.

Memory Management Functions in C++
Notice the subtle difference in the heading for this section and the previous section.

Apart from the new and delete operator, C++ introduces two new functions for dynamic memory management. These are “operator new()” and “operator delete()”. Do not confuse them with operator new and operator delete. Here is how they are used.

#include <iostream>

int main() {
  int *p = (int*) operator new(sizeof(int));
  cout << p << endl;
  operator delete(p);
}
