#include "network_connection.h"

#include <stdexcept>

network_connection::~network_connection() {
    close(sockfd);
}

void network_connection::connect_with_server() {
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::invalid_argument("Error create socket descriptor\n");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(DEF_PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    if(connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        throw std::invalid_argument("Error connect to server\n");
}

void network_connection::try_send(const std::string &msg) const {
    int sent = 0;
    if((sent = send(sockfd, msg.c_str(), msg.size(), 0)) < 0)
        throw std::invalid_argument("Error send to server \"" + msg + "\"");
}