#pragma once

#include <mutex>
#include <condition_variable>

#include <iostream>
#include <fstream>
#include <string>
#include <utility>


class threadsafe_filework {
public:
    explicit threadsafe_filework(std::string file_name) : _file_name(std::move(file_name)) {};

    void push(const std::string& msg);
    std::string wait_and_pop();
    bool empty() const;

    //TODO: какие операции стоит запретить

    threadsafe_filework(const threadsafe_filework&) = delete;
    threadsafe_filework(threadsafe_filework&&) = delete;
    threadsafe_filework& operator=(const threadsafe_filework&) = delete;
    threadsafe_filework& operator=(threadsafe_filework&&) = delete;
private:
    mutable std::mutex _mtx;
    std::condition_variable _del_cond;
    std::string _file_name;
};
