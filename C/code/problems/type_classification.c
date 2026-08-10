#include <stdio.h>
#include <ctype.h>

void checkString(const char *str)
{
    int hasDigit = 0;
    int hasAlpha = 0;
    int hasDot = 0;

    int isInteger = 1;
    int isFloat = 1;

    for (int i = 0; str[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)str[i];

        if (isdigit(c))
        {
            hasDigit = 1;
        }
        else if (isalpha(c))
        {
            hasAlpha = 1;
            isInteger = 0;
            isFloat = 0;
        }
        else if (str[i] == '.')
        {
            hasDot++;

            // More than one dot → not a valid float
            if (hasDot > 1)
                isFloat = 0;

            isInteger = 0;
        }
        else
        {
            // Any other character
            isInteger = 0;
            isFloat = 0;
        }
    }

    if (isInteger && hasDigit)
    {
        printf("Integer\n");
    }
    else if (isFloat && hasDigit && hasDot == 1)
    {
        printf("Float\n");
    }
    else if (hasAlpha && hasDigit)
    {
        printf("Alphanumeric\n");
    }
    else if (hasAlpha)
    {
        printf("Alphabetic\n");
    }
    else
    {
        printf("Other\n");
    }
}

int main()
{
    char str[100];

    printf("Enter a string: ");
    scanf("%99s", str); //%99s is used to prevent buffer overflow

    checkString(str);

    return 0;
}
