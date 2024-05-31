#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void check_arguments(int argc, char *argv);
void check_streaming_socket(int simple_socket);
void check_bind(int return_status, int simple_socket);
void check_connection(int return_status, int simple_socket);
void check_child_connection(int simple_child_socket, int simple_socket);

const char MESSAGE[] = "Hello UPO student!\n";

void check_arguments(int argc, char *argv)
{
    if (2 != argc)
    {
        fprintf(stderr, "Usage: %s <port>\n", &argv[0]);
        exit(1);
    }
}

void check_streaming_socket(int simple_socket)
{
    if (simple_socket == -1)
    {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else
        fprintf(stderr, "Socket created!\n");
}

void check_bind(int return_status, int simple_socket)
{
    if (return_status == 0)
        fprintf(stderr, "Bind completed!\n");
    else
    {
        fprintf(stderr, "Could not bind to address!\n");
        close(simple_socket);
        exit(1);
    }
}

void check_connection(int return_status, int simple_socket)
{
    if (return_status == -1)
    {
        fprintf(stderr, "Cannot listen on socket!\n");
        close(simple_socket);
        exit(1);
    }
}

void check_child_connection(int simple_child_socket, int simple_socket)
{
    if (simple_child_socket == -1)
    {
        fprintf(stderr, "Cannot accept connections!\n");
        close(simple_socket);
        exit(1);
    }
}
