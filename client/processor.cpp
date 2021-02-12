#include "processor.h"


#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

void processor::run_in_process() {
    while(true) {
        try {
            interruption_point();
            std::string msg = read_message();
            interruption_point();
            if(msg == "exit") {
                _fworker.push("exit");
                break;
            }
            if(!check_size(msg)) throw std::invalid_argument("Message more than 64");
            if(!check_num(msg)) throw std::invalid_argument("Only numbers");
            std::sort(msg.rbegin(), msg.rend());
            msg = replace_string(msg);
            _fworker.push(msg);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << "\n";
        }
        catch (thread_interrupted& e) {
            throw;
        }

    }
}

void processor::run_out_process() noexcept{
    try {
        //TODO: корректное завершение при отключении сервера
        //TODO: зацикливается отправка на сервер при закрытии терминала клиента
        network_connection_client _net{};
        _net.connect_with_server();
        while (true) {
            std::string msg = _fworker.wait_and_pop();
            if (msg == "exit") {
                _net.try_send("end");
                break;
            }
            std::cout << msg << '\n';
            _net.try_send(std::to_string(get_sum(msg)));
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}


bool processor::check_size(const std::string &msg) noexcept {
    return msg.size() < 64;
}

bool processor::check_num(const std::string &msg) noexcept {
    return msg.find_first_not_of("0123456789") == std::string::npos;
}

bool processor::is_even(char number) noexcept {
    return (static_cast<int>(number) - 48) % 2 == 0;
}

std::string processor::replace_string(const std::string &msg) {
    std::string res;
    for(char c : msg) {
        if(is_even(c)) res += "KB";
        else res.push_back(c);
    }
    return res;
}

std::string processor::read_message() {
    std::string res;
    std::cin >> res;
    std::cin.ignore(32767,  '\n');
    return res;
}

unsigned processor::get_sum(const std::string &msg) {
    unsigned res = 0;
    for(char c : msg) {
        if(std::isdigit(static_cast<unsigned char>(c))) res += static_cast<unsigned>(c) - 48;
    }
    return res;
}

