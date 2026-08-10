#include <stdio.h>

#if 0
void simple_pointer()
{
	int a = 10;
  	int* p = &a;
}


void pointer_to_const_int()
{
	int a = 10;
	//can not modify using *p, but can be updated directly a as it's not constant.
  	const int* p = &a; //int const * p = &a
  	*p = 20;
  	a = 20;
  	printf("%d\n", *p);
  	printf("%d\n", a);
}


void const_pointer_to_int()
{
	int a = 10;
	int b = 30;
	
  	int* const p = &a; 
  	*p = 20;
  	a = 20;
  	p = &b; //p can not point to any other var now.
  	printf("%d\n", *p);
  	printf("%d\n", a);
}
#endif

void pointer_to_arr()
{
	int arr[] = {10, 32, 20, 42, 50};
	int* p = &arr[0]; //pointer is pointing to first element of array and since array is contiguous so *p+1, *p+2 are printing next array 
	//elements.
	printf("%d\n", *p);
	printf("%d\n", *p+1);
	printf("%d\n", *p+2);
	printf("%d\n", *p+3);
}

void pointer_to_arr_of_n_int()
{
	// An array of 5 integers
	int arr[] = {10, 32, 20, 42, 50};

	// p is a pointer to the entire array of 5 integers
	int (*p)[5] = &arr;

	// *p gives the entire array
	// **p gives the first element: arr[0] → 10
	printf("%d\n", **p);      // 10

	// **p is arr[0], so adding 1 gives arr[0] + 1
	printf("%d\n", **p + 1);  // 11

	// **p is arr[0], so adding 2 gives arr[0] + 2
	printf("%d\n", **p + 2);  // 12

	// **p is arr[0], so adding 3 gives arr[0] + 3
	printf("%d\n", **p + 3);  // 13
	
	/*
	p[0][0] → 10
	p[0][1] → 32
	p[0][2] → 20
	p[0][3] → 42
	p[0][4] → 50
	*/

}

void array_of_pointers()
{
	int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;

    // Array of 4 integer pointers
    int *p[4];

    // Store addresses in the pointer array
    p[0] = &a;
    p[1] = &b;
    p[2] = &c;
    p[3] = &d;

    // Dereference each pointer to get the value
    printf("%d\n", *p[0]);  // 10
    printf("%d\n", *p[1]);  // 20
    printf("%d\n", *p[2]);  // 30
    printf("%d\n", *p[3]);  // 40
}

int main()
{
  	//simple_pointer();
  	//pointer_to_const_int();
	//const_pointer_to_int();
	//pointer_to_arr();
	//pointer_to_arr_of_n_int();
	array_of_pointers();
    return 0;
}
