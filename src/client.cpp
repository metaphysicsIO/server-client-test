#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>


int create_socket()
{
    int s = socket(AF_INET, SOCK_STREAM, 0);

    if(s < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }

    return s;
}

int main()
{
    const char *peer_host = "localhost";
    const short peer_port = 1234;

    // Create the socket
    int s0 = create_socket(); //socket(AF_INET, SOCK_STREAM, 0);

    // Fill in the server IP address
    struct sockaddr_in server;
    int serverAddrLen;
    bzero(&server, sizeof(server));

    // resolve server addr
    struct hostent *host = gethostbyname(peer_host);

    server.sin_family = AF_INET;
    server.sin_port = htons(peer_port);

    // Write resolved IP of server to addr struct
    memmove(&(server.sin_addr.s_addr), host->h_addr_list[0], 4);

    // connect to server
    int conn = connect(s0, (struct sockaddr*) &server, sizeof(server));

    /* Server interaction*/
    char input[] = "Hello";
    int packet_size = 1024;

    // Send input to server.
    write(s0, input, sizeof(input));

    // RECV from server
    char buffer[packet_size];
    int res = read(s0, buffer, packet_size);

    // Print what server sends 
    std::cout << "<Server returns>: " << buffer << std::endl;

    return 0;
}
