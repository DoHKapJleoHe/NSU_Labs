#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;

pthread_mutexattr_t attrs;

int thread_locked_mutex = 0;

void* thread(void* arg)
{
    pthread_mutex_lock(&mutex2);

    thread_locked_mutex = 1;

    for(int i = 0; i < 5; i++)
    {
	pthread_mutex_lock(&mutex1);
	printf("Hello from thread!\n");
	pthread_mutex_unlock(&mutex2);
	pthread_mutex_lock(&mutex3);
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex2);
	pthread_mutex_unlock(&mutex3);
    }

    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main(int argc, char* argv[])
{
    int err;
    char errbuf[30];
    pthread_t tid;

    pthread_mutexattr_settype(&attrs, PTHREAD_MUTEX_ERRORCHECK);

    if((err = pthread_mutex_init(&mutex1, &attrs)) != 0)
    {
	strerror_r(err, errbuf, 30);
	printf("Couldn't initialize mutex: %s", errbuf);

	return -1;
    }

    if((err = pthread_mutex_init(&mutex2, &attrs)) != 0)
    {
	strerror_r(err, errbuf, 30);
	printf("Couldn't initialize mutex: %s", errbuf);

	return -1;
    }

    if( (err = pthread_mutex_init(&mutex3, &attrs)) != 0 )
    {
	strerror_r(err, errbuf, 30);
	printf("Couldn't initialize mutex3: %s", errbuf);

	return -1;
    }

    pthread_mutex_lock(&mutex1);

    if((err = pthread_create(&tid, NULL, thread, NULL)) != 0)
    {
	strerror_r(err, errbuf, 30);
	printf("Couldn't create thread: %s", errbuf);

	return -1;
    }

    while(!thread_locked_mutex)
    {
	sched_yield();
    }

    for(int i = 0; i < 5; i++)
    {
	printf("Hello from main!\n");
	pthread_mutex_lock(&mutex3);
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_lock(&mutex2);
	pthread_mutex_unlock(&mutex3);
	pthread_mutex_lock(&mutex1);
	pthread_mutex_unlock(&mutex2);
    }

    pthread_mutex_unlock(&mutex1);

    if((err = pthread_join(tid, NULL)))
    {
	strerror_r(err, errbuf, 30);
	printf("Couldn't join thread: %s", errbuf);

	return -1;
    }

    pthread_mutexattr_destroy(&attrs);
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    pthread_mutex_destroy(&mutex3);

    return 0;
}
