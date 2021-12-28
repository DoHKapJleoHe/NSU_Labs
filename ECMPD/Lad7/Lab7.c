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

void straight(int size)
{
    int* arr_straight = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        arr_straight[i] = (i + 1) % size;
    }

    int k = 0;
    /// Warming up cache ///
    for (int i = 0; i < size; i++)
    {
        k = arr_straight[k];
    }
    ////////////////////////

    k = 0;
    unsigned long long tmp = 0;
    for (int j = 0; j < 100; j++)
    {
        uint64_t start = rdtsc();
        for (int i = 0; i < size; i++)
        {
            k = arr_straight[k];
        }
        uint64_t end = rdtsc();
        
        tmp += (unsigned long long)(end - start) / size;
    }
    if (k == 123456)
    {
        printf("It's a prank bro!!");
    }

    printf("Average  straight time: %llu\n", tmp / 100);
    printf("%d %llu\n", size, tmp / 100);
    free(arr_straight);
}

void reverse(int size)
{
    int* arr_reverse = (int*)malloc(size * sizeof(int));
    arr_reverse[0] = size - 1;
    for (int i = 1; i < size; i++)
    {
        arr_reverse[i] = i - 1;
    }

    int k = 0;
    /// Warming up cache ///
    for (int i = 0; i < size; i++)
    {
        k = arr_reverse[k];
    }
    ////////////////////////

    k = 0;
    unsigned long long tmp = 0;
    for (int j = 0; j < 100; j++)
    {
        uint64_t start = rdtsc();
        for (int i = 0; i < size; i++)
        {
            k = arr_reverse[k];
        }
        uint64_t end = rdtsc();

        tmp += (unsigned long long)(end - start) / size;
    }
    if (k == 123456)
    {
        printf("It's a prank bro!!");
    }

    printf("Average reverse time: %llu\n", tmp / 100);
    printf("%d %llu\n", size, tmp / 100);
    free(arr_reverse);
}

void random(int size)
{
    int* arr_random = (int*)malloc(size * sizeof(int));
    if (arr_random == NULL)
        exit(0);
    
    int* arr_1 = (int*)malloc(size * sizeof(int));
    if (arr_1 == NULL)
        exit(0);
    for (int i = 0; i < size; i++)
    {
        arr_1[i] = i;       // filled array with numbers
    }

    int temp = 0;
    int j = 0;
    for (int i = 1; i < size; i++)
    {
        j = rand() % size;
        temp = arr_1[j];
        arr_1[j] = arr_1[i];
        arr_1[i] = temp;
    }

    for (int i = 0; i < size; i++)
    {
        arr_random[arr_1[i]] = arr_1[(i + 1) % size];
    }

    int k = 0;
    /// Warming up cache ///
    for (int i = 0; i < size; i++)
    {
        k = arr_random[k];
    }
    ////////////////////////

    k = 0;
    unsigned long long tmp = 0;
    for (int j = 0; j < 100; j++)
    {
        uint64_t start = rdtsc();
        for (int i = 0; i < size; i++)
        {
            k = arr_random[k];
        }
        uint64_t end = rdtsc();
        
        tmp += (unsigned long long)(end - start) / size;
    }
    if (k == 123456)
    {
        printf("It's a prank bro!!");
    }

    printf("Average random time: %llu\n", tmp / 100);
    printf("%d %llu\n", size, tmp / 100);
    free(arr_random);
}

int main(int argc, char* argv[])
{
    int size = 8;

    // putting CPU on the operating frequency
    int mat_size = 500;
    int* matrix_1 = (int*)malloc(mat_size * mat_size * sizeof(int));
    int* matrix_2 = (int*)malloc(mat_size * mat_size * sizeof(int));

    for (int i = 0; i < mat_size; i++)
    {
        for (int k = 0; k < mat_size; k++)
        {
            for (int j = 0; j < mat_size; j++)
            {
                matrix_1[i * mat_size + j] = matrix_1[i * mat_size + k] + matrix_2[k * mat_size + j];
            }
        }
    }
    free(matrix_1);
    free(matrix_2);
    /////////////////////////////////////////

    for (int i = 0; i < 80; i++)
    {
        straight(size);
        printf("+=+=+=+=+=+=+=+=+=+=\n");
        reverse(size);
        printf("+=+=+=+=+=+=+=+=+=+=\n");
        random(size);
        printf("---------------------\n");
        printf("---------------------\n");
        size *= 1.2;
    }
}
