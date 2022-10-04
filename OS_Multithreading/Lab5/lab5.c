#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void clean_up_handler(void* arg)
{
    printf("Hi! It is thread. I just finished working. Have a nice day!\n");
}

void* work(void* arg)
{
    //pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    pthread_cleanup_push(clean_up_handler, NULL);

    for(int i = 0; i < 1000000; i++)
    {
	printf("%d\n", i);
    }

    pthread_cleanup_pop(1);

    return NULL;
}

int main()
{
    int err;
    char errbuf[30];
    pthread_t tid;

    err = pthread_create(&tid, NULL, work, NULL);
    if(err != 0)
    {
	strerror_r(err, errbuf, 30);
	printf("Couldn't create thread: %s", errbuf);

	return -1;
    }

    sleep(2);

    int* status;
    if((err = pthread_cancel(tid)) != 0)
    {
	strerror_r(err, errbuf, 30);
	printf("Error during cancelation: %s", errbuf);

	return -1;
    }

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
