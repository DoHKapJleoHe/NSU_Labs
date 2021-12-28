#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

double razlojenie(unsigned long long N)
{
    double pi = 0;
    unsigned long long n = 0;

    while(N > 0)
    {
	pi += pow(-1, n) / (2*n + 1);
	n++;
	N--;
    }
    pi *= 4;

return pi;
}

int main(int argc, char* argv[])
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    int length = strlen(argv[1]);
    unsigned long long N = 0;
    for(int i = 0; i < length; i++)
    {
	N += (argv[1][i] - 48) * pow(10, length - i - 1);
    }
    double pi = razlojenie(N);
    printf("%f\n", pi);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time taken: %lf sec.\n", end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec));
return 0;
}
