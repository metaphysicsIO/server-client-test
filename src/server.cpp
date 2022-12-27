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

struct sockaddr_in set_self_addr(short listen_port)
{
    //TODO: Remove arg when Server class made.
    struct sockaddr_in my_addr;

    memset(&my_addr, 0, sizeof(struct sockaddr_in));
    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(listen_port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    return my_addr;
}

int main()
{
    // TODO: Create server class.
    // TODO: Add variables as needed.
    const short listen_port = 1234;
    const int MAX_QUEUE_LENGTH = 1;
    const int packet_size = 1024;
    char exit[packet_size] = "quit";
    bool play = true;

    // Create the socket
    int s0 = create_socket(); //socket(AF_INET, SOCK_STREAM, 0);

    // Set addr struct containing self-address
    sockaddr_in my_addr = set_self_addr(listen_port); // TODO: remove `listen_port` after server class made.

    // bind sock to addr
    int res = bind(s0, (struct sockaddr*) &my_addr, sizeof(my_addr));

    // Set to close listen port at program termination
    struct linger linger_opt = {1,0};
    setsockopt(s0, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

    // Listen for connection
    int conn = listen(s0, MAX_QUEUE_LENGTH);

    // Accept connection
    struct sockaddr_in peer_addr;
    socklen_t peer_addr_len;
    int s1 = accept(s0, (struct sockaddr*) &peer_addr, &peer_addr_len);

    // Continue until kill SIG
    while(play)
    {
        // RECV from client
        char buffer[packet_size];
        conn = read(s1, buffer, packet_size);

        // Print client message
        std::cout << "<Client returns>: " << buffer << std::endl;

        // Respond to client (with client message)
        write(s1, buffer, sizeof(buffer));

        // Check if exiting.
        if(buffer == exit)
        {
            play = false;
        }
    }

    // Close sockets
    close(s0);
    close(s1);

    return 0;
}
