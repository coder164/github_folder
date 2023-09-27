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
		sleep(10);
	}
	
	/* father */
	if (pid > 0)
	{
		printf("g_i: %d \tj: %d\n", g_i, j);
		j = 10;
		g_i = 20;
		sleep(20);
	}

	return 0;
	
}
