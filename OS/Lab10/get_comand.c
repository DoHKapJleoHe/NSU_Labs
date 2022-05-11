#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
        pid_t pid = fork();
        if(pid == -1)
        {
                perror("Couldn't create child");
                return 0;
        }

        if(pid == 0)
        {
                int execResult = execvp(argv[1], argv + 1);
                if(execResult == -1)
                {
                        perror("exec error");
                        return 0;
                }
        }
        int sig;
        pid_t wait_res = wait(&sig);

        printf("Exit signal = %d\n", sig);


        return 0;
}

