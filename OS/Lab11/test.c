#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	char* path = getenv("PATH");

	printf("PATH: %s\n", path);

	return 0;
}
