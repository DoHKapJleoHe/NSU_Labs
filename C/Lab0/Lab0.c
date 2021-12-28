
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int char_to_dig(char c) {
	
	if (c >= 'a' && c <= 'z')
		c += 'A' - 'a';

	return (c >= 'A' && c <= 'Z') ? (10 + c - 'A') : (c - '0');
}

char dig_to_char(int n) {

	return (n >= 0 && n <= 9) ? ('0' + n) : ('A' - 10 + n);
}

	long double translate_to_10_drobnoe(int num_sys, char* number)
	{
		long double sum = 0;
		long long int integer_part = 0;
		int i = 0;
		char c = 0;


		for (i = 0; (c = *number) != '.'; ++i) {
			integer_part = (integer_part * num_sys) + char_to_dig(c);
			++number;
		}


		++number;


		for (i = 0; integer_part > 0; ++i) {
			sum += (integer_part % num_sys) * pow(num_sys, i);
			integer_part /= num_sys;
		}


		for (i = -1; (c = *number) != '\0'; --i) {
			sum += char_to_dig(c) * pow(num_sys, i);
			++number;
		}
		return sum;
	}

double translate_to_10_celoe(int num_sys, char* number) {
	long double sum = 0;
	long long int integer_part = 0;
	int i = 0;
	char c = 0;
	
	for (i = 0; (c = *number) != '\0'; ++i) {
		integer_part = (integer_part * num_sys) + char_to_dig(c);
		++number;
	}

	for (i = 0; integer_part > 0; ++i) {
		sum += (integer_part % num_sys) * pow(num_sys, i);
		integer_part /= num_sys;
	}
	return sum;
}

void translate(long double number, int num_sys) {
	int i = 0;
	char integer_result_end[100], fract_result_end[100];
	long long int integer_part = (long long int)number;
	long double fract_part = number - (long long int)number;

	do {
		integer_result_end[i++] = dig_to_char(integer_part % num_sys);
		integer_part /= num_sys;
	} while (integer_part);
	integer_result_end[i] = '\0';
	int len = i;
	for (i = 0; i < len / 2; ++i) {
		int temp = integer_result_end[i];
		integer_result_end[i] = integer_result_end[len - i - 1];
		integer_result_end[len - i - 1] = temp;
	}

	i = 0;
	while (fract_part > 0 && i < 12) {
		fract_part *= num_sys;
		integer_part = (long long int)fract_part;
		fract_part -= (long long int)fract_part;
		fract_result_end[i++] = dig_to_char(integer_part);
	}

	fract_result_end[i] = '\0';

	if (i == 0)
		printf("%s.0\n", integer_result_end);
	else
		printf("%s.%s\n", integer_result_end, fract_result_end);
}

int main() {

	int num_sys1 = 0;
	int num_sys2 = 0;
	char number[100];
	long double dec = 0;
	int fract_part = 0;
	if (1 != scanf("%d \n", &num_sys1))
	{
		printf("Bad input!");
		return 0;
	}
	if (1 != scanf("%d \n", &num_sys2))
	{
		printf("Bad input!");
		return 0;
	}
	if(!fgets(number, 100, stdin))
	{
	    printf("bad input\n");
	}

	if ((num_sys1 < 2 || num_sys1 > 16) || (num_sys2 < 2 || num_sys2 > 16)) 
	{
		printf("bad input\n");
		return 0;
	}

	char* p = number;
	if (*p == '.')
	{
		printf("bad input\n");
		return 0;
	}
	while (*p) {
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
	--p;
	if (*p == '.') 
	{
		printf("bad input\n");
		return 0;
	}

	if (fract_part > 1) 
	{
		printf("bad input\n");
		return 0;
	}

	if (fract_part)
		dec = translate_to_10_drobnoe(num_sys1, number);
	else
		dec = translate_to_10_celoe(num_sys1, number);

	translate(dec, num_sys2);

	return 0;
}

