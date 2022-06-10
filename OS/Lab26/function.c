#include<stdio.h>

int main(int argc, char* argv[])
{
	char text[7] = "hello\n";
	FILE* pipe = popen("./func", "w");
	if(pipe == NULL)
	{
		perror("failed to create pipe!");
		return 0;
	}

	fwrite(text, sizeof(char), 7, pipe);
	pclose(pipe);

	return 0;
}
