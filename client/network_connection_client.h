#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>

class network_connection_client {
public:
    ~network_connection_client();

    void connect_with_server();
    void try_send(const std::string& msg) const;
private:
    int sockfd;
    struct sockaddr_in server_address;

    static const uint16_t DEF_PORT = 40001;
};

