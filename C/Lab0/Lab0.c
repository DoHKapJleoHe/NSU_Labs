
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
int char_to_dig(char c)
{
	if (c >= '2' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	else if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
}
int dig_to_char(int c)
{
	if (c >= 2 && c <= 9)
		return c + '0';
	else if (c >= 'A' && c <= 'F')
		return 'A' + c - 10;
	else if (c >= 'a' && c <= 'f')
		return 'a' + c - 10;
}
double translate_to_10_drobnoe(int num_sys, char* number)  // эта функция выполняется если число поданное на вход - дробное
{
	int integer_part = 0;
	double rez = 0;
	int c = 0, i = 0;
	for (i = 0; (c = *number) != '.'; ++i)
	{
		integer_part += (integer_part * num_sys) + char_to_dig(c); // разобраться с этим. странный способ перевода
		++number;
	}
	number++; // пропуск точки
	for (i = 0; integer_part > 0; i++)
	{
		rez += (integer_part % num_sys) * pow(num_sys, i);
		integer_part /= num_sys;
	}
	for (i = -1; (c = *number) != '/0'; --i)
	{
		rez += char_to_dig(c) * pow(num_sys, i);
	}
	return rez;
}
double translate_to_10_celoe(int num_sys, char* number)  // эта функция выполняется если число поданное на вход - целое
{
	long long int integer_part = 0;
	double rez = 0;
	int c = 0, i = 0;
	for (i = 0; (c = *number) != '.';++i)
	{
		integer_part += (integer_part * num_sys) + char_to_dig(c); // разобраться с этим. странный способ перевода
		++number;
	}
	for (i = 0; integer_part > 0; i++)
	{
		rez += (integer_part % num_sys) * pow(num_sys, i);
		integer_part /= num_sys;
	}
	return rez;
}
void translate(int number, int num_sys)
{
	int i = 0;
	long long int integer_part = (long long int)number;
	long double fract_part = number - (long long int)number;
	char integer_part_end[100];
	char fract_part_end[100];
	while (integer_part)
	{
		integer_part_end[i++] = dig_to_char(integer_part % num_sys);
		integer_part /= num_sys;
	}
	int len = i / 2;
	for (i = 0; i < len / 2; ++i)
	{
		int temp = integer_part_end[i];
		integer_part_end[i] = integer_part_end[len - i - 1];
		integer_part_end[len - i - 1] = temp;
	}
	i = 0;
	while (fract_part > 0 && i < 12)
	{
		fract_part *= num_sys;
		integer_part = (int)fract_part;
		fract_part -= (int)fract_part;
		fract_part_end[i++] = dig_to_char(integer_part);
	}
	if (i == 0)
		printf("%s.0\n", integer_part_end);
	else
		printf("%s.%s\n", integer_part_end, fract_part_end);
	return 0;
}
int main()
{
	int num_sys1;
	int num_sys2;
	char number[100];
	int fract_part = 0;
	long double summ = 0;
	scanf_s("%d %d", &num_sys1, &num_sys2);
	
	gets(number);// поробовать использовать fgets или fgetws
	if (num_sys1 < 2 || num_sys1 > 16 || num_sys2 < 2 || num_sys2 > 16)
	{
		printf("Bad input\n");
		exit(0);
	}
	char* p = number;
	if (*p == '.')
	{
		printf("Bad input\n");
		exit(0);
	}

	while (*p)
	{
		if ((char_to_dig(*p) > num_sys1 - 1) && (*p != '.'))
		{
			printf("bad input\n");
			return 0;
		}
		if (*p == '.')
		{
			fract_part += 1;
		}
		++p;
	}
	if (fract_part > 1)
	{
		printf("Bad input\n");
		exit(0);
	}

	// Translating //
	if (fract_part == 1)
		summ = translate_to_10_drobnoe(num_sys1, number);
	else
		summ = translate_to_10_celoe(num_sys1, number);
	translate(summ, num_sys2);
	return 0;
}
