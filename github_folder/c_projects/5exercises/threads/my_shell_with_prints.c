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
	const char delimiters[] = "\n";
	int status, i, pid;
	char* token;
	i = 1;
	while (TRUE) 
	{
		printf("\n\tMy prompt\n");
		fgets(strCommand, MAX_STR_SIZE - 1, stdin);
		if (ToExit(strCommand))
		{
			return;
		}
		token = strtok(strCommand, delimiters);
		strParameters[i - 1] = token;
		while (NULL != strParameters[i - 1])
		{
			printf("\t\tInner while\n");
			printf("\t\ttoken = %s\n", token);
			if (ToExit(token))
			{
				return;
			}
			token = strtok(NULL, delimiters);
			strParameters[i] = token;
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
