#include "network_connection_server.h"

#include <stdexcept>
#include <iostream>
#include <cstring>
#include <fcntl.h>

//TODO: нужна ли проверка на socket >= 0 ?
network_connection_server::~network_connection_server() {
    std::cout << "close socket\n";
    std::cout << shutdown(socket_client, 2);
    std::cout << shutdown(socket_server, 2);
    close(socket_client);
    close(socket_server);
}

void network_connection_server::connection_with_client() {
    if((socket_server = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::invalid_argument("Error create server socket descriptor\n");

    fcntl(socket_server, F_SETFL, O_NONBLOCK);
    server_addres.sin_port = htons(DEF_PORT);
    server_addres.sin_family = AF_INET;
    server_addres.sin_addr.s_addr = htonl(INADDR_ANY);

    if((bind(socket_server, (struct sockaddr *)&server_addres, sizeof(server_addres))) == -1)
        throw std::invalid_argument("Error bind socket\n");

    if(listen(socket_server, 1) == -1) {
        throw std::invalid_argument("Failure on seting que for connection\n");
    }
}

std::string network_connection_server::recv() {
    if (read(socket_client, buffer, 8) <= 0)
        throw std::invalid_argument("Error read from client socket\n");
    std::string res(buffer);
    std::memset(buffer, 0, 8);
    return res;
}