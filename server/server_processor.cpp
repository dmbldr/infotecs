#include "server_processor.h"
#include "network_connection_server.h"

#include <stdexcept>
#include <iostream>

#include <csignal>
#include <cstring>

#include <fcntl.h>

volatile sig_atomic_t caught_signum = 0;

void handler(int signum) {
    caught_signum = signum;
}

void server_processor::run() {
    struct sigaction act{};
    std::memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    act.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &act, nullptr);
    sigaction(SIGINT, &act, nullptr);
    sigaction(SIGQUIT, &act, nullptr);

    try {
        network_connection_server net{};
        net.connection_with_client();
        std::string msg;
        while(caught_signum == 0) {
            fd_set readset;
            FD_ZERO(&readset);
            FD_SET(net.socket_server, &readset);
            FD_SET(net.socket_client, &readset);
            struct timeval timeout{};
            timeout.tv_sec = 0;
            timeout.tv_usec = 200000;
            if(select(std::max(net.socket_server, net.socket_client) + 1, &readset, nullptr, nullptr, &timeout) == -1)
                throw network_exception("Error: select");
            if(FD_ISSET(net.socket_server, &readset)) {
                net.socket_client = accept(net.socket_server, nullptr, nullptr);
                if(net.socket_client == -1)
                    throw network_exception("Error create client socket descriptor\n");
                fcntl(net.socket_client, F_SETFL, O_NONBLOCK);
                std::cout << "Client connected\n";
            }
            if(FD_ISSET(net.socket_client, &readset)) {
                msg = net.recv();
                if (msg == "end") break;
                std::cout << msg << '\n';
                if (chek_num(std::stoi(msg))) std::cout << "The data is correct\n";
                else std::cout << "The data is incorrect\n";
            }
        }
        std::cout << "Client disconnected\n";
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
}

bool server_processor::chek_num(int value) {
    if((value > 99) && (value % 32 == 0)) return true;
    return false;
}