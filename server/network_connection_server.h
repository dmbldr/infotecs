#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>

class network_connection_server {
public:
    ~network_connection_server();

    void connection_with_client();
    std::string recv();

    void sig_handler(int signum) const;
private:
    char buffer[8];
    int socket_client;
    int socket_server;
    struct sockaddr_in server_addres;

    static const uint16_t DEF_PORT = 40001;
};
