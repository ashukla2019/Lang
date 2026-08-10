#include <stdio.h>

int myAtoi(const char *str)
{
    int num = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-')
    {
        sign = -1;
        i++;
    }

    while (str[i] != '\0')
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }

    return num * sign;
}

int main()
{
    char str[] = "12345";

    printf("%d\n", myAtoi(str));

    return 0;
}
