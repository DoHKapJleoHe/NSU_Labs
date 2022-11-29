#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<pthread.h>

#define READER_BUFFER_LENGTH 256
#define REQUEST_BUFFER_LENGTH 1024
#define RESPONSE_BUFFER_LENGTH 256
#define ERROR_BUFFER_LENGTH 30

pthread_mutex_t stop_mutex;
pthread_cond_t cond;
int is_stopped = 0; // 1 - true, 0 - false
volatile int program_finished = 0; // 1 - true, 0 - false

void* send_request(void* arg)
{
    int sfd;
    int err;
    char errbuf[ERROR_BUFFER_LENGTH];
    char* port = "80";
    char* host = (char*)arg;

    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if((err = getaddrinfo(host, port, &hints, &result)) != 0)
    {
        strerror_r(err, errbuf, ERROR_BUFFER_LENGTH);
	    printf("Couldn't get host info: %s\n", errbuf);
	    return NULL;
    }

    if((sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1)
    {
        strerror_r(sfd, errbuf, ERROR_BUFFER_LENGTH);
	    printf("Couldn't create socket: %s\n", errbuf);
	    return NULL;
    }

    if((err = connect(sfd, result->ai_addr, result->ai_addrlen)) == -1)
    {
        strerror_r(err, errbuf, ERROR_BUFFER_LENGTH);
	    printf("Couldn't get host info: %s\n", errbuf);
	    return NULL;
    }

    char request[REQUEST_BUFFER_LENGTH];
    char request_template[] = "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";
    sprintf(request, request_template, host);
    write(sfd, request, REQUEST_BUFFER_LENGTH);

    char response_buffer[RESPONSE_BUFFER_LENGTH];
    int lines_typed = 0;
    while(1)
    {
        int nbytes = 0;
        // perhaps here should be a mutex lock while checking "is_stoped" value
        if(is_stopped != 1)
        {
            memset(&response_buffer, 0, RESPONSE_BUFFER_LENGTH);
            nbytes = read(sfd, response_buffer, RESPONSE_BUFFER_LENGTH);
            if(nbytes <= 0)
            {
                program_finished = 1; // инкремент лучше не делать, там требуется больше операций!!!!
                is_stopped = 1;
                pthread_cond_signal(&cond);
                break; 
            }
            else
            {
                write(1, response_buffer, nbytes);
                lines_typed++;
                if(lines_typed == 25)
                {
                    lines_typed = 0;
                    is_stopped = 1;
                    printf("\n----------PRESS ENTER TO SCROLL DOWN----------\n");

                    pthread_cond_signal(&cond);
                }
            }   
        }
    }

    return NULL;
}

void* console_reader(void* arg)
{
    while (1)
    {
        pthread_mutex_lock(&stop_mutex);
	    while(is_stopped != 1)
	    {
	        pthread_cond_wait(&cond, &stop_mutex);
	    }

        if(program_finished == 1)
        {
            break;
        }

        char reader_buffer[READER_BUFFER_LENGTH];
        read(0, reader_buffer, READER_BUFFER_LENGTH);

        is_stopped = 0;
        pthread_mutex_unlock(&stop_mutex);
    }

    return NULL;
}

int main(int argc, char* argv[])
{
    char* host = argv[1];
    int err;
    char errbuf[30];
    pthread_t server, console;

    if((err = pthread_mutex_init(&stop_mutex, NULL)) != 0)
    {
	    strerror_r(err, errbuf, ERROR_BUFFER_LENGTH);
	    printf("Error while initializing mutex : %s\n", errbuf);
	    return -1;
    }

    if( ( err = pthread_cond_init(&cond, NULL) ) != 0 )
    {
	    strerror_r(err, errbuf, ERROR_BUFFER_LENGTH);
	    printf("Error while initializing mutex : %s\n", errbuf);
	    return -1;
    }

    if( (err = pthread_create(&server, NULL, send_request, (void*)host)) != 0 )
    {
	    strerror_r(err, errbuf, ERROR_BUFFER_LENGTH);
	    printf("Error while creating thread : %s\n", errbuf);
	    return -1;
    }

    if( (err = pthread_create(&console, NULL, console_reader, NULL)) != 0 )
    {
	    strerror_r(err, errbuf, ERROR_BUFFER_LENGTH);
	    printf("Error while creating thread : %s\n", errbuf);
	    return -1;
    }

    if((err = pthread_join(server, NULL)) != 0)
    {
	    strerror_r(err, errbuf, ERROR_BUFFER_LENGTH);
	    printf("Couldn't join server thread : %s\n", errbuf);
	    return -1;
    }

    if((err = pthread_join(console, NULL)) != 0)
    {
	    strerror_r(err, errbuf, ERROR_BUFFER_LENGTH);
	    printf("Couldn't join console thread : %s\n", errbuf);
	    return -1;
    }

    pthread_mutex_destroy(&stop_mutex);
    return 0;
}
