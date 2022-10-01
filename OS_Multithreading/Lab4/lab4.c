#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* work(void* arg)
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    for(int i = 0; i < 1000000000; i++)
    {
	printf("%d\n", i);
    }

    return NULL;
}

int main()
{
    int err;
    pthread_t tid;
    char errbuf[30];

    err = pthread_create(&tid, NULL, work, NULL);
    if(err != 0)
    {
	strerror_r(err, errbuf, 30);
	printf("Couldn't create thread: %s", errbuf);

	return -1;
    }

    sleep(2);

    if((err = pthread_cancel(tid)) != 0)
    {
	strerror_r(err, errbuf, 30);
	printf("Error during cancelation: %s", errbuf);

	return -1;
    }

    int* status;

    if((err = pthread_join(tid, (void**)&status)) != 0)
    {
	strerror_r(err, errbuf, 30);
	printf("Couldn't join: %s", errbuf);

	return -1;
    }

    if(status == PTHREAD_CANCELED)
	printf("Thread was succesfuly canceled!\n");

    return 0;
}
