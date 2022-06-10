#include "sys/socket.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <poll.h>

#define POLL_SIZE 3

int main(int argc, char* argv[])
{
	struct sockaddr_un serv_addr;
	struct pollfd poll_set[POLL_SIZE];
	int numfds = 0;

	int sfd = socket(AF_UNIX, SOCK_STREAM, 0); //creating socket of server
        if (sfd == -1)
        {
                perror("error to create socket");
                return 0;
        }

	memset(&serv_addr, 0, sizeof(struct sockaddr_un)); // zero out addres
        serv_addr.sun_family = AF_UNIX; // set domain to addres
        strcpy(serv_addr.sun_path, "socket"); // set name to address(by this name client can connect to server)


	if (bind(sfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr_un)) == -1)
        {
		close(sfd);
                perror("Error while binding");
                return 0;
        }

        if (listen(sfd, 5) == -1) //listening on server's soket
        {
		close(sfd);
                perror("Error while listening");
                return 0;
        }

	memset(poll_set, '\0', sizeof(poll_set));
	poll_set[0].fd = sfd;
	poll_set[0].events = POLLIN;
	numfds++;

	int cfd;
	struct sockaddr_un cli_addr;
	char buf[100];
	int res = 0, bytes, cur_fds = 0;

	while(true)
	{
		int idx;

		res = poll(poll_set, numfds,1000 * 5); // waiting 10 seconds
		if(res == 0)
			break;
		if(res == -1)
		{
			perror("Error in poll");
			return 0;
		}

		cur_fds = numfds;
		for(idx = 0; idx < cur_fds; idx++)
		{
			if(poll_set[idx].revents == 0)
			{
				continue;
			}

			if(poll_set[idx].fd == sfd)
			{
				cfd = accept(sfd, NULL, NULL);

				poll_set[numfds].fd = cfd;
				poll_set[numfds].events = POLLIN;
				numfds++;
				printf("Client connected\n");
			}
			else if(poll_set[idx].revents == POLLIN)
			{
				bytes = 0;
				if((bytes = read(poll_set[idx].fd, buf, 100)) == 0)
				{
					perror("Couldn't read");
					return 0;
				}
				if(bytes > 0)
				{
					for(int i = 0; i < bytes; i++)
					{
						buf[i] = toupper(buf[i]);
					}
					write(1, buf, bytes);
					//bytes = read(poll_set[idx].fd, buf, 100);
				}
			}
			else
			{
				printf("Removing client...\n");
				close(poll_set[idx].fd);
				poll_set[idx].events = 0;
				poll_set[idx] = poll_set[idx + 1];
				numfds--;
			}

		}
	}

	for(int i = 0; i < numfds; i++)
	{
		close(poll_set[i].fd);
	}

	return 0;
}

