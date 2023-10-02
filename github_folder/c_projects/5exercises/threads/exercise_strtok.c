#include <stdio.h>
#include <string.h> /* for strtok() */

int main()
{
    char str[80] = "This is - www.tutorialspoint.com - website";
    const char s[] = " -";
    char* token;

    /* get the first token */
    token = strtok(str, s);

    /* walk through other tokens */
    while (NULL != token)
    {
        printf("%s\n", token);
        token = strtok(NULL, s);
    }

    return 0;
}