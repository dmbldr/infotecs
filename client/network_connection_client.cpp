#include "network_connection_client.h"

#include <stdexcept>

//TODO: свои исключения для сетевых ошибок

network_connection_client::~network_connection_client() {
    shutdown(_sockfd, 2);
    close(_sockfd);
}

void network_connection_client::connect_with_server() {
    if((_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::invalid_argument("Error create socket descriptor\n");

    _server_address.sin_family = AF_INET;
    _server_address.sin_port = htons(DEF_PORT);
    _server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(_sockfd, (struct sockaddr *)&_server_address, sizeof(_server_address)) == -1)
        throw std::invalid_argument("Error connect to server\n");
}

void network_connection_client::try_send(std::string const& msg) const {
    const char *line = msg.c_str();
    if(write(_sockfd, line, 1) < 0)
        throw std::invalid_argument("Error send to server \"" + msg + "\"");
    if(write(_sockfd, line+1, msg.size()-1) < 0)
        throw std::invalid_argument("Error send to server \"" + msg + "\"");
}