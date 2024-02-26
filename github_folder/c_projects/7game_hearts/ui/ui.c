#include <stdio.h>

#include "ui.h"

#define OK (0)
#define TRUE (1)
#define ASCII_ZERO (48)

int GetNumHumans(void);
static void CleanBuffer(void);

int main(void)
{
    int numberOfHumans = 0;
    printf("Welcome to The Game Hearts\n");
    printf("Please type the number of human players (0 - 4)\n");
    numberOfHumans = GetNumHumans();
    if ('q' == numberOfHumans || 'Q' == numberOfHumans)
    {
        printf("The program will exit now...\n");
    }
    
    return OK;
}

int GetNumHumans(void)
{
    char input;
    while (TRUE)
    {
        printf("Please type the number of human players (0 - 4)\n");
        input = getchar();
        if ('q' == input || 'Q' == input)
        {
            CleanBuffer();
            break;
        }
        else if (input < '1' || input > '4')
        {
            printf("Sorry, the program only can take numbers between 0 - 4\n");
            printf("Please try again\n");
        }
        else
        {
            printf("Program recieved %d successfully.\n", input - ASCII_ZERO);
            CleanBuffer();
            break;
        }
        CleanBuffer();
        putchar('\n');
    }
    return input;
}

static void CleanBuffer(void)
{
    while(getchar() != '\n')
    {
    }
}
