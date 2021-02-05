#include "processor.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>

void processor::run_in_process() {
    while(true) {
        std::string msg = read_message();
        //TODO: класс исключение означающий завершение работы
        if(msg == "exit") break;
        try {
            if(!check_size(msg)) throw std::invalid_argument("Message more than 64");
            if(!check_num(msg)) throw std::invalid_argument("Only numbers");
            std::sort(msg.rbegin(), msg.rend());
            msg = replace_string(msg);
            _fworker.push(msg);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
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