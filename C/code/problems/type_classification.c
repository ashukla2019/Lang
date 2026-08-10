#include <stdio.h>
#include <ctype.h>

void checkString(char *str)
{
    int digit = 0;
    int alpha = 0;
    int dot = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isdigit((unsigned char)str[i]))
            digit = 1;

        if (isalpha((unsigned char)str[i]))
            alpha = 1;

        if (str[i] == '.')
            dot = 1;
    }

    if (digit && alpha)
        printf("Alphanumeric\n");

    else if (digit && dot && !alpha)
        printf("Float\n");

    else if (digit && !dot && !alpha)
        printf("Integer\n");

    else if (alpha)
        printf("Alphabetic\n");

    else
        printf("Other\n");
}

int main()
{
    char str[100];

    printf("Enter a string: ");
    scanf("%99s", str);

    checkString(str);

    return 0;
}
