#include<iostream>
#include<string.h>
using namespace std;

//usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
PATH: /usr/local/sbin

int main()
{

    char *token;
    char *path = getenv("PATH");
 
    token = strtok(path, ":");
    puts(token);
 
    while (token = strtok(0, ":")) 
    {
        puts(token);
    }
 
    printf("PATH: %s\n", path);
    return 0;
}
