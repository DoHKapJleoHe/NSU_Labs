#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<sys/syscall.h>

void* work(void* arg)
{
    pid_t tid;
    tid = syscall(SYS_gettid);

    char** t;

    for(t = (char**)arg + 1; *t != NULL; t++)
    {
	printf("Thread id: %d ", tid);
	printf("%s\n", *t);
    }

    return NULL;
}

int main(int argc, char* argv[])
{
    int err;
    pthread_t tids[4];
    char errbuf[100];

    for(int i = 0; i < 4; i++)
    {
	err = pthread_create(&tids[i], NULL, work, (void*)argv);
	if(err != 0)
	{
	    strerror_r(err, errbuf, 100);
	    printf("Error occured: %s", errbuf);

	    return 0;
	}
    }

    for(int i = 0; i < 4; i++)
    {
	if((err = pthread_join(tids[i], NULL)) != 0)
	{
	    strerror_r(err, errbuf, 100);
	    printf("Error occured: %s", errbuf);

	    return 0;
	}
    }

    return 0;
}
