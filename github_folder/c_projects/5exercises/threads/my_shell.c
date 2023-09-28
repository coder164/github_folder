#include <stdio.h>
#include <string.h> /* for strtok */
#define MAX_STR_SIZE 128
#define MAX_COMMANDS 18
#define TRUE 1
#define FALSE 0

static void MyShell(void);

int main()
{
	MyShell();
	return 0;
}

static void MyShell(void) {
	char strCommand[MAX_STR_SIZE];
	char* strParameters[MAX_COMMANDS];
	const char commandEnd[] = " \n";
	int status, i;
	char* token;
	while (TRUE) 
	{
		i = 1;
		printf("My prompt\n");
		fgets(strCommand, MAX_STR_SIZE - 1, stdin);
		if (strcmp(strCommand, "exit\n") == 0)
		{
			return;
		}
		strParameters[0] = strtok(strCommand, commandEnd);
		while (strParameters[i - 1] != NULL)
		{
			strParameters[i] = strtok(NULL, commandEnd);
			token = strtok(NULL, commandEnd);
			if (strcmp(strParameters[i],"exit\n") == 0)
			{
				return;
			}
			++i;
		}		
		if (fork() > 0)
		{
			/* Parent Code */
			waitpid(-1, &status, 0);
		}
		else 
		{
			/* Child code */
			execvp(strParameters[0], strParameters);
			printf("Fail\n");
		}
	}
}

