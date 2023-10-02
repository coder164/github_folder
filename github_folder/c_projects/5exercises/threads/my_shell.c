#include <stdio.h>
#include <string.h> /* for strtok */
#define MAX_STR_SIZE 128
#define MAX_COMMANDS 18
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
	char strCommand[MAX_STR_SIZE];
	char* strParameters[MAX_COMMANDS];
	const char commandEnd[] = " \n";
	int status, i, pid;
	char* token;
	while (TRUE) 
	{
		i = 1;
		printf("\n\tMy prompt\n");
		fgets(strCommand, MAX_STR_SIZE - 1, stdin);
		if (ToExit(strCommand))
		{
			return;
		}
		strParameters[i - 1] = strtok(strCommand, commandEnd);
		while (strParameters[i] != NULL)
		{
			strParameters[i] = strtok(NULL, commandEnd);
			token = strtok(NULL, commandEnd);
			printf("\t\tInner while\n");
			printf("\t\tstrParameters[%d] = %s\n", i, strParameters[i]);
			if (ToExit(strParameters[i]))
			{
				return;
			}
			++i;
		}
		printf("\touter while\n");
		pid = fork();
		if (pid > 0)
		{
			printf("\tparent started.\n");
			printf("\tpid = %d\n", pid);
			waitpid(-1, &status, 0);
			printf("\tparent code ended. status = %d\n", status);
		}
		else if (pid == 0)
		{
			printf("\t\tchild code\n");
			printf("\t\tpid = %d\n", pid);
			execvp(strParameters[0], strParameters);
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
