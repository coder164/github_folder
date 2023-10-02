#include <stdio.h>
#include <string.h> /* for strtok() */
#define MAX_COMMAND_LENGTH 128
#define MAX_NOUMBER_OF_COMMANDS 18
#define TRUE 1
#define FALSE 0

static void MyShell(void);

int main()
{
	MyShell();
	return 0;
}

static void MyShell(void) {
	char command[MAX_COMMAND_LENGTH];
	char* commandsList[MAX_NOUMBER_OF_COMMANDS];
	const char delimiters[] = " \n";
	int status, i, pid;
	while (TRUE) 
	{
		i = 0;
		printf("\n\tMy prompt\n");
		fgets(command, MAX_COMMAND_LENGTH - 1, stdin);
		if (strcmp(command, "exit\n") == 0)
		{
			break;
		}
		commandsList[i] = strtok(command, delimiters);
		while (NULL != commandsList[i])
		{
			++i;
			commandsList[i] = strtok(NULL, delimiters);
		}
		pid = fork();
		if (pid > 0)		/* parent code */
		{
			waitpid(-1, &status, 0);
		}
		else if (pid == 0)	/* child code */
		{
			execvp(command, commandsList);
			printf("command not found\n");
			break;
		}
		else
		{
			printf("pid < 0, there is an error\n");
		}
	}
	printf("exiting from MyShell()\n");
}
