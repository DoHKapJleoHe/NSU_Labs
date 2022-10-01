#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* newThread(void* arg)
{
    for(int i = 0; i < 5; i++)
    {
	printf("Hello from new thread!\n");
    }
    int* res = (int*)arg;
    *res = 5;
    int a = 5;

    return (void*)res;
}

int main()
{
    int err;
    pthread_t tid;
    int* res = (int*)malloc(sizeof(int));

    err = pthread_create(&tid, NULL, newThread, (void*)res);
    if(err != 0)
    {
	perror("Couldn't create new thread: ");

	return 0;
    }

    int tmp = 0;

    if(pthread_join(tid, (void**)&res) != 0)
    {
	perror("Couldn't join thread: ");

	return 0;
    }

    tmp = *res;

    printf("Result: %d\n", tmp);

    for(int i = 0; i < 5; i++)
    {
	printf("Hello from main thread!\n");
    }

    free(res);

    return 0;
}
