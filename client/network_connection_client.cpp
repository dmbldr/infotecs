#include "network_connection_client.h"

#include <stdexcept>
//TODO: свои исключения для сетевых ошибок
//TODO: нужна ли обработка errno?

network_connection_client::~network_connection_client() {
    close(sockfd);
}

void network_connection_client::connect_with_server() {
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::invalid_argument("Error create socket descriptor\n");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(DEF_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
        throw std::invalid_argument("Error connect to server\n");
}

void network_connection_client::try_send(const std::string &msg) const {
    //TODO: вместо <0 надо что-то другое? Что?
    if(send(sockfd, msg.c_str(), msg.size(), 0) < 0)
        throw std::invalid_argument("Error send to server \"" + msg + "\"");
}