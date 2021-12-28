#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<malloc.h>
#ifdef _WIN32
#include <intrin.h>
uint64_t rdtsc()
{
	return __rdtsc();
}
#else
uint64_t rdtsc() 
{
	unsigned int lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t)hi << 32) | lo;
}
#endif



void calc_time(int fragments_number)
{
	int ofset = 4 * 1024 * 1024; // размер кэша третьего уровня, а именно 4 МБайта
	int size = ofset * fragments_number;
	int fragment_size = ofset / fragments_number;

	// making linked list in array (value of every element is an index of the following element)
	int* arr = (int*)malloc(size * sizeof(int));
	for (int n = 0; n < fragments_number - 1; n++)
	{
		for (int i = 0; i < fragment_size; i++)
		{
			arr[ofset * n + i] = ofset * (n + 1) + i;
		}
	}

	for (int i = 0; i < fragment_size; i++)
		arr[(fragments_number - 1) * ofset + i] = (i + 1) % fragment_size;

	// traversing the array
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		k = arr[k];
	}
	
	k = 0;
	int min = 9999999;
	for (int i = 0; i < 500; i++)
	{
		uint64_t start = rdtsc();
		for (int j = 0; j < 10000; j++)
		{
			k = arr[k];
		}
		uint64_t end = rdtsc();

		if (end - start < min)
			min = end - start;
	}
	if (k == 1234567)
		printf("!!KEKW!!");
	double avg = static_cast<double>(min / 10000);
	printf("%d %lf\n", fragments_number, avg);
	free(arr);
}

int main(int argc, char* argv[])
{
	for (int fragments_number = 1; fragments_number <= 32; fragments_number++)
	{
		calc_time(fragments_number);
	}
}
