#include "sys/socket.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
        struct sockaddr_un addrs;

        int sfd = socket(AF_UNIX, SOCK_STREAM, 0); //creating socket of server
        if (sfd == -1)
        {
                perror("error to create socket");
                return 0;
        }

        memset(&addrs, 0, sizeof(struct sockaddr_un)); // zero out addres
        addrs.sun_family = AF_UNIX; // set domain to addres
        strcpy(addrs.sun_path, "socket"); // set name to address(by this name client can connect to server)

        if (bind(sfd, (struct sockaddr*)&addrs, sizeof(struct sockaddr_un)) == -1)
        {
                perror("Error while binding");
                return 0;
        }

        if (listen(sfd, 1) == -1) //listening on server's soket
        {
                perror("Error while listening");
                return 0;
        }

        pid_t child_pid = fork();
        if (child_pid == -1)
        {
                perror("Error while fork! Couldn't create child");
                return 0;
        }

        if (child_pid == 0)
        {
                struct sockaddr_un addrc;

                int cfd = socket(AF_UNIX, SOCK_STREAM, 0); // creating socket of client
                if (cfd == -1)
                {
                        perror("Couldn't create socket");
                        return 0;
                }

                memset(&addrc, 0, sizeof(struct sockaddr_un));
                addrc.sun_family = AF_UNIX;
                strcpy(addrc.sun_path, "socket");

                if (connect(cfd, (struct sockaddr*)&addrc, sizeof(struct sockaddr_un)) == -1) // connecting to server process
                {
                        perror("Error while connection");
                        return 0;
                }

                write(cfd, "hello", 5); //writing to socket
                close(cfd);
                //close(sfd);
        }
        else
        {
                int afd = accept(sfd, NULL, NULL);
                if (afd == -1)
                {
                        perror("Error while accepting");
                        return 0;
                }

                char buf[10];

                int read_byte = read(afd, buf, 10);
                for (int i = 0; i < read_byte; i++)
                {
                        buf[i] = toupper(buf[i]);
                }
                write(1, buf, 5);
                close(sfd);
                close(afd);
        }
}

