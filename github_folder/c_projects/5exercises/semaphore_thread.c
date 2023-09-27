#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SLOTS_NUM_IN_BUFFER 100
#define TRUE 1
#define FALSE 0

sem_t mutex;
sem_t empty;
sem_t full;

void* Producer(void* arg);
void* Consumer(void* arg);
int counter = 0;

int main()
{
	pthread_t t1, t2, t3;
	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, SLOTS_NUM_IN_BUFFER);
	sem_init(&full, 0, 0);
	pthread_create(&t1, NULL, Producer, NULL);
	pthread_create(&t2, NULL, Consumer, NULL);
	pthread_create(&t3, NULL, Consumer, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	return 0;	
}

void* Producer(void* arg)
{
	while(TRUE)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		++counter;
		printf("%d\n", counter);
		sem_post(&mutex);
		sem_post(&full);
	}
}

void* Consumer(void* arg)
{
	while(TRUE)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		--counter;
		printf("%d\n", counter);
		sem_post(&mutex);
		sem_post(&empty);
	}
}

/*
syntax from: 
https://www.ibm.com/docs/en/i/7.4?topic=ssw_ibm_i_74/apis/ipcsemi.html
https://man7.org/linux/man-pages/man7/sem_overview.7.html
to link with -pthread 
*/
