#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/select.h>
#include<sys/socket.h>

int main(int argc, char* argv[])
{
    int cfd;
    char* port = "80";
    fd_set fds;
    struct addrinfo hints;
    struct addrinfo *result;

    FD_ZERO(&fds);
    FD_SET(0, &fds); // 0 reserved for stdin

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(argv[1], port, &hints, &result) != 0)
    {
        perror("Couldn't get info about host... ");
        return 0;
    }

    if((cfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1)
    {
        perror("Couldn't create socket... ");
        return 0;
    }

    if(connect(cfd, result->ai_addr, result->ai_addrlen) == -1)
    {
        perror("Error while connection to host... ");
        return 0;
    }

    char request[1024];
    char request_template[] = "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";
    sprintf(request, request_template, argv[1]);
    write(cfd, request, 1024); //sending GET request

    FD_SET(cfd, &fds);

    char response_buffer[256];
    char reading_buffer[256];
    int lines_typed = 0;
    int is_stopped = 0; // 1 - true, 0 - false
    int program_finished = 0; // 1 - true, 0 - false
    int all_response = 0;

    while(!program_finished)
    {
	    int err = select(cfd + 1, &fds, NULL, NULL, NULL);

	    if(err < 0)
	    {
	        perror("Select error...\n");
	        break;
	    }
	    else
	    {
	        if( FD_ISSET(0, &fds) )
	        {
               	    is_stopped = 0;
                    read(0, reading_buffer, 256);
	        }
	        if( FD_ISSET(cfd, &fds) )
	        {
		    //reading response
		    int nbytes;

                    if(is_stopped != 1)
                    {
		        nbytes = read(cfd, response_buffer, 256);
                        if(nbytes <= 0)
                        {
                            program_finished = 1; 
                        }
                        else
                        {
		            write(1, response_buffer, 256);
                            lines_typed++;
                            if(lines_typed == 25)
                            {
                                lines_typed = 0;
                                is_stopped = 1;
                                printf("\n----------PRESS SPACE TO SCROLL DOWN----------\n");
                            }
                            memset(&response_buffer, 0, sizeof(char));
                        }   
                    }
	        }
	    }

        // select changing given set of file decriptiors that's why i need to always set them after use
        FD_SET(0, &fds);
        FD_SET(cfd, &fds);

        if(program_finished == 1)
            break;
    }

    close(cfd);
    return 0;
}
