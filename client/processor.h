#pragma once

#include "threadsafe_filework.h"
#include "network_connection_client.h"
#include "interruptible_thread.h"

#include <string>


class processor {
public:

    bool check_size(const std::string& msg) noexcept;
    bool check_num(const std::string& msg) noexcept;
    bool is_even(char number) noexcept;
    std::string replace_string(const std::string& msg);
    static std::string read_message();
    unsigned get_sum(const std::string& msg);

    void run_in_process();
    void run_out_process() noexcept;
private:
    threadsafe_filework _fworker;
};


