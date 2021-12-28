#define CRT_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

int partition(int a[], int left, int right)
{
	int piv = a[(left + right) / 2];
	int left_1 = left,
		right_1 = right;
	while (left_1 <= right_1)
	{
		while (a[left_1] < piv)
		{
			left_1++;
		}
		while (a[right_1] > piv)
		{
			right_1--;
		}
		if (left_1 >= right_1)
			break;
		int temp = a[left_1];
		a[left_1] = a[right_1];
		a[right_1] = temp;

		left_1++;
		right_1--;
	}
	return right_1;
}

void QuickSort(int a[], int left, int right)
{
	if (left < right)
	{
		int q = partition(a, left, right);
		QuickSort(a, left, q);
		QuickSort(a, q + 1, right);
	}
}

int main(void)
{
	int length = 0;
	if (1 != scanf("%d", &length))
	{
		printf("end");
		return 0;
	}
	int* a = (int*)malloc(length * sizeof(int));
	for (int i = 0; i < length; ++i)
	{
		if (1 != scanf("%d", &a[i]))
		{
			printf("end");
			return 0;
		}
	}
	QuickSort(a, 0, length - 1);
	for (int i = 0; i < length; i++)
	{
		printf("%d\n", a[i]);
	}
	free(a);
	return 0;
}
