#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

/*
* Using struct to avoid length calculation in thread function.
* Any calculations in thread may lead to incorrect sorting 
*/
typedef struct sortStruct{
    int length;
    char* text;
}sortStruct;

void* sort(void* arg)
{
    sortStruct* pars = (sortStruct*)arg;

    sleep(0.5 * (pars->length));

    printf("%s\n", pars->text);

    return NULL;
}

int main(int argc, char* argv[])
{
    int err;
    char errbuf[30];
    pthread_t tids[100];

    sortStruct* params = (sortStruct*)malloc((argc-1) * sizeof(sortStruct));

    for(int i = 0; i < argc - 1; i++)
    {
	params[i].length = strlen(argv[1 + i]);
	params[i].text = argv[1 + i];
    }

    /*program name is included in argc, that's why i subtract 1 from argc*/
    for(int i = 0; i < argc - 1; i++)
    {
	if((err = pthread_create(&tids[i], NULL, sort, (void*)&params[i])) != 0)
	{
	    strerror_r(err, errbuf, 30);
	    printf("Couldn't create new thread: %s", errbuf);

	    return -1;
	}
    }

    for(int i = 0; i < argc - 1; i++)
    {
	if((err = pthread_join(tids[i], NULL)) != 0)
	{
	    strerror_r(err, errbuf, 30);
	    printf("Couldn't join thread: %s", errbuf);

	    return -1;
	}
    }

    free(params);

    return 0;
}
