#include<stdio.h>

//Reverse string using recursion:
char* print_reverse(char *str)
{
	//Base case
    if (*str == '\0')
    {
        return;
    }

    print_reverse(str + 1);
    printf("%c", *str);
    return str;
}

/*strlen():counts the length ofgiven string */
unsigned int my_strlen(const char *s)
{
    unsigned int count = 0;
    while(*s)
    {
        count++;
        s++;
    }
    return count;
}


/*
strcpy(): char* strcpy(char* destination, const char* source);
The strcpy() function copies the null-terminated C-string pointed to by source to the
memory pointed to by destination
*/
char* my_strcpy(char* destination, const char* source)
{
    int index =0;
    while (source[index])
    {
        destination[index] = source[index];
        index++;
    }
 
    // include the terminating null character
    destination[index] = '\0';
 
    return destination;
}

char* my_strcat(char* destination, const char* source)
{
    int index1 =0;
	int index2 =0;
    while (destination[index1])
    {
        index1++;
    }
    while (source[index2])
    {
        destination[index1] = source[index2];
		index1++;
		index2++;
    }
    // include the terminating null character
    destination[index1] = '\0';
 
    // the destination is returned by standard `strcpy()`
    return destination;
}

// Function to implement strcmp function
int my_strcmp(const char *X, const char *Y)
{
    while (*X)
    {
        // if characters differ, or end of the second string is reached
        if (*X != *Y) {
            break;
        }
 
        // move to the next pair of characters
        X++;
        Y++;
    }
 
    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

/*
//strtok()
//Tokenizing a string using strtok():
int main()
{
	char str[] = "Geeks-for-Geeks";

	//Returns first token
	char *token = strtok(str, "-");

	//Keep printing tokens while one of the delimiters present in str[].
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, "-");
	}

	return 0;
}
*/

//strstr():char *strstr(const char *haystack, const char *needle) function finds the 
//first occurrence of the substring needle in the string
int my_strStr(char* haystack, char* needle) 
 {
	int m = strlen(haystack), n = strlen(needle);
	for (int i = 0; i <= m - n; i++) 
	{
		int j = 0;
		for (; j < n; j++)
		{
			if (haystack[i + j] != needle[j]) 
			{
				break;
			}
		}
		if (j == n) 
		{
			return i;
		}
	}
	return -1;
}

/*
atoi(): The atoi function converts a string to an integer. 
The atoi function skips all white-space characters at the beginning of the string, 
converts the subsequent characters as part of the number, 
and then stops when it encounters the first character that isn't a number
*/
int myAtoi(char* s) 
{
int res =0;
int sign =1;
int i=0;

if(s[0] == '-')
{
    sign = -1;
    i++;
}
for(; s[i] != '\0'; ++i)
{
    res = res*10 + s[i] - '0'; // s[i] - '0' -> convert character into num
}
return (sign*res);
}

int main()
{
	char str1[] = "Hello";
	char str2[100];
	printf("string length=%d\n", my_strlen(str1));
	printf("Reversed string is = %s\n", print_reverse(str1));
	printf("copied string=%s\n", my_strcpy(str2, str1));
	printf("string after concatenation=%s\n", my_strcat(str2, str1));
	return 0;
}
 
