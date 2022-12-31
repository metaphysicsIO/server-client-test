#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

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
    const short listen_port = 1234;
    const int packet_size = 1024;
    bool play = true;
    int addr_len;
    int s1;
    int max_clients = 100;
    int client_socket[max_clients] = {0};
    int sd;
    int max_sd;
    int action;
    int value;

    // set socket descriptors
    fd_set read_fds;

    // Create the socket
    int s0 = create_socket(); //socket(AF_INET, SOCK_STREAM, 0);

    // Set addr struct containing self-address
    sockaddr_in my_addr = set_self_addr(listen_port); // TODO: remove `listen_port` after server class made.

    // bind sock to addr
    bind(s0, (struct sockaddr*) &my_addr, sizeof(my_addr));

    // Set to close listen port at program termination
    struct linger linger_opt = {1,0};
    setsockopt(s0, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

    // Listen for connection
    //int conn = listen(s0, max_clients);
    listen(s0, max_clients);

    // Accept connection
    addr_len = sizeof(my_addr);

    // Continue until kill SIG
    while(play)
    {
        // clears set. First step for init file descriptor set.
        FD_ZERO(&read_fds);

        // add master socket to set (s0)
        FD_SET(s0, &read_fds);
        max_sd = s0;

        // Add child sockets to set
        for( int i = 0; i < max_clients; ++i)
        {
            // Socket descriptor
            sd = client_socket[i];

            // Check if socket is valid
            if(sd > 0)
            {
                // adds the file descriptor fd to set.
                FD_SET(sd, &read_fds);

                // Set the highest socket descriptor, for Select()
                if(sd > max_sd)
                {
                    max_sd = sd;
                }
            }
        }

        // Wait for action on a socket.
        // man: SELECT(2): 
        // select(readfds, writefds, exceptfds, nfds, timeout)
        action = select(max_sd+1, &read_fds, NULL, NULL, NULL);

        if((action < 0) && (errno!=EINTR))
        {
            std::cout << "SELECT ERR" << std::endl;
        }

        //Activity on master socket: incoming connection
        if(FD_ISSET(s0, &read_fds))
        {
            s1 = accept(s0, (struct sockaddr *) &my_addr, 
                       (socklen_t*)&addr_len);

            // Add socket to array of sockets
            for(int i = 0; i < max_clients; ++i)
            {
                // Find empty position
                if(client_socket[i] == 0)
                {
                    client_socket[i] = s1;
                    break;
                }
            }
        }

        //TODO: Use the map primative for managing non-empty sockets
        for(int i = 0; i < max_clients; ++i)
        {
            sd = client_socket[i];

            char buffer[packet_size];

            if(FD_ISSET(sd, &read_fds))
            {
                // Check buffers
                if((value = read(sd, buffer, packet_size)) == 0)
                {
                    // This means someone disconnected.
                    getpeername(sd, (struct sockaddr *) &my_addr, (socklen_t*)&addr_len);
                    printf("Disconnected - %s : %d\n", inet_ntoa(my_addr.sin_addr),
                                                    ntohs(my_addr.sin_port));
                    // Close socket
                    close(sd);
                    // Set as empty sock in list.
                    client_socket[i] = 0;
                }else{
                    buffer[value] = '\0';

                    getpeername(sd, (struct sockaddr *) &my_addr, (socklen_t*)&addr_len);

                    // Prints what the client has sent.
                    printf("[%s:%d]: %s\n", inet_ntoa(my_addr.sin_addr),ntohs(my_addr.sin_port),buffer);

                    // SEND
                    write(sd, buffer, packet_size);
                }
            }
        }
    }

    // Close sockets
    close(s0);
    close(s1);

    return 0;
}
