#include <stdio.h>


// ============================================================
// 1. POINTER TO CHAR ARRAY / STRING
// ============================================================

void pointer_to_char_arr()
{
	char arr[] = "Hello";

	// p points to the first character
	char *p = &arr[0];

	/*
		arr:

		+---+---+---+---+---+----+
		| H | e | l | l | o | \0 |
		+---+---+---+---+---+----+
		  ^
		  |
		  p
	*/

	printf("%c\n", *p);       // H
	printf("%c\n", *(p + 1)); // e
	printf("%c\n", *(p + 2)); // l
	printf("%c\n", *(p + 3)); // l
	printf("%c\n", *(p + 4)); // o

	/*
		*p       -> 'H'
		*(p + 1) -> 'e'
		*(p + 2) -> 'l'
		*(p + 3) -> 'l'
		*(p + 4) -> 'o'
	*/

	// These are equivalent:
	//
	// char *p = &arr[0];
	// char *p = arr;
}


// ============================================================
// 2. ARRAY OF CHAR POINTERS
// ============================================================

void array_of_char_pointers()
{
	// Array of 4 pointers to char
	char *p[4];

	// Each pointer points to a string
	p[0] = "Apple";
	p[1] = "Banana";
	p[2] = "Mango";
	p[3] = "Orange";

	/*
		Visual:

		      p
		+--------+--------+--------+--------+
		| p[0]   | p[1]   | p[2]   | p[3]   |
		+---|----+---|----+---|----+---|----+
		    |        |        |        |
		    v        v        v        v
		 "Apple" "Banana" "Mango" "Orange"
	*/

	// p[i] gives the address of the string
	printf("%s\n", p[0]); // Apple
	printf("%s\n", p[1]); // Banana
	printf("%s\n", p[2]); // Mango
	printf("%s\n", p[3]); // Orange

	// *p[i] gives the first character
	printf("%c\n", *p[0]); // A
	printf("%c\n", *p[1]); // B
	printf("%c\n", *p[2]); // M
	printf("%c\n", *p[3]); // O

	/*
		Individual characters:

		p[0][0] -> A
		p[0][1] -> p
		p[0][2] -> p

		p[1][0] -> B
		p[1][1] -> a
	*/

	printf("%c\n", p[0][0]); // A
	printf("%c\n", p[0][1]); // p
	printf("%c\n", p[0][2]); // p

	printf("%c\n", p[1][0]); // B
	printf("%c\n", p[1][1]); // a
}


// ============================================================
// 3. POINTER TO ARRAY OF N CHARS
// ============================================================

void pointer_to_char_arr_of_n()
{
	// Array of 5 characters
	char arr[5] = {'A', 'B', 'C', 'D', 'E'};

	// p is a pointer to the ENTIRE array of 5 chars
	char (*p)[5] = &arr;

	/*
		p[0] refers to the first array.

		p[0][0] -> A
		p[0][1] -> B
		p[0][2] -> C
		p[0][3] -> D
		p[0][4] -> E
	*/
	printf("%s\n", *p); //print whole string
	printf("%c\n", p[0][0]); // A
	printf("%c\n", p[0][1]); // B
	printf("%c\n", p[0][2]); // C
	printf("%c\n", p[0][3]); // D
	printf("%c\n", p[0][4]); // E
}


// ============================================================
// 4. IMPORTANT DECLARATION COMPARISON
// ============================================================

/*
	char *p;
		-> pointer to char


	char *p[5];
		-> array of 5 pointers to char


	char (*p)[5];
		-> pointer to an array of 5 chars


	char p[5];
		-> array of 5 chars


	Parentheses are VERY important!

	char *p[5];

		[] has higher precedence than *
		-> array of pointers


	char (*p)[5];

		() forces * to bind first
		-> pointer to array
*/


int main()
{
	// pointer_to_char_arr();
	// array_of_char_pointers();

	pointer_to_char_arr_of_n();

	return 0;
}

