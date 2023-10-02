#include <stdio.h>

int g_i = 5;
int main()
{
	int j = 8;
	size_t pid;
	sleep(10);
	pid = fork();
	
	/* child */
	if (pid == 0)
	{
		printf("g_i: %d \tj: %d\n", g_i, j);
		j = 25;
		g_i = 50;
		printf("g_i: %d \tj: %d\n", g_i, j);
		sleep(10);
	}
	
	/* father */
	if (pid > 0)
	{
		printf("g_i: %d \tj: %d\n", g_i, j);
		j = 10;
		g_i = 20;
		printf("g_i: %d \tj: %d\n", g_i, j);
		sleep(5); /* the normal condition */
		/* sleep(20); here shold be zombie because the child is done while the father is not, then the father can't get the return status of the child process. so the child remain as a zombie untill the father process ends. Z+ <defunct> */
	}

	return 0;
}

/*
to show all processes in the terminal write in a separate terminal:
ps -n
*/
