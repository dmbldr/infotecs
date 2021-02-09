#include "network_connection_server.h"

network_connection_server::~network_connection_server() {
    close(socket_client);
    close(socket_server);
}

void network_connection_server::connection_with_client() {
    if((socket_server = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::invalid_argument("Error create server socket descriptor\n");

    server_address.sin_port = htons(DEF_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    if((bind(socket_server, (struct sockaddr *)&server_addres, sizeof(server_addres))) == -1)
        throw std::invalid_argument("Error bind socket\n");

    if(listen(server_socket, 1) == -1) {
        throw std::invalid_argument("Failure on seting que for connections\n");
    }

    if((socket_client = accept(socket_server, NULL, NULL)) == -1)
        throw std::invalid_argument("Error create client socket descriptor\n");
}

std::string network_connection_server::recv() {

}