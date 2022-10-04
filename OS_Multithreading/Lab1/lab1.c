#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* newThread(void* arg)
{
    for(int i = 0; i < 5; i++)
    {
	printf("Hello from new thread!\n");
    }

    pthread_exit(NULL);
}

int main()
{
    int err;
    pthread_t tid;

    err = pthread_create(&tid, NULL, newThread, NULL);
    if(err != 0)
    {
	perror("Couldm't create new thread: ");
	return -1;
    }

    for(int i = 0; i < 5; i++)
    {
	printf("Hello from main thread!\n");
    }

    pthread_exit(NULL);
}
