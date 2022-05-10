#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
        int fd[2];

        if(pipe(fd) == -1)
        {
                perror("Couldn't create pipe");
                return 0;
        }

        pid_t child1;
        pid_t child2;

        child1 = fork();
        if(child1 == -1)
        {
                perror("Couldn't create child1");
                return 0;
        }
        if(child1 == 0)
        {
                close(fd[0]);
                write(fd[1], "hello\n", 6);
                close(fd[1]);
        }

        child2 = fork();
        if(child2 == -1)
        {
                perror("Couldn't create child2");
                return 0;
        }
        if(child2 == 0)
        {
                char temp[6];
                close(fd[1]);
                read(fd[0], temp, 6);
                for(int i = 0; i <= 5; i++)
                {
                        temp[i] = toupper(temp[i]);
                }
                fflush(stdout);
                write(1, temp, 6);
                close(fd[0]);
                //printf("%s", temp);

        }

        close(fd[0]);
        close(fd[1]);
        return 0;
}
