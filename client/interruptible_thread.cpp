#include "interruptible_thread.h"

void interruption_point() {
    if (this_thread_interrupt_flag().is_set()) {
        throw thread_interrupted("The second thread has finished work. ");
    }
}

void interruptible_thread::join() {
    internal_thread.join();
}
bool interruptible_thread::joinable() const {
    return internal_thread.joinable();
}
void interruptible_thread::interrupt() {
    if (flag) flag->set();
}

void interrupt_flag::set() {
    flag.store(true, std::memory_order_relaxed);
}
bool interrupt_flag::is_set() const {
    return flag.load(std::memory_order_relaxed);
}