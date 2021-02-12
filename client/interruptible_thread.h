#pragma once

#include <atomic>
#include <thread>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <future>

class thread_interrupted : public std::exception {
public:
    bool t_interrupted;
    thread_interrupted() : t_interrupted{ true } {}
};

class interrupt_flag {
public:
    std::atomic<bool> flag;

    void set();
    bool is_set() const;
};

thread_local interrupt_flag this_thread_interrupt_flag;
void interruption_point();

class interruptible_thread {
public:
    template<typename F, typename T>
    interruptible_thread(F function, T instance) {
        std::promise<interrupt_flag*> p;
        internal_thread = std::thread([function, instance, &p] {
            p.set_value(&this_thread_interrupt_flag);
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
        if(internal_thread.joinable()) internal_thread.join();
    }
    void join();
    void detach();
    bool joinable() const;
    void interrupt();
private:
    std::thread internal_thread;
    interrupt_flag* flag;
};