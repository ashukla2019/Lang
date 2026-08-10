Problem asked in interview: Remove target from given string:

#include <stdio.h>
#include <string.h>

void *removeTarget(char *str, char target)
{
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != target)
        {
            str[j++] = str[i];
        }
    }

    str[j] = '\0';

    return str;
}

int main()
{
    char arr[] = "abcdefa";
    char target = 'a';

    char *result = (char *)removeTarget(arr, target);

    printf("%s\n", result);

    return 0;
}

