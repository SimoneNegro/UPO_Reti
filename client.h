#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void check_arguments(int argc, char *argv);
void check_streaming_socket(int socket);
void check_connection(int connection, int socket);
void get_message(int socket, char *buffer, size_t buffer_size);

void check_arguments(int argc, char *argv)
{
    if (3 != argc)
    {
        fprintf(stderr, "Usage: %s <server> <port>\n", &argv[0]);
        exit(1);
    }
}

void check_streaming_socket(int socket)
{
    if (socket == -1)
    {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else
        fprintf(stderr, "Socket created!\n");
}

void check_connection(int connection, int socket)
{
    if (connection == 0)
        fprintf(stderr, "Connect successful!\n");
    else
    {
        fprintf(stderr, "Could not connect to address!\n");
        close(socket);
        exit(1);
    }
}

void get_message(int socket, char *buffer, size_t buffer_size)
{
    int return_status = read(socket, buffer, buffer_size);

    if (return_status > 0)
        printf("%d: %s", return_status, buffer);
    else
        fprintf(stderr, "Return Status = %d \n", return_status);
}