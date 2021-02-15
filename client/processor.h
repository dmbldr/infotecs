#pragma once

#include "threadsafe_filework.h"
#include "network_connection_client.h"
#include "interruptible_thread.h"

#include <string>


class processor {
public:
    void run_in_process();
    void run_out_process() noexcept;

    bool check_size(std::string const& msg) noexcept;
    bool check_num(std::string const& msg) noexcept;
    bool is_even(char number) noexcept;
    std::string replace_string(std::string const& msg);
    static std::string read_message();
    unsigned get_sum(std::string const& msg);
private:
    threadsafe_filework _fworker;
};


