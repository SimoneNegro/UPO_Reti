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

const char MESSAGE[] = "Hello UPO student!\n";

int main(int argc, char *argv[])
{
    int simple_socket = 0;
    int simple_port = 0;
    int return_status = 0;
    struct sockaddr_in simple_server;

    check_arguments(argc, *argv);

    simple_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    check_streaming_socket(simple_socket);

    /* retrieve the port number for listening */
    simple_port = atoi(argv[1]);

    /* setup the address structure */
    /* use INADDR_ANY to bind to all local addresses  */
    memset(&simple_server, '\0', sizeof(simple_server));
    simple_server.sin_family = AF_INET;
    simple_server.sin_addr.s_addr = htonl(INADDR_ANY);
    simple_server.sin_port = htons(simple_port);

    /*  bind to the address and port with our socket  */
    return_status = bind(simple_socket, (struct sockaddr *)&simple_server, sizeof(simple_server));
    check_bind(return_status, simple_socket);

    /* lets listen on the socket for connections      */
    return_status = listen(simple_socket, 5);

    if (return_status == -1)
    {
        fprintf(stderr, "Cannot listen on socket!\n");
        close(simple_socket);
        exit(1);
    }

    while (1)
    {
        struct sockaddr_in clientName = {0};
        int simpleChildSocket = 0;
        int clientNameLength = sizeof(clientName);

        /* wait here */

        simpleChildSocket = accept(simple_socket, (struct sockaddr *)&clientName, &clientNameLength);

        if (simpleChildSocket == -1)
        {
            fprintf(stderr, "Cannot accept connections!\n");
            close(simple_socket);
            exit(1);
        }

        /* handle the new connection request  */
        /* write out our message to the client */
        write(simpleChildSocket, MESSAGE, strlen(MESSAGE));
        close(simpleChildSocket);
    }

    close(simple_socket);
    return 0;
}

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
