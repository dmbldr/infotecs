#pragma once

#include "threadsafe_filework.h"

#include <string>

class processor {
public:

    bool check_size(const std::string& msg) noexcept;
    bool check_num(const std::string& msg) noexcept;
    bool is_even(char number) noexcept;
    std::string replace_string(const std::string& msg);
    std::string read_message();

    void run_in_process();
    //void out_process();
private:
    threadsafe_filework _fworker;
};
