#include "server_processor.h"
#include "network_connection_server.h"

#include <stdexcept>
#include <iostream>

void server_processor::run() {
    try {
        network_connection_server net{};
        net.connection_with_client();
        std::cout << "Client connected\n";
        std::string msg;
        while((msg = net.recv()) != "end") {
            try {
                std::cout << msg << '\n';
                if(chek_num(std::stoi(msg))) std::cout << "The data is correct\n";
                else throw std::invalid_argument("The data is incorrect\n");
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
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