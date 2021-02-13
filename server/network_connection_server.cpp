#include "network_connection_server.h"

#include <stdexcept>
#include <iostream>

#include <csignal>
#include <cstring>

//TODO: есть ли необходимость в отдельном классе сокет?
network_connection_server::~network_connection_server() {
    std::cout << "close socket\n";
    shutdown(socket_client, 2);
    shutdown(socket_server, 2);
    close(socket_client);
    close(socket_server);
}

void network_connection_server::connection_with_client() {
    struct sigaction act{};
    std::memset(&act, 0, sizeof(act));
    act.sa_handler = sig_handler;
    act.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &act, nullptr);

    if((socket_server = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::invalid_argument("Error create server socket descriptor\n");

    server_addres.sin_port = htons(DEF_PORT);
    server_addres.sin_family = AF_INET;
    server_addres.sin_addr.s_addr = htonl(INADDR_ANY);

    if((bind(socket_server, (struct sockaddr *)&server_addres, sizeof(server_addres))) == -1)
        throw std::invalid_argument("Error bind socket\n");

    if(listen(socket_server, 1) == -1) {
        throw std::invalid_argument("Failure on seting que for connections\n");
    }

    if((socket_client = accept(socket_server, nullptr, nullptr)) == -1)
        throw std::invalid_argument("Error create client socket descriptor\n");
}

std::string network_connection_server::recv() {
    if(read(socket_client, buffer, 8) == -1)
        throw std::invalid_argument("Error read from client socket\n");
    std::string res(buffer);
    return res;
}

void network_connection_server::sig_handler(int signum) const {
    shutdown(socket_client, 2);
    shutdown(socket_server, 2);
    close(socket_client);
    close(socket_server);
}