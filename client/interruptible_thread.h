#pragma once

#include <atomic>
#include <thread>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <future>

class thread_interrupted : public std::exception {
public:
    explicit thread_interrupted(std::string error) : _error(std::move(error)) {}

    const char* what() const noexcept override {
        return _error.c_str();
    }
private:
    std::string _error;
};

class interrupt_flag {
public:
    std::atomic<bool> flag;

    void set();
    bool is_set() const;
};


inline interrupt_flag& this_thread_interrupt_flag() {
    static thread_local interrupt_flag tmp;
    return tmp;
}

//inline thread_local interrupt_flag this_thread_interrupt_flag;
void interruption_point();

class interruptible_thread {
public:
    template<typename F, typename T>
    interruptible_thread(F function, T instance) {
        std::promise<interrupt_flag*> p;
        internal_thread = std::thread([function, instance, &p] {
            p.set_value(&this_thread_interrupt_flag());
            try {
                (instance.get().*function)();
            }
            catch (thread_interrupted const& e) {
                e.what();
            }
        });
        flag = p.get_future().get();
    }
    ~interruptible_thread() {
        if(joinable()) join();
    }
    void join();
    bool joinable() const;
    void interrupt();
private:
    std::thread internal_thread;
    interrupt_flag* flag;
};
