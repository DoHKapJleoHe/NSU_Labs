// Алгоритм Нараяны
#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int FindMaxIndex(int* number, int k)
{
    for (int i = k - 2; i >= 0; i--)
    {
        if (number[i] < number[i + 1])
            return i;
    }
    return -1;
}

int FindMaxIndexBigger(int* number, int element, int k)
{
    for (int i = k - 1; i > 0; i--)
    {
        if (number[i] > element)
            return i;
    }
    return -1;
}

int swap(int* number, int i, int j)
{
    int temp = number[i];
    number[i] = number[j];
    number[j] = temp;
    return 0;
}

int reverse(int* number, int index, int k)
{
    for (int i = index + 1, j = k - 1; i < j; i++, j--)
    {
        int temp = number[i];
        number[i] = number[j];
        number[j] = temp;
    }
    return 0;
}

int perestanovka(int* number, int k)
{
    for (int i = 0; i < k; i++)
        printf("%d", number[i]);
    return 0;
}

int main(void)
{
    int n = 0;
    int N = 0;
    int k = 0;
    char c = ' ';
    int number[100];
    while (1 == scanf("%c", &c))
    {
        if (c == '\n')
            break;
        else
        {
            int temp = c - '0';
            if (temp < 0 || temp > 9)
            {
                printf("bad input!");
                return 0;
            }
            number[k++] = temp;
        }
    }
    if (1 != scanf("%d", &N))
    {
        printf("bad input!");
        return 0;
    }
     if(k == 1)
    {
        return 0;
    }
    int oshibka = 0;
    for(int i = 0; i < k - 1; i++)
    {
        for(int j = i + 1; j < k; j++)
        {
            if(number[i] == number[j])
            oshibka += 1;
        }
    }
    if (oshibka > 0)
    {
        printf("bad input!");
        return 0;
    }
    while (n < N)
    {
        int index = FindMaxIndex(number, k);
        if (index == -1)
        {
            return 0;
        }
        int element = number[index];
        int swapindex = FindMaxIndexBigger(number, element, k);
        swap(number, index, swapindex);
        reverse(number,index,k);
        perestanovka(number, k);
        printf("\n");
        n++;
    }
    
    return 0;
}
