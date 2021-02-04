#pragma once

#include <thread>
#include <stdexcept>

class joining_thread {
public:
    explicit joining_thread(std::thread t) noexcept : _t(std::move(t))  {}
    ~joining_thread() noexcept;

    bool joinable() const noexcept;
    void join();

    joining_thread(const joining_thread&) = delete;
    joining_thread(joining_thread&&) = delete;
    joining_thread& operator=(const joining_thread&) = delete;
    joining_thread& operator=(joining_thread&&) = delete;
private:
    std::thread _t;
};

