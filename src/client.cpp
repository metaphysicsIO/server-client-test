#include <iostream>
#include <sstream>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <bitset>
 
int main(int argc, char *argv[])
{
    // Create socket
    int s0 = socket(AF_INET, SOCK_STREAM, 0);
    if(s0 < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }
 
    // Fill in server IP address
    struct sockaddr_in server;
    int serverAddrLen;
    bzero(&server, sizeof(server));
 
    char* peerHost = "localhost";

    if(argc > 1)
    {
        peerHost = argv[1];
    }

    // Resolve server address (convert from symbolic name to IP number)
    struct hostent *host = gethostbyname(peerHost);
    if(host == NULL)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }
 
    server.sin_family = AF_INET;
    short peerPort = 1234;
    if(argc >= 3)
    {
        peerPort = (short) atoi(argv[2]);
    }
    server.sin_port = htons(peerPort);
 
    // Write resolved IP address of a server to the address structure
    memmove(&(server.sin_addr.s_addr), host->h_addr_list[0], 4);
 
    // Connect to the remote server
    int res = connect(s0, (struct sockaddr*) &server, sizeof(server));
    if(res < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }

    // Take user input here:
    char user_input[] = "hello"; // Take input later. 

    // "encrypt"
    for(int i = 0; i < (sizeof(user_input)-1); ++i)
    {
        user_input[i] = (~user_input[i]); 
    }
    // TODO: Write encryption subroutine

    // Send user-input to server
    write(s0, user_input, sizeof(user_input));
    
    // Take server response
    char buffer[1024];
    res = read(s0, buffer, 1024);
    if(res < 0)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }
    buffer[res] = 0;
    //std::cout << "<SERVER SAYS>: " << buffer << std::endl;

    // "decrypt"
    // TODO: Write decryption subroutine
    for(int i = 0; i < sizeof(user_input)-1; ++i)
    {
        buffer[i] = (~buffer[i]);
    }

    std::cout << "Decrypted: " << buffer << std::endl;

    close(s0);

    return 0;
}
 
