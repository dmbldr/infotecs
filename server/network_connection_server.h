#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>

class network_exception : public std::exception {
public:
    explicit network_exception(std::string error) : _error(std::move(error)) {}

    const char* what() const noexcept override {
        return _error.c_str();
    }
private:
    std::string _error;
};

class network_connection_server {
public:
    ~network_connection_server();

    void connection_with_client();
    std::string recv();

    int socket_client = -1;
    int socket_server = -1;
private:
    char buffer[8]{};
    struct sockaddr_in server_addres{};

    static const uint16_t DEF_PORT = 40001;
};
