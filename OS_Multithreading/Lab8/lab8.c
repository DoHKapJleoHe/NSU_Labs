#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<math.h>

#define NUMBER_OF_STEPS 1000

typedef struct Params{
    int numOfThreads;
    int startPoint;
    double piPart;
}Params;

void* calculate(void* arg)
{
    double local_pi = 0.0;
    Params* prm = (Params*)arg;

    for(int i = prm->startPoint; i < NUMBER_OF_STEPS; i += prm->numOfThreads)
    {
	local_pi += pow(-1, i) / (2 * i + 1);
    }

    prm->piPart = local_pi;

    return prm;
}

int main(int argc, char* argv[])
{
    int err;
    char errbuf[30];

    if(argc != 2)
    {
	printf("Invalid argument: no argument!");
	return -1;
    }

    int tnum = atoi(argv[1]);
    pthread_t tids[tnum];

    double pi = 0;
    Params *params = (Params*)malloc( tnum * ( sizeof(Params) ) );

    for(int i = 0; i < tnum; i++)
    {
	params[i].numOfThreads = tnum;
	params[i].startPoint = i;
	params[i].piPart = 0.0;
    }

    for(int i = 0; i < tnum; i++)
    {
	if( ( err = pthread_create(&tids[i], NULL, calculate, (void*)&params[i]) ) != 0 )
	{
	    strerror_r(err, errbuf, 30);
	    printf("Couldn't create new thread: %s", errbuf);
	    return -1;
	}
    }

    for(int i = 0; i < tnum; i++)
    {
	Params* res;

	if( ( err = pthread_join(tids[i], (void**)&res) ) != 0 )
	{
	    strerror_r(err, errbuf, 30);
	    printf("Couldn't join thread: %s", errbuf);
	    return -1;
	}

	pi += res->piPart;
    }

    printf("Calculated pi = %.4f\n", pi * 4.0);

    return 0;
}
