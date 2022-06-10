#include <stdio.h>
#include <unistd.h>

int execvpe(char* file, char* argv[], char* envp[])
{
	extern char** environ;
	environ = envp;

	execvp(file, argv);

	return 0;
}

int main(int argc, char* argv[])
{
	char* new_env[2] = {"PATH=/home/students/20200/e.vartazaryan/Lab11", NULL};

	execvpe(argv[1], &argv[1], new_env);

	return 0;
}
