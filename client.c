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

int main(int argc, char *argv[])
{
    int simple_socket = 0;
    int simple_port = 0;
    int return_status = 0;
    char buffer[256] = "";
    struct sockaddr_in simple_server;

    check_arguments(argc, *argv);

    // create a streaming socket
    simple_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    check_streaming_socket(simple_socket);

    // retrieve the port number for connecting
    simple_port = atoi(argv[2]);

    // setup the address structure
    // use the IP address sent as an argument for the server address

    // bzero(&simple_server, sizeof(simple_server));
    memset(&simple_server, '\0', sizeof(simple_server));
    simple_server.sin_family = AF_INET;
    // inet_addr(argv[2], &simple_server.sin_addr.s_addr);
    simple_server.sin_addr.s_addr = inet_addr(argv[1]);
    simple_server.sin_port = htons(simple_port);

    // connect to the address and port with our socket
    return_status = connect(simple_socket, (struct sockaddr *)&simple_server, sizeof(simple_server));
    check_connection(return_status, simple_socket);

    // get the message from the server
    get_message(simple_socket, buffer, sizeof(buffer));

    close(simple_socket);
    return 0;
}

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

void get_message(int socket, char *buffer, size_t buffer_size) {
    int return_status = read(socket, buffer, buffer_size);

    if (return_status > 0)
        printf("%d: %s", return_status, buffer);
    else
        fprintf(stderr, "Return Status = %d \n", return_status);
}
