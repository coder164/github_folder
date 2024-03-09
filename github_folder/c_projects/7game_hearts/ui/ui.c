#include <stdio.h>
#include <stdlib.h>     /* for malloc */
#include <string.h>     /* for strcpy() */

#include "ui.h"

#define OK (0)
#define FALSE (0)
#define TRUE (1)
#define ASCII_ZERO (48)
#define MAX_NAME_LENGTH (30)

static char** CreateArrayOfNames(int _numOfHumans);
static int GetNumHumans(void);
static void DestroyArrayOfNames(char*** _arrOfNames);
static void PrintWelcome(void);
static void CleanBuffer(void);

int main(void)
{
    int numberOfHumans, i, len, numOfLetters;
    char** arrNames;
    char* line = NULL;
    char* name0, *name1, *name2, *name3;
    numberOfHumans = 0;
    i = 0;
    len = 0;
    numOfLetters = 0;
    PrintWelcome();
    numberOfHumans = GetNumHumans();
    if ('q' == numberOfHumans || 'Q' == numberOfHumans)
    {
        printf("The program will exit now...\n");
        return OK;
    }
    arrNames = CreateArrayOfNames(numberOfHumans);
    if (NULL == arrNames)
    {
        printf("There is an issue with the memory of the computer.\nThe program will exit now.");
        return OK;
    }
    printf("Please enter name: ");
    numOfLetters = getline(&line, &len, stdin);
    if (numOfLetters != -1)
    {
        printf("Retrieved line of length %d:\n", numOfLetters);
        line[numOfLetters - 1] = '\0';
        printf("%s\n", line);
    }
    name0 = (char*)malloc((numOfLetters) * sizeof(char));
    if (NULL == name0)
    {
        printf("There is an issue with the memory of the computer.\nThe program will exit now.");
        free(line);
        return OK;
    }
    strcpy(name0, line);
    printf("%s\n", name0);
    free(name0);
    free(line);
    DestroyArrayOfNames(&arrNames);
    return OK;
}

static void DestroyArrayOfNames(char*** _arrOfNames)
{
    if (NULL == _arrOfNames)
    {
        return;
    }
    free(*_arrOfNames);
    *_arrOfNames = NULL;
}

static char** CreateArrayOfNames(int _numOfHumans)
{
    char** arrayOfNames;
    arrayOfNames = (char**)malloc(_numOfHumans * sizeof(char*));
    if (NULL == arrayOfNames)
    {
        return NULL;
    }
    return arrayOfNames;
}

static void PrintWelcome(void)
{
    printf("Welcome to The Game Hearts\n");
}

static int GetNumHumans(void)
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
        else if (input < '0' || input > '4')
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
    while(TRUE)
    {
        if ('\n' == getchar())
        break;
    }
}
