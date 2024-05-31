#include <client.h>

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
