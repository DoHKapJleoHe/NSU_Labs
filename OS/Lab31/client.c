#include "sys/socket.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
	struct sockaddr_un cli_addr;

        int cfd = socket(AF_UNIX, SOCK_STREAM, 0);

        memset(&cli_addr, 0, sizeof(struct sockaddr_un));
        cli_addr.sun_family = AF_UNIX;

	strcpy(cli_addr.sun_path, "socket");

	if ( connect(cfd, (struct sockaddr*)&cli_addr, sizeof(struct sockaddr_un)) == -1 ) // connecting to server process
        {
       		perror("Error while connection");
                return 0;
        }

	write(cfd, "Hello\n", 6);
	sleep(2);
	write(cfd, "Hello2\n", 7);
	sleep(2);
	write(cfd, "Hello3\n", 7);
	sleep(3);
	close(cfd);

	return 0;
}
