#include <stdio.h>
#include <string.h> /* for strtok() */
#define MAX_COMMAND_LENGTH 128
#define MAX_NOUMBER_OF_COMMANDS 18
#define TRUE 1
#define FALSE 0

static void MyShell(void);
static int ToExit(const char* const _command);

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
	i = 0;
	while (TRUE) 
	{
		printf("\n\tMy prompt\n");
		fgets(command, MAX_COMMAND_LENGTH - 1, stdin);
		if (ToExit(command))
		{
			return;
		}
		commandsList[i] = strtok(command, delimiters);
		while (NULL != commandsList[i])
		{
			printf("\tInner while\n");
			printf("\tcommandsList[i] = %s\n", commandsList[i]);
			if (ToExit(commandsList[i]))
			{
				return;
			}
			++i;
			commandsList[i] = strtok(NULL, delimiters);
		}
		printf("outer while\n");
		pid = fork();
		if (pid > 0)
		{
			printf("\tparent started.\n");
			waitpid(-1, &status, 0);
			printf("\tparent code ended. status = %d\n", status);
		}
		else if (pid == 0)
		{
			printf("\t\tchild code\n");
			printf("commandsList[0] = %s \t commandsList[1] = %s\n", commandsList[0], commandsList[1]);
			execvp(commandsList[0], commandsList);
			printf("\t\tFail\n");
			break;
		}
		else
		{
			printf("pid < 0, there is an error\n");
		}
	}
	printf("exiting from MyShell()\n");
}

static int ToExit(const char* const _command)
{
	return (strcmp(_command, "exit\n") == 0) ? TRUE : FALSE;
}
