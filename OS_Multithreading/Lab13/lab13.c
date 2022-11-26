#include<stdio.h>
#include<string.h>
#include<pthread.h>

// 0 - main, 1 - thread
int typingNow = 0;

pthread_cond_t cond;
pthread_mutex_t mutex;

void print_error(int err)
{
    char errbuf[30];

    strerror_r(err, errbuf, 30);
    printf("Error occured: %s\n", errbuf);
}

void* thread(void* arg)
{
    int err;

    for(int i = 0; i < 5; i++)
    {
	pthread_mutex_lock(&mutex);
	while(typingNow != 1)
	{
	    if( (err = pthread_cond_wait(&cond, &mutex)) != 0 )
	    {
		print_error(err);
		return NULL;
	    }
	}
	printf("Hello from thread!\n");
	typingNow = 0;

	if( (err = pthread_cond_signal(&cond)) != 0 )
	{
	    print_error(err);
	    return NULL;
	}
	pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char* argv[])
{
    int err;
    pthread_t tid;

    if( ( err = pthread_mutex_init(&mutex, NULL) ) != 0 )
    {
	print_error(err);
	return -1;
    }

    if( ( err = pthread_cond_init(&cond, NULL) ) != 0 )
    {
	print_error(err);
	return -1;
    }

    if( ( err = pthread_create(&tid, NULL, thread, NULL) ) != 0 )
    {
	print_error(err);
	return -1;
    }

    for(int i = 0; i < 5; i++)
    {
	pthread_mutex_lock(&mutex);
	while(typingNow != 0)
	{
	    if( (err = pthread_cond_wait(&cond, &mutex)) != 0 )
	    {
		print_error(err);
		return -1;
	    }
	}

	printf("Hello from main!\n");
	typingNow = 1;

	if( (err = pthread_cond_signal(&cond)) != 0 )
	{
	    print_error(err);
	    return -1;
	}
	pthread_mutex_unlock(&mutex);
    }


    if( ( err = pthread_join(tid, NULL) ) != 0 )
    {
	print_error(err);
	return -1;
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
