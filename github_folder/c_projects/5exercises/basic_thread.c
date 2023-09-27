#include <stdio.h>
#include <pthread.h>
#define SIZE 1000
#define NUM_OF_THREADS 20
int globalNum = 0;

void *PrintFunc(void* _tid)
{
	int i;
	for (i = 0; i < SIZE; ++i, ++globalNum)
	{
		printf("threadNum: %d \tlocalvar: %d \t gloablNum: %d\n",
			*(int*)_tid, i, globalNum);
	}
	pthread_exit(NULL);
}

int main()
{
	int i, status, threadsNum[NUM_OF_THREADS];
	pthread_t threadsId[NUM_OF_THREADS];
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		threadsNum[i] = i;
		status = pthread_create(&threadsId[i], NULL, PrintFunc,
								&threadsNum[i]);
		if (status != 0)
		{
			printf("pthread_create() failed!\n");
		}
		pthread_join(threadsId[i], NULL);
	}
	return 0;	
}

/* to compile add -pthread at the end of the compilation comand.
for example:
gcc -ansi -pedantic -g thread.c -pthread
*/
