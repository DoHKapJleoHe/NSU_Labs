#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

sem_t sem1;
sem_t sem2;

void* thread(void* arg)
{
    for(int i = 0; i < 5; i++)
    {
	sem_wait(&sem2);

	printf("Hello from thread!\n");

	sem_post(&sem1);
    }

    return NULL;
}

int main()
{
    int err;
    pthread_t tid;
    char errbuf[30];

    if( (err = sem_init(&sem1, 0, 1)) != 0 )
    {
	strerror_r(err, errbuf, 30);
	printf("Error while initializing se1 : %s\n", errbuf);
	return -1;
    }
    if( (err = sem_init(&sem2, 0, 0)) != 0 )
    {
	strerror_r(err, errbuf, 30);
	printf("Error while initializing sem2 : %s\n", errbuf);
	return -1;
    }

    if( (err = pthread_create(&tid, NULL, thread, NULL)) != 0 )
    {
	strerror_r(err, errbuf, 30);
	printf("Error while creating thread : %s\n", errbuf);
	return -1;
    }

    for(int i = 0; i < 5; i++)
    {
	sem_wait(&sem1);

	printf("Hello from main!\n");

	sem_post(&sem2);
    }

    if( (err = pthread_join(tid, NULL)) != 0 )
    {
	strerror_r(err, errbuf, 30);
	printf("Couldn't join thread : %s\n", errbuf);
	return -1;
    }

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    return 0;
}
