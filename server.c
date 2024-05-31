#include <server.h>

int main(int argc, char *argv[])
{
    int simple_socket = 0;
    int simple_port = 0;
    int return_status = 0;
    struct sockaddr_in simple_server;

    check_arguments(argc, *argv);

    simple_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    check_streaming_socket(simple_socket);

    // retrieve the port number for listening 
    simple_port = atoi(argv[1]);

    // setup the address structure 
    // use INADDR_ANY to bind to all local addresses
    memset(&simple_server, '\0', sizeof(simple_server));
    simple_server.sin_family = AF_INET;
    simple_server.sin_addr.s_addr = htonl(INADDR_ANY);
    simple_server.sin_port = htons(simple_port);

    // bind to the address and port with our socket
    return_status = bind(simple_socket, (struct sockaddr *)&simple_server, sizeof(simple_server));
    check_bind(return_status, simple_socket);

    // lets listen on the socket for connections
    return_status = listen(simple_socket, 5);
    check_connection(return_status, simple_socket);

    while (1)
    {
        struct sockaddr_in client_name = {0};
        int simple_child_socket = 0;
        int client_name_length = sizeof(client_name);

        // wait here

        simple_child_socket = accept(simple_socket, (struct sockaddr *)&client_name, &client_name_length);
        check_child_connection(simple_child_socket, simple_socket);

        // handle the new connection request
        // write out our message to the client
        write(simple_child_socket, MESSAGE, strlen(MESSAGE));
        close(simple_child_socket);
    }

    close(simple_socket);
    return 0;
}
