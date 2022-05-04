#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        pid_t fork_result = fork();
        if(fork_result == -1) // if fork did job his incorrectly
        {
                perror("Fork error");
                return 0;
        }
        if(fork_result == 0)
        {
                int execResult = execl("/bin/cat", "cat", argv[1], NULL); //last argument must be NULL
                if(execResult == -1)
                {
                        perror("execl error");
                        return 0;
                }
        }
        printf("Text written by parrent");
        return 0;
}
