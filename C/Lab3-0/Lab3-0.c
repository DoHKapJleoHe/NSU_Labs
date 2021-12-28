#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(int a[], int n, int i) 
{
	while (2 * i + 1 < n)
	{
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int Max_Element = left;
		if (right < n && a[right] > a[left]) 
		{
			Max_Element = right;
		}
		if (a[i] >= a[Max_Element])
		{
			break;
		}
		swap(&a[i], &a[Max_Element]);
		i = Max_Element;
	}
}

void heapSort(int a[], int n) 
{
	int i = 0;
	for (i = n / 2 - 1; i >= 0; --i)
		heapify(a, n, i);
	for (i = n - 1; i > 0; --i) 
	{
		swap(&a[0], &a[i]);
		heapify(a, i, 0);
	}
}

int main(void) 
{
	int length = 0;
	if (1 != scanf("%d", &length)) // получаем длину массива
	{
		printf("end");
		return 0;
	}
	int* a = (int*)malloc(length * sizeof(int)); // выделяем память
	for (int i = 0; i < length; ++i) {
		if (1 != scanf("%d", &a[i])) // заполняем массив
		{
			printf("end");
			return 0;
		}
	}
	heapSort(a, length);
	for (int i = 0; i < length; ++i)  // вывод
	{
		printf("%d ", a[i]);
	}
	free(a);
	return 0;
}
